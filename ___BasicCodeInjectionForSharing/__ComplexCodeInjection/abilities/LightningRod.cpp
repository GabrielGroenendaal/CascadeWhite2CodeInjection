#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerNewLightningRod(int a1, ServerFlow *a2, int a3)
{
    if (CommonDamageRecoverCheck(a2, a3, TYPE_ELECTRIC))
    {
        CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_SPECIAL_ATTACK, 1);
    }
}

ABILITY_TRIGGERTABLE LightningRodHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerNewLightningRod}, // 22
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLightningRod(_DWORD *a1)
{
    *a1 = 1;
    return LightningRodHandlers;
}