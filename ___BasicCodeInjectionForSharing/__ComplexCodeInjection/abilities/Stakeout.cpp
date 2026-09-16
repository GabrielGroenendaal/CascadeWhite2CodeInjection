#include "../definitions/A_CodeInjection.h"

extern "C" bool SwitchedInThisTurn(ServerFlow *serverFlow, BattleMon *battleMon, int defendingSlot)
{
    // int *ActionOrderAttackingMon;
    // int *ActionOrderDefendingMon;
    // // if (serverFlow->turnCount == 0) {
    // //     for (u8 i = 0; i < 6; ++i) {
    // //         if (g_BattleField->firstTurnMons[i] == battleMon->ID) {
    // //             // A Pokémon that started the battle doesn't count as just switched in
    // //             return 0;
    // //         }
    // //     }
    // // }
    // ActionOrderAttackingMon = ActionOrder_SearchByMonID(a1, AttackingMon->ID);
    // ActionOrderDefendingMon = ActionOrder_SearchByMonID(a1, DefendingMon->ID);

    // if (ActionOrderAttackingMon > ActionOrderDefendingMon)
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    unsigned int v11[6];
    return !battleMon->TurnCount && !Handler_GetThisTurnAction(serverFlow, defendingSlot, v11);
}

extern "C" void HandlerStakeout(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        BattleMon *attackingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

        u32 defendingSlot = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, defendingSlot);

        if (SwitchedInThisTurn(serverFlow, defendingMon, defendingSlot))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
        }
    }
}
ABILITY_TRIGGERTABLE StakeoutHandlers[]{
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerStakeout},
};

// was: THUMB_BRANCH_EventAddFrisk
extern "C" ABILITY_TRIGGERTABLE *e77(_DWORD *a1)
{
    *a1 = 1;
    return StakeoutHandlers;
}