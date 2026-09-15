#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerToughClaws(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
        }
    }
}

ABILITY_TRIGGERTABLE ToughClawsHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerToughClaws}, // 6
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStall(_DWORD *a1)
{
    *a1 = 1;
    return ToughClawsHandlers;
}