#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerAtePower(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) // physical
        {
            BattleEventVar_MulValue(VAR_RATIO, 4915); // 20% boost
        }
    }
}

extern "C" void HandlerAerilateType(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
        {
            BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_FLYING);
        }
    }
}
ABILITY_TRIGGERTABLE AerilateHandlers[] = {
    {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerAerilateType}, // 22
    {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStickyHold(_DWORD *a1)
{
    *a1 = 2;
    return AerilateHandlers;
}