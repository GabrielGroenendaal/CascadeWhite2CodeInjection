#include "../definitions/A_CodeInjection.h"

void THUMB_BRANCH_HandlerCuteCharm(int a1, ServerFlow *a2, unsigned int *a3)
{
    u8 v6;                            // r6
    BattleMon *PokeParam;             // r7
    HandlerParam_ChangeStatStage *v8; // r4
    if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
    {
        if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
        {
            v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
            PokeParam = Handler_GetBattleMon(a2, v6);
            if (!BattleMon_IsFainted(PokeParam))
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                v8->poke_cnt = 1;
                v8->pokeID[0] = (unsigned int)v6;
                v8->fMoveAnimation = 1;
                v8->rankType = STATSTAGE_SPEED;
                v8->rankVolume = -1;
                v8->pad = STAT_CHANGE_HOSTILE_FLAG;
                BattleHandler_PopWork(a2, v8);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }
    return;
}