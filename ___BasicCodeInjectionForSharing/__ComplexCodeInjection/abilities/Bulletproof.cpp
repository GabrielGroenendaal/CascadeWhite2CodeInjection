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

const u16 BulletproofMoves[21] = {
    MOVE491_ACID_SPRAY,
    MOVE396_AURA_SPHERE,
    MOVE140_BARRAGE,
    MOVE331_BULLET_SEED,
    MOVE121_EGG_BOMB,
    MOVE486_ELECTRO_BALL,
    MOVE412_ENERGY_BALL,
    MOVE411_FOCUS_BLAST,
    MOVE360_GYRO_BALL,
    MOVE301_BOOMBURST,
    MOVE443_MAGNET_BOMB,
    MOVE426_MUD_BOMB,
    MOVE190_OCTAZOOKA,
    MOVE461_POLLEN_PUFF,
    MOVE350_ROCK_BLAST,
    MOVE439_ROCK_WRECKER,
    MOVE402_SEED_BOMB,
    MOVE247_SHADOW_BALL,
    MOVE188_SLUDGE_BOMB,
    MOVE311_WEATHER_BALL,
    MOVE192_ZAP_CANNON};
    
extern "C" void HandlerBulletproof(int a1, ServerFlow *a2, int a3)
{
    HandlerParam_Message *v9;
    if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        // if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_BOMB))//
        if (SEARCH_ARRAY(BulletproofMoves, BattleEventVar_GetValue(VAR_MOVE_ID)))
        {
            BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);

            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
            v9 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
            BattleHandler_StrSetup(&v9->str, 2u, 1246);
            BattleHandler_AddArg(&v9->str, a3);
            BattleHandler_PopWork(a2, v9);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
        }
    }
}

ABILITY_TRIGGERTABLE BulletproofHandlers[] = {
    {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerBulletproof}, // 22
};

// was: THUMB_BRANCH_EventAddDamp
extern "C" ABILITY_TRIGGERTABLE *e06(_DWORD *a1)
{
    *a1 = 1;
    return BulletproofHandlers;
}