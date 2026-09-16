#include "../definitions/A_CodeInjection.h"

extern "C" u8 SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u16 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)
            return 1;
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

const u16 StrongJawMoves[12] = {
    MOVE044_BITE,
    MOVE158_HYPER_FANG,
    MOVE162_SUPER_FANG,
    MOVE170_SNAP_TRAP,
    MOVE265_PSYCHIC_FANGS,
    MOVE305_POISON_FANG,
    MOVE422_THUNDER_FANG,
    MOVE423_ICE_FANG,
    MOVE424_FIRE_FANG,
    MOVE242_CRUNCH,
    MOVE141_LEECH_LIFE,
    MOVE030_DEVOUR};



extern "C" void HandlerStrongJaw(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (SEARCH_ARRAY(StrongJawMoves, (MoveID)BattleEventVar_GetValue(VAR_MOVE_ID)))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 6144);
        }
    }
}
ABILITY_TRIGGERTABLE StrongJawHandlers[]{
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerStrongJaw},
};

// was: THUMB_BRANCH_EventAddHydration
extern "C" ABILITY_TRIGGERTABLE *e5d(u32 *handlerAmount)
{
    *handlerAmount = 1;
    return StrongJawHandlers;
}