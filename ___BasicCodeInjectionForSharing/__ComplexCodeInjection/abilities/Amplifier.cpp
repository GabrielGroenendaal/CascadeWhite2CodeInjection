#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerAmplifier(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_SOUND))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
        }
    }
}

ABILITY_TRIGGERTABLE AmplifierHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerSoundproof}, // 22
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerAmplifier}};

// was: THUMB_BRANCH_EventAddSoundproof
extern "C" ABILITY_TRIGGERTABLE *e2b(_DWORD *a1)
{
    *a1 = 2;
    return AmplifierHandlers;
}