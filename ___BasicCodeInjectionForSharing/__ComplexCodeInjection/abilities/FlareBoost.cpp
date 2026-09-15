#include "_preStatus.h"


extern "C" void HandlerPreBurnOnAI(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
    {
        triggerPreStatus(a2, a3, CONDITION_BURN);
    }
}


ABILITY_TRIGGERTABLE FlareBoostHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerFlareBoost}, // 15
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI},
    {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerHeatproofStatus}, // 16
};


extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddFlareBoost(_DWORD *a1)
{
    *a1 = 3;
    return FlareBoostHandlers;
}