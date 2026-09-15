
#include "../definitions/A_CodeInjection.h"
#include "../definitions/settings.h"

extern "C" void HandlerFluffyFire(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_FIRE)
    {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
    }
}

extern "C" void HandlerFluffy(int a1, ServerFlow *a2, int a3)
{
    int ratio;
    BattleMon *attackingMon;
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
        {

            ratio = 2048;
        }
        else
        {
            ratio = 4096;
        }
        BattleEventVar_MulValue(VAR_RATIO, ratio);
    }
}

ABILITY_TRIGGERTABLE FluffyHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerFluffyFire},
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerFluffy},   // 22
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddImmunity(_DWORD *a1)
{
    *a1 = 3;
    return FluffyHandlers;
}
