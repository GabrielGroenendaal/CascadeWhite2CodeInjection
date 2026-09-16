#include "../definitions/A_CodeInjection.h"

/* Ice Body Buff*/
extern "C" void HandlerIceBody(int a1, ServerFlow *a2, int a3)
{
    BattleMon *PokeParam;       // r7
    HandlerParam_RecoverHP *v8; // r5
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        PokeParam = Handler_GetBattleMon(a2, a3);
        v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
        v8->header.flags |= 0x800000u;
        v8->pokeID = a3;
        v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, ((Handler_GetWeather((int)a2) == 3) ? 0x8u : 0x10u));
        BattleHandler_PopWork(a2, v8);
    }
}

ABILITY_TRIGGERTABLE IceBodyHandlers[] = {
    {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 22
    {EVENT_TURN_CHECK_BEGIN, (ABILITY_HANDLER_FUNC)HandlerIceBody},
};

// was: THUMB_BRANCH_EventAddIceBody
extern "C" ABILITY_TRIGGERTABLE *e73(_DWORD *a1)
{
    *a1 = 2;
    return IceBodyHandlers;
}
