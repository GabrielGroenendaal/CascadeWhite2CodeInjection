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

const u16 HyperCutterMoves[28] = {
    MOVE421_SHADOW_CLAW, MOVE533_SACRED_SWORD, MOVE534_RAZOR_SHELL, MOVE530_DUAL_CHOP, MOVE529_DRILL_RUN, MOVE554_SOLAR_BLADE,
    MOVE440_CROSS_POISON, MOVE427_PSYCHO_CUT, MOVE404_X_SCISSOR, MOVE400_NIGHT_SLASH, MOVE403_AIR_SLASH, MOVE384_PSYBLADE,
    MOVE348_LEAF_BLADE, MOVE337_DRAGON_CLAW, MOVE332_AERIAL_ACE, MOVE314_AIR_CUTTER, MOVE306_CRUSH_CLAW, MOVE232_METAL_CLAW,
    MOVE163_SLASH, MOVE154_FURY_SWIPES, MOVE065_DRILL_PECK, MOVE013_RAZOR_WINDS, MOVE210_FURY_CUTTER, MOVE015_CUT,
    MOVE075_RAZOR_LEAF, MOVE548_SECRET_SWORD, MOVE032_HORN_DRILL, MOVE064_AQUA_CUTTER};

extern "C" void HandlerHyperCutterDamage(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        if (SEARCH_ARRAY(HyperCutterMoves, BattleEventVar_GetValue(VAR_MOVE_ID)))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
        }
    }
}

ABILITY_TRIGGERTABLE hyperCutterHandlers[] = {
    {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerHyperCutterDamage}, // 22
    {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerHyperCutterCheck},
    {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerHyperCutterGuard}};

// was: THUMB_BRANCH_EventAddHyperCutter
extern "C" ABILITY_TRIGGERTABLE *e34(_DWORD *a1)
{
    *a1 = 3;
    return hyperCutterHandlers;
}