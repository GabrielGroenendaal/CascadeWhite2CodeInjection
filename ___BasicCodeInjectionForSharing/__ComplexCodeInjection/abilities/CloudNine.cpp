#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerAirLockAccuracy(int a1, int a2, unsigned int a3)
{
    BattleEventVar_MulValue(VAR_RATIO, 4915);
}

ABILITY_TRIGGERTABLE AirLockHandlers[] = {
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerAirLockSwitchIn}, // 22
    {EVENT_WEATHER_CHECK, (ABILITY_HANDLER_FUNC)HandlerAirLockChangeWeather},
    {EVENT_MOVE_ACCURACY, (ABILITY_HANDLER_FUNC)HandlerAirLockAccuracy},
};

// was: THUMB_BRANCH_EventAddAirLock
extern "C" ABILITY_TRIGGERTABLE *e4c(_DWORD *a1)
{
    *a1 = 3;
    return AirLockHandlers;
}
