#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerSlushRush(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && Handler_GetWeather(a2) == 3) // hail
    {
        BattleEventVar_MulValue(VAR_RATIO, 0x2000);
    }
}

extern "C" void HandlerSlushRushPower(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ICE)
    {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
    }
}

ABILITY_TRIGGERTABLE SlushRushHandlers[] = {
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSlushRush},              // 7
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 8
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSlushRushPower},
    {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorStatus},
    {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon},
    {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
    {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorActionEnd},
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddTangledFeet(_DWORD *a1)
{
    *a1 = 8;
    return SlushRushHandlers;
}