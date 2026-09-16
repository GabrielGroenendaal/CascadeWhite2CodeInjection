#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerDefiant(int a1, ServerFlow *a2, unsigned int a3)
{
    unsigned __int8 Value;             // r0
    HandlerParam_ChangeStatStage *v13; // r0

    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        Value = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        // k::Printf("Defiant Handler: The INTIM flag is %d\nAnd the Hostile flag is %d\n", BattleEventVar_GetValue(VAR_INTIMFLAG), BattleEventVar_GetValue(VAR_HOSTILEFLAG));
        if ((BattleEventVar_GetValue(VAR_INTIMFLAG) || BattleEventVar_GetValue(VAR_HOSTILEFLAG) || !MainModule_IsAllyMonID(a3, Value)) && BattleEventVar_GetValue(VAR_VOLUME) < 0)
        {
            v13 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
            v13->header.flags |= 0x800000u;
            v13->rankType = STATSTAGE_ATTACK;
            v13->rankVolume = 2;
            v13->fMoveAnimation = 1;
            v13->poke_cnt = 1;
            v13->pokeID[0] = a3;
            BattleHandler_PopWork(a2, v13);
        }
    }
}

ABILITY_TRIGGERTABLE DefiantHandlers[] = {
    {EVENT_STAT_STAGE_CHANGE_APPLIED, (ABILITY_HANDLER_FUNC)HandlerDefiant}, // 15
};


// was: EventAddDefiantNew
extern "C" ABILITY_TRIGGERTABLE * e80(_DWORD *a1)
{
  *a1 = 1;
  return DefiantHandlers;
}
