
#include "../definitions/A_CodeInjection.h"

void THUMB_BRANCH_HandlerSolidRock(int a1, int a2, int a3)
{
    u8 Value; // r0
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        Value = BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS);
        BattleEventVar_MulValue(VAR_RATIO, ((Value == EFFECTIVENESS_2) ? 3072 : ((Value == EFFECTIVENESS_4) ? 2304 : 4096)));
    }
}