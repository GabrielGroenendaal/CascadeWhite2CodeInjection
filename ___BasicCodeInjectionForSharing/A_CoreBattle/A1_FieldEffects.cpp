#include "codeinjection_new.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// Uses esdb_newBattle.yml

extern "C"
{

#pragma region SpeedChecks

    /* Checks to see if we're in Skyla's Gym, multiplying the speed of flying types if so */
    int checkSkylaGym(ServerFlow *a1, int a2)
    {
        PlayerState *playerState;
        int zoneId;

        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);
        if (zoneId == 108 && Handler_CheckFloating(a1, a2))
        {
            // k::Printf("\nSkyla's Wind is Blowing\n");
            return 6144;
        }
        else
        {
            return 4096;
        }
    }

    /*

       --------------------------------------------------------------------------------------------------
       ------------------------------------ CALCULATE SPEED  -------------------------------------------
       --------------------------------------------------------------------------------------------------

   */

    int THUMB_BRANCH_SAFESTACK_ServerEvent_CalculateSpeed(ServerFlow *a1, BattleMon *a2, bool IsTrickRoomEnabled)
    {
        int Value;
        int ID;
        int v8;
        PlayerState *playerState;
        int zoneId;
        int v9;
        unsigned int v10;

        Value = BattleMon_GetValue(a2, VALUE_SPEED_STAT);
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        int mulValue = checkSkylaGym(a1, ID);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetConstValue(VAR_SPEED, Value);
        BattleEventVar_SetValue(VAR_GENERAL_USE_FLAG, 1);
        BattleEventVar_SetValue(VAR_TRICK_ROOM_FLAG, 0);
        BattleEventVar_SetMulValue(VAR_RATIO, mulValue, 410, 0x20000);

        BattleEvent_CallHandlers(a1, EVENT_CALC_SPEED);
        v8 = BattleEventVar_GetValue(VAR_SPEED);
        v9 = BattleEventVar_GetValue(VAR_RATIO);
        v10 = fixed_round(v8, v9);

        if (BattleMon_CheckIfMoveCondition(a2, CONDITION_PARALYSIS) && BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG))
        {
            v10 = fixed_round(v8, 1024);
        }

        if (v10 > 10000)
        {
            LOWORD(v10) = 10000;
        }

        if (IsTrickRoomEnabled && BattleEventVar_GetValue(VAR_TRICK_ROOM_FLAG))
        {

            LOWORD(v10) = 10000 - v10;
        }

        BattleEventVar_Pop();
        return v10;
    }

#pragma endregion

#pragma region Power

    /*

       --------------------------------------------------------------------------------------------------
       ------------------------------------ GET ATTACK POWER --------------------------------------------
       --------------------------------------------------------------------------------------------------

       Here's where we hard code the effects of Foul Play, Body Press.
   */

    int THUMB_BRANCH_SAFESTACK_ServerEvent_GetAttackPower(
        ServerFlow *a1,
        BattleMon *AttackingMon,
        BattleMon *DefendingMon,
        MoveParam *a4,
        int criticalFlag)
    {
        BattleMonValue v8;         // r4
        int ID;                    // r0
        int v10;                   // r0
        int Value;                 // r1
        unsigned __int16 RealStat; // r0
        int v13;                   // r4
        int v14;                   // r4
        int v15;                   // r0
        int v16;                   // r4

        v8 = VALUE_SPECIAL_ATTACK_STAT;
        if (PML_MoveGetCategory(a4->MoveID) != 2)
        {
            v8 = VALUE_ATTACK_STAT;
        }
        if (a4->MoveID == MOVE206_BODY_PRESS)
        {
            v8 = VALUE_DEFENSE_STAT;
        }

        BattleEventVar_Push();
        ID = BattleMon_GetID(AttackingMon);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v10 = BattleMon_GetID(DefendingMon);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v10);
        BattleEventVar_SetValue(VAR_SWAP_POKE_ID, 31);

        BattleEventVar_SetValue(VAR_GENERAL_USE_FLAG, 0);
        BattleEvent_CallHandlers(a1, EVENT_BEFORE_ATTACKER_POWER);
        Value = BattleEventVar_GetValue(VAR_SWAP_POKE_ID);

        if (Value != 31)
        {
            AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, Value);
        }

        if (a4->MoveID == MOVE492_FOUL_PLAY)
        {
            AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, BattleMon_GetID(DefendingMon));
        }

        if (BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG) != 0)
        {
            RealStat = BattleMon_GetRealStat(AttackingMon, v8);
        }
        else if (criticalFlag)
        {
            RealStat = BattleMon_GetStatsForCritDamage(AttackingMon, v8);
        }
        else
        {

            RealStat = BattleMon_GetValue(AttackingMon, v8);
        }

        // // If we're using body press and it's hailing, we get a boostie.
        // if (v8 == VALUE_DEFENSE_STAGE && BattleMon_HasType(AttackingMon, TYPE_ICE) && ServerEvent_GetWeather(a1) == 3)
        // {
        //     RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        // }
        // if (v8 == VALUE_DEFENSE_STAGE && AttackingMon->HeldItem == IT0538_EVIOLITE && Handler_CheckEvolution(a1, ID))
        // {
        //     RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        // }
        // if (v8 == VALUE_DEFENSE_STAGE && (AttackingMon->HeldItem == IT0225_MASCOT_BADGE || AttackingMon->HeldItem == IT0215_TERA_BADGE))
        // {
        //     RealStat = (unsigned __int16)fixed_round(RealStat, 8192);
        // }
        // if (v8 == VALUE_DEFENSE_STAGE && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL063_MARVEL_SCALE && BattleMon_GetStatus(AttackingMon))
        // {
        //     RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        // }

        v13 = RealStat;

        // if (!Handler_IsSimulationMode(a1))
        //{
        // }

        BattleEventVar_SetConstValue(VAR_MOVE_ID, a4->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4->moveType);
        BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, a4->category);
        BattleEventVar_SetValue(VAR_POWER, v13);
        BattleEventVar_SetMulValue(VAR_RATIO, 4096, 410, 0x20000);
        BattleEvent_CallHandlers(a1, EVENT_ATTACKER_POWER);

        v14 = BattleEventVar_GetValue(VAR_POWER);
        v15 = BattleEventVar_GetValue(VAR_RATIO);
        v16 = fixed_round(v14, v15);

        BattleEventVar_Pop();
        return v16;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ GET TARGET DEFENSES -----------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    int THUMB_BRANCH_SAFESTACK_ServerEvent_GetTargetDefenses(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4, int a5)
    {
        BattleMonValue v7;         // r4
        int ID;                    // r0
        int v9;                    // r0
        int v10;                   // r0
        int Value;                 // r7
        unsigned __int16 RealStat; // r0
        int v13;                   // r7
        int v14;                   // r0
        int v15;                   // r0
        int v16;                   // r5
        int v17;                   // r6
        int category;              // [sp+8h] [bp-18h]
        BattleEventVar checkVar;

        v7 = VALUE_SPECIAL_DEFENSE_STAT;
        if (PML_MoveGetCategory(a4->MoveID) != 2)
        {
            v7 = VALUE_DEFENSE_STAT;
        }
        category = a4->category;
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v9 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v9);
        BattleEventVar_SetConstValue(VAR_BATTLE_MON_STAT, v7);
        BattleEventVar_SetValue(VAR_BATTLE_MON_STAT_SWAP_FLAG, 0);
        BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);
        BattleEvent_CallHandlers(a1, EVENT_BEFORE_DEFENDER_GUARD);

        /* Psyshock Check */
        if ((BattleEventVar_GetValue(VAR_BATTLE_MON_STAT_SWAP_FLAG) & 1) != 0 || a4->MoveID == MOVE473_PSYSHOCK || a4->MoveID == MOVE540_PSYSTRIKE)
        {
            if (v7 == VALUE_DEFENSE_STAT)
            {
                v7 = VALUE_SPECIAL_DEFENSE_STAT;
            }
            else
            {
                v7 = VALUE_DEFENSE_STAT;
            }
            if (v7 == VALUE_DEFENSE_STAT)
            {
                v10 = 1;
            }
            else
            {
                v10 = 2;
            }
            category = v10;
        }
        Value = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);

        BattleEventVar_Pop();
        if (Value)
        {
            RealStat = BattleMon_GetRealStat(a3, v7);
        }
        else if (a5)
        {
            RealStat = BattleMon_GetStatsForCritDamage(a3, v7);
        }
        else
        {
            RealStat = BattleMon_GetValue(a3, v7);
        }
        v13 = RealStat;

        /* Sand Boost for Rock Types*/
        if (ServerEvent_GetWeather(a1) == 4 && BattleMon_HasType(a3, TYPE_ROCK) && v7 == VALUE_SPECIAL_DEFENSE_STAT)
        {
            v13 = fixed_round(v13, 6144);
        }
        /* Defense Boost for Ice Types */
        if (ServerEvent_GetWeather(a1) == 3 && BattleMon_HasType(a3, TYPE_ICE) && v7 == VALUE_DEFENSE_STAT)
        {
            v13 = fixed_round(v13, 6144);
        }

        BattleEventVar_Push();
        v14 = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v14);
        v15 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v15);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a4->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4->moveType);
        BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, category);
        BattleEventVar_SetValue(VAR_GUARD, v13);
        BattleEventVar_SetMulValue(VAR_RATIO, 4096, 410, 0x20000);
        BattleEvent_CallHandlers(a1, EVENT_DEFENDER_GUARD);
        v16 = BattleEventVar_GetValue(VAR_GUARD);
        v17 = BattleEventVar_GetValue(VAR_RATIO);
        BattleEventVar_Pop();

        return fixed_round(v16, v17);
    }

#pragma endregion

#pragma region ShedinjaFix
    extern int __aeabi_idiv(s32 a1, s32 a2);

    void THUMB_BRANCH_SAFESTACK_PokeParty_RecalcStatsCore(PartyPkm *pPkm)
    {
        u32 Param;           // r6
        signed __int32 v3;   // r7
        signed __int32 v4;   // r5
        u32 v5;              // r0
        u16 v6;              // r5
        u16 Nature;          // r0
        u32 v8;              // r0
        u16 v9;              // r5
        u16 v10;             // r0
        u32 v11;             // r0
        u16 v12;             // r5
        u16 v13;             // r0
        u32 v14;             // r0
        u16 v15;             // r5
        u16 v16;             // r0
        u32 v17;             // r0
        u16 v18;             // r5
        u16 v19;             // r0
        u32 v20;             // r0
        signed __int32 data; // [sp+0h] [bp-58h]
        PersonalData *BW2;   // [sp+4h] [bp-54h]
        u32 v23;             // [sp+8h] [bp-50h]
        signed __int32 v24;  // [sp+Ch] [bp-4Ch]
        signed __int32 v25;  // [sp+10h] [bp-48h]
        signed __int32 v26;  // [sp+14h] [bp-44h]
        signed __int32 v27;  // [sp+18h] [bp-40h]
        signed __int32 v28;  // [sp+1Ch] [bp-3Ch]
        u32 v29;             // [sp+20h] [bp-38h]
        u32 v30;             // [sp+24h] [bp-34h]
        u32 v31;             // [sp+28h] [bp-30h]
        u32 v32;             // [sp+2Ch] [bp-2Ch]
        u32 v33;             // [sp+30h] [bp-28h]
        u32 v34;             // [sp+34h] [bp-24h]
        u32 v35;             // [sp+38h] [bp-20h]
        u16 v36;             // [sp+40h] [bp-18h]

        Param = PokeParty_GetParam(pPkm, PF_Level, 0);
        v34 = PokeParty_GetParam(pPkm, PF_MaxHP, 0);
        v3 = PokeParty_GetParam(pPkm, PF_NowHP, 0);
        v35 = PokeParty_GetParam(pPkm, PF_IvHP, 0);
        v4 = PokeParty_GetParam(pPkm, PF_EvHP, 0);
        v33 = PokeParty_GetParam(pPkm, PF_IvATK, 0);
        v28 = PokeParty_GetParam(pPkm, PF_EvATK, 0);
        v32 = PokeParty_GetParam(pPkm, PF_IvDEF, 0);
        v27 = PokeParty_GetParam(pPkm, PF_EvDEF, 0);
        v31 = PokeParty_GetParam(pPkm, PF_IvSPE, 0);
        v26 = PokeParty_GetParam(pPkm, PF_EvSPE, 0);
        v30 = PokeParty_GetParam(pPkm, PF_IvSPA, 0);
        v25 = PokeParty_GetParam(pPkm, PF_EvSPA, 0);
        v29 = PokeParty_GetParam(pPkm, PF_IvSPD, 0);
        v24 = PokeParty_GetParam(pPkm, PF_EvSPD, 0);
        v36 = PokeParty_GetParam(pPkm, PF_Forme, 0);
        v23 = PokeParty_GetParam(pPkm, PF_Species, 0);
        BW2 = PML_PersonalLoadBW2(v23, v36);
        v5 = Param + __aeabi_idiv(((__aeabi_idiv(v4, 4) + v35 + 2 * BW2->BaseHP) * Param), 100) + 10;
        data = v5;
        PokeParty_SetParam(pPkm, PF_MaxHP, v5);
        // v6 = ((v28 / 4 + v33 + 2 * BW2->BaseATK) * Param) / 100 + 5;
        v6 = __aeabi_idiv(((__aeabi_idiv(v28, 4) + v33 + 2 * BW2->BaseATK) * Param), 100) + 5;
        Nature = PokeParty_GetNature(pPkm);
        v8 = adjustStatForNature(Nature, v6, 1);
        PokeParty_SetParam(pPkm, PF_ATK, v8);
        // v9 = ((v27 / 4 + v32 + 2 * BW2->BaseDEF) * Param) / 100 + 5;
        v9 = __aeabi_idiv(((__aeabi_idiv(v27, 4) + v32 + 2 * BW2->BaseDEF) * Param), 100) + 5;
        v10 = PokeParty_GetNature(pPkm);
        v11 = adjustStatForNature(v10, v9, 2);
        PokeParty_SetParam(pPkm, PF_DEF, v11);
        v12 = __aeabi_idiv(((__aeabi_idiv(v26, 4) + v31 + 2 * BW2->BaseSPE) * Param), 100) + 5;
        // v12 = ((v26 / 4 + v31 + 2 * BW2->BaseSPE) * Param) / 100 + 5;
        v13 = PokeParty_GetNature(pPkm);
        v14 = adjustStatForNature(v13, v12, 5);
        PokeParty_SetParam(pPkm, PF_SPE, v14);
        v15 = __aeabi_idiv(((__aeabi_idiv(v25, 4) + v30 + 2 * BW2->BaseSPA) * Param), 100) + 5;

        // v15 = ((v25 / 4 + v30 + 2 * BW2->BaseSPA) * Param) / 100 + 5;
        v16 = PokeParty_GetNature(pPkm);
        v17 = adjustStatForNature(v16, v15, 3);
        PokeParty_SetParam(pPkm, PF_SPA, v17);
        // v15 = __aeabi_fdiv(((__aeabi_fdiv(v25, 4) + v30 + 2 * BW2->BaseSPA) * Param), 100) + 5;
        v18 = __aeabi_idiv(((__aeabi_idiv(v24, 4) + v29 + 2 * BW2->BaseSPD) * Param), 100) + 5;
        v19 = PokeParty_GetNature(pPkm);
        v20 = adjustStatForNature(v19, v18, 4);
        PokeParty_SetParam(pPkm, PF_SPD, v20);
        if (v3 || !v34)
        {
            if (v3)
            {
                if ((data - v34) >= 0)
                {
                    v3 += data - v34;
                }
                else if (v3 > data)
                {
                    v3 = data;
                }
            }
            else
            {
                v3 = data;
            }
        }
        if (v3)
        {
            PokeParty_SetParam(pPkm, PF_NowHP, v3);
        }
    }
#pragma end region
#pragma region NewUIChanges

    bool THUMB_BRANCH_IsTrainerOT(BoxPkm *pPkm, void *pTrainerInfo)
    {
        return 1;
    }
    // enum BottomScreenMenuState
    // {
    //     STATE_WAITING = 0x0,
    //     STATE_FIGHT = 0x1,
    //     STATE_MOVE_SELECT = 0x2,
    //     STATE_TARGET_SELECT = 0x3,
    //     STATE_YESNO = 0x4,
    //     STATE_ROTATION = 0x5,
    //     STATE_RECORD_PLAYBACK = 0x6,
    //     STATE_ENTREE_CATCH = 0x7,
    // };
    // struct BtlvInput_ClActObj
    // {
    //     void *obj;
    //     s16 x;
    //     s16 y;
    // };

    // struct SWAN_PACKED SWAN_ALIGNED(2) BtlvFingerCursorHandle
    // {
    //     void *dword0;
    //     void *field_4;
    //     void *dword8;
    //     _DWORD dwordC;
    //     _DWORD dword10;
    //     _DWORD dword14;
    //     int field_18;
    //     int field_1C;
    //     int field_20;
    //     int field_24;
    //     int field_28;
    //     _WORD HeapID;
    // };

    // struct BtlvInput_DirectionParam
    // {
    //     char field_0;
    //     u8 status;
    //     u16 pad;
    //     u16 HP;
    //     u16 MaxHP;
    //     int field_8;
    // };

    // struct BtlvInput
    // {
    //     TCBManager *tcbManager;
    //     int tcbData;
    //     void *TCBArray[8];
    //     void (*TCBCallbacks[8])(void *);
    //     ArcTool *UIGraphicsNarcPtr;
    //     GameData *gameData;
    //     BattleStyle battleStyle;
    //     BtlType BattleType;
    //     BottomScreenMenuState MenuState;
    //     void *msgData;
    //     BtlvFingerCursorHandle *FingerCursor;
    //     PalAnm *palAnm;
    //     unsigned int Flags;
    //     int Flags2;
    //     int TouchpadUsed;
    //     BtlvInput_DirectionParam field_74[6];
    //     BtlvInput_DirectionParam field_BC[6];
    //     int UIExtraIconsNCGR;
    //     int UIExtraIconsNCLR;
    //     int UIPokeballIconNCER;
    //     int UIButtonSelectCursorNCGR;
    //     int UIButtonSelectCursorNCER;
    //     void *BallIconClAct;
    //     BtlvInput_ClActObj PlayerBallIcons[6];
    //     BtlvInput_ClActObj EnemyBallIcons[6];
    //     void *CursorClAct;
    //     BtlvInput_ClActObj cursor[6];
    //     int MonIconNCGRs[3];
    //     int UIMonIconsNCLR;
    //     int UIMonIconsNCER;
    //     void *MonIconClAct;
    //     BtlvInput_ClActObj MonIconObj[3];
    //     int MoveTypeIconNCGRs[4];
    //     int MoveTypeIconNCLR;
    //     int MoveTypeIconNCER;
    //     void *MoveTypeClAct;
    //     void *MoveTypeObjs[4];
    //     void *WeatherClAct;
    //     void *WeatherObj[2];
    //     void *StruggleClAct;
    //     void *StruggleObj;
    //     int field_220;
    //     int AudienceNCLR;
    //     int AudienceNCER;
    //     void *field_22C;
    //     void *AudienceObj[22];
    //     int AudienceFlag;
    //     void *PokestarTheaterBGPalette;
    //     void *PokestarTheaterPersonPalette;
    //     int AudiencePaletteMode;
    //     int AudienceTimer;
    //     int AudienceAnimID;
    //     int AudienceLoopNum;
    //     int AudiencePaletteFlag;
    //     GFLFont *font;
    //     void *BmpWin1;
    //     void *Bitmap1;
    //     void *BmpWin2;
    //     void *Bitmap2;
    //     void *mainLoop;
    //     int mainLoopTCBFlag;
    //     HeapID heapID;
    //     u8 SelectedButtonPos[3][8];
    //     u8 IsButtonEnabled[8];
    //     u8 DoesSlotHaveMove[4];
    //     u16 SelectedMoves[3];
    //     u16 MoveIDs[4];
    //     u8 *cursorMode;
    //     int ActiveMonViewPos;
    //     int ViewPos;
    //     int IsTransformed;
    //     u16 BagPalette[16];
    //     char multiBattleMode;
    //     char IsPokestar;
    //     u8 NumAudienceMembers;
    //     char field_32B;
    //     int AudienceBit;
    //     BattleMon *ActiveMons[3];
    //     int field_33C[3][4];
    // };

    // int THUMB_BRANCH_BtlvInput_ChangeUIFileIDForPokestar(int result, BtlvInput *a2)
    // {
    //     k::Printf("\n\n===BtlvInput_ChangeUIFileIDForPokestar===\nresult is %d and a2->isPokeStar is %d\n\n", result, a2->IsPokestar);
    //     if (a2->IsPokestar)
    //     {
    //         result += 134;
    //     }
    //     return result;
    // }

    // extern int BtlvEffectMain_GetBattleMode();
    // extern int BtlvInput_ChangeUIFileIDForBattleMode(int result, BtlvInput *a2);

    // int THUMB_BRANCH_BtlvInput_GetFightScreenButtonNSCRFileID(BtlvInput *a1)
    // {
    //     u8 v2;                   // zf
    //     BattleStyle battleStyle; // r0
    //     v2 = a1->Flags << 27 >> 31 == 0;
    //     battleStyle = a1->battleStyle;
    //     if (v2)
    //     {
    //         if (battleStyle == BTL_STYLE_TRIPLE)
    //         {
    //             if (BtlvEffectMain_GetBattleMode() == 1)
    //             {
    //                 if (a1->ActiveMonViewPos != 4)
    //                 {
    //                     // v2 == 1, battleStyle == triples, bag enabled, at the first mon of selection
    //                     return BtlvInput_ChangeUIFileIDForBattleMode(363, a1);
    //                 }
    //                 // v2 == 1, battleStyle == triples, bag enabled, NOT at the first mon of selection
    //                 return BtlvInput_ChangeUIFileIDForBattleMode(369, a1);
    //             }
    //             if (a1->ActiveMonViewPos != 4)
    //             {
    //                 // v2 == 1, battleStyle == triples, bag disabled, at the first mon of selection
    //                 return BtlvInput_ChangeUIFileIDForBattleMode(362, a1);
    //             }
    //         }
    //         else if (BtlvEffectMain_GetBattleMode() == 1)
    //         {
    //             // v2 = 1, battleStyle != triple, bag enabled
    //             return BtlvInput_ChangeUIFileIDForBattleMode(369, a1);
    //         }
    //         // v2 == 1, battyleStyle == triple, bag not enabeld
    //         return BtlvInput_ChangeUIFileIDForBattleMode(361, a1);
    //     }

    //     if (battleStyle != BTL_STYLE_TRIPLE || a1->ActiveMonViewPos == 4)
    //     {
    //         if (BtlvEffectMain_GetBattleMode() == 1)
    //         {
    //             // v2 == 0, battleStyle != triples, bag enabled, NOT at the first mon of selection
    //             return BtlvInput_ChangeUIFileIDForBattleMode(370, a1);
    //         }
    //         else
    //         {
    //             // v2 == 0, battleStyle != triples, bag disabled, NOT at the first mon of selection
    //             return BtlvInput_ChangeUIFileIDForBattleMode(364, a1);
    //         }
    //     }
    //     else if (BtlvEffectMain_GetBattleMode() == 1)
    //     {
    //         // v2 == 0, bag enabled
    //         return BtlvInput_ChangeUIFileIDForBattleMode(371, a1);
    //     }
    //     else
    //     {
    //         // v2 == 0, bag disabled
    //         return BtlvInput_ChangeUIFileIDForBattleMode(365, a1);
    //     }
    // }

#pragma endregion
}

extern "C" void THUMB_BRANCH_SAFESTACK_PML_PkmSetMetParamsEx(BoxPkm *pPkm, u16 location, u16 year, u16 month, u16 day, bool isWild)
{
    __int16 v8; // r5
    u16 alteredLocation;

    alteredLocation = location;
    // k::Printf("\nSetting Met Params for Pkm %d: Loc %d, Date %d/%d/%d, isWild %d\n", pPkm->pid, location, month, day, year, isWild);
    if (location == 125    // Route 20
        || location == 72  // Lostlorn Forest
        || location == 122 // Floccessy Town
    )
    {
        PlayerState *playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        VecFx32 *vec = PlayerState_GetWPos(playerState);
        int zoneId = PlayerState_GetZoneID(playerState);

        // Route 20
        if (location == 122 && zoneId == 440)
        {
            alteredLocation = 94;
        }
        // Route 20
        if (zoneId == 446 && location == 125 && vec->y <= 0)
        {
            alteredLocation = 93;
        }
        // Lostlorn Forest
        if (location == 72 && zoneId == 385 && vec->z <= 1925120)
        {
            alteredLocation = 95;
        }
    }

    PML_PkmSetParam(pPkm, (PkmField)(isWild + 149), alteredLocation);
    v8 = (3 * isWild);
    PML_PkmSetParam(pPkm, (PkmField)(v8 + 143), year);
    PML_PkmSetParam(pPkm, (PkmField)(v8 + 144), month);
    PML_PkmSetParam(pPkm, (PkmField)(v8 + 145), day);
};

//  REMOVING SIMIPOUR, SIMISAGE, and SIMISEAR from evolution check for mascot badge/eviolite
extern "C" int HaveEvolutionRoot(ArcTool *a1, u16 a2, int a3, int a4);
extern "C" int THUMB_BRANCH_SAFESTACK_Handler_CheckEvolution(int a1, int a2)
{
    BattleMon *BattleMon; // r0
    u16 Species;          // r6
    unsigned int i;       // r4

    BattleMon = PokeCon_GetBattleMon((void *)(a1 + 8), a2);
    Species = BattleMon_GetSpecies(BattleMon);
    for (i = 0; i < 7; i = (i + 1))
    {
        if (Species == PK516_SIMIPOUR || Species == PK512_SIMISAGE || Species == PK514_SIMISEAR)
        {
            return 0;
        }
        if (HaveEvolutionRoot((ArcTool *)(a1 + 1188), Species, 0, i))
        {
            return 1;
        }
    }
    return 0;
};


// FIXING ABILITY CAPSULES 

extern "C" u32 PML_PkmGetParam(BoxPkm *pPkm, PkmField field, u32 data);
extern "C" int GetPersonalAbilCount(PersonalData *p);
extern "C" void THUMB_BRANCH_SAFESTACK_setAbilityForForm(BoxPkm *pPkm, u16 species)
{
    u16 Param;        // r0
    u32 v5;           // r7
    PersonalField v6; // r6
    int v7;           // r4
    u32 v8;           // r0
    PersonalData *p;  // [sp+0h] [bp-18h]

    Param = PML_PkmGetParam(pPkm, PF_Forme, 0);
    p = PML_PersonalLoadBW2(species, Param);
    v5 = PML_PkmGetParam(pPkm, PF_PID, 0);
    v6 = Personal_Abil1;
    v7 = 0x10000;
    if (PML_PkmGetParam(pPkm, PF_MetGameVersion, 0) < 0x14)
    {
        v7 = 1;
    }
    if (PML_PkmGetParam(pPkm, PF_IsHiddenAbility, 0))
    {
        v6 = Personal_AbilH;
    }
    else if (GetPersonalAbilCount(p) == 2 && (v5 & v7) != 0)
    {
        v6 = Personal_Abil2;
    }
    else
    {
    }

    if (PML_PkmGetParam(pPkm, PF_ContestCool, 0) == 1)
    {
        if (v6 == Personal_Abil1)
            v6 = Personal_Abil2;
        else if (v6 == Personal_Abil2)
            v6 = Personal_Abil1;
        else
        {
        }
    }
    v8 = PML_PersonalGetParam(p, v6);
    PML_PkmSetParam(pPkm, PF_Ability, v8);
};

extern "C" u32 THUMB_BRANCH_SAFESTACK_getPkmAbilSlotNumber(BoxPkm *pPkm)
{
    unsigned __int8 v2; // r4
    u16 Param;          // r6
    u16 v4;             // r0
    u32 v5;             // r7
    int v6;             // r6
    PersonalData *p;    // [sp+0h] [bp-18h]
    int result;

    v2 = 0;
    Param = PML_PkmGetParam(pPkm, PF_Species, 0);
    v4 = PML_PkmGetParam(pPkm, PF_Forme, 0);
    p = PML_PersonalLoadBW2(Param, v4);
    v5 = PML_PkmGetParam(pPkm, PF_PID, 0);
    v6 = 0x10000;
    result = 0;
    if (PML_PkmGetParam(pPkm, PF_MetGameVersion, 0) < 0x14)
    {
        v6 = 1;
    }
    if (PML_PkmGetParam(pPkm, PF_IsHiddenAbility, 0))
    {
        result = 2;
    }
    else if (GetPersonalAbilCount(p) == 2 && (v5 & v6) != 0)
    {
        result = 1;
    }
    else {

    }
    if (PML_PkmGetParam(pPkm, PF_ContestCool, 0) == 1)
    {
        if (result == 0)
            result = 1;
        else if (result == 1)
            result = 0;
        else
        {
        }
    }

    return result;
}