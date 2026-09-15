
#include "../definitions/A_CodeInjection.h"
/* WE WILL EVENTUALLY WANT TO REFERENCE THIS WORK VALUE DIRECTLY TO DETERMINE WHETHER TRUANT IS ACTIVE */
extern "C" void THUMB_BRANCH_HandlerTruant(int a1, int a2, int a3, _DWORD *a4)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        BattleMon *mon = Handler_GetBattleMon((ServerFlow *)a2, a3);
        if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILEDLASTTURN))
        {
            *a4 = 0;
        }

        if (*a4)
        {
            if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) && BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
            {
                a4[1] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVEFAIL_ABILITY);
            }
            *a4 = 0;
        }
        else
        {
            if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) && BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
            {
                *a4 = 1;
            }
        }
        if (BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
        {
            *a4 = 0;
        }
    }
}