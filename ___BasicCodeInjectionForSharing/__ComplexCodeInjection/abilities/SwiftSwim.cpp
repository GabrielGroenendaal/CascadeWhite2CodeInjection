#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerSwiftSwimResist(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER)
    {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
    }
}

ABILITY_TRIGGERTABLE SwiftSwimHandlers[] = {
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSwiftSwim},
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSwiftSwimResist} // 41
};

// was: THUMB_BRANCH_EventAddSwiftSwim
extern "C" ABILITY_TRIGGERTABLE *e21(_DWORD *a1)
{
    *a1 = 2;
    return SwiftSwimHandlers;
}