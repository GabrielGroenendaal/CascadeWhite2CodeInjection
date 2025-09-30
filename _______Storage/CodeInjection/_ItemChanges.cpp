#include "swan-master/codeinjection.h"
#include "NitoKernel/include/kPrint.h"

extern "C"
{

    bool THUMB_BRANCH_BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
    {
        if ((unsigned int)a1->HeldItem == 289 && a2 == CONDITION_TAUNT)
        {
            return true;
        }
        else if (a2 == CONDITION_BLOCK && (a1->Conditions[CONDITION_CURSE] & 7 != 0)){
            return true;
        }
        else
        {
            return (a1->Conditions[a2] & 7) != 0;
        }
    }

    int THUMB_BRANCH_HandlerLightBall(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            result = BattleMon_GetSpecies(PokeParam);
            if (result == 25 || result == 133)
            {
                return BattleEventVar_MulValue(VAR_RATIO, 0x2000);
            }
        }
        return result;
    }

    bool checkIfWildBattle(ServerFlow *a1)
    {
        // k::Printf("\nBtlType is %d\n", a1->mainModule->btlSetup->BtlType);
        return a1->mainModule->btlSetup->BtlType == 0;
    }

    // void HandlerDrowsyOrb(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    // {
    //     HandlerParam_AddCondition *v6; // r4
    //     int SubID;                     // r0

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
    //     {
    //         v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
    //         v6->sickID = CONDITION_SLEEP;
    //         v6->sickCont = MakeBasicStatus(CONDITION_SLEEP);
    //         v6->fAlmost = 0;
    //         v6->pokeID = (int)a3;
    //         v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
    //         BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 306);
    //         BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
    //         BattleHandler_PopWork(a2, v6);
    //     }
    // }

    // void HandlerDrowsyOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    // {
    //     HandlerParam_AddCondition *v6; // r4
    //     int SubID;                     // r0

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
    //     {
    //         v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
    //         v6->sickID = CONDITION_SLEEP;
    //         v6->sickCont = MakeBasicStatus(CONDITION_SLEEP);
    //         v6->fAlmost = 0;
    //         v6->pokeID = (int)a3;
    //         v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
    //         BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 306);
    //         BattleHandler_AddArg((u16 *)&v6->exStr, a3);
    //         BattleHandler_PopWork(a2, v6);
    //     }
    // }

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
            BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 273);
            BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerStaticOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            // v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            // v6->sickID = CONDITION_PARALYSIS;
            // v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            // v6->fAlmost = 0;
            // v6->pokeID = (int)a3;
            // //v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            // BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 273);
            // BattleHandler_AddArg((u16 *)&v6->exStr, a3);
            // BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v6->sickID = CONDITION_PARALYSIS;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = (int)a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 273);
            BattleHandler_AddArg((u16 *)&v6->exStr, a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

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
            v6->pokeID = (unsigned __int8)a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 258);
            BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg((u16 *)&v6->exStr, SubID);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerToxicOrbWild(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6; // r4
        int SubID;                     // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = Condition_MakeBadlyPoisoned();
            v6->fAlmost = 0;
            v6->pokeID = (int)a3;
            v6->exStr.args[0] = BattleEventItem_GetSubID(a1);
            BattleHandler_StrSetup((u16 *)&v6->exStr, 2u, 240);
            BattleHandler_AddArg((u16 *)&v6->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg((u16 *)&v6->exStr, SubID);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerMysteriousDevice(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 1) || BattleMon_IsStatChangeValid(PokeParam, 3u, 1) || BattleMon_IsStatChangeValid(PokeParam, 6u, -1))
            {
                ItemEvent_PushRun(a1, a2, (int)a3);
            }
        }
    }

    void HandlerMysteriousDeviceUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        int SubID;                    // r0

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (unsigned int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (unsigned int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (unsigned int)a3;
            v6->rankType = STATSTAGE_ACCURACY;
            v6->rankVolume = -1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerColressDevice(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            if (BattleMon_IsStatChangeValid(PokeParam, 1u, 1) || BattleMon_IsStatChangeValid(PokeParam, 3u, 1))
            {
                ItemEvent_PushRun(a1, a2, (int)a3);
            }
        }
    }

    void HandlerColressDeviceUse(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_ChangeStatStage *v5;
        HandlerParam_ChangeStatStage *v6;
        HandlerParam_ConsumeItem *v7; // r6
        int SubID;                    // r0

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (unsigned int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 1;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (unsigned int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerStressTester(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Damage *v1;
        int ItemParam;
        int SubID;
        BattleMon *PokeParam;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && checkIfWildBattle(a2))
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            v1 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, a3);
            v1->pokeID = a3;
            v1->damage = BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP) - 1;
            BattleHandler_StrSetup((u16 *)&v1->exStr, 2u, 1038);
            BattleHandler_AddArg((u16 *)&v1->exStr, a3);
            SubID = BattleEventItem_GetSubID(a1);
            BattleHandler_AddArg((u16 *)&v1->exStr, SubID);
            BattleHandler_PopWork(a2, v1);
        }
    }

    int HandlerAssaultVest(int a1, int a2, int a3)
    {

        int result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            if (BattleEventVar_GetValue(VAR_MOVECATEGORY) == 2)
            {
                return BattleEventVar_MulValue(VAR_RATIO, 6144);
            }
        }
        return result;
    }

    int HandlerRoseliBerry(int a1, int a2, int a3, unsigned int *a4)
    {
        return CommonResistBerry(a1, a2, a3, a4, TYPE_FAIRY, 0);
    }

    void HandlerFairyGemPower(int a1, int a2, int a3, unsigned int *a4)
    {
        CommonGemDecide(a1, a2, a3, a4, TYPE_FAIRY);
    }

    int HandlerFairyGemDecide(int a1, int a2, int a3, unsigned int *a4)
    {
        return CommonGemPower(a1, a2, a3, a4, TYPE_FAIRY);
    }

    int HandlerPixiePlate(int a1, int a2, int a3)
    {
        return CommonTypeBoostingItem(a1, a2, a3, TYPE_FAIRY);
    }

    int HandlerFairyDust(int a1, int a2, int a3)
    {
        return CommonTypeBoostingItem(a1, a2, a3, TYPE_FAIRY);
    }

    void HandlerWeaknessPolicy(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE) && BattleEventVar_GetValue(VAR_TYPEEFFECTIVENESS) > 3)
        {
            PokeParam = Handler_GetPokeParam(a2, (int)a3);
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

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            v5 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v5->poke_cnt = 1;
            v5->pokeID[0] = (unsigned int)a3;
            v5->rankType = STATSTAGE_ATTACK;
            v5->rankVolume = 2;
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (unsigned int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 2;
            BattleHandler_PopWork(a2, v6);
        }
    }

    int HandlerLuckyCharm(BattleEventItem *a1, ServerFlow *a2, int a3, unsigned int *a4)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_CRITICALFLAG))
        {
            BattleEventVar_MulValue(VAR_RATIO, 2048);
            *a4 = 1;
            return 1;
        }
        return 0;
    }

    void HandlerLuckyCharmUse(BattleEventItem *a1, ServerFlow *a2, int a3, unsigned int *a4)
    {
        HandlerParam_ConsumeItem *v7;
        int SubID;
        if (*a4)
        {
            if (HandlerCommon_CheckTargetPokeID(a3))
            {
                v7 = (HandlerParam_ConsumeItem *)(a2, EFFECT_CONSUMEITEM, a3);
                BattleHandler_StrSetup((u16 *)&v7->exStr, 2u, 219);
                BattleHandler_AddArg((u16 *)&v7->exStr, (int)a3);
                SubID = BattleEventItem_GetSubID(a1);
                BattleHandler_AddArg((u16 *)&v7->exStr, SubID);
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    void HandlerThroatSpraySoundMoveCheck(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            int moveID = BattleEventVar_GetValue(VAR_MOVEID);
            if (getMoveFlag(moveID, FLAG_SOUND))
            {
                BattleMon *currentMon = Handler_GetPokeParam(serverFlow, pokemonSlot);
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
            spAttackBoost->pokeID[0] = (u8)pokemonSlot;
            spAttackBoost->rankType = STATSTAGE_SPECIAL_ATTACK;
            spAttackBoost->rankVolume = 1;
            BattleHandler_PopWork(a2, spAttackBoost);
        }
    }

    void HandlerBlunderPolicyCheckMiss(BattleEventItem *battleEventItem, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        k::Printf("\nWe are inside the Blunder Policy Handler\n");
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            k::Printf("\nWe are inside the first loop of logic in the Blunder Policy Handler\n");

            BattleMon *battleMon = Handler_GetPokeParam(serverFlow, pokemonSlot);
            if (BattleMon_IsStatChangeValid(battleMon, STATSTAGE_SPEED, 2))
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
            speedBoost->pokeID[0] = (u8)pokemonSlot;
            speedBoost->rankType = STATSTAGE_SPEED;
            speedBoost->rankVolume = 2;
            BattleHandler_PopWork(a2, speedBoost);
        }
    }

    typedef struct
    {
        int triggerValue;
        ITEM_HANDLER_FUNC function;
    } ITEM_TRIGGERTABLE;

    ITEM_TRIGGERTABLE ItemTriggerTable[] =
        {
            {0x4B, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicy},    // 0
            {0x72, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicyUse}, // 1
            //{0x44, (ITEM_HANDLER_FUNC)HandlerWeaknessPolicyAfter},

            {0x38, (ITEM_HANDLER_FUNC)HandlerPixiePlate}, // 2

            {0x38, (ITEM_HANDLER_FUNC)HandlerFairyDust}, // 3

            {0x81, (ITEM_HANDLER_FUNC)HandlerFairyGemPower},  // 4
            {0x38, (ITEM_HANDLER_FUNC)HandlerFairyGemDecide}, // 5
            {0x88, (ITEM_HANDLER_FUNC)HandlerGemEnd},         // 6

            {0x47, (ITEM_HANDLER_FUNC)HandlerRoseliBerry},                  // 7
            {0x44, (ITEM_HANDLER_FUNC)HandlerCommonResistBerryDamageAfter}, // 8

            {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat}, // 9

            {0x3C, (ITEM_HANDLER_FUNC)HandlerAssaultVest}, // 10
            // {0x55, (ITEM_HANDLER_FUNC)HandlerAssaultVestSwitchIn},
            // {0x9C, (ITEM_HANDLER_FUNC)HandlerAssaultVestItemChange}

            // {0x77, (ITEM_HANDLER_FUNC)HandlerDrowsyOrb},     // 11
            // {0x55, (ITEM_HANDLER_FUNC)HandlerDrowsyOrbWild}, // 12

            {0x77, (ITEM_HANDLER_FUNC)HandlerFlameOrb},        // 11
            {0x55, (ITEM_HANDLER_FUNC)HandlerFlameOrbWild},    // 12
            {0x73, (ITEM_HANDLER_FUNC)HandlerFlameOrbUseTemp}, // 13
            {0xB, (ITEM_HANDLER_FUNC)HandlerSmokeBall},        // 14
            {0xD, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}, // 15

            {0x77, (ITEM_HANDLER_FUNC)HandlerToxicOrb},        // 16
            {0x55, (ITEM_HANDLER_FUNC)HandlerToxicOrbWild},    // 17
            {0x73, (ITEM_HANDLER_FUNC)HandlerToxicOrbUseTemp}, // 18
            {0xB, (ITEM_HANDLER_FUNC)HandlerSmokeBall},        // 19
            {0xD, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}, // 20

            {0x55, (ITEM_HANDLER_FUNC)HandlerStressTester},    // 21
            {0xB, (ITEM_HANDLER_FUNC)HandlerSmokeBall},        // 22
            {0xD, (ITEM_HANDLER_FUNC)HandlerSmokeBallMessage}, // 23

            {0x55, (ITEM_HANDLER_FUNC)HandlerMysteriousDevice},    // 24
            {0x72, (ITEM_HANDLER_FUNC)HandlerMysteriousDeviceUse}, // 25

            {0x47, (ITEM_HANDLER_FUNC)HandlerLuckyCharm},                   // 26
            {0x72, (ITEM_HANDLER_FUNC)HandlerLuckyCharmUse},                // 27
            {0x44, (ITEM_HANDLER_FUNC)HandlerCommonResistBerryDamageAfter}, // 28

            {0x55, (ITEM_HANDLER_FUNC)HandlerMysteriousDevice},    // 29
            {0x72, (ITEM_HANDLER_FUNC)HandlerMysteriousDeviceUse}, // 30

            {0x55, (ITEM_HANDLER_FUNC)HandlerColressDevice},    // 31
            {0x72, (ITEM_HANDLER_FUNC)HandlerColressDeviceUse}, // 32

            {0x77, (ITEM_HANDLER_FUNC)HandlerStaticOrb},     // 13
            {0x55, (ITEM_HANDLER_FUNC)HandlerStaticOrbWild}, // 14

            {0x27, (ITEM_HANDLER_FUNC)HandlerThroatSpraySoundMoveCheck},
            {0x72, (ITEM_HANDLER_FUNC)HandlerThroatSprayUse},

            {0x26, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyCheckMiss},
            {0x72, (ITEM_HANDLER_FUNC)HandlerBlunderPolicyUse}};

    // Weakness Policy
    int *THUMB_BRANCH_EventAddPowerLens(unsigned int *a1)
    {
        *a1 = 2;

        return (int *)&ItemTriggerTable[0].triggerValue;
    }

    // Fairy Dust
    int *THUMB_BRANCH_EventAddAdamantOrb(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&ItemTriggerTable[2].triggerValue;
    }

    // Pixie Plate
    int *THUMB_BRANCH_EventAddLustrousOrb(unsigned int *a1)
    {
        *a1 = 1;

        return (int *)&ItemTriggerTable[3].triggerValue;
    }

    // Fairy Gem
    int *THUMB_BRANCH_EventAddPowerBelt(unsigned int *a1)
    {
        *a1 = 3;

        return (int *)&ItemTriggerTable[4].triggerValue;
    }

    // Roseli Berry
    int *THUMB_BRANCH_EventAddLansatBerry(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[7].triggerValue;
    }

    // Safety Goggles
    int *THUMB_BRANCH_EventAddPowerAnklet(unsigned int *a1)
    {
        *a1 = 1;

        return (int *)&ItemTriggerTable[9].triggerValue;
    }

    // Assault Vest
    int *THUMB_BRANCH_EventAddPowerBracer(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&ItemTriggerTable[10].triggerValue;
    }

    // // Drowsy Orb
    // int *THUMB_BRANCH_EventAddRingTarget(unsigned int *a1)
    // {
    //     *a1 = 2;
    //     return (int *)&ItemTriggerTable[11].triggerValue;
    // }

    // // Static Orb
    // int *THUMB_BRANCH_EventAddQuickPowder(unsigned int *a1)
    // {
    //     *a1 = 2;
    //     return (int *)&ItemTriggerTable[13].triggerValue;
    // }

    int *THUMB_BRANCH_EventAddFlameOrb(unsigned int *a1)
    {
        *a1 = 5;
        return (int *)&ItemTriggerTable[11].triggerValue;
    }

    int *THUMB_BRANCH_EventAddToxicOrb(unsigned int *a1)
    {
        *a1 = 5;
        return (int *)&ItemTriggerTable[16].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMetalPowder(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&ItemTriggerTable[21].triggerValue;
    }

    int *THUMB_BRANCH_EventAddQuickPowder(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[24].triggerValue;
    }

    int *THUMB_BRANCH_EventAddRingTarget(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&ItemTriggerTable[26].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPowerWeight(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[29].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPowerBand(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[31].triggerValue;
    }

    // Static Orb
    int *THUMB_BRANCH_EventAddAmuletCoin(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[33].triggerValue;
    }

    // Throat Spray
    int *THUMB_BRANCH_EventAddGriseousOrb(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[35].triggerValue;
    }

    // Blunder Policy
    int *THUMB_BRANCH_EventAddLuckyPunch(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&ItemTriggerTable[37].triggerValue;
    }
}