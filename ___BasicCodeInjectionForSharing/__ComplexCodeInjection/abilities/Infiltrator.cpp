
#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerInfiltratorPower(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS) > 3)
    {
        BattleEventVar_MulValue(VAR_RATIO, 4915);
    }
}

ABILITY_TRIGGERTABLE InfiltratorHandlers[] = {
    {EVENT_MOVE_SEQUENCE_START, (ABILITY_HANDLER_FUNC)HandlerInfiltratorStart},
    {EVENT_MOVE_SEQUENCE_END, (ABILITY_HANDLER_FUNC)HandlerInfiltratorEnd},
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerInfiltratorPower}, // 6
};

// was: THUMB_BRANCH_EventAddInfiltrator
extern "C" ABILITY_TRIGGERTABLE *e97(_DWORD *a1)
{
    *a1 = 3;
    return InfiltratorHandlers;
}
