#include "swantypes.h"

extern "C" {
    int THUMB_BRANCH_HandlerIronFist(int a1, int a2, int a3)
    {
        int result;             // r0
        unsigned __int16 Value; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVEID);
            result = getMoveFlag(Value, FLAG_PUNCH);
            if (result)
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 5325);
            }
        }
        return result;
    }
}