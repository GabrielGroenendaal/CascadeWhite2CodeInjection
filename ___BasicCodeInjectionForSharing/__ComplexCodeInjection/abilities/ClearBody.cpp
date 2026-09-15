#include "../definitions/A_CodeInjection.h"

ABILITY_TRIGGERTABLE StrongBodyHandlers[] = {
    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerClearBodyCheck}, // 35
    {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerClearBodyGuard},       // 36
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerOvercoat},                   // 37
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddClearBody(_DWORD *a1)
{
    *a1 = 3;
    return StrongBodyHandlers;
}
