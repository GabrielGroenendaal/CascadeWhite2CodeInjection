
#include "../definitions/A_CodeInjection.h"
void THUMB_BRANCH_HandlerUnawareDefenseRank(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) || a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

void THUMB_BRANCH_HandlerUnawareAttackRank(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) || a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}