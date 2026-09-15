#include "../definitions/A_CodeInjection.h"

extern "C" void THUMB_BRANCH_HandlerStench(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (!BattleEventVar_GetValue(VAR_DEFAULT_EFFECT_CHANCE))
        {
            BattleEventVar_RewriteValue(VAR_EFFECT_CHANCE, 20);
        }
    }
}
