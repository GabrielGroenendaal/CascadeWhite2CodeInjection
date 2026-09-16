#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerMagician(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
        if (!*work)
        {
            u32 targetSlot = BattleEventVar_GetValue(VAR_TARGET_MON_ID);
            if (targetSlot != 31 && getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
            {
                BattleMon *targetMon = Handler_GetBattleMon(serverFlow, targetSlot);
                if (BattleMon_GetHeldItem(targetMon))
                {
                    if (!HandlerCommon_CheckIfCanStealPokeItem(serverFlow, pokemonSlot, targetSlot))
                    {
                        BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);
                        if (BattleMon_GetHeldItem(currentMon) == IT_NULL)
                        {
                            HandlerParam_SwapItem *swapItem;
                            swapItem = (HandlerParam_SwapItem *)BattleHandler_PushWork(serverFlow, EFFECT_SWAPITEM, pokemonSlot);
                            swapItem->pokeID = targetSlot;
                            BattleHandler_StrSetup(&swapItem->exStr, 2u, 1057);
                            BattleHandler_AddArg(&swapItem->exStr, pokemonSlot);
                            BattleHandler_AddArg(&swapItem->exStr, targetSlot);
                            ItemID heldItem = (ItemID)BattleMon_GetHeldItem(targetMon);
                            BattleHandler_AddArg(&swapItem->exStr, heldItem);
                            BattleHandler_PopWork(serverFlow, swapItem);
                        }
                        else
                        {
                            HandlerParam_SetItem *setItem;
                            setItem = (HandlerParam_SetItem *)BattleHandler_PushWork(serverFlow, EFFECT_SET_HELD_ITEM, pokemonSlot);
                            setItem->pokeID = targetSlot;
                            setItem->itemID = 0;
                            BattleHandler_StrSetup(&setItem->exStr, 2u, 1050); // Change the Text for this!
                            BattleHandler_AddArg(&setItem->exStr, pokemonSlot);
                            BattleHandler_AddArg(&setItem->exStr, targetSlot);
                            BattleHandler_AddArg(&setItem->exStr, BattleMon_GetHeldItem(targetMon));
                            BattleHandler_PopWork(serverFlow, setItem);
                        }
                        BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
                    }
                }
            }
        }
    }
}
ABILITY_TRIGGERTABLE PickpocketHandlers[]{
    {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, (ABILITY_HANDLER_FUNC)HandlerMagician},
};
// was: THUMB_BRANCH_EventAddPickpocket
extern "C" ABILITY_TRIGGERTABLE *e7c(_DWORD *a1)
{
    *a1 = 1;
    return PickpocketHandlers;
}
