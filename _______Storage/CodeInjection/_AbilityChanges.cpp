#include "swan-master/codeinjection.h"
#include "NitoKernel/include/kPrint.h"

extern "C"
{

    unsigned int *HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
    {
        char *v7; // r0
        int moveId;
        unsigned int *result;
        moveId = BattleEventVar_GetValue(VAR_MOVEID);

        if (moveId == 79 || moveId == 147 || moveId == 76 || moveId == 77 || moveId == 139)
        {
            result = (unsigned int *)BattleEventVar_RewriteValue(VAR_NOEFFECTFLAG, 1);
            if (result)
            {
                BattleHandler_PushRun(a2, 2, (int)a3);
                v7 = BattleHandler_PushWork(a2, 4, (int)a3);
                BattleHandler_StrSetup((unsigned __int16 *)v7 + 2, 2u, 210);
                BattleHandler_AddArg((u16 *)(v7 + 4), (int)a3);
                BattleHandler_PopWork(a2, (unsigned int *)v7);
                return BattleHandler_PushRun(a2, 3, (int)a3);
            }
        }
        return result;
    }


    bool PersonalCheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
    {
        if (a1->HeldItem == 289 && a2 == CONDITION_TAUNT)
        {
            return true;
        }
        else if (a2 == CONDITION_BLOCK && ((a1->Conditions[CONDITION_CURSE] & 7) != 0))
        {
            return true;
        }
        else
        {
            return (a1->Conditions[a2] & 7) != 0;
        }
    }

    // // void THUMB_BRANCH_HandlerSnowCloak(int a1, int a2, int a3)
    // // {
    // //     int attackingMon;
    // //     BattleMon *PokeParam;
    // //     if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && Handler_GetWeather((a2)) == 3) // hail
    // //     {
    // //         attackingMon = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    // //         PokeParam = Handler_GetPokeParam((ServerFlow*)a2, attackingMon);
    // //         k::Printf("\n\nWe're inside the Snow Cloak Handler Function\na1 = %d\na2 = %d\na3 = %d\nAttackingMon = %d\nPokeParam = %d\nHeld Item = %d\n\n",
    // //             a1, a2, a3, attackingMon, PokeParam, PokeParam->HeldItem);
    // //         if (PokeParam->HeldItem != 293){
    // //             BattleEventVar_MulValue(VAR_RATIO, 3277);
    // //         }
    // //     }
    // // }

    // // void THUMB_BRANCH_HandlerSandVeil(int a1, int a2, int a3)
    // // {
    // //     int attackingMon;
    // //     BattleMon *PokeParam;
    // //     if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) &&  Handler_GetWeather((a2)) == 4)// hail
    // //     {
    // //         attackingMon = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    // //         PokeParam = Handler_GetPokeParam((ServerFlow*)a2, attackingMon);
    // //         k::Printf("\n\nWe're inside the Sand Veil Handler Function\na1 = %d\na2 = %d\na3 = %d\nAttackingMon = %d\nPokeParam = %d\nHeld Item = %d\n\n",
    // //             a1, a2, a3, attackingMon, PokeParam, PokeParam->HeldItem);
    // //         if (PokeParam->HeldItem != 293){
    // //             BattleEventVar_MulValue(VAR_RATIO, 3277);
    // //         }
    // //     }
    // // }

    bool checksIfWildBattle(ServerFlow *a1)
    {
        // k::Printf("\nBtlType is %d\n", a1->mainModule->btlSetup->BtlType);
        return a1->mainModule->btlSetup->BtlType == 0;
    }

    bool checkForPaybackBoost(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon)
    {
        int *ActionOrderAttackingMon;
        int *ActionOrderDefendingMon;

        if (BattleMon_GetTurnFlag(DefendingMon, TURNFLAG_ACTIONDONE))
        {
            return true;
        }
        // k::Printf("\n\nDid we get this far?\n", ActionOrderAttackingMon);
        ActionOrderAttackingMon = ActionOrder_SearchByMonID(a1, AttackingMon->ID);
        ActionOrderDefendingMon = ActionOrder_SearchByMonID(a1, DefendingMon->ID);
        // k::Printf("The action order for the attacking mon is %d\n", ActionOrderAttackingMon);
        // k::Printf("The action order for the defending mon is %d\n\n", ActionOrderDefendingMon);
        if (ActionOrderAttackingMon > ActionOrderDefendingMon)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int THUMB_BRANCH_HandlerPayback(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int result2;
        unsigned __int8 Value;   // r0
        BattleMon *DefendingMon; // r0
        BattleMon *AttackingMon;
        bool paybackBoost;

        //k::Printf("\n\nWe're in the function\n\n");
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            DefendingMon = Handler_GetPokeParam(a2, Value);
            AttackingMon = Handler_GetPokeParam(a2, result);

            paybackBoost = checkForPaybackBoost(a2, AttackingMon, DefendingMon);
            //k::Printf("\nThe Payback Boost is %d\n", paybackBoost);
            if (paybackBoost)
            {
                return MultiplyBasePower(2);
            }
        }
        return result;
    }

    bool checkIfConsumableItem(int a1)
    {
        return (PML_ItemIsBerry(a1) ||
                a1 == 290 ||
                a1 == 43 ||
                (a1 >= 545 && a1 <= 564) ||
                a1 == 292 ||
                a1 == 291 ||
                a1 == 274 ||
                a1 == 542 ||
                a1 == 294 ||
                a1 == 543 ||
                a1 == 275 ||
                a1 == 219 ||
                a1 == 214 ||
                a1 == 271 ||
                a1 == 541);
    }

    // // For Unnerve
    // // a1 is the position of the pokemon with unnerve
    // // a2 is the ServerFlow
    // // a3 is the type of skip i think
    // // a6 is supposedly the side of
    bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(int a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
    {
        int PokeID;  // r0
        bool result; // r0

        result = 0;
        if (a3 == 5)
        {
            PokeID = BattleEventItem_GetPokeID(a1);
            if (!MainModule_IsAllyMonID(PokeID, a6))
            {
                if (checkIfConsumableItem(a5))
                {
                    return 1;
                }
            }
        }
        return result;
    }

    void THUMB_BRANCH_HandlerRegenerator(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;      // r6
        unsigned int v6;           // r4
        unsigned int v7;           // r0
        HandlerParam_ChangeHP *v8; // r0
        int Value;                 // [sp+0h] [bp-18h]

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetPokeParam(a2, (int)a3);
            if (!BattleMon_IsFainted(PokeParam) && !BattleMon_IsFullHP(PokeParam))
            {
                v6 = DivideMaxHPZeroCheck(PokeParam, 4u);
                Value = BattleMon_GetValue(PokeParam, VALUE_MAX_HP);
                v7 = Value - BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP);
                if (v6 > v7)
                {
                    v6 = v7;
                }
                v8 = (HandlerParam_ChangeHP *)BattleHandler_PushWork(a2, EFFECT_CHANGEHP, (int)a3);
                v8->pokeID[0] = (int)a3;
                v8->volume[0] = v6;
                v8->poke_cnt = 1;
                v8->fEffectDisable = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    // // For Fluffy
    int HandlerFluffy(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int isFire;
        int ratio;

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVEID);

            isFire = (PML_MoveGetType(Value) == TYPE_FIRE) ? 2 : 1;
            ratio = (getMoveFlag(Value, FLAG_CONTACT)) ? 2048 : 4096;

            // k::Printf("\n\n isFire is %d\nratio is %d\nisFire times Ratio is %d\n\n", isFire, ratio, isFire * ratio);

            return BattleEventVar_MulValue(VAR_RATIO, isFire * ratio);
        }
        return result;
    }

    void HandlerPickupNew(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *BattleMon; // r6
        int UsedItem;
        HandlerParam_SetItem *v8; // r0

        // k::Printf("\nWe are inside the first loop of logic\n");
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            // k::Printf("\nWe are inside the second loop of logic\n");

            BattleMon = Handler_GetPokeParam(a2, a3);
            UsedItem = BattleMon_GetUsedItem(BattleMon);

            if (UsedItem && BattleMon_GetHeldItem(BattleMon) == 0)
            {
                // k::Printf("\nWe are inside the third loop of logic\n");
                v8 = (HandlerParam_SetItem *)BattleHandler_PushWork(a2, EFFECT_SET_HELD_ITEM, a3);
                v8->header.flags |= 0x800000u;
                v8->itemID = UsedItem;
                v8->pokeID = a3;
                v8->fClearConsume = 0;
                BattleHandler_StrSetup((u16 *)&v8->exStr, 2u, 1162);
                BattleHandler_AddArg((u16 *)&v8->exStr, a3);
                BattleHandler_AddArg((u16 *)&v8->exStr, UsedItem);
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    // void THUMB_BRANCH_HandlerHarvest(int a1, ServerFlow *a2, int a3)
    // {
    //     BattleMon *PokeParam;     // r4
    //     int UsedItem;             // r0
    //     int v7;                   // r7
    //     HandlerParam_SetItem *v8; // r4
    //     if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    //     {
    //         PokeParam = Handler_GetPokeParam(a2, a3);
    //         UsedItem = BattleMon_GetUsedItem(PokeParam);
    //         v7 = UsedItem;
    //         if (UsedItem)
    //         {
    //             if (PML_ItemIsBerry(UsedItem) && BattleMon_GetHeldItem(PokeParam) == 0 && (Handler_GetWeather((int)a2) == 1 || AbilityEvent_RollEffectChance((int)a2, 50u)))
    //             {
    //                 v8 = (HandlerParam_SetItem *)BattleHandler_PushWork(a2, EFFECT_SET_HELD_ITEM, a3);
    //                 v8->header.flags |= 0x800000u;
    //                 v8->itemID = v7;
    //                 v8->pokeID = a3;
    //                 v8->fClearConsume = 1;
    //                 BattleHandler_StrSetup((u16 *)&v8->exStr, 2u, 475);
    //                 BattleHandler_AddArg((u16 *)&v8->exStr, a3);
    //                 BattleHandler_AddArg((u16 *)&v8->exStr, v7);
    //                 BattleHandler_PopWork(a2, v8);
    //             }
    //         }
    //     }
    // }

    // // Weak Armor
    void THUMB_BRANCH_HandlerWeakArmor(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;             // r7
        int v6;                           // r6
        HandlerParam_ChangeStatStage *v7; // r0
        HandlerParam_ChangeStatStage *v8; // r0

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVECATEGORY) == 1 && !BattleEventVar_GetValue(VAR_SUBSTITUTE))
        {
            PokeParam = Handler_GetPokeParam(a2, (int)a3);
            v6 = 0;
            if (BattleMon_IsStatChangeValid(PokeParam, 2u, -1) || BattleMon_IsStatChangeValid(PokeParam, 5u, 2))
            {
                v6 = 1;
            }
            if (v6)
            {
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v7->poke_cnt = 1;
                    v7->pokeID[0] = (unsigned int)a3;
                    v7->fMoveAnimation = 1;
                    v7->rankType = STATSTAGE_DEFENSE;
                    v7->rankVolume = -1;
                    BattleHandler_PopWork(a2, v7);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)a3;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = 2;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
    }

    // // For Gooey
    // // void THUMB_BRANCH_HandlerPickpocket(int a1, ServerFlow *a2, unsigned int a3)
    // // {
    // //     return;
    // // }

    // For Tough Claws
    void THUMB_BRANCH_HandlerCuteCharm(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;           // r0
        int v6;                           // r6
        BattleMon *PokeParam;             // r7
        HandlerParam_ChangeStatStage *v8; // r4

        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE))
        {
            Value = BattleEventVar_GetValue(VAR_MOVEID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
                PokeParam = Handler_GetPokeParam(a2, v6);
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)v6;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = -1;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
        return;
    }

    // Slush Rush
    void HandlerSlushRush(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && Handler_GetWeather(a2) == 3) // hail
        {
            BattleEventVar_MulValue(VAR_RATIO, 0x2000);
        }
    }

    // Tough Claws
    int HandlerToughClaws(int a1, int a2, int a3)
    {
        int result; // r0
        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            int MoveID = BattleEventVar_GetValue(VAR_MOVEID);
            if (getMoveFlag(MoveID, FLAG_CONTACT))
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 5324);
            }
        }
        return result;
    }

    // Heatproof
    int THUMB_BRANCH_HandlerHeatproofPower(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVETYPE);
            if (result == 9)
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 1024);
            }
        }
        return result;
    }

    int THUMB_BRANCH_HandlerIceBody(int a1, ServerFlow *a2, int a3)
    {
        int result;                 // r0
        BattleMon *PokeParam;       // r7
        HandlerParam_RecoverHP *v8; // r5

        result = BattleEventVar_GetValue(VAR_WEATHER);
        if (result == 3)
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetPokeParam(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x8u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVEFAILFLAG, 1);
            }
        }
        else
        {
            result = BattleEventVar_GetValue(VAR_MON_ID);
            if (a3 == result)
            {
                PokeParam = Handler_GetPokeParam(a2, a3);
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v8->header.flags |= 0x800000u;
                v8->pokeID = a3;
                v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, 0x10u);
                BattleHandler_PopWork(a2, v8);
                return BattleEventVar_RewriteValue(VAR_MOVEFAILFLAG, 1);
            }
        }
        return result;
    }

    //
    void HandlerPreBurnOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *PokeParam; // r7

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            // k::Printf("\nWe are in, lets see if this works");
            PokeParam = Handler_GetPokeParam(a2, a3);
            if (BattleMon_HasType(PokeParam, TYPE_FIRE))
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_POISON;
                v6->sickCont = MakeBasicStatus(CONDITION_POISON);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup((u16 *)&v6->exStr, 1u, 202);
                BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
            else
            {
                v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                v6->sickID = CONDITION_BURN;
                v6->sickCont = MakeBasicStatus(CONDITION_BURN);
                v6->fAlmost = 0;
                v6->pokeID = (unsigned __int8)a3;
                BattleHandler_StrSetup((u16 *)&v6->exStr, 1u, 201);
                BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
                BattleHandler_PopWork(a2, v6);
            }
        }
    }

    void HandlerPrePoisonOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = MakeBasicStatus(CONDITION_POISON);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup((u16 *)&v6->exStr, 1u, 202);
            BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerPreParalysisOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {

            v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
            v6->sickID = CONDITION_POISON;
            v6->sickCont = MakeBasicStatus(CONDITION_PARALYSIS);
            v6->fAlmost = 0;
            v6->pokeID = (unsigned __int8)a3;
            BattleHandler_StrSetup((u16 *)&v6->exStr, 1u, 203);
            BattleHandler_AddArg((u16 *)&v6->exStr, (int)a3);
            BattleHandler_PopWork(a2, v6);
        }
    }

    int checkHigher(int a1, int a2)
    {
        if (a1 < a2)
        {
            return a2;
        }
        return a1;
    }

    int HandlerToxicBoostStatus(int a1, int a2, int a3)
    {
        int result; // r0
        int Value;  // r0
        int v6;     // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_CONDITIONID);
            if (result == 4)
            {
                Value = BattleEventVar_GetValue(VAR_DAMAGE);
                v6 = checkHigher(Value / 2, 1);
                return BattleEventVar_RewriteValue(VAR_DAMAGE, v6);
            }
        }
        return result;
    }

    int HandlerCorrosion(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        // int PokeType;
        // int v6;               // r6
        // BattleMon *PokeParam; // r7

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result && BattleEventVar_GetValue(VAR_MOVETYPE) == TYPE_POISON)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_POISON, PokeType);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 4);
        }
        return result;
    }

    int HandlerDrySkinDamage(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVETYPE);
            if (result == 9)
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 8192);
            }
        }
        return result;
    }

    int HandlerToxicBoostDamage(int a1, int a2, int a3)
    {
        int result; // r0

        result = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_MOVETYPE);
            if (result == TYPE_POISON)
            {
                return BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
        return result;
    }

    // // int HandlerPickPocketStart(int a1, ServerFlow *a2, int a3, int *a4)
    // // {
    // //     int result;           // r0
    // //     BattleMon *PokeParam; // r0
    // //     result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
    // //     if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && getMoveFlag(BattleEventVar_GetValue(VAR_MOVEID), FLAG_CONTACT))
    // //     {
    // //         PokeParam = Handler_GetPokeParam(a2, a3);
    // //         result = BattleMon_GetHeldItem(PokeParam) != 0;
    // //         *a4 = result;
    // //     }
    // //     return result;
    // // }

    typedef struct
    {
        int triggerValue;
        ABILITY_HANDLER_FUNC function;
    } ABILITY_TRIGGERTABLE;

    ABILITY_TRIGGERTABLE AbilityTriggerTable[] =
        {
            // {0x2D, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders},
            // {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},

            {0x47, (ABILITY_HANDLER_FUNC)HandlerFriendGuard}, // 0
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 1
            {0x3B, (ABILITY_HANDLER_FUNC)HandlerPlusMinus},   // 2
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 3
            {0x76, (ABILITY_HANDLER_FUNC)HandlerHealer},      // 4
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerTelepathy},   // 5

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToughClaws}, // 6

            {0x13, (ABILITY_HANDLER_FUNC)HandlerSlushRush},        // 7
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 8

            {0x3B, (ABILITY_HANDLER_FUNC)HandlerThickFat},         // 9
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 10

            {0x3B, (ABILITY_HANDLER_FUNC)HandlerGuts},        // 11
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 12

            {0x13, (ABILITY_HANDLER_FUNC)HandlerQuickFeet},     // 13
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 14

            {0x38, (ABILITY_HANDLER_FUNC)HandlerFlareBoost},  // 15
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI}, // 16

            {0x6B, (ABILITY_HANDLER_FUNC)HandlerPoisonHeal},    // 17
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI}, // 18

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},       // 19
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},    // 20
            {0x6B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 21

            {0x47, (ABILITY_HANDLER_FUNC)HandlerFluffy},           // 22
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23

            {0x2D, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders}, // 24
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},        // 25

            {0x3E, (ABILITY_HANDLER_FUNC)HandlerCorrosion}, // 26

            {0x3C, (ABILITY_HANDLER_FUNC)HandlerMarvelScale},      // 27
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPreParalysisOnAI}, // 28

            {0x7F, (ABILITY_HANDLER_FUNC)HandlerRainDish},              // 29
            {0x65, (ABILITY_HANDLER_FUNC)HandlerWaterVeil},             // 30
            {0x67, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon}, // 31
            {0x8A, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},   // 32
            {0x55, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},   // 33
            {2, (ABILITY_HANDLER_FUNC)HandlerWaterVeilActionEnd},       // 34

            {0x5B, (ABILITY_HANDLER_FUNC)HandlerClearBodyCheck}, // 35
            {0x5C, (ABILITY_HANDLER_FUNC)HandlerClearBodyGuard}, // 36
            {0x7F, (ABILITY_HANDLER_FUNC)HandlerOvercoat},       // 37

            {0x7F, (ABILITY_HANDLER_FUNC)HandlerDrySkinWeather}, // 38
            {0x38, (ABILITY_HANDLER_FUNC)HandlerDrySkinDamage},  // 39
            {0x2D, (ABILITY_HANDLER_FUNC)HandlerDrySkinCheck},   // 40

            {0x54, (ABILITY_HANDLER_FUNC)HandlerPickupNew}, // 41

            {0x38, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},       // 42
            {0x55, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},    // 43
            {0x6B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 44
            {0x3B, (ABILITY_HANDLER_FUNC)HandlerToxicBoostDamage}
            // {0x81, (ABILITY_HANDLER_FUNC)HandlerPickPocketStart},
            // {0x83, (ABILITY_HANDLER_FUNC)HandlerPickPocketAction}
    };

    int *THUMB_BRANCH_EventAddFriendGuard(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[0].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPlus(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[2].triggerValue;
    }

    int *THUMB_BRANCH_EventAddHealer(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[4].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLightMetal(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[6].triggerValue;
    }

    int *THUMB_BRANCH_EventAddHeavyMetal(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[7].triggerValue;
    }

    int *THUMB_BRANCH_EventAddThickFat(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[9].triggerValue;
    }

    int *THUMB_BRANCH_EventAddGuts(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[11].triggerValue;
    }

    int *THUMB_BRANCH_EventAddQuickFeet(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddFlareBoost(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[15].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPoisonHeal(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[17].triggerValue;
    }

    int *THUMB_BRANCH_EventAddToxicBoost(unsigned int *a1)
    {
        *a1 = 4;
        return (int *)&AbilityTriggerTable[42].triggerValue;
    }

    int *THUMB_BRANCH_EventAddImmunity(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[22].triggerValue;
    }

    int *THUMB_BRANCH_EventAddOvercoat(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&AbilityTriggerTable[24].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLimber(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[26].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMarvelScale(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[27].triggerValue;
    }

    int *THUMB_BRANCH_EventAddRainDish(unsigned int *a1)
    {
        *a1 = 6;
        return (int *)&AbilityTriggerTable[29].triggerValue;
    }

    int *THUMB_BRANCH_EventAddClearBody(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&AbilityTriggerTable[35].triggerValue;
    }

    int *THUMB_BRANCH_EventAddDrySkin(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&AbilityTriggerTable[38].triggerValue;
    }

    int *THUMB_BRANCH_EventAddPickup(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&AbilityTriggerTable[41].triggerValue;
    }

    // int *THUMB_BRANCH_EventAddPickpocket(unsigned int *a1){
    //     *a1 = 2;
    //     return (int *)&AbilityTriggerTable[41].triggerValue;
    // }

    int GetTypeEffectivenessAltered(Types a1, int a2)
    {
        TypeEffectiveness result;
        int typeChart[18][18];
        unsigned int v3;

        if (a1 == 18 || a2 == 18)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        if (a1 == TYPE_ICE)
        {
            v3 = FreezeDryTypeChart[a1][a2];
        }
        else if (a1 == TYPE_FIGHTING)
        {
            v3 = SkyUppercutTypeChart[a1][a2];
        }
        else if (a1 == TYPE_POISON)
        {
            v3 = CorrosionTypeChart[a1][a2];
        }

        switch (v3)
        {
        case 0:
            result = EFFECTIVENESS_IMMUNE;
            break;
        case 2:
            result = EFFECTIVENESS_1_2;
            break;
        case 4:
            result = EFFECTIVENESS_1;
            break;
        case 8:
            result = EFFECTIVENESS_2;
            break;
        default:
            result = EFFECTIVENESS_1;
        }
        return result;
    }

    // // void THUMB_BRANCH_HandlerRapidSpin(int a1, ServerFlow *a2, unsigned int a3)
    // // {
    // //     BattleMon *BattleMon;               // r6
    // //     HandlerParam_CureCondition *v6;     // r0
    // //     HandlerParam_CureCondition *v7;     // r0
    // //     bool IsEffectActive_2;              // r7
    // //     bool IsEffectActive_3;              // r6
    // //     HandlerParam_RemoveSideEffect *v10; // r1
    // //     unsigned int v11;                   // r3
    // //     HandlerParam_RemoveSideEffect *v12; // r0
    // //     bool IsEffectActive_1;              // [sp+0h] [bp-20h]
    // //     bool IsEffectActive_4;
    // //     bool SideFromMonID; // [sp+4h] [bp-1Ch]
    // //     if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    // //     {
    // //         BattleMon = Handler_GetPokeParam(a2, a3);
    // //         if (BattleMon_CheckIfMoveCondition(BattleMon, CONDITION_LEECHSEED))
    // //         {
    // //             v6 = (HandlerParam_CureCondition *)BattleHandler_PushWork(a2, EFFECT_CURE_STATUS, a3);
    // //             v6->poke_cnt = 1;
    // //             v6->pokeID[0] = a3;
    // //             v6->sickCode = CONDITION_LEECHSEED;
    // //             BattleHandler_PopWork(a2, v6);
    // //         }
    // //         if (BattleMon_CheckIfMoveCondition(BattleMon, CONDITION_BIND))
    // //         {
    // //             v7 = (HandlerParam_CureCondition *)(a2, EFFECT_CURE_STATUS, a3);
    // //             v7->poke_cnt = 1;
    // //             v7->pokeID[0] = a3;
    // //             v7->sickCode = CONDITION_BIND;
    // //             BattleHandler_PopWork(a2, v7);
    // //         }
    // //         SideFromMonID = GetSideFromMonID(a3);
    // //         IsEffectActive_1 = j_j_BattleSideStatus_IsEffectActive_1(SideFromMonID, SIDEEFF_SPIKES);
    // //         IsEffectActive_2 = j_j_BattleSideStatus_IsEffectActive_2(SideFromMonID, SIDEEFF_TOXIC_SPIKES);
    // //         IsEffectActive_3 = j_j_BattleSideStatus_IsEffectActive_3(SideFromMonID, SIDEEFF_STEALTH_ROCK);
    // //         IsEffectActive_4 = BattleSideStatus_IsEffectActive(SideFromMonID, SIDEEFF_LUCKY_CHANT);
    // //         if (IsEffectActive_1 || IsEffectActive_2 || IsEffectActive_3 || IsEffectActive_4)
    // //         {
    // //             v10 = (HandlerParam_RemoveSideEffect *)BattleHandler_PushWork(a2, EFFECT_REMOVE_SIDE_EFFECT, a3);
    // //             v11 = 1;
    // //             v10->side = SideFromMonID;
    // //             v10->flags[0] = 3;
    // //             do
    // //             {
    // //                 v12 = (v10 + v11++);
    // //                 v12->flags[0] = 0;
    // //             } while (v11 < 3);
    // //             if (IsEffectActive_4 && v10->flags[0] > 1u)
    // //             {
    // //                 v10->flags[1] |= 0b00100000;
    // //             }
    // //             if (IsEffectActive_1 && v10->flags[0] > 1u)
    // //             {
    // //                 v10->flags[1] |= 0b01000000;
    // //             }
    // //             if (IsEffectActive_2 && v10->flags[0] > 1u)
    // //             {
    // //                 v10->flags[1] |= 0b10000000;
    // //             }
    // //             if (IsEffectActive_3 && v10->flags[0] > 2u)
    // //             {
    // //                 v10->flags[2] |= 0b00000001;
    // //             }
    // //             BattleHandler_PopWork(a2, v10);
    // //         }
    // //     }
    // // }

    void THUMB_BRANCH_HandlerSkullBash(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 556);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_DEFENSE;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerMeteorBeam(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 863);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
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

    // // void HandlerSkyAttack
    void HandlerSkyAttack(int a1, ServerFlow *a2, unsigned int *a3)
    {
        k::Printf("\nAre we inside?\n");
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 550);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

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

    // // void HandlerElectroShot
    void HandlerElectroShotCharge(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 866);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
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

    // // void HandlerIngrain

    int NewHandlerSkyUppercut(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        // int PokeType;
        // int v6;               // r6
        // BattleMon *PokeParam; // r7
        // int resultdata;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // // k::Printf("\n4. Result is Type Effectiveness is %d\n", result);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_FIGHTING, PokeType);
            // k::Printf("\nFinal Type Effectiveness is %d\n\n", result);
            // BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, result);
            // result = BattleEventVar_RewriteValue(VAR_TYPEEFFECTIVENESS, result);
            // k::Printf("\nReturn value is %d\n\n", result);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 3);
        }
        return result;
    }

    int HandlerFreezeDry(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        int PokeType;
        int v6;               // r6
        BattleMon *PokeParam; // r7

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            // v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_DEFENDING_MON);
            // PokeParam = Handler_GetPokeParam(a2, v6);
            // PokeType = BattleMon_GetPokeType(PokeParam);
            // result = GetTypeEffectivenesssVsMonAltered(TYPE_ICE, PokeType);
            return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 2);
        }
        return result;
    }

    int HandlerSwallowCheckFail(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0
        int HeldItem;         // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);
            if (!HeldItem)
            {
                return BattleEventVar_RewriteValue(VAR_FAILCAUSE, 26);
            }
            if (!PML_ItemIsBerry(HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_FAILCAUSE, 26);
            }
            if (!Handler_CheckItemUsable(a2, a3))
            {
                return BattleEventVar_RewriteValue(VAR_FAILCAUSE, 26);
            }
        }
        return result;
    }

    int HandlerSwallowHeal(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *PokeParam; // r0
        int Count;            // r0
        int v8;               // r1

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetPokeParam(a2, a3);

            if (PML_ItemIsBerry(PokeParam->HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_RATIO, 3072);
            }
            // return BattleEventVar_RewriteValue(VAR_RATIO, 1024);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerElectroBall(int a1, ServerFlow *a2, int a3)
    {
        int result;            // r0
        BattleMon *PokeParam;  // r5
        unsigned __int8 Value; // r0
        BattleMon *v8;         // r6
        int v9;                // r5
        int v10;               // r0
        int v11;               // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetPokeParam(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 > v10)
            {
                v11 = 120;
            }
            else
            {
                v11 = 60;
            }
            return BattleEventVar_RewriteValue(VAR_MOVEPOWER, v11);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerGyroBall(int a1, ServerFlow *a2, int a3)
    {
        int result;            // r0
        BattleMon *PokeParam;  // r5
        unsigned __int8 Value; // r0
        BattleMon *v8;         // r6
        int v9;                // r5
        int v10;               // r0
        int v11;               // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetPokeParam(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 < v10)
            {
                v11 = 120;
            }
            else
            {
                v11 = 60;
            }
            return BattleEventVar_RewriteValue(VAR_MOVEPOWER, v11);
        }
        return result;
    }

    int THUMB_BRANCH_HandlerSleepTalk(int r0_0, ServerFlow *r1_0, int a3, int *a4)
    {
        int result;             // r0
        unsigned int v6;        // r5
        unsigned int i;         // r6
        int ID;                 // r4
        unsigned int v9;        // r1
        int v10;                // r5
        int v11;                // r4
        unsigned int MoveCount; // [sp+8h] [bp-20h]
        BattleMon *PokeParam;   // [sp+Ch] [bp-1Ch]

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            PokeParam = Handler_GetPokeParam(r1_0, a3);
            // result = BattleMon_CheckIfMoveCondition(PokeParam, CONDITION_SLEEP);
            // if (result)
            // {
            MoveCount = BattleMon_GetMoveCount(PokeParam);
            v6 = 0;
            for (i = 0; v6 < MoveCount; v6 = (v6 + 1))
            {
                ID = Move_GetID(PokeParam, v6);
                if (!j_j_IsSleepTalkUncallableMove(ID) && ID != 156 && !getMoveFlag(ID, FLAG_REQUIRES_CHARGE))
                {
                    v9 = i;
                    i = (i + 1);
                    a4[v9] = ID;
                }
            }
            if (i)
            {
                v10 = *(a4 + ((4 * BattleRandom(i)) & 0x3FF));
                v11 = Handler_ReqMoveTargetAuto(r1_0, a3, v10);
                BattleEventVar_RewriteValue(VAR_MOVEID, v10);
                return BattleEventVar_RewriteValue(VAR_POKE_POS, v11);
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVEFAILFLAG, 1);
            }
            //}
        }
        return result;
    }

    void HandlerSwallowEnd(int a1, ServerFlow *a2, int a3, int *a4)
    {
        BattleMon *PokeParam;     // r0
        HandlerParam_Header *v8;  // r0
        HandlerParam_Message *v7; // r4
        HandlerParam_ActivateItem *v9;

        u16 HeldItem;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && !*a4)
        {
            PokeParam = Handler_GetPokeParam(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);

            if (PML_ItemIsBerry(HeldItem))
            {
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup((u16 *)&v7->str, 2u, 1159);
                BattleHandler_AddArg((u16 *)&v7->str, a3);
                BattleHandler_AddArg((u16 *)&v7->str, HeldItem);
                BattleHandler_PopWork(a2, v7);

                v9 = (HandlerParam_ActivateItem *)BattleHandler_PushWork(a2, EFFECT_ACTIVATEITEM, a3);
                v9->header.flags |= 0x1000000u;
                v9->itemID = (int)HeldItem;
                v9->pokeID = a3;
                BattleHandler_PopWork(a2, v9);

                v8 = (HandlerParam_Header *)BattleHandler_PushWork(a2, EFFECT_CONSUMEITEM, a3);
                v8[1].flags = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }

    void HandlerTeleportEffect(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v5; // r5
        HandlerParam_Switch *v7;  // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && Handler_GetFightEnableBenchPokeNum(a2, a3))
        {
            if (Handler_CheckReservedMemberChangeAction(a2))
            {
                v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup((u16 *)&v5->str, 2u, 767);
                BattleHandler_AddArg((u16 *)&v5->str, a3);
                BattleHandler_PopWork(a2, v5);
                v7 = (HandlerParam_Switch *)BattleHandler_PushWork(a2, EFFECT_SWITCH, a3);
                v7->pokeID = a3;
                v7->fIntrDisable = 1;
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

    int THUMB_BRANCH_HandlerIronFist(int a1, int a2, int a3)
    {
        int result;             // r0
        unsigned __int16 Value; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_MOVEID);
            result = getMoveFlag(Value, FLAG_PUNCH);
            if (result)
            {
                return BattleEventVar_MulValue(VAR_MOVEPOWERRATIO, 5325);
            }
        }
        return result;
    }

    // void HandlerStickyWeb(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     int Permanent;      // r4           // r4
    //     bool SideFromMonID; // r0
    //     Permanent = 1;
    //     SideFromMonID = GetSideFromOpposingMonID(a3);
    //     CommonCreateSideEffect(a1, a2, a3, a4, SideFromMonID, 5, Permanent, 148);
    // }

    // void HandlerSideStickyWeb(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    // {
    //     HandlerParam_ChangeStatStage *v3;
    //     int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
    //     if (currentSide == GetSideFromMonID(currentSlot))
    //     {
    //         BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
    //         v3 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, currentSlot);
    //         v3->poke_cnt = 1;
    //         v3->pokeID[0] = currentSlot;
    //         v3->rankType = STATSTAGE_SPEED;
    //         v3->rankVolume = -1;
    //         BattleHandler_PopWork(serverFlow, v3);
    //     }
    // }

    typedef struct
    {
        int triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;

    MOVE_TRIGGERTABLE MoveTriggerTable[] =
        {
            {0x96, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
            {0x3E, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut}, // BattleEvent_CheckTypeEffectiveness
            {0x3E, (MOVE_HANDLER_FUNC)HandlerFreezeDry},
            {0x94, (MOVE_HANDLER_FUNC)HandlerElectroShotRain},
            {0x96, (MOVE_HANDLER_FUNC)HandlerElectroShotCharge},
            {0x96, (MOVE_HANDLER_FUNC)HandlerSkyAttack},

            {0x1F, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
            {0x8F, (MOVE_HANDLER_FUNC)HandlerSwallowHeal},
            {0x27, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

            {0x1F, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
            {0x81, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
            {0x27, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
            //{0x39, (MOVE_HANDLER_FUNC)HandlerBodyPress}

            {0x96, (MOVE_HANDLER_FUNC)HandlerSkyAttack},

            {0x1F, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
            {0x81, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
            {0x27, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},

            {0xA0, (MOVE_HANDLER_FUNC)HandlerTeleportEffect},
            //{0x78, (MOVE_HANDLER_FUNC)HandlerUturn},
            {0x86, (MOVE_HANDLER_FUNC)HandlerUturn},
            //{0x27, (MOVE_HANDLER_FUNC)HandlerUturn}
            //{0xA1, (MOVE_HANDLER_FUNC)HandlerStickyWeb},

            //{0x55, (MOVE_HANDLER_FUNC)HandlerSideStickyWeb}
    };

    // typedef struct
    // {
    //     int triggerValue;
    //     SIDE_HANDLER_FUNC function;
    // } SIDE_TRIGGERTABLE;

    // SIDE_TRIGGERTABLE SideTriggerTable[] =
    //     {
    //         {0x55, (SIDE_HANDLER_FUNC)HandlerSideStickyWeb}
    // };

    // int *THUMB_BRANCH_EventAddSideLuckyChant(int *a1)
    // {
    //     *a1 = 1;
    //     return (int *)&SideTriggerTable[0].triggerValue;
    // }

    // Meteor Beam
    int *THUMB_BRANCH_EventAddFreezeShock(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[0].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSkyUppercut(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[1].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMiracleEye(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[2].triggerValue;
    }

    int *THUMB_BRANCH_EventAddForesight(unsigned int *a1)
    {
        *a1 = 2;
        return (int *)&MoveTriggerTable[3].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSwallow(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&MoveTriggerTable[6].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSpitUp(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&MoveTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSkyAttack(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[12].triggerValue;
    }

    int *THUMB_BRANCH_EventAddStockpile(unsigned int *a1)
    {
        *a1 = 3;
        return (int *)&MoveTriggerTable[13].triggerValue;
    }

    int *THUMB_BRANCH_EventAddTeleport(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[16].triggerValue;
    }

    int *THUMB_BRANCH_EventAddLockOn(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[17].triggerValue;
    }

    int THUMB_BRANCH_ServerControl_MoveExecuteCheck1(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        int v7;                          // r6
        int v8;                          // r0
        int v9;                          // r1
        ConditionData MoveConditionData; // r0
        int PreviousMove;                // r0
        int ID;                          // r0
        int v15;                         // [sp+Ch] [bp-24h]
        MoveCondition Status;            // [sp+10h] [bp-20h]

        v15 = 0;
        ServerControl_CheckMoveExeSleepCure(a1, a2);
        Status = BattleMon_GetStatus(a2);
        if (Status != CONDITION_SLEEP || (v7 = 2, ServerEvent_MoveExecuteFail(a1, a2, a3, 2)))
        {
            v15 = ServerControl_CheckMoveExeFreezeThaw(a1, a2, a3);
            Status = BattleMon_GetStatus(a2);
            if (Status == CONDITION_FREEZE && !v15)
            {
                v7 = 4;
                goto LABEL_50;
            }
            v8 = (int)*(&a1) + 0x1F7A + 2;
            if (v8 == 4)
            {
                v7 = 22;
                goto LABEL_50;
            }
            if (v8 == 2)
            {
                v7 = 23;
                goto LABEL_50;
            }
            if (!a4)
            {
                v9 = Move_SearchIndex(a2, a3);
                if (v9 != 4 && !Move_GetPP(a2, v9))
                {
                    v7 = 1;
                    goto LABEL_50;
                }
            }
            v7 = ServerEvent_CheckMoveExecute(a1, a2, a3, BattleEvent_MoveExecuteCheck1);
            if (!v7)
            {
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FOCUSPUNCHFAIL))
                {
                    v7 = 7;
                    goto LABEL_50;
                }
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FLINCH))
                {
                    v7 = 6;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_DISABLEMOVE) && a3 != 165)
                {
                    MoveConditionData = BattleMon_GetMoveCondition(a2, CONDITION_DISABLEMOVE);
                    if (a3 == Condition_GetParam(MoveConditionData))
                    {
                        v7 = 9;
                        goto LABEL_50;
                    }
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_HEALBLOCK) && getMoveFlag(a3, FLAG_HEALING))
                {
                    v7 = 13;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_GRAVITY) && getMoveFlag(a3, FLAG_GROUNDED_BY_GRAVITY))
                {
                    v7 = 20;
                    goto LABEL_50;
                }
                if (a3 == 165)
                {
                    goto LABEL_60;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_ENCORE) && (PreviousMove = BattleMon_GetPreviousMove(a2), PreviousMove != 165) && PreviousMove != a3 || BattleMon_CheckIfMoveCondition(a2, CONDITION_MOVELOCK) && a3 != BattleMon_GetPreviousMoveID(a2))
                {
                    v7 = 17;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_TAUNT) && !PML_MoveIsDamaging(a3))
                {
                    v7 = 10;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_IMPRISON) && BattleField_CheckImprison(a1->pokeCon, a2, a3))
                {
                    v7 = 12;
                }
                else
                {
                LABEL_60:
                    if (ServerControl_CheckConfusionHit(a1, a2))
                    {
                        v7 = 5;
                    }
                    else if (Status == CONDITION_PARALYSIS && a2->Ability != 63 && a2->Ability != 95 && RollEffectChance(0x19u))
                    {
                        v7 = 3;
                    }
                    else if (ServerControl_CheckAttract(a1, a2))
                    {
                        v7 = 8;
                    }
                }
            }
        }
    LABEL_50:
        if (v7)
        {
            ServerControl_MoveExecuteFail(a1, a2, a3, v7);
            return 1;
        }
        else
        {
            if (Status == CONDITION_SLEEP)
            {
                ServerDisplay_MoveExecuteFailMessage(a1, a2, a3, 2u);
                ServerDisplay_AddEffectAtPosition(a1, a2, 598);
            }
            else if (v15)
            {
                if (Status == CONDITION_FREEZE)
                {
                    ServerDisplay_CureStatus(a1, a2, 3, 0);
                    ID = BattleMon_GetID(a2);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 303, ID, a3, -65536);
                }
            }
            return 0;
        }
    }

    // void EndOfCharge()
    // {
    // }

    // int checkState(BattleMon *PokeParam)
    // {
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_SHADOWFORCE))
    //     {
    //         return 1;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_FLY))
    //     {
    //         return 2;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_DIG))
    //     {
    //         return 3;
    //     }
    //     if (BattleMon_GetConditionFlag(PokeParam, CONDITIONFLAG_DIVE))
    //     {
    //         return 4;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    // int checkScript(int a1)
    // {
    //     if (a1 == 1)
    //     {
    //         return 1168;
    //     }
    //     if (a1 == 2)
    //     {
    //         return 1171;
    //     }
    //     if (a1 == 3)
    //     {
    //         return 1165;
    //     }
    //     if (a1 == 4)
    //     {
    //         return 1177;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    // int HandlerPursuitStartCharge(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     int result;         // r0
    //     unsigned int Value; // r6
    //     int v8[6];          // [sp+0h] [bp-18h] BYREF
    //     int moveID;
    //     int state;
    //     BattleMon *PokeParam;
    //     HandlerParam_Message *v5; // r6

    //     PokeParam = Handler_GetPokeParam(a2, a3);
    //     k::Printf("\nLayer One: We are inside the function did we get this far?\n");
    //     if (checkState(PokeParam))
    //     {
    //         v8[1] = a4;
    //         result = Handler_GetThisTurnAction(a2, a3, v8);
    //         k::Printf("\nLayer Two: We are inside the function did we get this far?\n");
    //         if (result)
    //         {
    //             Value = BattleEventVar_GetValue(VAR_TARGETMONID);
    //             result = MainModule_IsAllyMonID(Value, a3);
    //             if (!result)
    //             {
    //                 k::Printf("\nLayer Three: We are inside the function did we get this far?\n");
    //                 Handler_PokeIDToPokePos(a2, Value);
    //                 Handler_PokeIDToPokePos(a2, a3);
    //                 result = Handler_IsTargetInRange(a2, a3, Value, 0);
    //                 if (!result)
    //                 {
    //                     k::Printf("\nWe are inside the function did we get this far?\n");
    //                     v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //                     BattleHandler_StrSetup((u16 *)&v5->str, 2u, checkScript(checkState(PokeParam)));
    //                     BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
    //                     BattleHandler_PopWork(a2, v5);

    //                     return Handler_AddSwitchOutInterrupt((int)&a2, a3);
    //                 }
    //             }
    //         }
    //     }
    //     return result;
    // }

    // void SwitchOutInterruptDig(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup((u16 *)&v5->str, 2u, 1165);
    //         BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptShadowForce(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup((u16 *)&v5->str, 2u, 1168);
    //         BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptFly(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup((u16 *)&v5->str, 2u, 1171);
    //         BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptBounce(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup((u16 *)&v5->str, 2u, 1174);
    //         BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // void SwitchOutInterruptDive(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     HandlerParam_Message *v5; // r6

    //     if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    //     {
    //         v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
    //         BattleHandler_StrSetup((u16 *)&v5->str, 2u, 1177);
    //         BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
    //         BattleHandler_PopWork(a2, v5);
    //     }
    // }

    // MOVE_TRIGGERTABLE MoveTriggerTable2[] =
    //     {
    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerDig},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerShadowForce},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},
    //         {0x2E, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
    //         {0x81, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
    //         {0x84, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerFly},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerBounce},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    //         {0x53, (MOVE_HANDLER_FUNC)HandlerPursuitStartCharge},
    //         {0x95, (MOVE_HANDLER_FUNC)HandlerDive},
    //         {0x98, (MOVE_HANDLER_FUNC)EndOfCharge},

    // };

    // int *THUMB_BRANCH_EventAddDig(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[0].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddShadowForce(unsigned int *a1)
    // {
    //     *a1 = 6;
    //     return (int *)&MoveTriggerTable2[3].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddFly(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[9].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddBounce(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[12].triggerValue;
    // }

    // int *THUMB_BRANCH_EventAddDive(unsigned int *a1)
    // {
    //     *a1 = 3;
    //     return (int *)&MoveTriggerTable2[15].triggerValue;
    // }
}