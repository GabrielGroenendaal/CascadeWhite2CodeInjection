

#include "aiSettings.h"



extern "C" {

    
    void THUMB_BRANCH_SAFESTACK_HandlerPosHealingWish(BattleEventItem *a1, ServerFlow *a2, int a3)
    /* HEALING WISH*/
    {
        u8 Value_5;           // r4
        BattleMon *PokeParam_2;         // r7
        HandlerParam_AddAnimation *v7;  // r6
        HandlerParam_RecoverHP *v8;     // r6
        HandlerParam_CureCondition *v9; // r0
        __int16 BattleMonStat_1; // [sp+8h] [bp-18h]

        Value_5 = BattleEventVar_GetValue(VAR_MON_ID);
        if (a3 == Handler_PokeIDToPokePos(a2, Value_5))
        {
            PokeParam_2 = Handler_GetBattleMon(a2, Value_5);
            v7 = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a2, EFFECT_ADD_ANIMATION, Value_5);
            v7->animNo = 639;
            v7->pos_from = a3;
            v7->pos_to = 6;
            BattleHandler_StrSetup(&v7->exStr, 2u, 697);
            BattleHandler_AddArg(&v7->exStr, Value_5);
            BattleHandler_PopWork(a2, v7);
            if (!BattleMon_IsFullHP(PokeParam_2))
            {
                v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, Value_5);
                v8->pokeID = Value_5;
                BattleMonStat_1 = BattleMon_GetValue(PokeParam_2, VALUE_MAX_HP);
                v8->recoverHP = BattleMonStat_1 - BattleMon_GetValue(PokeParam_2, VALUE_CURRENT_HP);
                BattleHandler_PopWork(a2, v8);
            }
            if (BattleMon_GetStatus(PokeParam_2))
            {
                v9 = (HandlerParam_CureCondition *)BattleHandler_PushWork(a2, EFFECT_CURE_STATUS, Value_5);
                v9->poke_cnt = 1;
                v9->pokeID[0] = Value_5;
                v9->sickCode = CONDITION_24;
                BattleHandler_PopWork(a2, v9);
            }
            ChangeStats(a2, Value_5, Value_5, STATSTAGE_ATTACK, 1, 0);
            ChangeStats(a2, Value_5, Value_5, STATSTAGE_DEFENSE, 1, 1);
            ChangeStats(a2, Value_5, Value_5, STATSTAGE_SPECIAL_ATTACK, 1, 1);
            ChangeStats(a2, Value_5, Value_5, STATSTAGE_SPECIAL_DEFENSE, 1, 1);
            ChangeStats(a2, Value_5, Value_5, STATSTAGE_SPEED, 1, 1);
            BattleEventItem_Remove(a1);
        }
    }

    void THUMB_BRANCH_SAFESTACK_Condition_HandlerBind(ServerFlow *a1, BattleMon *a2, unsigned int a3)
    /* ANIMATIONS FOR BIND END-OF-TURN */
    {
        int Param_1; // r0
        int v5; // r5
        int v6; // r6
        int v7; // r6
        HandlerParam_Damage *v8; // r4
        BattleMon *v9; // r0
        unsigned int v10; // r1
        ConditionData v13; // [sp+8h] [bp-20h]

        if ( j_j_BattleMon_IsFainted_7(a2) )
        {
            return;
        }
        v13.raw = j_j_GetConditionContinuationParam_1(a2, CONDITION_BIND).raw;
        Param_1 = j_j_Condition_GetParam_1(v13);
        v5 = Param_1;
        v7 = -1;
        if (Param_1 == MOVE463_MAGMA_STORM)
        {
            v7 = 633;
        }
        else if (Param_1 == MOVE250_WHIRLPOOL)
        {
            v7 = 635;
        }
        else if (Param_1 == MOVE128_CLAMP)
        {
            v7 = 634;
        }
        else if (Param_1 == MOVE035_WRAP)
        {
            v7 = 631;
        }
        else if (Param_1 == MOVE020_BIND)
        {
            v7 = 630;
        }
        else if (Param_1 == MOVE083_FIRE_SPIN)
        {
            v7 = 632;
        }
        else if (Param_1 == MOVE328_SAND_TOMB)
        {
            v7 = 636;
        }
        else if (Param_1 == MOVE171_NIGHTMARE){
            v7 = 685;
        }
        else if (Param_1 == MOVE286_IMPRISON){
            v7 = 684;
        }
        else if (Param_1 == MOVE090_FISSURE){
            v7 = 682;
        }
        else if (Param_1 == MOVE012_GUILLOTINE){
            v7 = 680;
        }
        else if (Param_1 == MOVE032_HORN_DRILL){
            v7 = 681;
        }
        else if (Param_1 == MOVE132_INFESTATION){
            v7 = 679;
        }
        else if (Param_1 == MOVE170_SNAP_TRAP){
            v7 = 683;
        }
        else if (Param_1 == MOVE377_ALLURING_VOICE){
            v7 = 686;
        }
        else if (Param_1 == MOVE066_SUBMISSION){
            v7 = 630;
        }
        else {
            v7 = 630;
        }
        v8 = (HandlerParam_Damage *)j_j_BattleHandler_PushWork_21(a1, EFFECT_DAMAGE, a3);
        v8->pokeID = a3;
        if ( j_j_Condition_GetFlag(v13) )
        {
            v9 = a2;
            v10 = 6;
        }
        else
        {
            v9 = a2;
            v10 = 8;
        }
        v8->damage = j_j_DivideMaxHPZeroCheck_5(v9, v10);
        if ( v7 != -1 )
        {
            v8->flags |= 2u;
            v8->effectNo = v7;
            v8->posFrom = j_j_Handler_PokeIDToPokePos_3(a1, a3);
            v8->posTo = 6;
        }
        j_j_BattleHandler_StrSetup_14(&v8->exStr.ID, 2u, 372);
        j_j_BattleHandler_AddArg_16(&v8->exStr, a3);
        j_j_BattleHandler_AddArg_17(&v8->exStr, v5);
        j_j_BattleHandler_PopWork_21(a1, v8);
    }
}