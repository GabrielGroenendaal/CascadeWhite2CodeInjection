#include "_preStatus.h"

extern "C" int checkHigher(int a1, int a2)
    {
        if (a1 < a2)
        {
            return a2;
        }
        return a1;
    }
extern "C" void HandlerPrePoisonOnAI(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
    {
        triggerPreStatus(a2, a3, CONDITION_POISON);
    }
}

extern "C" void HandlerToxicBoostStatus(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (BattleEventVar_GetValue(VAR_CONDITION_ID) == 5)
        {
            BattleEventVar_RewriteValue(VAR_DAMAGE, checkHigher(BattleEventVar_GetValue(VAR_DAMAGE) / 2, 1));
        }
    }
}

extern "C" void HandlerToxicBoostDamage(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_POISON)
        {
            BattleEventVar_MulValue(VAR_RATIO, 2048);
        }
    }
}

ABILITY_TRIGGERTABLE ToxicBoostHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},             // 42
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},           // 43
    {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 44
    {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerToxicBoostDamage}};

// was: THUMB_BRANCH_EventAddToxicBoost
extern "C" ABILITY_TRIGGERTABLE *e89(_DWORD *a1)
{
    *a1 = 4;
    return ToxicBoostHandlers;
}