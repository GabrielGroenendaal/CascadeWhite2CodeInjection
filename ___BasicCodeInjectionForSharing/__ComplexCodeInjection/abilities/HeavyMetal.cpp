
#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerHeavyMetalDefense(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1)
        {
            BattleEventVar_MulValue(VAR_RATIO, 6144);
        }
    }
}

extern "C" void HandlerHeavyMetalSpeed(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID)) // hail
    {
        BattleEventVar_MulValue(VAR_RATIO, 2730);
    }
}

ABILITY_TRIGGERTABLE HeavyMetalHandlers[] = {
    {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerHeavyMetalDefense}, // 22
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerHeavyMetalSpeed},
    {EVENT_WEIGHT_RATIO, (ABILITY_HANDLER_FUNC)HandlerHeavyMetal},
};

// was: THUMB_BRANCH_EventAddHeavyMetal
extern "C" ABILITY_TRIGGERTABLE *e86(_DWORD *a1)
{
    *a1 = 3;
    return HeavyMetalHandlers;
}
