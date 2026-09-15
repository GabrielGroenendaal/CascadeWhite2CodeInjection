
#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerPickupNew(int a1, ServerFlow *a2, int a3)
{
    BattleMon *BattleMon; // r6
    u16 UsedItem;
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        BattleMon = Handler_GetBattleMon(a2, a3);
        UsedItem = BattleMon_GetUsedItem(BattleMon);

        if (UsedItem && BattleMon_GetHeldItem(BattleMon) == 0)
        {
            // See if we can add
            ConditionData v10;
            MakeCondition(CONDITION_EMBARGO, BattleMon, &v10);
            HandlerParam_AddCondition *v8 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v8->pokeID = a3;
            v8->sickID = CONDITION_EMBARGO;
            v8->sickCont = v10;
            v8->fAlmost = 0;
            BattleHandler_StrSetup(&v8->exStr, 2u, 1333);
            BattleHandler_AddArg(&v8->exStr, v8->pokeID);
            BattleHandler_PopWork(a2, v8);

            HandlerParam_SetItem *v9 = (HandlerParam_SetItem *)BattleHandler_PushWork(a2, EFFECT_SET_HELD_ITEM, a3);
            v9->header.flags |= 0x800000u;
            v9->itemID = UsedItem;
            v9->pokeID = a3;
            v9->fClearConsume = 0;
            BattleHandler_StrSetup(&v9->exStr, 2u, 1162);
            BattleHandler_AddArg(&v9->exStr, a3);
            BattleHandler_AddArg(&v9->exStr, UsedItem);
            BattleHandler_PopWork(a2, v9);
        }
    }
}

ABILITY_TRIGGERTABLE PickupHandlers[] = {
    {EVENT_SWITCH_OUT_END, (ABILITY_HANDLER_FUNC)HandlerPickupNew}, // 41
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPickup(_DWORD *a1)
{
    *a1 = 1;
    return PickupHandlers;
}