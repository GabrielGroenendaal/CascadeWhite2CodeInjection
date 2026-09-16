
#include "../definitions/A_CodeInjection.h"

extern "C" void RivalryOffense(int a1, ServerFlow *a2, int a3)
{
    BattleMon *attackingMon; // r4
    unsigned __int8 Value;   // r0
    BattleMon *defendingMon; // r5
    int v8;                  // r4
    int v9;                  // r0

    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        attackingMon = Handler_GetBattleMon(a2, a3);
        defendingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON));
        v8 = BattleMon_GetPokeType(attackingMon);
        v9 = BattleMon_GetPokeType(defendingMon);

        if (PokeTypePair_HasSharedType(v8, v9))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5448);
        }
    }
}

extern "C" void RivalryDefense(int a1, ServerFlow *a2, int a3)
{
    BattleMon *attackingMon; // r4
    unsigned __int8 Value;   // r0
    BattleMon *defendingMon; // r5
    int v8;                  // r4
    int v9;                  // r0

    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        defendingMon = Handler_GetBattleMon(a2, a3);
        attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
        v8 = BattleMon_GetPokeType(attackingMon);
        v9 = BattleMon_GetPokeType(defendingMon);

        if (PokeTypePair_HasSharedType(v8, v9))
        {
            BattleEventVar_MulValue(VAR_RATIO, 2730);
        }
    }
}

ABILITY_TRIGGERTABLE RivalryHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)RivalryOffense},               // 41
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)RivalryDefense}, // 41
};

// was: THUMB_BRANCH_EventAddRivalry
extern "C" ABILITY_TRIGGERTABLE *e4f(_DWORD *a1)
{
    *a1 = 2;
    return RivalryHandlers;
}