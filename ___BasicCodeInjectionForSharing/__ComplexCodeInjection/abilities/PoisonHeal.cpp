

#include "_preStatus.h"

extern "C" void HandlerPrePoisonOnAI(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
    {
        triggerPreStatus(a2, a3, CONDITION_POISON);
    }
}

ABILITY_TRIGGERTABLE PoisonHealHandlers[] = {
    {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerPoisonHeal}, // 17
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},     // 18
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPoisonHeal(_DWORD *a1)
{
    *a1 = 2;
    return PoisonHealHandlers;
}
