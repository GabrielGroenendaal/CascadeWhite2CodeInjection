#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerSandRushResist(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ROCK)
    {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
    }
}

ABILITY_TRIGGERTABLE SandRushHandlers[] = {
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSandRush},              // FIX THIS
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSandVeilWeather}, // 41
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSandRushResist}};

// was: THUMB_BRANCH_EventAddSandRush
extern "C" ABILITY_TRIGGERTABLE *e92(_DWORD *a1)
{
    *a1 = 3;
    return SandRushHandlers;
}