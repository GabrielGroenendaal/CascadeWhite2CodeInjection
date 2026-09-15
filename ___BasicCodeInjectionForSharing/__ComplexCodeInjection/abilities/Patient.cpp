#include "../definitions/A_CodeInjection.h"

extern "C" void THUMB_BRANCH_HandlerAnalytic(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (HandlerCommon_IsMonLastInTurnOrder(a2, a3))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);
        }
    }
}