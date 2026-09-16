#include "../definitions/A_CodeInjection.h"

void HandlerEffectSporeNew(int a1, ServerFlow *a2, unsigned int *a3)
{
    u8 v5;            // r0
    MoveCondition v6; // r4
    ConditionData v7; // r0
    BattleMon *mon;
    HandlerParam_AddCondition *v9; // r5
    if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
    {
        mon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
        if (!BattleMon_HasType(mon, TYPE_GRASS) && BattleMon_GetHeldItem(mon) != IT0293_SAFETY_GOGGLES && BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT)
        {
            v5 = BattleRandom(30u);
            if (v5 <= 20)
            {
                v6 = CONDITION_PARALYSIS;
                if (v5 <= 10)
                {
                    v6 = CONDITION_SLEEP;
                }
            }
            else
            {
                v6 = CONDITION_POISON;
            }
            v7.raw = MakeBasicStatus(v6).raw;
            if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
            {
                v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v9->header.flags |= 0x800000u;
                v9->sickID = v6;
                v9->sickCont = v7;
                v9->fAlmost = 0;
                v9->pokeID = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleHandler_PopWork(a2, v9);
            }
        }
    }
}

ABILITY_TRIGGERTABLE EffectSporeHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerEffectSporeNew}, // 22

};

// was: EventAddEffectSporeNew
extern "C" ABILITY_TRIGGERTABLE *e1b(_DWORD *a1)
{
    *a1 = 1;
    return EffectSporeHandlers;
}