#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerCorrosion(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_POISON && BattleEventVar_GetValue(VAR_POKE_TYPE) == TYPE_STEEL)
    {
        BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 2);
    }
}

ABILITY_TRIGGERTABLE CorrosionHandlers[] = {
    {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerCorrosion}, // 26
};

// was: THUMB_BRANCH_EventAddLimber
extern "C" ABILITY_TRIGGERTABLE *e07(_DWORD *a1)
{
    *a1 = 1;
    return CorrosionHandlers;
}