#include "../definitions/A_CodeInjection.h"


// RKS System 
extern "C" void HandlerRKSSystem(BattleEventItem * item, ServerFlow * serverFlow, u32 pokemonSlot, u32 * work) {
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID)) {
        BattleMon* currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
        u8 type = PokeTypePair_GetType1(BattleMon_GetPokeType(currentMon));
        u8 moveType = PML_MoveGetType(Move_GetID(currentMon, 0));
        if (type != moveType){
            HandlerParam_ChangeForm* changeForm;
            changeForm = (HandlerParam_ChangeForm*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
            changeForm->header.flags |= 0x800000;
            changeForm->monID = pokemonSlot;
            changeForm->form = moveType;
            BattleHandler_StrSetup(&changeForm->strParam, 1u, 230); // CHANGE THIS MESSAGE ID
            BattleHandler_AddArg(&changeForm->strParam, pokemonSlot);
            BattleHandler_PopWork(serverFlow, changeForm);
        }
    }
}
ABILITY_TRIGGERTABLE RKSHandlers[]{
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerRKSSystem},
    {EVENT_TURN_CHECK_DONE, (ABILITY_HANDLER_FUNC)HandlerRKSSystem},
};
extern "C" ABILITY_TRIGGERTABLE * THUMB_BRANCH_EventAddColorChange(_DWORD * a1) {
    *a1 = 2;
    return RKSHandlers;
}
