#include "codeinjection_new.h"
#include "kPrint.h"

// Uses esdb_NewBattle.yml

extern "C"
{

    bool checkIfConsumableItem(int a1)
    {
        return (PML_ItemIsBerry(a1) ||
                a1 == IT0290_FAIRY_GEM ||
                a1 == IT0043_BERRY_JUICE ||
                (a1 >= IT0545_ABSORB_BULB && a1 <= IT0564_NORMAL_GEM) ||
                a1 == IT0291_WEAKNESS_POLICY ||
                a1 == IT0274_MYSTERY_DEVICE ||
                a1 == IT0542_RED_CARD ||
                a1 == IT0292_CLRS_BOOSTER ||
                a1 == IT0294_PROTO_BOOSTER ||
                a1 == IT0286_CLRS_ARMOR ||
                a1 == IT0254_PROTO_ARMOR ||
                a1 == IT0315_PROTO_ACCELERATOR ||
                a1 == IT0318_CLRS_ACCELERATOR ||
                a1 == IT0314_CLRS_INVENTION ||
                a1 == IT0539_EJECT_PACK ||
                a1 == IT0547_EJECT_BUTTON ||
                a1 == IT0275_FOCUS_SASH ||
                a1 == IT0219_MENTAL_HERB ||
                a1 == IT0214_WHITE_HERB ||
                a1 == IT0271_POWER_HERB ||
                a1 == IT0541_AIR_BALLOON ||
                a1 == IT0136_TRICKSTER_HERB ||
               a1 == IT0230_FOCUS_BAND || 
               a1 == IT0306_TERA_B_POLICY || 
               a1 == IT0256_BLUNDER_POLICY || 
               a1 == IT0305_TERA_W_POLICY || 
               a1 == IT0302_TERA_SASH);
    }

    bool checkForPaybackBoost(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon)
    {
        int *ActionOrderAttackingMon;
        int *ActionOrderDefendingMon;

        if (BattleMon_GetTurnFlag(DefendingMon, TURNFLAG_ACTIONDONE))
        {
            return true;
        }
        ActionOrderAttackingMon = ActionOrder_SearchByMonID(a1, AttackingMon->ID);
        ActionOrderDefendingMon = ActionOrder_SearchByMonID(a1, DefendingMon->ID);

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

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            DefendingMon = Handler_GetBattleMon(a2, Value);
            AttackingMon = Handler_GetBattleMon(a2, result);

            paybackBoost = checkForPaybackBoost(a2, AttackingMon, DefendingMon);

            if (paybackBoost)
            {
                // k::Printf("\n\nWe got the payback boost babyyyyy!\n\n");
                return HandlerCommon_MultiplyBasePower(2);
            }
        }
        return result;
    }

    void THUMB_BRANCH_HandlerDefenseCurl(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_SetConditionFlag *v5; // r0
        HandlerParam_Message *v6;
        int messageId;

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {

            if (BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE111_DEFENSE_CURL)
            {
                messageId = 1270;
            }
            else if (BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE112_BARRIER)
            {
                messageId = 1291;
            }
            else
            {
                messageId = 1273;
            }

            k::Printf("\nWe made it into this handler at least?\n");
            v6 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v6->str, 2u, messageId);
            BattleHandler_AddArg(&v6->str, (int)a3);
            BattleHandler_PopWork(a2, v6);

            v5 = (HandlerParam_SetConditionFlag *)BattleHandler_PushWork(a2, EFFECT_SET_CONDITION_FLAG, (int)a3);
            v5->monID = (int)a3;
            v5->flag = CONDITIONFLAG_DEFENSECURL;
            BattleHandler_PopWork(a2, v5);
        }
    }

    void THUMB_BRANCH_HandlerSkullBash(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 556);
            BattleHandler_AddArg(&v5->str, (int)a3);
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
            BattleHandler_StrSetup(&v5->str, 2u, 863);
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

    // // void HandlerSkyAttack
    void HandlerSkyAttack(int a1, ServerFlow *a2, unsigned int *a3)
    {
        // k::Printf("\nAre we inside?\n");
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v5->str, 2u, 550);
            BattleHandler_AddArg(&v5->str, (int)a3);
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
            PokeParam = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);
            if (!HeldItem)
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
            if (!PML_ItemIsBerry(HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            }
            if (!Handler_CheckItemUsable(a2, a3))
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
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
            PokeParam = Handler_GetBattleMon(a2, a3);

            if (PML_ItemIsBerry(PokeParam->HeldItem))
            {
                return BattleEventVar_RewriteValue(VAR_RATIO, 3072);
            }
            // return BattleEventVar_RewriteValue(VAR_RATIO, 1024);
        }
        return result;
    }

    MoveID NEW_PROTECT_COUNTER_MOVES[8] = {
        MOVE203_ENDURE, MOVE182_PROTECT, MOVE197_DETECT, MOVE469_WIDE_GUARD, MOVE501_QUICK_GUARD, MOVE376_SPIKY_SHIELD,
        MOVE462_SILK_TRAP, MOVE262_OBSTRUCT};

    void THUMB_BRANCH_HandlerProtectStart(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *BattleMon;        // r0
        int PreviousMoveID;          // r0
        int v7;                      // r3
        HandlerParam_SetCounter *v8; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon = Handler_GetBattleMon(a2, (int)a3);
            PreviousMoveID = BattleMon_GetPreviousMoveID(BattleMon);
            v7 = 0;
            while (PreviousMoveID != NEW_PROTECT_COUNTER_MOVES[v7])
            {
                if (++v7 >= 7)
                {
                    v8 = (HandlerParam_SetCounter *)BattleHandler_PushWork(a2, EFFECT_COUNTER, (int)a3);
                    v8->pokeID = (int)a3;
                    v8->counterID = COUNTER_PROTECT;
                    v8->value = 0;
                    BattleHandler_PopWork(a2, v8);
                    return;
                }
            }
        }
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
            PokeParam = Handler_GetBattleMon(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetBattleMon(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 > v10)
            {
                v11 = 110;
            }
            else
            {
                v11 = 55;
            }
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
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
            PokeParam = Handler_GetBattleMon(a2, a3);
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            v8 = Handler_GetBattleMon(a2, Value);
            v9 = Handler_CalculateSpeed(a2, PokeParam, 0);
            v10 = Handler_CalculateSpeed(a2, v8, 0);
            if (v9 < v10)
            {
                v11 = 110;
            }
            else
            {
                v11 = 55;
            }
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
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
            PokeParam = Handler_GetBattleMon(r1_0, a3);
            result = BattleMon_CheckIfMoveCondition(PokeParam, CONDITION_SLEEP);
            if (result)
            {
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
                    BattleEventVar_RewriteValue(VAR_MOVE_ID, v10);
                    return BattleEventVar_RewriteValue(VAR_POKE_POS, v11);
                }
                else
                {
                    return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                }
            }
        }
        return result;
    }

    int THUMB_BRANCH_BattleHandler_DelayMoveDamage(ServerFlow *a1, HandlerParam_DelayMoveDamage *a2)
    {
        BattleMon *battleMon;       // r6
        BattleMon *v5;              // r7
        int v7;                     // r0
        MoveAnimCtrl *moveAnimCtrl; // r0
        MoveAnimCtrl *v9;           // r2
        unsigned __int8 v10;        // r1
        unsigned __int16 MoveID;    // [sp+8h] [bp-30h]
        __int16 v12;                // [sp+Ah] [bp-2Eh]
        __int16 v13;                // [sp+Ch] [bp-2Ch]
        __int16 v14[20];            // [sp+10h] [bp-28h] BYREF

        battleMon = PokeCon_GetBattleMon(a1->pokeCon, a2->attackerID);
        v5 = PokeCon_GetBattleMon(a1->pokeCon, a2->targetID);
        ServerEvent_GetMoveParam(a1, a2->MoveID, (int)battleMon, (MoveParam *)v14);
        j_j_PokeSet_Clear_12(a1->PokeSetDamaged);
        j_j_PokeSet_Clear_13(a1->PokeSetTemp);
        j_j_PokeSet_Add_18(a1->PokeSetTemp, v5);
        j_j_PokeSet_SetDefaultTargetCount_0(a1->PokeSetTemp, 1);
        j_j_PokeSet_RemoveDisablePoke_1(a1->PokeSetTemp);
        if (j_j_PokeSet_IsRemovedAll_0(a1->PokeSetTemp))
        {
            ServerDisplay_MoveFail(a1);
            return 0;
        }
        else
        {

            //  WHERE WE"RE GOING TO MODIFY THE CODE TO ADD THE HANDLERS
            if (Handler_GetExistFrontPokePos(a1, a2->attackerID) == 6)
            {
                if (!checkIfConsumableItem(BattleMon_GetHeldItem(battleMon)))
                {
                    ItemEvent_AddItem(battleMon);
                }
                AbilityEvent_AddItem(battleMon);
            }

            flowsub_CheckPokeHideAvoid(a1, v14, battleMon, a1->PokeSetTemp);
            flowsub_CheckNoEffect_TypeAffinity(a1, (MoveParam *)v14, battleMon, a1->PokeSetTemp, &a1->dmgAffRec);
            flowsub_CheckNoEffect_Protect(a1, v14, battleMon, a1->PokeSetTemp, &a1->dmgAffRec);
            flowsub_CheckWazaAvoid(a1, v14, battleMon, a1->PokeSetTemp);
            j_j_PokeSet_IsRemovedAll_4(a1->PokeSetTemp);

            if (j_j_PokeSet_IsRemovedAll_4(a1->PokeSetTemp))
            {
                // Remove the handlers before the turn statement
                if (!checkIfConsumableItem(BattleMon_GetHeldItem(battleMon)))
                {
                    ItemEvent_RemoveItem(battleMon);
                }
                AbilityEvent_RemoveItem(battleMon);
                return 0;
            }
            else
            {
                moveAnimCtrl = a1->moveAnimContr;
                MoveID = moveAnimCtrl->MoveID;
                v12 = *&moveAnimCtrl->attackerPos;
                v13 = *&moveAnimCtrl->effectIndex;
                MoveAnimCtrl_Init(moveAnimCtrl);
                MoveAnimCtrl_Setup(a1->moveAnimContr, a1, battleMon, a1->PokeSetTemp);
                a1->moveAnimContr->effectIndex = 1;
                ServerControl_DamageRoot(a1, (MoveParam *)v14, battleMon, a1->PokeSetTemp, &a1->dmgAffRec, 1);
                v9 = a1->moveAnimContr;
                v10 = v9->flags & 1;
                v9->MoveID = MoveID;
                *&v9->attackerPos = v12;
                *&v9->effectIndex = v13;

                // Remove the handlers before the turn statement
                if (!checkIfConsumableItem(BattleMon_GetHeldItem(battleMon)))
                {
                    ItemEvent_RemoveItem(battleMon);
                }
                AbilityEvent_RemoveItem(battleMon);
                return v10;
            }
        }
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
            PokeParam = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(PokeParam);

            if (PML_ItemIsBerry(HeldItem))
            {
                v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v7->str, 2u, 1159);
                BattleHandler_AddArg(&v7->str, a3);
                BattleHandler_AddArg(&v7->str, HeldItem);
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
                BattleHandler_StrSetup(&v5->str, 2u, 767);
                BattleHandler_AddArg(&v5->str, a3);
                BattleHandler_PopWork(a2, v5);
                v7 = (HandlerParam_Switch *)BattleHandler_PushWork(a2, EFFECT_SWITCH, a3);
                v7->pokeID = a3;
                v7->fIntrDisable = 1;
                BattleHandler_PopWork(a2, v7);
            }
        }
    }

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

    int THUMB_BRANCH_HandlerSnoreCheck2(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *BattleMon; // r4

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            if (BattleEventVar_GetValue(VAR_FAIL_CAUSE) == 2)
            {
                return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 0);
            }
            // else
            // {
            //     result = BattleMon_CheckIfMoveCondition(BattleMon, CONDITION_SLEEP);
            //     if (!result)
            //     {
            //         return BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, 26);
            //     }
            // }
        }
        return result;
    }

    void HandlerHowlIncreaseStats(int a1, ServerFlow *a2, unsigned int a3)
    {
        HandlerParam_ChangeStatStage *atkBoost;
        HandlerParam_ChangeStatStage *spABoost;
        HandlerParam_Message *message;
        int i;
        i = 0;
        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            atkBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
            atkBoost->poke_cnt = 1;
            atkBoost->pokeID[0] = a3;
            atkBoost->rankType = STATSTAGE_ATTACK;
            atkBoost->rankVolume = 1;
            atkBoost->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, atkBoost);
            spABoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
            spABoost->poke_cnt = 1;
            spABoost->pokeID[0] = a3;
            spABoost->rankType = STATSTAGE_SPECIAL_ATTACK;
            spABoost->rankVolume = 1;
            spABoost->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, spABoost);
            u8 *TempWork;              // r4
            unsigned int NumTargets;   // r5
            __int16 ExistFrontPokePos; // [sp+0h] [bp-18h]

            ExistFrontPokePos = Handler_PokeIDToPokePos(a2, a3);
            TempWork = Handler_GetTempWork(a2);

            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x400, TempWork);
            while (i < NumTargets)
            {
                message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&message->str, 2u, 1231);
                BattleHandler_AddArg(&message->str, TempWork[i]);
                BattleHandler_PopWork(a2, message);
                atkBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                atkBoost->poke_cnt = 1;
                atkBoost->pokeID[0] = TempWork[i];
                atkBoost->rankType = STATSTAGE_ATTACK;
                atkBoost->rankVolume = 1;
                atkBoost->fMoveAnimation = 1;
                BattleHandler_PopWork(a2, atkBoost);
                spABoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                spABoost->poke_cnt = 1;
                spABoost->pokeID[0] = TempWork[i];
                spABoost->rankType = STATSTAGE_SPECIAL_ATTACK;
                spABoost->rankVolume = 1;
                spABoost->fMoveAnimation = 1;
                BattleHandler_PopWork(a2, spABoost);
                i++;
            }
        }
    }

    void HandlerStickyWeb(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {
        ConditionData Permanent;   // r4
        int SideFromOpposingMonID; // r0
        int messageId;

        SideFromOpposingMonID = GetSideFromOpposingMonID(a3);

        messageId = (SideFromOpposingMonID == 1) ? 211 : 210;

        // k::Printf("\n%d\n", SideFromOpposingMonID);
        CommonCreateSideEffect(a1, a2, a3, a4, (unsigned char)SideFromOpposingMonID, 14, 1, messageId);
    }

    typedef struct
    {
        BattleEventType triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;

    MOVE_TRIGGERTABLE MeteorBeamHandlers[] = {
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
    };

    MOVE_TRIGGERTABLE SkyUppercutHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut}};

    MOVE_TRIGGERTABLE FreezeDryHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)HandlerFreezeDry},
    };

    MOVE_TRIGGERTABLE ElectroShotHandlers[] = {
        {EVENT_CHECK_CHARGE_UP_SKIP, (MOVE_HANDLER_FUNC)HandlerElectroShotRain},
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerElectroShotCharge},
    };

    MOVE_TRIGGERTABLE SkyAttackHandlers[] = {
        {EVENT_CHARGE_UP_START_DONE, (MOVE_HANDLER_FUNC)HandlerSkyAttack},
    };

    MOVE_TRIGGERTABLE SwallowHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
        {EVENT_RECOVER_HP, (MOVE_HANDLER_FUNC)HandlerSwallowHeal},
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    };

    MOVE_TRIGGERTABLE StockpileHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    };

    MOVE_TRIGGERTABLE SpitUpHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerSwallowCheckFail},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerSwallowEnd},
    };

    MOVE_TRIGGERTABLE TeleportHandlers[] = {
        {EVENT_UNCATEGORIZED_MOVE, (MOVE_HANDLER_FUNC)HandlerTeleportEffect},
    };

    MOVE_TRIGGERTABLE PartingShotHandlers[] = {
        {EVENT_DAMAGE_PROCESSING_END_HIT_3, (MOVE_HANDLER_FUNC)HandlerUturn},
    };

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

    MOVE_TRIGGERTABLE StickyWebHandlers[] = {
        {EVENT_UNCATEGORIZED_MOVE_NO_TARGET, (MOVE_HANDLER_FUNC)HandlerStickyWeb},
    };

    MOVE_TRIGGERTABLE SpikyShieldHandlers[] = {
        {EVENT_MOVE_SEQUENCE_START, (MOVE_HANDLER_FUNC)HandlerProtectStart},
        {EVENT_MOVE_EXECUTE_CHECK2, (MOVE_HANDLER_FUNC)HandlerProtectCheckFail},
        {EVENT_MOVE_EXECUTE_FAIL, (MOVE_HANDLER_FUNC)HandlerProtectResetCounter},
        {EVENT_UNCATEGORIZED_MOVE, (MOVE_HANDLER_FUNC)HandlerProtect},
    };

    MOVE_TRIGGERTABLE HowlHandlers[] = {
        {EVENT_UNCATEGORIZED_MOVE, (MOVE_HANDLER_FUNC)HandlerHowlIncreaseStats},
    };

    int NewHandlerNaturalGiftPower(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *BattleMon; // r0
        u16 HeldItem;         // r0
        int Param;            // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(BattleMon);
            Param = ItemGetParam(HeldItem, ITSTAT_NATURAL_GIFT_POWER);
            if (Param)
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_POWER, Param);
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_POWER, 80);
            }
        }
        return result;
    }

    int THUMB_BRANCH_HandlerStoredPower(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *BattleMon; // r6
        int v7;               // r4
        unsigned int i;       // r5
        int Value;            // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            v7 = 0;
            for (i = 0; i < 7; ++i)
            {
                result = BattleMon_GetValue(BattleMon, BattleMonValues[i]) - 6;
                if (result > 0)
                {
                    v7 += result;
                }
            }
            if (v7)
            {
                Value = BattleEventVar_GetValue(VAR_MOVE_POWER);
                return BattleEventVar_RewriteValue(VAR_MOVE_POWER, Value + 25 * v7);
            }
        }
        return result;
    }

    int NewHandlerNaturalGiftType(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        BattleMon *BattleMon; // r0
        u16 HeldItem;         // r0
        int Param;            // r0

        result = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == result)
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            HeldItem = BattleMon_GetHeldItem(BattleMon);
            Param = ItemGetParam(HeldItem, ITSTAT_NATURAL_GIFT_TYPE);
            if (Param)
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_TYPE, Param);
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_NORMAL);
            }
        }
        return result;
    }

    MOVE_TRIGGERTABLE NaturalGiftHandlers[] = {
        {EVENT_MOVE_PARAM, (MOVE_HANDLER_FUNC)NewHandlerNaturalGiftType},
        {EVENT_MOVE_BASE_POWER, (MOVE_HANDLER_FUNC)HandlerProtectCheckFail},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddNaturalGift(_DWORD *a1)
    {
        *a1 = 2;
        return NaturalGiftHandlers;
    }

    // Howl
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSpite(_DWORD *a1)
    {
        *a1 = 1;
        return HowlHandlers;
    }

    // Spiky Shield
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddTrumpCard(_DWORD *a1)
    {
        *a1 = 4;
        return SpikyShieldHandlers;
    }

    // Silk Trap
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddCrushGrip(_DWORD *a1)
    {
        *a1 = 4;
        return SpikyShieldHandlers;
    }

    // Baneful Bunker
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddFusionFlare(_DWORD *a1)
    {
        *a1 = 4;
        return SpikyShieldHandlers;
    }

    // Sticky Web
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddMagnitude(_DWORD *a1)
    {
        *a1 = 1;
        return StickyWebHandlers;
    }
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

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddFreezeShock(_DWORD *a1)
    {
        *a1 = 1;
        return MeteorBeamHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSkyUppercut(_DWORD *a1)
    {
        *a1 = 1;
        return SkyUppercutHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddMiracleEye(_DWORD *a1)
    {
        *a1 = 1;
        return FreezeDryHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddForesight(_DWORD *a1)
    {
        *a1 = 2;
        return ElectroShotHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSwallow(_DWORD *a1)
    {
        *a1 = 3;
        return SwallowHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSpitup(_DWORD *a1)
    {
        *a1 = 3;
        return SpitUpHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddStockpile(_DWORD *a1)
    {
        *a1 = 3;
        return StockpileHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddSkyAttack(_DWORD *a1)
    {
        *a1 = 1;
        return SkyAttackHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddTeleport(_DWORD *a1)
    {
        *a1 = 1;
        return TeleportHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddLockOn(_DWORD *a1)
    {
        *a1 = 1;
        return PartingShotHandlers;
    }

    //
    //
    //
    //
    // STOMPING TANTRUM, UPROAR, ETC
    //
    //
    //
    //

    int StompingTantrumHandler(int a1, ServerFlow *a2, int a3)
    {
        int result;     // r0
        BattleMon *mon; // r5
        int v11;        // r1

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            mon = Handler_GetBattleMon(a2, a3);

            if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                v11 = 150;
                Handler_SetMoveEffectIndex(a2, 1);
            }
            else
            {
                v11 = 75;
            }
            // k::Printf("\n\nThe move power is %d\n", v11);
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, v11);
        }
        return result;
    }

    MOVE_TRIGGERTABLE StompingTantrumHandlers[] = {
        {EVENT_MOVE_BASE_POWER, (MOVE_HANDLER_FUNC)StompingTantrumHandler}};

    // Stomping Tantrum Moves and Co.
    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddUproar(_DWORD *a1)
    {
        *a1 = 1;
        return StompingTantrumHandlers;
    }

    //
    //
    //
    //
    // PRESENT
    //
    //
    //
    //

    void THUMB_BRANCH_SAFESTACK_HandlerPresentRandomCheck(int a1, ServerFlow *a2, int a3, int *a4)
    {
        int Defending;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            Defending = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            if (MainModule_IsAllyMonID(a3, Defending))
            {
                *a4 = BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
            Handler_SetMoveEffectIndex(a2, *a4 != 0);
        }
    }

    void THUMB_BRANCH_SAFESTACK_HandlerPresentHeal(int a1, ServerFlow *a2, unsigned int *a3, unsigned int **a4)
    {
        int Value;                  // r6
        BattleMon *BattleMon;       // r7
        HandlerParam_RecoverHP *v9; // r5
        HandlerParam_Message *message;
        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && *a4)
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            BattleMon = Handler_GetBattleMon(a2, Value);
            if (BattleMon_IsFullHP(BattleMon))
            {
                message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&message->str, 2u, 210);
                BattleHandler_AddArg(&message->str, Value);
                BattleHandler_PopWork(a2, message);
            }
            else
            {
                v9 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, (int)a3);
                v9->pokeID = Value;
                v9->recoverHP = DivideMaxHPZeroCheck(BattleMon, 2u);
                BattleHandler_StrSetup(&v9->exStr, 2u, 387);
                BattleHandler_AddArg(&v9->exStr, Value);
                BattleHandler_PopWork(a2, v9);
            }
        }
    }

    int THUMB_BRANCH_HandlerPresentPower(int a1, int a2, int a3)
    {
        int result;      // r0
        int v5;          // r4
        unsigned int v6; // r0

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            return BattleEventVar_RewriteValue(VAR_MOVE_POWER, 90);
        }
        return result;
    }

    //
    //
    //
    //
    // POLLEN PUFF
    //
    //
    //
    //

    void HandlerPollenPuffCheck(int a1, ServerFlow *a2, int a3, int *a4)
    {
        int Defending;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            Defending = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            if (MainModule_IsAllyMonID(a3, Defending))
            {
                *a4 = BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
            }
        }
    }

    void HandlerPollenPuffHeal(int a1, ServerFlow *a2, unsigned int *a3, unsigned int **a4)
    {
        int Value;                  // r6
        BattleMon *BattleMon;       // r7
        HandlerParam_RecoverHP *v9; // r5
        HandlerParam_Message *message;
        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && *a4)
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            BattleMon = Handler_GetBattleMon(a2, Value);
            if (BattleMon_IsFullHP(BattleMon))
            {
                message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&message->str, 2u, 210);
                BattleHandler_AddArg(&message->str, Value);
                BattleHandler_PopWork(a2, message);
            }
            else
            {
                v9 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, (int)a3);
                v9->pokeID = Value;
                v9->recoverHP = DivideMaxHPZeroCheck(BattleMon, 2u);
                BattleHandler_StrSetup(&v9->exStr, 2u, 387);
                BattleHandler_AddArg(&v9->exStr, Value);
                BattleHandler_PopWork(a2, v9);
            }
            // BattleHandler_PopWork(a2, v9);
        }
    }

    MOVE_TRIGGERTABLE PollenPuffHandlers[] = {
        {EVENT_CHECK_DAMAGE_TO_RECOVER, (MOVE_HANDLER_FUNC)HandlerPollenPuffCheck},
        {EVENT_APPLY_DAMAGE_TO_RECOVER, (MOVE_HANDLER_FUNC)HandlerPollenPuffHeal},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddLunarDance(_DWORD *a1)
    {
        *a1 = 2;
        return PollenPuffHandlers;
    }

    //
    //
    //
    //
    // SACRED SWORD AND CHIP AWAY
    //
    //
    //
    //
    int HandlerChipAwayType(int a1, ServerFlow *a2, int a3)
    {
        int result;

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            result = BattleEventVar_GetValue(VAR_POKE_TYPE);
            if (result == TYPE_GHOST)
            {
                return BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 1);
            }
        }
        return result;
    }

    MOVE_TRIGGERTABLE ChipAwayHandlers[] = {
        {EVENT_BEFORE_DEFENDER_GUARD, (MOVE_HANDLER_FUNC)HandlerChipAwayCalcDamage},
        {EVENT_MOVE_ACCURACY_STAGE, (MOVE_HANDLER_FUNC)HandlerChipAwayHitCheck},
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (MOVE_HANDLER_FUNC)HandlerChipAwayType},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddChipAway(_DWORD *a1)
    {
        *a1 = 3;
        return ChipAwayHandlers;
    }

    void HandlerTeeterDanceSpeedBoost(int a1, ServerFlow *a2, int a3)
    {

        BattleMon *mon;
        HandlerParam_ChangeStatStage *speedBoost;

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleMon_IsStatChangeValid(Handler_GetBattleMon(a2, a3), VALUE_SPEED_STAGE, 1))
            {
                speedBoost = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                speedBoost->poke_cnt = 1;
                speedBoost->pokeID[0] = a3;
                speedBoost->rankType = STATSTAGE_SPEED;
                speedBoost->rankVolume = 1;
                speedBoost->fMoveAnimation = 1;
                BattleHandler_PopWork(a2, speedBoost);
            }
        }
    }

    MOVE_TRIGGERTABLE TeeterDanceHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerTeeterDanceSpeedBoost},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddGuardSwap(_DWORD *a1)
    {
        *a1 = 1;
        return TeeterDanceHandlers;
    }

    //
    //
    //
    //
    // GIGA IMPACT / HYPER BEAM
    //
    //
    //
    //
    void HandlerRecharge(int a1, ServerFlow *a2, int a3)
    {

        BattleMon *mon;
        HandlerParam_Message *message;

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            mon = Handler_GetBattleMon(a2, a3);

            if (!BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILED))
            {
                message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&message->str, 2u, 1249);
                BattleHandler_AddArg(&message->str, a3);
                BattleHandler_PopWork(a2, message);
            }
        }
    }

    MOVE_TRIGGERTABLE RechargeHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerRecharge},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddPowerSplit(_DWORD *a1)
    {
        *a1 = 1;
        return RechargeHandlers;
    }

    void HandlerScaleShotEnd(int a1, ServerFlow *a2, int a3)
    {

        BattleMon *mon;
        HandlerParam_ChangeStatStage *defense;
        HandlerParam_ChangeStatStage *speed;

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            mon = Handler_GetBattleMon(a2, a3);

            if (BattleMon_IsStatChangeValid(mon, VALUE_DEFENSE_STAGE, -1) || BattleMon_IsStatChangeValid(mon, VALUE_SPEED_STAGE, 1))
            {
                defense = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                defense->poke_cnt = 1;
                defense->pokeID[0] = a3;
                defense->fMoveAnimation = 1;
                defense->rankType = STATSTAGE_DEFENSE;
                defense->rankVolume = -1;
                BattleHandler_PopWork(a2, defense);
                speed = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                speed->poke_cnt = 1;
                speed->pokeID[0] = a3;
                speed->fMoveAnimation = 1;
                speed->rankType = STATSTAGE_SPEED;
                speed->rankVolume = 1;
                BattleHandler_PopWork(a2, speed);
            }
        }
    }

    MOVE_TRIGGERTABLE ScaleShotHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerScaleShotEnd},

    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddFeint(_DWORD *a1)
    {
        *a1 = 1;
        return ScaleShotHandlers;
    }

    MOVE_TRIGGERTABLE TormentHandlers[] = {
        {EVENT_MOVE_CONDITION_PARAM, (MOVE_HANDLER_FUNC)HandlerLeechSeed},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddTorment(_DWORD *a1)
    {
        *a1 = 1;
        return TormentHandlers;
    }

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddGrudge(_DWORD *a1)
    {
        *a1 = 1;
        return StompingTantrumHandlers;
    }

    MoveCondition TRI_ATTACK_STATUSES[3] = {CONDITION_BURN, CONDITION_FREEZE, CONDITION_PARALYSIS};

    int THUMB_BRANCH_HandlerTriAttack(int a1, int a2, int a3)
    {
        int result;       // r0
        MoveCondition v5; // r5
        int raw;          // r4

        result = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (a3 == result)
        {
            v5 = *(TRI_ATTACK_STATUSES + ((4 * BattleRandom(3u)) & 0x3FF));
            raw = MakeBasicStatus(v5).raw;
            BattleEventVar_RewriteValue(VAR_CONDITION_ID, v5);
            BattleEventVar_RewriteValue(VAR_CONDITION_ADDRESS, raw);
            return BattleEventVar_RewriteValue(VAR_EFFECT_CHANCE, 10);
        }
        return result;
    }

    //
    //
    //
    //
    // KNOCK OFF FIX
    //
    //
    //
    //

    int HandlerKnockOffPower(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        BattleMon *defender;
        BattleMon *BattleMon; // r0

        result = 65;
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            defender = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON));
            BattleMon = Handler_GetBattleMon(a2, a3);

            if (!HandlerCommon_CheckIfCanStealPokeItem(a2, a3, BattleEventVar_GetValue(VAR_DEFENDING_MON)))
            {
                if (BattleMon_GetHeldItem(defender))
                {
                    result = 97.5;
                }
            }
        }
        return BattleEventVar_RewriteValue(VAR_MOVE_POWER, result);
    };

    MOVE_TRIGGERTABLE KnockOffHandlers[] = {
        {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, (MOVE_HANDLER_FUNC)HandlerKnockOff},
        {EVENT_MOVE_BASE_POWER, (MOVE_HANDLER_FUNC)HandlerKnockOffPower}};

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddKnockOff(_DWORD *a1)
    {
        *a1 = 2;
        return KnockOffHandlers;
    }

    //
    //
    //
    //
    // GIGA IMPACT / HYPER BEAM
    //
    //
    //
    //
    void HandlerOverheatRecharge(int a1, ServerFlow *a2, int a3)
    {

        BattleMon *mon;
        HandlerParam_Message *message;
        int MoveID;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            mon = Handler_GetBattleMon(a2, a3);
            MoveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (!BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILED))
            {
                message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);

                if (MoveID == MOVE315_OVERHEAT)
                {
                    BattleHandler_StrSetup(&message->str, 2u, 1252);
                }
                else if (MoveID == MOVE434_DRACO_METEOR || MoveID == MOVE437_LEAF_STORM)
                {
                    BattleHandler_StrSetup(&message->str, 2u, 1267);
                }
                else
                {
                    BattleHandler_StrSetup(&message->str, 2u, 1255);
                }
                BattleHandler_AddArg(&message->str, a3);
                BattleHandler_PopWork(a2, message);
            }
        }
    }

    MOVE_TRIGGERTABLE OverheatHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (MOVE_HANDLER_FUNC)HandlerOverheatRecharge},
    };

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddWonderRoom(_DWORD *a1)
    {
        *a1 = 1;
        return OverheatHandlers;
    }

    //
    //
    //
    //
    //  CURSE
    //
    //
    //
    //

    MoveTarget THUMB_BRANCH_DetermineCurseTargetData(BattleMon *a1)
    {
        return TARGET_OTHER_SELECT;
    }

    void THUMB_BRANCH_HandlerCurse(int a1, ServerFlow *a2, int a3)
    {
        char effectIndex;                  // r6
        int Value;                         // r7
        HandlerParam_AddCondition *v7;     // r6
        HandlerParam_ChangeHP *v8;         // r6
        HandlerParam_ChangeStatStage *v9;  // r0
        HandlerParam_ChangeStatStage *v10; // r0
        HandlerParam_ChangeStatStage *v11; // r0
        BattleMon *BattleMon;              // [sp+0h] [bp-20h]

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon = Handler_GetBattleMon(a2, a3);

            if (BattleMon_GetValue(BattleMon, VALUE_CURRENT_HP) > 0)
            {
                Value = BattleEventVar_GetValue(VAR_TARGET_MON_ID);
                if (Value != 31)
                {
                    v7 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
                    v7->pokeID = Value;
                    v7->sickID = CONDITION_CURSE;
                    v7->sickCont = Condition_MakePermanent();
                    BattleHandler_StrSetup(&v7->exStr, 2u, 1064);
                    BattleHandler_AddArg(&v7->exStr, a3);
                    BattleHandler_AddArg(&v7->exStr, Value);
                    BattleHandler_PopWork(a2, v7);
                    v8 = (HandlerParam_ChangeHP *)BattleHandler_PushWork(a2, EFFECT_CHANGEHP, a3);
                    v8->pokeID[0] = a3;
                    v8->volume[0] = -DivideMaxHPZeroCheck(BattleMon, 2u);
                    v8->poke_cnt = 1;
                    v8->header.flags |= 0x1000000u;
                    BattleHandler_PopWork(a2, v8);
                }
            }
            effectIndex = 1;

            Handler_SetMoveEffectIndex(a2, effectIndex);
        }
    }

    //
    //
    //
    //
    //  BIND TEXT
    //
    //
    //
    //

    void THUMB_BRANCH_HandlerBindTextSet(BattleEventItem *a1, int a2, int a3)
    {
        HandlerParam_StrParams *Value; // r4
        int v6;                        // r5
        int SubID;                     // r0
        __int16 v8;                    // r2

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_CONDITION_ID) == 8)
        {
            Value = (HandlerParam_StrParams *)BattleEventVar_GetValue(VAR_WORK_ADDRESS);
            v6 = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            SubID = BattleEventItem_GetSubID(a1);
            if (IsEqual(SubID, MOVE463_MAGMA_STORM))
            {
                v8 = 830;
            }
            else if (IsEqual(SubID, MOVE250_WHIRLPOOL))
            {
                v8 = 824;
            }
            else if (IsEqual(SubID, MOVE083_FIRE_SPIN))
            {
                v8 = 827;
            }
            else if (IsEqual(SubID, MOVE020_BIND))
            {
                v8 = 803;
            }
            else if (IsEqual(SubID, MOVE128_CLAMP))
            {
                v8 = 817;
            }
            else if (IsEqual(SubID, MOVE328_SAND_TOMB))
            {
                v8 = 833;
            }
            else if (IsEqual(SubID, MOVE035_WRAP))
            {
                v8 = 810;
            }
            else if (IsEqual(SubID, MOVE171_NIGHTMARE))
            {
                v8 = 1207;
            }
            else if (IsEqual(SubID, MOVE286_IMPRISON))
            {
                v8 = 1210;
            }
            else if (IsEqual(SubID, MOVE090_FISSURE))
            {
                v8 = 1213;
            }
            else if (IsEqual(SubID, MOVE012_GUILLOTINE))
            {
                v8 = 1216;
            }
            else if (IsEqual(SubID, MOVE032_HORN_DRILL))
            {
                v8 = 1219;
            }
            else if (IsEqual(SubID, MOVE132_INFESTATION))
            {
                v8 = 1222;
            }
            else if (IsEqual(SubID, MOVE170_SNAP_TRAP))
            {
                v8 = 1225;
            }
            else if (IsEqual(SubID, MOVE377_ALLURING_VOICE))
            {
                v8 = 1276;
            }
            else
            {
            }
            BattleHandler_StrSetup(Value, 2u, v8);
            BattleHandler_AddArg(Value, v6);
            BattleHandler_AddArg(Value, a3);
            return;
        }
    };

    int THUMB_BRANCH_HandlerAttractCheckFail(int a1, ServerFlow *a2, int a3)
    {
        int result; // r0
        return result;
    }

#pragma region ImpossibeMoves

    int THUMB_BRANCH_IsUnselectableMove(BtlClientWk *a1, BattleMon *a2, int move, Btlv_StringParam *strparam)
    {
        ConditionData MoveCondition; // r0
        int HeldItem;                // r0
        ConditionData v10;           // r0
        int ID;                      // r0
        int v12;                     // r0
        int v13;                     // r0
        int v14;                     // r0
        int v15;                     // r0
        int v16;                     // r0
        int v17;                     // r0
        int choicedMove;             // [sp+0h] [bp-28h]
        int previousMove;            // [sp+4h] [bp-24h]

        if (move != 165)
        {
            if (CanMonUseHeldItem(a1, a2) && BattleMon_CheckIfMoveCondition(a2, CONDITION_CHOICELOCK))
            {
                MoveCondition = BattleMon_GetMoveCondition(a2, CONDITION_CHOICELOCK);
                choicedMove = Condition_GetParam(MoveCondition);
                if (Move_IsUsable(a2, choicedMove))
                {
                    if (choicedMove != move)
                    {
                        if (strparam)
                        {
                            Btlv_StringParam_Setup(strparam, 1, 99);
                            HeldItem = BattleMon_GetHeldItem(a2);
                            Btlv_StringParam_AddArg(strparam, HeldItem);
                            Btlv_StringParam_AddArg(strparam, choicedMove);
                        }
                        return 1;
                    }
                }
            }
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_ENCORE))
            {
                v10 = BattleMon_GetMoveCondition(a2, CONDITION_ENCORE);
                previousMove = Condition_GetParam(v10);
                if (move != previousMove)
                {
                    if (strparam)
                    {
                        Btlv_StringParam_Setup(strparam, 1, 100);
                        ID = BattleMon_GetID(a2);
                        Btlv_StringParam_AddArg(strparam, ID);
                        Btlv_StringParam_AddArg(strparam, previousMove);
                    }
                    return 1;
                }
            }

            // Hyper Beam
            if ((BattleMon_GetPreviousMove(a2) == MOVE063_HYPER_BEAM && move == MOVE063_HYPER_BEAM && !BattleMon_GetTurnFlag(a2, TURNFLAG_MOVEFAILEDLASTTURN)) || (BattleMon_GetPreviousMove(a2) == MOVE416_GIGA_IMPACT && move == MOVE416_GIGA_IMPACT && !BattleMon_GetTurnFlag(a2, TURNFLAG_MOVEFAILEDLASTTURN)))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 1261);
                    v13 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v13);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }

            // Assault Vest
            if (a2->HeldItem == 289 && !PML_MoveIsDamaging(move))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 1258);
                    v12 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v12);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_TAUNT) && !PML_MoveIsDamaging(move))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 571);
                    v12 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v12);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_TORMENT) && move == BattleMon_GetPreviousMove(a2))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 580);
                    v13 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v13);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_DISABLEMOVE) && move == BattleMon_GetConditionAffectedMove(a2, CONDITION_DISABLEMOVE) && move != MOVE165_STRUGGLE)
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 595);
                    v14 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v14);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_HEALBLOCK) && getMoveFlag(move, FLAG_HEALING))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 890);
                    v15 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v15);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
            if (BattleField_CheckFieldEffectCore(a1->battleField, EFFECT_IMPRISON) && BattleField_CheckImprisonCore(a1->battleField, a1->pokeCon, a2, move))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 589);
                    v16 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v16);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
            if (BattleField_CheckFieldEffectCore(a1->battleField, EFFECT_GRAVITY) && getMoveFlag(move, FLAG_GROUNDED_BY_GRAVITY))
            {
                if (strparam)
                {
                    Btlv_StringParam_Setup(strparam, 2, 1086);
                    v17 = BattleMon_GetID(a2);
                    Btlv_StringParam_AddArg(strparam, v17);
                    Btlv_StringParam_AddArg(strparam, move);
                }
                return 1;
            }
        }
        return 0;
    };

    int THUMB_BRANCH_AddConditionCheckFailOverwrite(ServerFlow *a1, BattleMon *a2, MoveCondition a3, int a4, char a5)
    {
        int PokeType; // r6
        int v10;      // r0
        int v11;      // r0
        int v12;      // r0

        if (BattleMon_CheckIfMoveCondition(a2, a3) && a5 != 2)
        {
            return 1;
        }
        if (a3 < CONDITION_CONFUSION && BattleMon_GetStatus(a2) && !a5)
        {
            return 3;
        }
        if (ServerEvent_GetWeather(a1) == 1 && a3 == CONDITION_FREEZE)
        {
            return 3;
        }
        if (a3 == CONDITION_POISON)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_STEEL) || PokeTypePair_HasType(PokeType, TYPE_POISON))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_PARALYSIS)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_ELECTRIC))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_BURN)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_FIRE))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_FREEZE)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_ICE))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_CONFUSION)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_PSYCHIC))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_CURSE)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_NORMAL))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_LEECHSEED)
        {
            PokeType = BattleMon_GetPokeType(a2);
            if (PokeTypePair_HasType(PokeType, TYPE_GRASS))
            {
                return 2;
            }
        }
        if (a3 == CONDITION_DROWSY && BattleMon_GetStatus(a2))
        {
            return 3;
        }
        if (a3 == CONDITION_GASTROACID && BattleMon_GetValue(a2, VALUE_ABILITY) == 121) // multitype
        {
            return 3;
        }
        return 0;
    }

    void null()
    {
    }

#pragma endregion

#pragma region TwoTurnMoves

    int HandlerSwitchOutInterruptStart(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {
        int result;         // r0
        unsigned int Value; // r6
        int v8[6];          // [sp+0h] [bp-18h] BYREF
        BattleMon *attacker;
        HandlerParam_Message *message;
        int messageId;
        v8[1] = a4;

        result = Handler_GetThisTurnAction(a2, a3, (unsigned int *)v8);

        if (result)
        {

            Value = BattleEventVar_GetValue(VAR_TARGET_MON_ID);
            result = MainModule_IsAllyMonID(Value, a3);
            if (!result)
            {

                Handler_PokeIDToPokePos(a2, Value);
                Handler_PokeIDToPokePos(a2, a3);
                result = Handler_IsTargetInRange(a2, a3, Value, 0);
                if (!result)
                {

                    attacker = Handler_GetBattleMon(a2, a3);
                    if (BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_SHADOWFORCE) || BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_DIG) || BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_DIVE) || BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_FLY) || attacker->HeldItem == IT0271_POWER_HERB)
                    {

                        if (BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_SHADOWFORCE))
                        {
                            messageId = 1282;
                        }
                        if (BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_DIG))
                        {
                            messageId = 1279;
                        }
                        if (BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_DIVE))
                        {
                            messageId = 1288;
                        }
                        if (BattleMon_GetConditionFlag(attacker, CONDITIONFLAG_FLY))
                        {
                            messageId = 1285;
                        }
                        message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                        BattleHandler_StrSetup(&message->str, 2u, messageId);
                        BattleHandler_AddArg(&message->str, Value);
                        BattleHandler_PopWork(a2, message);
                        return Handler_AddSwitchOutInterrupt((int)a2, a3);
                    }
                }
            }
        }
        return result;
    };

    MOVE_TRIGGERTABLE ShadowForceHandlers[] = {
        {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerSwitchOutInterruptStart},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerShadowForce},
        {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)null},
        {EVENT_CHECK_PROTECT_BREAK, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
        {EVENT_DAMAGE_PROCESSING_END_HIT_1, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd}};

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddShadowForce(_DWORD *a1)
    {
        *a1 = 6;
        return ShadowForceHandlers;
    }

    MOVE_TRIGGERTABLE DigHandlers[] = {
        {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerSwitchOutInterruptStart},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerDig},
        {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)null},
        {EVENT_CHECK_PROTECT_BREAK, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
        {EVENT_DAMAGE_PROCESSING_END_HIT_1, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd}};

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddDig(_DWORD *a1)
    {
        *a1 = 6;
        return DigHandlers;
    }

    MOVE_TRIGGERTABLE DiveHandlers[] = {
        {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerSwitchOutInterruptStart},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerDive},
        {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)null},
        {EVENT_CHECK_PROTECT_BREAK, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
        {EVENT_DAMAGE_PROCESSING_END_HIT_1, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd}};

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddDive(_DWORD *a1)
    {
        *a1 = 6;
        return DiveHandlers;
    }

    MOVE_TRIGGERTABLE FlyHandlers[] = {
        {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerSwitchOutInterruptStart},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerFly},
        {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)null},
        {EVENT_CHECK_PROTECT_BREAK, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
        {EVENT_DAMAGE_PROCESSING_END_HIT_1, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd}};

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddFly(_DWORD *a1)
    {
        *a1 = 6;
        return FlyHandlers;
    }

    MOVE_TRIGGERTABLE BounceHandlers[] = {
        {EVENT_SWITCH_OUT_INTERRUPT, (MOVE_HANDLER_FUNC)HandlerSwitchOutInterruptStart},
        {EVENT_CHARGE_UP_START, (MOVE_HANDLER_FUNC)HandlerBounce},
        {EVENT_CHARGE_UP_END, (MOVE_HANDLER_FUNC)null},
        {EVENT_CHECK_PROTECT_BREAK, (MOVE_HANDLER_FUNC)HandlerFeintBreakProtect},
        {EVENT_DAMAGE_PROCESSING_START, (MOVE_HANDLER_FUNC)HandlerFeintResetProtectCounter},
        {EVENT_DAMAGE_PROCESSING_END_HIT_1, (MOVE_HANDLER_FUNC)HandlerShadowForceEnd}};

    MOVE_TRIGGERTABLE *THUMB_BRANCH_EventAddBounce(_DWORD *a1)
    {
        *a1 = 6;
        return BounceHandlers;
    }

#pragma endregion

#pragma region MiscMoves
    void THUMB_BRANCH_HandlerWaterPledgeCheck(BattleEventItem *a1, ServerFlow *serverFlow, int pokeId, _DWORD *work)
    {
        unsigned int attackingMonId;   // r0
        BattleMon *BattleMon;          // r0
        int SubID;                     // r0
        unsigned __int8 ComboMoveType; // r5
        Types moveType;                // r1
        int move1;
        int move2;
        int move1TypeE;
        int move2TypeE;
        unsigned __int16 comboMoveId;
        unsigned __int8 comboPokeId;

        attackingMonId = BattleEventVar_GetValue(VAR_ATTACKING_MON);
        if (pokeId == attackingMonId)
        {
            BattleMon = Handler_GetBattleMon(serverFlow, pokeId);
            attackingMonId = BattleMon_GetComboMoveData(BattleMon, &comboPokeId, &comboMoveId);
            if (attackingMonId)
            {
                SubID = BattleEventItem_GetSubID(a1);
                ComboMoveType = GetComboMoveType(SubID, comboMoveId);

                moveType = (Types)BattleEventVar_GetValue(VAR_MOVE_TYPE);
                if (ComboMoveType)
                {
                    work[0] = 1;
                    work[1] = ComboMoveType;
                    work[2] = comboPokeId;

                    move1 = PML_MoveGetType(SubID);
                    move2 = PML_MoveGetType(comboMoveId);
                    move1TypeE = GetTypeEffectivenessVsMon(move1, BattleMon_GetPokeType(Handler_GetBattleMon(serverFlow, BattleEventVar_GetValue(VAR_DEFENDING_MON))));
                    move2TypeE = GetTypeEffectivenessVsMon(move2, BattleMon_GetPokeType(Handler_GetBattleMon(serverFlow, BattleEventVar_GetValue(VAR_DEFENDING_MON))));

                    if (move2TypeE > move1TypeE)
                    {
                        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, move2);
                    }
                    else
                    {
                        BattleEventVar_RewriteValue(VAR_MOVE_TYPE, move1);
                    }
                }
            }
        }
    }

#pragma endregion

#pragma region WIPBindHandlers

    // void THUMB_BRANCH_HandlerSonicBoom(ServerFlow *a1, BattleMon *a2, unsigned int a3)
    // {
    //     int Param_1;             // r0
    //     int v5;                  // r5
    //     int v6;                  // r6
    //     int v7;                  // r6
    //     HandlerParam_Damage *v8; // r4
    //     BattleMon *v9;           // r0
    //     unsigned int v10;        // r1
    //     ConditionData v13;       // [sp+8h] [bp-20h]

    //     if (j_j_BattleMon_IsFainted_7(a2))
    //     {
    //         return;
    //     }
    //     v13 = j_j_GetConditionContinuationParam_1(a2, CONDITION_BIND);
    //     Param_1 = j_j_Condition_GetParam_1(v13);
    //     v6 = -1;

    //     if (IsEqual(Param_1, MOVE463_MAGMA_STORM))
    //     {
    //         v6 = 633;
    //     }
    //     else if (IsEqual(Param_1, MOVE250_WHIRLPOOL))
    //     {
    //         v6 = 635;
    //     }
    //     else if (IsEqual(Param_1, MOVE083_FIRE_SPIN))
    //     {
    //         v6 = 632;
    //     }
    //     else if (IsEqual(Param_1, MOVE020_BIND))
    //     {
    //         v6 = 630;
    //     }
    //     else if (IsEqual(Param_1, MOVE128_CLAMP))
    //     {
    //         v6 = 634;
    //     }
    //     else if (IsEqual(Param_1, MOVE328_SAND_TOMB))
    //     {
    //         v6 = 636;
    //     }
    //     else if (IsEqual(Param_1, MOVE035_WRAP))
    //     {
    //         v6 = 631;
    //     }
    //     else if (IsEqual(Param_1, MOVE132_INFESTATION))
    //     {
    //         v6 = 679;
    //     }
    //     else if (IsEqual(Param_1, MOVE012_GUILLOTINE))
    //     {
    //         v6 = 680;
    //     }
    //     else if (IsEqual(Param_1, MOVE032_HORN_DRILL))
    //     {
    //         v6 = 681;
    //     }
    //     else if (IsEqual(Param_1, MOVE090_FISSURE))
    //     {
    //         v6 = 682;
    //     }
    //     else if (IsEqual(Param_1, MOVE170_SNAP_TRAP))
    //     {
    //         v6 = 683;
    //     }
    //     else if (IsEqual(Param_1, MOVE286_IMPRISON))
    //     {
    //         v6 = 684;
    //     }
    //     else if (IsEqual(Param_1, MOVE171_NIGHTMARE))
    //     {
    //         v6 = 685;
    //     }
    //     else if (IsEqual(Param_1, MOVE264_ALLURING_VOICE))
    //     {
    //         v6 = 686;
    //     }
    //     else
    //     {
    //     }
    //     // if (Param_1 > MOVE128_CLAMP)
    //     // {
    //     //     if (Param_1 > MOVE328_SAND_TOMB)
    //     //     {
    //     //         if (Param_1 == MOVE463_MAGMA_STORM)
    //     //         {
    //     //             v6 = 633;
    //     //         }
    //     //         goto LABEL_24;
    //     //     }
    //     //     if (Param_1 < MOVE328_SAND_TOMB)
    //     //     {
    //     //         if (Param_1 == MOVE250_WHIRLPOOL)
    //     //         {
    //     //             v6 = 635;
    //     //         }
    //     //         goto LABEL_24;
    //     //     }
    //     //     v7 = 159;
    //     //     goto LABEL_23;
    //     // }
    //     // if (Param_1 >= MOVE128_CLAMP)
    //     // {
    //     //     v6 = 634;
    //     //     goto LABEL_24;
    //     // }
    //     // if (Param_1 <= MOVE035_WRAP)
    //     // {
    //     //     if (Param_1 < MOVE035_WRAP)
    //     //     {
    //     //         if (Param_1 == MOVE020_BIND)
    //     //         {
    //     //             v6 = 630;
    //     //         }
    //     //     }
    //     //     else
    //     //     {
    //     //         v6 = 631;
    //     //     }
    //     //     goto LABEL_24;
    //     // }
    //     // if (Param_1 == MOVE083_FIRE_SPIN)
    //     // {
    //     //     v7 = 158;
    //     // LABEL_23:
    //     //     v6 = 4 * v7;
    //     // }
    //     // LABEL_24:
    //     v8 = (HandlerParam_Damage *)j_j_BattleHandler_PushWork_21(a1, EFFECT_DAMAGE, a3);
    //     v8->pokeID = a3;
    //     v8->damage = j_j_DivideMaxHPZeroCheck_5(a2, (j_j_Condition_GetFlag(v13)) ? 8 : 10);
    //     if (v6 != -1)
    //     {
    //         v8->flags |= 2u;
    //         v8->effectNo = v6;
    //         v8->posFrom = j_j_Handler_PokeIDToPokePos_3(a1, a3);
    //         v8->posTo = 6;
    //     }
    //     j_j_BattleHandler_StrSetup_14(&v8->exStr.ID, 2u, 372);
    //     j_j_BattleHandler_AddArg_16(&v8->exStr, a3);
    //     j_j_BattleHandler_AddArg_17(&v8->exStr, v5);
    //     j_j_BattleHandler_PopWork_21(a1, v8);
    // }
#pragma endregion
}