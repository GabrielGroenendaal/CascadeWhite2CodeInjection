#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerForewarnMessage(int a1, ServerFlow *a2, unsigned int a3)
{
    BattleMon *PokeParam;     // r7
    HandlerParam_Message *v1; // r0

    if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        PokeParam = Handler_GetBattleMon(a2, (int)a3);
        BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
        v1 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
        BattleHandler_StrSetup(&v1->str, 2u, 1228);
        BattleHandler_AddArg(&v1->str, a3);
        BattleHandler_PopWork(a2, v1);
        BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
    }
}

extern "C" void HandlerForewarnNew(BattleEventItem *a1, ServerFlow *a2, int a3)
{
    if ((a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) || MainModule_IsAllyMonID(a3, BattleEventVar_GetValue(VAR_MON_ID))) && BattleEventVar_GetValue(VAR_CRITICAL_FLAG))
    {
        BattleEventVar_MulValue(VAR_RATIO, 3072);
    }
}

ABILITY_TRIGGERTABLE ForewarnHandlers[] = {
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerForewarnMessage}, // 22
    {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerForewarnMessage},
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerForewarnNew},
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}};

// was: THUMB_BRANCH_EventAddForewarn
extern "C" ABILITY_TRIGGERTABLE *e6c(_DWORD *a1)
{
    *a1 = 4;
    return ForewarnHandlers;
}
