#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerSavant(int a1, ServerFlow *serverFlow, int pokemonSlot)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
    {
        BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

        MoveParam params;
        ServerEvent_GetMoveParam(serverFlow, BattleEventVar_GetValue(VAR_MOVE_ID), (int)currentMon, &params);

        if (params.moveType != TYPE_NONE &&
            PokeTypePair_MakeMonotype(params.moveType) != BattleMon_GetPokeType(currentMon))
        {
            if (!BattleMon_CheckIfMoveCondition(currentMon, CONDITION_TERA))
            {
                BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);

                HandlerParam_ChangeType *changeType;
                changeType = (HandlerParam_ChangeType *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_TYPE, pokemonSlot);
                changeType->nextType = PokeTypePair_MakeMonotype(params.moveType);
                changeType->monID = pokemonSlot;
                BattleHandler_PopWork(serverFlow, changeType);

                BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
            }
        }
    }
}

ABILITY_TRIGGERTABLE SavantHandlers[] = {
    {EVENT_MOVE_EXECUTE_CHECK2, (ABILITY_HANDLER_FUNC)HandlerSavant}, // 22
};

extern "C" ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddBigPecks(_DWORD *a1)
{
    *a1 = 1;
    return SavantHandlers;
}
