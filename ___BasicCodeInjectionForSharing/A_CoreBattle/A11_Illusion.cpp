

#include "codeinjection_battlefield.h"
#include "kPrint.h"
#include "settings.h"
#include "swantypes.h"

extern "C" int BattleMon_CanBattle(BattleMon *a1);
extern "C" BattleStyle MainModule_GetBattleStyle(MainModule *a1);
extern "C" int MainModule_GetNumBattlePositionsOfClient(MainModule *a1, int a2);
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
        if (!(BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION))
        {
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
        } else {
            k::Printf("\nWe are skipping the illusion Pokemon");
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

    // // This is logic that is present in teh SwitchAI_Core with the output of this function, so I'm just nesting it in here
    // // It checks to see if the pokemon is in reserve, returning the last value in the char array which is the highest value BP move
    int iterate = 0;
    while (SwitchAI_CheckReserve(a1, a2[iterate]))
    {
        if (++iterate >= a3)
        {
            return result;
        }
    }
    result = a2[iterate];
    return result;
}


extern "C" unsigned int THUMB_BRANCH_PickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
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
                            if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION){
                                int actualBest = PersonalPickBestMonToSwitchInto(a1, a2, a3, a4);
                                k::Printf("\nThe actual best switch in is %d\n",  BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[actualBest])->Species);
                                if (actualBest == i){
                                    k::Printf("\nThe Illusion Pokemon is  the best switch in");
                                    if (RandomInRange(0, 100) > 50){
                                        k::Printf(" but is going dodge their duties\n");

                                        BasePower = BasePower >> 1;
                                    }
                                } 
                                else if (actualBest != i && BasePower >= 80){
                                    k::Printf("\nThe Illusion Pokemon is not the best switch in");
                                    if (RandomInRange(0, 100) > 50){
                                        k::Printf(" but is going to come in anyways\n");
                                        BasePower = BasePower << 1;
                                    }
                                }
                                else {

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
    if (MainModule_GetBattleStyle(a1) == BTL_STYLE_ROTATION)
    {
        NumBattlePositionsOfClient = 3;
    }
    else
    {
        NumBattlePositionsOfClient = MainModule_GetNumBattlePositionsOfClient(a1, a3);
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
                // SrcData = BattleMon_GetSrcData(a2->mons[i]);
                // BattleMon_SetIllusion(v8, SrcData);


                unsigned char validMonsInParty[28];
                int clientId = MainModule_PokeIDToClientID(v8->ID);
                k::Printf("\nThe mon we're checking is %d and the client id is %d", v8->Species, clientId);
                int numOfMonsToCheckForSwitch = GetNumBattleReadyPartyMons(a1->clients[clientId], validMonsInParty);
                k::Printf("\nThe number of mons to check for is %d\n", numOfMonsToCheckForSwitch);
                // finds the pokeposition of the pokemon
                __int16 pokePos = MainModule_GetClientPokePos(a1, clientId, NumBattlePositionsOfClient);
                k::Printf("\nPokePos is %d\n", pokePos);
                // randomly picks an opposing pokemon (makes illusion even spookier in doubles)
                BattleMon* opposingPokemon = SwitchAI_DetermineOpponent(a1->clients[clientId], pokePos);

                // grabs the battleparty idx of the best switch in target
                // this is a modified version of the PickBestMonToSwitchInto function, which normally has a random check for illusion pokemon to modify their BP.
                int illusionId = PersonalPickBestMonToSwitchInto(a1->clients[clientId], validMonsInParty, numOfMonsToCheckForSwitch, opposingPokemon);
                k::Printf("\nIllusion ID is %d and NumBattlePositionsOfClient is %d\n", illusionId, NumBattlePositionsOfClient);

                // checks to see if that is the illusion pokemon, if it isn't, continue.
                // if (illusionId == NumBattlePositionsOfClient)
                // {
                //     // runs the modified PickBestMonToSwitchInto again with a flag that causes it to ignore the illusion pokemon's id, as if they are fainted.
                //     // can never return nothing since, if there were no other pokemon to choose from, it would've been hit by the if statement earlier
                //     // feeding in the specific id to ignore allows multiple illusion pokemon to function on the same team
                //     illusionId = PersonalPickBestMonToSwitchInto(a1->clients[clientId], validMonsInParty, numOfMonsToCheckForSwitch, opposingPokemon, NumBattlePositionsOfClient);
                // }
                SrcData = BattleMon_GetSrcData(a2->mons[illusionId]);
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