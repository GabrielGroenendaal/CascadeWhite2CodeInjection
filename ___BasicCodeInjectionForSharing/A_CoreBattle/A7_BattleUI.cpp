

#include "codeinjection_battlefield.h"
#include "kPrint.h"
#include "settings.h"
#include "swantypes.h"

extern "C" int THUMB_BRANCH_BattleClient_ActionSelect_Root(BtlClientWk *a1, unsigned int *a2)
{
    unsigned int v3;                                     // r1
    BattleActionParam *v5;                               // r0
    int(__fastcall * v6)(BtlClientWk *, unsigned int *); // r1
    BtlClientWk *v7;                                     // r0
    unsigned int v8;                                     // r0
    bool v9;                                             // zf
    BtlvCore *btlvCore;                                  // r0
    int result;                                          // r0
    unsigned int v12;                                    // r0
    BattleMon *ClientPokeData;                           // r0
    int ID;                                              // r0

    v3 = *a2;
    if (v3 <= 8)
    {

        if (IsEqual(v3, 0))
        {
            a1->procPoke = PokeCon_GetClientPokeData(a1->pokeCon, a1->myID, a1->procPokeIdx);
            v5 = &a1->actionParam[a1->procPokeIdx];
            a1->procAction = (int*) v5;
            a1->currentActionCount = 0;
            BattleAction_SetNull(v5);
            if (AutoSelectAction(a1, a1->procPoke, a1->procAction))
            {
                v6 = BattleClient_ActionSelectCheckFinish;
                v7 = a1;
                BattleClient_ActionSelect_SetSubProc(v7, v6);
                return 0;
            }
            if (BattleClient_CheckTrainerMsg(a1, &a1->AITrainerMsgID) == 1)
            {
                v7 = a1;
                v6 = BattleClient_PlayGymLeaderFinalMusic;
                BattleClient_ActionSelect_SetSubProc(v7, v6);
                return 0;
            }
            v8 = *a2 + 1;
            *a2 = v8;
        }

        else if (IsEqual(v3, 1))
        {
            if (a1->prevPokeIdx != a1->procPokeIdx || a1->fStdMsgChanged)
            {
                BattleClient_SetupActionSelectStartStr(a1, (BattleMon *)a1->procPoke, &a1->strParam);
                BtlvCore_StartMessageImmediate(a1->btlvCore, &a1->strParam);
                a1->fStdMsgChanged = 0;
                a1->prevPokeIdx = a1->procPokeIdx;
                v8 = *a2 + 1;
                *a2 = v8;
            }
            v8 = v3 + 2;
            *a2 = v8;
        }

        else if (IsEqual(v3, 2))
        {
            if (!BtlvCore_WaitMessage(a1->btlvCore))
            {
                return 0;
            }
            ++*a2;
            BtlvCore_StartActionSelect(a1->btlvCore, (BattleMon *)a1->procPoke, a1->procPokeIdx > a1->firstPokeIdx, a1->procAction);
            v8 = *a2 + 1;
            *a2 = v8;
        }

        else if (IsEqual(v3, 3))
        {
            BtlvCore_StartActionSelect(a1->btlvCore, (BattleMon *)a1->procPoke, a1->procPokeIdx > a1->firstPokeIdx, a1->procAction);
            v8 = *a2 + 1;
            *a2 = v8;
        }

        else if (IsEqual(v3, 4))
        {
            v9 = BattleClient_CheckActionSelectForceQuit(a1, BattleClient_ActionForceQuit) == 0;
            btlvCore = (BtlvCore*)a1->btlvCore;
            if (!v9)
            {
                BtlvCore_QuitActionSelect(btlvCore);
                return 0;
            }
            v12 = BtlvCore_WaitActionSelect(btlvCore);
            if (v12 > 4)
            {
                return 0;
            }
            while (2)
            {

                if (IsEqual(v12, 0)){
                    return 0;
                }
                else if (IsEqual(v12, 1)){
                    LauncherCost_Save(a1, a1->procPokeIdx, 0);
                    v7 = a1;
                    v6 = BattleClient_ActionSelectFight;
                    BattleClient_ActionSelect_SetSubProc(v7, v6);
                    return 0;
                }
                else if (IsEqual(v12, 2)){
                    if (BattleMon_CheckIfMoveCondition((BattleMon *)a1->procPoke, CONDITION_SKY_DROP))
                    {
                        v8 = 6;
                        *a2 = v8;
                    }
                    if (a1->bagMode == 1 && !MainModule_IsWonderLauncherEnabled(a1->mainModule))
                    {
                        BtlvCore_RestartUI(a1->btlvCore);
                        v8 = 5;
                        *a2 = v8;
                    }
                    if (MainModule_GetPokestarType(a1->mainModule) == 1)
                    {
                        v7 = a1;
                        v6 = BattleClient_ActionSelectChooseSwitchPoke;
                    }
                    else
                    {
                        v7 = a1;
                        v6 = BattleClient_ActionSelectItem;
                    }
                    BattleClient_ActionSelect_SetSubProc(v7, v6);
                    return 0;
                    
                }
                else if (IsEqual(v12, 3)){
                     if (BattleMon_CheckIfMoveCondition((BattleMon *)a1->procPoke, CONDITION_SKY_DROP))
                    {
                        BtlvCore_RestartUI(a1->btlvCore);
                        v8 = 6;
                        *a2 = v8;
                    }
                    LauncherCost_Save(a1, a1->procPokeIdx, 0);
                    v7 = a1;
                    v6 = BattleClient_ActionSwitchPokemon;
                    BattleClient_ActionSelect_SetSubProc(v7, v6);
                    return 0;
                    
                }
                else if (IsEqual(v12, 4)){

                    if (a1->procPokeIdx == a1->firstPokeIdx)
                    {
                        if (BattleMon_CheckIfMoveCondition((BattleMon *)a1->procPoke, CONDITION_SKY_DROP) && MainModule_GetEscapeMode(a1->mainModule) != 2)
                        {
                            v8 = 6;
                            *a2 = v8;
                        }
                        LauncherCost_Save(a1, a1->procPokeIdx, 0);
                        v7 = a1;
                        v6 = BattleClient_ActionSelectEscape;
                        BattleClient_ActionSelect_SetSubProc(v7, v6);
                        return 0;
                    }
                    if (!a1->procPokeIdx)
                    {
                        return 0;
                    }
                    while (1)
                    {
                        ClientPokeData = PokeCon_GetClientPokeData(a1->pokeCon, a1->myID, --a1->procPokeIdx);
                        if (!AutoSelectAction(a1, ClientPokeData, 0))
                        {
                        }
                        if (!a1->procPokeIdx)
                        {
                            return 0;
                        }
                    }
                    a1->WonderLauncherEnergy += LauncherCost_Get(a1, a1->procPokeIdx);
                    if (BattleAction_GetActionType(&a1->actionParam[a1->procPokeIdx]) == ACTION_SWITCH)
                    {
                        j_j_PokeSelectResult_Pop(&a1->pokeSelectResult);
                    }
                    if (BattleAction_GetActionType(&a1->actionParam[a1->procPokeIdx]) == ACTION_ITEM)
                    {
                        selItemWork_Restore(a1, a1->procPokeIdx);
                    }
                    BattleClient_ActionSelect_SetSubProc(a1, BattleClient_ActionSelect_Root);
                    result = 0;

                }
                else {

                }
                
                return result;
            }
        }

        else if (IsEqual(v3, 5))
        {
            if (!BtlvCore_RestartUIIfNotTransitioning(a1->btlvCore))
            {
                return 0;
            }
            v8 = 3;
            *a2 = v8;
        }

        else if (IsEqual(v3, 6))
        {
            BtlvCore_RestartUIIfNotStandby(a1->btlvCore);
            v8 = *a2 + 1;
            *a2 = v8;
        }

        else if (IsEqual(v3, 7))
        {
            if (!BtlvCore_RestartUIIfNotTransitioning(a1->btlvCore))
            {
                return 0;
            }
            Btlv_StringParam_Setup(&a1->strParam, 1, 197);
            ID = BattleMon_GetID(a1->procPoke);
            Btlv_StringParam_AddArg(&a1->strParam, ID);
            BattleClient_ActionSelect_StartMessage(a1, &a1->strParam);
            v8 = *a2 + 1;
            *a2 = v8;
        }

        else if (IsEqual(v3, 8))
        {
            if (!BtlvCore_WaitMessage(a1->btlvCore))
            {
                return 0;
            }
            v8 = 1;
            *a2 = v8;
        }

        else
        {
            return 0;
        }
    }
    return 0;
}