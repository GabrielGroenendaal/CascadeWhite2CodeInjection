#ifndef __INCLUDE_ALL_H
#define __INCLUDE_ALL_H

#include <stdint.h>
#include <stddef.h>

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

#ifdef __GNUC__
#define SWAN_PACKED __attribute__((__packed__))
#define SWAN_ALIGNED(x) __attribute__((aligned(x)))
#endif

#ifdef _MSC_VER // unsupported on MSVC
#define SWAN_PACKED
#define SWAN_ALIGNED(x)
#endif

#define NELEMS(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

#ifdef __cplusplus
#define STRUCT_DECLARE(tag) struct tag;
#define UNION_DECLARE(tag) union tag;
#define ENUM_DECLARE(tag) enum tag : u32;
#else
#define STRUCT_DECLARE(tag) typedef struct tag tag;
#define UNION_DECLARE(tag) typedef union tag tag;
#define ENUM_DECLARE(tag) typedef enum tag tag;
#endif

typedef uint64_t u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;
typedef int32_t b32; // 32-bit bool
typedef u16 HeapID;
u32 &HIDWORD(u64 &x)
{
    return *(reinterpret_cast<u32 *>(&x) + 1);
}
u32 &LODWORD(u64 &x)
{
    return *(reinterpret_cast<u32 *>(&x) + 0);
}
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define wchar_t short
#ifdef __GNUC__
#define SWAN_PACKED __attribute__((__packed__))
#endif
#ifdef _MSC_VER // unsupported on MSVC
#define SWAN_PACKED
#endif
#if defined(_MSC_VER)
#define INLINE inline __forceinline
#elif defined(__GNUC__)
#define INLINE inline __attribute__((always_inline))
#endif
#ifdef __cplusplus
#define C_DECL_BEGIN \
    extern "C"       \
    {
#define C_DECL_END } // extern "C"
#define SWAN_CPPTYPE(ns, typename) \
    namespace ns                   \
    {                              \
        typedef typename typename; \
    }
#define SWAN_CPPTYPE_EX(ns, cppTypename, typename) \
    namespace ns                                   \
    {                                              \
        typedef typename cppTypename;              \
    }
#define SWAN_CPPONLY(code) code
#else
#define C_DECL_BEGIN
#define C_DECL_END
#define SWAN_CPPTYPE(ns, typename)
#define SWAN_CPPTYPE_EX(ns, cppTypename, typename)
#define SWAN_CPPONLY(code)
#endif

#endif

extern "C" b32 SearchArray(const u32* const arr, const u32 arrSize, const u32 value) {
    for (u32 i = 0; i < arrSize; ++i) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)
#include "../codeinjection_battlefield.h"
#include "../kPrint.h"
#include "../settings.h"



#pragma region BattleFieldSetup

struct BattleFieldExt
{
    WeatherID weather;
    BattleEventItem *battleEventItems[FIELD_EFFECT_AMOUNT];
    ConditionData conditionData[FIELD_EFFECT_AMOUNT];
    u32 turnCount[FIELD_EFFECT_AMOUNT];
    u32 dependPokeID[FIELD_EFFECT_AMOUNT][6];
    u32 dependPokeCount[FIELD_EFFECT_AMOUNT];
    u32 effectEnableFlags[FIELD_EFFECT_AMOUNT];

    // Stores the damage a Substitute takes each action
    // - Reset in [ServerControl_DamageRoot] & [CommonEmergencyExitCheck]
    // - Set in [BattleMon_AddSubstituteDamage]
    // - Used in [CommonEmergencyExitCheck]
    u32 actionSubstituteDamage[31];
    u8 firstTurnMons[6] = {31};
    // Tracks which Emergency Exit Pok�mon should switch after the move is over
    // - Used in [CommonEmergencyExitCheck] & [HandlerEmergencyExitSwitch]
    u32 emergencyExitFlag;

    u8 neutralizingGasMons;
};
BattleFieldExt *g_BattleField;

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
    return g_BattleField->actionSubstituteDamage[battleSlot];
}
extern "C" void BattleField_SetSubstituteDamage(u32 battleSlot, u32 value)
{
    g_BattleField->actionSubstituteDamage[battleSlot] = value;
}

extern "C" b32 BattleField_CheckEmergencyExitFlag(u32 battleSlot)
{
    return (g_BattleField->emergencyExitFlag >> battleSlot) & 1;
}
extern "C" void BattleField_SetEmergencyExitFlag(u32 battleSlot)
{
    g_BattleField->emergencyExitFlag |= (1 << battleSlot);
}
extern "C" void BattleField_ResetEmergencyExitFlag(u32 battleSlot)
{
    g_BattleField->emergencyExitFlag &= ~(1 << battleSlot);
}

extern "C" u32 BattleField_GetNeutralizingGasMons()
{
    return g_BattleField->neutralizingGasMons;
}
extern "C" void BattleField_AddNeutralizingGasMon()
{
    ++g_BattleField->neutralizingGasMons;
}
extern "C" void BattleField_RemoveNeutralizingGasMon()
{
    --g_BattleField->neutralizingGasMons;
}

extern "C" b32 SwitchedInThisTurn(ServerFlow *serverFlow, BattleMon *battleMon)
{
    if (serverFlow->turnCount == 0)
    {
        for (u8 i = 0; i < 6; ++i)
        {
            if (g_BattleField->firstTurnMons[i] == battleMon->ID)
            {
                // A Pok�mon that started the battle doesn't count as just switched in
                return 0;
            }
        }
    }
    return !battleMon->TurnCount;
}

#pragma endregion


#pragma region Berserk

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
            u32 currentHPPercent = (currentHP * 100) / maxHP;

            u32 beforeDmgHP = currentHP + BattleEventVar_GetValue(VAR_DAMAGE) - BattleField_GetSubstituteDamage(pokemonSlot);
            u32 beforeDmgHPPercent = (beforeDmgHP * 100) / maxHP;
            if (beforeDmgHPPercent >= 50)
            {
                if (currentHPPercent < 50)
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
                }
            }

            BattleField_SetSubstituteDamage(pokemonSlot, 0);
        }
    }
}
BattleEventHandlerTableEntry BerserkHandlers[]{
    {EVENT_DAMAGE_PROCESSING_END_HIT_2, (BattleEventHandler)HandlerBerserk},
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

#define BATTLE_NEUTRALIZING_GAS_START_MSGID 221
#define BATTLE_NEUTRALIZING_GAS_END_MSGID 222

AbilID abilityCantBeNeutralized[] = {
    ABIL121_MULTITYPE,
    ABIL076_NEUTRALIZING_GAS

};

extern "C" b32 AbilityCantBeNeutralized(AbilID ability) {
    return SEARCH_ARRAY((const u32*)abilityCantBeNeutralized, ability); }


extern "C" void ServerEvent_AbilityNullified(ServerFlow *a1, BattleMon *a2);
extern "C" void ServerEvent_AbilityNullifyCured(ServerFlow *serverFlow, BattleMon *battleMon)
{
    BattleEventVar_Push();
    u32 currentSlot = BattleMon_GetID(battleMon);
    BattleEventVar_SetConstValue(VAR_MON_ID, currentSlot);
    // Abilities with an effect when given also activate when they stop being nullifyed
    BattleEvent_CallHandlers(serverFlow, EVENT_AFTER_ABILITY_CHANGE);
    BattleEventVar_Pop();
}

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
        !AbilityCantBeNeutralized((AbilID)BattleMon_GetValue(a1, VALUE_ABILITY))) {
        return 1;
    }
 
    return (a1->Conditions[a2] & 7) != 0;
    
}

extern "C" void NeutralizingGasEnd(ServerFlow *serverFlow, u32 pokemonSlot)
{
    BattleField_RemoveNeutralizingGasMon();

    // Only trigger the nullify cured events if there are no more Neutralizing Gas Pok�mon
    if (BattleField_GetNeutralizingGasMons() == 0)
    {
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
                        if (BattleMon_GetValue(affectedMon, VALUE_ABILITY) != ABIL076_NEUTRALIZING_GAS)
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
extern "C" BattleEventHandlerTableEntry *EventAddNeutralizingGas(u32 *handlerAmount)
{
    *handlerAmount = ARRAY_COUNT(NeutralizingGasHandlers);
    return NeutralizingGasHandlers;
}

#pragma endregion

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

extern "C" u32 checkEVFlags(u32 param){
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
  if (field == PF_EvATK || field == PF_EvDEF || field == PF_EvHP || field == PF_EvSPA || field == PF_EvSPD || field == PF_EvSPE){
    ParamCore = ParamCore * checkEVFlags(ParamCore);
  }
  return ParamCore;
}