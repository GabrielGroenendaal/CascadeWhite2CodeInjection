#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerIntimidateCheck(int a1, int a2, int a3, int *a4)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (BattleEventVar_GetValue(VAR_INTIMFLAG))
        {
            if (BattleEventVar_GetValue(VAR_VOLUME) < 0)
            {

                *a4 = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
    }
}

extern "C" void HandlerIntimidateGuard(int a1, ServerFlow *a2, int pokemonSlot, int *a4)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID) && BattleEventVar_GetValue(VAR_INTIMFLAG))
    {
        BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, pokemonSlot);
        HandlerParam_Message *message;
        message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, pokemonSlot);
        BattleHandler_StrSetup(&message->str, 2u, 201);
        BattleHandler_AddArg(&message->str, pokemonSlot);
        BattleHandler_PopWork(a2, message);
        BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
    }
}

ABILITY_TRIGGERTABLE ScrappyHandlers[] = {
    {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerScrappy}, // 22
    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerIntimidateCheck},
    {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerIntimidateGuard},

    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerHyperCutterCheck},

    {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerHyperCutterGuard}};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddScrappy(_DWORD *a1)
{
    *a1 = 5;
    return ScrappyHandlers;
}