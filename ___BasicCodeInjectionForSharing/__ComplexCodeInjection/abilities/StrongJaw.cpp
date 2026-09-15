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

extern "C" void THUMB_BRANCH_HandlerSuperFang(int a1, ServerFlow *a2, int a3)
{
    unsigned __int8 Value; // r0
    BattleMon *BattleMon;  // r0
    unsigned int v8;       // r0
    int v9;                // r1

    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        BattleMon = Handler_GetBattleMon(a2, Value);
        v8 = BattleMon_GetValue(BattleMon, VALUE_CURRENT_HP);
        v9 = (v8 + (v8 >> 31)) << 15 >> 16;
        if (!v9)
        {
            v9 = 1;
        }
        if (BattleMon_GetValue(Handler_GetBattleMon(a2, a3), VALUE_EFFECTIVE_ABILITY) == ABIL093_STRONG_JAW)
        {
            v9 = v9 + (v9 >> 1);
        }
        BattleEventVar_RewriteValue(VAR_FIXED_DAMAGE, v9);
    }
}

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

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHydration(u32 *handlerAmount)
{
    *handlerAmount = 1;
    return StrongJawHandlers;
}