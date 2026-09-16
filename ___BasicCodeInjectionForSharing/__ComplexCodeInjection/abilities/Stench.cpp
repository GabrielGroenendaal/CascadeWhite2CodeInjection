#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerStenchNew(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (!BattleEventVar_GetValue(VAR_DEFAULT_EFFECT_CHANCE))
        {
            BattleEventVar_RewriteValue(VAR_EFFECT_CHANCE, 20);
        }
    }
}


ABILITY_TRIGGERTABLE StenchHandlers[] = {
    {EVENT_MOVE_FLINCH_CHANCE, (ABILITY_HANDLER_FUNC)HandlerStenchNew}, // 22

};

// was: EventAddStenchNew
extern "C" ABILITY_TRIGGERTABLE * e01(_DWORD *a1)
{
    *a1 = 1;
    return StenchHandlers;
}