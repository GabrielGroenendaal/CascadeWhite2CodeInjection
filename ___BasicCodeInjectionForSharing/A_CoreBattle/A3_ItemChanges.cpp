#include "codeinjection_new.h"
#include "kPrint.h"

// Uses esdb_newBattle.yml

extern "C"
{

    typedef struct
    {
        BattleEventType triggerValue;
        ITEM_HANDLER_FUNC function;
    } ITEM_TRIGGERTABLE;

#pragma region WIPBattleItems
    /*


        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        -------------------------------------- NEW BATTLE ITEMS ------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------


    */

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ COVERT CLOAK ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerCovertCloakConditionCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot != BattleEventVar_GetValue(VAR_ATTACKING_MON) && pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            MoveID moveID = (MoveID)BattleEventVar_GetValue(VAR_MOVE_ID);
            if (IsAffectedBySheerForce(moveID))
            {
                BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
    }

    ITEM_TRIGGERTABLE CovertCloakHandlers[] = {
        {EVENT_ADD_CONDITION, (ITEM_HANDLER_FUNC)HandlerCovertCloakConditionCheck},
        {EVENT_ADD_STAT_STAGE_CHANGE_TARGET, (ITEM_HANDLER_FUNC)HandlerCovertCloakConditionCheck},
        {EVENT_FLINCH_CHECK, (ITEM_HANDLER_FUNC)HandlerInnerFocus},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddRingTarget(_DWORD *a1)
    {
        *a1 = 3;
        return CovertCloakHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ MASCOT BADGE ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    bool checkBSTLowerThan400(ServerFlow *serverFlow, u32 pokemonSlot)
    {
        BattleMon *mon = Handler_GetBattleMon(serverFlow, pokemonSlot);

        PersonalData *bw2 = PML_PersonalLoadBW2(mon->Species, mon->Form);
        int bst = PML_PersonalGetParam(bw2, Personal_HP) +
                  PML_PersonalGetParam(bw2, Personal_ATK) +
                  PML_PersonalGetParam(bw2, Personal_DEF) +
                  PML_PersonalGetParam(bw2, Personal_SPA) +
                  PML_PersonalGetParam(bw2, Personal_SPD) +
                  PML_PersonalGetParam(bw2, Personal_SPE);

        k::Printf("\nThe total bst calculated is %d\n", bst);

        if (bst < 400)
        {
            return true;
        }
        return false;
    }

    void HandlerMascotBadgeDefense(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (checkBSTLowerThan400(serverFlow, pokemonSlot))
            {
                BattleEventVar_MulValue(VAR_RATIO, 8192);
            }
        }
    }

    void HandlerMascotBadgeOffense(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (checkBSTLowerThan400(serverFlow, pokemonSlot))
            {
                BattleEventVar_MulValue(VAR_RATIO, 8192);
            }
        }
    }

    void HandlerMascotBadgeSpeed(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (checkBSTLowerThan400(serverFlow, pokemonSlot))
            {
                BattleEventVar_MulValue(VAR_RATIO, 8192);
            }
        }
    }

    ITEM_TRIGGERTABLE MascotBadgeHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ITEM_HANDLER_FUNC)HandlerMascotBadgeDefense},
        {EVENT_ATTACKER_POWER, (ITEM_HANDLER_FUNC)HandlerMascotBadgeOffense},
        {EVENT_CALC_SPEED, (ITEM_HANDLER_FUNC)HandlerMascotBadgeSpeed},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSoulDew(_DWORD *a1)
    {
        *a1 = 3;
        return MascotBadgeHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------- UTILITY UMBRELLA ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerUtilityUmbrella(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        return;
    }

    ITEM_TRIGGERTABLE UtilityUmbrellaHandlers[] = {
        {EVENT_ADD_CONDITION, (ITEM_HANDLER_FUNC)HandlerUtilityUmbrella},
        {EVENT_ADD_STAT_STAGE_CHANGE_TARGET, (ITEM_HANDLER_FUNC)HandlerUtilityUmbrella},
        {EVENT_FLINCH_CHECK, (ITEM_HANDLER_FUNC)HandlerUtilityUmbrella},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddBindingBand(_DWORD *a1)
    {
        *a1 = 3;
        return UtilityUmbrellaHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ CLEAR AMULET ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    // CLEAR AMULET
    void HandlerClearAmuletCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        CommonStatDropGuardCheck(serverFlow, pokemonSlot, work, 8);
    }
    void HandlerClearAmuletMessage(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (*work)
        {
            HandlerParam_Message *message = (HandlerParam_Message *)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
            BattleHandler_StrSetup(&message->str, 2u, 1291);
            BattleHandler_AddArg(&message->str, pokemonSlot);
            BattleHandler_PopWork(serverFlow, message);
        }
        *work = 0;
    }
    ITEM_TRIGGERTABLE ClearAmuletHandlers[] = {
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ITEM_HANDLER_FUNC)HandlerClearAmuletCheck},
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ITEM_HANDLER_FUNC)HandlerClearAmuletMessage},
    };
    ITEM_TRIGGERTABLE *EventAddClearAmulet(u32 *handlerAmount)
    {
        *handlerAmount = 3;
        return ClearAmuletHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ FOCUS BAND --------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerFocusBandNew(int a1, ServerFlow *a2, int a3, int *a4)
    {
        BattleMon *BattleMon; // r0
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsFullHP(BattleMon))
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
                *a4 = 1;
            }
            else
            {
                *a4 = 0;
            }
        }
    }
    
    int HandlerFocusBandAfter(BattleEventItem *a1, ServerFlow *a2, int a3, int **a4)
    {
        int result;                   // r0
        HandlerParam_ConsumeItem *v8; // r7
        int SubID;                    // r0

        if (*a4)
        {

            v8 = (HandlerParam_ConsumeItem *)BattleHandler_PushWork(a2, EFFECT_CONSUMEITEM, a3);
            BattleHandler_StrSetup(&v8->exStr, 2u, 0xDBu);
            BattleHandler_AddArg(&v8->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v8->exStr, SubID);
            BattleHandler_PopWork(a2, v8);
            result = 0;
            *a4 = 0;
        }
        return result;
    }

    ITEM_TRIGGERTABLE FocusBandHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerFocusBandNew},
        {EVENT_AFTER_DAMAGE_REACTION, (ITEM_HANDLER_FUNC)HandlerFocusBandAfter},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddFocusBand(_DWORD *a1)
    {
        *a1 = 2;
        return FocusBandHandlers;
    }
    /*

        --------------------------------------------------------------------------------------------------
        -------------------------------------- EJECT PACK ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerEjectPackStatCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID) &&
            BattleEventVar_GetValue(VAR_VOLUME) < 0)
        {
            work[0] = 1;
        }
    }
    void HandlerEjectPackActionEnd(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID) &&
            work[0] == 1)
        {
            work[0] = 0;
            if (Handler_GetFightEnableBenchPokeNum(serverFlow, pokemonSlot) && Handler_CheckReservedMemberChangeAction(serverFlow))
            {
                ItemEvent_PushRun(item, serverFlow, pokemonSlot);
            }
        }
    }
    void HandlerEjectPackUse(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            HandlerParam_Switch *switchOut;
            switchOut = (HandlerParam_Switch *)BattleHandler_PushWork(serverFlow, EFFECT_SWITCH, pokemonSlot);
            switchOut->pokeID = pokemonSlot;
            BattleHandler_PopWork(serverFlow, switchOut);
        }
    }
    ITEM_TRIGGERTABLE EjectPackHandlers[] = {
        {EVENT_STAT_STAGE_CHANGE_APPLIED, (ITEM_HANDLER_FUNC)HandlerEjectPackStatCheck},
        {EVENT_ACTION_PROCESSING_END, (ITEM_HANDLER_FUNC)HandlerEjectPackActionEnd},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerEjectPackUse},
    };
    extern "C" ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddFloatStone(u32 *handlerAmount)
    {
        *handlerAmount = 3;
        return EjectPackHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ PROTECTIVE GEAR ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerProtectiveGear(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        return;
    }

    ITEM_TRIGGERTABLE ProtectiveGearHandlers[] = {
        {EVENT_ADD_CONDITION, (ITEM_HANDLER_FUNC)HandlerProtectiveGear},
        {EVENT_ADD_STAT_STAGE_CHANGE_TARGET, (ITEM_HANDLER_FUNC)HandlerProtectiveGear},
        {EVENT_FLINCH_CHECK, (ITEM_HANDLER_FUNC)HandlerProtectiveGear},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSmokeBall(_DWORD *a1)
    {
        *a1 = 3;
        return ProtectiveGearHandlers;
    }

#pragma endregion

    /*


























    */

#pragma region WeatherMoves

    void HandlerSolarBeamPowerNew(int a1, int a2, int a3)
    {
        BattleMon *attackingMon;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);

            if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != 34 && BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != 94 && BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != 122 && (Handler_GetWeather(a2) - 2) <= 2u)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
            }
        }
    }

    int HandlerSolarBeamSunCheckNew(int a1, int a2, int a3)
    {
        int result; // r0
        BattleMon *attackingMon;

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);

            if (Handler_GetWeather(a2) == 1 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 34 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 94 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 122)
            {
                if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT && attackingMon->HeldItem != IT0544_UTILITY_UMBRELLA)
                {
                    return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
                }
            }
        }
        return result;
    }

    int HandlerGrowthNew(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r1
        BattleMon *attackingMon;

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);
            result = Handler_GetWeather(a2);
            if (result == 1 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 34 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 94 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 122)
            {
                if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT && attackingMon->HeldItem != IT0544_UTILITY_UMBRELLA)
                {
                    Value = BattleEventVar_GetValue(VAR_VOLUME);
                    if (Value == 1)
                    {
                        Value = 2;
                    }
                    return BattleEventVar_RewriteValue(VAR_VOLUME, Value);
                }
            }
        }
        return result;
    }

    int HandlerSynthesis(int a1, int a2, int a3)
    {
        int result;           // r0
        unsigned int Weather; // r0
        int v7;               // r1
        BattleMon *attackingMon;

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            attackingMon = Handler_GetBattleMon((ServerFlow *)a2, a3);
            Weather = Handler_GetWeather(a2);

            if (Weather == 1 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 34 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 94 || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == 122)
            {
                if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT && attackingMon->HeldItem != IT0544_UTILITY_UMBRELLA)
                {
                    v7 = 2732;
                }
            }
            else if (Weather == 2 || Weather == 3 || Weather == 4)
            {
                v7 = 1024;
            }
            else
            {
                v7 = 2048;
            }
            return BattleEventVar_RewriteValue(VAR_RATIO, v7);
        }
        return result;
    }
    typedef struct
    {
        BattleEventType triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;
    MOVE_TRIGGERTABLE SolarBeamHandlers[] = {
        {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerSolarBeamSunCheckNew},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerSolarBeamCharge},
        {EVENT_MOVE_POWER, (MOVE_HANDLER_FUNC)HandlerSolarBeamPowerNew}};

    MOVE_TRIGGERTABLE SynthesisHandlers[] = {
        {EVENT_RECOVER_HP, (MOVE_HANDLER_FUNC)HandlerSynthesis},
    };

    MOVE_TRIGGERTABLE GrowthHandlers[] = {
        {EVENT_GET_STAT_STAGE_CHANGE_VALUE, (MOVE_HANDLER_FUNC)HandlerGrowthNew},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSolarBeam(_DWORD *a1)
    {
        *a1 = 3;
        return SolarBeamHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSynthesis(_DWORD *a1)
    {
        *a1 = 1;
        return SynthesisHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddGrowth(_DWORD *a1)
    {
        *a1 = 1;
        return GrowthHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ ELECTRO SHOT ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    int HandlerElectroShotRain(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            result = Handler_GetWeather(a2);
            if (result == 2)
            {
                return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
        }
        return result;
    }

    void HandlerElectroShotCharge(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 866);
            BattleHandler_AddArg(&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    MOVE_TRIGGERTABLE ElectroShotHandlers[] = {
        {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerElectroShotRain},
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerElectroShotCharge},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddForesight(_DWORD *a1)
    {
        *a1 = 2;
        return ElectroShotHandlers;
    }

    int HandlerThunderRainCheck(ServerFlow *a1, int a2, int a3)
    {
        int result; // r0
        BattleMon *mon;
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            mon = Handler_GetBattleMon(a1, a3);
            result = Handler_GetWeather(a2);
            if (result == 2 && mon->HeldItem != IT0544_UTILITY_UMBRELLA && BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT)
            {
                return BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
        }
        return result;
    }

    int HandlerThunderSunCheck(ServerFlow *a1, int a2, int a3)
    {
        int result; // r0
        BattleMon *mon;
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            mon = Handler_GetBattleMon(a1, a3);

            result = Handler_GetWeather(a2);
            if (result == 1 && mon->HeldItem != IT0544_UTILITY_UMBRELLA && BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT)
            {
                return BattleEventVar_RewriteValue(VAR_ACCURACY, 50);
            }
        }
        return result;
    }

    MOVE_TRIGGERTABLE ThunderHandlers[] = {
        {EVENT_CHECK_HIDING, (MOVE_HANDLER_FUNC)HandlerThunderFlyCheck},
        {EVENT_BYPASS_ACCURACY_CHECK, (MOVE_HANDLER_FUNC)HandlerThunderRainCheck},
        {EVENT_MOVE_ACCURACY, (MOVE_HANDLER_FUNC)HandlerThunderSunCheck}};
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddThunder(_DWORD *a1)
    {
        *a1 = 3;
        return ThunderHandlers;
    }

#pragma endregion

/*
































*/
#pragma region BattleItems

    bool overrideContact(BattleMon *a1, MoveID a2)
    {
        if (BattleMon_GetHeldItem(a1) == IT0228_PROTECTIVE_GEAR || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            return true;
        if (BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL089_IRON_FIST && getMoveFlag(a2, FLAG_PUNCH))
            return true;
        return false;
    }

    void THUMB_BRANCH_HandlerRockyHelmet(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;  // r0
        HandlerParam_Damage *v7; // r4
        BattleMon *attackingMon;
        BattleMon *BattleMon;      // r6
        unsigned __int8 ItemParam; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
                if (overrideContact(attackingMon, (MoveID)Value))
                    return;

                v7 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                v7->pokeID = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v7->pokeID);
                ItemParam = CommonGetItemParam(a1, ITSTAT_USE_PARAM);
                v7->damage = DivideMaxHPZeroCheck(BattleMon, ItemParam);
                BattleHandler_StrSetup(&v7->exStr, 2u, 424);
                BattleHandler_AddArg(&v7->exStr, v7->pokeID);
                BattleHandler_PopWork(a2, v7);
            }
        }
    }
    /*

        ----------------------------------------------------------------------------------------------------
        ------------------------------------- MARANGA BERRY ------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerMarangaBerryDamageReaction(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 2)
        {
            BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            // if (IsModifyItemMove((MoveID)BattleEventVar_GetValue(VAR_MOVE_ID), BattleMon_GetHeldItem(defendingMon))) // CHECK ITEM IS NOT KNOCKED OFF OR CHANGED
            //     return;

            if (BattleMon_IsStatChangeValid(defendingMon, STATSTAGE_SPECIAL_DEFENSE, 1))
            {
                ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
            }
        }
    }

    void HandlerMarangaBerryUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *spDefenseBoost;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            spDefenseBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            spDefenseBoost->poke_cnt = 1;
            spDefenseBoost->pokeID[0] = (u8)pokemonSlot;
            spDefenseBoost->rankType = STATSTAGE_SPECIAL_DEFENSE;
            spDefenseBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, spDefenseBoost);
        }
    }

    ITEM_TRIGGERTABLE MarangaBerryHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerMarangaBerryDamageReaction},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerMarangaBerryUse},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerMarangaBerryUse},
    };

    ITEM_TRIGGERTABLE *EventAddWikiBerry(int *a1)
    {
        *a1 = ARRAY_COUNT(MarangaBerryHandlers);
        return MarangaBerryHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        ---------------------------------------- KEE BERRY -------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerKeeBerryDamageReaction(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1)
        {
            BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            // if (IsModifyItemMove((MoveID)BattleEventVar_GetValue(VAR_MOVE_ID), BattleMon_GetHeldItem(defendingMon))) // CHECK ITEM IS NOT KNOCKED OFF OR CHANGED
            //     return;

            if (BattleMon_IsStatChangeValid(defendingMon, STATSTAGE_DEFENSE, 1))
            {
                ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
            }
        }
    }

    void HandlerKeeBerryUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *defenseBoost;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            defenseBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            defenseBoost->poke_cnt = 1;
            defenseBoost->pokeID[0] = (u8)pokemonSlot;
            defenseBoost->rankType = STATSTAGE_DEFENSE;
            defenseBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, defenseBoost);
        }
    }

    ITEM_TRIGGERTABLE KeeBerryHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerKeeBerryDamageReaction},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerKeeBerryUse},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerKeeBerryUse},
    };

    ITEM_TRIGGERTABLE *EventAddAguavBerry(int *a1)
    {
        *a1 = ARRAY_COUNT(KeeBerryHandlers);
        return KeeBerryHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        ------------------------------------- ASSAULT VEST -------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerAssaultVest(int a1, int a2, int a3)
    {

        int result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 2)
            {
                BattleEventVar_MulValue(VAR_RATIO, 6144);
            }
        }
    }

    ITEM_TRIGGERTABLE AssaultVestHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ITEM_HANDLER_FUNC)HandlerAssaultVest}, // 10
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerBracer(_DWORD *a1)
    {
        *a1 = 1;
        return AssaultVestHandlers;
    };

    /*

        ----------------------------------------------------------------------------------------------------
        ------------------------------------- WEAKNESS POLICY ----------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerWeaknessPolicy(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS) > 3)
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 2) || BattleMon_IsStatChangeValid(PokeParam, 3u, 2))
            {
                ItemEvent_PushRun(a1, a2, (int)a3);
            }
        }
    }

    void HandlerWeaknessPolicyUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        int SubID;                    // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 2;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 2;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE WeaknessPolicyHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicy}, // 0
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicyUse},            // 1
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerLens(_DWORD *a1)
    {
        *a1 = 2;
        return WeaknessPolicyHandlers;
    };

    /*

        ----------------------------------------------------------------------------------------------------
        --------------------------------------- FAIRY DUST -------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerFairyDust(BattleEventItem *a1, int a2, int a3)
    {
        CommonTypeBoostingItem(a1, a2, a3, TYPE_FAIRY);
    }

    ITEM_TRIGGERTABLE FairyDustHandlers[] = {
        {EVENT_MOVE_POWER, (ITEM_HANDLER_FUNC)HandlerFairyDust}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddAdamantOrb(_DWORD *a1)
    {
        *a1 = 1;
        return FairyDustHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        ------------------------------------- TRICKSTER HERB -----------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerTricksterHerbPriorityCheck(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && !PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)))
        {
            if (BattleEventVar_RewriteValue(VAR_MOVE_PRIORITY, BattleEventVar_GetValue(VAR_MOVE_PRIORITY) + 1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    ITEM_TRIGGERTABLE TricksterHerbHandlers[] = {
        {EVENT_CHECK_SPECIAL_PRIORITY, (ITEM_HANDLER_FUNC)HandlerTricksterHerbPriorityCheck},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerCustapBerryUse}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLustrousOrb(_DWORD *a1)
    {
        *a1 = 2;
        return TricksterHerbHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        ---------------------------------------- FAIRY GEM -------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerFairyGemPower(int a1, ServerFlow *a2, int a3, _DWORD *a4)
    {
        CommonGemDecide(a1, a2, a3, a4, TYPE_FAIRY);
    }

    void HandlerFairyGemDecide(int a1, ServerFlow *a2, int a3, _DWORD *a4)
    {
        CommonGemPower(a1, a2, a3, a4, TYPE_FAIRY);
    }

    ITEM_TRIGGERTABLE FairyGemHandlers[] = {
        {EVENT_DAMAGE_PROCESSING_START, (ITEM_HANDLER_FUNC)HandlerFairyGemPower},
        {EVENT_MOVE_POWER, (ITEM_HANDLER_FUNC)HandlerFairyGemDecide},
        {EVENT_DAMAGE_PROCESSING_END, (ITEM_HANDLER_FUNC)HandlerGemEnd},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerBelt(_DWORD *a1)
    {
        *a1 = 3;
        return FairyGemHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        ------------------------------------- ROSELI BERRY -------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    int HandlerRoseliBerry(int a1, ServerFlow *a2, int a3, _DWORD *a4)
    {
        return CommonResistBerry(a1, a2, a3, a4, TYPE_FAIRY, 0);
    }

    ITEM_TRIGGERTABLE RoseliBerryHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerRoseliBerry},
        {EVENT_AFTER_DAMAGE_REACTION, (ITEM_HANDLER_FUNC)HandlerCommonResistBerryDamageAfter},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLansatBerry(_DWORD *a1)
    {
        *a1 = 2;
        return RoseliBerryHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ THROAT SPRAY ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerThroatSpraySoundMoveCheck(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            int moveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(moveID, FLAG_SOUND))
            {
                BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
                if (BattleMon_IsStatChangeValid(currentMon, STATSTAGE_SPECIAL_ATTACK, 1))
                {
                    ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
                }
            }
        }
    }

    void HandlerThroatSprayUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *spAttackBoost;
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            spAttackBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            spAttackBoost->poke_cnt = 1;
            spAttackBoost->pokeID[0] = pokemonSlot;
            spAttackBoost->rankType = STATSTAGE_SPECIAL_ATTACK;
            spAttackBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, spAttackBoost);
        }
    }

    ITEM_TRIGGERTABLE ThroatSprayHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (ITEM_HANDLER_FUNC)HandlerThroatSpraySoundMoveCheck}, // 35
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerThroatSprayUse},                    // 36
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddGriseousOrb(_DWORD *a1)
    {
        *a1 = 2;
        return ThroatSprayHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        --------------------------------------- LIGHT BALL -------------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void THUMB_BRANCH_SAFESTACK_HandlerLightBall(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            result = BattleMon_GetSpecies(PokeParam);
            if (result == 25 || result == 133)
            {
                BattleEventVar_MulValue(VAR_RATIO, 0x2000);
            }
        }
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------- BLUNDER POLICY -----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerBlunderPolicyCheckMiss(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        // k::Printf("\nWe are inside the Blunder Policy Handler\n");
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            // k::Printf("\nWe are inside the first loop of logic in the Blunder Policy Handler\n");

            BattleMon *battleMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            if (BattleMon_GetTurnFlag(battleMon, TURNFLAG_MOVEFAILED) && BattleMon_IsStatChangeValid(battleMon, STATSTAGE_SPEED, 2))
            {
                ItemEvent_PushRun(battleEventItem, serverFlow, pokemonSlot);
            }
        }
    }

    void HandlerBlunderPolicyUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_ChangeStatStage *speedBoost;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            speedBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, pokemonSlot);
            speedBoost->poke_cnt = 1;
            speedBoost->pokeID[0] = pokemonSlot;
            speedBoost->rankType = STATSTAGE_SPEED;
            speedBoost->rankVolume = 2;
            BattleHandler_PopWork(a2, speedBoost);
        }
    }

    ITEM_TRIGGERTABLE BlunderPolicyHandlers[] = {
        {EVENT_MOVE_EXECUTE_NOEFFECT, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyCheckMiss}, // 37
        {EVENT_MOVE_EXECUTE_END, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyCheckMiss},      // 37
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyUse},                    // 38
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLuckyPunch(_DWORD *a1)
    {
        *a1 = 3;
        return BlunderPolicyHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------- SAFETY GOGGLES -----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v7; // r0
        int moveId;
        int result;
        moveId = BattleEventVar_GetValue(VAR_MOVE_ID);

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && (moveId == 78 || moveId == 79 || moveId == 147 || moveId == 76 || moveId == 476 || moveId == 77 || moveId == 139))
        {
            result = BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
            if (result)
            {
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v7->str, 2u, 210);
                BattleHandler_AddArg(&v7->str, (int)a3);
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    ITEM_TRIGGERTABLE SafetyGogglesHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ITEM_HANDLER_FUNC)HandlerOvercoatPowders},
        {EVENT_WEATHER_REACTION, (ITEM_HANDLER_FUNC)HandlerOvercoat},
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerAnklet(_DWORD *a1)
    {
        *a1 = 2;
        return SafetyGogglesHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------------- STICK --------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void NewStickHandler(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *BattleMon;   // r0
        unsigned __int16 Value; // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            if (BattleMon_GetSpecies(BattleMon) == PK083_FARFETCH_D)
            {
                Value = BattleEventVar_GetValue(VAR_MOVE_ID);
                if (PML_MoveGetCategory(Value) == 1)
                {
                    BattleEventVar_MulValue(VAR_RATIO, 0x2000);
                }
            }
        }
    }

    ITEM_TRIGGERTABLE StickHandlers[] = {
        {EVENT_ATTACKER_POWER, (ITEM_HANDLER_FUNC)NewStickHandler}, // 24
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddStick(_DWORD *a1)
    {
        *a1 = 1;
        return StickHandlers;
    }

    /*

        ----------------------------------------------------------------------------------------------------
        ----------------------------------- ATTACK INSURANCE -----------------------------------------------
        ----------------------------------------------------------------------------------------------------

    */

    void HandlerAttackInsuranceUse(BattleEventItem *battleEventItem, ServerFlow *a2, int pokemonSlot, int *work)
    {
        HandlerParam_Damage *damage;
        int target;
        BattleMon *defendingMon;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID) && PML_MoveIsDamaging(BattleEventVar_GetValue(VAR_MOVE_ID)))
        {
            defendingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON));

            damage = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, pokemonSlot);
            damage->pokeID = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            damage->damage = DivideMaxHPZeroCheck(defendingMon, 8u);
            BattleHandler_StrSetup(&damage->exStr, 2u, 1237);
            BattleHandler_AddArg(&damage->exStr, damage->pokeID);
            BattleHandler_PopWork(a2, damage);
        }
    }

    ITEM_TRIGGERTABLE AttackInsuranceHandlers[] = {
        {EVENT_MOVE_EXECUTE_NOEFFECT, (ITEM_HANDLER_FUNC)HandlerAttackInsuranceUse}, // 24
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddLaxIncense(_DWORD *a1)
    {
        *a1 = 1;
        return AttackInsuranceHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------------------- LOADED DICE -----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerLoadedDice(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot = BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon *attackingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            if (attackingMon->HeldItem == IT0317_LOADED_DICE)
            {
                int hitCount = BattleEventVar_GetValue(VAR_MAX_HIT_COUNT);
                if (hitCount == 5)
                {
                    if (BattleRandom(100u) < 50)
                        hitCount = 4;
                    else
                        hitCount = 5;
                }

                BattleEventVar_RewriteValue(VAR_HIT_COUNT, hitCount);
                BattleEventVar_RewriteValue(VAR_AVOID_FLAG, 0);
            }
        }
    }

    ITEM_TRIGGERTABLE LoadedDiceHandlers[] = {
        {EVENT_MOVE_HIT_COUNT, (ITEM_HANDLER_FUNC)HandlerLoadedDice},

    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddWaveIncense(int *a1)
    {
        *a1 = 1;
        return LoadedDiceHandlers;
    }

#pragma endregion

    /*

















    */

#pragma region QoLItems
    /*


        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        ----------------------------- QOL PRE-DAMAGE AND PRE-STATUS ITEMS --------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------


    */

    bool checkIfWildBattle(ServerFlow *a1)
    {
        return a1->mainModule->btlSetup->btlType == 0;
    }

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------------- FLAME ORB ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerFlameOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_BURN;
            v6->sickCont = MakeBasicStatus(CONDITION_BURN);
            v6->fAlmost = 0;
            v6->pokeID = a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 258);
            BattleHandler_AddArg(&v6->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v6->exStr, SubID);
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE FlameOrbHandlers[] = {
        {EVENT_TURN_CHECK_END, (ITEM_HANDLER_FUNC)HandlerFlameOrb},
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerFlameOrbWild},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerFlameOrbUseTemp},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddFlameOrb(_DWORD *a1)
    {
        *a1 = 5;
        return FlameOrbHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------------- TOXIC ORB ------------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerToxicOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = Condition_MakeBadlyPoisoned();
            v6->fAlmost = 0;
            v6->pokeID = a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 240);
            BattleHandler_AddArg(&v6->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v6->exStr, SubID);
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE ToxicOrbHandlers[] = {
        {EVENT_TURN_CHECK_END, (ITEM_HANDLER_FUNC)HandlerToxicOrb},
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerToxicOrbWild},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerToxicOrbUseTemp},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddToxicOrb(_DWORD *a1)
    {
        *a1 = 5;
        return ToxicOrbHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ STRESS TESTER -----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerStressTester(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Damage *v1;
        int ItemParam;
        int SubID;
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);

            k::Printf("\n\nThe pokemon's sex is %d\n\n", PokeParam->Sex);
            v1 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, a3);
            v1->pokeID = a3;
            v1->damage = BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP) - 1;
            BattleHandler_StrSetup(&v1->exStr, 2u, 1038);
            BattleHandler_AddArg(&v1->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg(&v1->exStr, SubID);
            BattleHandler_PopWork(a2, v1);
        }
    }

    ITEM_TRIGGERTABLE StressTesterHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerStressTester},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddMetalPowder(_DWORD *a1)
    {
        *a1 = 3;
        return StressTesterHandlers;
    }

    /*

       --------------------------------------------------------------------------------------------------
       -------------------------------------- STATIC ORB ------------------------------------------------
       --------------------------------------------------------------------------------------------------

    */

    void HandlerStaticOrb(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_PARALYSIS;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = (int)a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 273);
            BattleHandler_AddArg(&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerStaticOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v6->sickID = CONDITION_PARALYSIS;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup(&v6->exStr, 2u, 273);
            BattleHandler_AddArg(&v6->exStr, a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE StaticOrbHandlers[] = {
        {EVENT_TURN_CHECK_END, (ITEM_HANDLER_FUNC)HandlerStaticOrb},
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerStaticOrbWild},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerLightBallUseTemp},
        {EVENT_SKIP_RUN_CALC, (ITEM_HANDLER_FUNC)HandlerSmokeBall},
        {EVENT_RUN_EXIT_MESSAGE, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddAmuletCoin(_DWORD *a1)
    {
        *a1 = 5;
        return StaticOrbHandlers;
    }

#pragma endregion

    /*

















    */

#pragma region ColressItems
    /*


        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        ---------------------------------------- COLRESS ITEMS -------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------


    */

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------- MYSTERIOUS DEVICE / PROTO BOOSTER ------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerProtoBooster(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 1) || BattleMon_IsStatChangeValid(PokeParam, 3u, 1) || BattleMon_IsStatChangeValid(PokeParam, 6u, -1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerProtoBoosterUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        HandlerParam_Message *v8;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v8 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v8->str, 2u, 1192);
            BattleHandler_AddArg(&v8->str, (int)a3);
            BattleHandler_AddArg(&v8->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v8);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ACCURACY;
            v6->rankVolume = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE ProtoBoosterHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerProtoBooster},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerProtoBoosterUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddQuickPowder(_DWORD *a1)
    {
        *a1 = 2;
        return ProtoBoosterHandlers;
    }

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerWeight(_DWORD *a1)
    {
        *a1 = 2;
        return ProtoBoosterHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------------------- CLRS BOOSTER ----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerCLRSBooster(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 1) || BattleMon_IsStatChangeValid(PokeParam, 3u, 1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerCLRSBoosterUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        HandlerParam_Message *v8;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v8 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v8->str, 2u, 1192);
            BattleHandler_AddArg(&v8->str, (int)a3);
            BattleHandler_AddArg(&v8->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v8);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE CLRSBoosterHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerCLRSBooster},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerCLRSBoosterUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerBand(_DWORD *a1)
    {
        *a1 = 2;
        return CLRSBoosterHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------- CLRS PROTO ACCELERATOR -----------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerProtoAccelerator(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 5u, 2) || BattleMon_IsStatChangeValid(PokeParam, 6u, -1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerProtoAcceleratorUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        HandlerParam_Message *v8;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v8 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v8->str, 2u, 1192);
            BattleHandler_AddArg(&v8->str, (int)a3);
            BattleHandler_AddArg(&v8->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v8);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_SPEED;
            v5->rankVolume = 2;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ACCURACY;
            v6->rankVolume = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE ProtoAcceleratorHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerProtoAccelerator},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerProtoAcceleratorUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddRockIncense(_DWORD *a1)
    {
        *a1 = 2;
        return ProtoAcceleratorHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ CLRS ACCELERATOR --------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerCLRSAccelerator(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 5u, 2))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerCLRSAcceleratorUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        HandlerParam_Message *v8;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v8 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v8->str, 2u, 1192);
            BattleHandler_AddArg(&v8->str, (int)a3);
            BattleHandler_AddArg(&v8->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v8);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_SPEED;
            v5->rankVolume = 2;
            BattleHandler_PopWork(a2, v5);
        }
    }

    ITEM_TRIGGERTABLE CLRSAccleratorHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerCLRSAccelerator},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerCLRSAcceleratorUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddRoseIncense(_DWORD *a1)
    {
        *a1 = 2;
        return CLRSAccleratorHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- CLRS INVENTION ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerCLRSInvention(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 5u, 2))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerCLRSInventionUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ChangeStatStage *v7;
        HandlerParam_ChangeStatStage *v8;
        HandlerParam_ChangeStatStage *v9;

        HandlerParam_ConsumeItem *v10; // r6
        HandlerParam_Message *v11;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v11 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v11->str, 2u, 1192);
            BattleHandler_AddArg(&v11->str, (int)a3);
            BattleHandler_AddArg(&v11->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v11);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_DEFENSE;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
            v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v7->poke_cnt = 1;
            v7->pokeID[0] = (int)a3;
            v7->rankType = STATSTAGE_SPECIAL_ATTACK;
            v7->rankVolume = 1;
            v7->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v7);
            v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v8->poke_cnt = 1;
            v8->pokeID[0] = (int)a3;
            v8->rankType = STATSTAGE_SPECIAL_DEFENSE;
            v8->rankVolume = 1;
            v8->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v8);
            v9 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v9->poke_cnt = 1;
            v9->pokeID[0] = (int)a3;
            v9->rankType = STATSTAGE_SPEED;
            v9->rankVolume = 1;
            v9->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v9);
        }
    }

    ITEM_TRIGGERTABLE CLRSInventionHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerCLRSInvention},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerCLRSInventionUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddOddIncense(_DWORD *a1)
    {
        *a1 = 2;
        return CLRSInventionHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------------- PROTO ARMOR ----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerProtoArmor(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 2u, 1) || BattleMon_IsStatChangeValid(PokeParam, 4u, 1) || BattleMon_IsStatChangeValid(PokeParam, 6u, -1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerProtoArmorUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        HandlerParam_Message *v8;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v8 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v8->str, 2u, 1192);
            BattleHandler_AddArg(&v8->str, (int)a3);
            BattleHandler_AddArg(&v8->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v8);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_DEFENSE;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_DEFENSE;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ACCURACY;
            v6->rankVolume = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE ProtoArmorHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerProtoArmor},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerProtoArmorUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSeaIncense(_DWORD *a1)
    {
        *a1 = 2;
        return ProtoArmorHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ---------------------------------------- CLRS ARMOR ----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerCLRSArmor(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 2u, 1) || BattleMon_IsStatChangeValid(PokeParam, 4u, 1))
            {
                ItemEvent_PushRun(a1, a2, a3);
            }
        }
    }

    void HandlerCLRSArmorUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        HandlerParam_Message *v8;
        int SubID; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v8 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v8->str, 2u, 1192);
            BattleHandler_AddArg(&v8->str, (int)a3);
            BattleHandler_AddArg(&v8->str, BattleEventItem_GetSubID((BattleEventItem *)a1));
            BattleHandler_PopWork(a2, v8);

            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (int)a3;
            v5->rankType = STATSTAGE_DEFENSE;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_DEFENSE;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE CLRSArmorHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerCLRSArmor},   // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerCLRSArmorUse}, // 25
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddGripClaw(_DWORD *a1)
    {
        *a1 = 2;
        return CLRSArmorHandlers;
    }

#pragma endregion

    /*

















    */

#pragma region WeatherRocks
    /*


        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        ------------------------------- WEATHER ROCKS RE-IMPLEMENTATION ----------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------


    */

    /*

        --------------------------------------------------------------------------------------------------
        ---------------------------------------- SMOOTH ROCK ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerSmoothRock(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        // k::Printf("\nWe got this far");
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && ServerEvent_GetWeather(a2) != WEATHER_SAND)
        {
            // k::Printf("\nWe are now this far");
            ItemEvent_PushRun(a1, a2, a3);
        }
    }

    void HandlerSmoothRockUse(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_ChangeWeather *v6; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            // k::Printf("\nWe made it into this function\n");
            v6 = (HandlerParam_ChangeWeather *)BattleHandler_PushWork(a2, EFFECT_CHANGE_WEATHER, a3);
            v6->weather = WEATHER_SAND;
            v6->turnCount = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE SmoothRockHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerSmoothRock},             // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerSmoothRockUse},           // 24
        {EVENT_WEATHER_REACTION, (ITEM_HANDLER_FUNC)HandlerSandVeilWeather}, // 24
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSmoothRock(_DWORD *a1)
    {
        *a1 = 3;
        return SmoothRockHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------------- ICY ROCK ----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerIcyRock(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && ServerEvent_GetWeather(a2) != WEATHER_HAIL)
        {
            ItemEvent_PushRun(a1, a2, a3);
        }
    }

    void HandlerIcyRockUse(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_ChangeWeather *v6; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v6 = (HandlerParam_ChangeWeather *)BattleHandler_PushWork(a2, EFFECT_CHANGE_WEATHER, a3);
            v6->weather = WEATHER_HAIL;
            v6->turnCount = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE IcyRockHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerIcyRock}, // 24
        // {EVENT_AFTER_ITEM_EQUIP, (ITEM_HANDLER_FUNC)HandlerIcyRock},          // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerIcyRockUse},               // 24
        {EVENT_WEATHER_REACTION, (ITEM_HANDLER_FUNC)HandlerSnowCloakWeather}, // 24
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddIcyRock(_DWORD *a1)
    {
        *a1 = 3;
        return IcyRockHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------------- HEAT ROCK ----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerHeatRock(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && ServerEvent_GetWeather(a2) != WEATHER_SUN)
        {
            ItemEvent_PushRun(a1, a2, a3);
        }
    }

    void HandlerHeatRockUse(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_ChangeWeather *v6; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v6 = (HandlerParam_ChangeWeather *)BattleHandler_PushWork(a2, EFFECT_CHANGE_WEATHER, a3);
            v6->weather = WEATHER_SUN;
            v6->turnCount = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE HeatRockHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerHeatRock}, // 24
        //{EVENT_AFTER_ITEM_EQUIP, (ITEM_HANDLER_FUNC)HandlerHeatRock}, // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerHeatRockUse}, // 24
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddHeatRock(_DWORD *a1)
    {
        *a1 = 2;
        return HeatRockHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------------- DAMP ROCK ----------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    void HandlerDampRock(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && ServerEvent_GetWeather(a2) != WEATHER_RAIN)
        {
            ItemEvent_PushRun(a1, a2, a3);
        }
    }

    void HandlerDampRockUse(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_ChangeWeather *v6; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            v6 = (HandlerParam_ChangeWeather *)BattleHandler_PushWork(a2, EFFECT_CHANGE_WEATHER, a3);
            v6->weather = WEATHER_RAIN;
            v6->turnCount = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    ITEM_TRIGGERTABLE DampRockHandlers[] = {
        {EVENT_SWITCH_IN, (ITEM_HANDLER_FUNC)HandlerDampRock}, // 24
        //{EVENT_AFTER_ITEM_EQUIP, (ITEM_HANDLER_FUNC)HandlerDampRock}, // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerDampRockUse}, // 24
    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddDampRock(_DWORD *a1)
    {
        *a1 = 2;
        return DampRockHandlers;
    }

#pragma endregion
    /*

















    */

#pragma region Terastalization
    /*


        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------- TERASTALIZATION IMPLEMENTATION AND ITEMS -----------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------
        --------------------------------------------------------------------------------------------------


    */
    // Add Logic for Not Resetting Tera Flag which is our new terastailization flag
    void THUMB_BRANCH_ClearMoveStatusWork(BattleMon *a1, int a2)
    {
        unsigned int v2; // r3
        int *Conditions; // r6
        int v4;          // r2
        unsigned int v5; // r5
        int isTera;
        v2 = 0;
        if (!a2)
        {
            v2 = 6;
        }
        Conditions = a1->Conditions;

        isTera = a1->Conditions[CONDITION_TERA];
        do
        {
            v4 = v2;
            a1->Conditions[v2] = 0;
            v5 = Conditions[v2++];
            Conditions[v4] = (v5 & 0xFFFFFFF8);
        } while (v2 < 0x24);

        if (isTera)
        {
            a1->Conditions[CONDITION_TERA] = isTera;
        }
        sys_memset(a1->MoveConditionCounter, 0, 0x24u);
    }

    void THUMB_BRANCH_BattleMon_SetupBySrcDataBase(BattleMon *a1, PartyPkm *a2, int a3)
    {
        if (a3 && !BattleMon_CheckIfMoveCondition(a1, CONDITION_TERA))
        {
            a1->Type1 = PokeParty_GetParam(a2, PF_Type1, 0);
            a1->Type2 = PokeParty_GetParam(a2, PF_Type2, 0);
        }
        a1->Sex = PokeParty_GetSex(a2);
        a1->Attack = PokeParty_GetParam(a2, PF_ATK, 0);
        a1->Defense = PokeParty_GetParam(a2, PF_DEF, 0);
        a1->SpecialAttack = PokeParty_GetParam(a2, PF_SPA, 0);
        a1->SpecialDefense = PokeParty_GetParam(a2, PF_SPD, 0);
        a1->Speed = PokeParty_GetParam(a2, PF_SPE, 0);
    }

    // Overwritten to remove the unintended effects of overwriting the CONDITION_ACCURACY_UP effect
    bool THUMB_BRANCH_ServerEvent_CheckHit(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4)
    {
        int ID;                       // r0
        int v10;                      // r0
        int Value;                    // r0
        int v12;                      // r0
        int v13;                      // r4
        int v14;                      // r5
        int v15;                      // r1
        int v16;                      // r0
        unsigned int v17;             // r0
        unsigned __int8 v18;          // r4
        unsigned __int8 MoveAccuracy; // [sp+0h] [bp-20h]
        int v20;                      // [sp+4h] [bp-1Ch]
        int v21;                      // [sp+8h] [bp-18h]

        if (ServerControl_IsGuaranteedHit(a1, a2, a3) || ServerEvent_BypassAccuracyCheck(a1, a2, a3, (MoveID)a4->MoveID))
        {
            return 1;
        }
        MoveAccuracy = ServerEvent_GetMoveAccuracy(a1, a2, a3, a4);
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v10 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v10);
        BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);
        Value = BattleMon_GetValue(a2, VALUE_ACCURACY_STAGE);
        BattleEventVar_SetValue(VAR_ACCURACY_STAGE, Value);
        v12 = BattleMon_GetValue(a3, VALUE_EVASION_STAGE);
        BattleEventVar_SetValue(VAR_EVASION_STAGE, v12);
        BattleEventVar_SetMulValue(VAR_RATIO, 4096, 41, 0x20000);
        BattleEvent_CallHandlers(a1, EVENT_MOVE_ACCURACY_STAGE);
        v20 = BattleEventVar_GetValue(VAR_ACCURACY_STAGE);
        v13 = BattleEventVar_GetValue(VAR_EVASION_STAGE);
        v21 = BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS);
        if (BattleMon_CheckIfMoveCondition(a3, CONDITION_FORESIGHT) && v13 > 6 || v21)
        {
            v13 = 6;
        }
        // if (BattleMon_GetTurnFlag(a2, TURNFLAG_ACCURACYUP))
        // {
        //     BattleEventVar_MulValue(VAR_RATIO, 4915);
        // }
        v14 = BattleEventVar_GetValue(VAR_RATIO);
        BattleEventVar_Pop();
        v15 = v20 + 6 - v13;
        if (v15 < 0)
        {
            v15 = 0;
        }
        if (v15 > 12)
        {
            // LOBYTE(v15) = 12;
            v15 = (v15 & 0xFF00) | 0xC;
            // Value = (Value & 0xFF00) | 0x04
        }
        v16 = Calc_MulRatio(MoveAccuracy, v15);
        v17 = fixed_round(v16, v14);
        v18 = v17;
        if (v17 > 0x64)
        {
            v18 = 100;
        }
        if (MainModule_GetDebugFlag())
        {
            v18 = 100;
        }
        return BattleRandom(0x64u) < v18;
    }

    extern bool j_j_PosPoke_IsExist(PosPoke *a1, int a2);
    extern void BattleMon_ChangePokeType(BattleMon *a1, int a2);

    // int checkPosPokeHelper(PosPoke *a1, int a2)
    // {
    //     int pos;
    //     unsigned int i;   // r4
    //     PosPokeState *v3; // r3

    //     for (i = 0; i < 6; ++i)
    //     {
    //         v3 = &a1->state[i];
    //         k::Printf("\nenable is %d and existPokeID is %d", v3->fEnable, v3->existPokeID);
    //         if (v3->fEnable && a2 == v3->existPokeID)
    //         {
    //             return i;
    //         }
    //     }
    //     return 6;
    // }
    // bool checkPosPoke(PosPoke *a1, int a2)
    // {

    //     return checkPosPokeHelper(a1, a2) != 6;
    // }

    // extern int splitTypeCore(BattleMon *a1, u8 *a2, u8 *a3);

    // int THUMB_BRANCH_SAFESTACK_BattleHandler_ChangeType(ServerFlow *a1, HandlerParam_ChangeType *a2)
    // {
    //     BattleMon *BattleMon; // r6
    //     int Species;          // r0
    //     int Type1;            // r0

    //     k::Printf("\nCheck A!");
    //     if (!j_j_PosPoke_IsExist(&a1->posPoke, a2->monID))
    //     {
    //         k::Printf("\nCheck B!, mon ID = %d and helper returns %d", j_j_PosPoke_IsExist(&a1->posPoke, a2->monID), j_j_PosPoke_IsExist(&a1->posPoke, a2->monID));
    //         return 0;
    //     }

    //     BattleMon = PokeCon_GetBattleMon(a1->pokeCon, a2->monID);
    //     k::Printf("\nCheck C!");
    //     if (BattleMon_CheckIfMoveCondition(BattleMon, CONDITION_TERA))
    //     {
    //         k::Printf("\nCheck D!");
    //         k::Printf("\nWe're a tera mon, silly!");
    //         return 0;
    //     }
    //     if (BattleMon_IsFainted(BattleMon))
    //     {
    //         return 0;
    //     }
    //     Species = BattleMon_GetSpecies(BattleMon);
    //     if (Species == PK493_ARCEUS)
    //     {
    //         return 0;
    //     }
    //     ServerDisplay_AddCommon(a1->serverCommandQueue, 22, a2->monID, a2->nextType);
    //     BattleMon_ChangePokeType(BattleMon, a2->nextType);
    //     if (!a2->pad && PokeTypePair_IsMonotype(a2->nextType))
    //     {
    //         k::Printf("\nCheck E!");
    //         Type1 = PokeTypePair_GetType1(a2->nextType);
    //         u8 v9;
    //         u8 v10;
    //         splitTypeCore(BattleMon, &v9, &v10);
    //         k::Printf("\nThe type is %d, but the actual types are %d and %d", Type1, v9, v10);
    //         ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 896, a2->monID, Type1, -65536); // 896: [VAR PKNICK(0)] transformed\ninto the [VAR TYPE(1)] type!
    //     }
    //     return 1;
    // }

    int PersonalCondition_CheckFloating(ServerFlow *a1, BattleMon *a2)
    {
        int result;

        if (BattleMon_CheckIfMoveCondition(a2, CONDITION_INGRAIN))
        {
            BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        }
        if (BattleMon_CheckIfMoveCondition(a2, CONDITION_KNOCKEDDOWN))
        {
            BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        }
        if (BattleMon_CheckIfMoveCondition(a2, CONDITION_FLOATING))
        {
            BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
        }
        return result;
    }

    int THUMB_BRANCH_ServerEvent_CheckFloating(ServerFlow *a1, BattleMon *a2, int a3)
    {
        bool HasType; // r4
        int ID;       // r0
        int Value;    // r4
        int v8;       // r5
        int result;   // r0

        if (a3)
        {
            HasType = BattleMon_HasType(a2, TYPE_FLYING);
        }
        else
        {
            HasType = 0;
        }
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, HasType);
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEvent_CallHandlers(a1, EVENT_CHECK_FLOATING);
        PersonalCondition_CheckFloating(a1, a2);
        Value = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);
        v8 = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
        BattleEventVar_Pop();
        result = 0;
        if (!v8)
        {
            return Value;
        }
        return result;
    }

    void HandlerTera(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot)
    {
        HandlerParam_ChangeType *changeType;
        HandlerParam_AddCondition *addConditon;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {

            BattleMon *mon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            if (BattleMon_CheckIfMoveCondition(mon, CONDITION_TERA))
            {
                return;
            }

            int type = PML_MoveGetType(Move_GetID(mon, 0));

            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(serverFlow, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE516_BESTOW;
            addAnimation->pos_from = 3;
            addAnimation->pos_to = 3;
            BattleHandler_PopWork(serverFlow, addAnimation);

            changeType = (HandlerParam_ChangeType *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_TYPE, pokemonSlot);
            changeType->nextType = PokeTypePair_MakeMonotype(type);
            changeType->monID = pokemonSlot;
            changeType->pad = 1;
            BattleHandler_PopWork(serverFlow, changeType);

            addConditon = (HandlerParam_AddCondition *)BattleHandler_PushWork(serverFlow, EFFECT_ADDCONDITION, pokemonSlot);
            addConditon->pokeID = pokemonSlot;
            addConditon->sickID = CONDITION_TERA;
            addConditon->sickCont = Condition_MakePermanent();
            BattleHandler_StrSetup(&addConditon->exStr, 2u, 1294);
            BattleHandler_AddArg(&addConditon->exStr, pokemonSlot);
            BattleHandler_AddArg(&addConditon->exStr, type);
            BattleHandler_PopWork(serverFlow, addConditon);
        }
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ TERA CHOICE SPECS -------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraChoiceSpecsHandlers[] = {
        {EVENT_CHOOSE_MOVE, (ITEM_HANDLER_FUNC)HandlerChoiceItemCommonMoveLock},
        {EVENT_HELD_ITEM_DECIDE, (ITEM_HANDLER_FUNC)HandlerChoiceItemCommonItemChange},
        {EVENT_ATTACKER_POWER, (ITEM_HANDLER_FUNC)HandlerChoiceSpecsPower},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddFlamePlate(_DWORD *a1)
    {
        *a1 = 4;
        return TeraChoiceSpecsHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA CHOICE BAND -------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraChoiceBandHandlers[] = {
        {EVENT_CHOOSE_MOVE, (ITEM_HANDLER_FUNC)HandlerChoiceItemCommonMoveLock},
        {EVENT_HELD_ITEM_DECIDE, (ITEM_HANDLER_FUNC)HandlerChoiceItemCommonItemChange},
        {EVENT_ATTACKER_POWER, (ITEM_HANDLER_FUNC)HandlerChoiceBandPower},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSplashPlate(_DWORD *a1)
    {
        *a1 = 4;
        return TeraChoiceBandHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA CHOICE SCARF ------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraChoiceScarfHandlers[] = {
        {EVENT_CHOOSE_MOVE, (ITEM_HANDLER_FUNC)HandlerChoiceItemCommonMoveLock},
        {EVENT_HELD_ITEM_DECIDE, (ITEM_HANDLER_FUNC)HandlerChoiceItemCommonItemChange},
        {EVENT_CALC_SPEED, (ITEM_HANDLER_FUNC)HandlerChoiceScarf},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddZapPlate(_DWORD *a1)
    {
        *a1 = 4;
        return TeraChoiceScarfHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA LIFE ORB  ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraLifeOrbHandlers[] = {
        {EVENT_DAMAGE_PROCESSING_END_HIT_2, (ITEM_HANDLER_FUNC)HandlerLifeOrbReaction},
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerLifeOrbPower},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddMeadowPlate(_DWORD *a1)
    {
        *a1 = 3;
        return TeraLifeOrbHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA FOCUS SASH --------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraSashHandlers[] = {
        {EVENT_ENDURE_CHECK, (ITEM_HANDLER_FUNC)HandlerFocusSash},
        {EVENT_ENDURE, (ITEM_HANDLER_FUNC)HandlerFocusSashUse},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddIciclePlate(_DWORD *a1)
    {
        *a1 = 3;
        return TeraSashHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA FOCUS BAND  -------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraFocusBandHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerFocusBandNew},
        {EVENT_AFTER_DAMAGE_REACTION, (ITEM_HANDLER_FUNC)HandlerFocusBandAfter},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddFistPlate(_DWORD *a1)
    {
        *a1 = 3;
        return TeraFocusBandHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA QUICK CLAW --------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraQuickClawHandlers[] = {
        {EVENT_CHECK_SPECIAL_PRIORITY, (ITEM_HANDLER_FUNC)HandlerQuickClawPriorityCheck},
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerQuickClawUse},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAdToxicPlate(_DWORD *a1)
    {
        *a1 = 3;
        return TeraQuickClawHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------- TERA WEAKNESS POLICY -----------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraWeaknessPolicyHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicy}, // 0
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicyUse},            // 1
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddEarthPlate(_DWORD *a1)
    {
        *a1 = 3;
        return TeraWeaknessPolicyHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------- TERA BLUNDER POLICY ------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraBlunderPolicyHandlers[] = {
        {EVENT_MOVE_EXECUTE_NOEFFECT, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyCheckMiss}, // 37
        {EVENT_MOVE_EXECUTE_END, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyCheckMiss},      // 37
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyUse},                    // 38
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSkyPlate(_DWORD *a1)
    {
        *a1 = 4;
        return TeraBlunderPolicyHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA BRIGHTPOWDER ------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraBrightPowderHandlers[] = {
        {EVENT_MOVE_ACCURACY, (ITEM_HANDLER_FUNC)HandlerBrightPowder}, // 37                  // 38
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddMindPlate(_DWORD *a1)
    {
        *a1 = 2;
        return TeraBrightPowderHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ TERA ASSAULT VEST -------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraAssaultVestHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ITEM_HANDLER_FUNC)HandlerAssaultVest}, // 10
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddInsectPlate(_DWORD *a1)
    {
        *a1 = 2;
        return TeraAssaultVestHandlers;
    };

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA INSURANCE ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraAttackInsuranceHandlers[] = {
        {EVENT_MOVE_EXECUTE_NOEFFECT, (ITEM_HANDLER_FUNC)HandlerAttackInsuranceUse}, // 24
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddStonePlate(_DWORD *a1)
    {
        *a1 = 2;
        return TeraAttackInsuranceHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ TERA EXPERT BELT --------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraExpertBeltHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ITEM_HANDLER_FUNC)HandlerAttackInsuranceUse}, // 24
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddSpookyPlate(_DWORD *a1)
    {
        *a1 = 2;
        return TeraExpertBeltHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA LEFTOVERS ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraLeftoversHandlers[] = {
        {EVENT_TURN_CHECK_BEGIN, (ITEM_HANDLER_FUNC)HandlerLeftoversReaction}, // 24
        {EVENT_USE_ITEM, (ITEM_HANDLER_FUNC)HandlerLeftoversUse},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddDracoPlate(_DWORD *a1)
    {
        *a1 = 3;
        return TeraLeftoversHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------- TERA LOADED DICE ---------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraLoadedDiceHandlers[] = {
        {EVENT_MOVE_HIT_COUNT, (ITEM_HANDLER_FUNC)HandlerLoadedDice},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}

    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddDreadPlate(int *a1)
    {
        *a1 = 2;
        return TeraLoadedDiceHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------- TERA KING'S ROCK -------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraKingsRockHandlers[] = {
        {EVENT_MOVE_FLINCH_CHANCE, (ITEM_HANDLER_FUNC)HandlerKingsRock},
        {EVENT_USE_ITEM_TEMP, (ITEM_HANDLER_FUNC)HandlerKingsRockUseTemp},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}

    };

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddIronPlate(int *a1)
    {
        *a1 = 3;
        return TeraKingsRockHandlers;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ TERA MASCOT BADGE -------------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    ITEM_TRIGGERTABLE TeraMascotBadgeHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ITEM_HANDLER_FUNC)HandlerMascotBadgeDefense},
        {EVENT_ATTACKER_POWER, (ITEM_HANDLER_FUNC)HandlerMascotBadgeOffense},
        {EVENT_CALC_SPEED, (ITEM_HANDLER_FUNC)HandlerMascotBadgeSpeed},
        {EVENT_BEFORE_ATTACKS, (ITEM_HANDLER_FUNC)HandlerTera}};

    ITEM_TRIGGERTABLE *THUMB_BRANCH_EventAddMachoBrace(int *a1)
    {
        *a1 = 4;
        return TeraMascotBadgeHandlers;
    }
#pragma endregion
}