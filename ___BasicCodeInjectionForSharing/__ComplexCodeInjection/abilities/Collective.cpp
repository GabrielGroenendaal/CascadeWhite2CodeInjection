#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerCollective(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
    {
        BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

        //  0: Combee-Male
        //  1: Combee-Female
        //  2: Combee-Collective
        // 23: X -> Z
        // 24: Y -> Unown-Exclamation
        // 25: Z -> Unown-Question
        // 26: ! -> Unown-Exclamation Schooling
        // 27: ? -> Unown-Question Schooling

        u8 currentForm = BattleMon_GetValue(currentMon, VALUE_FORM);
        u8 newForm = currentForm;
        u16 msgID = 264;

        // TODO: ADD WISHIWASHI
        if (BattleMon_GetSpecies(currentMon) == 201)
        {
            u32 currentHP = BattleMon_GetValue(currentMon, VALUE_CURRENT_HP);
            if (currentForm == 24 || currentForm == 25)
            {
                if (currentHP > DivideMaxHPZeroCheck(currentMon, 4u))
                {
                    newForm = currentForm - 2;
                    msgID = 264;
                }
            }
            if (currentForm == 26 || currentForm == 27)
            {
                if (currentHP <= DivideMaxHPZeroCheck(currentMon, 4u))
                {
                    newForm = currentForm + 2;
                    msgID = 265;
                }
            }
        }

        if (BattleMon_GetSpecies(currentMon) == 415)
        {
            if (BattleMon_GetValue(currentMon, VALUE_SEX) == 0)
            {
                u32 currentHP = BattleMon_GetValue(currentMon, VALUE_CURRENT_HP);
                if (currentForm == 0)
                {
                    if (currentHP > DivideMaxHPZeroCheck(currentMon, 4u))
                    {
                        newForm = currentForm + 2;
                        msgID = 264;
                    }
                }
                if (currentForm == 2)
                {
                    if (currentHP <= DivideMaxHPZeroCheck(currentMon, 4u))
                    {
                        newForm = currentForm - 2;
                        msgID = 265;
                    }
                }
            }
        }

        if (currentForm != newForm)
        {
            HandlerParam_ChangeForm *changeForm;
            changeForm = (HandlerParam_ChangeForm *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
            changeForm->header.flags |= 0x800000;
            changeForm->monID = pokemonSlot;
            changeForm->form = newForm;
            BattleHandler_StrSetup(&changeForm->strParam, 1u, msgID);
            BattleHandler_AddArg(&changeForm->strParam, pokemonSlot);
            BattleHandler_PopWork(serverFlow, changeForm);
        }
    }
}

ABILITY_TRIGGERTABLE CollectiveHandlers[]{
    {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerCollective},
    {EVENT_TURN_CHECK_DONE, (ABILITY_HANDLER_FUNC)HandlerCollective},
};

// was: THUMB_BRANCH_EventAddZenMode
extern "C" ABILITY_TRIGGERTABLE *ea1(_DWORD *a1)
{
    *a1 = 2;
    return CollectiveHandlers;
}