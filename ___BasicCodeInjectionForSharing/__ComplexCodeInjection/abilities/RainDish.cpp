#include "../definitions/A_CodeInjection.h"

ABILITY_TRIGGERTABLE RainDishHandlers[] = {
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerRainDish},                // 29
    {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerWaterVeil},       // 30
    {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon}, // 31
    {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus}, // 32
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},            // 33
    {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerWaterVeilActionEnd}, // 34
};
extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRainDish(_DWORD *a1)
{
    *a1 = 6;
    return RainDishHandlers;
}