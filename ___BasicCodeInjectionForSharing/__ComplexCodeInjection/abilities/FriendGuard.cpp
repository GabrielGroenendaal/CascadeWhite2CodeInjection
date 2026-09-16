#include "../definitions/A_CodeInjection.h"

ABILITY_TRIGGERTABLE FriendGuardHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerFriendGuard}, // 0
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}};

// was: THUMB_BRANCH_EventAddFriendGuard
extern "C" ABILITY_TRIGGERTABLE *e84(_DWORD *a1)
{
    *a1 = 2;
    return FriendGuardHandlers;
}