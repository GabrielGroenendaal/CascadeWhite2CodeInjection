

#include "codeinjection_battlefield.h"
#include "kPrint.h"
#include "settings.h"
#include "swantypes.h"

extern "C" u32 SearchArray(const u32 *const arr, const u32 arrSize, const u32 value)
{
    for (u32 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)
        {
            return 1;
        }
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

#pragma region BattleFieldSetup

// struct BattleField
// {
//     int Weather;
//     int WeatherTurns;
//     BattleEventItem *battleEventItems[8];
//     ConditionData conditionData[8];
//     u32 TurnCount[8];
//     u32 DependPokeID[8][6];
//     u32 DependPokeCount[8];
//     u32 EffectEnableFlags[8];
// };

struct BattleFieldExt
{
    // WeatherID weather;
    // BattleEventItem *battleEventItems[FIELD_EFFECT_AMOUNT];
    // ConditionData conditionData[FIELD_EFFECT_AMOUNT];
    // u32 turnCount[FIELD_EFFECT_AMOUNT];
    // u32 dependPokeID[FIELD_EFFECT_AMOUNT][6];
    // u32 dependPokeCount[FIELD_EFFECT_AMOUNT];
    // u32 effectEnableFlags[FIELD_EFFECT_AMOUNT];

    // Stores the damage a Substitute takes each action
    // - Reset in [ServerControl_DamageRoot] & [CommonEmergencyExitCheck]
    // - Set in [BattleMon_AddSubstituteDamage]
    // - Used in [CommonEmergencyExitCheck]
    u32 actionSubstituteDamage[31];
    // u8 firstTurnMons[6] = {31};
    // Tracks which Emergency Exit Pok�mon should switch after the move is over
    // - Used in [CommonEmergencyExitCheck] & [HandlerEmergencyExitSwitch]
    u32 emergencyExitFlag;

    u32 BerserkFlag;

    u8 neutralizingGasMons;
    u32 Test;
};
BattleFieldExt *g_BattleVars;

u8 endTurnSwitchFlag = 0;

extern "C" b32 CheckEndTurnSwitchFlag()
{
    return endTurnSwitchFlag;
}
extern "C" void SetEndTurnSwitchFlag()
{
    endTurnSwitchFlag = 1;
}
extern "C" void ResetEndTurnSwitchFlag()
{
    endTurnSwitchFlag = 0;
}

extern "C" u32 BattleField_GetSubstituteDamage(u32 battleSlot)
{
    return g_BattleVars->actionSubstituteDamage[battleSlot];
}
extern "C" void BattleField_SetSubstituteDamage(u32 battleSlot, u32 value)
{
    g_BattleVars->actionSubstituteDamage[battleSlot] = value;
}

extern "C" b32 BattleField_CheckBerserkFlag(u32 battleSlot)
{
    return (g_BattleVars->emergencyExitFlag >> battleSlot) & 1;
}
extern "C" void BattleField_SetBerserkFlag(u32 battleSlot)
{
    g_BattleVars->emergencyExitFlag |= (1 << battleSlot);
}
extern "C" void BattleField_ResetBerserkFlag(u32 battleSlot)
{
    g_BattleVars->emergencyExitFlag &= ~(1 << battleSlot);
}

extern "C" b32 BattleField_CheckEmergencyExitFlag(u32 battleSlot)
{
    return (g_BattleVars->emergencyExitFlag >> battleSlot) & 1;
}
extern "C" void BattleField_SetEmergencyExitFlag(u32 battleSlot)
{
    g_BattleVars->emergencyExitFlag |= (1 << battleSlot);
}
extern "C" void BattleField_ResetEmergencyExitFlag(u32 battleSlot)
{
    g_BattleVars->emergencyExitFlag &= ~(1 << battleSlot);
}

extern "C" u32 BattleField_GetNeutralizingGasMons()
{
    return g_BattleVars->neutralizingGasMons;
}
extern "C" void BattleField_AddNeutralizingGasMon()
{
    ++g_BattleVars->neutralizingGasMons;
}
extern "C" void BattleField_RemoveNeutralizingGasMon()
{
    --g_BattleVars->neutralizingGasMons;
}

extern "C" void BattleField_InitCore(BattleField *a1, int a2);
extern "C" void *GFL_HeapAllocate(HeapID heapId, u32 size, b32 calloc, const char *sourceFile, u16 lineNo);

extern "C" BattleField *THUMB_BRANCH_BattleField_Init(HeapID a1)
{
    BattleField *v1;

    if (!g_BattleVars)
    {
        g_BattleVars = (BattleFieldExt *)GFL_HeapAllocate(a1, sizeof(BattleFieldExt), 1, "btl_field.c", 0x10Cu);
        g_BattleVars->neutralizingGasMons = 0;
        g_BattleVars->emergencyExitFlag = 0;
        g_BattleVars->BerserkFlag = 0;
        g_BattleVars->Test = 5;
        sys_memset(g_BattleVars->actionSubstituteDamage, 0, 31 * sizeof(u32));
    }
    v1 = (BattleField *)GFL_HeapAllocate(a1, 0x168u, 1, "btl_field.c", 0x10Cu);
    BattleField_InitCore(v1, 0);
    return v1;
}

extern "C" void GFL_HeapFree(void *heap);

extern "C" void THUMB_BRANCH_BattleField_Free(void *battleField)
{
    if (g_BattleVars)
    {
        GFL_HeapFree(g_BattleVars);
        g_BattleVars = nullptr;
    }
    GFL_HeapFree(battleField);
}

#pragma endregion

#pragma region TryImplementingTheseAndSeeWHatHappens

extern "C" void ServerDisplay_SimpleHP(ServerFlow *a1, BattleMon *a2, int a3, int a4);
extern "C" void TurnFlag_Set(BattleMon *a1, TurnFlag a2);
extern "C" void BattleHandler_StrClear(HandlerParam_StrParams *a1);
extern "C" int ServerControl_CheckFainted(ServerFlow *a1, BattleMon *a2);
extern "C" void BattleMon_CureMoveCondition(BattleMon *a1, MoveCondition a2);
extern "C" int CureStatusCondition(BattleMon *a1);
extern "C" int AddConditionCheckFailOverwrite(ServerFlow *a1, BattleMon *a2, MoveCondition a3, ConditionData a4, char a5);
extern "C" void AddConditionCheckFailStandard(ServerFlow *a1, BattleMon *a2, int a3, unsigned int a4);
extern "C" int ServerEvent_MoveConditionCheckFail(ServerFlow *a1, BattleMon *a2, BattleMon *a3, int a4);
extern "C" void ServerEvent_AddConditionFailed(ServerFlow *a1, BattleMon *a2, BattleMon *a3, int a4);
extern "C" void PokeSet_SeekStart(PokeSet *a1);
extern "C" BattleMon *PokeSet_SeekNext(PokeSet *a1);

// Called when the ability of a Pokemon stops being nullifyed [ServerControl_CureCondition]
extern "C" void ServerEvent_AbilityNullifyCured(ServerFlow *serverFlow, BattleMon *battleMon)
{
    BattleEventVar_Push();
    u32 currentSlot = BattleMon_GetID(battleMon);
    BattleEventVar_SetConstValue(VAR_MON_ID, currentSlot);
    // Abilities with an effect when given also activate when they stop being nullifyed
    BattleEvent_CallHandlers(serverFlow, EVENT_AFTER_ABILITY_CHANGE);
    BattleEventVar_Pop();
}

// Called after receiving simple damage (status, recoil, items...) [ServerControl_SimpleDamageCore]
extern "C" void ServerEvent_SimpleDamageReaction(ServerFlow *serverFlow, BattleMon *battleMon, u32 damage)
{
    u32 HEID = HEManager_PushState(&serverFlow->heManager);

    BattleEventVar_Push();
    SET_UP_NEW_EVENT;
    u32 currentSlot = BattleMon_GetID(battleMon);
    BattleEventVar_SetConstValue(NEW_VAR_MON_ID, currentSlot);
    BattleEventVar_SetConstValue(VAR_DAMAGE, damage);
    BattleEvent_CallHandlers(serverFlow, EVENT_CHECK_ITEM_REACTION);
    BattleEventVar_Pop();

    HEManager_PopState(&serverFlow->heManager, HEID);
}

extern "C" b32 THUMB_BRANCH_ServerControl_SimpleDamageCore(ServerFlow *serverFlow, BattleMon *battleMon, int damage, HandlerParam_StrParams *str)
{
    int damageToDeal = -damage;
    if (!damageToDeal)
    {
        return 0;
    }

    ServerDisplay_SimpleHP(serverFlow, battleMon, damageToDeal, 1);
    TurnFlag_Set(battleMon, TURNFLAG_DAMAGED);
    if (str)
    {
        BattleHandler_SetString(serverFlow, str);
        BattleHandler_StrClear(str);
    }

    ServerControl_CheckItemReaction(serverFlow, battleMon, 1);
    // Call to new event
    ServerEvent_SimpleDamageReaction(serverFlow, battleMon, damage);
    if (ServerControl_CheckFainted(serverFlow, battleMon))
    {
        ServerControl_CheckMatchup(serverFlow);
    }

    return 1;
}

extern "C" int checkPosPoke(PosPoke a1, int pokemonslot)
{
    unsigned int i;
    PosPokeState v3;
    for (i = 0; i < 6; i++)
    {
        v3 = a1.state[i];
        if (v3.fEnable && v3.existPokeID == pokemonslot)
        {
            return i;
        }
    }
    return 6;
}

// Neutralizing Gas - Added event when an ability stops being nullyfied (EVENT_AFTER_ABILITY_CHANGE)
extern "C" void THUMB_BRANCH_ServerControl_CureCondition(ServerFlow *serverFlow, BattleMon *battleMon, MoveCondition condition, ConditionData *prevCondition)
{
    if (condition)
    {
        u32 pokemonSlot = BattleMon_GetID(battleMon);
        if (prevCondition)
        {
            *prevCondition = BattleMon_GetMoveCondition(battleMon, condition);
        }
        if (condition >= CONDITION_CONFUSION)
        {
            BattleMon_CureMoveCondition(battleMon, condition);
            if (condition == CONDITION_GASTROACID)
            {
                // Call server event when ability nullify is over
                ServerEvent_AbilityNullifyCured(serverFlow, battleMon);
            }
            ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_CureMoveCondition, pokemonSlot, condition);
        }
        else
        {
            CureStatusCondition(battleMon);
            ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_CureStatusCondition, pokemonSlot);
            if (checkPosPoke(serverFlow->posPoke, pokemonSlot) != 6)
            {
                ServerDisplay_AddCommon(serverFlow->serverCommandQueue, SCID_StatusIcon, pokemonSlot, 0);
            }
        }
    }
}

extern "C" u32 THUMB_BRANCH_SAFESTACK_ServerControl_AddConditionCheckFail(ServerFlow *serverFlow, BattleMon *defendingMon, BattleMon *attackingMon, MoveCondition condition, ConditionData condData, u8 overrideMode, u32 almost)
{
    u32 failStatus = AddConditionCheckFailOverwrite(serverFlow, defendingMon, condition, condData, overrideMode);

    if (condition == CONDITION_GASTROACID &&
        (defendingMon->Conditions[condition]) == 0)
    {

        switch (failStatus)
        {
        case 0:
            // Gastro Acid fails agains certain abilities
            if (BattleMon_GetValue(defendingMon, VALUE_ABILITY) == ABIL046_NEUTRALIZING_GAS)
            {
                failStatus = 3;
            }
            break;
        case 1:
            // Gastro Acid should not fail if the condition is already detected
            // only because the Pok�mon is affected by Neutralizing Gas
            failStatus = 0;
            break;
        }
    }

    if (failStatus)
    {
        if (almost)
        {
            AddConditionCheckFailStandard(serverFlow, defendingMon, failStatus, condition);
        }
        return 1;
    }
    else
    {
        u32 HEID = HEManager_PushState(&serverFlow->heManager);
        u32 failFlag = ServerEvent_MoveConditionCheckFail(serverFlow, attackingMon, defendingMon, condition);
        // Added new state to force the fail
        if ((failFlag && almost) || failFlag == FORCE_FAIL_MESSAGE)
        {
            ServerEvent_AddConditionFailed(serverFlow, defendingMon, attackingMon, condition);
            // This disables the default fail message
            serverFlow->field_78A |= 0x10u;
        }
        HEManager_PopState(&serverFlow->heManager, HEID);
        return failFlag;
    }
}

extern "C" void P_SeekStart(PokeSet p)
{
    p.getIdx = 0;
}

extern "C" BattleMon* P_SeekNext(PokeSet p)
{
    unsigned int getIdx; // r3

    getIdx = p.getIdx;
    if (getIdx >= p.count)
    {
        return 0;
    }
    ++p.getIdx;
    return p.battleMon[getIdx];
}
extern "C" void ServerEvent_SwitchInPriority(ServerFlow *serverFlow)
{
    PokeSet* set = (PokeSet *)((int)serverFlow + 0x1A68);
    PokeSet_SeekStart(set);
    for (BattleMon *currentMon = PokeSet_SeekNext(set); currentMon; currentMon = PokeSet_SeekNext(set))
    {
        u32 HEID = HEManager_PushState(&serverFlow->heManager);
        u32 currentSlot = BattleMon_GetID(currentMon);
        BattleEventVar_Push();
        SET_UP_NEW_EVENT;
        BattleEventVar_SetConstValue(NEW_VAR_MON_ID, currentSlot);
        BattleEvent_CallHandlers(serverFlow, EVENT_ENDURE);
        BattleEventVar_Pop();
        HEManager_PopState(&serverFlow->heManager, HEID);
    }
}

// Neutralizing Gas - Add server event that activates before every other switch-in event
extern "C" void THUMB_BRANCH_ServerEvent_AfterSwitchInPrevious(ServerFlow *serverFlow)
{
    // Add an event that triggers before every other switch in event
    ServerEvent_SwitchInPriority(serverFlow);

    BattleEventVar_Push();
    BattleEvent_CallHandlers(serverFlow, EVENT_SWITCH_IN_PREVIOUS);
    BattleEventVar_Pop();
}

// Emergency Exit - Store damage taken by the substitute to acuratelly calculate HP when hit
extern "C" b32 THUMB_BRANCH_BattleMon_AddSubstituteDamage(BattleMon *battleMon, u32 *damage)
{
    b32 result;

    u32 substituteHP = battleMon->SubstituteHP;
    if (substituteHP > *damage)
    {
        battleMon->SubstituteHP = substituteHP - *damage;
        result = 0;
    }
    else
    {
        *damage = substituteHP;
        battleMon->SubstituteHP = 0;
        result = 1;
    }

    u32 substituteDamage = BattleField_GetSubstituteDamage(battleMon->ID) + *damage;
    BattleField_SetSubstituteDamage(battleMon->ID, substituteDamage);
    return result;
}

#pragma region Berserk

extern "C" void HandlerBerserkSwitchIn(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot = BattleEventVar_GetValue(VAR_MON_ID))
    {
        BattleField_ResetBerserkFlag(pokemonSlot);
    }
}
extern "C" u32 div32(u32 numerator, u32 denominator);

extern "C" void HandlerBerserk(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    u32 targetCount = BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u8 i = 0; i < targetCount; ++i)
    {
        u32 targetSlot = BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + i));
        if (pokemonSlot == targetSlot)
        {

            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            u32 maxHP = BattleMon_GetValue(currentMon, VALUE_MAX_HP);

            u32 currentHP = BattleMon_GetValue(currentMon, VALUE_CURRENT_HP);

            u32 currentHPPercent = div32(currentHP * 100, maxHP);

            u32 beforeDmgHP = currentHP + BattleEventVar_GetValue(VAR_DAMAGE) - BattleField_GetSubstituteDamage(pokemonSlot);
            u32 beforeDmgHPPercent = div32(beforeDmgHP * 100, maxHP); //(beforeDmgHP * 100) / maxHP;
            if (beforeDmgHPPercent >= 50)
            {
                if (currentHPPercent < 50 && !BattleField_CheckBerserkFlag(pokemonSlot))
                {
                    BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);

                    HandlerParam_ChangeStatStage *stageChange;
                    stageChange = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, pokemonSlot);
                    stageChange->poke_cnt = 1;
                    stageChange->pokeID[0] = pokemonSlot;
                    stageChange->fMoveAnimation = 1;
                    stageChange->rankType = STATSTAGE_SPECIAL_ATTACK;
                    stageChange->rankVolume = 1;
                    BattleHandler_PopWork(serverFlow, stageChange);

                    HandlerParam_ChangeStatStage *stageChange2;
                    stageChange2 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, pokemonSlot);
                    stageChange2->poke_cnt = 1;
                    stageChange2->pokeID[0] = pokemonSlot;
                    stageChange2->fMoveAnimation = 1;
                    stageChange2->rankType = STATSTAGE_ATTACK;
                    stageChange2->rankVolume = 1;
                    BattleHandler_PopWork(serverFlow, stageChange);

                    BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);

                    BattleField_SetBerserkFlag(pokemonSlot);
                }
            }

            BattleField_SetSubstituteDamage(pokemonSlot, 0);
        }
    }
}

BattleEventHandlerTableEntry BerserkHandlers[]{
    {EVENT_DAMAGE_PROCESSING_END_HIT_2, (BattleEventHandler)HandlerBerserk},
    {EVENT_SWITCH_IN, (BattleEventHandler)HandlerBerserkSwitchIn},
};

extern "C" BattleEventHandlerTableEntry *THUMB_BRANCH_EventAddPoisonPoint(u32 *handlerAmount)
{
    *handlerAmount = ARRAY_COUNT(BerserkHandlers);
    return BerserkHandlers;
}

#pragma endregion

#pragma region EmergencyExit

extern "C" void CommonEmergencyExitCheck(ServerFlow *serverFlow, u32 currentSlot)
{
    BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
    u32 maxHP = BattleMon_GetValue(currentMon, VALUE_MAX_HP);

    u32 currentHP = BattleMon_GetValue(currentMon, VALUE_CURRENT_HP);
    u32 currentHPPercent = (currentHP * 100) / maxHP;

    u32 beforeDmgHP = currentHP + BattleEventVar_GetValue(VAR_DAMAGE) - BattleField_GetSubstituteDamage(currentSlot);
    u32 beforeDmgHPPercent = (beforeDmgHP * 100) / maxHP;
#if EMERGENCY_EXIT_DEBUG
    DPRINTF("MAX HP: %d \n", maxHP);
    DPRINTF("CURRENT HP: %d \n", currentHP);
    DPRINTF("DAMAGE: %d \n", BattleEventVar_GetValue(VAR_DAMAGE));
    DPRINTF("SUBSTITUTE DAMAGE: %d \n", BattleField_GetSubstituteDamage(currentSlot));
    DPRINTF("BEFORE HP: %d \n", beforeDmgHP);
    DPRINTF("BEFORE HP PERCENT: %d \n", beforeDmgHPPercent);
    DPRINTF("CURRENT HP PERCENT: %d \n", currentHPPercent);
#endif
    if (beforeDmgHPPercent >= 50 &&
        currentHPPercent < 50)
    {
        BattleField_SetEmergencyExitFlag(currentSlot);
    }

    BattleField_SetSubstituteDamage(currentSlot, 0);
}
extern "C" void HandlerEmergencyExitDamageCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    u32 targetCount = BattleEventVar_GetValue(VAR_TARGET_COUNT);
    for (u32 target = 0; target < targetCount; ++target)
    {

        u32 targetSlot = BattleEventVar_GetValue((BattleEventVar)(VAR_TARGET_MON_ID + target));
        if (pokemonSlot == targetSlot)
        {
            CommonEmergencyExitCheck(serverFlow, pokemonSlot);

            if (BattleField_CheckEmergencyExitFlag(pokemonSlot))
            {
                BattleField_ResetEmergencyExitFlag(pokemonSlot);
#if EMERGENCY_EXIT_DEBUG
                DPRINTF("EE SWITCH -> SLOT: %d\n", pokemonSlot);
#endif
                BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);

                HandlerParam_Switch *switchOut;
                switchOut = (HandlerParam_Switch *)BattleHandler_PushWork(serverFlow, EFFECT_SWITCH, pokemonSlot);
                switchOut->pokeID = pokemonSlot;
                BattleHandler_PopWork(serverFlow, switchOut);

                BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
            }
        }
    }
}
extern "C" void HandlerEmergencyExitSimpleCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (IS_NOT_NEW_EVENT)
        return;

    if (pokemonSlot == BattleEventVar_GetValue(NEW_VAR_MON_ID))
    {
#if EMERGENCY_EXIT_DEBUG
        DPRINTF("EE SIMPLE -> SLOT: %d\n", pokemonSlot);
#endif
        CommonEmergencyExitCheck(serverFlow, pokemonSlot);
    }
}
extern "C" void HandlerEmergencyExitSwitchEnd(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (BattleField_CheckEmergencyExitFlag(pokemonSlot))
    {
        BattleField_ResetEmergencyExitFlag(pokemonSlot);
#if EMERGENCY_EXIT_DEBUG
        DPRINTF("EE SWITCH END -> SLOT: %d\n", pokemonSlot);
#endif
        if (Handler_GetFightEnableBenchPokeNum(serverFlow, pokemonSlot) && Handler_CheckReservedMemberChangeAction(serverFlow))
        {

            BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);

            HandlerParam_Switch *switchOut;
            switchOut = (HandlerParam_Switch *)BattleHandler_PushWork(serverFlow, EFFECT_SWITCH, pokemonSlot);
            switchOut->pokeID = pokemonSlot;
            BattleHandler_PopWork(serverFlow, switchOut);

            BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);

            // Set the flag to switch after a turn has ended
            SetEndTurnSwitchFlag();
        }
    }
}
BattleEventHandlerTableEntry EmergencyExitHandlers[]{
    {EVENT_DAMAGE_PROCESSING_END_HIT_2, (BattleEventHandler)HandlerEmergencyExitDamageCheck},
    {EVENT_CHECK_ITEM_REACTION, (BattleEventHandler)HandlerEmergencyExitSimpleCheck},
    {EVENT_TURN_CHECK_END, (BattleEventHandler)HandlerEmergencyExitSwitchEnd},
};

extern "C" BattleEventHandlerTableEntry *THUMB_BRANCH_EventAddRunAway(u32 *handlerAmount)
{
    *handlerAmount = ARRAY_COUNT(EmergencyExitHandlers);
    return EmergencyExitHandlers;
}

#pragma endregion

#pragma region NeutralizingGas

#define BATTLE_NEUTRALIZING_GAS_START_MSGID 240
#define BATTLE_NEUTRALIZING_GAS_END_MSGID 241

AbilID abilityCantBeNeutralized[] = {
    ABIL046_NEUTRALIZING_GAS,
    ABIL121_MULTITYPE

};

extern "C" b32 AbilityCantBeNeutralized(AbilID ability)
{
    return SEARCH_ARRAY((const u32 *)abilityCantBeNeutralized, ability);
}

extern "C" void ServerEvent_AbilityNullified(ServerFlow *a1, BattleMon *a2);

extern "C" bool THUMB_BRANCH_SAFESTACK_BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
{
    // if (a1->HeldItem == 289 && a2 == CONDITION_TAUNT)
    // {
    //     return true;
    // }
    if (a2 == CONDITION_BLOCK && ((a1->Conditions[CONDITION_CURSE] & 7) != 0))
    {
        return true;
    }

    if (a2 == CONDITION_GASTROACID &&
        BattleField_GetNeutralizingGasMons() &&
        !AbilityCantBeNeutralized((AbilID)BattleMon_GetValue(a1, VALUE_ABILITY)))
    {
        return 1;
    }

    return (a1->Conditions[a2] & 7) != 0;
}

extern "C" void NeutralizingGasEnd(ServerFlow *serverFlow, u32 pokemonSlot)
{
    k::Printf("\nWe are in the end neutralizing function");
    BattleField_RemoveNeutralizingGasMon();
    k::Printf("\nThe number of neutralizing mons after this switch is %d\n", BattleField_GetNeutralizingGasMons());
    // Only trigger the nullify cured events if there are no more Neutralizing Gas Pok�mon
    if (BattleField_GetNeutralizingGasMons() == 0)
    {
        k::Printf("\nIn we go!");   
        HandlerParam_Message *message;
        message = (HandlerParam_Message *)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
        BattleHandler_StrSetup(&message->str, 1u, BATTLE_NEUTRALIZING_GAS_END_MSGID);
        BattleHandler_PopWork(serverFlow, message);

        for (u8 i = 0; i < 24; ++i)
        {
            BattleMon *affectedMon = PokeCon_GetBattleMon(serverFlow->pokeCon, i);
            if (affectedMon)
            {

                u32 affectedPos = Handler_PokeIDToPokePos(serverFlow, BattleMon_GetID(affectedMon));
                // If it's currently in the battlefield
                if (affectedPos != 6 &&
                    !BattleMon_IsFainted(affectedMon))
                {

                    ServerEvent_AbilityNullifyCured(serverFlow, affectedMon);
                }
            }
        }
    }
}
extern "C" void HandlerNeutralizingGasStart(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    k::Printf("\n\nNeutralizingGasStart");
    
    if (IS_NOT_NEW_EVENT)
        return;

    if (pokemonSlot == BattleEventVar_GetValue(NEW_VAR_MON_ID))
    {
        BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);

        HandlerParam_Message *message;
        message = (HandlerParam_Message *)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, pokemonSlot);
        BattleHandler_StrSetup(&message->str, 1u, BATTLE_NEUTRALIZING_GAS_START_MSGID);
        BattleHandler_PopWork(serverFlow, message);

        BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);

        // Only trigger the nullify events if Neutralizing Gas is not already active
        if (BattleField_GetNeutralizingGasMons() == 0)
        {
            for (u8 i = 0; i < 24; ++i)
            {
                BattleMon *affectedMon = PokeCon_GetBattleMon(serverFlow->pokeCon, i);
                if (affectedMon)
                {

                    u32 affectedPos = Handler_PokeIDToPokePos(serverFlow, BattleMon_GetID(affectedMon));
                    // If it's currently in the battlefield
                    if (affectedPos != 6 &&
                        !BattleMon_IsFainted(affectedMon))
                    {

                        // Neutralizing Gas can't be neutralized by another Nutralizing Gas
                        // but since it can be neutralized by Gastro Acid it has a EVENT_ABILITY_NULLIFIED event
                        // and thus we have to make an special case here
                        if (BattleMon_GetValue(affectedMon, VALUE_ABILITY) != ABIL046_NEUTRALIZING_GAS)
                        {
                            ServerEvent_AbilityNullified(serverFlow, affectedMon);
                        }
                    }
                }
            }
        }

        BattleField_AddNeutralizingGasMon();
    }
}
extern "C" void HandlerNeutralizingGasEnd(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
    {
        NeutralizingGasEnd(serverFlow, pokemonSlot);
    }
}
extern "C" void HandlerNeutralizingGasEndFainted(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID) &&
        BattleMon_IsFainted(Handler_GetBattleMon(serverFlow, pokemonSlot)))
    {
        NeutralizingGasEnd(serverFlow, pokemonSlot);
    }
}
BattleEventHandlerTableEntry NeutralizingGasHandlers[]{
    {EVENT_ENDURE, (BattleEventHandler)HandlerNeutralizingGasStart},
    {EVENT_SWITCH_OUT_END, (BattleEventHandler)HandlerNeutralizingGasEnd},
    {EVENT_BEFORE_ABILITY_CHANGE, (BattleEventHandler)HandlerNeutralizingGasEnd},
    {EVENT_ABILITY_NULLIFIED, (BattleEventHandler)HandlerNeutralizingGasEnd},
    {EVENT_NOTIFY_FAINTED, (BattleEventHandler)HandlerNeutralizingGasEndFainted},
};
extern "C" BattleEventHandlerTableEntry *THUMB_BRANCH_EventAddPressure(u32 *handlerAmount)
{
    k::Printf("\n\nAre we loading the handlers even?\n\n");
    *handlerAmount = ARRAY_COUNT(NeutralizingGasHandlers);
    return NeutralizingGasHandlers;
}

#pragma endregion

#pragma region DynamicSpeed

#define ACTION_ORDER_GET_PRIO(actionOrder, idx) (actionOrder[idx].field_8 >> 16) & 0x3FFFFF
#define ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder, idx) ((actionOrder[idx].field_8 >> 13) & 0x7)

// extern "C" u32 CommonGetAllyPos(ServerFlow *serverFlow, u32 battlePos);
extern "C" ActionOrderWork *GetExtraActionOrder(u32 actionIdx);
extern "C" b32 IsPosInCenterTripleBattle(u32 battlePos);
extern void sys_memset16(u16 value, void *ptr, size_t size);
extern void *sys_memcpy16(const void *src, void *dst, size_t size);
extern void sys_memset32(u32 value, void *ptr, size_t size);
extern void *sys_memcpy32(const void *src, void *dest, size_t size);
extern void sys_memcpy_volatile(const void *src, volatile int *dest, size_t size);
extern void sys_memset32_fast(u32 value, const void *ptr, size_t size);
extern void *sys_memcpy32_fast(const void *src, void *dst, u32 size);
extern void sys_memset(const void *ptr, u8 value, size_t size);
extern void sys_memset_fast(const void *ptr, u8 value, size_t size);
extern const void *sys_memcpy(const void *src, void *dst, u32 size);
extern s32 sys_memcmp(const void *src1, const void *src2, size_t size);
extern const void *sys_memcpy_fast(const void *src, void *dst, size_t size);
extern const void *sys_memcpy_ex(const void *src, void *dst, s32 size);
// extern "C" u32 j_j_FaintRecord_GetCount_1(FaintRecord *faintRecord, u32 turn);
extern "C" void SortActionOrderBySpeed(ServerFlow *serverFlow, ActionOrderWork *actionOrder, u32 remainingActions);

u8 interruptActionFlag = 0;

u8 sendLastSlots[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

extern "C" void SwapPokemonOrder(ActionOrderWork *actionOrder, u16 *speedStats, u8 *priority, u8 *eventPriority, u8 slowIdx, u8 fastIdx)
{
    BattleMon *bufferMon = actionOrder[fastIdx].battleMon;
    BattleActionParam *bufferAction = actionOrder[fastIdx].Action;
    u32 buffer_speed = actionOrder[fastIdx].field_8;
    u8 buffer_partyID = actionOrder[fastIdx].field_C;
    u8 buffer_done = actionOrder[fastIdx].fDone;
    u8 buffer_field_E = actionOrder[fastIdx].field_E;
    u8 buffer_field_F = actionOrder[fastIdx].field_F;
    u16 bufferSpeed = speedStats[fastIdx];
    u8 bufferPriority = priority[fastIdx];
    u8 bufferEventPriority = eventPriority[fastIdx];

    actionOrder[fastIdx].battleMon = actionOrder[slowIdx].battleMon;
    actionOrder[slowIdx].battleMon = bufferMon;

    actionOrder[fastIdx].Action = actionOrder[slowIdx].Action;
    actionOrder[slowIdx].Action = bufferAction;

    actionOrder[fastIdx].field_8 = actionOrder[slowIdx].field_8;
    actionOrder[slowIdx].field_8 = buffer_speed;

    actionOrder[fastIdx].field_C = actionOrder[slowIdx].field_C;
    actionOrder[slowIdx].field_C = buffer_partyID;

    actionOrder[fastIdx].fDone = actionOrder[slowIdx].fDone;
    actionOrder[slowIdx].fDone = buffer_done;

    actionOrder[fastIdx].field_E = actionOrder[slowIdx].field_E;
    actionOrder[slowIdx].field_E = buffer_field_E;

    actionOrder[fastIdx].field_F = actionOrder[slowIdx].field_F;
    actionOrder[slowIdx].field_F = buffer_field_F;

    speedStats[fastIdx] = speedStats[slowIdx];
    speedStats[slowIdx] = bufferSpeed;

    priority[fastIdx] = priority[slowIdx];
    priority[slowIdx] = bufferPriority;

    eventPriority[fastIdx] = eventPriority[slowIdx];
    eventPriority[slowIdx] = bufferEventPriority;
}

extern "C" void PokeSet_SortBySpeedDynamic(ServerFlow *serverFlow, ActionOrderWork *actionOrder, u8 firstIdx, u8 turnStart)
{
    // Skip the Pok�mons that have already moved.
    u8 startIdx = firstIdx;
    if (!turnStart)
        startIdx += 1;

    // "firstIdx" is the latest Pok�mon to move.
    u8 pokeAmount = serverFlow->numActOrder - startIdx;

    // Reset the send last slots at the start of the turn.
    if (startIdx == 0)
        sys_memset(sendLastSlots, 0xFF, 6);

    if (pokeAmount > 1)
    {
        u16 speedStats[6];
        sys_memset(speedStats, 0, 12);

        u8 priority[6];
        sys_memset(priority, 0, 6);

        // 7 is the default, 6-0 are reserved for quash and 8 for escaping battle.
        u8 eventPriority[6];
        sys_memset(eventPriority, 7, 6);

        for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
        {
            if (!BattleMon_IsFainted(actionOrder[i].battleMon))
            {
                speedStats[i] = (u16)ServerEvent_CalculateSpeed(serverFlow, actionOrder[i].battleMon, 1);

                priority[i] = ACTION_ORDER_GET_PRIO(actionOrder, i);
                // Special priority takes into account item & ability prio boosts (1 = no added prio).
                int specialPriority = ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder, i);
                priority[i] += (specialPriority - 1);

                for (u8 j = 0; j < 6; ++j)
                {
                    if (sendLastSlots[j] == 0xFF)
                        break;

                    // If the mon has been sent last we give them a
                    // "quash speed" from 6 - 0 (non-quashed mons have 7)
                    if (sendLastSlots[j] == actionOrder[i].battleMon->ID)
                        eventPriority[i] = 6 - j;
                    // We don't break after finding a match, a mon can be quashed
                    // multiple times and the only one that matters is the last one
                }

                // This means the mon is making an escape attempt.
                // This makes it first, and overrides any other move priority.
                if (BattleAction_GetAction(&actionOrder[i].Action) == 4)
                    eventPriority[i] = 8;
            }
            else
            {
                priority[i] = 0xFF;
            }
        }

        // We randomize the initial order to resolve speed ties.
        for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
        {
            u8 randomSpot = startIdx + (u8)BattleRandom(pokeAmount);

            if (randomSpot != i)
                SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, randomSpot);
        }

        u8 changes = 1;
        while (changes != 0)
        {
            changes = 0;

            for (u8 i = startIdx; i < serverFlow->numActOrder; ++i)
            {
                // Check if the first Pok�mon is fainted.
                if (priority[i] != 0xFF)
                {
                    if (i + 1 < serverFlow->numActOrder)
                    {
                        for (u8 j = i + 1; j < serverFlow->numActOrder; ++j)
                        {
                            // Check if the second Pok�mon is fainted.
                            if (priority[j] != 0xFF)
                            {
                                u8 poke1EventPriority = eventPriority[i];
                                u8 poke2EventPriority = eventPriority[j];

                                if (poke2EventPriority > poke1EventPriority)
                                {
                                    SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, j);
                                    ++changes;
                                }
                                else if (poke2EventPriority == poke1EventPriority)
                                {
                                    u8 poke1Priority = priority[i];
                                    u8 poke2Priority = priority[j];

                                    if (poke2Priority > poke1Priority)
                                    {
                                        SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, j);
                                        ++changes;
                                    }
                                    else if (poke2Priority == poke1Priority)
                                    {
                                        u16 poke1Speed = speedStats[i];
                                        u16 poke2Speed = speedStats[j];

                                        if (poke2Speed > poke1Speed)
                                        {
                                            SwapPokemonOrder(actionOrder, speedStats, priority, eventPriority, i, j);
                                            ++changes;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

extern "C" u32 THUMB_BRANCH_BattleHandler_InterruptAction(ServerFlow *serverFlow, HandlerParam_InterruptPoke *params)
{
    if (!ActionOrder_InterruptReserve(serverFlow, params->pokeID))
    {
        return 0;
    }
    BattleHandler_SetString(serverFlow, &params->exStr);

    interruptActionFlag = 1;
    return 1;
}

extern "C" u32 THUMB_BRANCH_BattleHandler_SendLast(ServerFlow *serverFlow, HandlerParam_SendLast *params)
{
    if (!ActionOrder_SendToLast(serverFlow, params->pokeID))
    {
        return 0;
    }
    BattleHandler_SetString(serverFlow, &params->exStr);

    // Add the Pok�mon slot to the send last slots.
    for (u8 i = 0; i < 6; ++i)
    {
        if (sendLastSlots[i] == 0xFF)
        {
            sendLastSlots[i] = params->pokeID;
            break;
        }
    }

    return 1;
}

// Defines if a switch should be made after the turn has been processed
// The vanilla game does not have logic to switch after all actions have been performed
// like for example after receiving damage from a status condition
// - Set in [HandlerEmergencyExitSwitchEnd]
// - Reset & used in [ServerFlow_ActOrderProcMain]

// extern "C" u32 CommonGetAllyPos(ServerFlow *serverFlow, u32 battlePos)
// {
//     BattleStyle battleStyle = (BattleStyle)BtlSetup_GetBattleStyle(serverFlow->mainModule);
//     if (battleStyle != BTL_STYLE_DOUBLE && battleStyle != BTL_STYLE_TRIPLE)
//     {
//         return 6;
//     }
//
//     u8 isEnemy = battlePos & 1;
//     if (isEnemy)
//     {
//         battlePos -= 1;
//     }
//
//     u32 allyPos = 0;
//     if (battleStyle != BTL_STYLE_TRIPLE)
//     {
//         if (battlePos == 0)
//         {
//             allyPos = 2;
//         }
//         else
//         {
//             allyPos = 0;
//         }
//     }
//     else
//     {
//         if (IsPosInCenterTripleBattle(battlePos))
//         {
//             allyPos = BattleRandom(2) * 4;
//         }
//         else
//         {
//             allyPos = 2;
//         }
//     }
//
//     return allyPos + isEnemy;
// }

// Stores data of extra action generated by Dancer, Instruct...
// - Set in [HandlerDancerCheckMove]
// - Reset and used in [ServerFlow_ActOrderProcMain]
ActionOrderWork extraActionOrder[6];

extern "C" void ShiftExtraActionOrders()
{
    for (u8 i = 5; i != 0; --i)
    {
        sys_memcpy(&extraActionOrder[i - 1], &extraActionOrder[i], sizeof(ActionOrderWork));
    }
    sys_memset(&extraActionOrder[0], 0, sizeof(ActionOrderWork));
}
extern "C" ActionOrderWork *GetExtraActionOrder(u32 actionIdx)
{
    return extraActionOrder + actionIdx;
}

extern "C" void sub_219FB7C(ServerFlow *a1, ActionOrderWork *a2, unsigned int a3);

// Defines if an extra action is taking place
// - Set and reset in [ServerFlow_ActOrderProcMain]
u8 extraActionFlag = 0;

extern "C" b32 CheckExtraActionFlag()
{
    return extraActionFlag;
}
extern "C" void SetExtraActionFlag()
{
    extraActionFlag = 1;
}
extern "C" void ResetExtraActionFlag()
{
    extraActionFlag = 0;
}
extern "C" void Turnflag_Clear(BattleMon *battleMon, TurnFlag flag);
extern "C" int FaintRecord_GetCount(FaintRecord *a1, unsigned int turn);

extern "C" int getFaintCount(FaintRecord *a1, unsigned int turn)
{
    if (turn >= 4)
    {
        return 0;
    }
    else
    {
        return a1->turnRecord[turn].count;
    }
}

extern "C" int THUMB_BRANCH_SAFESTACK_ServerFlow_ActOrderProcMain(ServerFlow *serverFlow, u32 currentActionIdx)
{
    u32 procAction = 0;
    ActionOrderWork *actionOrderWork = serverFlow->actionOrderWork;

    k::Printf("\n\n====SERVERFLOW_ACTORDERPROCMAIN===\n\n\nThe serverFlow result is %d\n", serverFlow->flowResult);

    for (u8 i = 0; i < 6; ++i)
    {
        sys_memset(&extraActionOrder[i], 0, sizeof(ActionOrderWork));
    }

    // Re-calc speed after switch-ins
    PokeSet_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, 1);

    while (currentActionIdx < serverFlow->numActOrder || extraActionOrder[0].battleMon != nullptr)
    {
        ActionOrderWork *currentActionOrder = &actionOrderWork[currentActionIdx];
        // Swap the current action if an extra one has been scheduled
        u8 isExtraAction = 0;
        if (extraActionOrder[0].battleMon != nullptr)
        {
            isExtraAction = 1;
            currentActionOrder = &extraActionOrder[0];

            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_ACTIONSTART);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_ACTIONDONE);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_MOVEPROCDONE);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_MOVED);
            Turnflag_Clear(currentActionOrder->battleMon, TURNFLAG_USINGFLING);

            SetExtraActionFlag();
        }

        if (!CheckExtraActionFlag())
        {
            // [1 = fight] [2 = item] [3 = switch] [4 = run]
            u32 action = BattleAction_GetAction(&currentActionOrder->Action);
            // I think this recals speed in rotation battles
            if (procAction == 6 && action != 6)
            {
                ServerControl_CheckActivation(serverFlow);
                sub_219FB7C(serverFlow, currentActionOrder, (u32)serverFlow->numActOrder - currentActionIdx);
            }
        }

        procAction = ActionOrder_Proc(serverFlow, currentActionOrder);

        // Skip speed calcs if After You was used
        if (interruptActionFlag != 1)
        {
            // Re-calc speed
            PokeSet_SortBySpeedDynamic(serverFlow, actionOrderWork, (u8)currentActionIdx, 0);
        }
        interruptActionFlag = 0;

        // Move the next extra action to the first slot
        if (isExtraAction)
        {
            for (u8 i = 0; i < 5; ++i)
            {
                sys_memcpy(&extraActionOrder[i + 1], &extraActionOrder[i], sizeof(ActionOrderWork));
            }
            sys_memset(&extraActionOrder[5], 0, sizeof(ActionOrderWork));

            ResetExtraActionFlag();
        }

        u32 getExp = ServerControl_CheckExpGet(serverFlow);
        b32 matchup = ServerControl_CheckMatchup(serverFlow);

        // Stop the turn if the battle ends
        if (matchup)
        {
            serverFlow->flowResult = (FlowResult)4;
            // Don't advance an action if we have an extra action
            if (isExtraAction)
            {
                return currentActionIdx;
            }
            else
            {
                return currentActionIdx + 1;
            }
        }

        // Stop the turn if a new Pok�mon has to enter the battle
        if (serverFlow->flowResult == 6 || serverFlow->flowResult == 1)
        {
            // Don't advance an action if we have an extra action
            if (isExtraAction)
            {
                return currentActionIdx;
            }
            else
            {
                return currentActionIdx + 1;
            }
        }

        // Stop the turn if a Pok�mon died but the battle is not over
        if (getExp)
        {
            serverFlow->flowResult = (FlowResult)3;
            // Don't advance an action if we have an extra action
            if (isExtraAction)
            {
                return currentActionIdx;
            }
            else
            {
                return currentActionIdx + 1;
            }
        }

        // Don't advance an action if we have an extra action
        if (!isExtraAction)
        {
            ++currentActionIdx;
        }
    }

    // Only TurnCheck if the turn is completely over
    if (!serverFlow->flowResult)
    {
        u32 turnCheck = ServerControl_TurnCheck(serverFlow);

        // Battle is over
        if (ServerControl_CheckMatchup(serverFlow))
        {
            serverFlow->flowResult = (FlowResult)4;
            return serverFlow->numActOrder;
        }

        // A Pok�mon fainted during the TurnCheck
        if (turnCheck)
        {
            serverFlow->flowResult = (FlowResult)3;
            return serverFlow->numActOrder;
        }

        if (CheckEndTurnSwitchFlag())
        {
            ResetEndTurnSwitchFlag();

            // Skip TurnCheck if a Pok�mon has to enter the battle during the TurnCheck
            serverFlow->turnCheckSeq = (FlowResult)7;

            serverFlow->flowResult = (FlowResult)1;
            return serverFlow->numActOrder;
        }

        u32 faintedCount = getFaintCount(&serverFlow->faintRecord, 0);
        if (Handler_IsPosOpenForRevivedMon(serverFlow) || faintedCount)
        {
            ServerFlow_ReqChangePokeForServer(serverFlow, &serverFlow->field_4CE);
            ServerDisplay_IllusionSet(serverFlow, &serverFlow->field_4CE);
            serverFlow->flowResult = (FlowResult)2;
            return serverFlow->numActOrder;
        }

        serverFlow->flowResult = (FlowResult)0;
    }
    return serverFlow->numActOrder;
}

// j_j_FaintRecord_GetCount_1
// SortActionOrderBySpeed
#pragma endregion

#pragma region EVMods

/*

    ----------------------------------------------------------------------------------------------------
    ---------------------------------- EV Modifications ------------------------------------------------
    ----------------------------------------------------------------------------------------------------

*/

extern "C" u32 PokeParty_PkmDecryptCheck(PartyPkm *pPkm);
extern "C" u32 PokeParty_GetParamCore(PartyPkm *pkm, PkmField field, void *extra);
extern "C" void PokeParty_PkmEncrypt(PartyPkm *pPkm);

STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
extern "C" EventWorkSave *GameData_GetEventWork(void *gameData);
extern "C" u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);

extern "C" u32 checkEVFlags(u32 param)
{
    EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
    u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16434);
    return *lvl_cap_ptr;
}

extern "C" u32 THUMB_BRANCH_PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra)
{
    u32 ParamCore; // r4

    PokeParty_PkmDecryptCheck(pPkm);
    ParamCore = PokeParty_GetParamCore(pPkm, field, extra);
    PokeParty_PkmEncrypt(pPkm);
    if (field == PF_EvATK || field == PF_EvDEF || field == PF_EvHP || field == PF_EvSPA || field == PF_EvSPD || field == PF_EvSPE)
    {
        ParamCore = ParamCore * checkEVFlags(ParamCore);
    }
    return ParamCore;
}

#pragma endregion

#pragma region Field Effect Stuff

/*

    ----------------------------------------------------------------------------------------------------
    ---------------------------------- COMBINED FIELD EFFECT CHANGES  ----------------------------------
    ----------------------------------------------------------------------------------------------------

*/

#pragma endregion
