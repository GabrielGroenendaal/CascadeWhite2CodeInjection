#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerNormalizePower(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) // physical
        {
            BattleEventVar_MulValue(VAR_RATIO, 5325); // 20% boost
        }
    }
    // if (BattleEventVar_GetValue(VAR_MOVE_TYPE) != TYPE_NORMAL)
    // {
    //     BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_NORMAL);
    // }
}
extern "C" void HandlerNormalizeEffectiveness(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
    {
        BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 1);
    }
}

ABILITY_TRIGGERTABLE NormalizeHandlers[] = {
    {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerNormalize}, // 22
    {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerNormalizePower},
    {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerNormalizeEffectiveness},

};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddNormalize(_DWORD *a1)
{
    *a1 = 3;
    return NormalizeHandlers;
}