#include "../definitions/A_CodeInjection.h"

extern "C" u8 SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u16 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)  return 1;
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

const u16 WindMoves[17] = {
    MOVE403_AIR_SLASH,
    MOVE542_HURRICANE,
    MOVE257_HEAT_WAVE,
    MOVE466_OMINOUS_WIND,
    MOVE318_SILVER_WIND,
    MOVE016_GUST,
    MOVE059_BLIZZARD,
    MOVE379_PETAL_BLIZZARD,
    MOVE511_FAIRY_WIND,
    MOVE180_DIAMOND_STORM,
    MOVE013_RAZOR_WINDS,
    MOVE177_AEROBLAST,
    MOVE196_ICY_WIND,
    MOVE366_TAILWIND,
    MOVE239_TWISTER,
    MOVE018_WHIRLWIND,
    MOVE314_AIR_CUTTER};

extern "C" void HandlerWindRiderTailwind(int a1, ServerFlow *a2, int a3)
{
    // HandlerParam_Message *v9;
    if ((BattleEventVar_GetValue(VAR_MON_ID) == a3 || MainModule_IsAllyMonID(a3, BattleEventVar_GetValue(VAR_MON_ID))) && BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE366_TAILWIND)
    {
        CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
    }
    // if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
    // {
    //     if (isInArray(BattleEventVar_GetValue(VAR_MOVE_ID), 1))
    //     {
    //         BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
    //         CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
    //     }
    // }
}

extern "C" void HandlerWindRider(int a1, ServerFlow *a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        // if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_WIND))
        if (SEARCH_ARRAY(WindMoves, BattleEventVar_GetValue(VAR_MOVE_ID)))
        {
            BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        }
    }
}
ABILITY_TRIGGERTABLE WindRiderHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerWindRider}, // 22
    {EVENT_MOVE_EXECUTE_END, (ABILITY_HANDLER_FUNC)HandlerWindRiderTailwind}};

// was: THUMB_BRANCH_EventAddKeenEye
extern "C" ABILITY_TRIGGERTABLE *e33(_DWORD *a1)
{
    *a1 = 2;
    return WindRiderHandlers;
}
