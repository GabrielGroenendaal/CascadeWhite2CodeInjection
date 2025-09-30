
#include "structs_new.h"
// #include "../swan-master/system/game_data.h"

unsigned short int &HIWORD(unsigned int &x)
{
    return *(reinterpret_cast<unsigned short int *>(&x) + 1);
}

unsigned short int &LOWORD(unsigned int &x)
{
    return *(reinterpret_cast<unsigned short int *>(&x) + 0);
}

bool IsEqual(int a1, int a2)
{
    char *c1 = (char *)&a1;
    char *c2 = (char *)&a2;

    for (u16 i = 0; i < 4; ++i)
    {
        if (c1[i] != c2[i])
            return false;
    }
    return true;
}

// u16& HIWORD(u32& x)
// {
//     return *(reinterpret_cast<u16*>(&x) + 1);
// }

// u16& LOWORD(u32& x)
// {
//     return *(reinterpret_cast<u16*>(&x) + 0);
// }

C_DECL_BEGIN

// STUFF FOR FIELD EFFECTS
extern bool BattleMon_IsStatChangeValid(BattleMon *a1, unsigned int a2, int a3);
extern bool Handler_IsSimulationMode(ServerFlow *a1);
extern PlayerState *GameData_GetPlayerState(GameData *gameData);
extern BtlSetup *MainModule_GetBtlSetup(MainModule *a1);
extern int PlayerState_GetZoneID(PlayerState *a1);
extern int BattleEventVar_GetValue(BattleEventVar a1);
extern void HandlerDig(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerDive(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerBounce(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerFly(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerShadowForce(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerShadowForceEnd(int a1, ServerFlow *a2, unsigned int *a3);
extern int HandlerPursuitStart(int a1, ServerFlow *a2, unsigned int a3, int a4);
extern int HandlerFeintBreakProtect(int a1, int a2, int a3);
extern int HandlerFeintResetProtectCounter(int a1, ServerFlow *a2, unsigned int a3, char *a4);
extern BattleFieldStatus *BtlSetup_GetFieldStatus(MainModule *a1);
extern int ServerControl_ChangeWeather(ServerFlow *a1, unsigned int a2, int a3);
extern int ServerControl_ChangeWeatherCore(ServerFlow *a1, int a2, int a3);
extern int ServerControl_FieldEffectCore(ServerFlow *a1, int a2, ConditionData a3, int a4);
extern bool Handler_IsTargetInRange(ServerFlow *a1, int a2, int a3, int a4);
extern int Handler_AddSwitchOutInterrupt(int result, char a2);
extern BattleMon *BattleParty_GetPartyMember(BattleParty *a1, unsigned int a2);
extern SVCL_WORK *BattleServer_GetClientWork(BtlServerWk *a1, int a2);
extern int ServerControl_AfterSwitchIn(ServerFlow *a1);
extern int Handler_GetThisTurnAction(ServerFlow *a1, int a2, _DWORD *a3);
extern int BattleMon_GetHeldItem(BattleMon *a1);
extern int BtlSetup_GetBattleStyle(MainModule *a1);
extern int ServerControl_SwitchInCore(ServerFlow *a1, int a2, unsigned int a3, int a4);
extern bool BattleMon_IsFainted(BattleMon *a1);
extern bool Handler_CheckItemUsable(ServerFlow *a1, int a2);
extern int Handler_CheckReservedMemberChangeAction(ServerFlow *a1);
extern void MainModule_RegisterPokedexSeenFlag(MainModule *a1, int a2, int a3);
extern ServerFlow *BattleServer_GetServerFlow(BtlServerWk *a1);
extern int HandlerClearBodyCheck(int a1, int a2, int a3, int *a4);
extern bool Handler_GetFightEnableBenchPokeNum(ServerFlow *a1, unsigned int a2);
extern int BattleEventVar_Push();
extern int BattleEventVar_Pop();
extern int HandlerCommon_MultiplyBasePower(int a1);
extern int *ActionOrder_SearchByMonID(ServerFlow *a1, int a2);
extern int HandlerClearBodyGuard(int a1, ServerFlow *a2, int a3, int *a4);
extern bool BattleMon_IsFullHP(BattleMon *a1);
extern int BattleHandler_AddArg(HandlerParam_StrParams *result, int a2);
extern void BattleHandler_StrSetup(HandlerParam_StrParams *result, unsigned __int8 a2, __int16 a3);
extern HandlerParam_Header *BattleHandler_PushWork(ServerFlow *a1, BattleHandlerEffect a2, int a3);
extern void BattleHandler_PopWork(ServerFlow *a1, void *a2);
extern void BattleHandler_PushRun(ServerFlow *a1, BattleHandlerEffect a2, int a3);
extern int BattleMon_GetValue(BattleMon *a1, BattleMonValue a2);
extern int BattleMon_GetID(BattleMon *a1);
extern unsigned int BattleEventVar_SetConstValue(BattleEventVar a1, int a2);
extern int j_j_FaintRecord_GetCount(FaintRecord *a1, unsigned int turn);
extern int FaintRecord_GetPokeID(FaintRecord *a1, unsigned int a2, unsigned int a3);
extern int j_j_DeadRec_GetCount(FaintRecord *a1, unsigned int a2);
extern int j_j_FaintRecord_GetPokeID(FaintRecord *a1, unsigned int a2, unsigned int a3);
extern unsigned int BattleEventVar_SetValue(BattleEventVar a1, int a2);
extern unsigned int BattleEventVar_SetMulValue(BattleEventVar a1, int a2, int a3, int a4);
extern int BattleEvent_CallHandlers(ServerFlow *a1, BattleEventType a2);
extern int GetTypeEffectivenessMultiplier(int a1, int a2);
extern int fixed_round(int a1, int a2);
extern int Handler_PokeIDToPokePos(ServerFlow *a1, unsigned int a2);
extern int Handler_ExpandPokeID(ServerFlow *a1, __int16 a2, u8 *a3);
extern MoveCondition BattleMon_GetStatus(BattleMon *a1);
extern bool BattleMon_HasType(BattleMon *a1, Types a2);
extern bool BattleMon_GetConditionFlag(BattleMon *a1, ConditionFlag a2);
extern ZoneSpawnInfo *GameData_GetEntraLinkParentSpawnInfo(GameData *a1);
// extern PlayerState *GameData_GetPlayerState(GameData *a1);
extern int HandlerGetMainModule(int a1);
extern bool MainModule_IsAllyMonID(unsigned int a1, unsigned int a2);
extern unsigned int DivideMaxHPZeroCheck(BattleMon *a1, unsigned int a2);
extern int PML_ItemIsBerry(u16 itemId);
extern void HandlerUturn(BattleEventItem *a1, ServerFlow *a2, unsigned int a3);
extern int Handler_GetTurnCounter(ServerFlow *a1);
extern int g_ZoneDataSystem;
extern void HandlerToxicOrbUseTemp(int a1, ServerFlow *a2, u8 a3);
extern void HandlerFlameOrbUseTemp(int a1, ServerFlow *a2, u8 a3);
extern ConditionData Condition_MakePermanent();
extern ConditionData BattleMon_GetMoveCondition(BattleMon *a1, MoveCondition a2);
extern int CheckIfMonToSwitchToWithSEMove(BtlClientWk *a1, BattleMon *a2, int Effectiveness);
extern int Condition_GetParam(ConditionData a1);
extern unsigned int RandomInRange(unsigned int a1, unsigned int a2);
extern void HandlerFlameOrb(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerToxicOrb(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerSmokeBallMessage(BattleEventItem *a1, ServerFlow *a2, unsigned int a3);
extern int HandlerSmokeBall(int a1, int a2, unsigned int a3);
extern bool PokeTypePair_IsMonotype(int a1);
extern ConditionData Condition_MakeBadlyPoisoned();
extern bool GetSideFromOpposingMonID(unsigned int a1);
extern void CommonCreateSideEffect(
    int a1,
    ServerFlow *a2,
    unsigned int a3,
    int a4,
    unsigned __int8 a5,
    int a6,
    int a7,
    __int16 a8);
extern unsigned int BattleEventVar_SetRewriteOnceValue(BattleEventVar a1, int a2);

extern int HandlerCommonGuardStatus(int a1, int a2, MoveCondition a3);
extern int BattleMon_GetRealStat(BattleMon *a1, BattleMonValue a2);
extern int BattleMon_GetStatsForCritDamage(BattleMon *a1, int a2);
extern int Handler_GetBattleTerrain(ServerFlow *a1);
extern int Handler_GetPrevUsedMove(ServerFlow *a1);
extern int ServerEvent_GetWeather(ServerFlow *a1);
extern int j_j_IsNotAllowedCopycatMove(int a1);
extern u32 PML_MoveGetCategory(int a1);
extern int j_j_IsSleepTalkUncallableMove(int a1);
extern int BattleRandom(unsigned int a1);
extern int Handler_ReqMoveTargetAuto(ServerFlow *a1, int a2, int a3);
extern void PokeParty_SetParam(PartyPkm *a1, PkmField a2, u32 a3);
extern u32 PokeParty_GetParam(PartyPkm *a1, PkmField a2, void *extra);
extern bool AbilityEvent_RollEffectChance(int a1, unsigned int a2);
extern int PML_ItemGetParam(ItemData *a1, ItemField a2);
extern void *ServerDisplay_AddCommon(ServerCommandQueue *a1, int a2, ...);
extern int BattleEventVar_RewriteValue(BattleEventVar a1, int a2);
extern bool getMoveFlag(int a1, MoveFlag a2);
extern int HandlerOvercoat(int a1, int a2, int a3);
extern void HandlerFriendGuard(int a1, int a2, unsigned int a3);
extern void HandlerTelepathy(int a1, ServerFlow *a2, unsigned int a3);
extern int Handler_GetWeather(int a1);
extern void HandlerPlusMinus(int a1, ServerFlow *a2, unsigned int a3, u8 *a4, int a5, int a6, int a7, int a8);
extern int HandlerHealer(int a1, ServerFlow *a2, unsigned int a3, int a4);
extern void BattleEventVar_MulValue(BattleEventVar a1, int a2);
extern int CommonResistBerry(int a1, ServerFlow *a2, int a3, _DWORD *a4, unsigned __int8 a5, int a6);
extern void HandlerCommonResistBerryDamageAfter(BattleEventItem *a1, ServerFlow *a2, int a3, unsigned int **a4);
extern int HandlerGemEnd(int a1, int a2, int a3, int *a4);
extern void CommonGemDecide(int r0_0, ServerFlow *a2, int a3, _DWORD *a4, unsigned __int8 a5);
extern void CommonGemPower(int a1, ServerFlow *a2, int a3, _DWORD *a4, unsigned __int8 a5);
extern void CommonTypeBoostingItem(BattleEventItem *a1, int a2, int a3, int a4);
extern void ItemEvent_PushRun(BattleEventItem *a1, ServerFlow *a2, int a3);
extern int BattleEventItem_GetSubID(BattleEventItem *a1);
extern int HandlerCommon_CheckTargetMonID(int a1);
extern void HandlerMarvelScale(int a1, ServerFlow *a2, int a3);
extern ConditionData Condition_MakePermanentParam(int a1);
extern BattleMon *BattleParty_GetMonData(BattleParty *a1, unsigned int a2);
extern int BattleMon_GetMoveCount(BattleMon *a1);
extern int HandlerRainDish(int a1, ServerFlow *a2, int a3);
extern int BattleMon_GetPokeType(BattleMon *a1);
extern u8 PML_MoveGetType(int a1);
extern int Move_GetID(BattleMon *a1, int a2);
extern int HandlerChipAwayHitCheck(int a1, int a2, int a3);
extern int HandlerChipAwayCalcDamage(int a1, int a2, int a3);
extern BattleParty *BattleClient_GetActParty(BtlClientWk *a1);
extern int Move_GetPP(BattleMon *a1, unsigned int a2);
extern u16 PML_MoveGetBasePower(int id);
extern int HandlerWaterVeil(int a1, int a2, int a3, int *a4);
extern void HandlerWaterVeilCureStatus(int a1, ServerFlow *a2, unsigned int *a3);
extern bool PML_MoveIsDamaging(int id);
extern int HandlerKeenEyeGuard(int a1, ServerFlow *a2, int a3, int *a4);
extern int HandlerKeenEyeCheck(int a1, int a2, int a3, int *a4);
extern u8 PML_MoveGetType(int a1);
extern void HandlerWaterVeilActionEnd(int a1, ServerFlow *a2, int a3);
extern TypeEffectiveness GetTypeEffectiveness(int a1, int a2);
extern int GetTypeEffectivenessVsMon(int a1, int a2);
extern BattleMon *GetBattleMonFromBattlePos(TrainerAIEnv *a1, int a2);
extern int PokeTypePair_GetType1(int a1);
extern int PokeTypePair_GetType2(int a1);
extern BattleMon *PokeCon_GetPokeParam(PokeCon *a1, int a2);
extern int BattleMon_GetSpecies(BattleMon *a1);
extern unsigned int BattleMon_IsIllusionEnabled(BattleMon *a1);
extern BattleMon *MainModule_GetIllusionDisguise(MainModule *a1, int a2, int a3);
extern bool BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2);
extern int Handler_CalculateSpeed(ServerFlow *a1, BattleMon *a2, int a3);
extern int Handler_SimulationEffectivenessCore(ServerFlow *a1, int a2, int a3, int a4);
extern int PML_MoveGetParam(int a1, MoveField a2);
extern int ServerEvent_CalcDamage(
    ServerFlow *a1,
    BattleMon *AttackingMon,
    BattleMon *DefendingMon,
    MoveParam *MoveParam,
    int TypeEffectiveness,
    int targetDmgRatio,
    int criticalFlag,
    int BattleDebugMode,
    _WORD *destDamage);
extern void ServerEvent_GetMoveParam(ServerFlow *a1, int a2, int a3, MoveParam *a4);
extern int HandlerSnowCloakWeather(int a1, int a2, int a3, int a4);
extern void HandlerThickFat(int a1, int a2, int a3);
extern void HandlerGuts(int a1, ServerFlow *a2, int a3);
extern void HandlerFlareBoost(int a1, ServerFlow *a2, int a3);
extern int HandlerQuickFeet(int a1, ServerFlow *a2, int a3);
extern void HandlerToxicBoost(int a1, ServerFlow *a2, int a3);
extern void HandlerPoisonHeal(int a1, ServerFlow *a2, unsigned int *a3);
extern int HandlerAddStatusFailedCommon(int a1, ServerFlow *a2, int a3, int *a4);
extern bool GetSideFromMonID(unsigned int a1);
extern int BattleField_GetWeather();
extern void *PML_ItemReadDataFile(unsigned int a1, int a2, HeapID a3);
extern void HandlerLightBallUseTemp(int a1, ServerFlow *a2, unsigned int *a3);
extern ConditionData MakeBasicStatus(MoveCondition a1);
// extern int PokeList_GetEVsAppliedAfterLimit(int a1, int a2, int a3, int a4);
// extern void ApplyHeal(PartyPkm *a1, int a2, unsigned int a3, int a4);
// extern int CheckPPGain(PartyPkm *a1, int a2, int a3);
// extern int PokeParty_AddPP(PartyPkm *pkm, int moveIdx, int addend);
// extern u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);
// extern void PokeParty_RecalcStats(PartyPkm *a1);
// extern int PokeList_ApplyFriendship(PartyPkm *a1, int a2, int a3, u16 a4, unsigned __int16 a5, HeapID a6);
// extern int BattleMon_GetHPRatio(BattleMon *a1);

// New Effects
extern void ServerControl_CheckMoveExeSleepCure(ServerFlow *a1, BattleMon *a2);
extern int ServerEvent_MoveExecuteFail(ServerFlow *a1, BattleMon *a2, int a3, int a4);
extern int ServerControl_CheckMoveExeFreezeThaw(ServerFlow *a1, BattleMon *a2, int a3);
extern int Move_SearchIndex(BattleMon *a1, int a2);
extern int ServerEvent_CheckMoveExecute(ServerFlow *a1, BattleMon *a2, int a3, BattleEventType a4);
extern bool BattleMon_GetTurnFlag(BattleMon *a1, TurnFlag a2);
extern int BattleField_CheckImprison(PokeCon *a1, BattleMon *a2, int a3);
extern u32 BattleField_CheckEffect(BattleFieldEffect a1);
extern int BattleMon_GetPreviousMoveID(BattleMon *a1);
extern int BattleMon_GetPreviousMove(BattleMon *a1);
extern bool ServerControl_CheckConfusionHit(ServerFlow *a1, BattleMon *a2);
extern bool ServerControl_CheckAttract(ServerFlow *a1, BattleMon *a2);
extern void ServerControl_MoveExecuteFail(ServerFlow *a1, BattleMon *a2, int a3, MoveFailCause a4);
extern char *ServerDisplay_MoveExecuteFailMessage(ServerFlow *a1, int a2, int a3, unsigned int a4);
extern void ServerDisplay_AddEffectAtPosition(ServerFlow *a1, BattleMon *a2, int a3);
extern void ServerDisplay_CureStatus(ServerFlow *a1, BattleMon *a2, int a3, char *a4);
extern void ServerDisplay_AddMessageImpl(ServerCommandQueue *a1, int a2, __int16 a3, ...);
extern bool RollEffectChance(unsigned int a1);
extern int HandlerDrySkinCheck(int a1, ServerFlow *a2, int a3);
extern void HandlerDrySkinWeather(int a1, ServerFlow *a2, int a3);
extern int BattleMon_GetUsedItem(BattleMon *a1);
extern int BattleMon_GetHPRatio(BattleMon *a1);
extern int BattleEventItem_GetPokeID(BattleEventItem *a1);

// Old ESDB
extern int j_j_BTL_SICKEVENT_CheckNotEffectByType(ServerFlow *a1, BattleMon *a2);
extern int HandlerCommon_CheckTargetPokeID(int a1);
extern BattleMon *Handler_GetPokeParam(ServerFlow *a1, int a2);
extern FaintRecord *Handler_GetActionRecord(ServerFlow *a1);
// extern BattleMon *PokeCon_GetPokeParam(PokeCon *a1, int a2);

// New ESDB
extern int j_j_Condition_CheckUnaffectedByType(ServerFlow *a1, BattleMon *a2);
extern int HandlerCommon_CheckTargetMonID(int a1);
extern BattleMon *Handler_GetBattleMon(ServerFlow *a1, int a2);
extern MainModule *BtlvEffectMain_GetMainModule();
extern FaintRecord *Handler_GetFaintRecord(ServerFlow *a1);
// extern BattleMon *PokeCon_GetBattleMon(PokeCon *a1, int a2);
extern bool Handler_CheckFloating(ServerFlow *a1, int a2);
extern bool ServerControl_CheckFloating(ServerFlow *a1, BattleMon *a2, int a3);

extern void HandlerMagmaArmorActionEnd(int a1, ServerFlow *a2, int a3);
extern void HandlerMagmaArmorCureStatus(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerMagmaArmorStatus(int a1, int a2, int a3, int *a4);
extern int HandlerSandVeilWeather(int a1, int a2, int a3, int a4);
extern void HandlerSandForce(int a1, int a2, int a3);
extern void HandlerSandRush(int a1, int a2, int a3);
extern void HandlerSwiftSwim(int a1, int a2, int a3);
// extern int g_GameBeaconSys;
extern int Handler_GetExistFrontPokePos(ServerFlow *a1, int a2);
extern u8 *Handler_GetTempWork(ServerFlow *a1);
extern bool PokeTypePair_HasSharedType(int a1, int a2);
extern void HandlerSolarBeamCharge(int a1, ServerFlow *a2, unsigned int *a3);
extern int ServerDisplay_MoveAnimation(ServerFlow *a1, int a2, MoveAnimCtrl *a3, unsigned __int16 a4);

// BindFix
extern bool j_j_BattleMon_IsFainted_7(BattleMon *a1);
extern ConditionData j_j_GetConditionContinuationParam_1(BattleMon *a1, MoveCondition a2);
extern int j_j_Condition_GetParam_1(ConditionData a1);
extern HandlerParam_Header *j_j_BattleHandler_PushWork_21(ServerFlow *a1, BattleHandlerEffect a2, int a3);
extern bool j_j_Condition_GetFlag(ConditionData a1);
extern unsigned int j_j_DivideMaxHPZeroCheck_5(BattleMon *a1, unsigned int a2);
extern int j_j_Handler_PokeIDToPokePos_3(ServerFlow *a1, unsigned int a2);
extern void j_j_BattleHandler_StrSetup_14(_WORD *result, unsigned __int8 a2, __int16 a3);
extern void j_j_BattleHandler_AddArg_16(HandlerParam_StrParams *result, int a2);
extern void j_j_BattleHandler_AddArg_17(HandlerParam_StrParams *result, int a2);
extern void j_j_BattleHandler_PopWork_21(ServerFlow *a1, void *a2);

// Legendary Pokemon Fights
extern void PokeParty_InitCore(PokeParty *party, int capacity);
extern void *GFL_HeapAllocate(HeapID heapId, u32 size, b32 calloc, const char *sourceFile, u16 lineNo);
extern void TrainerData_ReadTrainerData(u16 trId, TrainerData *dest);
extern void TrainerData_ReadParty(u16 trId, void *dest);
extern int TrainerClass_GetSex(u32 trClass);
extern u32 PokeParty_GetPkmRawSize();
extern void TrainerUtil_CalcBasePID(u16 species, u16 form, u8 abilAndSex, u32 *dest, HeapID heapId);
extern void GFL_HeapFree(void *heap);
extern void PokeParty_SetMove(PartyPkm *pPkm, MoveID moveIdx, u8 moveSlot);
extern void TrainerUtil_SetupPkm(u16 trId, PartyPkm *pkm, u16 forme, u8 genderAndAbil);
extern bool PokeParty_AddPkm(PokeParty *party, PartyPkm *pPkm);
extern void PokeParty_CreatePkm(
    PartyPkm *pkm,
    MonsNo species,
    u8 level,
    u32 tidSet,
    int abil,
    u32 ivs,
    u32 pid,
    u32 abil_mask);
extern void PML_PkmSetParam(BoxPkm *pPkm, PkmField field, u32 data);
extern BattleMon *PokeCon_GetClientMonData(PokeCon *a1, int a2, unsigned int a3);
extern bool IsOpponentClientID(MainModule *a1, char a2, char a3);
extern bool TrainerParam_HasTrainerInfo(MainModule *a1, int a2);
extern void Btlv_StringParam_Setup(Btlv_StringParam *a1, char a2, __int16 a3);
extern void Btlv_StringParam_AddArg(Btlv_StringParam *a1, int a2);
extern void sub_21D022C(BtlvCore *a1, Btlv_StringParam *a2);
extern int GetMemberPutStrID(BtlClientWk *a1);
extern int BattleViewCmd_WaitMessage(BtlvCore *a1);
extern unsigned int MainModule_GetClientPokePos(MainModule *a1, int a2, int a3);
extern void sub_21D0088(BtlvCore *a1, int a2, char a3, char a4);
extern int sub_21D00C4(BtlvCore *a1);
extern void sub_21B1F24(BtlClientWk *a1);
extern int GetPlayerClientID(MainModule *a1);
extern void sub_21B9730(BtlClientWk *a1, char *a2, BattleParty *a3);
// extern int GetSwitchOutStrID(BtlClientWk *a1, int a2, int *a3);
extern int MainModule_GetCommMode(MainModule *a1);
extern unsigned int sub_21B1F40(BtlClientWk *a1);
extern int ServerControl_FaintPokemon(ServerFlow *a1, BattleMon *a2);
extern int BattleHandler_SetString(ServerFlow *a1, HandlerParam_StrParams *a2);
extern bool j_j_PosPoke_IsExist_7(PosPoke *a1, int a2);
extern void IncrementProtectCounter(ServerFlow *a1, int a2, int a3);
extern void j_PokeSet_SeekStart_10(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_18(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_19(PokeSet *a1);
extern int ServerControl_IsGuaranteedHit(ServerFlow *a1, BattleMon *a2, BattleMon *a3);
extern int ServerControl_CheckNoEffectCore(
    ServerFlow *a1,
    unsigned __int16 *a2,
    int a3,
    BattleMon *a4,
    int a5,
    int a6);
extern void j_PokeSet_Remove_0(PokeSet *a1, BattleMon *a2);
extern void j_PokeSet_Remove_8(PokeSet *a1, BattleMon *a2);
extern void j_PokeSet_Remove_10(PokeSet *a1, BattleMon *a2);
extern void j_PokeSet_SeekStart_11(PokeSet *a1);
extern void j_PokeSet_SeekStart_20(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_20(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_21(PokeSet *a1);
extern void j_PokeSet_Remove_1(PokeSet *a1, BattleMon *a2);
extern void j_PokeSet_Remove_2(PokeSet *a1, BattleMon *a2);
extern void j_PokeSet_Remove_3(PokeSet *a1, BattleMon *a2);
extern void j_j_PokeSet_Remove_9(PokeSet *a1, BattleMon *a2);
extern void j_PokeSet_SeekStart_12(PokeSet *a1);
extern void j_PokeSet_SeekStart_13(PokeSet *a1);
extern void j_j_PokeSet_SeekStart_7(PokeSet *a1);
extern void j_j_PokeSet_SeekStart_19(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_22(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_23(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_24(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_25(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_28(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_29(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_40(PokeSet *a1);
extern BattleMon *j_PokeSet_SeekNext_41(PokeSet *a1);
extern BattleMon *j_j_PokeSet_SeekNext_38(PokeSet *a1);
extern BattleMon *j_j_PokeSet_SeekNext_39(PokeSet *a1);
extern BattleMon *j_PokeSet_Get_8(PokeSet *a1, unsigned int a2);
extern int ServerEvent_SkipAvoidCheck(ServerFlow *a1, BattleMon *a2, BattleMon *a3, unsigned __int16 *a4);
extern bool ServerEvent_CheckHit(ServerFlow *a1, BattleMon *a2, BattleMon *a3, unsigned __int16 *a4);
extern int j_PokeSet_GetCountMax_4(PokeSet *a1);
extern int ServerEvent_CheckProtectBreak(ServerFlow *a1, BattleMon *a2);
extern int HandlerProtectCheckFail(int a1, ServerFlow *a2, int a3);
extern void HandlerProtectStart(int a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerProtectResetCounter(BattleEventItem *a1, ServerFlow *a2, int a3);
extern void HandlerProtect(int a1, ServerFlow *a2, unsigned int *a3);
extern void j_FaintRecord_Add(FaintRecord *result, char a2);
extern int BtlSetup_IsBattleType(MainModule *a1, BtlSetupFlag mask);
extern unsigned int j_MainModule_PokeIDToClientID(unsigned int a1);
extern int ServerControl_ClearMonDependentEffects(ServerFlow *a1, BattleMon *a2, int a3);
extern void BattleMon_ClearForFainted(BattleMon *a1);
extern unsigned int GetEnemyMaxLevel(ServerFlow *a1);
extern void ChangeFriendshipWhenFainted(MainModule *a1, BattleMon *a2, int a3);
extern bool MainModule_IsAllyClientID(int a1, int a2);
extern int RecordData_Increment(MainModule *a1, int a2);
extern int j_PosPoke_SwitchOut_0(int a1, int a2);
extern void PosPoke_SwitchOut(PosPoke *a1, int a2);
extern void j_PosPoke_SwitchOut(PosPoke *a1, int a2);
extern void j_j_PosPoke_SwitchOut(PosPoke *a1, int a2);
extern int MainModule_PokeIDToClientID(int a1);
extern void FaintRecord_Add(FaintRecord *result, char a2);

extern void CommonTypeNoEffectRankUp(ServerFlow *a1, int a2, unsigned int a3, int a4);
extern int CommonDamageRecoverCheck(ServerFlow *a1, int a2, int a3);
extern void HandlerSoundproof(int a1, ServerFlow *a2, unsigned int *a3);
extern int MoveEvent_AddItem(BattleMon *a1, int a2, int a3);
extern void MoveEvent_ForceRemoveItemFromBattleMon(BattleMon *a1, int a2);
extern BattleActionType BattleAction_GetAction(BattleActionParam *a1);
extern EventWorkSave *GameData_GetEventWork(void *gameData);
extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);

extern void ServerDisplay_AbilityPopupAdd(ServerFlow *a1, BattleMon *a2);
extern bool j_j_PosPoke_IsExist_3(PosPoke *a1, int a2);
extern bool j_j_PosPoke_IsExist_4(PosPoke *a1, int a2);
extern int ServerControl_StatStageChangeCore(
    ServerFlow *a1,
    int a2,
    BattleMon *a3,
    unsigned int a4,
    int a5,
    unsigned __int8 a6,
    unsigned __int16 a7,
    int a8,
    int a9,
    int a10);

extern void ServerDisplay_AbilityPopupRemove(ServerFlow *a1, BattleMon *a2);
extern int HandlerScrappy(int a1, int a2, int a3);
extern void HandlerRattled(int a1, ServerFlow *a2, int a3);
extern void CommonStatDropGuardMessage(ServerFlow *a1, int a2, int *a3, __int16 a4);
extern void HandlerInnerFocus(int a1, ServerFlow *a2, int a3);
extern void sys_memset(const void *ptr, u8 value, size_t size);
extern void MoveDamageRec_ClearTurn(BattleMon *a1);
extern void TurnFlag_Set(BattleMon *a1, TurnFlag a2);
extern unsigned int HEManager_PushState(int *a1);
extern void ServerEvent_MoveUseEnd_Common(ServerFlow *a1, int a2, int a3, BattleEventType a4);
extern void HEManager_PopState(int *result, int a2);
extern bool PosPoke_IsExist(PosPoke *a1, int a2);
extern void Handler_SetMoveEffectIndex(ServerFlow *a1, char a2);
extern bool CanMonUseHeldItem(BtlClientWk *a1, BattleMon *a2);
extern int Move_IsUsable(BattleMon *a1, int a2);
extern u32 BattleField_CheckFieldEffectCore(BattleField *a1, BattleFieldEffect a2);
extern int BattleField_CheckImprisonCore(BattleField *a1, PokeCon *a2, BattleMon *a3, int a4);
extern int BattleMon_GetConditionAffectedMove(BattleMon *a1, MoveCondition a2);

extern void HandlerKnockOff(int a1, ServerFlow *r1_0, unsigned int a3);
extern bool HandlerCommon_CheckIfCanStealPokeItem(ServerFlow *a1, unsigned int a2, int a3);
extern void HandlerNormalize(int a1, int a2, int a3);
extern void HandlerGrudgeReducePP(BattleEventItem *a1, ServerFlow *r1_0, int a3);
extern void HandlerDestinyBondStart(BattleEventItem *a1, int a2, int a3);
extern int Handler_CheckEvolution(ServerFlow *a1, int a2);
extern int HandlerLeechSeed(int a1, ServerFlow *a2, int a3);
extern void HandlerJustified(int a1, ServerFlow *a2, unsigned int *a3);
extern int ServerEvent_CheckHiding(ServerFlow *a1, BattleMon *a2, BattleMon *a3);
extern void ServerDisplay_MoveAvoid(ServerFlow *a1, BattleMon *a2);
extern int ServerEvent_CheckMoveDamageEffectiveness(
    ServerFlow *a1,
    BattleMon *a2,
    BattleMon *a3,
    MoveParam *a4,
    int a5);
extern void EffectivenessRecorder_Add(EffectivenessRecorder *result, int PokeID, int a3);
extern void EffectivenessCounter_CountUp(
    EffectivenessCounter *a1,
    ServerFlow *a2,
    BattleMon *attacker,
    BattleMon *defender,
    int effectiveness);
extern void EffectivenessRecorder_Init(EffectivenessRecorder *result);
extern int MainModule_GetPlayerClientID(MainModule *a1);

// AI STUFF
extern u32 AIGetMoveParam(TrainerAIEnv *a1, int a2, MoveField a3);
extern u32 VM_Read32(void *vm);
extern int Handler_SimulationDamage(ServerFlow *a1, int a2, int a3, int a4, bool a5, bool a6);
extern int AIConditionalJump(void *a1, unsigned int condition, int param1, int param2);

// SHADOW TAG
extern bool PokeTypePair_HasType(int a1, Types a2);

// TRACE
extern BattleStyle Handler_GetBattleStyle(ServerFlow *a1);
extern int IsPosInRangeTripleBattle(int a1, int a2);
extern int j_j_IsTraceFailAbility_0(int a1);
extern int j_j_IsTraceFailAbility(int a1);
extern int sub_219C508(unsigned int a1, int a2);
extern int Handler_PokePosToPokeID(ServerFlow *a1, int a2);

// FUTURE SIGHT
extern void j_j_PokeSet_Clear_12(const void *a1);
extern void j_j_PokeSet_Clear_13(const void *a1);
extern void j_j_PokeSet_Add_18(PokeSet *a1, BattleMon *a2);
extern void j_j_PokeSet_SetDefaultTargetCount_0(PokeSet *a1, char a2);
extern void j_j_PokeSet_RemoveDisablePoke_1(PokeSet *a1);
extern bool j_j_PokeSet_IsRemovedAll_0(PokeSet *a1);
extern bool j_j_PokeSet_IsRemovedAll_4(PokeSet *a1);
extern void ServerDisplay_MoveFail(ServerFlow *a1);
extern void flowsub_CheckPokeHideAvoid(ServerFlow *a1, __int16 *a2, BattleMon *a3, PokeSet *a4);
extern void flowsub_CheckNoEffect_TypeAffinity(
    ServerFlow *a1,
    MoveParam *a2,
    BattleMon *attacker,
    PokeSet *targets,
    int *effrec);
extern void flowsub_CheckNoEffect_Protect(ServerFlow *a1, __int16 *a2, BattleMon *a3, PokeSet *a4, int *a5);
extern void flowsub_CheckWazaAvoid(ServerFlow *a1, __int16 *a2, BattleMon *a3, PokeSet *a4);
extern void MoveAnimCtrl_Init(MoveAnimCtrl *result);
extern void MoveAnimCtrl_Setup(MoveAnimCtrl *a1, ServerFlow *a2, BattleMon *a3, PokeSet *a4);
extern int ServerControl_DamageRoot(ServerFlow *a1, MoveParam *a2, BattleMon *a3, PokeSet *a4, int *a5, int a6);
extern void ItemEvent_AddItem(BattleMon *a1);
extern void AbilityEvent_AddItem(BattleMon *a1);
extern void ItemEvent_RemoveItem(BattleMon *a1);
extern void AbilityEvent_RemoveItem(BattleMon *a1);
extern int ItemGetParam(u16 a1, ItemField a2);
extern bool Handler_CheckMatchup(int a1);
extern int CommonGetItemParam(BattleEventItem *a1, ItemField a2);

// WHITE SCREEN FIX
extern void wcharsncpy(wchar_t *pSrc, wchar_t *pDest, int length);
extern void GFL_StrBufStoreString(StrBuf *strbuf, wchar_t *dest, int length);
extern int BattleMon_GetComboMoveData(BattleMon *a1, _BYTE *a2, _WORD *a3);
extern int GetComboMoveType(int a1, int a2);
extern u8 Condition_GetTurnMax(void *a1);

extern int PokeTypePair_MakeMonotype(__int16 a1);
extern void HandlerAnticipation(int a1, _DWORD *a2, unsigned int a3, int a4);
extern int BattleMon_CanBattle(BattleMon *a1);
extern BattleStyle MainModule_GetBattleStyle(MainModule *a1);
extern int MainModule_GetNumBattlePositionsOfClient(MainModule *a1, int a2);
extern unsigned int BattleMon_IsIllusionEnabled(BattleMon *a1);
extern PartyPkm *BattleMon_GetViewSrcData(BattleMon *a1);
extern void BattleMon_SetIllusion(BattleMon *result, PartyPkm *a2);
extern void BattleMon_RemoveIllusion(BattleMon *result);
extern PartyPkm *BattleMon_GetSrcData(BattleMon *a1);
extern unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4, int flag);
extern int MainModule_BattlePosToClientID(MainModule *a1, int a2);
extern BattleMon *SwitchAI_DetermineOpponent(void *a1, __int16 a2);
extern unsigned int MainModule_GetClientPokePos(MainModule *a1, int clientID, int partyIndex);
extern BattleMon *PokeCon_GetBattleMon(void *a1, int a2);
extern int SwitchAI_CheckReserve(BtlClientWk *a1, int a2);
extern int GetNumBattleReadyPartyMons(BtlClientWk *a1, u8 *a2);
extern bool HandlerCommon_IsMonLastInTurnOrder(ServerFlow *a1, int a2);
extern int Handler_GetThisTurnAction(ServerFlow *a1, int a2, _DWORD *a3);
extern int HandlerThiefStart(int a1, ServerFlow *a2, int a3, int *a4);
extern bool Handler_IsSideEffectActive(ServerFlow *a1, int a2, int a3);
extern int Tables_CheckTableElems(int a1, unsigned __int16 *a2, unsigned int a3);
extern u32 PokeParty_GetSex(PartyPkm *pPkm);
extern int MainModule_GetDebugFlag();
extern int ServerEvent_BypassAccuracyCheck(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveID a4);
extern unsigned int ServerEvent_GetMoveAccuracy(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4);
extern unsigned int Calc_MulRatio(int result, int a2);
extern void HandlerChoiceItemCommonMoveLock(int a1, ServerFlow *a2, int a3);
extern void HandlerChoiceItemCommonItemChange(int a1, ServerFlow *a2, u8 a3);
extern void HandlerChoiceSpecsPower(int a1, int a2, int a3);
extern void HandlerChoiceScarf(int a1, int a2, int a3);
extern void HandlerChoiceBandPower(int a1, int a2, int a3);
extern void HandlerLifeOrbPower(BattleEventItem *a1, int a2, int a3);
extern void HandlerLifeOrbReaction(int a1, ServerFlow *a2, unsigned int *a3);
extern int HandlerFocusSash(int a1, ServerFlow *a2, int a3, int *a4);
extern int HandlerFocusSashUse(BattleEventItem *a1, ServerFlow *a2, int a3, int *a4);
extern int HandlerFocusBand(BattleEventItem *a1, ServerFlow *a2, int a3, int *a4);
extern int HandlerFocusBandCheck(BattleEventItem *a1, int a2, int a3, int *a4);
extern int HandlerFocusBandUse(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3);
extern int HandlerQuickClawUse(BattleEventItem *a1, ServerFlow *a2, int a3, _DWORD *a4);
extern int HandlerQuickClawPriorityCheck(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerBrightPowder(BattleEventItem *a1, int a2, int a3);
extern void HandlerLeftoversUse(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerLeftoversReaction(BattleEventItem *a1, ServerFlow *a2, unsigned int *a3);
extern void HandlerKingsRock(BattleEventItem *a1, int a2, int a3);
extern void HandlerKingsRockUseTemp(int a1, ServerFlow *a2, unsigned int *a3);
extern int HandlerCustapBerryUse(BattleEventItem *a1, ServerFlow *a2, int a3, _DWORD *a4);
extern b32 IsAffectedBySheerForce(MoveID moveID);
extern PersonalData * PML_PersonalLoadBW2(u16 species, u16 form);
extern u32 PML_PersonalGetParam(PersonalData *personal, PersonalField field);

C_DECL_END
