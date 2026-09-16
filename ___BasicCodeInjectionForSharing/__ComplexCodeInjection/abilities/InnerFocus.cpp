
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

extern "C" void HandlerInnerFocusAttack(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (BattleEventVar_GetValue(VAR_POKE_TYPE) == TYPE_DARK)
        {
            BattleEventVar_RewriteValue(VAR_NO_TYPE_EFFECTIVENESS, 1);
        }
    }
}

ABILITY_TRIGGERTABLE InnerFocusHandlers[] = {
    {EVENT_FLINCH_CHECK, (ABILITY_HANDLER_FUNC)HandlerInnerFocus}, // 22
    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerIntimidateCheck},
    {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerIntimidateGuard},
    {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerInnerFocusAttack}};

// was: THUMB_BRANCH_EventAddInnerFocus
extern "C" ABILITY_TRIGGERTABLE *e27(_DWORD *a1)
{
    *a1 = 4;
    return InnerFocusHandlers;
}
