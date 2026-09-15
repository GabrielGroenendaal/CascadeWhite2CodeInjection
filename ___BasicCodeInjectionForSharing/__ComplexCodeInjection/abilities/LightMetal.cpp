#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerLightMetalDefense(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1)
            {

                BattleEventVar_MulValue(VAR_RATIO, 2730);
            }
        }
    }

extern "C" void HandlerLightMetalSpeed(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID)) // hail
    {
        BattleEventVar_MulValue(VAR_RATIO, 6144);
    }
}

ABILITY_TRIGGERTABLE LightMetalHandlers[] = {
    {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerLightMetalDefense}, // 22
    {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerLightMetalSpeed},
    {EVENT_WEIGHT_RATIO, (ABILITY_HANDLER_FUNC)HandlerLightMetal},
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLightMetal(_DWORD *a1)
{
    *a1 = 3;
    return LightMetalHandlers;
}