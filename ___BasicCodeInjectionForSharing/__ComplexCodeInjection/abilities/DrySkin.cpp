
#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerDrySkinDamage(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == 9)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
        }
    }
}

ABILITY_TRIGGERTABLE DrySkinHandlers[] = {
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerDrySkinWeather},      // 38
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerDrySkinDamage},             // 39
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerDrySkinCheck}, // 40
};

// was: THUMB_BRANCH_EventAddDrySkin
extern "C" ABILITY_TRIGGERTABLE *e57(_DWORD *a1)
{
    *a1 = 3;
    return DrySkinHandlers;
}