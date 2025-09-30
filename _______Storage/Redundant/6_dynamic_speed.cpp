
#include "codeinjection_battlefield.h"
#include "kPrint.h"
#include "settings.h"

#define THUMB_BRANCH_ServerFlow_ActOrderProcMain THUMB_BRANCH_OVL_167_0x0219FA10
#define THUMB_BRANCH_BattleHandler_InterruptAction THUMB_BRANCH_OVL_167_0x021ADEF0
#define THUMB_BRANCH_BattleHandler_SendLast THUMB_BRANCH_OVL_167_0x021ADF2C

#define ACTION_ORDER_GET_PRIO(actionOrder) (actionOrder[i].field_8 >> 16) & 0x3FFFFF
#define ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder) ((actionOrder[i].field_8 >> 13) & 0x7)

// Records if an InterruptAction event (After You) was triggered in the current turn
// - Used in [ServerFlow_ActOrderProcMain] & [BattleHandler_InterruptAction]
u8 interruptActionFlag = 0;

// Records the battleslot of the mons that have been sent last (Quash) in the current turn
// - Used in [PokeSet_SortBySpeedDynamic] & [BattleHandler_SendLast]
u8 sendLastSlots[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

// Uses x.yml


extern "C" {
	
	void SwapPokemonOrder(ActionOrderWork* actionOrder, u16* speedStats, u8* priority, u8* eventPriority, u8 slowIdx, u8 fastIdx)
    {
        BattleMon* bufferMon = actionOrder[fastIdx].battleMon;
        BattleActionParam* bufferAction = actionOrder[fastIdx].Action;
        u32 buffer_field_8 = actionOrder[fastIdx].field_8;
        char buffer_field_C = actionOrder[fastIdx].field_C;
        char buffer_fDone = actionOrder[fastIdx].fDone;
        char buffer_field_E = actionOrder[fastIdx].field_E;
        char buffer_field_F = actionOrder[fastIdx].field_F;
        u8 bufferSpeed = speedStats[fastIdx];
        u8 bufferPriority = priority[fastIdx];
        u8 bufferEventPriority = eventPriority[fastIdx];

        actionOrder[fastIdx].battleMon = actionOrder[slowIdx].battleMon;
        actionOrder[slowIdx].battleMon = bufferMon;

        actionOrder[fastIdx].Action = actionOrder[slowIdx].Action;
        actionOrder[slowIdx].Action = bufferAction;

        actionOrder[fastIdx].field_8 = actionOrder[slowIdx].field_8;
        actionOrder[slowIdx].field_8 = buffer_field_8;

        actionOrder[fastIdx].field_C = actionOrder[slowIdx].field_C;
        actionOrder[slowIdx].field_C = buffer_field_C;

        actionOrder[fastIdx].fDone = actionOrder[slowIdx].fDone;
        actionOrder[slowIdx].fDone = buffer_fDone;

        actionOrder[fastIdx].field_E = actionOrder[slowIdx].field_E;
        actionOrder[slowIdx].field_E = buffer_field_E;

        actionOrder[fastIdx].field_F = actionOrder[slowIdx].field_F;
        actionOrder[slowIdx].field_F = buffer_field_F;

        speedStats[fastIdx] = speedStats[slowIdx];
        speedStats[slowIdx] = bufferSpeed;

        priority[fastIdx] = priority[slowIdx];
        priority[slowIdx] = bufferPriority;

        eventPriority[fastIdx] = eventPriority[slowIdx];
        eventPriority[slowIdx] = bufferEventPriority;
    }

    void PokeSet_SortBySpeedDynamic(ServerFlow* serverFlow, ActionOrderWork* actionOrder, u8 firstIdx, u8 turnStart)
    {
        u8 startIdx = firstIdx; // Skip the mons that have already moved
        if (!turnStart)
            startIdx += 1;
        u8 pokeAmount = serverFlow->numActOrder - startIdx; // firstIdx is the latest mon to move

        k::Printf("\nWe are inside this function and this is working\n");
        if (startIdx == 0) // reset the send last slots at the start of the turn
            sys_memset(sendLastSlots, 0xFF, 6);

        if (pokeAmount > 1)
        {
            u16 speedStats[6];
            sys_memset(speedStats, 0, 12);

            u8 priority[6];
            sys_memset(priority, 0, 6);

            u8 eventPriority[6]; // 7 is the default, 6-0 are reserved for quash and 8 for escaping battle
            sys_memset(eventPriority, 7, 6);

            for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
            {
                if (!BattleMon_IsFainted(actionOrder[i].battleMon))
                {
                    speedStats[i] = (u16)ServerEvent_CalculateSpeed(serverFlow, actionOrder[i].battleMon, 1);

                    priority[i] = ACTION_ORDER_GET_PRIO(actionOrder);
                    int specialPriority = ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder); // special priority takes into account item & ability prio boosts (1 = no added prio)
                    priority[i] += (specialPriority - 1);

                    for (u8 j = 0; j < 6; ++j)
                    {
                        if (sendLastSlots[j] == 0xFF)
                            break;

                        if (sendLastSlots[j] == actionOrder[i].battleMon->ID) // if the mon has been sent last
                            eventPriority[i] = 6 - j; // we give him a "quash speed" from 6 - 0 (non-quashed mons have 7)
                        // we don't break after finding a match
                        // a mon can be quashed multiple times and the only one that matters is the last one
                    }
                    k::Printf("\nThe Action for battlemon %d is %d", actionOrder[i].battleMon->Species, BattleAction_GetAction(&actionOrder[i].Action));
                    if (BattleAction_GetAction(&actionOrder[i].Action) == 4) // this means the mon is making an escape attempt
                        k::Printf("\nWe got here at least?\n");
                        eventPriority[i] = 8; // this makes it first, and overrides any other move priority
                }
                else
                {
                    priority[i] = 0xFF;
                }
            }

            // I randomize the initial order to resolve speed ties
            for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
            {
                u8 randomSpot = startIdx + (u8)BattleRandom(pokeAmount);
                if (randomSpot != i)
                    SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, randomSpot);
            }

            u8 changes = 1;
            while (changes != 0)
            {
                changes = 0;

                for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
                {
                    if (priority[i] != 0xFF) // check if the first mon is fainted
                    {
                        if (i + 1 < serverFlow->numActOrder)
                        {
                            for (u8 j = i + 1; j < serverFlow->numActOrder; ++j)
                            {
                                if (priority[j] != 0xFF) // check if the second mon is fainted
                                {
                                    u8 poke1EventPriority = eventPriority[i];
                                    u8 poke2EventPriority = eventPriority[j];
                                    if (poke2EventPriority > poke1EventPriority)
                                    {
                                        SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, j);
                                        ++changes;
                                    }
                                    else if (poke2EventPriority == poke1EventPriority)
                                    {
                                        u8 poke1Priority = priority[i];
                                        u8 poke2Priority = priority[j];
                                        if (poke2Priority > poke1Priority)
                                        {
                                            SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, j);
                                            ++changes;
                                        }
                                        else if (poke2Priority == poke1Priority)
                                        {
                                            u16 poke1Speed = speedStats[i];
                                            u16 poke2Speed = speedStats[j];
                                            if (poke2Speed > poke1Speed)
                                            {
                                                SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, j);
                                                ++changes;
                                            }
                                        }
                                    }
                                }
                            }
            }
        }
    }
            }

#if DYNAMIC_SPEED_DEBUG
            DPRINTF("ORDER(%d):", startIdx);
            for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
                DPRINTF("%d.", actionOrder[i].battleMon->battleSlot);
            DPRINTF("\nSPEED(%d):", startIdx);
            for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
                DPRINTF("%d.", speedStats[i]);
            DPRINT("\n");
#endif
        }
    }

    int THUMB_BRANCH_ServerFlow_ActOrderProcMain(ServerFlow* serverFlow, u32 currentActionIdx)
    {
        ActionOrderWork* actionOrderWork;
        int action;
        BattleMon* battleMon;
        bool v8;
        BattleMon* v9;
        int flowResult;
        BattleMon* v12;
        int turnCheck;
        int count_1;
        int v15;
        int v16;

        v15 = 0;
        if (currentActionIdx >= (u32)(u8)serverFlow->numActOrder)
        {
        LABEL_14:
            if (!serverFlow->flowResult)
            {
                turnCheck = (u8)ServerControl_TurnCheck(serverFlow);
                if (ServerControl_CheckMatchup(serverFlow))
                {
                    serverFlow->flowResult = 4;
                    return (u8)serverFlow->numActOrder;
                }
                if (turnCheck)
                {
                    serverFlow->flowResult = 3;
                    return (u8)serverFlow->numActOrder;
                }
                count_1 = j_j_DeadRec_GetCount_1(&serverFlow->faintRecord, 0);
                if (Handler_IsPosOpenForRevivedMon(serverFlow) || count_1)
                {
                    ServerFlow_ReqChangePokeForServer(serverFlow, (unsigned __int8 *)&serverFlow->field_4CE);
                    ServerDisplay_IllusionSet(serverFlow, (unsigned __int8 *)&serverFlow->field_4CE);
                    serverFlow->flowResult = 2;
                    return (u8)serverFlow->numActOrder;
                }
                serverFlow->flowResult = 0;
            }
            return (u8)serverFlow->numActOrder;
        }
        else
        {
            actionOrderWork = serverFlow->actionOrderWork;

            PokeSet_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, 1); // pre-calc speed to take into account switch-in speed modifiers (weather...)

            while (1)
            {
                // [1 = fight] [2 = item] [3 = switch] [4 = run]
                action = BattleAction_GetAction(&actionOrderWork[currentActionIdx].Action);
                if (v15 == 6 && action != 6)
                {
                    ServerControl_CheckActivation(serverFlow);
                    sub_219FB7C(serverFlow, &actionOrderWork[currentActionIdx], (u32)serverFlow->numActOrder - currentActionIdx);
                }
                v15 = ActionOrder_Proc(serverFlow, &actionOrderWork[currentActionIdx]);

                if (interruptActionFlag != 1) // skip speed calcs if after you was used
                    PokeSet_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, 0); // re-calc speed
                interruptActionFlag = 0;

                v16 = (u8)ServerControl_CheckExpGet(serverFlow);

                battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, 0);

                CheckHPDebug(battleMon);
                v8 = ServerControl_CheckMatchup(serverFlow);
                v9 = PokeCon_GetBattleMon(serverFlow->pokeCon, 0);
                CheckHPDebug(v9);
                if (v8)
                {
                    serverFlow->flowResult = 4;
                    return currentActionIdx + 1;
                }
                flowResult = serverFlow->flowResult;
                if (flowResult == 6 || flowResult == 1)
                {
                    return currentActionIdx + 1;
                }
                if (v16)
                {
                    break;
                }
                if (++currentActionIdx >= (u32)serverFlow->numActOrder)
                {
                    goto LABEL_14;
                }
                }
            v12 = PokeCon_GetBattleMon(serverFlow->pokeCon, 0);
            CheckHPDebug(v12);
            serverFlow->flowResult = 3;
            return currentActionIdx + 1;
            }
        }

    int THUMB_BRANCH_BattleHandler_InterruptAction(ServerFlow* serverFlow, HandlerParam_InterruptPoke* params)
    {
        if (!ActionOrder_InterruptReserve(serverFlow, params->pokeID))
        {
            return 0;
        }
        BattleHandler_SetString(serverFlow, &params->exStr);

        interruptActionFlag = 1;
        return 1;
    }

    int THUMB_BRANCH_BattleHandler_SendLast(ServerFlow* serverFlow, HandlerParam_SendLast* params)
    {
        if (!ActionOrder_SendToLast(serverFlow, params->pokeID))
        {
            return 0;
        }
        BattleHandler_SetString(serverFlow, &params->exStr);

        for (u8 i = 0; i < 6; ++i) // add the mon slot to the send last slots
        {
            if (sendLastSlots[i] == 0xFF)
            {
                sendLastSlots[i] = params->pokeID;
                break;
            }
        }
        
        return 1;
    }
	
}