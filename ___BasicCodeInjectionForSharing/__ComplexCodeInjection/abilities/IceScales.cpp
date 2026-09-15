#include "../definitions/A_CodeInjection.h"



extern "C" void HandlerIceScales(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) == 2)
    {
        BattleEventVar_MulValue(VAR_RATIO, 2048);
    }
}
ABILITY_TRIGGERTABLE IceScalesHandlers[] = {
    {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerIceScales}, // 22
};
extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddWonderSkin(_DWORD *a1)
{
    *a1 = 1;
    return IceScalesHandlers;
}
