

#include "codeinjection_battlefield.h"
#include "kPrint.h"
#include "settings.h"
#include "swantypes.h"

extern "C" int BattleMon_CanBattle(BattleMon *a1);
extern "C" int sub_219C424(MainModule *a1, int a2);
extern "C" unsigned int BattleMon_IsIllusionEnabled(BattleMon *a1);
extern "C" PartyPkm *BattleMon_GetViewSrcData(BattleMon *a1);
extern "C" void BattleMon_SetIllusion(BattleMon *result, PartyPkm *a2);
extern "C" void BattleMon_RemoveIllusion(BattleMon *result);
extern "C" PartyPkm *BattleMon_GetSrcData(BattleMon *a1);
// extern "C" unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4, int flag);
extern "C" int MainModule_BattlePosToClientID(MainModule *a1, int a2);
extern "C" BattleMon *SwitchAI_DetermineOpponent(void *a1, __int16 a2);
extern "C" unsigned int MainModule_GetClientPokePos(MainModule *a1, int clientID, int partyIndex);
// extern "C" BattleMon *PokeCon_GetBattleMon(void *a1, int a2);
extern "C" int SwitchAI_CheckReserve(BtlClientWk *a1, int a2);
extern "C" int GetNumBattleReadyPartyMons(BtlClientWk *a1, u8 *a2);
extern "C" int MainModule_PokeIDToClientID(int a1);

int illusionMonId;

extern "C" unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
{
    unsigned int v5;                     // r5
    BattleMon *MonData;                  // r6
    int ID;                              // r4
    unsigned int BasePower;              // r4
    unsigned int TypeEffectivenessVsMon; // r0
    unsigned int v10;                    // r0
    unsigned int result;                 // r0
    unsigned int j;                      // r5
    unsigned int k;                      // r6
    unsigned int v14;                    // r1
    unsigned int v15;                    // r0
    unsigned int v18;
    int randomvalue;
    u8 v16;                 // r1
    int Type;               // [sp+8h] [bp-38h]
    unsigned int MoveCount; // [sp+Ch] [bp-34h]
    unsigned int i;         // [sp+10h] [bp-30h]
    int PokeType;           // [sp+14h] [bp-2Ch]
    __int16 v23[6];         // [sp+1Ch] [bp-24h]
    BattleMon *v24;         // [sp+28h] [bp-18h]

    v24 = a4;
    PokeType = BattleMon_GetPokeType(a4);
    for (i = 0; i < a3; i = (i + 1))
    {
        v5 = 0;
        v23[i] = 0;
        MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
        if (!BattleMon_IsFainted(MonData))
        {
            MoveCount = BattleMon_GetMoveCount(MonData);
            if (MoveCount)
            {
                do
                {
                    if (Move_GetPP(MonData, v5))
                    {
                        ID = Move_GetID(MonData, v5);
                        if (PML_MoveIsDamaging(ID))
                        {
                            Type = PML_MoveGetType(ID);
                            BasePower = PML_MoveGetBasePower(ID);
                            TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);
                            if (TypeEffectivenessVsMon <= 5)
                            {

                                switch (TypeEffectivenessVsMon)
                                {
                                case 0:
                                    BasePower = 0;
                                    break;
                                case 1:
                                    v10 = BasePower << 14;
                                    goto LABEL_11;
                                case 2:
                                    v10 = BasePower << 15;
                                    goto LABEL_11;
                                case 4:
                                    v10 = BasePower << 17;
                                    goto LABEL_11;
                                case 5:
                                    v10 = BasePower << 18;
                                LABEL_11:
                                    BasePower = HIWORD(v10);
                                    break;
                                default:
                                    v10 = BasePower << 16;
                                    BasePower = HIWORD(v10);
                                    break;
                                }
                            }

                            if (v23[i] < BasePower)
                            {
                                v23[i] = BasePower;
                            }
                        }
                    }
                    v5 = (v5 + 1);
                } while (v5 < MoveCount);
            }
        }
    }
    result = a3;

    for (j = 0; j < a3; result = a3)
    {
        for (k = (j + 1); k < a3; k = (k + 1))
        {
            v14 = v23[k];
            v15 = v23[j];
            if (v15 < v14)
            {
                v23[j] = v14;
                v23[k] = v15;
                v16 = a2[j];
                a2[j] = a2[k];
                a2[k] = v16;
            }
        }
        j = (unsigned __int8)(j + 1);
    }

    if (a3 > 1)
    {
        k::Printf("\nWe are checking the first slot to see if it's an illusion mon and...");
        if (BattleMon_GetValue(BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[0]), VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION){
            illusionMonId = a2[1];
        } else {
            illusionMonId = a2[0];
        }
        // k::Printf("We are setting the illusion Mon ID here");
    }
    else
    {
        illusionMonId = a2[0];
    }

    return result;
}

void copyArray(u8 *arr, u8 *arrCopy)
{
    for (int i = 0; i < 28; i++)
    {
        arrCopy[i] = arr[i];
    }
}

extern "C" const void * sys_memcpy(const void *src, void *dst, u32 size);
extern "C" unsigned int THUMB_BRANCH_SAFESTACK_PickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
{
    unsigned int v5;                     // r5
    BattleMon *MonData;                  // r6
    int ID;                              // r4
    unsigned int BasePower;              // r4
    unsigned int TypeEffectivenessVsMon; // r0
    unsigned int v10;                    // r0
    unsigned int result;                 // r0
    unsigned int j;                      // r5
    unsigned int k;                      // r6
    unsigned int v14;                    // r1
    unsigned int v15;                    // r0
    unsigned int v18;
    int randomvalue;
    u8 v16;                 // r1
    int Type;               // [sp+8h] [bp-38h]
    unsigned int MoveCount; // [sp+Ch] [bp-34h]
    unsigned int i;         // [sp+10h] [bp-30h]
    int PokeType;           // [sp+14h] [bp-2Ch]
    __int16 v23[6];         // [sp+1Ch] [bp-24h]
    BattleMon *v24;         // [sp+28h] [bp-18h]

    v24 = a4;
    PokeType = BattleMon_GetPokeType(a4);

    // k::Printf("\n\n=====WE ARE IN THE PICKBESTMONTOSWITCHINTO FUNCTION======\n");

    u8 *monsCopy;
    sys_memcpy(a2, monsCopy, sizeof(a2));

    int personalResult = PersonalPickBestMonToSwitchInto(a1, monsCopy, a3, a4);
    personalResult = monsCopy[0];

    for (i = 0; i < a3; i = (i + 1))
    {
        v5 = 0;
        v23[i] = 0;
        MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
        if (!BattleMon_IsFainted(MonData))
        {
            // k::Printf("\n\nWe are checking %d with ID %d and index %d", MonData->Species, MonData->ID, i);
            MoveCount = BattleMon_GetMoveCount(MonData);
            if (MoveCount)
            {
                do
                {
                    if (Move_GetPP(MonData, v5))
                    {
                        ID = Move_GetID(MonData, v5);
                        if (PML_MoveIsDamaging(ID))
                        {
                            Type = PML_MoveGetType(ID);
                            BasePower = PML_MoveGetBasePower(ID);
                            TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);
                            if (TypeEffectivenessVsMon <= 5)
                            {

                                switch (TypeEffectivenessVsMon)
                                {
                                case 0:
                                    BasePower = 0;
                                    break;
                                case 1:
                                    v10 = BasePower << 14;
                                    goto LABEL_11;
                                case 2:
                                    v10 = BasePower << 15;
                                    goto LABEL_11;
                                case 4:
                                    v10 = BasePower << 17;
                                    goto LABEL_11;
                                case 5:
                                    v10 = BasePower << 18;
                                LABEL_11:
                                    BasePower = HIWORD(v10);
                                    break;
                                default:
                                    v10 = BasePower << 16;
                                    BasePower = HIWORD(v10);
                                    break;
                                }
                            }

                            if (v23[i] < BasePower)
                            {
                                v23[i] = BasePower;
                            }
                        }
                    }
                    v5 = (v5 + 1);
                } while (v5 < MoveCount);
            }
            if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
            {
                // k::Printf("\nThe actual best switch in is %d\n",  BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[actualBest])->Species);

                // k::Printf("\nFor Pokemon %d, their highest base power move is %d.\nWithout this pokemon of id=%d the switch ai would return %d.",
                //     BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[actualBest])->Species, v23[i], i, actualBest);
                k::Printf("\nThe actual best switch in is %d with id %d while the current Pokemon we are assessing is %d with id %d\n", BattleParty_GetMonData(BattleClient_GetActParty(a1), personalResult)->Species, personalResult, MonData->Species, a2[i]);
                if (personalResult == a2[i])
                {
                    k::Printf("\nThe Illusion Pokemon is the best switch in");
                    if (BattleRandom(100) > 50)
                    {
                        k::Printf(" but is going dodge their duties\n");

                        BasePower = BasePower >> 1;
                        k::Printf("\nBasePower is now %d", BasePower);
                    }
                }
                else if (personalResult != a2[i] && BasePower >= 80)
                {
                    k::Printf("\nThe Illusion Pokemon is not the best switch in");
                    if (BattleRandom(100) > 10)
                    {
                        k::Printf(" but is going to come in anyways\n");
                        BasePower = BasePower << 1;
                    }
                }
                else
                {
                }
                v23[i] = BasePower;
            }
        }
    }
    result = a3;

    for (j = 0; j < a3; result = a3)
    {
        for (k = (j + 1); k < a3; k = (k + 1))
        {
            v14 = v23[k];
            v15 = v23[j];
            if (v15 < v14)
            {
                v23[j] = v14;
                v23[k] = v15;
                v16 = a2[j];
                a2[j] = a2[k];
                a2[k] = v16;
            }
        }
        j = (unsigned __int8)(j + 1);
    }
    return result;
}

extern "C" void THUMB_BRANCH_MainModule_SetIllusionForParty(MainModule *a1, BattleParty *a2, int a3)
{
    int i;                          // r6
    int NumBattlePositionsOfClient; // r4
    int j;                          // r0
    BattleMon *v8;                  // r7
    PartyPkm *SrcData;              // r0
    int v10;                        // r4

    for (i = a2->memberCount - 1; i > 0; --i)
    {
        if (BattleMon_CanBattle(a2->mons[i]))
        {
            break;
        }
    }
    if (BtlSetup_GetBattleStyle(a1) == BTL_STYLE_ROTATION)
    {
        NumBattlePositionsOfClient = 3;
    }
    else
    {
        NumBattlePositionsOfClient = sub_219C424(a1, a3);
    }
    for (j = a2->memberCount; NumBattlePositionsOfClient < j; ++NumBattlePositionsOfClient)
    {
        v8 = a2->mons[NumBattlePositionsOfClient];
        if (BattleMon_GetValue(v8, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
        {
            if (NumBattlePositionsOfClient >= i)
            {
                if (BattleMon_GetViewSrcData(v8) != a1->TempPartyPkm)
                {
                    BattleMon_RemoveIllusion(v8);
                }
            }
            else
            {
                // k::Printf("\nIllusion Mon ID is %d", illusionMonId);
                SrcData = BattleMon_GetSrcData(a2->mons[illusionMonId]);
                BattleMon_SetIllusion(v8, SrcData);
            }
        }
        j = a2->memberCount;
    }
    v10 = 0;
    if (j > 0)
    {
        do
        {
            BattleMon_IsIllusionEnabled(a2->mons[v10++]);
        } while (v10 < a2->memberCount);
    }
}

#pragma region unneeded
/*

    So it would be cute to modify teh wild pokemon illusion logic if we decide to make this available to players, but I'm not planning on
    doing that nor do i care about first mon Illusion logic.

*/
// extern "C" PokeParty* GetSrcParty(MainModule *a1, int a2, int a3);
// extern "C" u32 PokeParty_GetPkmCount(PokeParty *pPartyBlk);
// extern "C" PartyPkm * PokeParty_GetPkm(PokeParty *party, int slot);
// extern "C" BattleMon* BattleMon_Create(PartyPkm *a1, char a2, HeapID a3);
// extern "C" void BattleParty_AddMember(BattleParty *result, BattleMon *a2);
// extern "C" int GetPartyPkmnEligibleForBattle(PokeParty *a1);
// extern "C" BtlType MainModule_GetBattleType(MainModule *a1);
// extern "C" PartyPkm * PokeParty_NewTempPkm(MonsNo species, u32 level, u32 sidtid, AbilLock abil_num, HeapID heapId);
// extern "C" void BattleParty_MoveAlivePokeToFirst(BattleParty *a1);

// extern "C" void THUMB_BRANCH_PokeCon_SetParty(PokeCon *a1, MainModule *a2, int a3)
// {
//     unsigned int v4;                // r4
//     int i;                          // r5
//     PartyPkm *Pkm;                  // r0
//     int PartyPkmnEligibleForBattle; // r6
//     int v8;                         // r4
//     int v9;                         // r5
//     PartyPkm *v10;                  // r0
//     PokeParty *SrcParty;            // r6
//     unsigned int v12;               // r4
//     unsigned int v13;               // r5
//     PartyPkm *v14;                  // r0
//     int Param;                      // r0
//     MonsNo v16;                     // r0
//     unsigned __int16 Value;         // r0
//     u32 j;                          // [sp+Ch] [bp-3Ch]
//     int v21;                        // [sp+10h] [bp-38h]
//     MonsNo species;                 // [sp+14h] [bp-34h]
//     BattleMon *result;              // [sp+18h] [bp-30h]
//     u32 PkmCount;                   // [sp+1Ch] [bp-2Ch]
//     PokeParty *party;               // [sp+20h] [bp-28h]
//     BattleParty *v26;               // [sp+24h] [bp-24h]
//     int v27;                        // [sp+28h] [bp-20h]

//     v26 = a1->party;
//     party = GetSrcParty(a2, a3, a1->fForServer);
//     v27 = a3;
//     PkmCount = PokeParty_GetPkmCount(party);
//     v4 = 0;
//     v21 = FIRST_POS_FOR_CLIENT_ID[a3];
//     a1->srcParty[a3] = party;
//     for (i = v21; v4 < PkmCount; ++v4)
//     {
//         Pkm = PokeParty_GetPkm(party, v4);
//         a1->activePokeParam[i] = BattleMon_Create(Pkm, i, 0x12u);
//         BattleParty_AddMember(&v26[v27], a1->activePokeParam[i]);
//         i = (i + 1);
//     }
//     PartyPkmnEligibleForBattle = GetPartyPkmnEligibleForBattle(party);
//     if (PartyPkmnEligibleForBattle > 0)
//     {
//         v8 = 0;
//         v9 = v21;
//         do
//         {
//             if (BattleMon_GetValue(a1->activePokeParam[v9], VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
//             {
//                 v10 = PokeParty_GetPkm(party, PartyPkmnEligibleForBattle);
//                 BattleMon_SetIllusion(a1->activePokeParam[v9], v10);
//             }
//             ++v8;
//             v9 = (v9 + 1);
//         } while (v8 < PartyPkmnEligibleForBattle);
//     }
//     if (MainModule_GetBattleType(a2) == BtlType_Wild && a3 == 1)
//     {
//         for (j = 0; j < PkmCount; v21 = (v21 + 1))
//         {
//             result = a1->activePokeParam[v21];
//             if (BattleMon_GetSpecies(result) == PK571_ZOROARK && BattleMon_GetValue(result, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
//             {
//                 species = PK_NULL;
//                 SrcParty = GetSrcParty(a2, 0, a1->fForServer);
//                 v12 = PokeParty_GetPkmCount(SrcParty);
//                 v13 = 0;
//                 if (v12)
//                 {
//                     while (1)
//                     {
//                         v14 = PokeParty_GetPkm(SrcParty, v13);
//                         Param = PokeParty_GetParam(v14, PF_Species, 0);
//                         if (Param == PK243_RAIKOU)
//                         {
//                             v16 = PK244_ENTEI;
//                             goto LABEL_16;
//                         }
//                         if (Param == PK244_ENTEI)
//                         {
//                             v16 = PK245_SUICUNE;
//                             goto LABEL_16;
//                         }
//                         if (Param == PK245_SUICUNE)
//                         {
//                             break;
//                         }
//                         v13 = (v13 + 1);
//                         if (v13 >= v12)
//                         {
//                             goto LABEL_22;
//                         }
//                     }
//                     v16 = PK243_RAIKOU;
//                 LABEL_16:
//                     species = v16;
//                 }
//             LABEL_22:
//                 if (species)
//                 {
//                     if (!a2->TempPartyPkm)
//                     {
//                         Value = BattleMon_GetValue(result, VALUE_LEVEL);
//                         a2->TempPartyPkm = PokeParty_NewTempPkm(species, Value, 0, ABIL_0, a2->heapID);
//                     }
//                     BattleMon_SetIllusion(result, a2->TempPartyPkm);
//                 }
//             }
//             else if (BattleMon_GetValue(result, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION){

//             }
//             else {

//             }
//             ++j;
//         }
//     }
//     BattleParty_MoveAlivePokeToFirst(&v26[v27]);
// }
#pragma endregion