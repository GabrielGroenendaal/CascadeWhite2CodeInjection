#include "../definitions/A_CodeInjection.h"


extern "C" void HandlerMoldBreakerPower(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 4505);
    }
}

ABILITY_TRIGGERTABLE MoldBreakerHandlers[] = {
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerSwitchIn}, // 22
    {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerSwitchIn},
    {EVENT_MOVE_SEQUENCE_START, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerStart},
    {EVENT_MOVE_SEQUENCE_END, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerEnd},
    {EVENT_ABILITY_NULLIFIED, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerConfirm},
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerPower}, // 6
};

// was: EventAddMoldBreakerNew
extern "C" ABILITY_TRIGGERTABLE * e68(_DWORD *a1)
{
    *a1 = 6;
    return MoldBreakerHandlers;
}