
#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
{
    HandlerParam_Message *v7; // r0
    int moveId;
    int result;
    if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        moveId = BattleEventVar_GetValue(VAR_MOVE_ID);

        if ((moveId == 78 || moveId == 79 || moveId == 147 || moveId == 476 || moveId == 77 || moveId == 139))
        {
            result = BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
            if (result)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v7->str, 2u, 210);
                BattleHandler_AddArg(&v7->str, (int)a3);
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }
}

ABILITY_TRIGGERTABLE OvercoatHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders}, // 24
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerOvercoat},               // 25
};

// was: THUMB_BRANCH_EventAddOvercoat
extern "C" ABILITY_TRIGGERTABLE *e8e(_DWORD *a1)
{
    *a1 = 2;
    return OvercoatHandlers;
}