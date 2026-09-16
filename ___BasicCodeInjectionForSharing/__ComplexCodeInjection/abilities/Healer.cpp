#include "../definitions/A_CodeInjection.h"

extern "C" int HandlerNewHealer(int a1, ServerFlow *a2, unsigned int a3, int a4)
{

    u8 NumTargets;            // r0
    __int16 v7;               // r0
    u8 currentTarget;         // r4
    u8 currentTargetPosition; // r1
    BattleMon *battleMon;     // r0
    BattleMon *Ally;
    HandlerParam_RecoverHP *v6; // r5
    u8 v13[5];                  // [sp+4h] [bp-1Ch] BYREF
    int v14;                    // [sp+8h] [bp-18h]

    NumTargets = BattleEventVar_GetValue(VAR_MON_ID);
    v14 = a4;
    if (a3 == NumTargets)
    {
        battleMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_MON_ID));
        if (!BattleMon_IsFullHP(battleMon))
        {
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
            v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
            v6->pokeID = a3;
            v6->recoverHP = DivideMaxHPZeroCheck(battleMon, 0x10u);
            BattleHandler_PopWork(a2, v6);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
        }
        v7 = Handler_PokeIDToPokePos(a2, a3);
        NumTargets = Handler_ExpandPokeID(a2, v7 | 0x700, v13);
        for (currentTarget = 0; currentTarget < NumTargets; currentTarget++)
        {
            currentTargetPosition = v13[currentTarget];
            Ally = Handler_GetBattleMon(a2, currentTargetPosition);
            if (!BattleMon_IsFullHP(Ally) && Ally->ID != battleMon->ID)
            {
                v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, currentTargetPosition);
                v6->pokeID = currentTargetPosition;
                v6->recoverHP = DivideMaxHPZeroCheck(Ally, 0x10u);
                BattleHandler_PopWork(a2, v6);
            }
        }
    }
    return NumTargets;
}

ABILITY_TRIGGERTABLE HealerHandlers[] = {
    {EVENT_TURN_CHECK_BEGIN, (ABILITY_HANDLER_FUNC)HandlerNewHealer},        // 4
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}, // 5
};

// was: THUMB_BRANCH_EventAddHealer
extern "C" ABILITY_TRIGGERTABLE *e83(_DWORD *a1)
{
    *a1 = 2;
    return HealerHandlers;
}