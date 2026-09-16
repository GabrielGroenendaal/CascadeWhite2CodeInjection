#include "_preStatus.h"

extern "C" void HandlerPreStatusForGuts(int a1, ServerFlow *a2, int a3)
{
    HandlerParam_AddCondition *v6;
    BattleMon *PokeParam; // r7

    if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
    {
        PokeParam = Handler_GetBattleMon(a2, a3);
        u8 condition;
        u8 textId;

        if (PokeParam->Species == PK377_REGIROCK)
        {
            condition = CONDITION_PARALYSIS;
        }
        else
        {
            condition = ((BattleMon_HasType(PokeParam, TYPE_FIRE)) ? ((PokeParam->Sex == 0) ? CONDITION_POISON : CONDITION_PARALYSIS) : ((PokeParam->Sex == 0) ? CONDITION_BURN : CONDITION_PARALYSIS));
        }
        triggerPreStatus(a2, a3, (MoveCondition)condition);
    }
}
ABILITY_TRIGGERTABLE GutsHandlers[] = {
    {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerGuts},        // 11
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreStatusForGuts}, // 12

};

// was: THUMB_BRANCH_EventAddGuts
extern "C" ABILITY_TRIGGERTABLE *e3e(_DWORD *a1)
{
    *a1 = 2;
    return GutsHandlers;
}