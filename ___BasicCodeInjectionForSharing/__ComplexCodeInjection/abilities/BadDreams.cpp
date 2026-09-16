#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerBadDreamsTrapping(int a1, ServerFlow *a2, unsigned int a3, int a4)
{
    __int16 ExistFrontPokePos; // r0
    unsigned int NumTargets;   // r6
    unsigned int v10;          // r4
    BattleMon *BattleMon;      // r0
    unsigned char v12[24];     // [sp+0h] [bp-18h] BYREF

    *v12 = a4;
    if (!MainModule_IsAllyMonID(BattleEventVar_GetValue(VAR_MON_ID), a3))
    {
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
        NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, v12);
        v10 = 0;
        if (NumTargets)
        {
            while (1)
            {
                BattleMon = Handler_GetBattleMon(a2, v12[v10]);
                if (!BattleMon_CheckIfMoveCondition(BattleMon, CONDITION_SLEEP) || BattleMon_HasType(BattleMon, TYPE_GHOST))
                {
                    break;
                }
                v10 = (v10 + 1);
                if (v10 >= NumTargets)
                {
                    BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                }
            }
        }
        else
        {
            BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        }
    }
}

ABILITY_TRIGGERTABLE BadDreamsHandlers[] = {
    {EVENT_TURN_CHECK_END, (ABILITY_HANDLER_FUNC)HandlerBadDreams},      // 22
    {EVENT_PREVENT_RUN, (ABILITY_HANDLER_FUNC)HandlerBadDreamsTrapping}, // 22
};

// was: THUMB_BRANCH_EventAddBadDreams
extern "C" ABILITY_TRIGGERTABLE *e7b(_DWORD *a1)
{
    *a1 = 2;
    return BadDreamsHandlers;
}