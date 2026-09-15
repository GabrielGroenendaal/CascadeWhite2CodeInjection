
#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerRattledIntimidateCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (BattleEventVar_GetValue(VAR_INTIMFLAG))
        {
            work[0] = 1;
        }
        else
        {
            work[0] = 0;
        }
    }
}

extern "C" void HandlerRattledIntimidate(int a1, ServerFlow *a2, int a3, u32 *work)
{
    HandlerParam_ChangeStatStage *v13; // r0
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && work[0])
    {
        work[0] = 0;
        v13 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
        v13->header.flags |= 0x800000u;
        v13->rankType = STATSTAGE_SPEED;
        v13->rankVolume = 3;
        v13->fMoveAnimation = 1;
        v13->poke_cnt = 1;
        v13->pokeID[0] = a3;
        BattleHandler_PopWork(a2, v13);
    }
}
extern "C" void THUMB_BRANCH_HandlerRattled(int a1, ServerFlow *a2, int a3)
{
    int Value;                        // r0
    HandlerParam_ChangeStatStage *v6; // r0
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
    {
        Value = (unsigned __int8)BattleEventVar_GetValue(VAR_MOVE_TYPE);
        if (Value == TYPE_DARK || Value == TYPE_BUG || Value == TYPE_GHOST)
        {
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
            v6->header.flags |= 0x800000u;
            v6->poke_cnt = 1;
            v6->pokeID[0] = a3;
            v6->rankType = STATSTAGE_SPEED;
            v6->rankVolume = 3;
            BattleHandler_PopWork(a2, v6);
        }
    }
}

ABILITY_TRIGGERTABLE RattledHandlers[] = {
    {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerRattled}, // 22
    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerRattledIntimidateCheck},
    {EVENT_STAT_STAGE_CHANGE_APPLIED, (ABILITY_HANDLER_FUNC)HandlerRattledIntimidate}};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRattled(_DWORD *a1)
{
    *a1 = 3;
    return RattledHandlers;
}