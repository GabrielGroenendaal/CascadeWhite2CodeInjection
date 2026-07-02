#include "newitems_support.h"
#include "../A_CoreBattle/settings.h"
#include "kPrint.h"
extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

#define GIANT_CHASM 100        // CHANGE THIS LATER
#define GIANT_CHASM_CAVE 100   // CHANGE THIS LATER
#define GIANT_CHASM_FOREST 100 // CHANGE THIS LATER
#define ROUTE_22 100           // CHANGE THIS LATER
#define ROUTE_13 100           // CHANGE THIS LATER
#define KYUREM_FLAG 100        // CHANGE THIS LATER
#define ROUTE_23 100           // CHANGE THIS LATER
extern "C" int SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u32 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)
extern "C"
{

#pragma region LimitedTMSupport
    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------ More Shop Checks for Limited TMs ----------------------------------
        --------------------------------------------------------------------------------------------------

    */
    // void THUMB_BRANCH_sub_21AD5A0(void *a1, int a2, int a3)
    // {
    //     ShopUIWork *v4;          // r5
    //     int result;              // r0
    //     unsigned int BlockWidth; // r6
    //     GFLBitmap *Bitmap;       // r0
    //     u32 Width;               // r7
    //     GFLBitmap *v9;           // r0
    //     unsigned int v10;        // r6
    //     GFLBitmap *v11;          // r0
    //     u32 v12;                 // r7
    //     GFLBitmap *v13;          // r0

    //     v4 = sub_2026548(a1);
    //     result = -2;
    //     if (a2 != -2)
    //     {
    //         if (BagSave_CheckAmount(v4->Bag, v4->ItemInfo[a2].TagID, 1) && !PML_ItemIsTMHM(v4->ItemInfo[a2].TagID))
    //         {
    //             BlockWidth = GFL_FontGetBlockWidth(v4->NoneDispStr, v4->m_Font, 0);
    //             Bitmap = BmpWin_GetBitmap((BmpWin *)v4->dword194);
    //             Width = GFL_BitmapGetWidth(Bitmap);
    //             v9 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
    //             sub_21AD4CC(v4->dword1D8, v9, Width - BlockWidth, a3, v4->NoneDispStr, v4->m_Font, 12704);
    //         }
    //         else
    //         {
    //             WordSetNumber(v4->WordSet, 1, v4->ItemInfo[a2].Price, 5u, 1u, 1);
    //             GFL_WordSetFormatStrbuf(v4->WordSet, v4->StrBuff, v4->BalanceDispStr);
    //             v10 = GFL_FontGetBlockWidth(v4->StrBuff, v4->m_Font, 0);
    //             v11 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
    //             v12 = GFL_BitmapGetWidth(v11);
    //             v13 = BmpWin_GetBitmap((BmpWin *)v4->dword194);
    //             sub_21AD4CC(v4->dword1D8, v13, v12 - v10, a3, v4->StrBuff, v4->m_Font, 12704);
    //         }
    //     }
    // }

    /*

       --------------------------------------------------------------------------------------------------
       -------------------- FIX THE SHOP PURCHASING MECHANICS FOR LIMITED TMS ---------------------------
       --------------------------------------------------------------------------------------------------

   */

    extern u32 ShopUI_GetBalance(ShopUIWork *ui);
    extern u32 BagSave_CheckAvailItemSpace(BagSaveData *pItemBlk, u16 item_idx, u16 quantity, HeapID heapId);
    extern bool BagSave_GetItemCountByID(BagSaveData *bag, u16 itemId);
    extern void ShopUI_SetBuyConfirmMessage(ShopUIWork *shop);
    extern void ShopUI_SetStatusDialogue(ShopUIWork *shop, int msgId, int currencyItemID, int plural);
    extern u32 div32(u32 numerator, u32 denominator);

    // u32 THUMB_BRANCH_sub_21AC110(ShopUIWork *shop)
    // {
    //     u32 Balance;            // r6
    //     bool ItemCountByID;     // r7
    //     u32 result;             // r0
    //     u32 PurchasedItemPrice; // r0
    //     int v6;                 // r1
    //     unsigned int v7;        // r0

    //     Balance = ShopUI_GetBalance(shop);
    //     ItemCountByID = BagSave_GetItemCountByID(shop->Bag, shop->PurchasingItemID);
    //     if (BagSave_CheckAvailItemSpace(shop->Bag, shop->PurchasingItemID, 1u, shop->heapID))
    //     {
    //         PurchasedItemPrice = shop->PurchasedItemPrice;
    //         if (Balance >= PurchasedItemPrice)
    //         {
    //             if (Balance >= 2 * PurchasedItemPrice)
    //             {
    //                 if (shop->SoldItemClass == 2)
    //                 {
    //                     ShopUI_SetBuyConfirmMessage(shop);
    //                     shop->ShopUIState = 12;
    //                     result = 6;
    //                     shop->ABWaitNextState = 6;
    //                 }
    //                 else
    //                 {
    //                     ShopUI_SetStatusDialogue(shop, 4, shop->PurchasingItemID, 0);
    //                     shop->ShopUIState = 12;
    //                     shop->ABWaitNextState = 2;
    //                     v7 = div32(Balance, shop->PurchasedItemPrice); // Balance / shop->PurchasedItemPrice;
    //                     shop->PurchasingItemCount = v7;
    //                     if (v7 > 0x63)
    //                     {
    //                         shop->PurchasingItemCount = 99;
    //                     }
    //                     result = 999;
    //                     if (shop->PurchasingItemCount + ItemCountByID > result)
    //                     {
    //                         result = 999 - ItemCountByID;
    //                         shop->PurchasingItemCount = result;
    //                     }
    //                 }
    //             }
    //             else
    //             {
    //                 ShopUI_SetBuyConfirmMessage(shop);
    //                 shop->ShopUIState = 12;
    //                 result = 5;
    //                 shop->ABWaitNextState = 5;
    //             }
    //         }
    //         else
    //         {
    //             if (shop->Currency)
    //             {
    //                 v6 = 16;
    //             }
    //             else
    //             {
    //                 v6 = 3;
    //             }
    //             ShopUI_SetStatusDialogue(shop, v6, shop->PurchasingItemID, 0);
    //             shop->ShopUIState = 12;
    //             result = 4;
    //             shop->ABWaitNextState = 4;
    //         }
    //     }
    //     else
    //     {
    //         ShopUI_SetStatusDialogue(shop, 10, shop->PurchasingItemID, 0);
    //         shop->ShopUIState = 12;
    //         result = 4;
    //         shop->ABWaitNextState = 4;
    //     }
    //     return result;
    // }

    extern bool CheckGetPartyPokemon(void *env, int slot, PartyPkm **ppPkm);
    int THUMB_BRANCH_s0108_PokePartyGetMoveCount(void *vm, void *env)
    {
        u16 *dest;       // r7
        int partyIdx;    // r0
        u16 v6;          // r5
        int i;           // r4
        PartyPkm *ppPkm; // [sp+0h] [bp-18h] BYREF

        dest = ScriptReadVar(vm, env);
        partyIdx = ScriptReadAny(vm, env);
        v6 = 0;
        // k::Printf("Getting move count for party index %d\n", partyIdx);
        if (CheckGetPartyPokemon(env, partyIdx, &ppPkm))
        {
            // k::Printf("Found Pokemon species %d\n", PokeParty_GetParam(ppPkm, PF_Species, 0));
            for (i = 0; i < 4; ++i)
            {
                // k::Printf("Move %d ID is %d\n", i + 1, PokeParty_GetParam(ppPkm, (PkmField)(i + PF_Move1), 0));
                if (PokeParty_GetParam(ppPkm, (PkmField)(i + PF_Move1), 0))
                {
                    ++v6;
                }
            }
        }
        *dest = v6;
        return 0;
    }

#pragma endregion

#pragma region WildPokemonModifiers
    extern b32 EventWork_FlagGet(EventWorkSave *eventWork, int eventBitNum);

    int THUMB_BRANCH_SAFESTACK_TransformVsPokePartyBySeason(GameData *gameData, PokeParty *party, Season s)
    {
        int result;
        return result;
    }

    u32 GetIVSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16433);

        // // k::Printf("Current IV setting is %d\n", *lvl_cap_ptr);

        return *lvl_cap_ptr;
    }

    void improveIVs(PartyPkm *pPkm)
    {
        // Placeholder for potential future IV improvement logic
        int ivA;
        int ivB;
        int count;

        // k::Printf("Improving IVs for species %d\n", PokeParty_GetParam(pPkm, PF_Species, 0));
        while (count < 5)
        {
            // k::Printf("Rolling IVs for stat %d, current IVs are %d\n", count, PokeParty_GetParam(pPkm, (PkmField)(PF_IvHP + count), 0));
            ivA = GFL_RandomMT() >> 27;
            ivB = GFL_RandomMT() >> 27;
            if (ivA >= ivB)
            {
                PokeParty_SetParam(pPkm, (PkmField)(PF_IvHP + count), ivA);
            }
            else
            {
                PokeParty_SetParam(pPkm, (PkmField)(PF_IvHP + count), ivB);
            }
            count++;
        }
        PokeParty_RecalcStats(pPkm);
    }

    const u16 KyuremSplitBerserkZones[6] = {
        GIANT_CHASM, GIANT_CHASM_FOREST, GIANT_CHASM_CAVE, ROUTE_13, ROUTE_22, ROUTE_23};

    extern "C" int isKyuremEvent(EncountManager *mgr)
    {
        return false;
        // EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        // u16 *kyurem_ptr = EventWork_GetWkPtr(eventWork, KYUREM_FLAG);

        // if (*kyurem_ptr == 1){
        //     PlayerState *playerState = GameData_GetPlayerState(mgr->gameData);
        //     int zoneId = PlayerState_GetZoneID(playerState);

        //     return SEARCH_ARRAY(KyuremSplitBerserkZones, zoneId);
        // }
        // return 0;
    }

    struct GenPokeParam
    {
        HeapID HeapID;
        __int16 field_2;
        int Species;
        u32 Forme;
        u32 Level;
        int HeldItem;
        AbilLock AbilLock;
        GenderSet Gender;
        ShinyType ShinyType;
        u32 BallItemID;
        int HiddenAbility;
    };

    /*

        --------------------------------------------------------------------------------------------------
        --------------------- CREATING EGGS TO ADD TO THE PARTY WITH EVENTS ------------------------------
        --------------------------------------------------------------------------------------------------

    */
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
            improveIVs(v9);
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
                        changedIVs[random2] = 1;
                        PokeParty_SetParam(v9, ivs[random2], 31);
                        numOfPerfectIVs++;
                    }
                } while (numOfPerfectIVs < 3);
            }
            else
            {
            }

            if (WhiteListedPokemon[species] > 1)
            {
                int random2 = GFL_RandomLCAlt(1000u);

                if (random2 <= (25u * WhiteListedPokemon[species]))
                {
                    PokeParty_SetHiddenAbil(v9, species, Param);
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

    /*

        --------------------------------------------------------------------------------------------------
        ---------------------------------- CREATING WILD POKEMON -----------------------------------------
        --------------------------------------------------------------------------------------------------

    */

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

        /* Random Deerling Seasonal Form */
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

        // Unown Checks
        if (pkmData->Species == 201)
        {
            random = GFL_RandomLCAlt(23u);
            PokeParty_ChangeForme(pPkm, random);
        }

        /* IV Settings */
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
                    changedIVs[random2] = 1;
                    PokeParty_SetParam(pPkm, ivs[random2], 31);
                    numOfPerfectIVs++;
                }
            } while (numOfPerfectIVs < 3);
        }
        else
        {
        }

        PokeParty_SetDefaultMoves(pPkm);

        /* Potential Hidden Ability? */
        if (WhiteListedPokemon[pkmData->Species] > 1)
        {
            random2 = GFL_RandomLCAlt(1000u);

            if (random2 <= (25u * WhiteListedPokemon[pkmData->Species]))
            {
                PokeParty_SetHiddenAbil(pPkm, pkmData->Species, pkmData->Forme);
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

        // Kyurem Event Support
        if (isKyuremEvent(mgr))
        {
            random = GFL_RandomLCAlt(100u);
            HeldItem = 294;
            if (random <= 32u)
            {
                HeldItem = 294;
            }
            else if (random > 32u && random <= 64)
            {
                HeldItem = 254;
            }
            else if (random > 64u && random <= 96u)
            {
                HeldItem = 315;
            }
            else if (random > 96u && random <= 100u)
            {
                HeldItem = 314;
            }
            else
            {
                HeldItem = 294;
            }
            PokeParty_SetParam(pPkm, PF_Item, HeldItem);
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

    extern PartyPkm *GameData_MakeBoxPkm(GameData *gameData, GenPokeParam *param);

    int THUMB_BRANCH_SAFESTACK_addPkmToParty(GameData *gameData, GenPokeParam *param)
    {
        PokeParty *Party; // r6
        int Capacity;     // r5
        PartyPkm *BoxPkm; // r5
        _DWORD *Pokedex;  // r0

        Party = GameData_GetParty(gameData);
        Capacity = PokeParty_GetCapacity(Party);
        if (Capacity <= (int)PokeParty_GetPkmCount(Party))
        {
            return 0;
        }
        BoxPkm = GameData_MakeBoxPkm(gameData, param);
        improveIVs(BoxPkm);
        if (GetIVSetting() == 2)
        {
            PokeParty_SetParam(BoxPkm, PF_IvATK, 31);
            PokeParty_SetParam(BoxPkm, PF_IvDEF, 31);
            PokeParty_SetParam(BoxPkm, PF_IvHP, 31);
            PokeParty_SetParam(BoxPkm, PF_IvSPA, 31);
            PokeParty_SetParam(BoxPkm, PF_IvSPD, 31);
            PokeParty_SetParam(BoxPkm, PF_IvSPE, 31);
        }
        else if (GetIVSetting() == 1)
        {
            int numOfPerfectIVs = 0;
            int random2 = 0;
            PkmField ivs[6] = {PF_IvHP, PF_IvATK, PF_IvDEF, PF_IvSPA, PF_IvSPD, PF_IvSPE};
            int changedIVs[6] = {0, 0, 0, 0, 0, 0};
            do
            {
                random2 = GFL_RandomLCAlt(5u);
                if (changedIVs[random2] == 0)
                {
                    changedIVs[random2] = 1;
                    PokeParty_SetParam(BoxPkm, ivs[random2], 31);
                    numOfPerfectIVs++;
                }
            } while (numOfPerfectIVs < 3);
        }
        else
        {
        }
        PokeParty_AddPkm(Party, BoxPkm);
        Pokedex = (_DWORD *)GameData_GetPokedex(gameData);
        addPkmToDex(Pokedex, BoxPkm);
        GFL_HeapFree(BoxPkm);
        return 1;
    }

    extern void* Field_GetDayCare(void *field);
    extern PartyPkm* DayCare_GetPkm(void *dayCare, u8 slot);
    extern void setAbilityForForm(BoxPkm *pPkm, u16 species);

    // Checks if the Pokemon has an ability of a specified slot
    int THUMB_BRANCH_s00F4_DayCareCalcNewLevel(void *a1, void *a2)
    {
        u16 *Var; // r4
        u8 Any; // r6
        void *GameSystem; // r0
        void *Field; // r0
        void *DayCare; // r5
        PartyPkm *pkm;
        PersonalData *personal;
        u16 abil1; 
        u16 abil2;
        u16 hiddenAbil;
        u16 currentAbil;
        u16 species; 
        u8 forme;
        Var = ScriptReadVar(a1, a2);
        Any = ScriptReadAny(a1, a2);
        GameSystem = FieldScriptEnv_GetGameSystem(a2);
        Field = GSYS_GetField(GameSystem);
        DayCare = Field_GetDayCare(Field);
        pkm = DayCare_GetPkm(DayCare, Any);
        species = PokeParty_GetParam(pkm, PF_Species, 0);
        forme = PokeParty_GetParam(pkm, PF_Forme, 0);
        personal = PML_PersonalLoadBW2(species, 0);
        abil1 = PML_PersonalGetParam(personal, (PersonalField)(26));
        abil2 = PML_PersonalGetParam(personal, (PersonalField)(27));
        hiddenAbil = PML_PersonalGetParam(personal, (PersonalField)(28));
        currentAbil = PokeParty_GetParam(pkm, PF_Ability, 0);

        if (Any == 0){
            if (abil1 == currentAbil){
                *Var = 0;
            }
            else {
                *Var = abil1;
            }
        }
        else if (Any == 1){
            if (abil2 == currentAbil){
                *Var = 0;
            }
            else if (abil1 == abil2){
                *Var = 0;
            }
            else {
                *Var = abil2;
            }
        }
        else if (Any == 2){
            if (hiddenAbil == 0){
                *Var = 0;
            }
            else if (abil1 == hiddenAbil){
                *Var = 0;
            }
            else if (hiddenAbil == abil2){
                *Var = 0;
            }
            else if (currentAbil == hiddenAbil){
                *Var = 0;
            }
            else if (WhiteListedPokemon[species] < 2){
                *Var = 0;
            }
            else {
                *Var = hiddenAbil;
            }
        }
        else if (Any == 4){
            if (PokeParty_GetParam(pkm, PF_IsHiddenAbility, 0)){
                PokeParty_SetParam(pkm, PF_IsHiddenAbility, 0);
                setAbilityForForm(&pkm->Base, species);
                PokeParty_RecalcStats(pkm);
                *Var = PokeParty_GetParam(pkm, PF_Ability, 0);
            }
            currentAbil = PokeParty_GetParam(pkm, PF_Ability, 0);
            if (currentAbil != abil1){
                PokeParty_SetParam(pkm, PF_ContestCool, ((PokeParty_GetParam(pkm, PF_ContestCool, 0) == 0) ? 1 : 0));
                setAbilityForForm(&pkm->Base, species);
                PokeParty_RecalcStats(pkm);
                *Var = PokeParty_GetParam(pkm, PF_Ability, 0);
            }
        }
        else if (Any == 5){
            if (PokeParty_GetParam(pkm, PF_IsHiddenAbility, 0)){
                PokeParty_SetParam(pkm, PF_IsHiddenAbility, 0);
                setAbilityForForm(&pkm->Base, species);
                PokeParty_RecalcStats(pkm);
                *Var = PokeParty_GetParam(pkm, PF_Ability, 0);
            }
            currentAbil = PokeParty_GetParam(pkm, PF_Ability, 0);
            if (currentAbil != abil2){
                PokeParty_SetParam(pkm, PF_ContestCool, ((PokeParty_GetParam(pkm, PF_ContestCool, 0) == 0) ? 1 : 0));
                setAbilityForForm(&pkm->Base, species);
                PokeParty_RecalcStats(pkm);
                *Var = PokeParty_GetParam(pkm, PF_Ability, 0);
            }
        }
        else if (Any == 6){
            PokeParty_SetHiddenAbil(pkm, species, forme);
            PokeParty_RecalcStats(pkm);
            *Var = PokeParty_GetParam(pkm, PF_Ability, 0);
        }
        else if (Any == 7) {
            *Var = currentAbil;
        }    
        else if (Any == 8){
            *Var = PokeParty_GetParam(pkm, PF_Ability, 0); 
        }
        else {
            *Var = 0;
        }
        return 0;
    }


#pragma endregion

#pragma region Wild Battle Encounter Changes

    enum PlayerExState
    {
        FLD_PLAYER_EXSTATE_NONE = 0x0,
        FLD_PLAYER_EXSTATE_CYCLING = 0x1,
        FLD_PLAYER_EXSTATE_SURF = 0x2,
        FLD_PLAYER_EXSTATE_DIVE = 0x3,
    };
    struct WildEncSlot
    {
        u16 IdAndForme;
        u8 LvMin;
        u8 LvMax;
    };
    struct VecFx32
    {
        s32 x;
        s32 y;
        s32 z;
    };
    struct RailPosition
    {
        u16 ComponentID;
        u8 ComponentIsLine;
        u8 RailDirection;
        s16 PosSide;
        u16 PosFront;
    };
    struct PlayerState
    {
        u16 ZoneID;
        VecFx32 VecPos;
        RailPosition RailPos;
        u16 RotationAngle;
        u8 field_1A;
        u8 IsPosRail;
        u16 NowOBJCODE;
        __int16 field_1E;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int field_34;
        int field_38;
        int field_3C;
        PlayerExState ExState;
    };
    struct ToggledEncounters
    {
        u16 ZoneID;
        u16 flagToCheck;
        u8 enablingValue;
    };
    extern void FieldEncount_GenWildPokeParam(EncountManager *mgr, WildEncSlot *src, WildPokemonParam *dest);
    extern bool FieldEncount_CheckLevelRepelled(EncountManager *mgr, u32 level);
    extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
    extern PlayerState *GameData_GetPlayerState(GameData *gameData);
    extern int PlayerState_GetZoneID(PlayerState *a1);
    extern int GetLeaguePokeCenReturnLocationIdx();
    extern int GetReturnLocationIdx(GameData *a1);
    extern b32 EventWork_FlagGet(EventWorkSave *eventWork, int eventBitNum);
    extern void EventWork_FlagReset(EventWorkSave *eventWork, u32 flagId);
    extern u32 getBadgeCount(void *pTrainerCardData);
    extern void *getTrainerCardDataBlkAddress(void *pBaseBlk);
    extern bool isBadgeObtained(void *pTrainerCardData, int badgeNum);
    ToggledEncounters toggleEncounters[12] = {
        {613, 16451, 2}, // Cobalion Encounter Enabling
        {155, 16472, 2}, // Virizion Encounter Enabling

        /* STRANGE HOUSE ENCOUNTER DISABLING */
        {462, 16441, 1},
        {510, 16441, 1},
        {511, 16441, 1},
        {512, 16441, 1},
        {513, 16441, 1},
        {514, 16441, 1},
        {569, 16441, 1},
        {570, 16441, 1},
        {571, 16441, 1},
        {572, 16441, 1},
    };

    const u16 draydenSplitDisabledEncounterZones[7] = {
        308, 348, 309, 365, 367, 310, 368};

    // const u16 marlonSplitDisabledZones[4] = {
    //     515, 516, 240, 463};

    bool isEncounterDisabled(EncountManager *mgr)
    {
        PlayerState *playerState = GameData_GetPlayerState(mgr->gameData);
        int zoneId = PlayerState_GetZoneID(playerState);
        for (int i = 0; i < ARRAY_COUNT(toggleEncounters); i++)
        {
            if (zoneId == toggleEncounters[i].ZoneID)
            {
                EventWorkSave *eventWork = GameData_GetEventWork(mgr->gameData);
                u16 *flagValue = EventWork_GetWkPtr(eventWork, toggleEncounters[i].flagToCheck);
                if (*flagValue == toggleEncounters[i].enablingValue)
                {
                    // k::Printf("\nEncounters enabled! flag is %d, event flag = %d", toggleEncounters[i].flagToCheck, flagValue);
                    return false;
                }
                else
                {
                    // k::Printf("\nEncounters enabled flag is %d, event flag is = %d!", toggleEncounters[i].flagToCheck, flagValue);
                    return true;
                }
            }
        }
        int badgeCount = getBadgeCount(getTrainerCardDataBlkAddress(mgr->gameData));

        if (isBadgeObtained(getTrainerCardDataBlkAddress(mgr->gameData), 6) && SEARCH_ARRAY(draydenSplitDisabledEncounterZones, zoneId))
        {
            return true;
        }
        // if (isBadgeObtained(getTrainerCardDataBlkAddress(mgr->gameData), 7) && SEARCH_ARRAY(marlonSplitDisabledZones, zoneId))
        // {
        //     return true;
        // }
        return false;
    }

    int THUMB_BRANCH_SAFESTACK_FieldEncount_GenWildsCore(EncountManager *mgr, WildEncSlot *src, WildPokemonParam *dest)
    {
        int v4; // r4
        int v5; // r6

        v4 = 0;
        v5 = 0;

        if (isEncounterDisabled(mgr))
        {
            return 0;
        }
        if (mgr->EncountCount)
        {
            do
            {
                FieldEncount_GenWildPokeParam(mgr, src, &dest[v4]);
                if (!FieldEncount_CheckLevelRepelled(mgr, dest[v4].Level))
                {
                    ++v4;
                }
                ++v5;
            } while (v5 < mgr->EncountCount);
        }
        return v4;
    }

    bool THUMB_BRANCH_IsReturnLocationNonLeaguePokeCen(GameData *a1)
    {
        int LeaguePokeCenReturnLocationIdx; // r4

        // Clears a gauntlet in case you lose the battle.
        if (EventWork_FlagGet(GameData_GetEventWork(a1), 522))
        {
            EventWork_FlagReset(GameData_GetEventWork(a1), 523);
        }

        LeaguePokeCenReturnLocationIdx = GetLeaguePokeCenReturnLocationIdx();
        return LeaguePokeCenReturnLocationIdx != GetReturnLocationIdx(a1);
    }

    // int THUMB_BRANCH_s023F_CallPlaceNameDisp(int a1, void *a2)
    // {
    //     void *GameSystem; // r0
    //     void *Field; // r5
    //     void *PlaceName; // r4
    //     u16 PlayerStateZoneID; // r0

    //     GameSystem = FieldScriptEnv_GetGameSystem(a2);
    //     Field = GSYS_GetField(GameSystem);
    //     PlaceName = Field_GetPlaceName(Field);
    //     PlayerStateZoneID = Field_GetPlayerStateZoneID(Field);
    //     BeginForcePlaceNameDisp((int)PlaceName, PlayerStateZoneID);
    //     return 0;
    // }

#pragma endregion
#pragma region HMOverhaul

    enum PlayerMoveStatus
    {
        FLD_PLAYER_MVSTATUS_STAND = 0x0,
        FLD_PLAYER_MVSTATUS_MOVE = 0x1,
        FLD_PLAYER_MVSTATUS_TURN = 0x2,
    };
    enum PlayerActionStatus
    {
        FLD_PLAYER_ACTSTATUS_IDLE = 0x0,
        FLD_PLAYER_ACTSTATUS_BEGIN = 0x1,
        FLD_PLAYER_ACTSTATUS_PERFORMING = 0x2,
        FLD_PLAYER_ACTSTATUS_FINISHED = 0x3,
    };
    enum FieldInteractFlag
    {
        FLD_INTERACT_KEY_A_DOWN = 0x1,
        FLD_INTERACT_KEY_X_DOWN = 0x2,
        FLD_INTERACT_PLAYER_STEP_MARK = 0x4,
        FLD_INTERACT_PLAYER_STEP_BEGIN = 0x8,
        FLD_INTERACT_PLAYER_ACT_FINISHED = 0x10,
        FLD_INTERACT_PLAYER_MOVE_TURNING = 0x20,
        FLD_INTERACT_KEY_IN_MOVE_DIR = 0x40,
        FLD_INTERACT_KEY_Y_DOWN = 0x80,
        FLD_INTERACT_KEY_AXY_DOWN = 0x100,
        FLD_INTERACT_PLAYER_MOVE_VERTICAL_ONLY = 0x400,
        FLD_INTERACT_PLAYER_MOVE_NONE = 0x800,
    };
    enum Direction
    {
        DIR_UP = 0x0,
        DIR_DOWN = 0x1,
        DIR_LEFT = 0x2,
        DIR_RIGHT = 0x3,
        DIR_ANY = 0x8,
        DIR_NONE = 0x9
    };

    struct TileType
    {
        u16 Class;
        u16 Flags;
    };

    struct SpecialTileScript
    {
        b32 (*RecognitionFunc)(int);
        u16 Direction;
        u16 SCRID;
    };

    struct FieldEventCheckData
    {
        u32 FieldmapHeapID;
        void *m_GameSys;
        GameData *m_GameData;
        void *Entities;
        u16 ZoneID;
        void *Fieldmap;
        void *Player;
        int m_PlayerActionStatus;
        int m_PlayerMoveStatus;
        Direction PlayerDirection;
        u16 ReserveSCRID;
        u32 NewPressedKeys;
        u32 HeldKeys;
        u16 InputPlayerMoveDir;
        void *PlayerPos;
        TileType TileUnderPlayer;
        FieldInteractFlag Flags;
    };

    extern b32 GameData_IsForceSeasonSync(GameData *gameData);
    extern TileType FieldPlayer_GetTileTypeUnder(void *player);
    extern TileType FieldPlayer_GetTileTypeInDir(void *player, Direction dir);
    extern int GetTileClass(TileType result);
    extern int sub_2018C64(int a1);
    extern int CheckSurfHeightAllow(void *player, unsigned __int16 dir);
    extern int GameData_FindPartyPkmByMove(GameData *gameData, u16 move);
    extern b32 CheckCanInteractWaterfall(void *player, TileType tileUnder, TileType tileInDir);
    extern bool BagSave_GetItemCountByID(BagSaveData *bag, u16 itemId);
    SpecialTileScript *SPECIAL_TILE_SCRIPTS = (SpecialTileScript *)0x21CA878;
    typedef s32 fx32;
    extern PlayerExState FieldPlayer_GetExState(void *player);
    extern TileType FieldPlayer_GetTileTypeInDirEx(void *player, Direction dir, fx32 *pYPos);
    extern bool CheckSurfBeginTiles(TileType a1, u32 a2);
    u32 GetSurfSetting(FieldEventCheckData *wk)
    {
        BagSaveData *Bag;
        Bag = GameData_GetBag(wk->m_GameData);
        return (BagSave_GetItemCountByID(Bag, 424) != 0);
    }

    b32 THUMB_BRANCH_PML_MoveIsHM(u16 moveNum)
    {
        //   unsigned int i; // r3

        //   for ( i = 0; i < 6; i = (unsigned __int8)(i + 1) )
        //   {
        //     if ( moveNum == (unsigned __int16)TM_MOVE_LIST[i + 92] )
        //     {
        //       return 1;
        //     }
        //   }
        return 0;
    }

    int THUMB_BRANCH_SAFESTACK_CheckFieldEnvInteraction(FieldEventCheckData *wk)
    {
        int TileClass;                        // r6
        unsigned int i;                       // r4
        SpecialTileScript *specialTileScript; // r1
        int Direction;                        // r2
        TileType tileInDir;                   // [sp+0h] [bp-20h]
        TileType tileUnder;                   // [sp+4h] [bp-1Ch]
        if (GameData_IsForceSeasonSync(wk->m_GameData))
        {
            // k::Printf("\n===CheckFieldEnvInteraction===   Check 2");
            return 0xFFFF;
        }
        // k::Printf("\n===CheckFieldEnvInteraction===   Check 3");
        tileUnder = FieldPlayer_GetTileTypeUnder(wk->Player);
        tileInDir = FieldPlayer_GetTileTypeInDir(wk->Player, wk->PlayerDirection);
        TileClass = GetTileClass(tileInDir);
        // k::Printf("\n===CheckFieldEnvInteraction===   Check 4");
        for (i = 0; i < 0xD; ++i)
        {
            // k::Printf("\n===CheckFieldEnvInteraction===   Check 5A-%d", i);
            specialTileScript = &SPECIAL_TILE_SCRIPTS[i];
            Direction = specialTileScript->Direction;
            if ((wk->PlayerDirection == Direction || Direction == 9) && specialTileScript->RecognitionFunc(TileClass))
            {
                // k::Printf("\n===CheckFieldEnvInteraction===   Check 5B-%d", i);
                return SPECIAL_TILE_SCRIPTS[i].SCRID;
            }
        }
        // k::Printf("\n===CheckFieldEnvInteraction===   Check 6");
        if (!sub_2018C64(wk->ZoneID) || GameData_IsForceSeasonSync(wk->m_GameData))
        {
            // k::Printf("\n===CheckFieldEnvInteraction===   Check 7");
            return 0xFFFF;
        }
        if (CheckSurfHeightAllow(wk->Player, wk->PlayerDirection) &&
            GetSurfSetting(wk) && wk->ZoneID != 345
            // GameData_FindPartyPkmByMove(wk->m_GameData, MOVE057_SURF) != 6
        )
        {
            return 10002;
        }
        // k::Printf("\n===CheckFieldEnvInteraction===   Check 10");
        if (CheckCanInteractWaterfall(wk->Player, tileUnder, tileInDir))
        {
            // k::Printf("\n===CheckFieldEnvInteraction===   Check 11");
            return 10006;
        }
        // k::Printf("\n===CheckFieldEnvInteraction===   Check 12\n\n\n");
        return 0xFFFF;
    }

    extern void PokeParty_RecoverAll(PokeParty *pParty);
    extern b32 GameData_CheckPairFlag(GameData *gameData);

    int personalPokePartyHeal(PokeParty *pParty, u8 shouldHeal)
    {
        signed __int32 PkmCount; // r6
        int i;                   // r5
        PartyPkm *Pkm;           // r4
        u8 check;
        PkmCount = PokeParty_GetPkmCount(pParty);
        for (i = 0; i < PkmCount; ++i)
        {
            Pkm = PokeParty_GetPkm(pParty, i);
            if (PokeParty_GetParam(Pkm, PF_NowHP, 0) != 0)
            {
                if (shouldHeal)
                {
                    PokeParty_Recover(Pkm);
                }
                check = 1;
            }
        }
        return check;
    }
    extern void ClearFollowNpcData(void *result);
    extern void *GetFieldFollowerCfg(GameData *gameData);
    void THUMB_BRANCH_ShutdownFollowWork(GameData *gameData)
    {
        void *FieldFollowerCfg;   // r6
        EventWorkSave *EventWork; // r4

        FieldFollowerCfg = GetFieldFollowerCfg(gameData);
        EventWork = GameData_GetEventWork(gameData);
        k::Printf("\nWe are in the function to reset follow state.");
        if (GameData_CheckPairFlag(gameData))
        {
            k::Printf("\nWe have successfully reset the follower state EventWork is %d\n", EventWork_FlagGet(EventWork, 2406));
            EventWork_FlagReset(EventWork, 2406);
            k::Printf("\nWe have successfully reset the follower state. Eventwork 2406 is %d\n", EventWork_FlagGet(EventWork, 2406));
            *EventWork_GetWkPtr(EventWork, 16451) = 255;
            ClearFollowNpcData(FieldFollowerCfg);
        }
    }

    void THUMB_BRANCH_PokeParty_RecoverAll(PokeParty *pParty)
    {
        signed __int32 PkmCount; // r6
        int i;                   // r5
        PartyPkm *Pkm;           // r4
        if (GameData_CheckPairFlag(GAME_DATA) && EventWork_FlagGet(GameData_GetEventWork(GAME_DATA), 535))
        {
            if (!personalPokePartyHeal(pParty, 0))
            {
                PkmCount = PokeParty_GetPkmCount(pParty);
                for (i = 0; i < PkmCount; ++i)
                {
                    Pkm = PokeParty_GetPkm(pParty, i);
                    if (PokeParty_GetParam(Pkm, PF_IsSpeciesValid, 0))
                    {
                        PokeParty_Recover(Pkm);
                    }
                }
            }
        }
        else
        {
            PkmCount = PokeParty_GetPkmCount(pParty);
            for (i = 0; i < PkmCount; ++i)
            {
                Pkm = PokeParty_GetPkm(pParty, i);
                if (PokeParty_GetParam(Pkm, PF_IsSpeciesValid, 0))
                {
                    PokeParty_Recover(Pkm);
                }
            }
        }
    }

    // Our new party heal function that doesn't heal fainted pokemon.

    int THUMB_BRANCH_s0112_PokePartyGetEVTotal(void *vm, void *env)
    {
        u16 *Var;           // r6
        int Any;            // r0
        u16 v6;             // r4
        GameData *GameData; // r0
        PokeParty *Party;   // r0
        PartyPkm *ppPkm;    // [sp+0h] [bp-18h] BYREF

        Var = ScriptReadVar(vm, env);
        Any = ScriptReadAny(vm, env);

        GameData = FieldScriptEnv_GetGameData(env);
        Party = GameData_GetParty(GameData);
        if (!personalPokePartyHeal(Party, 1))
        {
            PokeParty_RecoverAll(Party);
        }
        *Var = v6;
        return 0;
    }
    enum FieldmapCtrlType
    {
        FLD_MAPCTRL_GRID = 0x0,
        FLD_MAPCTRL_RAIL = 0x1,
        FLD_MAPCTRL_HYBRID = 0x2,
    };
    struct EncData
    {
        u8 UserData[8];
        WildEncSlot Slots[56];
    };
    struct GPosXYZ
    {
        u16 X;
        s16 Y;
        u16 Z;
    };
    struct EncountState
    {
        GPosXYZ GPos;
        u8 EncountRateBlockCounter;
        u8 EncountRateStepIncrement;
        u32 EncountRateStepCounter;
        TileType TileTypeUnder;
        u16 EncountRate;
        u16 field_12;
        u32 field_14;
        u16 field_18;
        GPosXYZ RareEncountPos;
        u32 field_20;
        u32 field_24;
    };
    struct EncountSystem
    {
        void *m_Field;
        void *m_GameSystem;
        GameData *m_GameData;
        EncData *m_EncData;
        void *m_EffectEncountState;
    };
    extern EncountState *GameData_GetEncountState(GameData *a1);
    extern signed int EncSys_IsActive(EncountSystem *encsys);
    extern void *GetMapMatrixSystem(GameData *pBaseBlk);
    extern u16 Field_GetPlayerStateZoneID(void *field);
    extern void *Field_GetPlayer(void *field);
    extern void *FieldPlayer_GetActor(void *player);
    extern void CopyActorWPos(void *mmdl, VecFx32 *dest);
    extern bool RangeCheckChunkCoordinateWorld(void *a1, int a2, int a3);
    extern int GetZoneIDAtMatrixXZWorld(void *a1, fx32 x, fx32 z);
    extern FieldmapCtrlType Field_GetResolvedControllerTypeID(void *field);
    extern bool sub_21A24AC(EncountState *a1, int a2);
    extern u32 PassPower_ApplyExploringChance(u32 basePhenomenonChance);
    extern int positionShakingSpot(EncountSystem *encSys, int a2, u8 type);
    extern void sub_21A272C(void **a1, int a2);
    extern void setShakingSpotOff(EncountState *result);

    // extern u8* EventWork_GetFlagBytePtr(EventWorkSave *eventWork, u32 flagId);
    // extern _DWORD __ROR4__(_DWORD d, char c);
    // b32 THUMB_BRANCH_EventWork_FlagGet(EventWorkSave *eventWork, int eventBitNum)
    // {
    //     u8 *FlagBytePtr; // r0
    //     int v4;          // r1
    //     b32 result;      // r0

    //     FlagBytePtr = EventWork_GetFlagBytePtr(eventWork, eventBitNum);
    //     if (!FlagBytePtr)
    //     {
    //         k::Printf("\nthe EventBitNumber %d returns 0", eventBitNum);
    //         return 0;
    //     }
    //     v4 = *FlagBytePtr;
    //     result = 1;
    //     if ((v4 & (1 << ((eventBitNum < 0) + __ROR4__((eventBitNum << 29) - ((unsigned int)eventBitNum >> 31), 29)))) == 0)
    //     {
    //         k::Printf("\nthe EventBitNumber %d returns 0", eventBitNum);
    //         return 0;
    //     }
    //     k::Printf("\nthe EventBitNumber %d returns 1", eventBitNum);
    //     return result;
    // }

    bool isPhenoDisabled(EncountSystem *mgr)
    {
        PlayerState *playerState = GameData_GetPlayerState(mgr->m_GameData);
        int zoneId = PlayerState_GetZoneID(playerState);
        EventWorkSave *eventWork = GameData_GetEventWork(mgr->m_GameData);

        if (EventWork_FlagGet(eventWork, 2406) == 1)
        {
            k::Printf("\nPheno is disabled");
            return true;
        }
        for (int i = 0; i < ARRAY_COUNT(toggleEncounters); i++)
        {
            if (zoneId == toggleEncounters[i].ZoneID)
            {
                u32 flagValue = EventWork_FlagGet(eventWork, toggleEncounters[i].flagToCheck);
                if (flagValue == toggleEncounters[i].enablingValue)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
        int badgeCount = getBadgeCount(getTrainerCardDataBlkAddress(mgr->m_GameData));

        if (isBadgeObtained(getTrainerCardDataBlkAddress(mgr->m_GameData), 6) && SEARCH_ARRAY(draydenSplitDisabledEncounterZones, zoneId))
        {
            return true;
        }
        // if (isBadgeObtained(getTrainerCardDataBlkAddress(mgr->m_GameData), 7) && SEARCH_ARRAY(marlonSplitDisabledZones, zoneId))
        // {
        //     return true;
        // }
        return false;
    }

    void THUMB_BRANCH_SAFESTACK_UpdatePhenomenon(EncountSystem *encSys)
    {
        int v2;                          // r6
        _WORD *m_EffectEncountState;     // r7
        void *MapMatrixSystem;           // r4
        void *Player;                    // r0
        void *Actor;                     // r0
        int ZoneIDAtMatrixXZWorld;       // r0
        void *TrainerCardDataBlkAddress; // r0
        EncData *m_EncData;              // r1
        u32 v10;                         // r4
        EncountState *a1;                // [sp+0h] [bp-28h]
        int PlayerStateZoneID;           // [sp+4h] [bp-24h]
        VecFx32 dest;                    // [sp+8h] [bp-20h] BYREF

        v2 = 0;
        a1 = GameData_GetEncountState(encSys->m_GameData);
        if (EncSys_IsActive(encSys))
        {
            m_EffectEncountState = (unsigned short *)encSys->m_EffectEncountState;
            MapMatrixSystem = GetMapMatrixSystem(encSys->m_GameData);
            if (encSys->m_Field)
            {
                if (MapMatrixSystem)
                {
                    PlayerStateZoneID = Field_GetPlayerStateZoneID(encSys->m_Field);
                    Player = Field_GetPlayer(encSys->m_Field);
                    Actor = FieldPlayer_GetActor(Player);
                    CopyActorWPos(Actor, &dest);
                    if (RangeCheckChunkCoordinateWorld(MapMatrixSystem, dest.x, dest.z))
                    {
                        ZoneIDAtMatrixXZWorld = GetZoneIDAtMatrixXZWorld(MapMatrixSystem, dest.x, dest.z);
                        if (PlayerStateZoneID != 0xFFFF && ZoneIDAtMatrixXZWorld != 0xFFFF && PlayerStateZoneID == ZoneIDAtMatrixXZWorld)
                        {
                            TrainerCardDataBlkAddress = getTrainerCardDataBlkAddress(encSys->m_GameData);
                            if (isBadgeObtained(TrainerCardDataBlkAddress, 0) && !isPhenoDisabled(encSys) && Field_GetResolvedControllerTypeID(encSys->m_Field) == FLD_MAPCTRL_GRID)
                            {
                                m_EncData = encSys->m_EncData;
                                if (m_EncData->UserData[2])
                                {
                                    v2 = 1;
                                }
                                if (m_EncData->UserData[4] || m_EncData->UserData[6])
                                {
                                    v2 |= 2u;
                                }
                                if (v2 && (a1->field_24 & 0xF00) == 0 && sub_21A24AC(a1, (int)m_EffectEncountState))
                                {
                                    v10 = PassPower_ApplyExploringChance((unsigned __int16)m_EffectEncountState[733]);
                                    if (GFL_RandomLCAlt(1000u) < 300 * v10)
                                    {
                                        positionShakingSpot(encSys, (int)m_EffectEncountState, v2);
                                        if (m_EffectEncountState[2])
                                        {
                                            sub_21A272C((void **)&encSys->m_Field, (int)m_EffectEncountState);
                                        }
                                    }
                                    else
                                    {
                                        setShakingSpotOff(a1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

#pragma endregion
#pragma region SomeKindOfEncounterEffectController
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
    //
    // int THUMB_BRANCH_CheckOverridenTrainerBattleBG(int trClass, int defaultBgId)
    // {
    //     int v2; // r5
    //     v2 = 0xBD;
    //     v2 = 0x14;
    //     v2 = 0;
    //     if (trClass == 0xBD)
    //     {
    //         return 0x14;
    //     }
    //     if (trClass == 218)
    //     {
    //         return 4;
    //     }

    //     return defaultBgId;
    // }

    // struct EncEff
    // {
    //     void *EventData;
    //     void (*RenderFunc)(EncEff *);
    //     void *m_Field;
    //     u32 SubOverlayIDs[3];
    //     u32 SubOverlayCount;
    //     void *WorkArea;
    // };

    // struct SWAN_ALIGNED(4) GameEvent
    // {
    //     void *ReturnEvent;
    //     void *Callback;
    //     u32 EventState;
    //     void *EventData;
    //     void *m_GameSystem;
    // };

    // struct EncEffCtl
    // {
    //     GameEvent *(*EventCreateFunc)(void *, void *, int);
    //     void (*RenderFunc)(EncEff *);
    //     unsigned int OverlayID;
    //     unsigned int IsOutFadeWhite;
    //     unsigned int RequiredHeapSize;
    // };

    // EncEffCtl *ENC_EFFECT_CONTROLLERS = (EncEffCtl *)0x21D2620;

    // extern void GameEvent_ChainNext(void *currentEvent, void *event);
    // extern void EncEff_LoadSubOvl(void *encEff, u32 ovlId);
    // extern void *Field_GetGameSystem(void *field_info);
    // extern u32 GFL_HeapGetHighestAllocatableSize(HeapID heapId);
    // extern void *GameEvent_GetData(GameEvent *event);
    // extern GameData *GSYS_GetGameData(void *gsys);
    // extern GameEvent *GameEvent_Create(void *gsys, GameEvent *parent, void *callback, u32 dataSize);
    // extern void *GameData_GetFieldSoundSystem(GameData *gameData);
    // extern void *GSYS_GetPlayerState(void *gsys);
    // extern int EventBattleBGMPlay_Callback(int a1, _DWORD *a2, void *event);
    // extern int PlayerState_GetZoneID(void *a1);

    // void THUMB_BRANCH_EncEff_StartEvent(EncEff *encEff, GameEvent *parentEvent, int battleBGId)
    // {
    //     void *m_Field;    // r7
    //     int v6;           // r6
    //     int OverlayID;    // r1
    //     GameEvent *v8;    // r4
    //     void *GameSystem; // [sp+4h] [bp-1Ch]

    //     m_Field = encEff->m_Field;
    //     GameSystem = Field_GetGameSystem(m_Field);
    //     if (battleBGId >= 38)
    //     {
    //         battleBGId = 0;
    //     }
    //     if (GFL_HeapGetHighestAllocatableSize(HEAPID_FIELDMAP) < ENC_EFFECT_CONTROLLERS[battleBGId].RequiredHeapSize)
    //     {
    //         battleBGId = 7;
    //     }

    //     if (PlayerState_GetZoneID(GSYS_GetPlayerState(GameSystem)) == 613)
    //     {
    //         battleBGId = 35;
    //     }

    //     v6 = battleBGId;
    //     OverlayID = ENC_EFFECT_CONTROLLERS[battleBGId].OverlayID;
    //     if (OverlayID != -1)
    //     {
    //         EncEff_LoadSubOvl(encEff, OverlayID);
    //     }
    //     v8 = ENC_EFFECT_CONTROLLERS[battleBGId].EventCreateFunc(
    //         GameSystem,
    //         m_Field,
    //         ENC_EFFECT_CONTROLLERS[battleBGId].IsOutFadeWhite);
    //     GameEvent_ChainNext(parentEvent, v8);
    //     encEff->EventData = GameEvent_GetData(v8);
    //     encEff->RenderFunc = ENC_EFFECT_CONTROLLERS[v6].RenderFunc;
    // };
#pragma endregion

#pragma region WIPStuff

    /*

           --------------------------------------------------------------------------------------------------
           ---------------------------------- CREATING TRADE POKEMON -----------------------------------------
           --------------------------------------------------------------------------------------------------

       */

    void THUMB_BRANCH_EventFieldTrade_CreatePkm(GameData *gameData, HeapID heapId, PartyPkm *pkm, FieldTradePkm *tradePkm)
    {
        GenderSet Gender;        // r3
        u32 pid;                 // r0
        StrBuf *Name;            // r7
        u32 IvHP;                // r2
        u32 IvATK;               // r2
        u32 IvDEF;               // r2
        u32 IvSPE;               // r2
        u32 IvSPA;               // r2
        u32 IvSPD;               // r2
        u32 Nature;              // r2
        StrBuf *v17;             // r7
        u16 *GameDataPlayerInfo; // r0

        Gender = tradePkm->Gender;
        if (Gender == 255)
        {
            Gender = GENDER_EITHER;
        }
        pid = PML_GenPID(tradePkm->TIDSet, tradePkm->Species, tradePkm->Forme, Gender, tradePkm->abilLock, SHINY_PREVENT);
        PokeParty_CreatePkm(
            pkm,
            (MonsNo)(unsigned __int16)tradePkm->Species,
            tradePkm->Level,
            tradePkm->TIDSet,
            ABIL_0,
            0xFFFFFFFF,
            pid,
            0);
        PokeParty_SetParam(pkm, PF_Forme, tradePkm->Forme);
        EventFieldTrade_DebugLogPkm(pkm);
        Name = FieldTradeInput_LoadName(heapId, tradePkm->NicknameIndex);
        PokeParty_SetParam(pkm, PF_NicknameStrBuf, (u32)Name);
        GFL_StrBufFree(Name);

        if (WhiteListedPokemon[tradePkm->Species] > 1)
        {
            int random2 = GFL_RandomLCAlt(1000u);

            if (random2 <= (25u * WhiteListedPokemon[tradePkm->Species]))
            {
                PokeParty_SetHiddenAbil(pkm, tradePkm->Species, tradePkm->Forme);
            }
        }
        improveIVs(pkm);
        IvHP = tradePkm->IvHP;
        if (IvHP != 255)
        {
            PokeParty_SetParam(pkm, PF_IvHP, IvHP);
        }
        IvATK = tradePkm->IvATK;
        if (IvATK != 255)
        {
            PokeParty_SetParam(pkm, PF_IvATK, IvATK);
        }
        IvDEF = tradePkm->IvDEF;
        if (IvDEF != 255)
        {
            PokeParty_SetParam(pkm, PF_IvDEF, IvDEF);
        }
        IvSPE = tradePkm->IvSPE;
        if (IvSPE != 255)
        {
            PokeParty_SetParam(pkm, PF_IvSPE, IvSPE);
        }
        IvSPA = tradePkm->IvSPA;
        if (IvSPA != 255)
        {
            PokeParty_SetParam(pkm, PF_IvSPA, IvSPA);
        }
        IvSPD = tradePkm->IvSPD;
        if (IvSPD != 255)
        {
            PokeParty_SetParam(pkm, PF_IvSPD, IvSPD);
        }

        Nature = tradePkm->Nature;
        if (Nature != 255)
        {
            PokeParty_SetParam(pkm, PF_Nature, Nature);
        }

        if (GetIVSetting() == 2)
        {
            PokeParty_SetParam(pkm, PF_IvATK, 31);
            PokeParty_SetParam(pkm, PF_IvDEF, 31);
            PokeParty_SetParam(pkm, PF_IvHP, 31);
            PokeParty_SetParam(pkm, PF_IvSPA, 31);
            PokeParty_SetParam(pkm, PF_IvSPD, 31);
            PokeParty_SetParam(pkm, PF_IvSPE, 31);
        }
        else if (GetIVSetting() == 1)
        {
            int numOfPerfectIVs = 0;
            int random2 = 0;
            PkmField ivs[6] = {PF_IvHP, PF_IvATK, PF_IvDEF, PF_IvSPA, PF_IvSPD, PF_IvSPE};
            int changedIVs[6] = {0, 0, 0, 0, 0, 0};
            do
            {
                random2 = GFL_RandomLCAlt(5u);
                if (changedIVs[random2] == 0)
                {
                    changedIVs[random2] = 1;
                    PokeParty_SetParam(pkm, ivs[random2], 31);
                    numOfPerfectIVs++;
                }
            } while (numOfPerfectIVs < 3);
        }
        else
        {
        }

        PokeParty_SetParam(pkm, PF_ContestCool, tradePkm->ContestCool);
        PokeParty_SetParam(pkm, PF_ContestBeauty, tradePkm->ContestBeauty);
        PokeParty_SetParam(pkm, PF_ContestCute, tradePkm->ContestCute);
        PokeParty_SetParam(pkm, PF_ContestSmart, tradePkm->ContestSmart);
        PokeParty_SetParam(pkm, PF_ContestTough, tradePkm->ContestTough);
        PokeParty_SetParam(pkm, PF_Item, tradePkm->HeldItem);
        v17 = FieldTradeInput_LoadName(heapId, tradePkm->OTNameIndex);
        PokeParty_SetParam(pkm, PF_OTNameStrBuf, (u32)v17);
        GFL_StrBufFree(v17);
        PokeParty_SetParam(pkm, PF_TrGender, tradePkm->OTGender);
        PokeParty_SetParam(pkm, PF_Region, tradePkm->OTRegion);
        GameDataPlayerInfo = GetGameDataPlayerInfo(gameData);
        PokeParty_SetupMetData(pkm, PKM_OBTAIN_FIELD_TRADE, GameDataPlayerInfo, 30002u, heapId);
        PokeParty_SetParam(pkm, PF_Happiness, 70u);
        EventFieldTrade_DebugLogPkm(pkm);
        PokeParty_RecalcStats(pkm);
    }

    extern u32 getIDAsUInt(void *pTrainerInfo);
    extern PartyPkm *PokeParty_NewPkm(
        u16 species,
        u8 level,
        u32 idSet,
        AbilLock abil_num,
        u32 ivs,
        u32 pid,
        u32 abil_mask);
    extern int GetItemParam(u16 itemId, u16 itemField, HeapID heapId);
    extern int PML_ItemGetMonsBallID(u16 itemId);
    extern int ZoneData_GetPlaceNameID(u16 zoneId);
    extern int howManyTotalPokesAreInBoxes(void *boxAccessor);
    extern void *GameData_GetBoxSaveAccessor(GameData *gameData);
    extern int nullsub_28(void *result);
    extern b32 BoxSaveAccessor_InsertPkm(void *boxAccessor, BoxPkm *pkm);
    
    int THUMB_BRANCH_GameData_AddBoxPkm(GameData *gameData, GenPokeParam *param)
    {
        void *BoxSaveAccessor; // r6
        PartyPkm *partyPkm;    // r5
        BoxPkm *v7;            // r0
        void *Pokedex;         // r0

        BoxSaveAccessor = GameData_GetBoxSaveAccessor(gameData);
        if (howManyTotalPokesAreInBoxes(BoxSaveAccessor) >= 720)
        {
            return 0;
        }
        partyPkm = GameData_MakeBoxPkm(gameData, param);
        PokeParty_SetParam(partyPkm, PF_IsHiddenAbility, 0);
        setAbilityForForm(&partyPkm->Base, param->Species);
        if (param->HiddenAbility == SHINY_PREVENT)
        {
            improveIVs(partyPkm);
        }
        if (WhiteListedPokemon[param->Species] > 1)
        {
            int random2 = GFL_RandomLCAlt(1000u);

            if (random2 <= (25u * WhiteListedPokemon[param->Species]))
            {
                PokeParty_SetHiddenAbil(partyPkm, param->Species, param->Forme);
            }
        }
        if (GetIVSetting() == 2)
        {
            PokeParty_SetParam(partyPkm, PF_IvATK, 31);
            PokeParty_SetParam(partyPkm, PF_IvDEF, 31);
            PokeParty_SetParam(partyPkm, PF_IvHP, 31);
            PokeParty_SetParam(partyPkm, PF_IvSPA, 31);
            PokeParty_SetParam(partyPkm, PF_IvSPD, 31);
            PokeParty_SetParam(partyPkm, PF_IvSPE, 31);
        }
        else if (GetIVSetting() == 1)
        {
            int numOfPerfectIVs = 0;
            int random2 = 0;
            PkmField ivs[6] = {PF_IvHP, PF_IvATK, PF_IvDEF, PF_IvSPA, PF_IvSPD, PF_IvSPE};
            int changedIVs[6] = {0, 0, 0, 0, 0, 0};
            do
            {
                random2 = GFL_RandomLCAlt(5u);
                if (changedIVs[random2] == 0)
                {
                    changedIVs[random2] = 1;
                    PokeParty_SetParam(partyPkm, ivs[random2], 31);
                    numOfPerfectIVs++;
                }
            } while (numOfPerfectIVs < 3);
        }
        else
        {
        }
        PokeParty_RecalcStats(partyPkm);

        v7 = (BoxPkm *)nullsub_28(partyPkm);
        BoxSaveAccessor_InsertPkm(BoxSaveAccessor, v7);
        Pokedex = GameData_GetPokedex(gameData);
        addPkmToDex((unsigned int *)Pokedex, partyPkm);
        GFL_HeapFree(partyPkm);
        return 1;
    }

    // PartyPkm *THUMB_BRANCH_SAFESTACK_GameData_MakeBoxPkm(GameData *gameData, GenPokeParam *param)
    // {
    //     u16 *GameDataPlayerInfo;  // r7
    //     u16 *v5;                  // r0
    //     unsigned int IDAsUInt;    // r4
    //     u32 v7;                   // r0
    //     PartyPkm *pkm;            // r4
    //     int MonsBallID;           // r0
    //     PlayerState *PlayerState; // r0
    //     u16 ZoneID;               // r0
    //     u16 PlaceNameID;          // r0
    //     k::Printf("\nCrash Check #1: Species %d\n", param->Species);
    //     GameDataPlayerInfo = GetGameDataPlayerInfo(gameData);
    //      k::Printf("\nCrash Check #2: Species %d\n", param->Species);
    //     v5 = GetGameDataPlayerInfo(gameData);
    //      k::Printf("\nCrash Check #3: Species %d\n", param->Species);
    //     IDAsUInt = getIDAsUInt(v5);
    //      k::Printf("\nCrash Check #4: Species %d\n", param->Species);
    //     v7 = PML_GenPID(IDAsUInt, param->Species, param->Forme, param->Gender, param->AbilLock, param->ShinyType);
    //      k::Printf("\nCrash Check #5: Species %d\n", param->Species);

    //      PokeParty_CreatePkm(
    //         pkm,
    //         (MonsNo)(unsigned __int16)param->Species,
    //         param->Level,
    //         IDAsUInt,
    //         ABIL_0,
    //         0xFFFFFFFF,
    //         v7,
    //         0);
    //     // pkm = PokeParty_NewPkm(param->Species, param->Level, IDAsUInt, ABIL_0, 0xFFFFFFFF, v7, 0);
    //     k::Printf("\nCrash Check #6: Species %d\nability = %d,\nhiddenability =%d",PokeParty_GetParam(pkm, PF_Species, 0), PokeParty_GetParam(pkm, PF_Ability, 0), PokeParty_GetParam(pkm, PF_IsHiddenAbility, 0));
    //     PokeParty_ChangeForme(pkm, (unsigned __int16)param->Forme);
    //     PokeParty_SetParam(pkm, PF_Item, param->HeldItem);
    //      k::Printf("\nCrash Check #7: Species %d\n", param->Species);
    //     if (param->HiddenAbility)
    //     {
    //         PokeParty_SetHiddenAbil(pkm, param->Species, param->Forme);
    //     }
    //     if (GetItemParam(param->BallItemID, 0xF, param->HeapID) == 4)
    //     {
    //         MonsBallID = PML_ItemGetMonsBallID(param->BallItemID);
    //         PokeParty_SetParam(pkm, PF_Pokeball, MonsBallID);
    //     }
    //      k::Printf("\nCrash Check #8: Species %d\n", param->Species);
    //     if (WhiteListedPokemon[param->Species] == 1)
    //     {
    //         int random2 = GFL_RandomLCAlt(100u);

    //         if (random2 <= 10u)
    //         {
    //             PokeParty_SetHiddenAbil(pkm, param->Species, param->Forme);
    //         }
    //     }
    //      k::Printf("\nCrash Check #9: Species %d\n", param->Species);
    //     if (GetIVSetting() == 2)
    //     {
    //         PokeParty_SetParam(pkm, PF_IvATK, 31);
    //         PokeParty_SetParam(pkm, PF_IvDEF, 31);
    //         PokeParty_SetParam(pkm, PF_IvHP, 31);
    //         PokeParty_SetParam(pkm, PF_IvSPA, 31);
    //         PokeParty_SetParam(pkm, PF_IvSPD, 31);
    //         PokeParty_SetParam(pkm, PF_IvSPE, 31);
    //     }
    //     else if (GetIVSetting() == 1)
    //     {
    //         int numOfPerfectIVs = 0;
    //         int random2 = 0;
    //         PkmField ivs[6] = {PF_IvHP, PF_IvATK, PF_IvDEF, PF_IvSPA, PF_IvSPD, PF_IvSPE};
    //         int changedIVs[6] = {0, 0, 0, 0, 0, 0};
    //         do
    //         {
    //             random2 = GFL_RandomLCAlt(5u);
    //             if (changedIVs[random2] == 0)
    //             {
    //                 changedIVs[random2] = 1;
    //                 PokeParty_SetParam(pkm, ivs[random2], 31);
    //                 numOfPerfectIVs++;
    //             }
    //         } while (numOfPerfectIVs < 3);
    //     }
    //     else
    //     {
    //     }

    //     k::Printf("\nMade Box Pkm for species %d\n", param->Species);

    //     PlayerState = GameData_GetPlayerState(gameData);

    //     k::Printf("\nCrash Check #10: Species %d\n", param->Species);

    //     ZoneID = PlayerState_GetZoneID(PlayerState);

    //     k::Printf("\nCrash Check #11: Species %d\n", param->Species);

    //     PlaceNameID = ZoneData_GetPlaceNameID(ZoneID);

    //     k::Printf("\nCrash Check #12: Species %d\n", param->Species);

    //     PokeParty_SetupMetData(pkm, PKM_OBTAIN_CAPTURE, GameDataPlayerInfo, PlaceNameID, param->HeapID);

    //     k::Printf("\nCrash Check #13: Species %d\n", param->Species);

    //     PokeParty_RecalcStats(pkm);

    //     k::Printf("\nCrash Check #14: Species %d\n", param->Species);

    //     return pkm;
    // }

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
    //
    //         if (random2 <= 45u)
    //         {
    //
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
    //
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
    // enum BattleStyle
    // {
    //     BTL_STYLE_SINGLE = 0x0,
    //     BTL_STYLE_DOUBLE = 0x1,
    //     BTL_STYLE_TRIPLE = 0x2,
    //     BTL_STYLE_ROTATION = 0x3,
    // };
    // struct SWAN_ALIGNED(2) BattleFieldStatus
    // {
    //     u32 BattleBGID;
    //     _DWORD BattlePedestalID;
    //     _BYTE BtlWeather;
    //     u8 Season;
    //     u16 ZoneID;
    //     u8 Hour;
    //     u8 Minute;
    //     char field_E;
    //     char field_F;
    // };
    // struct TrainerBattleSetup
    // {
    //     _DWORD TrID;
    //     _DWORD TrClass;
    //     _DWORD TrAIBits;
    //     u16 TrItems[4];
    //     StrBuf *TrainerName;
    //     __int16 field_18[4];
    //     __int16 field_20[4];
    // };

    // enum BattleResult
    // {
    //     BTL_RESULT_DEFEAT = 0x0,
    //     BTL_RESULT_VICTORY = 0x1,
    //     BTL_RESULT_DRAW = 0x2,
    //     BTL_RESULT_FLEE = 0x3,
    //     BTL_RESULT_FLEE_FOE = 0x4,
    //     BTL_RESULT_CAPTURE = 0x5,
    //     BTL_RESULT_6 = 0x6,
    // };

    // struct SWAN_ALIGNED(4) BtlSetup
    // {
    //     u32 BtlType;
    //     BattleStyle BtlStyle;
    //     BattleFieldStatus m_FieldStatus;
    //     u16 BattleBGMID;
    //     __int16 WinBGMID;
    //     int field_1C;
    //     char field_20;
    //     char field_21;
    //     char field_22;
    //     char field_23;
    //     PokeParty *Parties[4];
    //     int m_PlayerInfo;
    //     int field_38;
    //     int field_3C;
    //     int field_40;
    //     int field_44;
    //     TrainerBattleSetup *TrainerSetups[4];
    //     int field_58;
    //     int field_5C;
    //     int field_60;
    //     int field_64;
    //     int field_68;
    //     int field_6C;
    //     int field_70;
    //     int m_TrainerData;
    //     int m_ItemWork;
    //     int field_7C;
    //     int m_Dex;
    //     int m_RecordData;
    //     int field_88;
    //     int field_8C;
    //     int field_90;
    //     char field_94;
    //     char field_95;
    //     char field_96;
    //     char field_97;
    //     char BadgeCount;
    //     char field_99;
    //     char field_9A;
    //     char field_9B;
    //     int field_9C;
    //     __int16 field_A0;
    //     __int16 field_A2;
    //     int field_A4;
    //     BattleResult BattleResult;
    //     char CapturedPkmIdx;
    //     char field_AD;
    //     __int16 field_AE;
    //     void *field_B0;
    //     int field_B4;
    //     int field_B8;
    //     int field_BC;
    //     int field_C0;
    //     int field_C4;
    //     int field_C8;
    //     int field_CC;
    //     u16 HPSum;
    //     u8 CurrentTurn;
    //     u8 SwitchCount;
    //     u8 NoEffectHits;
    //     u8 SuperEffectiveHits;
    //     u8 NotVeryEffectiveHits;
    //     u8 OpponentNoEffectHits;
    //     u8 OpponentNotVeryEffectiveHits;
    //     u8 BattlesWon;
    //     u8 OpponentFainted;
    //     u8 AllyFainted;
    //     u8 UniqueMovesUsed;
    //     char field_DD;
    //     char field_DE;
    //     char field_DF;
    //     int field_E0;
    //     int field_E4;
    //     int field_E8;
    //     int field_EC;
    //     int field_F0;
    //     int field_F4;
    //     int field_F8;
    //     int field_FC;
    //     int field_100;
    //     int field_104;
    //     int field_108;
    //     int field_10C;
    //     int field_110;
    //     int field_114;
    //     int field_118;
    //     int field_11C;
    //     int field_120;
    //     int field_124;
    //     int field_128;
    //     int field_12C;
    //     int field_130;
    //     int field_134;
    //     int field_138;
    //     u8 KeySystemLevelAdjust;
    //     char field_13D;
    //     char field_13E;
    //     char field_13F;
    //     int field_140;
    //     int field_144;
    //     int field_148;
    // };

    // struct SWAN_ALIGNED(4) EventBattleCall
    // {
    //     void *GameSys;
    //     GameData *GameData;
    //     BtlSetup *BtlSetup;
    //     _BYTE gapC[8];
    //     b32 HasOwnExitHandler;
    //     b32 NoAutoDefeat;
    //     u32 IsTrialHouseBattle;
    //     int RetainBtlSetupOnExit;
    //     u32 EncEffID;
    //     u32 Flags;
    // };

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
    //     // k::Printf("\nThe battle id is %d\n", btlSetup->TrainerSetups[1]->TrID);

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
#pragma endregion
}

#pragma region NewScriptCommands

extern "C" bool BagSave_AddItem(BagSaveData *bag, u16 itemId, u16 quantity, HeapID heapId);
extern "C" u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);

extern "C" int RemoteItems(void *vm, void *env)
{
    GameData *gameData;
    PokeParty *party;
    PartyPkm *pkm;
    u8 pokeCount;
    HeapID heap = FieldScriptEnv_GetHeapID(env);
    gameData = FieldScriptEnv_GetGameData(env);
    party = GameData_GetParty(gameData);
    pokeCount = PokeParty_GetPkmCount(party);
    for (int i = 0; i < pokeCount; i++)
    {
        pkm = PokeParty_GetPkm(party, i);

        if (PokeParty_GetParam(pkm, PF_Item, 0))
        {
            BagSave_AddItem(GameData_GetBag(gameData), PokeParty_GetParam(pkm, PF_Item, 0), 1, heap);
            PokeParty_SetParam(pkm, PF_Item, 0);
        }
    }
    return 0;
}

extern "C" int EdgeExp(void *vm, void *env)
{
    GameData *gameData;
    PokeParty *party;
    PartyPkm *pkm;
    u8 pokeCount;
    int species;
    int form;
    int level;
    u32 PkmLvExp;
    gameData = FieldScriptEnv_GetGameData(env);
    party = GameData_GetParty(gameData);
    pokeCount = PokeParty_GetPkmCount(party);

    for (int i = 0; i < pokeCount; i++)
    {
        pkm = PokeParty_GetPkm(party, i);
        level = PokeParty_GetParam(pkm, PF_Level, 0);
        species = PokeParty_GetParam(pkm, PF_Species, 0);
        form = PokeParty_GetParam(pkm, PF_Forme, 0);
        PkmLvExp = PML_UtilGetPkmLvExp(species, form, (level + 1)) - 1; // Gets the EXp needed to be current level + 1
        PokeParty_SetParam(pkm, PF_Experience, PkmLvExp);
        PokeParty_RecalcStats(pkm);
    }
    return 0;
}
// Replaces 133
extern "C" void *FULL_COPY_12_0x0216BA44 = (void *)RemoteItems;
// Replaces 135
extern "C" void *FULL_COPY_12_0x0216BA4C = (void *)EdgeExp;
// Replaces 00 in the EV_CMD_PERM array
extern "C" u8 FULL_COPY_EVCMD_PERM_TABLE_0x132 = 7;
extern "C" u8 FULL_COPY_EVCMD_PERM_TABLE_0x134 = 7;

#pragma endregion