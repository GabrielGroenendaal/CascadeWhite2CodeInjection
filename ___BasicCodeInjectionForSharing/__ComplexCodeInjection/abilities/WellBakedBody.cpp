#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerWellBakedBody(int a1, ServerFlow *a2, int a3)
{
    if (CommonDamageRecoverCheck(a2, a3, TYPE_FIRE))
    {
        CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_DEFENSE, 2);
    }
}

ABILITY_TRIGGERTABLE WellBakedBodyHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerWellBakedBody}, // 22
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSuctionCups(_DWORD *a1)
{
    *a1 = 1;
    return WellBakedBodyHandlers;
}
