

#include "definitions/codeinjection_battlefield.h"
#include "definitions/kPrint.h"
#include "definitions/settings.h"
#include "definitions/swantypes.h"
#include "definitions/kDLL.h"

#define TESTING_NO_NEGATIVE_SCALING true

// Temporary: tracing an in-game "undefined instruction" crash through the DLL
// loading / ability-event dispatch path. Lights up the DPRINT/DPRINTF calls
// already scattered through LoadDll/FreeDll below (they were previously dead
// - LIBRARY_LOAD_DEBUG/DPRINT/DPRINTF were never defined anywhere) plus new
// tracing added around every function-pointer call, which is the most likely
// place a bad/unrelocated pointer would produce an undefined instruction.
#define LIBRARY_LOAD_DEBUG false
#define DPRINT(msg) k::Printf(msg)
#define DPRINTF(fmt, ...) k::Printf(fmt, __VA_ARGS__)

// Not extern "C": overloaded below for u16 arrays too (MOLD_BREAKER_AFFECTED_ABILITIES
// etc.) - extern "C" linkage would collide since it disables C++ overload resolution.
u32 SearchArray(const u32 *const arr, const u32 arrSize, const u32 value)
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


#pragma region DLL_Loading
#define MAX_LOADED_DLLS 72
// name is a fixed-size buffer (not a `const char*`) that we copy into in LoadDll,
// rather than storing the caller's pointer directly. produceDLLName() returns a
// pointer to its own `static char result[20]` that gets overwritten on every call,
// so every slot's name would otherwise alias that same buffer - every strcmp below
// would then compare the buffer against itself (always "equal"), so a second ability
// loading here would be treated as "already loaded" and hand back the FIRST loaded
// ability's handle instead of loading its own module (e.g. Thick Fat silently got
// Savant's handle and GetProcAddress("e2f") failed because Savant's module doesn't
// export that symbol).
struct LoadedDll
{
    char name[20];
    u32 count;
    k::dll::LibraryHandle handle;
};

// List of loaded DLLs in the current battle
// Loaded in [FieldEffectEvent_AddItem], [SideEffectEvent_AddItem], [AbilityEvent_AddItem], [ItemEvent_AddItem], [MoveEvent_AddItem]
// Freed in [BattleEventItem_Remove]
// Reset in [BattleField_Free]
LoadedDll loadedDlls[MAX_LOADED_DLLS];
extern "C" void ClearDll(u32 idx) {
    loadedDlls[idx].name[0] = '\0';
    loadedDlls[idx].count = 0;
}
extern "C" void ClearLoadedDlls() {
    #if LIBRARY_LOAD_DEBUG
        DPRINT("Clearing Dlls!\n");
    #endif
    for (u32 dllIdx = 0; dllIdx < MAX_LOADED_DLLS; ++dllIdx)
        ClearDll(dllIdx);
}
#if LIBRARY_LOAD_DEBUG
extern "C" void PrintLoadedDlls() {
    for (u8 dllIdx = 0; dllIdx < 24; ++dllIdx) {

        if (loadedDlls[dllIdx].name[0] == '\0') {
            DPRINT("--- \n");
        }
        else {
            DPRINTF("%s (%d) \n", loadedDlls[dllIdx].name, loadedDlls[dllIdx].count);
        }
    }
}
#endif

extern "C" int strcmp(const char* str1, const char* str2);
extern "C" char* strcpy(char* dst, const char* src);
extern "C" b32 LoadDll(const char* dllName)
{
    if (dllName == nullptr)
        return 1;

    for (u8 dllIdx = 0; dllIdx < MAX_LOADED_DLLS; ++dllIdx)
    {
        if (loadedDlls[dllIdx].name[0] == '\0')
        {
            // MakeLibraryPath (kDLL.cpp) builds the real NitroFS path this way:
            // LIBRARY_PATH_PREFIX + dllName + LIBRARY_PATH_SUFFIX. Reconstructing
            // and printing it here shows exactly what path the game is about to
            // try to open, to compare against what's actually in the ROM's NitroFS.
            k::dll::LibraryHandle handle = k::dll::LoadLibrary(dllName);
            if (!handle)
            {
                return 0;
            }
            strcpy(loadedDlls[dllIdx].name, dllName);
            loadedDlls[dllIdx].count = 1;
            loadedDlls[dllIdx].handle = handle;
            break;
        }
        if (strcmp(loadedDlls[dllIdx].name, dllName) == 0)
        {
            ++loadedDlls[dllIdx].count;
            break;
        }
    }
    return 1;
}

// Looks up the handle of an already-loaded DLL by name (set in LoadDll above),
// so callers can GetProcAddress into it once LoadDll reports success.
extern "C" k::dll::LibraryHandle GetLoadedDllHandle(const char* dllName)
{
    for (u8 dllIdx = 0; dllIdx < MAX_LOADED_DLLS; ++dllIdx)
    {
        if (loadedDlls[dllIdx].name[0] == '\0')
            return nullptr;
        if (strcmp(loadedDlls[dllIdx].name, dllName) == 0)
            return loadedDlls[dllIdx].handle;
    }
    return nullptr;
}
extern "C" void FreeDll(const char* dllName) {
    if (dllName == nullptr)
        return;

    for (u8 dllIdx = 0; dllIdx < MAX_LOADED_DLLS; ++dllIdx) {
        if (loadedDlls[dllIdx].name[0] == '\0')
            break;

        if (strcmp(loadedDlls[dllIdx].name, dllName) == 0) {

            --loadedDlls[dllIdx].count;
            if (loadedDlls[dllIdx].count == 0) {
                k::dll::ReleaseLibrary(loadedDlls[dllIdx].name);
                //k::Printf("FreeDll: released %s (refcount hit 0)\n", dllName);
                for (; dllIdx < MAX_LOADED_DLLS; ++dllIdx) {
                    if (dllIdx == MAX_LOADED_DLLS - 1 ||
                        loadedDlls[dllIdx + 1].name[0] == '\0') {
                        ClearDll(dllIdx);
                        break;
                    }

                    loadedDlls[dllIdx] = loadedDlls[dllIdx + 1];
                }
            }
            else {
                //k::Printf("FreeDll: decremented %s (refcount now %d, not released)\n", dllName, loadedDlls[dllIdx].count);
            }
            return;
        }
    }
    //k::Printf("FreeDll: %s was not loaded!\n", dllName);
}
extern "C" void FreeLoadedDlls() {
    // Free all the loaded code
    for (u8 dllIdx = 0; dllIdx < MAX_LOADED_DLLS; ++dllIdx)
    {
        if (loadedDlls[dllIdx].name[0] == '\0')
            break;

        k::dll::ReleaseLibrary(loadedDlls[dllIdx].name);
        #if LIBRARY_LOAD_DEBUG
                DPRINTF("Freed %s!\n", loadedDlls[dllIdx]);
        #endif
        loadedDlls[dllIdx].name[0] = '\0';
        loadedDlls[dllIdx].count = 0;
    }
    ClearLoadedDlls();
}

#pragma endregion


#pragma region BattleFieldSetup

u8 entryTurn = 0;
bool checkIfWildBattle(ServerFlow *a1)
{
    return a1->mainModule->btlSetup->btlType == 0;
}

struct BattleFieldExt
{
    u32 actionSubstituteDamage[31];
    // u8 firstTurnMons[6] = {31};
    // Tracks which Emergency Exit Pok�mon should switch after the move is over
    // - Used in [CommonEmergencyExitCheck] & [HandlerEmergencyExitSwitch]
    u32 emergencyExitFlag;
    u32 BerserkFlag;
    u8 neutralizingGasMons;
    u32 Test;
    u8 entrySlots[31];
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
    entryTurn = 0;
    if (!g_BattleVars)
    {
        g_BattleVars = (BattleFieldExt *)GFL_HeapAllocate(a1, sizeof(BattleFieldExt), 1, "btl_field.c", 0x10Cu);
        g_BattleVars->neutralizingGasMons = 0;
        g_BattleVars->emergencyExitFlag = 0;
        g_BattleVars->BerserkFlag = 0;
        g_BattleVars->Test = 5;
        sys_memset(g_BattleVars->actionSubstituteDamage, 0, 31 * sizeof(u32));
        sys_memset(g_BattleVars->entrySlots, 31, 31);
    }
    v1 = (BattleField *)GFL_HeapAllocate(a1, 0x168u, 1, "btl_field.c", 0x10Cu);
    BattleField_InitCore(v1, 0);
    return v1;
}

extern "C" int ServerEvent_CheckMultihitHits(ServerFlow *a1, BattleMon *a2, int a3, HitCheckParam *a4);
extern "C" void THUMB_BRANCH_LINK_ServerControl_DamageRoot_0x36(ServerFlow *serverFlow, BattleMon *attackingMon, MoveID moveID, HitCheckParam *hitCheckParam)
{
    ServerEvent_CheckMultihitHits(serverFlow, attackingMon, moveID, hitCheckParam);
    sys_memset(g_BattleVars->actionSubstituteDamage, 0, 31 * sizeof(u32));
}

extern "C" void GFL_HeapFree(void *heap);

extern "C" void THUMB_BRANCH_BattleField_Free(void *battleField)
{
    if (g_BattleVars)
    {
        GFL_HeapFree(g_BattleVars);
        g_BattleVars = nullptr;
        FreeLoadedDlls();
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
        // k::Printf("PosPoke Slot %d: existPokeID=%d, fEnable=%d\n", i,  v3.existPokeID, v3.fEnable);
        if (v3.fEnable && v3.existPokeID == pokemonslot)
        {
            return i;
        }
    }
    return 6;
}

// Neutralizing Gas - Added event when an ability stops being nullyfied (EVENT_AFTER_ABILITY_CHANGE)
extern "C" void THUMB_BRANCH_SAFESTACK_ServerControl_CureCondition(ServerFlow *serverFlow, BattleMon *battleMon, MoveCondition condition, ConditionData *prevCondition)
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
            int pokemonPos = PosPoke_GetPokeExistPos(&serverFlow->posPoke, pokemonSlot);
            // k::Printf("Checking status condition for slot %d at pos %d\n", pokemonSlot, pokemonPos);
            // k::Printf("Trying this out: %d\n", PosPoke_IsExist(&serverFlow->posPoke, pokemonSlot));
            // k::Printf("Our pospoke function returns %d\n", checkPosPoke(serverFlow->posPoke, pokemonSlot));
            if (pokemonPos != 6)
            {
                // k::Printf("Cured status condition for slot %d at pos %d\n", pokemonSlot, pokemonPos);

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

extern "C" void ServerEvent_SwitchInPriority(ServerFlow *serverFlow)
{
    PokeSet *set = (PokeSet *)((int)serverFlow + 0x1A68);
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

#pragma endregion

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
    u32 currentHPPercent = div32((currentHP * 100), maxHP);

    u32 beforeDmgHP = currentHP + BattleEventVar_GetValue(VAR_DAMAGE) - BattleField_GetSubstituteDamage(currentSlot);
    u32 beforeDmgHPPercent = div32((beforeDmgHP * 100), maxHP);
#if DEBUGGING_DYNAMICSPEED && DEBUGGING_ALL
    k::Printf("MAX HP: %d \n", maxHP);
    k::Printf("CURRENT HP: %d \n", currentHP);
    k::Printf("DAMAGE: %d \n", BattleEventVar_GetValue(VAR_DAMAGE));
    k::Printf("SUBSTITUTE DAMAGE: %d \n", BattleField_GetSubstituteDamage(currentSlot));
    k::Printf("BEFORE HP: %d \n", beforeDmgHP);
    k::Printf("BEFORE HP PERCENT: %d \n", beforeDmgHPPercent);
    k::Printf("CURRENT HP PERCENT: %d \n", currentHPPercent);
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
                // #if DEBUGGING_DYNAMICSPEED && DEBUGGING_ALL
                // #endif
                if (Handler_GetFightEnableBenchPokeNum(serverFlow, pokemonSlot) && Handler_CheckReservedMemberChangeAction(serverFlow))
                {
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
}
extern "C" void HandlerEmergencyExitSimpleCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{

    if (IS_NOT_NEW_EVENT)
        return;

    if (pokemonSlot == BattleEventVar_GetValue(NEW_VAR_MON_ID))
    {

        CommonEmergencyExitCheck(serverFlow, pokemonSlot);
    }
}
extern "C" void HandlerEmergencyExitSwitchEnd(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
{
    if (BattleField_CheckEmergencyExitFlag(pokemonSlot))
    {
        BattleField_ResetEmergencyExitFlag(pokemonSlot);

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
    *handlerAmount = 3;
    return EmergencyExitHandlers;
}

#pragma endregion

#pragma region NeutralizingGas

#define BATTLE_NEUTRALIZING_GAS_START_MSGID 240
#define BATTLE_NEUTRALIZING_GAS_END_MSGID 241

u32 abilityCantBeNeutralized[] = {
    ABIL046_NEUTRALIZING_GAS,
    ABIL121_MULTITYPE,
    ABIL002_DRIZZLE,
    ABIL070_DROUGHT,
    ABIL045_SAND_STREAM,
    ABIL117_SNOW_WARNING,
    ABIL150_IMPOSTER,
    ABIL149_ILLUSION
};

extern "C" b32 AbilityCantBeNeutralized(AbilID ability)
{
    return SEARCH_ARRAY((const u32 *)abilityCantBeNeutralized, ability);
}

extern "C" void ServerEvent_AbilityNullified(ServerFlow *a1, BattleMon *a2);

extern "C" bool THUMB_BRANCH_SAFESTACK_BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2)
{
    if (a1->HeldItem == IT0289_ASSAULT_VEST && a2 == CONDITION_TAUNT)
    {
        return true;
    }

    
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
    *handlerAmount = ARRAY_COUNT(NeutralizingGasHandlers);
    return NeutralizingGasHandlers;
}

#pragma endregion

#pragma region AlteredEntryTurnProcessing

// Stores data of extra action generated by Dancer, Instruct...
// - Set in [HandlerDancerCheckMove]
// - Reset and used in [ServerFlow_ActOrderProcMain]

// extern "C" bool ProcessEntryTurn(ServerFlow *serverFlow)
// {
//     serverFlow->field_78A &= ~8u;
//     PokeSet_Clear(&serverFlow->switching_in_mons);

//     FRONT_POKE_SEEK_WORK seekWork[6];
//     FRONT_POKE_SEEK_InitWork(seekWork, serverFlow);

//     BattleMon *battleMon;
//     while (FRONT_POKE_SEEK_GetNext(seekWork, serverFlow, &battleMon))
//     {
//         PokeSet_Add(&serverFlow->switching_in_mons, battleMon);
//         serverFlow->field_7C1[BattleMon_GetID(battleMon)] = 0;
//     }

//     PokeSet_SortBySpeed(&serverFlow->switching_in_mons, serverFlow);
//     u32 HEID = HEManager_PushState(&serverFlow->heManager);
//     ServerEvent_AfterSwitchInPrevious(serverFlow);
//     HEManager_PopState(&serverFlow->heManager, HEID);

//     PokeSet_SeekStart(&serverFlow->switching_in_mons);
//     for (battleMon = PokeSet_SeekNext(&serverFlow->switching_in_mons); battleMon; battleMon = PokeSet_SeekNext(&serverFlow->switching_in_mons))
//     {

//         // Check the entry Pok�mon array
//         u8 entryIdx = 0;
//         for (; entryIdx < 31; ++entryIdx)
//         {
//             u8 entry = g_BattleVars->entrySlots[entryIdx];
//             u8 slot = BattleMon_GetID(battleMon);

//             if (entry == slot)
//             {
//                 // Don't process already processed Pok�mon
//                 entryIdx = 0xFF;
//                 break;
//             }
//             if (entry == 31)
//             {
//                 // Store the new Pok�mon so it's no longer processed
//                 g_BattleVars->entrySlots[entryIdx] = slot;
//                 break;
//             }
//         }
//         if (entryIdx == 0xFF)
//         {
//             continue;
//         }

//         HEID = HEManager_PushState(&serverFlow->heManager);
//         ServerEvent_SwitchIn(serverFlow, battleMon);
//         HEManager_PopState(&serverFlow->heManager, HEID);

//         HEID = HEManager_PushState(&serverFlow->heManager);
//         ServerEvent_ActProcEnd(serverFlow, battleMon, 0);
//         HEManager_PopState(&serverFlow->heManager, HEID);

//         u32 getExp = ServerControl_CheckExpGet(serverFlow);
//         b32 matchup = ServerControl_CheckMatchup(serverFlow);

//         // Stop the entry turn if the battle ends
//         if (matchup)
//         {
//             serverFlow->flowResult = (FlowResult)4;
//             return false;
//         }

//         // Stop the entry turn if a new Pok�mon has to enter the battle
//         if (serverFlow->flowResult == 6 || serverFlow->flowResult == 1)
//         {
//             return false;
//         }

//         // Stop the entry turn if a Pok�mon died but the battle is not over
//         if (getExp)
//         {
//             serverFlow->flowResult = (FlowResult)3;
//             return false;
//         }
//     }

//     HEID = HEManager_PushState(&serverFlow->heManager);
//     ServerEvent_AfterLastSwitchIn(serverFlow);
//     HEManager_PopState(&serverFlow->heManager, HEID);

//     // Finish the entry turn
//     serverFlow->flowResult = (FlowResult)0;
//     return true;
// }

// extern "C" void THUMB_BRANCH_LINK_ServerControl_ActOrderProc_OnlyPokeIn_0x82(ServerFlow *serverFlow)
// {
//     if (entryTurn != 0)
//     {
//         ServerControl_AfterSwitchIn(serverFlow);
//     }
// }

// extern "C" bool BattleClient_SubProc_UI_SelectAction(BtlClientWk *btlClient, unsigned int *state);
// extern "C" bool sub_21B22AC(BtlClientWk *a1, unsigned int *a2);
// extern "C" bool sub_21B2258(BtlClientWk *a1, unsigned int *a2);
// extern "C" unsigned int MainModule_IsCompetitorScenarioMode(MainModule *a1);

// extern "C" bool THUMB_BRANCH_sub_21B23F8(BtlClientWk *btlClient, unsigned int *a2, int a3, int a4)
// {
//     // k::Printf("\nSUBPROC_UI_SELECTACTION\nentryTurn = %d\n\n\n", entryTurn);
//     if (entryTurn != 0)
//     {
//         if (MainModule_IsCompetitorScenarioMode(btlClient->mainModule) == 1)
//         {
//             return sub_21B22AC(btlClient, a2);
//         }
//         else
//         {
//             return BattleClient_SubProc_UI_SelectAction(btlClient, a2);
//         }
//     }
//     return 1;
// }

#pragma endregion

#pragma region DynamicSpeed

#define ACTION_ORDER_GET_PRIO(actionOrder, idx) (actionOrder[idx].field_8 >> 16) & 0x3FFFFF
#define ACTION_ORDER_GET_SPECIAL_PRIO(actionOrder, idx) ((actionOrder[idx].field_8 >> 13) & 0x7)

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

// extern "C" void THUMB_BRANCH_ServerEvent_BeforeAttacks(ServerFlow *a1, BattleMon *a2, int a3)
// {
//     int ID; // r0

//     //   k::Printf("Dynamic Speed - Before Attacks Event\n");
//     BattleEventVar_Push();
//     ID = BattleMon_GetID(a2);
//     BattleEventVar_SetValue(VAR_MON_ID, ID);
//     BattleEventVar_SetValue(VAR_MOVE_ID, a3);
//     BattleEvent_CallHandlers(a1, EVENT_BEFORE_ATTACKS);
//     BattleEventVar_Pop();
// }

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

#if DEBUGGING_DYNAMICSPEED && DEBUGGING_ALL
    k::Printf("\n\n====SERVERFLOW_ACTORDERPROCMAIN===\n\n\nThe serverFlow result is %d\n", serverFlow->flowResult);
#endif
    // if (entryTurn == 0)
    // {
    //     if (ProcessEntryTurn(serverFlow))
    //     {
    //         entryTurn = 1;
    //     }
    //     return 0;
    // }

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

#pragma endregion

#pragma region EjectButton

struct FRONT_POKE_SEEK_WORK
{
    u8 clientIdx;
    u8 pokeIdx;
    u8 endFlag;
    u8 unk;
};

extern "C" void FRONT_POKE_SEEK_InitWork(FRONT_POKE_SEEK_WORK *frontSet, ServerFlow *serverFlow);
extern "C" b32 FRONT_POKE_SEEK_GetNext(FRONT_POKE_SEEK_WORK *frontSet, ServerFlow *serverFlow, BattleMon **battleMon);
extern "C" void PokeSet_Clear(PokeSet *pokeSet);
extern "C" void ServerEvent_ActProcEnd(ServerFlow *serverFlow, BattleMon *currentMon, u32 action);
extern "C" void ServerEvent_AfterSwitchInPrevious(ServerFlow *serverFlow);
extern "C" void ServerEvent_SwitchIn(ServerFlow *serverFlow, BattleMon *battleMon);
extern "C" void ServerEvent_AfterLastSwitchIn(ServerFlow *serverFlow);
extern "C" void PokeSet_Add(PokeSet *pokeSet, BattleMon *battleMon);
extern "C" u32 PokeSet_SortBySpeed(PokeSet *pokeSet, ServerFlow *serverFlow);
extern "C" u32 ServerControl_ActOrderProc_OnlyPokeIn(ServerFlow *serverFlow, u32 *clientAction);
extern "C" BtlServerWk *BattleServer_InitChangePokemonReq(BtlServerWk *result);
extern "C" void BattleEventVar_CheckStackCleared();

extern "C" u32 ServerFlow_SwitchEndTurn(ServerFlow *serverFlow, u32 *clientAction)
{
    serverFlow->flowResult = (FlowResult)0;
    serverFlow->serverCommandQueue->writePtr = 0;
    serverFlow->serverCommandQueue->readPtr = 0;

    // Reset switch flag (used in Handler_CheckReservedMemberChangeAction)
    serverFlow->field_78A &= ~8u;

    if (serverFlow->cmdBuildStep ||
        (BattleServer_InitChangePokemonReq(serverFlow->server),
         BattleEventVar_CheckStackCleared(),
         serverFlow->field_77D = 0,
         serverFlow->cmdBuildStep = 1,
         !ServerControl_ActOrderProc_OnlyPokeIn(serverFlow, clientAction)))
    {

        FRONT_POKE_SEEK_WORK seekWork[6];
        FRONT_POKE_SEEK_InitWork(seekWork, serverFlow);

        BattleMon *battleMon;
        while (FRONT_POKE_SEEK_GetNext(seekWork, serverFlow, &battleMon))
        {
            ServerEvent_ActProcEnd(serverFlow, battleMon, 0);
            if (serverFlow->flowResult == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

extern "C" u32 sub_219F214(BtlServerWk *btlServer);
extern "C" u32 sub_219DF90(MainModule *mainModule);
extern "C" void sub_219F0EC(BtlServerWk *btlServer);
extern "C" bool sub_219F06C(BtlServerWk *btlServer, u8, u8);
extern "C" void sub_219F168(BtlServerWk *server, u16 cmdID, u8 *data, u32 dataSize);
extern "C" bool BattleServer_IsWaitingClientReply(BtlServerWk *btlServer);
#define SEQUENCE_FUNCTION(name) u32 (*name)(BtlServerWk * btlServer, u32 * statePtr)
extern "C" void BattleServer_ChangeSequence(BtlServerWk *btlServer, SEQUENCE_FUNCTION(sequence));
extern "C" void BattleServer_SetDefaultSequence(BtlServerWk *btlServer);
extern "C" BtlServerWk *BattleServer_InitChangePokemonReq(BtlServerWk *result);

extern "C" u32 BtlServer_EndTurnSequence(BtlServerWk *btlServer, u32 *state)
{
    switch (*state)
    {
    case 0:
        sub_219F168(btlServer, 6, &btlServer->field_CB4, btlServer->field_CBA);
        *state = 1;
        break;
    case 1:
        if (!BattleServer_IsWaitingClientReply(btlServer))
        {
            return 0;
        }
        sub_219F214(btlServer);
        if (sub_219DF90((MainModule *)btlServer->mainModule))
        {
            BattleServer_ChangeSequence(btlServer, (SEQUENCE_FUNCTION())0x219ECC5); // BtlServer_EndMatchSequence
        }
        else
        {
            sub_219F0EC(btlServer);
            if (!sub_219F06C(btlServer, 2u, 0))
            {
                *state = 3;
            }
            else
            {
                *state = 2;
            }
        }
        break;
    case 2:
        if (!BattleServer_IsWaitingClientReply(btlServer))
        {
            return 0;
        }
        sub_219F214(btlServer);
        *state = 3;
        return 0;
    case 3:
        sub_219F214(btlServer);
        btlServer->serverFlow->cmdBuildStep = 0;
        *state = 4;
    case 4:
        btlServer->serverTurnState = ServerFlow_SwitchEndTurn(btlServer->serverFlow, &btlServer->clientAction);
        sub_219F168(btlServer, 8, btlServer->field_CB0 + 8, *btlServer->field_CB0);
        *state = 5;
        break;
    case 5:
        if (!BattleServer_IsWaitingClientReply(btlServer))
        {
            return 0;
        }
        sub_219F214(btlServer);
        switch (btlServer->serverTurnState)
        {
        case 1:
            *state = 0;
            break;
        default:
            BattleServer_SetDefaultSequence(btlServer);
            break;
        }
        break;
    }

    return 0;
}

extern "C" void THUMB_BRANCH_LINK_BtlServer_StartBattleSequence_0x9C(BtlServerWk *btlServer)
{
    BattleServer_ChangeSequence(btlServer, BtlServer_EndTurnSequence);
}

extern "C" void THUMB_BRANCH_LINK_BtlServer_FaintSequence_0x136(BtlServerWk *btlServer)
{
    BattleServer_ChangeSequence(btlServer, BtlServer_EndTurnSequence);
}
#pragma endregion

#pragma region EVMods

/*

    ----------------------------------------------------------------------------------------------------
    ---------------------------------- EV Modifications ------------------------------------------------
    ----------------------------------------------------------------------------------------------------

*/

// extern "C" u32 PokeParty_PkmDecryptCheck(PartyPkm *pPkm);
// extern "C" u32 PokeParty_GetParamCore(PartyPkm *pkm, PkmField field, void *extra);
// extern "C" void PokeParty_PkmEncrypt(PartyPkm *pPkm);

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

// extern "C" u32 THUMB_BRANCH_PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra)
// {
//     u32 ParamCore; // r4

//     PokeParty_PkmDecryptCheck(pPkm);
//     ParamCore = PokeParty_GetParamCore(pPkm, field, extra);
//     PokeParty_PkmEncrypt(pPkm);
//     if (field == PF_EvATK || field == PF_EvDEF || field == PF_EvHP || field == PF_EvSPA || field == PF_EvSPD || field == PF_EvSPE)
//     {
//         ParamCore = ParamCore * checkEVFlags(ParamCore);
//     }
//     return ParamCore;
// }

extern "C" s32 fx_sqrt(s32 num);
extern "C" u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);

extern "C" u32 GetExpForLevel100(BattleMon *a1)
{
    return PML_UtilGetPkmLvExp(a1->Species, a1->Form, 100);
}
extern "C" u32 checkLevelCap(u8 level)
{
    EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
    u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16465);
    if (*lvl_cap_ptr == 1){
        u16* lvl_cap_value = EventWork_GetWkPtr(eventWork, 16466);
        if (level >= *lvl_cap_value) {
            return 0;
        } else {
            return 1;
        }
    } 
    return 1;
}

extern "C" u32 scaleExpToLevelCap(unsigned int amountOfExpGainedSoFar, u8 defeatedMonLevel, u8 monGainingExpLevel)
{
    EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
    u16 *exp_boost_ptr = EventWork_GetWkPtr(eventWork, 16467);

    if (*exp_boost_ptr == 1){
        u16* lvl_cap_value = EventWork_GetWkPtr(eventWork, 16466);
        if (monGainingExpLevel >= *lvl_cap_value){
            if (defeatedMonLevel >= (monGainingExpLevel - 5)){
                return (defeatedMonLevel - 10);
            }
        }
        else {
            if (defeatedMonLevel < *lvl_cap_value){
                if (monGainingExpLevel <= (*lvl_cap_value - 5)){
                    return (defeatedMonLevel + (*lvl_cap_value * 2));
                } 
                else {
                    return *lvl_cap_value;
                }
            } 
        }
    } 
    else if (*exp_boost_ptr == 2){
        u16* lvl_cap_value = EventWork_GetWkPtr(eventWork, 16466);
        if (monGainingExpLevel >= *lvl_cap_value){
            if (defeatedMonLevel >= (monGainingExpLevel - 5)){
                return (defeatedMonLevel - 10);
            }
        }
        else {
            if (defeatedMonLevel < *lvl_cap_value){
                if (monGainingExpLevel <= (*lvl_cap_value - 5)){
                    return (defeatedMonLevel + (*lvl_cap_value * 3));
                } 
                else {
                    return (*lvl_cap_value * 2);
                }
            } 
        }
    }
    else {
        #if TESTING_NO_NEGATIVE_SCALING 
                if (defeatedMonLevel < monGainingExpLevel){
                    return monGainingExpLevel;
                }
        #endif 
    }
   
     return defeatedMonLevel;
    
}

extern "C" int THUMB_BRANCH_ScaleExpGainedByLevel(BattleMon *monGainingExp, unsigned int amountOfExpGainedSoFar, int monGainingExpLevel, int defeatedMonLevel)
{
    int v4;                      // r5
    int v6;                      // r4
    float v7;                    // r0
    unsigned int v8;             // r5
    float v9;                    // r0
    unsigned int v10;            // r4
    unsigned int ExpForLevel100; // r0
    int tempDefeatedMonLevel;
    if (!checkLevelCap(monGainingExpLevel)){
        return 0;
    }
    // k::Printf("\n\nmonGainingExperience is %d\namountofExpSoFar is %d\nlevel is %d\ndefeatedMonLevel is %d\n\n",
    //           BattleMon_GetID(monGainingExp), amountOfExpGainedSoFar, monGainingExpLevel, defeatedMonLevel);

    tempDefeatedMonLevel = scaleExpToLevelCap(amountOfExpGainedSoFar, defeatedMonLevel, monGainingExpLevel);
    v4 = 2 * tempDefeatedMonLevel + 10;
    v6 = tempDefeatedMonLevel + monGainingExpLevel + 10;
    if (2 * tempDefeatedMonLevel == -10)
    {
        v7 = (v4 << 12) - 0.5;
    }
    else
    {
        v7 = (v4 << 12) + 0.5;
    }
    v8 = (fx_sqrt(v7) * v4 * v4) >> 12;
    if (v6)
    {
        v9 = (v6 << 12) + 0.5;
    }
    else
    {
        v9 = 0 - 0.5;
    }
    v10 = div32(amountOfExpGainedSoFar * v8, ((v6 * v6 * fx_sqrt(v9)) >> 12)) + 1;
    // amountOfExpGainedSoFar * v8 / ((v6 * v6 * fx_sqrt(v9)) >> 12) + 1;
    ExpForLevel100 = GetExpForLevel100(monGainingExp);
    if (v10 > ExpForLevel100)
    {
        return ExpForLevel100;
    }
    // k::Printf("\n\nmonGainingExperience is %d\namountofExpSoFar is %d\nlevel is %d\ndefeatedMonLevel is %d\nfinalExp is %d\n\n",
            //   BattleMon_GetID(monGainingExp), amountOfExpGainedSoFar, monGainingExpLevel, defeatedMonLevel, v10);
    return v10;
}
#pragma endregion


#pragma region StaticAbilitiesChanges

unsigned __int16 MOLD_BREAKER_AFFECTED_ABILITIES[51] = {
    ABIL025_WONDER_GUARD,
    ABIL043_AMPLIFIER,
    ABIL026_LEVITATE,
    ABIL008_SAND_VEIL,
    ABIL081_SNOW_CLOAK,
    ABIL011_WATER_ABSORB,
    ABIL004_BATTLE_ARMOR,
    ABIL031_LIGHTNING_ROD,
    ABIL114_STORM_DRAIN,
    ABIL075_SHELL_ARMOR,
    ABIL109_UNAWARE,
    ABIL021_WELL_BAKED_BODY,
    ABIL086_SIMPLE,
    ABIL077_SLUSH_RUSH,
    ABIL116_SOLID_ROCK,
    ABIL111_FILTER,
    ABIL018_FLASH_FIRE,
    ABIL078_MOTOR_DRIVE,
    ABIL063_MARVEL_SCALE,
    ABIL047_THICK_FAT,
    ABIL085_HEATPROOF,
    ABIL073_STRONG_BODY,
    ABIL029_CLEAR_BODY,
    ABIL051_WIND_RIDER,
    ABIL052_HYPER_CUTTER,
    ABIL039_INNER_FOCUS,
    ABIL019_SHIELD_DUST,
    ABIL005_STURDY,
    ABIL006_BULLETPROOF,
    ABIL102_FUR_COAT,
    ABIL015_THUNDER_ARMOR,
    ABIL072_RESILIENT,
    ABIL017_FLUFFY,
    ABIL126_CONTRARY,
    ABIL132_FRIEND_GUARD,
    ABIL136_MULTISCALE,
    ABIL140_ICE_SCALES,
    ABIL147_WONDER_SKIN,
    ABIL156_MAGIC_BOUNCE,
    ABIL157_SAP_SIPPER,
    ABIL010_VOLT_ABSORB,
    ABIL087_DRY_SKIN,
    ABIL122_FLOWER_GIFT,
    ABIL134_HEAVY_METAL,
    ABIL135_LIGHT_METAL,
    ABIL143_POISON_TOUCH,
    ABIL113_SCRAPPY,
    ABIL056_GOOEY,
    ABIL009_STATIC,
    ABIL049_FLAME_BODY,
    ABIL027_EFFECT_SPORE,
};

// Overload of SearchArray (line ~21) for u16 arrays - same SEARCH_ARRAY macro picks
// whichever overload matches the array's element type.
u8 SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u16 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)
            return 1;
    }
    return 0;
}

extern "C" bool THUMB_BRANCH_SAFESTACK_HandlerMoldBreakerSkipCheck(int a1, int a2, BattleEventType a3, int a4, unsigned __int16 a5)
{
    // k::Printf("Mold Breaker Skip Check: Event %d, Move %d, EVENT_MOVE_SEQUENCE_END = %d\nis mold breaker effected ability = %d\n", a3, a5, a3 == EVENT_MOVE_SEQUENCE_END, SEARCH_ARRAY(MOLD_BREAKER_AFFECTED_ABILITIES, a5));
    return (a3 == EVENT_MOVE_SEQUENCE_END && SEARCH_ARRAY(MOLD_BREAKER_AFFECTED_ABILITIES, a5));
}
#pragma endregion 

#pragma region AbilityEventModification
extern "C" bool checkIfConsumableItem(int a1)
{
    // There is surely something we could do to simplify this
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
            a1 == IT0299_TERA_C_BAND ||
            a1 == IT0288_STICKY_BARB ||
            a1 == IT0273_FLAME_ORB ||
            a1 == IT0272_TOXIC_ORB ||
            a1 == IT0306_TERA_B_POLICY ||
            a1 == IT0256_BLUNDER_POLICY ||
            a1 == IT0305_TERA_W_POLICY ||
            a1 == IT0302_TERA_SASH ||
            a1 == IT0304_TERA_CLAW ||
            a1 == IT0217_QUICK_CLAW ||
            a1 == IT0281_BLACK_SLUDGE ||
            a1 == IT0228_TERA_GEM ||
            a1 == IT0234_LEFTOVERS ||
            a1 == IT0311_TERA_LEFTOVERS || a1 == IT0255_ATTACK_INSURANCE || a1 == IT0309_TERA_INSURANCE);
}

/* Unnerve Buff */
extern "C" bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(BattleEventItem *a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
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

extern "C" void THUMB_BRANCH_HandlerSuperFang(int a1, ServerFlow *a2, int a3)
{
    unsigned __int8 Value; // r0
    BattleMon *BattleMon;  // r0
    unsigned int v8;       // r0
    int v9;                // r1

    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
    {
        Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        BattleMon = Handler_GetBattleMon(a2, Value);
        v8 = BattleMon_GetValue(BattleMon, VALUE_CURRENT_HP);
        v9 = (v8 + (v8 >> 31)) << 15 >> 16;
        if (!v9)
        {
            v9 = 1;
        }
        if (BattleMon_GetValue(Handler_GetBattleMon(a2, a3), VALUE_EFFECTIVE_ABILITY) == ABIL093_STRONG_JAW)
        {
            v9 = v9 + (v9 >> 1);
        }
        BattleEventVar_RewriteValue(VAR_FIXED_DAMAGE, v9);
    }
}

extern "C" void THUMB_BRANCH_HandlerTruant(int a1, int a2, int a3, _DWORD *a4)
{
    if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
    {
        BattleMon *mon = Handler_GetBattleMon((ServerFlow *)a2, a3);
        if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILEDLASTTURN))
        {
            *a4 = 0;
        }

        if (*a4)
        {
            if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) && BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
            {
                a4[1] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVEFAIL_ABILITY);
            }
            *a4 = 0;
        }
        else
        {
            if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) && BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
            {
                *a4 = 1;
            }
        }
        if (BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
        {
            *a4 = 0;
        }
    }
}


void THUMB_BRANCH_HandlerUnawareDefenseRank(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) || a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

void THUMB_BRANCH_HandlerUnawareAttackRank(int a1, int a2, int a3)
{
    if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) || a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    {
        BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
    }
}

    typedef void *(*ABILITY_SETUP_FUNC)(int *);
    typedef BattleEventHandlerTableEntry* (*AbilityEventAddFunc)(u32*);
    struct	AbilityEventAddTable {AbilID ability;AbilityEventAddFunc func;};

    // BattleEvent_AddItem is already declared in definitions/codeinjection_battlefield.h
    // (with a const BattleEventHandlerTableEntry* HandlerTable param); redeclaring it here
    // with a mismatched const void* param type is a hard conflicting-declaration error.

    // Which abilities get their handler-add function loaded from a DLL, and the exact
    // export name to GetProcAddress once loaded. Generated from what abilities/*.cpp
    // actually exports (via nm on the compiled .elf) rather than hand-maintained, so
    // it can't drift out of sync with the ability files like the old overWrites[]
    // array (which had 75 entries for 67 actual files - 8 of them, including some for
    // abilities later moved to static A4/A8 hooks, no longer had a matching .dll at all).
    struct AbilityEventOverride
    {
        u8 abilID;
        const char* exportName;
    };
    const AbilityEventOverride abilityEventOverrides[] = {
        {60 , "e3c"}, // was: "THUMB_BRANCH_EventAddStickyHold"
        {106, "e6a"}, // was: "EventAddAftermathNew"
        {43 , "e2b"}, // was: "THUMB_BRANCH_EventAddSoundproof"
        {83 , "e53"}, // was: "THUMB_BRANCH_EventAddAngerPoint"
        {123, "e7b"}, // was: "THUMB_BRANCH_EventAddBadDreams"
        {6  , "e06"}, // was: "THUMB_BRANCH_EventAddDamp"
        {29 , "e1d"}, // was: "THUMB_BRANCH_EventAddClearBody"
        {76 , "e4c"}, // was: "THUMB_BRANCH_EventAddAirLock"
        {161, "ea1"}, // was: "THUMB_BRANCH_EventAddZenMode"
        {7  , "e07"}, // was: "THUMB_BRANCH_EventAddLimber"
        {128, "e80"}, // was: "EventAddDefiantNew"
        {103, "e67"}, // was: "THUMB_BRANCH_EventAddKlutz"
        {87 , "e57"}, // was: "THUMB_BRANCH_EventAddDrySkin"
        {27 , "e1b"}, // was: "EventAddEffectSporeNew"
        {138, "e8a"}, // was: "THUMB_BRANCH_EventAddFlareBoost"
        {17 , "e11"}, // was: "THUMB_BRANCH_EventAddImmunity"
        {108, "e6c"}, // was: "THUMB_BRANCH_EventAddForewarn"
        {132, "e84"}, // was: "THUMB_BRANCH_EventAddFriendGuard"
        {102, "e66"}, // was: "THUMB_BRANCH_EventAddLeafGuard"
        {12 , "e0c"}, // was: "THUMB_BRANCH_EventAddOblivious"
        {56 , "e38"}, // was: "EventAddGooey"
        {62 , "e3e"}, // was: "THUMB_BRANCH_EventAddGuts"
        {131, "e83"}, // was: "THUMB_BRANCH_EventAddHealer"
        {134, "e86"}, // was: "THUMB_BRANCH_EventAddHeavyMetal"
        {52 , "e34"}, // was: "THUMB_BRANCH_EventAddHyperCutter"
        {115, "e73"}, // was: "THUMB_BRANCH_EventAddIceBody"
        {140, "e8c"}, // was: "THUMB_BRANCH_EventAddWonderSkin"
        {151, "e97"}, // was: "THUMB_BRANCH_EventAddInfiltrator"
        {39 , "e27"}, // was: "THUMB_BRANCH_EventAddInnerFocus"
        {154, "e9a"}, // was: "THUMB_BRANCH_EventAddJustified"
        {135, "e87"}, // was: "THUMB_BRANCH_EventAddLightMetal"
        {31 , "e1f"}, // was: "THUMB_BRANCH_EventAddLightningRod"
        {63 , "e3f"}, // was: "THUMB_BRANCH_EventAddMarvelScale"
        {41 , "e29"}, // was: "THUMB_BRANCH_EventAddWaterVeil"
        {105, "e69"}, // was: "THUMB_BRANCH_EventAddSuperLuck"
        {104, "e68"}, // was: "EventAddMoldBreakerNew"
        {96 , "e60"}, // was: "THUMB_BRANCH_EventAddNormalize"
        {142, "e8e"}, // was: "THUMB_BRANCH_EventAddOvercoat"
        {124, "e7c"}, // was: "THUMB_BRANCH_EventAddPickpocket"
        {53 , "e35"}, // was: "THUMB_BRANCH_EventAddPickup"
        {40 , "e28"}, // was: "THUMB_BRANCH_EventAddMagmaArmor"
        {57 , "e39"}, // was: "THUMB_BRANCH_EventAddPlusMinus"
        {90 , "e5a"}, // was: "THUMB_BRANCH_EventAddPoisonHeal"
        {20 , "e14"}, // was: "THUMB_BRANCH_EventAddOwnTempo"
        {95 , "e5f"}, // was: "THUMB_BRANCH_EventAddQuickFeet"
        {44 , "e2c"}, // was: "THUMB_BRANCH_EventAddRainDish"
        {155, "e9b"}, // was: "THUMB_BRANCH_EventAddRattled"
        {48 , "e30"}, // was: "THUMB_BRANCH_EventAddTelepathy"
        {79 , "e4f"}, // was: "THUMB_BRANCH_EventAddRivalry"
        {16 , "e10"}, // was: "THUMB_BRANCH_EventAddColorChange"
        {159, "e9f"}, // was: "EventAddSandForceNew"
        {146, "e92"}, // was: "THUMB_BRANCH_EventAddSandRush"
        {145, "e91"}, // was: "THUMB_BRANCH_EventAddBigPecks"
        {113, "e71"}, // was: "THUMB_BRANCH_EventAddScrappy"
        {77 , "e4d"}, // was: "THUMB_BRANCH_EventAddTangledFeet"
        {119, "e77"}, // was: "THUMB_BRANCH_EventAddFrisk"
        {1  , "e01"}, // was: "EventAddStenchNew"
        {114, "e72"}, // was: "THUMB_BRANCH_EventAddStormDrain"
        {93 , "e5d"}, // was: "THUMB_BRANCH_EventAddHydration"
        {33 , "e21"}, // was: "THUMB_BRANCH_EventAddSwiftSwim"
        {47 , "e2f"}, // was: "THUMB_BRANCH_EventAddThickFat"
        {15 , "e0f"}, // was: "THUMB_BRANCH_EventAddInsomnia"
        {100, "e64"}, // was: "THUMB_BRANCH_EventAddStall"
        {137, "e89"}, // was: "THUMB_BRANCH_EventAddToxicBoost"
        {36 , "e24"}, // was: "EventAddTraceNew"
        {21 , "e15"}, // was: "THUMB_BRANCH_EventAddSuctionCups"
        {51 , "e33"}, // was: "THUMB_BRANCH_EventAddKeenEye"
    };
    const AbilityEventOverride* FindAbilityEventOverride(u8 abilID)
    {
        for (u32 i = 0; i < ARRAY_COUNT(abilityEventOverrides); ++i)
        {
            if (abilityEventOverrides[i].abilID == abilID)
                return &abilityEventOverrides[i];
        }
        return nullptr;
    }

    extern "C" u8 checkDupes(u8 ability){
        u8 abilID = ability;
        abilID = (abilID == 58) ? 57 : abilID; 
        abilID = (abilID == 73) ? 29 : abilID; 
        abilID = (abilID == 13) ? 76 : abilID; 
        abilID = (abilID == 111) ? 116 : abilID; 
        abilID = (abilID == 147) ? 140 : abilID; 
        abilID = (abilID == 163 || abilID == 164) ? 104 : abilID;
        return abilID;
    }

    
    // extern "C" void strcpy(*char result, *char string);
    // extern "C" void strcat(*char result, *char string);
    extern "C" int sprintf(char* result, const char* input, ...);
    extern "C" void BattleEvent_PopItem(BattleEventItem *a1);
    extern "C" int GetHandlerMainPriority(u32 *a1);
    extern "C" int AbilityEvent_GetSubPriority(BattleMon *a1);
    extern "C" char* produceDLLName(u8 ability){
        // static: callers (LoadDll/FreeDll) use the returned pointer immediately after the
        // call returns, so it must not point at a stack frame that no longer exists.
        static char result[20];
        sprintf(result, "abilities/%d", ability);
        //k::Printf("Produced DLL name: %s\n", result);
        return result;
    }
    extern "C" BattleEventItem * GetAbilityEvent(BattleMon * battleMon, u8 ability, AbilityEventAddFunc func) {
        u32 handlerAmount = 0;
        BattleEventHandlerTableEntry* battleHandlerItems = (BattleEventHandlerTableEntry*)func(&handlerAmount);
        // handlerAmount gets reused/overwritten by GetHandlerMainPriority below, so print
        // the real handler count here to confirm we got the right table (e.g. Thick Fat
        // should report 7, not vanilla's 1).
        //k::Printf("GetAbilityEvent: ability=%d handlerAmount=%d battleHandlerItems=%p\n", ability, handlerAmount, battleHandlerItems);

        BattleEventPriority mainPrio = (BattleEventPriority)GetHandlerMainPriority(&handlerAmount);
        u32 subPrio = AbilityEvent_GetSubPriority(battleMon);
        u32 pokemonSlot = BattleMon_GetID(battleMon);
        return BattleEvent_AddItem(EVENTITEM_ABILITY, ability, mainPrio, subPrio, pokemonSlot, battleHandlerItems, handlerAmount);
    }

    extern "C" BattleEventItem* THUMB_BRANCH_AbilityEvent_AddItem(BattleMon* battleMon) {
        u8 ability = BattleMon_GetValue(battleMon, VALUE_ABILITY);

        // Check for new or overriden abilities
        u8 abilID = checkDupes(ability);
        const AbilityEventOverride* override = FindAbilityEventOverride(abilID);
        if (override) {
            const char* dllName = produceDLLName(abilID);
            b32 loaded = LoadDll(dllName);
            //k::Printf("THUMB_BRANCH_AbilityEvent_AddItem: ability=%d abilID=%d LoadDll returned %d\n", ability, abilID, loaded);
            if (loaded) {
                k::dll::LibraryHandle handle = GetLoadedDllHandle(dllName);
                void* funcAddr = handle ? k::dll::GetProcAddress(handle, override->exportName) : nullptr;
                //k::Printf("THUMB_BRANCH_AbilityEvent_AddItem: GetProcAddress(%s) = %p\n", override->exportName, funcAddr);
                if (funcAddr) {
                    return GetAbilityEvent(battleMon, ability, (AbilityEventAddFunc)funcAddr);
                }
            }
            // Loading or lookup failed - fall through to the vanilla table below
            // rather than silently doing nothing for this Pokemon's ability.
        }
        // Check for vanilla abilities
        AbilityEventAddTable* abilityEventAddTable = (AbilityEventAddTable*)0x21D7F38;
        for (u32 abilityEvent = 0; abilityEvent < 158; ++abilityEvent) {

            AbilityEventAddTable* abilityAddEvent = &abilityEventAddTable[abilityEvent];
            if (ability == abilityAddEvent->ability) {
                return GetAbilityEvent(battleMon, ability, abilityAddEvent->func);
            }
        }
        return 0;
    }


    extern "C" void THUMB_BRANCH_LINK_BattleEventItem_Remove_0x44(BattleEventItem * item) {
        // BattleEventItem's factorType/subID fields read wrong through the struct: the
        // vanilla ROM (per IDA disasm) lays out eventItemType as a 4-byte field at 0x10
        // ("DCD"), but BattleEventItemType has no explicit underlying type, so this
        // compiler collapses it to a 1-byte enum (confirmed via static_assert against
        // this exact toolchain: sizeof(BattleEventItemType) == 1 here). That shifts
        // factorType to offset 0xD instead of 0x10, and every field after it (priority,
        // flags, work[], subID, dependID, pokeID) 4 bytes earlier than the real vanilla
        // layout - so item->factorType/item->subID were reading garbage. Bypass the
        // struct here and read the known-correct vanilla byte offsets directly instead
        // of risking a project-wide struct layout change other code may depend on.
        u8* raw = (u8*)item;
        u32 factorType = *(u32*)(raw + 0x10);
        u16 subID = *(u16*)(raw + 0x38);

        // Unconditional - fires for every removed item regardless of factorType, so we
        // can tell "hook never triggers" apart from "triggers, but never with
        // factorType==EVENTITEM_ABILITY (0x4) because no ability item got removed yet".
        //k::Printf("THUMB_BRANCH_LINK_BattleEventItem_Remove_0x44: item=%p factorType=%d subID=%d\n", item, factorType, subID);
        switch (factorType)
        {
            case 0x4:
            {
                u8 abilID = checkDupes((u8)subID);
                if (FindAbilityEventOverride(abilID)){
                    const char* dllName = produceDLLName(abilID);
                    //k::Printf("THUMB_BRANCH_LINK_BattleEventItem_Remove_0x44: freeing abilID=%d dllName=%s\n", abilID, dllName);
                    FreeDll(dllName);
                }
                break;
            }
            default:
                break;
            }
        BattleEvent_PopItem(item);
    }


#pragma endregion

