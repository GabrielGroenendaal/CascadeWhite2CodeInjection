#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerDistracting(int a1, ServerFlow *a2, int a3)
{
    u8 *TempWork;                     // r4
    u8 NumTargets;                    // r5
    HandlerParam_ChangeStatStage *v7; // r1
    __int16 ExistFrontPokePos;        // [sp+0h] [bp-18h]

    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            TempWork = Handler_GetTempWork(a2);
            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, TempWork);
            if (NumTargets)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);

                v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                // v7->header.flags |= 0x08000000;
                v7->rankType = STATSTAGE_EVASION;
                v7->rankVolume = -1;
                v7->fMoveAnimation = 1;
                v7->poke_cnt = NumTargets;
                for (u8 frontCurrent = 0; frontCurrent < NumTargets; ++frontCurrent)
                {
                    v7->pokeID[frontCurrent] = TempWork[frontCurrent];
                }
                v7->pad = VAR_HOSTILEFLAG;
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }
}

ABILITY_TRIGGERTABLE DistractingHandlers[] = {
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerDistracting},            // 41
    {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerDistracting}, // 41
};
// was: THUMB_BRANCH_EventAddKlutz
extern "C" ABILITY_TRIGGERTABLE *e67(_DWORD *a1)
{
    *a1 = 2;
    return DistractingHandlers;
}