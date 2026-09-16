#include "../definitions/A_CodeInjection.h"

ABILITY_TRIGGERTABLE PlusMinusHandlers[] = {
    {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerPlusMinus},          // 2
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}, // 3
};
// was: THUMB_BRANCH_EventAddPlusMinus
extern "C" ABILITY_TRIGGERTABLE *e39(_DWORD *a1)
{
    *a1 = 2;
    return PlusMinusHandlers;
}