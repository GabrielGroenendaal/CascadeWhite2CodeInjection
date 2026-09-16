#include "../definitions/A_CodeInjection.h"



extern "C" void HandlerSandForce(int a1, int a2, int a3)
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


ABILITY_TRIGGERTABLE SandForceHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSandForce}, // 15
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSandVeilWeather}
};


// was: EventAddSandForceNew
extern "C" ABILITY_TRIGGERTABLE * e9f(_DWORD *a1)
{
  *a1 = 2;
  return SandForceHandlers;
}
