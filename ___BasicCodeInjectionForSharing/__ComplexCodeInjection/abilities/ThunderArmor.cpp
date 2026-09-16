#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerThunderArmor(int a1, ServerFlow *a2, int a3)
{
    if (CommonDamageRecoverCheck(a2, a3, TYPE_ELECTRIC))
    {
        CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
    }
}

ABILITY_TRIGGERTABLE ThunderArmorHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerThunderArmor}, // 22
};

// was: THUMB_BRANCH_EventAddInsomnia
extern "C" ABILITY_TRIGGERTABLE *e0f(_DWORD *a1)
{
    *a1 = 1;
    return ThunderArmorHandlers;
}
