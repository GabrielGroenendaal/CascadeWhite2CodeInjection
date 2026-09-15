#include "../definitions/A_CodeInjection.h"



extern "C" void THUMB_BRANCH_HandlerSandForce(int a1, int a2, int a3)
{
    u8 Value; // r0

    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        Value = BattleEventVar_GetValue(VAR_MOVE_TYPE);
        if (Value == 4 || Value == 5 || Value == 8)
        {
            if (Handler_GetWeather(a2) == 4)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5734);
            }
            else
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 4915);
            }
        }
    }
}