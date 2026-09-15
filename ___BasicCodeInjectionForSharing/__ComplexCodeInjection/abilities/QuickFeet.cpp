#include "_preStatus.h"

extern "C" void HandlerPreParalysisOnAI(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
    {
        triggerPreStatus(a2, a3, CONDITION_PARALYSIS);
    }
}

ABILITY_TRIGGERTABLE QuickFeetHandlers[] = {
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerQuickFeet},       // 13
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreParalysisOnAI}, // 14
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddQuickFeet(_DWORD *a1)
{
    *a1 = 2;
    return QuickFeetHandlers;
}
