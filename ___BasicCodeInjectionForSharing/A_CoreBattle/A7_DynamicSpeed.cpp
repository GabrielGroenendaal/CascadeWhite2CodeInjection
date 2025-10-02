#include "swantypes.h"
#include "codeinjection_battlefield.h"
#include "kPrint.h"
#include "settings.h"

#define ACTION_ORDER_GET_PRIO(actionOrder, idx) (actionOrder[idx].field_8 >> 16) & 0x3FFFFF
#define ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder, idx) ((actionOrder[idx].field_8 >> 13) & 0x7)

extern "C" b32 CheckEndTurnSwitchFlag();
extern "C" void SetEndTurnSwitchFlag();
extern "C" void ResetEndTurnSwitchFlag();

extern "C" u32 CommonGetAllyPos(ServerFlow *serverFlow, u32 battlePos);

extern "C" void ShiftExtraActionOrders();
extern "C" ActionOrderWork *GetExtraActionOrder(u32 actionIdx);

extern "C" b32 CheckExtraActionFlag();
extern "C" void SetExtraActionFlag();
extern "C" void ResetExtraActionFlag();
extern "C" b32 IsCenterInTripleBattle(u32 battlePos);
extern void sys_memset16(u16 value, void *ptr, size_t size);
extern void *sys_memcpy16(const void *src, void *dst, size_t size);
extern void sys_memset32(u32 value, void *ptr, size_t size);
extern void *sys_memcpy32(const void *src, void *dest, size_t size);
extern void sys_memcpy_volatile(const void *src, volatile int *dest, size_t size);
extern void sys_memset32_fast(u32 value, const void *ptr, size_t size);
extern void *sys_memcpy32_fast(const void *src, void *dst, u32 size);
extern void sys_memset(const void *ptr, u8 value, size_t size);
extern void sys_memset_fast(const void *ptr, u8 value, size_t size);
extern const void *sys_memcpy(const void *src, void *dst, u32 size);
extern s32 sys_memcmp(const void *src1, const void *src2, size_t size);
extern const void *sys_memcpy_fast(const void *src, void *dst, size_t size);
extern const void *sys_memcpy_ex(const void *src, void *dst, s32 size);

extern "C" u32 j_j_FaintRecord_GetCount_1(FaintRecord *faintRecord, u32 turn);
extern "C" void SortActionOrderBySpeed(ServerFlow *serverFlow, ActionOrderWork *actionOrder, u32 remainingActions);
// extern "C" b32 ActionOrder_InterruptReserve(ServerFlow * serverFlow, u32 pokemonSlot);
// extern "C" u32 ActionOrder_SendToLast(ServerFlow * serverFlow, u32 pokemonSlot);

// Records if an InterruptAction event (After You) was triggered in the current turn
// - Used in [ServerFlow_ActOrderProcMain] & [BattleHandler_InterruptAction]
u8 interruptActionFlag = 0;

// Records the battleslot of the mons that have been sent last (Quash) in the current turn
// - Used in [PokeSet_SortBySpeedDynamic] & [BattleHandler_SendLast]
u8 sendLastSlots[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

extern "C" void SwapPokemonOrder(ActionOrderWork *actionOrder, u16 *speedStats, u8 *priority, u8 *eventPriority, u8 slowIdx, u8 fastIdx)
{
    BattleMon *bufferMon = actionOrder[fastIdx].battleMon;
    BattleActionParam *bufferAction = actionOrder[fastIdx].Action;
    u32 buffer_speed = actionOrder[fastIdx].field_8;
    u8 buffer_partyID = actionOrder[fastIdx].field_C;
    u8 buffer_done = actionOrder[fastIdx].fDone;
    u8 buffer_field_E = actionOrder[fastIdx].field_E;
    u8 buffer_field_F = actionOrder[fastIdx].field_F;
    u16 bufferSpeed = speedStats[fastIdx];
    u8 bufferPriority = priority[fastIdx];
    u8 bufferEventPriority = eventPriority[fastIdx];

    actionOrder[fastIdx].battleMon = actionOrder[slowIdx].battleMon;
    actionOrder[slowIdx].battleMon = bufferMon;

    actionOrder[fastIdx].Action = actionOrder[slowIdx].Action;
    actionOrder[slowIdx].Action = bufferAction;

    actionOrder[fastIdx].field_8 = actionOrder[slowIdx].field_8;
    actionOrder[slowIdx].field_8 = buffer_speed;

    actionOrder[fastIdx].field_C = actionOrder[slowIdx].field_C;
    actionOrder[slowIdx].field_C = buffer_partyID;

    actionOrder[fastIdx].fDone = actionOrder[slowIdx].fDone;
    actionOrder[slowIdx].fDone = buffer_done;

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

extern "C" void PokeSet_SortBySpeedDynamic(ServerFlow *serverFlow, ActionOrderWork *actionOrder, u8 firstIdx, u8 turnStart)
{
    // Skip the Pok�mons that have already moved.
    u8 startIdx = firstIdx;
    if (!turnStart)
        startIdx += 1;

    // "firstIdx" is the latest Pok�mon to move.
    u8 pokeAmount = serverFlow->numActOrder - startIdx;

    // Reset the send last slots at the start of the turn.
    if (startIdx == 0)
        sys_memset(sendLastSlots, 0xFF, 6);

    if (pokeAmount > 1)
    {
        u16 speedStats[6];
        sys_memset(speedStats, 0, 12);

        u8 priority[6];
        sys_memset(priority, 0, 6);

        // 7 is the default, 6-0 are reserved for quash and 8 for escaping battle.
        u8 eventPriority[6];
        sys_memset(eventPriority, 7, 6);

        for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
        {
            if (!BattleMon_IsFainted(actionOrder[i].battleMon))
            {
                speedStats[i] = (u16)ServerEvent_CalculateSpeed(serverFlow, actionOrder[i].battleMon, 1);

                priority[i] = ACTION_ORDER_GET_PRIO(actionOrder, i);
                // Special priority takes into account item & ability prio boosts (1 = no added prio).
                int specialPriority = ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder, i);
                priority[i] += (specialPriority - 1);

                for (u8 j = 0; j < 6; ++j)
                {
                    if (sendLastSlots[j] == 0xFF)
                        break;

                    // If the mon has been sent last we give them a
                    // "quash speed" from 6 - 0 (non-quashed mons have 7)
                    if (sendLastSlots[j] == actionOrder[i].battleMon->ID)
                        eventPriority[i] = 6 - j;
                    // We don't break after finding a match, a mon can be quashed
                    // multiple times and the only one that matters is the last one
                }

                // This means the mon is making an escape attempt.
                // This makes it first, and overrides any other move priority.
                if (BattleAction_GetAction(&actionOrder[i].Action) == 4)
                    eventPriority[i] = 8;
            }
            else
            {
                priority[i] = 0xFF;
            }
        }

        // We randomize the initial order to resolve speed ties.
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
                // Check if the first Pok�mon is fainted.
                if (priority[i] != 0xFF)
                {
                    if (i + 1 < serverFlow->numActOrder)
                    {
                        for (u8 j = i + 1; j < serverFlow->numActOrder; ++j)
                        {
                            // Check if the second Pok�mon is fainted.
                            if (priority[j] != 0xFF)
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
        DPRINTF("\nPRIORITY(%d):", startIdx);
        for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
            DPRINTF("%d.", priority[i]);
        DPRINTF("\nEVENT(%d):", startIdx);
        for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
            DPRINTF("%d.", eventPriority[i]);
        DPRINT("\n\n");
#endif
    }
}

extern "C" u32 THUMB_BRANCH_BattleHandler_InterruptAction(ServerFlow *serverFlow, HandlerParam_InterruptPoke *params)
{
    if (!ActionOrder_InterruptReserve(serverFlow, params->pokeID))
    {
        return 0;
    }
    BattleHandler_SetString(serverFlow, &params->exStr);

    interruptActionFlag = 1;
    return 1;
}

extern "C" u32 THUMB_BRANCH_BattleHandler_SendLast(ServerFlow *serverFlow, HandlerParam_SendLast *params)
{
    if (!ActionOrder_SendToLast(serverFlow, params->pokeID))
    {
        return 0;
    }
    BattleHandler_SetString(serverFlow, &params->exStr);

    // Add the Pok�mon slot to the send last slots.
    for (u8 i = 0; i < 6; ++i)
    {
        if (sendLastSlots[i] == 0xFF)
        {
            sendLastSlots[i] = params->pokeID;
            break;
        }
    }

    return 1;
}

// Defines if a switch should be made after the turn has been processed
// The vanilla game does not have logic to switch after all actions have been performed
// like for example after receiving damage from a status condition
// - Set in [HandlerEmergencyExitSwitchEnd]
// - Reset & used in [ServerFlow_ActOrderProcMain]
u8 endTurnSwitchFlag = 0;

extern "C" b32 CheckEndTurnSwitchFlag()
{
    return endTurnSwitchFlag;
}
extern "C" void SetEndTurnSwitchFlag()
{
    endTurnSwitchFlag = 1;
}
extern "C" void ResetEndTurnSwitchFlag()
{
    endTurnSwitchFlag = 0;
}

extern "C" u32 CommonGetAllyPos(ServerFlow *serverFlow, u32 battlePos)
{
    BattleStyle battleStyle = (BattleStyle)BtlSetup_GetBattleStyle(serverFlow->mainModule);
    if (battleStyle != BTL_STYLE_DOUBLE && battleStyle != BTL_STYLE_TRIPLE)
    {
        return 6;
    }

    u8 isEnemy = battlePos & 1;
    if (isEnemy)
    {
        battlePos -= 1;
    }

    u32 allyPos = 0;
    if (battleStyle != BTL_STYLE_TRIPLE)
    {
        if (battlePos == 0)
        {
            allyPos = 2;
        }
        else
        {
            allyPos = 0;
        }
    }
    else
    {
        if (IsCenterInTripleBattle(battlePos))
        {
            allyPos = BattleRandom(2) * 4;
        }
        else
        {
            allyPos = 2;
        }
    }

    return allyPos + isEnemy;
}

// Stores data of extra action generated by Dancer, Instruct...
// - Set in [HandlerDancerCheckMove]
// - Reset and used in [ServerFlow_ActOrderProcMain]
ActionOrderWork extraActionOrder[6];

extern "C" void ShiftExtraActionOrders()
{
    for (u8 i = 5; i != 0; --i)
    {
        sys_memcpy(&extraActionOrder[i - 1], &extraActionOrder[i], sizeof(ActionOrderWork));
    }
    sys_memset(&extraActionOrder[0], 0, sizeof(ActionOrderWork));
}
extern "C" ActionOrderWork *GetExtraActionOrder(u32 actionIdx)
{
    return extraActionOrder + actionIdx;
}

// Defines if an extra action is taking place
// - Set and reset in [ServerFlow_ActOrderProcMain]
u8 extraActionFlag = 0;

extern "C" b32 CheckExtraActionFlag()
{
    return extraActionFlag;
}
extern "C" void SetExtraActionFlag()
{
    extraActionFlag = 1;
}
extern "C" void ResetExtraActionFlag()
{
    extraActionFlag = 0;
}
extern "C" void Turnflag_Clear(BattleMon *battleMon, TurnFlag flag);

extern "C" int THUMB_BRANCH_ServerFlow_ActOrderProcMain(ServerFlow *serverFlow, u32 currentActionIdx)
{
    u32 procAction = 0;
    ActionOrderWork *actionOrderWork = serverFlow->actionOrderWork;

    for (u8 i = 0; i < 6; ++i)
    {
        sys_memset(&extraActionOrder[i], 0, sizeof(ActionOrderWork));
    }

    // Re-calc speed after switch-ins
    PokeSet_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, 1);

    while (currentActionIdx < serverFlow->numActOrder || extraActionOrder[0].battleMon != nullptr)
    {
        ActionOrderWork *currentActionOrder = &actionOrderWork[currentActionIdx];
        // Swap the current action if an extra one has been scheduled
        u8 isExtraAction = 0;
        if (extraActionOrder[0].battleMon != nullptr)
        {
            isExtraAction = 1;
            currentActionOrder = &extraActionOrder[0];

            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_ACTIONSTART);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_ACTIONDONE);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_MOVEPROCDONE);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_MOVED);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_USINGFLING);

            SetExtraActionFlag();
        }

        if (!CheckExtraActionFlag())
        {
            // [1 = fight] [2 = item] [3 = switch] [4 = run]
            u32 action = BattleAction_GetAction(&currentActionOrder->Action);
            // I think this recals speed in rotation battles
            if (procAction == 6 && action != 6)
            {
                ServerControl_CheckActivation(serverFlow);
                SortActionOrderBySpeed(serverFlow, currentActionOrder, (u32)serverFlow->numActOrder - currentActionIdx);
            }
        }

        procAction = ActionOrder_Proc(serverFlow, currentActionOrder);

        // Skip speed calcs if After You was used
        if (interruptActionFlag != 1)
        {
            // Re-calc speed
            PokeSet_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, 0);
        }
        interruptActionFlag = 0;

        // Move the next extra action to the first slot
        if (isExtraAction)
        {
            for (u8 i = 0; i < 5; ++i)
            {
                sys_memcpy(&extraActionOrder[i + 1], &extraActionOrder[i], sizeof(ActionOrderWork));
            }
            sys_memset(&extraActionOrder[5], 0, sizeof(ActionOrderWork));

            ResetExtraActionFlag();
        }

        u32 getExp = ServerControl_CheckExpGet(serverFlow);
        b32 matchup = ServerControl_CheckMatchup(serverFlow);

        // Stop the turn if the battle ends
        if (matchup)
        {
            serverFlow->flowResult = 4;
            // Don't advance an action if we have an extra action
            if (isExtraAction)
            {
                return currentActionIdx;
            }
            else
            {
                return currentActionIdx + 1;
            }
        }

        // Stop the turn if a new Pok�mon has to enter the battle
        if (serverFlow->flowResult == 6 || serverFlow->flowResult == 1)
        {
            // Don't advance an action if we have an extra action
            if (isExtraAction)
            {
                return currentActionIdx;
            }
            else
            {
                return currentActionIdx + 1;
            }
        }

        // Stop the turn if a Pok�mon died but the battle is not over
        if (getExp)
        {
            serverFlow->flowResult = 3;
            // Don't advance an action if we have an extra action
            if (isExtraAction)
            {
                return currentActionIdx;
            }
            else
            {
                return currentActionIdx + 1;
            }
        }

        // Don't advance an action if we have an extra action
        if (!isExtraAction)
        {
            ++currentActionIdx;
        }
    }

    // Only TurnCheck if the turn is completely over
    if (!serverFlow->flowResult)
    {
        u32 turnCheck = ServerControl_TurnCheck(serverFlow);

        // Battle is over
        if (ServerControl_CheckMatchup(serverFlow))
        {
            serverFlow->flowResult = 4;
            return serverFlow->numActOrder;
        }

        // A Pok�mon fainted during the TurnCheck
        if (turnCheck)
        {
            serverFlow->flowResult = 3;
            return serverFlow->numActOrder;
        }


        if (CheckEndTurnSwitchFlag())
        {
            ResetEndTurnSwitchFlag();

            // Skip TurnCheck if a Pok�mon has to enter the battle during the TurnCheck
            serverFlow->TurnCheckSeq = 7;

            serverFlow->flowResult = 1;
            return serverFlow->numActOrder;
        }

        u32 faintedCount = j_j_FaintRecord_GetCount(&serverFlow->faintRecord, 0);
        if (Handler_IsPosOpenForRevivedMon(serverFlow) || faintedCount)
        {
            ServerFlow_ReqChangePokeForServer(serverFlow, (unsigned __int8 *)&serverFlow->field_4CE);
            ServerDisplay_IllusionSet(serverFlow, (unsigned __int8 *)&serverFlow->field_4CE);
            serverFlow->flowResult = 2;
            return serverFlow->numActOrder;
        }

        serverFlow->flowResult = 0;
    }
    return serverFlow->numActOrder;
}
