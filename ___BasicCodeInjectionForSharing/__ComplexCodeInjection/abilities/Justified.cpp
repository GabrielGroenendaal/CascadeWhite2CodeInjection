#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerJustifiedDefense(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if ( BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_DARK)
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
    }

    ABILITY_TRIGGERTABLE JustifiedHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerJustified}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerJustifiedDefense},  // 22
    };

    // was: THUMB_BRANCH_EventAddJustified
    extern "C" ABILITY_TRIGGERTABLE *e9a(_DWORD *a1)
    {
        *a1 = 2;
        return JustifiedHandlers;
    }