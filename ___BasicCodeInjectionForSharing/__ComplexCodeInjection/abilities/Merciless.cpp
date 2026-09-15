

#include "../definitions/A_CodeInjection.h"

extern "C" void MercilessOffense(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (BattleMon_GetStatus(Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON))))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5120);
        }
    }
}

extern "C" void MercilessDefense(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        if (BattleMon_GetStatus(Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON))))
        {
            BattleEventVar_MulValue(VAR_RATIO, 3072);
        }
    }
}

ABILITY_TRIGGERTABLE MercilessHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)MercilessOffense},               // 41
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)MercilessDefense}, // 41
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddWaterVeil(_DWORD *a1)
{
    *a1 = 2;
    return MercilessHandlers;
}