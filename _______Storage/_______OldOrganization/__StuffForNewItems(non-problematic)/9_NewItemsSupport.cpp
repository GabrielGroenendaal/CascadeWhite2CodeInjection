#include "newitems_support.h"
#include "../settings.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

extern "C"
{

#if TOGGLE_TMS
    void THUMB_BRANCH_sub_21AD5A0(void *a1, int a2, int a3)
    {
        ShopUIWork *v4;          // r5
        int result;              // r0
        unsigned int BlockWidth; // r6
        GFLBitmap *Bitmap;       // r0
        u32 Width;               // r7
        GFLBitmap *v9;           // r0
        unsigned int v10;        // r6
        GFLBitmap *v11;          // r0
        u32 v12;                 // r7
        GFLBitmap *v13;          // r0

        v4 = sub_2026548(a1);
        result = -2;
        if (a2 != -2)
        {
            if (BagSave_CheckAmount(v4->Bag, v4->ItemInfo[a2].TagID, 1) && !PML_ItemIsTMHM(v4->ItemInfo[a2].TagID))
            {
                BlockWidth = GFL_FontGetBlockWidth(v4->NoneDispStr, v4->m_Font, 0);
                Bitmap = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                Width = GFL_BitmapGetWidth(Bitmap);
                v9 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                sub_21AD4CC(v4->dword1D8, v9, Width - BlockWidth, a3, v4->NoneDispStr, v4->m_Font, 12704);
            }
            else
            {
                WordSetNumber(v4->WordSet, 1, v4->ItemInfo[a2].Price, 5u, 1u, 1);
                GFL_WordSetFormatStrbuf(v4->WordSet, v4->StrBuff, v4->BalanceDispStr);
                v10 = GFL_FontGetBlockWidth(v4->StrBuff, v4->m_Font, 0);
                v11 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                v12 = GFL_BitmapGetWidth(v11);
                v13 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
                sub_21AD4CC(v4->dword1D8, v13, v12 - v10, a3, v4->StrBuff, v4->m_Font, 12704);
            }
        }
    }
#endif

    int THUMB_BRANCH_SAFESTACK_TransformVsPokePartyBySeason(GameData *gameData, PokeParty *party, Season s)
    {
        int result;
        return result;
    }

    u32 GetIVSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16433);

        // k::Printf("Current IV setting is %d\n", *lvl_cap_ptr);

        return *lvl_cap_ptr;
    }

    // void THUMB_BRANCH_SAFESTACK_createEggPkm(PartyPkm *newPkm, EggPkm *eggPkm, void *pTrainerInfo, u16 location, HeapID heapId)
    // {
    //     int i;             // r4
    //     StrBuf *v8;        // r4
    //     StrBuf *StrbufNew; // r4
    //     int v12[12];       // [sp+18h] [bp-30h]
    //     int random2;

    //     v12[6] = location;
    //     v12[0] = 70;
    //     v12[1] = 71;
    //     v12[2] = 72;
    //     v12[3] = 74;
    //     v12[4] = 75;
    //     v12[5] = 73;
    //     PokeParty_CreatePkm(
    //         newPkm,
    //         (MonsNo)(unsigned __int16)eggPkm->Species,
    //         eggPkm->Level,
    //         eggPkm->TID,
    //         ABIL_0,
    //         0xFFFFFFFF,
    //         eggPkm->PID,
    //         0);
    //     PokeParty_SetParam(newPkm, PF_Forme, eggPkm->Forme);
    //     PokeParty_SetParam(newPkm, PF_Nature, eggPkm->Nature);
    //     PokeParty_SetParam(newPkm, PF_Happiness, eggPkm->Happiness);
    //     if (eggPkm->Ability == 2)
    //     {
    //         PokeParty_SetHiddenAbil(newPkm, eggPkm->Species, eggPkm->Forme);
    //     }
    //     for (i = 0; i < 6; ++i)
    //     {
    //         PokeParty_SetParam(newPkm, (PkmField)v12[i], eggPkm->IVs[i]);
    //     }

    // if (GetIVSetting() == 1)
    // {
    //     PokeParty_SetParam(newPkm, PF_IvATK, 31);
    //     PokeParty_SetParam(newPkm, PF_IvDEF, 31);
    //     PokeParty_SetParam(newPkm, PF_IvHP, 31);
    //     PokeParty_SetParam(newPkm, PF_IvSPA, 31);
    //     PokeParty_SetParam(newPkm, PF_IvSPD, 31);
    //     PokeParty_SetParam(newPkm, PF_IvSPE, 31);
    // }

    // for (int i; i < ARRAY_COUNT(whiteListedPokemon); i++)
    // {
    //     if (whiteListedPokemon[i] == (MonsNo)eggPkm->Species)
    //     {
    //         random2 = GFL_RandomLCAlt(100u);

    //         if (random2 <= 45u)
    //         {

    //             PokeParty_SetParam(newPkm, PF_Ability,
    //                                PML_PersonalGetParam(
    //                                    PML_PersonalLoadBW2(eggPkm->Species, PokeParty_GetParam(newPkm, PF_Forme, 0)),
    //                                    Personal_Abil1));
    //         }
    //         else if (random2 > 45u && random2 <= 90u)
    //         {
    //             PokeParty_SetParam(newPkm, PF_Ability,
    //                                PML_PersonalGetParam(
    //                                    PML_PersonalLoadBW2(eggPkm->Species, PokeParty_GetParam(newPkm, PF_Forme, 0)),
    //                                    Personal_Abil2));
    //         }
    //         else
    //         {
    //             PokeParty_SetParam(newPkm, PF_Ability,
    //                                PML_PersonalGetParam(
    //                                    PML_PersonalLoadBW2(eggPkm->Species, PokeParty_GetParam(newPkm, PF_Forme, 0)),
    //                                    Personal_AbilH));
    //         }
    //         i = ARRAY_COUNT(whiteListedPokemon);
    //     }
    // }

    //     PokeParty_SetParam(newPkm, PF_Move1, eggPkm->Moves[0]);
    //     PokeParty_SetParam(newPkm, PF_Move2, eggPkm->Moves[1]);
    //     PokeParty_SetParam(newPkm, PF_Move3, eggPkm->Moves[2]);
    //     PokeParty_SetParam(newPkm, PF_Move4, eggPkm->Moves[3]);
    //     v8 = (StrBuf *)copyTrainerNameToNewStrbuf((wchar_t *)pTrainerInfo, heapId);
    //     PokeParty_SetParam(newPkm, PF_OTNameStrBuf, (u32)v8);
    //     GFL_StrBufFree(v8);
    //     StrbufNew = GFL_MsgDataLoadStrbufNew((MsgData*)g_PMLSpeciesNamesResident, 650);
    //     PokeParty_SetParam(newPkm, PF_NicknameStrBuf, (u32)StrbufNew);
    //     GFL_StrBufFree(StrbufNew);
    //     PokeParty_SetupMetData(newPkm, PKM_OBTAIN_EGG_BRED, pTrainerInfo, location, heapId);
    //     PokeParty_SetParam(newPkm, PF_IsEgg, 1u);
    //     PokeParty_PPRecover(newPkm);
    //     PokeParty_RecalcStats(newPkm);
    //     PokeParty_Recover(newPkm);
    // };

    int THUMB_BRANCH_SAFESTACK_s010F_PokePartyAddEgg(void *vm, void *env)
    {
        HeapID heapId;           // r4
        u16 *Var;                // r6
        u32 Any;                 // r7
        int Capacity;            // r5
        int result;              // r0
        PartyPkm *v9;            // r5
        u16 *GameDataPlayerInfo; // r0
        StrBuf *v11;             // r7
        u16 Param;               // r0
        PersonalData *v13;       // r7
        StrBuf *StrbufNew;       // r7
        GameData *pBaseBlk;      // [sp+4h] [bp-2Ch]
        PokeParty *pPartyBlk;    // [sp+8h] [bp-28h]
        u16 *pTrainerInfo;       // [sp+Ch] [bp-24h]
        MonsNo species;          // [sp+10h] [bp-20h]
        u32 data;                // [sp+14h] [bp-1Ch]
        int random2;

        FieldScriptEnv_GetGameSystem(env);
        pBaseBlk = FieldScriptEnv_GetGameData(env);
        heapId = FieldScriptEnv_GetHeapID(env);
        pPartyBlk = GameData_GetParty(pBaseBlk);
        pTrainerInfo = GetGameDataPlayerInfo(pBaseBlk);
        Var = ScriptReadVar(vm, env);
        species = (MonsNo)ScriptReadAny(vm, env);
        Any = ScriptReadAny(vm, env);
        Capacity = PokeParty_GetCapacity(pPartyBlk);
        if (Capacity > (int)PokeParty_GetPkmCount(pPartyBlk))
        {
            v9 = PokeParty_NewTempPkm(species, 1u, 0xFFFFFFFF, (AbilLock)-1, heapId);
            PokeParty_SetParam(v9, PF_Forme, Any);
            GameDataPlayerInfo = GetGameDataPlayerInfo(pBaseBlk);
            v11 = (StrBuf *)copyTrainerNameToNewStrbuf((wchar_t *)GameDataPlayerInfo, heapId);
            PokeParty_SetParam(v9, PF_OTNameStrBuf, (u32)v11);
            GFL_StrBufFree(v11);
            LOWORD((unsigned int &)v11) = PokeParty_GetParam(v9, PF_Species, 0);
            Param = PokeParty_GetParam(v9, PF_Forme, 0);
            v13 = PML_PersonalLoad(species, Param, heapId);
            data = PML_PersonalGetParam(v13, Personal_EggHappiness);
            PML_PersonalFree(v13);
            PokeParty_SetParam(v9, PF_Happiness, data);
            PokeParty_SetParam(v9, PF_IsEgg, 1u);

            if (GetIVSetting() == 2)
            {
                PokeParty_SetParam(v9, PF_IvATK, 31);
                PokeParty_SetParam(v9, PF_IvDEF, 31);
                PokeParty_SetParam(v9, PF_IvHP, 31);
                PokeParty_SetParam(v9, PF_IvSPA, 31);
                PokeParty_SetParam(v9, PF_IvSPD, 31);
                PokeParty_SetParam(v9, PF_IvSPE, 31);
            }
            else if (GetIVSetting() == 1)
            {
                int numOfPerfectIVs = 0;
                PkmField ivs[6] = {PF_IvHP, PF_IvATK, PF_IvDEF, PF_IvSPA, PF_IvSPD, PF_IvSPE};
                int changedIVs[6] = {0, 0, 0, 0, 0, 0};
                do
                {
                    random2 = GFL_RandomLCAlt(5u);
                    if (changedIVs[random2] == 0)
                    {
                        changedIVs[random2] == 1;
                        PokeParty_SetParam(v9, ivs[random2], 31);
                        numOfPerfectIVs++;
                    }
                } while (numOfPerfectIVs < 3);
            }
            else
            {
            }

            if (WhiteListedPokemon[species] == 1)
            {
                random2 = GFL_RandomLCAlt(100u);

                if (random2 <= 45u)
                {

                    PokeParty_SetParam(v9, PF_Ability,
                                       PML_PersonalGetParam(
                                           PML_PersonalLoadBW2(species, PokeParty_GetParam(v9, PF_Forme, 0)),
                                           Personal_Abil1));
                }
                else if (random2 > 45u && random2 <= 90u)
                {
                    PokeParty_SetParam(v9, PF_Ability,
                                       PML_PersonalGetParam(
                                           PML_PersonalLoadBW2(species, PokeParty_GetParam(v9, PF_Forme, 0)),
                                           Personal_Abil2));
                }
                else
                {
                    PokeParty_SetParam(v9, PF_Ability,
                                       PML_PersonalGetParam(
                                           PML_PersonalLoadBW2(species, PokeParty_GetParam(v9, PF_Forme, 0)),
                                           Personal_AbilH));
                }
            }

            StrbufNew = GFL_MsgDataLoadStrbufNew((MsgData *)g_PMLSpeciesNamesResident, 650);
            PokeParty_SetParam(v9, PF_NicknameStrBuf, (u32)StrbufNew);
            GFL_StrBufFree(StrbufNew);
            PokeParty_RecalcStats(v9);
            PokeParty_SetupMetData(v9, PKM_OBTAIN_EGG_BRED, pTrainerInfo, 0xEA63u, heapId);
            PokeParty_AddPkm(pPartyBlk, v9);
            GFL_HeapFree(v9);
            *Var = 1;
            return 0;
        }
        else
        {
            result = 0;
            *Var = 0;
        }
        return result;
    };

    int THUMB_BRANCH_FieldEncount_CreateWildPkm(PartyPkm *pPkm, EncountManager *mgr, WildPokemonParam *pkmData)
    {
        u32 pid;                  // r7
        u32 baseShinyRerollCount; // r6
        BagSaveData *Bag;         // r0
        u32 v8;                   // r0
        u32 rareRerollIndex;      // r6
        u32 HeldItem;             // r2
        u32 TrainerGender;        // r0
        wchar_t *PlayerName;      // r0
        int result;               // r0
        u16 *pTrainerInfo;
        u32 rareRerollCount;    // [sp+14h] [bp-1Ch]
        PersonalData *personal; // [sp+18h] [bp-18h]
        u32 random;
        u32 random2;

        pTrainerInfo = GetGameDataPlayerInfo(mgr->gameData);
        personal = PML_PersonalLoad(pkmData->Species, pkmData->Forme, HEAPID_GAMEEVENT);
        baseShinyRerollCount = 1;
        Bag = GameData_GetBag(mgr->gameData);
        if (BagSave_CheckAmount(Bag, 632, 1))
        {
            baseShinyRerollCount = 3;
        }
        v8 = PassPower_ApplyLuckyShiny(baseShinyRerollCount);
        rareRerollIndex = 0;
        for (rareRerollCount = v8; rareRerollIndex < rareRerollCount; ++rareRerollIndex)
        {
            pid = FieldEncount_GenPID(mgr, personal, pkmData);
            if (PML_UtilPIDIsRare(mgr->PTID, pid))
            {
                break;
            }
        }
        PokeParty_CreatePkm(pPkm, (MonsNo)pkmData->Species, pkmData->Level, mgr->PTID, ABIL_0, 0xFFFFFFFF, pid, 0);
        PokeParty_ChangeForme(pPkm, pkmData->Forme);

        if (pkmData->Species == 585)
        {
            random = GFL_RandomLCAlt(100u);

            if (random <= 25u)
            {
                PokeParty_ChangeForme(pPkm, 0);
            }
            else if (random > 25u && random <= 50u)
            {
                PokeParty_ChangeForme(pPkm, 1);
            }
            else if (random > 50u && random <= 75u)
            {
                PokeParty_ChangeForme(pPkm, 2);
            }
            else if (random > 75u && random <= 100u)
            {
                PokeParty_ChangeForme(pPkm, 3);
            }
            else
            {
                PokeParty_ChangeForme(pPkm, 0);
            }
        }

        if (GetIVSetting() == 2)
        {
            PokeParty_SetParam(pPkm, PF_IvATK, 31);
            PokeParty_SetParam(pPkm, PF_IvDEF, 31);
            PokeParty_SetParam(pPkm, PF_IvHP, 31);
            PokeParty_SetParam(pPkm, PF_IvSPA, 31);
            PokeParty_SetParam(pPkm, PF_IvSPD, 31);
            PokeParty_SetParam(pPkm, PF_IvSPE, 31);
        }
        else if (GetIVSetting() == 1)
        {

            int numOfPerfectIVs = 0;
            PkmField ivs[6] = {PF_IvHP, PF_IvATK, PF_IvDEF, PF_IvSPA, PF_IvSPD, PF_IvSPE};
            int changedIVs[6] = {0, 0, 0, 0, 0, 0};
            do
            {
                random2 = GFL_RandomLCAlt(5u);
                if (changedIVs[random2] == 0)
                {
                    changedIVs[random2] == 1;
                    PokeParty_SetParam(pPkm, ivs[random2], 31);
                    numOfPerfectIVs++;
                }
            } while (numOfPerfectIVs < 3);
        }
        else
        {
        }

        PokeParty_SetDefaultMoves(pPkm);

        if (WhiteListedPokemon[pkmData->Species] == 1)
        {
            random2 = GFL_RandomLCAlt(100u);

            if (random2 <= 45u)
            {

                PokeParty_SetParam(pPkm, PF_Ability,
                                   PML_PersonalGetParam(
                                       PML_PersonalLoadBW2(pkmData->Species, PokeParty_GetParam(pPkm, PF_Forme, 0)),
                                       Personal_Abil1));
            }
            else if (random2 > 45u && random2 <= 90u)
            {
                PokeParty_SetParam(pPkm, PF_Ability,
                                   PML_PersonalGetParam(
                                       PML_PersonalLoadBW2(pkmData->Species, PokeParty_GetParam(pPkm, PF_Forme, 0)),
                                       Personal_Abil2));
            }
            else
            {
                PokeParty_SetParam(pPkm, PF_Ability,
                                   PML_PersonalGetParam(
                                       PML_PersonalLoadBW2(pkmData->Species, PokeParty_GetParam(pPkm, PF_Forme, 0)),
                                       Personal_AbilH));
            }
        }

        if (pkmData->HiddenAbility)
        {
            PokeParty_SetHiddenAbil(pPkm, pkmData->Species, pkmData->Forme);
        }
        HeldItem = pkmData->HeldItem;
        if (HeldItem <= 0x27E)
        {
            if (pkmData->HeldItem)
            {
                PokeParty_SetParam(pPkm, PF_Item, HeldItem);
            }
            else
            {
                FieldEncount_SetRandomHeldItem(
                    pPkm,
                    personal,
                    (unsigned int)(mgr->Flags << 22) >> 31,
                    mgr->EncType == ENCTYPE_LAND_DOUBLE);
            }
        }
        TrainerGender = getTrainerGender(pTrainerInfo);
        PokeParty_SetParam(pPkm, PF_TrGender, TrainerGender);
        PlayerName = GetPlayerName((int)pTrainerInfo);
        PokeParty_SetParam(pPkm, PF_OTNameRaw, (u32)PlayerName);
        if ((mgr->Flags & 0x400) != 0)
        {
            PokeParty_SetParam(pPkm, PF_Nature, mgr->PPkNature);
        }
        PokeParty_RecalcStats(pPkm);
        PML_PersonalFree(personal);
        return result;
    }
    // struct TrClassBattleBGOverride
    // {
    //     u16 TrClassID;
    //     u16 BattleBGID;
    // };

    // TrClassBattleBGOverride TR_CLASS_BATTLE_BG_OVERRIDES[] = {
    //     {0xBD, 0x14},
    //     {218, 4},
    //     {232, 35},
    //     {215, 35},
    //     {213, 35},
    //     {220, 35}};

    int THUMB_BRANCH_CheckOverridenTrainerBattleBG(int trClass, int defaultBgId)
    {
        int v2; // r5
        v2 = 0xBD;
        v2 = 0x14;
        v2 = 0;
        if (trClass == 0xBD)
        {
            return 0x14;
        }
        if (trClass == 218)
        {
            return 4;
        }

        return defaultBgId;
    }

    struct EncEff
    {
        void *EventData;
        void (*RenderFunc)(EncEff *);
        void *m_Field;
        u32 SubOverlayIDs[3];
        u32 SubOverlayCount;
        void *WorkArea;
    };

    struct SWAN_ALIGNED(4) GameEvent
    {
        void *ReturnEvent;
        void *Callback;
        u32 EventState;
        void *EventData;
        void *m_GameSystem;
    };

    struct EncEffCtl
    {
        GameEvent *(*EventCreateFunc)(void *, void *, int);
        void (*RenderFunc)(EncEff *);
        unsigned int OverlayID;
        unsigned int IsOutFadeWhite;
        unsigned int RequiredHeapSize;
    };

    EncEffCtl *ENC_EFFECT_CONTROLLERS = (EncEffCtl *)0x21D2620;

    extern void GameEvent_ChainNext(void *currentEvent, void *event);
    extern void EncEff_LoadSubOvl(void *encEff, u32 ovlId);
    extern void *Field_GetGameSystem(void *field_info);
    extern u32 GFL_HeapGetHighestAllocatableSize(HeapID heapId);
    extern void *GameEvent_GetData(GameEvent *event);
    extern GameData *GSYS_GetGameData(void *gsys);
    extern GameEvent *GameEvent_Create(void *gsys, GameEvent *parent, void *callback, u32 dataSize);
    extern void *GameData_GetFieldSoundSystem(GameData *gameData);
    extern void *GSYS_GetPlayerState(void *gsys);
    extern int EventBattleBGMPlay_Callback(int a1, _DWORD *a2, void *event);
    extern int PlayerState_GetZoneID(void *a1);

    void THUMB_BRANCH_EncEff_StartEvent(EncEff *encEff, GameEvent *parentEvent, int battleBGId)
    {
        void *m_Field;    // r7
        int v6;           // r6
        int OverlayID;    // r1
        GameEvent *v8;    // r4
        void *GameSystem; // [sp+4h] [bp-1Ch]

        m_Field = encEff->m_Field;
        GameSystem = Field_GetGameSystem(m_Field);
        if (battleBGId >= 38)
        {
            battleBGId = 0;
        }
        if (GFL_HeapGetHighestAllocatableSize(HEAPID_FIELDMAP) < ENC_EFFECT_CONTROLLERS[battleBGId].RequiredHeapSize)
        {
            battleBGId = 7;
        }

        if (PlayerState_GetZoneID(GSYS_GetPlayerState(GameSystem)) == 613)
        {
            battleBGId = 35;
        }

        v6 = battleBGId;
        OverlayID = ENC_EFFECT_CONTROLLERS[battleBGId].OverlayID;
        if (OverlayID != -1)
        {
            EncEff_LoadSubOvl(encEff, OverlayID);
        }
        v8 = ENC_EFFECT_CONTROLLERS[battleBGId].EventCreateFunc(
            GameSystem,
            m_Field,
            ENC_EFFECT_CONTROLLERS[battleBGId].IsOutFadeWhite);
        GameEvent_ChainNext(parentEvent, v8);
        encEff->EventData = GameEvent_GetData(v8);
        encEff->RenderFunc = ENC_EFFECT_CONTROLLERS[v6].RenderFunc;
    };

    enum BattleStyle
    {
        BTL_STYLE_SINGLE = 0x0,
        BTL_STYLE_DOUBLE = 0x1,
        BTL_STYLE_TRIPLE = 0x2,
        BTL_STYLE_ROTATION = 0x3,
    };
    struct SWAN_ALIGNED(2) BattleFieldStatus
    {
        u32 BattleBGID;
        _DWORD BattlePedestalID;
        _BYTE BtlWeather;
        u8 Season;
        u16 ZoneID;
        u8 Hour;
        u8 Minute;
        char field_E;
        char field_F;
    };
    struct TrainerBattleSetup
    {
        _DWORD TrID;
        _DWORD TrClass;
        _DWORD TrAIBits;
        u16 TrItems[4];
        StrBuf *TrainerName;
        __int16 field_18[4];
        __int16 field_20[4];
    };

    enum BattleResult
    {
        BTL_RESULT_DEFEAT = 0x0,
        BTL_RESULT_VICTORY = 0x1,
        BTL_RESULT_DRAW = 0x2,
        BTL_RESULT_FLEE = 0x3,
        BTL_RESULT_FLEE_FOE = 0x4,
        BTL_RESULT_CAPTURE = 0x5,
        BTL_RESULT_6 = 0x6,
    };

    struct SWAN_ALIGNED(4) BtlSetup
    {
        u32 BtlType;
        BattleStyle BtlStyle;
        BattleFieldStatus m_FieldStatus;
        u16 BattleBGMID;
        __int16 WinBGMID;
        int field_1C;
        char field_20;
        char field_21;
        char field_22;
        char field_23;
        PokeParty *Parties[4];
        int m_PlayerInfo;
        int field_38;
        int field_3C;
        int field_40;
        int field_44;
        TrainerBattleSetup *TrainerSetups[4];
        int field_58;
        int field_5C;
        int field_60;
        int field_64;
        int field_68;
        int field_6C;
        int field_70;
        int m_TrainerData;
        int m_ItemWork;
        int field_7C;
        int m_Dex;
        int m_RecordData;
        int field_88;
        int field_8C;
        int field_90;
        char field_94;
        char field_95;
        char field_96;
        char field_97;
        char BadgeCount;
        char field_99;
        char field_9A;
        char field_9B;
        int field_9C;
        __int16 field_A0;
        __int16 field_A2;
        int field_A4;
        BattleResult BattleResult;
        char CapturedPkmIdx;
        char field_AD;
        __int16 field_AE;
        void *field_B0;
        int field_B4;
        int field_B8;
        int field_BC;
        int field_C0;
        int field_C4;
        int field_C8;
        int field_CC;
        u16 HPSum;
        u8 CurrentTurn;
        u8 SwitchCount;
        u8 NoEffectHits;
        u8 SuperEffectiveHits;
        u8 NotVeryEffectiveHits;
        u8 OpponentNoEffectHits;
        u8 OpponentNotVeryEffectiveHits;
        u8 BattlesWon;
        u8 OpponentFainted;
        u8 AllyFainted;
        u8 UniqueMovesUsed;
        char field_DD;
        char field_DE;
        char field_DF;
        int field_E0;
        int field_E4;
        int field_E8;
        int field_EC;
        int field_F0;
        int field_F4;
        int field_F8;
        int field_FC;
        int field_100;
        int field_104;
        int field_108;
        int field_10C;
        int field_110;
        int field_114;
        int field_118;
        int field_11C;
        int field_120;
        int field_124;
        int field_128;
        int field_12C;
        int field_130;
        int field_134;
        int field_138;
        u8 KeySystemLevelAdjust;
        char field_13D;
        char field_13E;
        char field_13F;
        int field_140;
        int field_144;
        int field_148;
    };

    struct SWAN_ALIGNED(4) EventBattleCall
    {
        void *GameSys;
        GameData *GameData;
        BtlSetup *BtlSetup;
        _BYTE gapC[8];
        b32 HasOwnExitHandler;
        b32 NoAutoDefeat;
        u32 IsTrialHouseBattle;
        int RetainBtlSetupOnExit;
        u32 EncEffID;
        u32 Flags;
    };

    // THUMB_BRANCH_EventBattleBGMPlay_Create(void *gsys, int bgmId)
    // {
    //     GameData *GameData; // r7
    //     GameEvent *v5;      // r6
    //     _DWORD *Data;       // r4

    //     GameData = GSYS_GetGameData(gsys);
    //     v5 = GameEvent_Create(gsys, 0, (void *)EventBattleBGMPlay_Callback, 0x10u);
    //     Data = (unsigned int *)GameEvent_GetData(v5);
    //     Data[1] = (unsigned int)GameData_GetFieldSoundSystem(GameData);
    //     Data[2] = bgmId;
    //     return v5;
    // };

    // extern void sys_memset32(u32 value, void *ptr, size_t size);

    // void THUMB_BRANCH_EventBattleCall_Setup(EventBattleCall *event, void *gsys, BtlSetup *btlSetup)
    // {
    //     k::Printf("\nThe battle id is %d\n", btlSetup->TrainerSetups[1]->TrID);

    //     if (btlSetup->TrainerSetups[1]->TrID == 491 ||  btlSetup->TrainerSetups[1]->TrID == 507 || btlSetup->TrainerSetups[1]->TrID == 508 || btlSetup->TrainerSetups[1]->TrID == 509){
    //         event->EncEffID = 35;
    //     }

    //     sys_memset32(0, event, 0x2Cu);
    //     event->GameSys = gsys;
    //     event->GameData = GSYS_GetGameData(gsys);
    //     event->BtlSetup = btlSetup;
    //     event->HasOwnExitHandler = 0;
    //     event->NoAutoDefeat = 0;
    //     event->IsTrialHouseBattle = 0;
    // };
}