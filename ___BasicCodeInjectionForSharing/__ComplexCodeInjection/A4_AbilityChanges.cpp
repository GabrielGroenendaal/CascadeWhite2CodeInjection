
#include "definitions/settings.h"
#include "definitions/A_CodeInjection.h"
#include "definitions/kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define TRYING_BATTLESCAN_EXPANSION false
#define USING_OVERRIDE_CONTACT false
// Uses esdb_newBattle.yml





#pragma region Notes
/* 
    
    ABILITY TABLE EDITS:    
        Somewhere in the code exists a table like the Move handle effect table. 
        We are going to edit this table to change the pointers for a bunch of abilities. 
        
        Luckily we don't need to carefully manage handlers too much. They're pretty plentiful. 

        [ ATE ABILITIES ]
            I mostly want to combine these to save space. 

            Refrigerate: 
                Double check that refrigerate doesn'tt work properly right now. If it does i'm even more confused .

                This is not currently assigned in the code 
                It's in theory attached to telepathy fsr. 
                Current Abil: 140 (8C in hex)
                Points To: EventAddTelepathy (89 1B 1C 02)
                Change to: EventAddStickyHold (39 11 1C 02) 
                
            Oblivious: 
                Abil No: 12 (0C in hex)
                Points To: EventAddOblivious (A5 EE 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)

            Super Luck: 
                Abil No: 105 (69 in hex)
                Points To: EventAddSuperLuck (55 F4 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)
            
            Magma Armor: 
                Abil No: 40 (28 in hex)
                Points To: EventAddMagmaArmor (21 ED 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)


        
        [ CLONE ABILITIES ]
            These abilities have the same effect as other abilities but a unique ABiL ID. 
            That's limited real estate so we should combine them. 

            Vital Spirit: 
                Abil No: 72 (48 in hex)
                Points To: EventAddInsomnia (E1 EC 1B 02)
                Change To: EventAddShieldDust (81 F2 1B 02)
                Name: Vital Spirit -> Resilient
            
            Illuminate
                Abil No. 35 (23 in hex)
                Points To: None 
                Change To: EventAddCompoundeyes (A5 E2 1B 02)
*/
/* 
    See if we can implement the following changes as hex edits to save space. 
    
        - Regenerator Nerf 
        - Stench Buff 
        - Dry Skin Nerf
        - Iron Fist Buff 
        - Weak Armor Buff 
*/
/* 
    ORPHANED ABILITY HANDLERS 

    Steadfast isn't being used 
    Defeatist isn't being used 
    Liquid Ooze isn't being used 
    Zen Mode isn't being used 
    Color Change isn't being used
    Ballistics isn't being used 
    Slow Start is barely being used 
    Natural Cure is barely being used 
    Shed Skin is barely being used 
    Overcoat is barely being used 

*/
#pragma endregion 


#pragma region definitions

extern "C" u8 SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u16 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)  return 1;
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

const u16 nonStatusProtectMoves[4] = {
    MOVE376_SPIKY_SHIELD,
    MOVE462_SILK_TRAP,
    MOVE559_BANEFUL_BUNKER,
    MOVE262_OBSTRUCT};

#pragma endregion

extern "C"
{

#pragma region helpers



    uint8_t getOverheatByte(BattleMon *a1)
    {
        return *((uint8_t *)a1 + 0xEA);
    }
    void setOverheatByte(BattleMon *a1, int a2)
    {
        *((uint8_t *)a1 + 0xEA) = a2;
    }
    uint8_t getOverheatLastTurnByte(BattleMon *a1)
    {
        return *((uint8_t *)a1 + 0xEB);
    }
    void setOverheatLastTurnByte(BattleMon *a1, int a2)
    {
        *((uint8_t *)a1 + 0xEB) = a2;
    }

#pragma endregion

#pragma region OverWrites 

    /* INTIMIDATE */
extern "C" void THUMB_BRANCH_HandlerIntimidate(int a1, ServerFlow *a2, int a3)
{
    u8 *TempWork;                     // r4
    u8 NumTargets;                    // r5
    HandlerParam_ChangeStatStage *v7; // r1
    __int16 ExistFrontPokePos;        // [sp+0h] [bp-18h]

    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
        TempWork = Handler_GetTempWork(a2);
        NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, TempWork);
        if (NumTargets)
        {
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);

            v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
            // v7->header.flags |= 0x08000000;
            v7->rankType = STATSTAGE_ATTACK;
            v7->rankVolume = -1;
            v7->fMoveAnimation = 1;
            v7->poke_cnt = NumTargets;
            for (u8 frontCurrent = 0; frontCurrent < NumTargets; ++frontCurrent)
            {
                v7->pokeID[frontCurrent] = TempWork[frontCurrent];
            }
            v7->pad = STAT_CHANGE_INTIMIDATE_FLAG;
            BattleHandler_PopWork(a2, v7);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
        }
    }
}

extern "C" void THUMB_BRANCH_HandlerAnalytic(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (HandlerCommon_IsMonLastInTurnOrder(a2, a3))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);
        }
    }
}

void THUMB_BRANCH_HandlerSolidRock(int a1, int a2, int a3)
{
    u8 Value; // r0
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        Value = BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS);
        BattleEventVar_MulValue(VAR_RATIO, ((Value == EFFECTIVENESS_2) ? 3072 : ((Value == EFFECTIVENESS_4) ? 2304 : 4096)));
    }
}



    /* Heatproof */
    //u8 FULL_COPY_HandlerHeatproofPower_0x6 = 2u;
    u16 FULL_COPY_HandlerHeatproofPower_0x6 = 0x2402;
    /* Regenerator */
    u16 FULL_COPY_HandlerRegenerator_0x2E = 8452;
    /* Weak Armor */
    //u8 FULL_COPY_HandlerWeakArmor_0x9E = 0x0F;
    u16 FULL_COPY_HandlerWeakArmor_0x9E = 0x730F;
    /* Iron Fist*/
    u16 FULL_COPY_HandlerIronFist_0x2C = 0x14CD; // 5325

    ABILITY_TRIGGERTABLE DefeatistHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 6
    };

    // MAJESTIC WARD 
    ABILITY_TRIGGERTABLE * THUMB_BRANCH_EventAddDefeatist(_DWORD * a1) {
        *a1 = 0;
        return DefeatistHandlers;
    }

    void THUMB_BRANCH_HandlerMultiscale(int a1, int a2, int a3)
    {
        return;
    }

    
    void THUMB_BRANCH_CommonStatDropGuardCheck(int a1, int a2, int *a3, int a4)
    {
        if (a2 == BattleEventVar_GetValue(VAR_MON_ID) && (a2 != BattleEventVar_GetValue(VAR_ATTACKING_MON) || BattleEventVar_GetValue(VAR_HOSTILEFLAG) == 1) && (a4 == 8 || a4 == BattleEventVar_GetValue(VAR_MOVE_EFFECT)) && BattleEventVar_GetValue(VAR_VOLUME) < 0)
        {
            *a3 = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        }
    };

    int THUMB_BRANCH_SAFESTACK_ServerEvent_CheckNoEffect(
        ServerFlow *a1,
        MoveParam *a2,
        BattleEventType a3,
        BattleMon *a4,
        BattleMon *a5,
        int a6,
        _WORD *a7,
        int *a8)
    {
        u8 ID;        // r0
        u8 v12;       // r0
        u8 v13;       // r0
        u8 Value;     // r5
        int IfEnabled; // [sp+4h] [bp-1Ch]

        ID = BattleMon_GetID(a5);
        IfEnabled = sub_21B0874((EffectivenessRecorder *)a6, ID);
        BattleHandler_StrClear(a7);
        BattleEventVar_Push();
        v12 = BattleMon_GetID(a4);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v12);
        v13 = BattleMon_GetID(a5);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v13);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a2->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a2->moveType);
        BattleEventVar_SetConstValue(VAR_MAGIC_COAT_FLAG, a2->flags & 1);
        BattleEventVar_SetConstValue(VAR_WORK_ADDRESS, (int)a7);
        BattleEventVar_SetConstValue(VAR_TYPE_EFFECTIVENESS, IfEnabled);
        BattleEventVar_SetRewriteOnceValue(VAR_NO_EFFECT_FLAG, 0);
        BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);
        BattleEvent_CallHandlers(a1, a3);
        Value = BattleEventVar_GetValue(VAR_NO_EFFECT_FLAG);
        *a8 = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);
        BattleEventVar_Pop();

        int moveId = a2->MoveID;
        if ((moveId == 78 || moveId == 79 || moveId == 147 || moveId == 476 || moveId == 77 || moveId == 139) && BattleMon_HasType(a5, TYPE_GRASS))
        {
            Value = 1;
        }
        return Value;
    }


    void THUMB_BRANCH_CommonContactStatusAbility(
        ServerFlow *a1,
        unsigned int *a2,
        MoveCondition a3,
        ConditionData a4,
        unsigned __int8 a5)
    {
        unsigned __int16 Value; // r0
        BattleMon *attackingMon;
        HandlerParam_AddCondition *v9; // r5
        u8 monInQuestion = (((int)a2 == BattleEventVar_GetValue(VAR_DEFENDING_MON)) ? BattleEventVar_GetValue(VAR_ATTACKING_MON) : ((int)a2 == BattleEventVar_GetValue(VAR_ATTACKING_MON)) ? BattleEventVar_GetValue(VAR_DEFENDING_MON) : 255);
        if (monInQuestion != 255 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT) && !AbilityEvent_RollEffectChance((int)a1, a5))
            {
                v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, (int)a2);
                v9->header.flags |= 0x800000u;
                v9->sickID = a3;
                v9->sickCont = a4;
                v9->fAlmost = 0;
                v9->pokeID = monInQuestion;
                BattleHandler_PopWork(a1, v9);
            }
        }
    }


    void THUMB_BRANCH_CommonLowHPBoostAbility(ServerFlow *a1, int a2, int a3)
    {
        BattleMon *BattleMon; // r6
        if (a2 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon = Handler_GetBattleMon(a1, a2);
            if (a3 == BattleEventVar_GetValue(VAR_MOVE_TYPE))
            {
                BattleEventVar_MulValue(VAR_RATIO, ((BattleMon_GetValue(BattleMon, VALUE_CURRENT_HP) <= DivideMaxHp(BattleMon, 3u)) ? 6144 : 5120));
            }
        }
    }

    int THUMB_BRANCH_IsMonTrapped(BtlClientWk *a1, BattleMon *a2, _BYTE *a3, _WORD *a4)
    {
        int ID;               // r0
        __int16 v7;           // r0
        unsigned int v8;      // r7
        int Value;            // r4
        BattleMon *BattleMon; // [sp+8h] [bp-20h]
        unsigned int Count;   // [sp+Ch] [bp-1Ch]
        u8 ids[24];         // [sp+10h] [bp-18h] BYREF

        ID = BattleMon_GetID(a2);
        v7 = MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, ID);
        Count = MainModule_ExpandExistPokeID(a1->mainModule, a1->pokeCon, v7 | 0x100, ids);
        v8 = 0;
        if (BattleMon_HasType(a2, TYPE_GHOST))
        {
            return 4;
        }
        if (Count)
        {
            while (1)
            {
                BattleMon = PokeCon_GetBattleMon(a1->pokeCon, ids[v8]);
                Value = BattleMon_GetValue(BattleMon, VALUE_EFFECTIVE_ABILITY);
                BattleMon_GetID(BattleMon); // what's going on here

                if (Value == ABIL023_SHADOW_TAG && DoesMonHaveShadowTag((int)a1, a2) && !BattleMon_HasType(a2, TYPE_GHOST))
                {
                    break;
                }
                if (Value == ABIL123_BAD_DREAMS && BattleMon_CheckIfMoveCondition(a2, CONDITION_SLEEP))
                {
                    break;
                }
                if (Value == ABIL071_ARENA_TRAP && IsMonTrappedByArenaTrap(a1, a2) || Value == ABIL042_MAGNET_PULL && IsMonSteelType((int)a1, (int)a2))
                {
                    break;
                }
                v8 = (v8 + 1);
                if (v8 >= Count)
                {
                    goto LABEL_11;
                }
            }
            *a3 = BattleMon_GetID(BattleMon);
            *a4 = Value;
            return 0;
        }
        else
        {
        LABEL_11:
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_BLOCK) || BattleMon_CheckIfMoveCondition(a2, CONDITION_BIND))
            {
                *a3 = BattleMon_GetID(a2);
                *a4 = 0;
                return 3;
            }
            else
            {
                return 4;
            }
        }
    }

#pragma endregion 
    
#pragma region CouldbeOverwritten

    // could just be overwritten with a "LINK maybe?" 
    extern "C" void THUMB_BRANCH_ServerControl_MoveUseNotEffective(ServerFlow *a1, int a2, int a3)
    {
        int v6; // r7
        BattleMon *mon;
        mon = Handler_GetBattleMon(a1, a2);
        TurnFlag_Set(mon, TURNFLAG_MOVEFAILED);
        v6 = HEManager_PushState((int *)&a1->heManager);
        ServerEvent_MoveUseEnd_Common(a1, a2, a3, EVENT_MOVE_EXECUTE_NOEFFECT);
        HEManager_PopState((int *)&a1->heManager, v6);
    }

    // could just be overwritten with a "LINK maybe?"
    extern "C" void THUMB_BRANCH_ServerEvent_CheckMoveExecuteFail(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        int ID; // r0
        TurnFlag_Set(a2, TURNFLAG_MOVEFAILED);

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a3);
        BattleEventVar_SetConstValue(VAR_FAIL_CAUSE, a4);
        BattleEvent_CallHandlers(a1, EVENT_MOVE_EXECUTE_FAIL);
        BattleEventVar_Pop();
    }

    // could just be overwritten with a "LINK maybe?"
    extern "C" b32 THUMB_BRANCH_SAFESTACK_ServerEvent_CheckStatStageChangeSuccess(ServerFlow *serverFlow, BattleMon *affectedMon, StatStage statStage, u32 attackingSlot, int volume, u32 moveSerial)
    {
        BattleEventVar_Push();
        u32 affectedSlot = BattleMon_GetID(affectedMon);
        BattleEventVar_SetConstValue(VAR_MON_ID, affectedSlot);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, attackingSlot);
        BattleEventVar_SetConstValue(VAR_MOVE_EFFECT, statStage);
        BattleEventVar_SetConstValue(VAR_VOLUME, volume);
        BattleEventVar_SetValue(VAR_INTIMFLAG, (moveSerial & STAT_CHANGE_INTIMIDATE_FLAG) != 0); // Intimidate Flag
        BattleEventVar_SetValue(VAR_HOSTILEFLAG, (moveSerial & STAT_CHANGE_HOSTILE_FLAG) != 0);  // Mirror Armor Flag
        // BattleEventVar_SetValue(VAR_OPPORTUNIST_FLAG, (moveSerial & STAT_CHANGE_OPPORTUNIST_FLAG) != 0);   // Opportunist Flag
        BattleEventVar_SetValue(VAR_DELAY_ATTACK_FLAG, (moveSerial & STAT_CHANGE_PARTING_SHOT_FLAG) != 0); // Parting Shot Flag
        BattleEventVar_SetConstValue(VAR_STAT_STAGE_CHANGE_COUNT, moveSerial & 0x0FFFFFFF);
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEvent_CallHandlers(serverFlow, EVENT_STAT_STAGE_CHANGE_LAST_CHECK);
        u32 failFlag = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
        BattleEventVar_Pop();

        if (!failFlag)
        {
            return 1;
        }
        return 0;
    }
    
    // could just be overwritten with a "LINK maybe?"
    extern "C" void THUMB_BRANCH_ServerEvent_StatStageChangeFail(ServerFlow *serverFlow, BattleMon *currentMon, u32 moveSerial)
    {
        BattleEventVar_Push();
        u32 currentSlot = BattleMon_GetID(currentMon);
        BattleEventVar_SetConstValue(VAR_MON_ID, currentSlot);
        BattleEventVar_SetConstValue(VAR_INTIMFLAG, (moveSerial & STAT_CHANGE_INTIMIDATE_FLAG) != 0); // Intimidate Flag
        BattleEventVar_SetConstValue(VAR_HOSTILEFLAG, (moveSerial & STAT_CHANGE_HOSTILE_FLAG) != 0);  // Mirror Armor Flag
        // BattleEventVar_SetConstValue(VAR_OPPORTUNIST_FLAG, (moveSerial & STAT_CHANGE_OPPORTUNIST_FLAG) != 0);   // Opportunist Flag
        BattleEventVar_SetConstValue(VAR_DELAY_ATTACK_FLAG, (moveSerial & STAT_CHANGE_PARTING_SHOT_FLAG) != 0); // Parting Shot Flag
        BattleEventVar_SetConstValue(VAR_STAT_STAGE_CHANGE_COUNT, moveSerial & 0x0FFFFFFF);
        BattleEvent_CallHandlers(serverFlow, EVENT_STAT_STAGE_CHANGE_FAIL);
        BattleEventVar_Pop();
    }

#pragma endregion

#pragma region MoveFailureConditions

    int THUMB_BRANCH_SAFESTACK_ServerControl_MoveExecuteCheck1(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        MoveFailCause v7;                      // r6
        ActionIgnoreReason actionIgnoreReason; // r0
        int v9;                                // r1
        ConditionData MoveConditionData;       // r0
        u16 PreviousMove;                      // r0                          // r0
        int v15;                               // [sp+Ch] [bp-24h]
        MoveCondition Status;                  // [sp+10h] [bp-20h]
        u8 abil;
        v15 = 0;
        ServerControl_CheckMoveExeSleepCure(a1, a2);
        Status = BattleMon_GetStatus(a2);
        abil = BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY);
        PreviousMove = BattleMon_GetPreviousMoveID(a2);
        if (Status != CONDITION_SLEEP || (v7 = MOVEFAIL_SLEEP, ServerEvent_MoveExecuteFail(a1, a2, a3, 2)))
        {
            v15 = ServerControl_CheckMoveExeFreezeThaw(a1, a2, a3);
            Status = BattleMon_GetStatus(a2);
            if (Status == CONDITION_FREEZE && !v15)
            {
                v7 = MOVEFAIL_FREEZE;
                goto LABEL_50;
            }
            actionIgnoreReason = a1->actionIgnoreReason;
            if (actionIgnoreReason == REASON_OVERLEVELED)
            {
                v7 = MOVEFAIL_IGNORE;
                goto LABEL_50;
            }
            if (actionIgnoreReason == REASON_FALL_ASLEEP)
            {
                v7 = MOVEFAIL_IGNORE_FALL_ASLEEP;
                goto LABEL_50;
            }
            if (!a4)
            {
                v9 = Move_SearchIndex(a2, a3);
                if (v9 != 4 && !Move_GetPP(a2, v9))
                {
                    v7 = MOVEFAIL_PPZERO;
                    goto LABEL_50;
                }
            }
            v7 = (MoveFailCause)ServerEvent_CheckMoveExecute(a1, a2, a3, EVENT_MOVE_EXECUTE_CHECK1);
            if (v7 == MOVEFAIL_NULL)
            {
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FLINCH))
                {
                    v7 = MOVEFAIL_FLINCH;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_DISABLEMOVE) && a3 != 165)
                {
                    MoveConditionData = BattleMon_GetMoveCondition(a2, CONDITION_DISABLEMOVE);
                    if (a3 == Condition_GetParam(MoveConditionData))
                    {
                        v7 = MOVEFAIL_DISABLE;
                        goto LABEL_50;
                    }
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_HEALBLOCK) && getMoveFlag(a3, FLAG_HEALING))
                {
                    v7 = MOVEFAIL_HEALBLOCK;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_GRAVITY) && getMoveFlag(a3, FLAG_GROUNDED_BY_GRAVITY))
                {
                    v7 = MOVEFAIL_GRAVITY;
                    goto LABEL_50;
                }
                if (a3 == 165)
                {
                    goto LABEL_60;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_ENCORE) && PreviousMove != 165 && PreviousMove != a3)
                {
                    v7 = MOVEFAIL_MOVELOCK;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_MOVELOCK) && a3 != PreviousMove){
                    v7 = MOVEFAIL_MOVELOCK;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_TAUNT) && !PML_MoveIsDamaging(a3))
                {
                    v7 = MOVEFAIL_TAUNT;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_IMPRISON) && BattleField_CheckImprison(a1->pokeCon, a2, a3))
                {
                    v7 = MOVEFAIL_IMPRISON;
                }
                else
                {
                LABEL_60:
                    if (ServerControl_CheckConfusionHit(a1, a2))
                    {
                        v7 = MOVEFAIL_CONFUSION;
                    }
                    else if (Status == CONDITION_PARALYSIS)
                    {
                        if (abil == ABIL062_GUTS || abil == ABIL063_MARVEL_SCALE || abil == ABIL039_INNER_FOCUS)
                        {
                        }
                        else if (abil == ABIL095_QUICK_FEET && RollEffectChance(0x4u))
                        {
                            v7 = MOVEFAIL_PARALYSIS;
                        }
                        else
                        {
                            if (RollEffectChance(0x19u)) v7 = MOVEFAIL_PARALYSIS;
                        }
                    }
                    else if (ServerControl_CheckAttract(a1, a2))
                    {
                        v7 = MOVEFAIL_ATTRACT;
                    }
                }
            }
        }
    LABEL_50:
        if (v7)
        {
            ServerControl_MoveExecuteFail(a1, a2, a3, v7);
            return 1;
        }
        else
        {
            if (Status == CONDITION_SLEEP)
            {
                ServerDisplay_MoveExecuteFailMessage(a1, (int)a2, a3, 2u);
                ServerDisplay_AddEffectAtPosition(a1, a2, 598);
            }
            else if (v15)
            {
                if (Status == CONDITION_FREEZE)
                {
                    ServerDisplay_CureStatus(a1, a2, 3, 0);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 303, BattleMon_GetID(a2), a3, -65536);
                }
            }
            return 0;
        }
    }

    // #if TESTING_UNHOOKED_FUNCTIONS
    // void THUMB_BRANCH_flowsub_CheckNoEffect_TypeAffinity(
    // #else 
    // void THUMB_BRANCH_ServerFlow_CheckNoEffect_TypeEffectiveness(
    // #endif
    //     ServerFlow *a1,
    //     MoveParam *a2,
    //     BattleMon *attacker,
    //     PokeSet *targets,
    //     EffectivenessRecorder *effrec)
    // {
    //     BattleMon *i;     // r5
    //     int v8;           // r7
    //     unsigned int v11; // r5
    //     EffectivenessRecorder_Init(effrec);
    //     j_j_PokeSet_SeekStart_7(targets);
    //     for (i = j_PokeSet_SeekNext_29(targets); i; i = j_PokeSet_SeekNext_28(targets))
    //     {
    //         v8 = ServerEvent_CheckMoveDamageEffectiveness(a1, attacker, i, a2, 1);
    //         EffectivenessRecorder_Add(effrec, BattleMon_GetID(i), v8);
    //         if (!v8)
    //         {
    //             // TurnFlag Added Here
    //             if (!MainModule_IsAllyMonID(i->ID, attacker->ID))  TurnFlag_Set(attacker, TURNFLAG_MOVEFAILED);
    //             j_PokeSet_Remove_8(targets, i);
    //             EffectivenessCounter_CountUp(&a1->effectivenessCounter, a1, attacker, i, 0);
    //             v11 = j_MainModule_PokeIDToClientID(BattleMon_GetID(attacker));
    //             if (v11 == MainModule_GetPlayerClientID(a1->mainModule))
    //             {
    //                 RecordData_Increment(a1->mainModule, 75);
    //             }
    //         }
    //     }
    // }
 
    // // FIGURE OUT WHAT THE FUCK IS GOING ON HERE 
    // #if TESTING_UNHOOKED_FUNCTIONS
    // void THUMB_BRANCH_flowsub_CheckWazaAvoid(
    // #else 
    // void THUMB_BRANCH_ServerFlow_CheckNoEffect_Avoid(
    // #endif
    //     ServerFlow *a1, 
    //     unsigned __int16 *a2, 
    //     BattleMon *a3, 
    //     PokeSet *a4)
    // {
    //     BattleMon *i; // r4
    //     if (j_PokeSet_GetCountMax_4(a4) != 1 || j_PokeSet_Get_8(a4, 0) != a3)
    //     {
    //         j_PokeSet_SeekStart_20(a4);
    //         for (i = j_PokeSet_SeekNext_41(a4); i; i = j_PokeSet_SeekNext_40(a4))
    //         {
    //             if (!ServerEvent_SkipAvoidCheck(a1, a3, i, a2) && !ServerEvent_CheckHit(a1, a3, i, a2))
    //             {
    //                 if (!MainModule_IsAllyMonID(i->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
    //                 j_PokeSet_Remove_10(a4, i);
    //                 ServerDisplay_MoveAvoid(a1, i);
    //             }
    //         }
    //     }
    // };

    // #if TESTING_UNHOOKED_FUNCTIONS
    // void THUMB_BRANCH_flowsub_CheckPokeHideAvoid(
    // #else 
    // void THUMB_BRANCH_ServerFlow_CheckNoEffect_Hiding(
    // #endif 
    //     ServerFlow *a1, 
    //     unsigned __int16 *a2, 
    //     BattleMon *a3, 
    //     PokeSet *a4)
    // {
    //     BattleMon *i; // r4
    //     j_j_PokeSet_SeekStart_19(a4);
    //     for (i = j_j_PokeSet_SeekNext_38(a4); i; i = j_j_PokeSet_SeekNext_39(a4))
    //     {
    //         if (!ServerControl_IsGuaranteedHit(a1, a3, i))
    //         {
    //             if (ServerEvent_CheckHiding(a1, a3, i))
    //             {
    //                 if (!MainModule_IsAllyMonID(i->ID, a3->ID))  TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
    //                 j_j_PokeSet_Remove_9(a4, i);
    //                 ServerDisplay_MoveAvoid(a1, i);
    //             }
    //         }
    //     }
    // };

    void THUMB_BRANCH_SAFESTACK_flowsub_CheckNoEffect_Protect(ServerFlow *a1, unsigned __int16 *a2, BattleMon *a3, PokeSet *a4, int a5)
    {
        BattleMon *i; // r7
        BattleMon *j; // r7
        BattleMon *k; // r7
        BattleMon *m; // r7
        // int ID;       // r0
        j_PokeSet_SeekStart_10(a4);

        for (i = j_PokeSet_SeekNext_18(a4); i; i = j_PokeSet_SeekNext_19(a4))
        {
            if (!ServerControl_IsGuaranteedHit(a1, a3, i) && ServerControl_CheckNoEffectCore(a1, a2, (int)a3, i, a5, 43))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(i->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_0(a4, i);
            }
        }
        j_PokeSet_SeekStart_11(a4);
        for (j = j_PokeSet_SeekNext_20(a4); j; j = j_PokeSet_SeekNext_21(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, j, a5, 44))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(j->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_1(a4, j);
            }
        }

        if (getMoveFlag(*a2, FLAG_BLOCKED_BY_PROTECT))
        {
            j_PokeSet_SeekStart_12(a4);
            for (k = j_PokeSet_SeekNext_22(a4); k; k = j_PokeSet_SeekNext_23(a4))
            {
                if (BattleMon_GetTurnFlag(k, TURNFLAG_PROTECT) && !ServerEvent_CheckProtectBreak(a1, a3))
                {
                    if (!(SEARCH_ARRAY(nonStatusProtectMoves, BattleMon_GetPreviousMoveID(k)) && PML_MoveGetCategory(*a2) == 0))
                    {
                        // Add TurnFlag modification for the Attacking Pokemon here
                        if (!MainModule_IsAllyMonID(k->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                        j_PokeSet_Remove_2(a4, k);
                        //ID = BattleMon_GetID(k);
                        ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 523,  BattleMon_GetID(k), -65536);
                        if (BattleMon_GetPreviousMoveID(k) == MOVE376_SPIKY_SHIELD && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ) {
                            HandlerParam_Damage *v7 = (HandlerParam_Damage *)BattleHandler_PushWork(a1, EFFECT_DAMAGE, a3->ID);
                            v7->pokeID = a3->ID;
                            v7->damage = DivideMaxHPZeroCheck(a3, 8u);
                            BattleHandler_StrSetup(&v7->exStr, 2u, 1189);
                            BattleHandler_AddArg(&v7->exStr, v7->pokeID);
                            BattleHandler_PopWork(a1, v7);}

                        if (BattleMon_GetPreviousMoveID(k) == MOVE462_SILK_TRAP && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ) {
                            HandlerParam_ChangeStatStage *v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a1, EFFECT_CHANGESTATSTAGE, a3->ID);
                            v8->pokeID[0] = a3->ID;
                            v8->poke_cnt = 1;
                            v8->fMoveAnimation = 1;
                            v8->rankType = STATSTAGE_SPEED;
                            v8->rankVolume = -2;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1264);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID[0]);
                            BattleHandler_PopWork(a1, v8);}
                        
                        if (BattleMon_GetPreviousMoveID(k) == MOVE262_OBSTRUCT && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ){
                            HandlerParam_ChangeStatStage *v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a1, EFFECT_CHANGESTATSTAGE, a3->ID);
                            v8->pokeID[0] = a3->ID;
                            v8->poke_cnt = 1;
                            v8->fMoveAnimation = 1;
                            v8->rankType = STATSTAGE_DEFENSE;
                            v8->rankVolume = -2;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1339);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID[0]);
                            BattleHandler_PopWork(a1, v8);}
                        
                        if (BattleMon_GetPreviousMoveID(k) == MOVE559_BANEFUL_BUNKER && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ){
                            HandlerParam_AddCondition *v8 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, a3->ID);
                            v8->pokeID = a3->ID;
                            v8->sickID = CONDITION_POISON;
                            v8->sickCont = MakeBasicStatus(CONDITION_POISON);
                            v8->fAlmost = 0;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1336);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID);
                            BattleHandler_PopWork(a1, v8);}
                    }
                }
            }
        }
        j_PokeSet_SeekStart_13(a4);
        for (m = j_PokeSet_SeekNext_24(a4); m; m = j_PokeSet_SeekNext_25(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, m, a5, 45))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(m->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_3(a4, m);
            }
        }
    }

    void THUMB_BRANCH_BattleMon_TurnCheck(BattleMon *a1)
    {
        u8 didMoveFail = BattleMon_GetTurnFlag(a1, TURNFLAG_MOVEFAILED);
        sys_memset(a1->TurnFlag, 0, 2u);
        if (a1->TurnCount < 9999u) ++a1->TurnCount;
        if (didMoveFail) TurnFlag_Set(a1, TURNFLAG_MOVEFAILEDLASTTURN);
        setOverheatLastTurnByte(a1, (getOverheatByte(a1)) ? 1 : 0);
        setOverheatByte(a1, 0);
        MoveDamageRec_ClearTurn(a1);
    }



#pragma endregion
}

#pragma region UIDefinitions
    struct MsgFileEntry
    {
        int Offset;
        u16 CharCount;
        u16 Padding;
    };
    struct SWAN_ALIGNED(4) MsgData
    {
        void *FileHandle;
        int RawData;
        MsgFileEntry CurrentEntry;
        int MsgOfsInArc;
        ArcTool *MsgArc;
        __int16 HeapID;
        u8 LanguageId;
        u8 IsAllPreload;
    };
    struct PokestarChoiceData
    {
        void *font;
        HeapID heapID;
        u8 end_flag;
        u8 pad;
        int msgID;
        void *buf[4];
        int *result;
        int comm_error_flag;
    };
    struct SWAN_PACKED SWAN_ALIGNED(1) BattlePokeListData
    {
        void *gameData;
        PokeParty *pokeParty;
        PokeParty *AllyPokeParty;
        void *Font;
        HeapID heapID;
        __int16 field_12;
        BattleStyle battleStyle;
        int IsBagDisabled;
        char AllyClientID;
        u8 SelectedPokeIndex[2];
        char ListMode;
        u8 SelectedMon;
        char InfoPokeIndex;
        char NumPartyMembers;
        char field_23;
        __int16 SelectedItem;
        __int16 IsSelectedMonTrapped;
        void *tcbmanager;
        void *palAnm;
        int IsFinished;
        int CommErrorFlag;
        char skill_item_use;
        char field_39;
        char field_3A;
        char field_3B;
        int field_3C;
        int SoundEffectFlag;
        int cursorFlag;
        u8 field_48[3];
        char MoveInfoMoveIndex;
        char EndFlag;
    };
    struct BattleScenarioData
    {
        void *font;
        HeapID heapID;
        u8 end_flag;
        u8 pad;
        void *party;
        int scenario_num;
        int page_num;
        int time_out_flag;
        int comm_error_flag;
    };
    struct PokeList_MoveData
    {
        __int16 MoveID;
        char CurrentPP;
        char MaxPP;
        char Type;
        char Category;
        char Accuracy;
        char Power;
    };
    struct PokeList_BmpWinData
    {
        void *BmpWin;
        char field_4;
        char field_5;
        char field_6;
        char field_7;
    };
    struct PokeListData
    {
        PartyPkm *partyPkm;
        __int16 Species;
        __int16 Attack;
        __int16 Defense;
        __int16 Speed;
        __int16 SpecialAttack;
        __int16 SpecialDefense;
        __int16 CurrentHP;
        __int16 MaxHP;
        char Type1;
        char Type2;
        char Level;
        char SexStatusIsEgg;
        __int16 Ability;
        __int16 Item;
        int Experience;
        int ExpForLevel;
        int ExpToNextLevel;
        int Forme;
        PokeList_MoveData MoveData[4];
    };
    struct ClAct_0x7C
    {
        int field_0;
        int field_4;
        int field_8;
        int field_C;
        _BYTE gap10[84];
        int field_64;
        int field_68;
        int field_6C;
        int field_70;
        int field_74;
        int field_78;
    };
    struct SWAN_ALIGNED(4) ClActObj
    {
        ClActObj *next;
        ClActObj *prev;
        void *unit;
        u16 posX;
        u16 posY;
        __int16 field_10;
        __int16 field_12;
        int scaleX;
        int scaleY;
        int field_1C;
        int field_20;
        int field_24;
        int field_28;
        _BYTE gap2C[20];
        int field_40;
        _BYTE gap44[16];
        int field_54;
        __int16 rotation;
        __int16 animID;
        __int16 field_5C;
        __int16 field_5E;
        int Flags;
        int field_64;
        ClAct_0x7C field_68;
    };
    struct PokeListMain
    {
        BattlePokeListData *pokeListSetupData;
        PokeListData pokeListData[6];
        u8 field_1CC[6];
        void *TCBManagerEx;
        void *PalAnm;
        _BYTE gap1DC[7324];
        int field_1E78;
        _BYTE gap1E7C[28];
        char field_1E98;
        char field_1E99;
        char field_1E9A;
        char field_1E9B;
        void *GFLFont;
        MsgData *msgData;
        void *WordSetSystem;
        void *StrBuf;
        void *PrintSys;
        int field_1EB0;
        int field_1EB4;
        int field_1EB8;
        ClActObj *field_1EBC[40];
        int field_1F5C;
        PokeList_BmpWinData field_1F60[2];
        PokeList_BmpWinData field_1F70[64];
        void *field_2170;
        char field_2174;
        char field_2175;
        char field_2176;
        char field_2177;
        int field_2178;
        int field_217C;
        char field_2180;
        int field_2184;
        int field_2188;
        int field_218C;
        char field_2190;
        char field_2191;
        _BYTE gap2192;
        char field_2193;
        int field_2194;
        _BYTE gap2198[768];
        char field_2498;
        char field_2499;
        char field_249A;
        char field_249B;
        __int16 field_249C;
        __int16 field_249E;
        _BYTE gap24A0[156];
        int field_253C;
        int field_2540;
    };
    enum InputButton
    {
        KEY_A = 0x1,
        KEY_B = 0x2,
        KEY_SELECT = 0x4,
        KEY_START = 0x8,
        KEY_RIGHT = 0x10,
        KEY_LEFT = 0x20,
        KEY_UP = 0x40,
        KEY_DOWN = 0x80,
        KEY_R = 0x100,
        KEY_L = 0x200,
        KEY_X = 0x400,
        KEY_Y = 0x800,
        KEY_TOUCH = 0x1000,
        KEY_LID = 0x2000,
    };
    extern "C" u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);
    extern "C" int sub_21F9E78(PokeListMain *a1, int a2);
    extern "C" void sub_21F4A30(PokeListMain *a1, unsigned int a2, char a3, int a4);
    extern "C" int PokeList_GetSelectedMonID(PokeListMain *a1, int a2);
    extern "C" int sub_21F4F14(PokeListMain *a1);
    extern "C" void sub_21F4F50(int a1);
    extern "C" void PokeList_LoadPokeData(PokeListMain *a1, PartyPkm *a2, PokeListData *a3);
    extern "C" PartyPkm *PokeParty_GetPkm(void *party, int slot);
    extern "C" u32 PokeParty_GetPkmCount(void *pPartyBlk);
    extern "C" u32 PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra);
    extern "C" u32 getExpForPkm_Wrapper(void *pPkm);
    extern "C" u32 PokeParty_GetSex(PartyPkm *pPkm);
    extern "C" int PML_MoveGetMaxPP(int wazaId, unsigned int ppUpStage);
    extern "C" bool PML_MoveIsAlwaysHit(int wazaId);
    extern "C" int sub_202D8EC(PartyPkm *a1);
    extern "C" int BattleClient_GetMyID(void *a1);
    extern "C" PokeParty *MainModule_GetPokeParty(void *a1, int a2);
    extern "C" int MainModule_IsCompetitiveBattleType(void *a1);
    extern "C" PokeParty *MainModule_GetAllyPokeParty(void *a1, char a2);
    extern "C" int sub_219C86C(void *a1, char a2);
    extern "C" int MainModule_CheckNumFrontPos(void *a1, char a2);
    extern "C" char *sub_689B7C8(void *a1);
    extern "C" void *BtlvEffectMain_GetTCBManager();
    extern "C" void *BtlvEffectMain_GetPalAnm();
    extern "C" void *MainModule_GetGameData(void *a1);
    extern "C" int sub_21CF250(BtlvCore *a1);
    extern "C" InputButton GCTX_HIDGetHeldKeys();
    extern "C" int MainModule_IsPartnerBattle(MainModule *a1);
    extern "C" u32 PML_PersonalGetParamSingle(u16 species, u16 form, PersonalField field);
    extern "C" int sub_21FA27C(PokeListMain *a1, unsigned int a2);
    extern "C" int PokeList_IsAlreadyInBattle(PokeListMain *a1, int a2);
    extern "C" int PokeList_IsEgg(PokeListMain *a1);
    extern "C" int PokeList_IsAlreadySelectedForSwitchIn(PokeListMain *a1, int a2);
    extern "C" int PokeList_DetermineSwitchInFailCause(PokeListMain *a1);
    extern "C" StrBuf *GFL_MsgDataLoadStrbufNew(MsgData *msgData, int msgId);
    extern "C" void GFL_WordSetFormatStrbuf(void *wordSet, StrBuf *dest, StrBuf *source);
    extern "C" void loadPokemonNicknameToStrbuf(void *a1, int a2, PartyPkm *a3);
    extern "C" void GFL_StrBufFree(StrBuf *pStrbuf);
    extern "C" u32 GetScanSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16438);
        return (*lvl_cap_ptr) ? 1 : 0;
    }
    #if TRYING_BATTLESCAN_EXPANSION
    #define FIELD_D8_ABILITY   0u
    #define FIELD_D8_POKETYPES    16u
    #define FIELD_D8_ABILITY_MASK    (0xFFFFu << FIELD_D8_ABILITY)   // 0x0000FFFF
    #define FIELD_D8_POKETYPES_MASK     (0xFFu   << FIELD_D8_POKETYPES)    // 0x00FF0000
    #define FIELD_D8_GASTRO_MASK   (1u << 24u)  // 0x01000000
    #define FIELD_D8_APPEARED_MASK  (1u << 25u)
    #define FIELD_D8_WILD_MASK  (1u << 26u)
    #define FIELD_D8_ILLUSION_MASK (1u << 27u)

    extern "C" u32 setBit(u32 value, u32 mask, u8 flag){
        value &= ~mask;
        if (flag) value |= mask;
        return value;
    }

    extern "C" u8 getBit(u32 value, u32 mask) {
        return (value & mask) != 0;
    }

    extern "C" u32 setU16(u32 value, u16 abil){
        value &= ~FIELD_D8_ABILITY_MASK;
        value |= ((u32)abil << FIELD_D8_ABILITY);
        return value;
    }
    extern "C" u16 getU16(u32 value){
        return (u16)((value & FIELD_D8_ABILITY_MASK) >> FIELD_D8_ABILITY);
    }

    extern "C" u32 setU8(u32 value, u8 types) {
        value &= ~FIELD_D8_POKETYPES_MASK;
        value |= ((u32)types << FIELD_D8_POKETYPES);
        return value;
    }
    extern "C" u8 getU8(u32 value) {
        return (u8)((value & FIELD_D8_POKETYPES_MASK) >> FIELD_D8_POKETYPES);
    }

    #endif 
    extern "C" u8 isWild(u32 value){
        #if TESTING_BATTLESCAN_EXPANSION
        return getBit(value, FIELD_D8_WILD_MASK);
        #else 
        return (value == 2);
        #endif 
    }
#pragma endregion 

#pragma region UIFunctions

extern "C" void findBattleMon(BtlvCore *a1, PokeParty *a2, int clientId)
{
    BattleParty party = a1->pokeCon->party[clientId];
   
    /* WILD BATTLES */
    if (a1->mainModule->btlSetup->btlType == 0)
    {
        for (int j = 0; j < party.memberCount; j++)
        {
            if (party.mons[j]->partySrc->Base.pid == a2->Pokemon[j].Base.pid)
            {
                a2->Pokemon[j].field_D8 = 2;
            }
        }
        return;
    };

    for (int i = 0; i < party.memberCount; i++)
    {
        if (party.mons[i]->partySrc->Base.pid == a2->Pokemon[i].Base.pid)
        {
            if (party.mons[i]->AppearedTurn == 10000)
            {
                a2->Pokemon[i].field_D8 = 1;
            }
            else
            {
                a2->Pokemon[i].field_D8 = 0;
            }
            if (party.mons[i]->Ability == ABIL149_ILLUSION)
            {
                for (int j = 0; j < party.memberCount; j++)
                {
                    if (party.mons[j]->partySrc->Base.pid == a2->Pokemon[j].Base.pid)
                    {
                        a2->Pokemon[j].field_D4 = 1;
                    }
                }
                break;
            }
        }
    }
}

extern "C" void THUMB_BRANCH_SAFESTACK_StartBottomScreenMenu(BtlvCore *a1, BattlePokeListData *a2, int a3, char a4, __int16 a5)
{
    int v9;                  // r0
    int IsAllyInMultiBattle; // r0
    char v11;                // r1
    int v12;                 // [sp+0h] [bp-18h]
    int isRightBumper = (GCTX_HIDGetHeldKeys() & 256);
    int isLeftBumper = (GCTX_HIDGetHeldKeys() & 512);

    if (a3 != 0)
    {
        v12 = BattleClient_GetMyID(a1->client);
    }
    else if (isLeftBumper)
    {
        v12 = (MainModule_IsPartnerBattle(a1->mainModule)) ? ((a1->mainModule->btlSetup->btlType == 0) ? 1 : 3) : 1;
    }
    else if (isRightBumper)
    {
        v12 = (MainModule_IsPartnerBattle(a1->mainModule)) ? 1 : 1;
    }
    else
    {
        v12 = BattleClient_GetMyID(a1->client);
    }
    a2->pokeParty = MainModule_GetPokeParty(a1->mainModule, v12);
    if (v12 != BattleClient_GetMyID(a1->client))
    {
        findBattleMon(a1, a2->pokeParty, v12);
    }
    v9 = a3 != 3 && MainModule_IsCompetitiveBattleType(a1->mainModule);
    a2->IsBagDisabled = v9;
    if (v9)
    {
        a2->AllyPokeParty = MainModule_GetAllyPokeParty(a1->mainModule, v12);
        IsAllyInMultiBattle = sub_219C86C(a1->mainModule, v12);
    }
    else
    {
        IsAllyInMultiBattle = 0;
        a2->AllyPokeParty = 0;
    }
    a2->ListMode = a3;
    a2->AllyClientID = IsAllyInMultiBattle;
    if (BtlSetup_GetBattleStyle(a1->mainModule) == BTL_STYLE_ROTATION)
    {
        a2->NumPartyMembers = 3;
    }
    else
    {
        a2->NumPartyMembers = MainModule_CheckNumFrontPos(a1->mainModule, v12);
    }
    if (a3 == 4 || a3 == 5)
    {
        v11 = a4;
    }
    else
    {
        v11 = 0;
    }
    if (isLeftBumper || isRightBumper)
    {
        a2->field_3C = 1;
    }
    else
    {
        a2->field_3C = 0;
    }

    a2->SelectedMon = v11;
    a2->InfoPokeIndex = a4;
    a2->IsSelectedMonTrapped = a5;
    a2->MoveInfoMoveIndex = 0;
    a2->heapID = a1->heapID;
    a2->Font = a1->Font1;
    a2->battleStyle = (BattleStyle)BtlSetup_GetBattleStyle(a1->mainModule);
    a2->cursorFlag = (int)sub_689B7C8(a1->btlvScd);
    a2->tcbmanager = BtlvEffectMain_GetTCBManager();
    a2->palAnm = BtlvEffectMain_GetPalAnm();
    a2->gameData = MainModule_GetGameData(a1->mainModule);
    a2->IsFinished = 0;
    a2->SoundEffectFlag = sub_21CF250(a1);
    a2->CommErrorFlag = 0;
    a2->EndFlag = 0;
}


extern "C" void THUMB_BRANCH_SAFESTACK_PokeList_LoadPokeData(PokeListMain *a1, PartyPkm *a2, PokeListData *a3)
{
    u32 Param;             // r0
    char Level;            // r1
    int ExpForPkm_Wrapper; // r0
    char v7;               // r1
    unsigned int i;        // r6
    PokeList_MoveData *v9; // r4
    char v10;              // r0
    int isEnemy;
    BattleMon* mon;

    a3->partyPkm = a2;
    // mon = getBattleMon(a2);
    int PokeTypes; 

    if (a2)
    {
        a3->Species = PokeParty_GetParam(a2, PF_Species, 0);
        if (a3->Species)
        {
            // a3->Species = 201; // (a2->field_D8 == 1 && isEnemy && !GetScanSetting()) ? 201 : a3->Species;
            // a3->Forme = (a2->field_D8 == 1) ? 0:
            isEnemy = a1->pokeListSetupData->field_3C;
            
            // k::Printf("\nChecking the Pokeball and Nickname struccts for Pokemon #%d!\nPokeballl is %d\nPF_NicknameStr is %d\nPF_NicknameRaw is %d\nPF_NicknameStrKeepFlags is %d\nPF_NicknameRawKeepFlags is %d\nPF_HasNickname is %d\n",
            //     a3->Species,
            //     PokeParty_GetParam(a2, PF_Pokeball, 0),
            //     PokeParty_GetParam(a2, PF_NicknameStrBuf, 0),
            //     PokeParty_GetParam(a2, PF_NicknameRaw, 0),
            //     PokeParty_GetParam(a2, PF_NicknameStrBufKeepFlags, 0),
            //     PokeParty_GetParam(a2, PF_NicknameRawKeepFlags, 0),
            //     PokeParty_GetParam(a2, PF_HasNickname, 0)
            // );


            a3->Species = (a2->field_D8 == 1 && isEnemy && GetScanSetting()) ? 0 : a3->Species;
            a3->Species = (a2->field_D4 == 1) ? 0 : a3->Species;
            a3->Forme = PokeParty_GetParam(a3->partyPkm, PF_Forme, 0);

            if (isEnemy && GetScanSetting()) // && !GetScanSetting())
            {
                a3->Attack = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_ATK);
                a3->Defense = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_DEF);
                a3->Speed = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPE);
                a3->SpecialAttack = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPA);
                a3->SpecialDefense = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPD);
            }
            else
            {
                a3->Attack = PokeParty_GetParam(a3->partyPkm, PF_ATK, 0);
                a3->Defense = PokeParty_GetParam(a3->partyPkm, PF_DEF, 0);
                a3->Speed = PokeParty_GetParam(a3->partyPkm, PF_SPE, 0);
                a3->SpecialAttack = PokeParty_GetParam(a3->partyPkm, PF_SPA, 0);
                a3->SpecialDefense = PokeParty_GetParam(a3->partyPkm, PF_SPD, 0);
            }
            a3->CurrentHP = PokeParty_GetParam(a3->partyPkm, PF_NowHP, 0);
            a3->MaxHP = PokeParty_GetParam(a3->partyPkm, PF_MaxHP, 0);
            // PokeTypes = BattleMon_GetPokeType(mon);
            // a3->Type1 = PokeTypePair_GetType1(PokeTypes);
            // a3->Type2 = PokeTypePair_GetType2(PokeTypes);
            a3->Type1 = PokeParty_GetParam(a3->partyPkm, PF_Type1, 0);
            a3->Type2 = PokeParty_GetParam(a3->partyPkm, PF_Type2, 0);
            a3->Level = PokeParty_GetParam(a3->partyPkm, PF_Level, 0) & 0x7F | a3->Level & 0x80;
            Param = PokeParty_GetParam(a3->partyPkm, PF_IsNotNidoran, 0);
            Level = a3->Level;
            if (Param == 1)
            {
                a3->Level = Level & 0x7F;
            }
            else
            {
                a3->Level = Level | 0x80;
            }
            a3->SexStatusIsEgg = PokeParty_GetSex(a3->partyPkm) & 7 | a3->SexStatusIsEgg & 0xF8;
            a3->SexStatusIsEgg = (8 * sub_202D8EC(a3->partyPkm)) & 0x7F | a3->SexStatusIsEgg & 0x87;
            a3->SexStatusIsEgg = (PokeParty_GetParam(a3->partyPkm, PF_IsEgg, 0) << 7) | a3->SexStatusIsEgg & 0x7F;
            // a3->Ability = BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY);
            a3->Ability = PokeParty_GetParam(a3->partyPkm, PF_Ability, 0);
            a3->Item = PokeParty_GetParam(a3->partyPkm, PF_Item, 0);
            a3->Experience = (isEnemy) ? 0 : PokeParty_GetParam(a3->partyPkm, PF_Experience, 0);
            ExpForPkm_Wrapper = getExpForPkm_Wrapper(a3->partyPkm);
            v7 = a3->Level;
            a3->ExpForLevel = (isEnemy) ? 0 : ExpForPkm_Wrapper;
            if ((v7 & 0x7F) != 100)
            {
                ExpForPkm_Wrapper = PML_UtilGetPkmLvExp(a3->Species, a3->Forme, ((v7 & 0x7F) + 1));
            }
            a3->ExpToNextLevel = (isEnemy) ? 0 : ExpForPkm_Wrapper;
            for (i = 0; i < 4; ++i)
            {

                // currentPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0);
                // maxPP =  PML_MoveGetParam(v9->MoveID, MVDATA_BASEPP) + 3;
                int missingPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0) < (PML_MoveGetParam(PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0), MVDATA_BASEPP) + ((a2->field_D8 == 2) ? 0 : 3));
                if (isEnemy && !missingPP && GetScanSetting()) // && !(PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0) < (PML_MoveGetParam(v9->MoveID, MVDATA_BASEPP) + 3)))
                {
                    continue;
                }
                else
                {

                    PokeList_MoveData *v9 = &a3->MoveData[i];
                    v9->MoveID = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0);
                    if (v9->MoveID)
                    {
                        v9->CurrentPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0);
                        v9->MaxPP = PML_MoveGetParam(PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0), MVDATA_BASEPP) + ((a2->field_D8 == 2 || !isEnemy) ? 0 : 3);
                        // v9->MaxPP = PML_MoveGetMaxPP(v9->MoveID, v9->MaxPP) + 3;
                        // if (isEnemy)
                        // {
                        //     v9->MaxPP = PML_MoveGetParam(v9->MoveID, MVDATA_BASEPP);
                        // }
                        v9->Type = PML_MoveGetParam(v9->MoveID, MVDATA_TYPE);
                        v9->Category = PML_MoveGetParam(v9->MoveID, MVDATA_CATEGORY);
                        if (PML_MoveIsAlwaysHit(v9->MoveID))
                        {
                            v10 = 0;
                        }
                        else
                        {
                            v10 = PML_MoveGetParam(v9->MoveID, MVDATA_ACCURACY);
                        }
                        v9->Accuracy = v10;
                        v9->Power = PML_MoveGetParam(v9->MoveID, MVDATA_POWER);
                    }
                }
            }
        }
    }
    else
    {
        a3->Species = 0;
    }
}


extern "C" int THUMB_BRANCH_SAFESTACK_PokeList_DetermineSwitchInFailCause(PokeListMain *a1)
{
    int SelectedMonID; // r0
    PokeListData *v3;  // r5

    SelectedMonID = PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon);
    v3 = &a1->pokeListData[SelectedMonID];
    if (a1->pokeListSetupData->field_3C)
    {
        return 7;
    }
    if (sub_21FA27C(a1, SelectedMonID))
    {
        return 1;
    }
    if (!v3->CurrentHP)
    {
        return 2;
    }
    if (PokeList_IsAlreadyInBattle(a1, a1->pokeListSetupData->SelectedMon))
    {
        return 3;
    }
    if (PokeList_IsEgg(a1))
    {
        return 5;
    }
    if (PokeList_IsAlreadySelectedForSwitchIn(a1, a1->pokeListSetupData->SelectedMon) == 1)
    {
        return 4;
    }
    if (a1->pokeListSetupData->IsSelectedMonTrapped)
    {
        return 6;
    }
    return 0;
}

extern "C" int THUMB_BRANCH_SAFESTACK_PokeList_LoadSwitchInFailMessage(PokeListMain *a1)
{
    StrBuf *StrbufNew; // r7
    int SelectedMonID; // r6
    unsigned int v4;   // r0
    int v5;            // r1
    MsgData *msgdata;  // r0
    int v7;            // r1
    MsgData *v8;       // r0

    SelectedMonID = PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon);
    v4 = PokeList_DetermineSwitchInFailCause(a1);
    if (v4 <= 7)
    {
        if (v4 == 0)
        {
            return 1;
        }
        else if (v4 == 1)
        {
            v5 = 90;
            msgdata = a1->msgData;
            goto LABEL_4;
        }
        else if (v4 == 2)
        {
            v7 = 87;
            v8 = a1->msgData;
            goto LABEL_6;
        }
        else if (v4 == 3)
        {
            v7 = 86;
            v8 = a1->msgData;
            goto LABEL_6;
        }
        else if (v4 == 4)
        {
            v7 = 103;
            v8 = a1->msgData;
            goto LABEL_6;
        }
        else if (v4 == 7)
        {
            v5 = 108;
            msgdata = a1->msgData;
            goto LABEL_4;
        }
        else if (v4 == 5)
        {
            v5 = 89;
            msgdata = a1->msgData;
        LABEL_4:
            StrbufNew = GFL_MsgDataLoadStrbufNew(msgdata, v5);
        }
        else if (v4 == 6)
        {
            SelectedMonID = a1->pokeListSetupData->InfoPokeIndex;
            v7 = 88;
            v8 = a1->msgData;
        LABEL_6:
            StrbufNew = GFL_MsgDataLoadStrbufNew(v8, v7);
            loadPokemonNicknameToStrbuf(a1->WordSetSystem, 0, a1->pokeListData[SelectedMonID].partyPkm);
        }
        else if (v4 == 7)
        {
        }
        else
        {
        }
    }
    GFL_WordSetFormatStrbuf(a1->WordSetSystem, (StrBuf *)a1->StrBuf, StrbufNew);
    GFL_StrBufFree(StrbufNew);
    return 0;
}

#pragma endregion 

#pragma region WIP 
#if USING_OVERRIDE_CONTACT
    bool overrideContact(BattleMon *a1, MoveID a2)
    {
        if (BattleMon_GetHeldItem(a1) == IT0293_SAFETY_GOGGLES || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            return true;
        return false;
    }

    void THUMB_BRANCH_CommonContactStatusAbility(
        ServerFlow *a1,
        unsigned int *a2,
        MoveCondition a3,
        ConditionData a4,
        unsigned __int8 a5)
    {
        unsigned __int16 Value; // r0
        BattleMon *attackingMon;
        HandlerParam_AddCondition *v9; // r5
        u8 monInQuestion = (((int)a2 == BattleEventVar_GetValue(VAR_DEFENDING_MON)) ? BattleEventVar_GetValue(VAR_ATTACKING_MON) : ((int)a2 == BattleEventVar_GetValue(VAR_ATTACKING_MON)) ? BattleEventVar_GetValue(VAR_DEFENDING_MON) : 255);
        if (monInQuestion != 255 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT) && !AbilityEvent_RollEffectChance((int)a1, a5))
            {
                v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, (int)a2);
                v9->header.flags |= 0x800000u;
                v9->sickID = a3;
                v9->sickCont = a4;
                v9->fAlmost = 0;
                v9->pokeID = monInQuestion;
                BattleHandler_PopWork(a1, v9);
            }
        }
    }
    void THUMB_BRANCH_HandlerMummy(int a1, ServerFlow *a2, unsigned int a3)
    {
        unsigned __int16 Value;         // r0
        unsigned int v6;                // r6
        BattleMon *BattleMon;           // r0
        HandlerParam_ChangeAbility *v8; // r4

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && !Handler_CheckMatchup((int)a2))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v6);

                if (overrideContact(BattleMon, (MoveID)Value))
                    return;

                if (BattleMon_GetValue(BattleMon, VALUE_ABILITY) != 152)
                {
                    v8 = (HandlerParam_ChangeAbility *)BattleHandler_PushWork(a2, EFFECT_CHANGEABILITY, a3);
                    v8->abilityID = 152;
                    v8->pokeID = v6;
                    BattleHandler_StrSetup(&v8->exStr, 2u, 463);
                    BattleHandler_AddArg(&v8->exStr, v8->pokeID);
                    if (!MainModule_IsAllyMonID(a3, v6))
                    {
                        v8->header.flags |= 0x800000u;
                    }
                    BattleHandler_PopWork(a2, v8);
                }
            }
        }
    }
    
    void THUMB_BRANCH_HandlerRoughSkin(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;  // r0
        int v6;                  // r6
        BattleMon *BattleMon;    // r7
        HandlerParam_Damage *v8; // r4

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v6);

                if (overrideContact(BattleMon, (MoveID)Value))
                    return;

                if (!BattleMon_IsFainted(BattleMon))
                {
                    v8 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                    v8->header.flags |= 0x800000u;
                    v8->pokeID = v6;
                    v8->damage = DivideMaxHPZeroCheck(BattleMon, 8u);
                    BattleHandler_StrSetup(&v8->exStr, 2u, 430);
                    BattleHandler_AddArg(&v8->exStr, v6);
                    BattleHandler_PopWork(a2, v8);
                }
            }
        }
    }
#endif

#if ADDING_BATTLE_BOX_FIGHTS 

extern PokeParty * convertBoxedPokeSetToParty(void *pBox, HeapID heapId);
extern void * GameData_GetSaveControl(GameData *gameData);
extern void *  getBattleBox(void *pSaveInfoBase);

void THUMB_BRANCH_SAFESTACK_BtlSetup_SetTrainer2v2(
        void *setup,
        GameData *gameData,
        BattleFieldStatus *fieldStatus,
        int allyTrId,
        int foe1TrId,
        int foe2TrId,
        HeapID heapId)
{
    BtlSetup_LoadTrainerBase(setup, gameData, BTL_STYLE_DOUBLE, fieldStatus, heapId);
    BtlSetup_LoadTrainer(setup, gameData, 2, (PokeParty **)((u8 *)setup + 0x2C), allyTrId, heapId);
    BtlSetup_LoadTrainer(setup, gameData, 1, (PokeParty **)((u8 *)setup + 0x28), foe1TrId, heapId);
    BtlSetup_LoadTrainer(setup, gameData, 3, (PokeParty **)((u8 *)setup + 0x30), foe2TrId, heapId);
    if (allyTrId == BATTLE_BOX_ID){
        (PokeParty **)((u8 *)setup + 0x2C) = convertBoxedPokeSetToParty(getBattleBox(GameData_GetSaveControl(gameData)), heapId)
    }
  setup->field_22 = 3;
}
#endif 
#pragma endregion