#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerAngerPointPower(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (BattleMon_GetTurnFlag(Handler_GetBattleMon(a2, a3), TURNFLAG_MOVEFAILEDLASTTURN))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 6144);
        }
    }
}

extern "C" void HandlerAngerPointSpeed(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (BattleMon_GetTurnFlag(Handler_GetBattleMon(a2, a3), TURNFLAG_MOVEFAILEDLASTTURN))
        {
            BattleEventVar_MulValue(VAR_RATIO, 6144);
        }
    }
}

extern "C" void HandlerAngerPointMessage(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (BattleMon_GetTurnFlag(Handler_GetBattleMon(a2, a3), TURNFLAG_MOVEFAILED))
        {
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
            HandlerParam_Message *v1 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v1->str, 2u, 1243);
            BattleHandler_AddArg(&v1->str, a3);
            BattleHandler_PopWork(a2, v1);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
        }
    }
}

ABILITY_TRIGGERTABLE AngerPointHandlers[] = {
    {EVENT_MOVE_EXECUTE_END, (ABILITY_HANDLER_FUNC)HandlerAngerPointMessage},  // 22
    {EVENT_MOVE_EXECUTE_FAIL, (ABILITY_HANDLER_FUNC)HandlerAngerPointMessage}, // 22
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerAngerPointPower},
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerAngerPointSpeed},

};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddAngerPoint(_DWORD *a1)
{
    *a1 = 4;
    return AngerPointHandlers;
}
