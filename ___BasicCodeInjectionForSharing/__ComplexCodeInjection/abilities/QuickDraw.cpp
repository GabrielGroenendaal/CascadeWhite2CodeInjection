#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerQuickDraw(int a1, ServerFlow *a2, int a3)
{
    HandlerParam_Message *v9;

    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (RollEffectChance(30u))
        {
            if (BattleEventVar_RewriteValue(VAR_PRIORITY, 2))
            {

                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                v9 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v9->str, 2u, 1348); // replace with the actual id
                BattleHandler_AddArg(&v9->str, a3);
                BattleHandler_PopWork(a2, v9);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }
}
ABILITY_TRIGGERTABLE QuickDrawHandlers[] = {
    {EVENT_CHECK_SPECIAL_PRIORITY, (ABILITY_HANDLER_FUNC)HandlerQuickDraw}, // 22
};

// was: THUMB_BRANCH_EventAddOwnTempo
extern "C" ABILITY_TRIGGERTABLE *e14(_DWORD *a1)
{
    *a1 = 1;
    return QuickDrawHandlers;
}