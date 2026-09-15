
#include "../definitions/A_CodeInjection.h"

extern "C" void HanderFurCoat(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) == 1)
        {
            BattleEventVar_MulValue(VAR_RATIO, 2048);
        }
    }
}

ABILITY_TRIGGERTABLE FurCoatHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HanderFurCoat},   // 22
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLeafGuard(_DWORD *a1)
{
    *a1 = 2;
    return FurCoatHandlers;
}