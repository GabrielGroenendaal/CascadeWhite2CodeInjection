
#include "structs_new.h"
//#include "../swan-master/system/game_data.h"



unsigned short int &HIWORD(unsigned int &x)
{
    return *(reinterpret_cast<unsigned short int *>(&x) + 1);
}

unsigned short int &LOWORD(unsigned int &x)
{
    return *(reinterpret_cast<unsigned short int *>(&x) + 0);
}

C_DECL_BEGIN


// STUFF FOR FIELD EFFECTS
extern bool BattleMon_IsStatChangeValid(BattleMon *a1, int a2, int a3);
extern BattleMon *Handler_GetPokeParam(ServerFlow *a1, int a2);
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
extern int ServerControl_ChangeWeatherCore(ServerFlow *a1, unsigned int a2, int a3);
extern int ServerControl_FieldEffectCore(ServerFlow *a1, int a2, int a3, int a4);
extern bool Handler_IsTargetInRange(ServerFlow *a1, int a2, int a3, int a4);
extern int Handler_AddSwitchOutInterrupt(int result, char a2);
extern BattleMon *BattleParty_GetPartyMember(BattleParty *a1, int a2);
extern SVCL_WORK *BattleServer_GetClientWork(BtlServerWk *a1, int a2);
extern int ServerControl_AfterSwitchIn(ServerFlow *a1);
extern int Handler_GetThisTurnAction(ServerFlow *a1, int a2, int *a3);
extern int BattleMon_GetHeldItem(BattleMon *a1);
extern int BtlSetup_GetBattleStyle(MainModule *a1);
extern int ServerControl_SwitchInCore(ServerFlow *a1, int a2, int a3, int a4);
extern bool BattleMon_IsFainted(BattleMon *a1);
extern bool Handler_CheckItemUsable(ServerFlow *a1, int a2);
extern int Handler_CheckReservedMemberChangeAction(ServerFlow *a1);
extern int MainModule_RegisterPokedexSeenFlag(MainModule *a1, int a2, int a3);
extern ServerFlow *BattleServer_GetServerFlow(BtlServerWk *a1);
extern int HandlerClearBodyCheck(int a1, int a2, int a3, int *a4);
extern bool Handler_GetFightEnableBenchPokeNum(ServerFlow *a1, unsigned int a2);
extern int BattleEventVar_Push();
extern int BattleEventVar_Pop();
extern int MultiplyBasePower(int a1);
extern int* ActionOrder_SearchByMonID(ServerFlow *a1, int a2);
extern int HandlerClearBodyGuard(int a1, ServerFlow *a2, int a3, int *a4);
extern bool BattleMon_IsFullHP(BattleMon *a1);
extern int BattleHandler_AddArg(unsigned __int16 *result, int a2);
extern unsigned __int16 *BattleHandler_StrSetup(unsigned __int16 *result, unsigned __int8 a2, __int16 a3);
extern char *BattleHandler_PushWork(ServerFlow *a1, int a2, int a3);
extern unsigned int *BattleHandler_PopWork(ServerFlow *a1, void *a2);
extern unsigned int *BattleHandler_PushRun(ServerFlow *a1, int a2, int a3);
extern int BattleMon_GetValue(BattleMon *a1, BattleMonValue a2);
extern int BattleMon_GetID(BattleMon *a1);
extern unsigned int BattleEventVar_SetConstValue(BattleEventVar a1, int a2);
extern int FaintRecord_GetCount(FaintRecord *a1, unsigned int turn);
extern int FaintRecord_GetPokeID(FaintRecord *a1, unsigned int a2, unsigned int a3);
extern int j_j_DeadRec_GetCount_3(FaintRecord *a1, unsigned int a2);
extern int j_j_FaintRecord_GetPokeID(FaintRecord *a1, unsigned int a2, unsigned int a3);
extern unsigned int BattleEventVar_SetValue(BattleEventVar a1, int a2);
extern FaintRecord *Handler_GetActionRecord(ServerFlow *a1);
extern unsigned int BattleEventVar_SetMulValue(BattleEventVar a1, int a2, int a3, int a4);
extern int BattleEvent_CallHandlers(ServerFlow *a1, BattleEventType a2);
extern int GetTypeEffectivenessMultiplier(int a1, int a2);
extern int fixed_round(int a1, unsigned int a2);
extern int Handler_PokeIDToPokePos(ServerFlow *a1, unsigned int a2);
extern int Handler_ExpandPokeID(ServerFlow *a1, __int16 a2, u8 *a3);
extern MoveCondition BattleMon_GetStatus(BattleMon *a1);
extern bool BattleMon_HasType(BattleMon *a1, Types a2);
extern bool BattleMon_GetConditionFlag(BattleMon *a1, ConditionFlag a2);
extern ZoneSpawnInfo *GameData_GetEntraLinkParentSpawnInfo(GameData *a1);
extern PlayerState *GameData_GetPlayerState(GameData *a1);
extern int HandlerGetMainModule(int a1);
extern bool MainModule_IsAllyMonID(unsigned int a1, unsigned int a2);
extern unsigned int DivideMaxHPZeroCheck(BattleMon *a1, unsigned int a2);
extern int PML_ItemIsBerry(int a1);
extern void HandlerUturn(BattleEventItem *a1, ServerFlow *a2, unsigned int a3);
extern int g_GameBeaconSys;
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
extern void PokeParty_SetParam(PartyPkm *a1, PkmField a2, int a3);
extern u32 PokeParty_GetParam(PartyPkm *a1, PkmField a2, void *extra);
extern bool AbilityEvent_RollEffectChance(int a1, unsigned int a2);
extern int PML_ItemGetParam(ItemData *a1, ItemField a2);
extern char *ServerDisplay_AddCommon(ServerCommandQueue *a1, int a2, ...);
extern int BattleEventVar_RewriteValue(BattleEventVar a1, int a2);
extern bool getMoveFlag(int a1, MoveFlag a2);
extern int HandlerOvercoat(int a1, int a2, int a3);
extern int HandlerFriendGuard(int a1, int a2, unsigned int a3);
extern int HandlerTelepathy(int a1, int a2, int a3);
extern int Handler_GetWeather(int a1);
extern int HandlerPlusMinus(int a1, ServerFlow *a2, unsigned int a3, int a4, int a5, int a6, int a7, int a8);
extern int HandlerHealer(int a1, ServerFlow *a2, unsigned int a3, int a4);
extern int BattleEventVar_MulValue(BattleEventVar a1, int a2);
extern int CommonResistBerry(int a1, int a2, int a3, unsigned int *a4, unsigned __int8 a5, int a6);
extern unsigned int *HandlerCommonResistBerryDamageAfter(int a1, int a2, int a3, unsigned int **a4);
extern int HandlerGemEnd(int a1, int a2, int a3, int *a4);
extern void CommonGemDecide(int r0_0, int a2, int a3, unsigned int *a4, unsigned __int8 a5);
extern int CommonGemPower(int a1, int a2, int a3, unsigned int *a4, unsigned __int8 a5);
extern int CommonTypeBoostingItem(int a1, int a2, int a3, int a4);
extern void ItemEvent_PushRun(BattleEventItem *a1, ServerFlow *a2, int a3);
extern int BattleEventItem_GetSubID(BattleEventItem *a1);
extern int HandlerCommon_CheckTargetPokeID(int a1);
extern int HandlerMarvelScale(int a1, ServerFlow *a2, int a3);
extern ConditionData Condition_MakePermanentParam(int a1);
extern ConditionData Condition_MakePermanent();
extern BattleMon *BattleParty_GetMonData(BattleParty *a1, unsigned int a2);
extern int BattleMon_GetMoveCount(BattleMon *a1);
extern int HandlerRainDish(int a1, ServerFlow *a2, int a3);
extern int BattleMon_GetPokeType(BattleMon *a1);
extern u8 PML_MoveGetType(int a1);
extern int Move_GetID(BattleMon *a1, int a2);
extern int HandlerChipAwayHitCheck(int a1, int a2, int a3);
extern BattleParty *BattleClient_GetActParty(BtlClientWk *a1);
extern int Move_GetPP(BattleMon *a1, unsigned int a2);
extern u16 PML_MoveGetBasePower(int id);
extern int HandlerWaterVeil(int a1, int a2, int a3, int *a4);
extern void HandlerWaterVeilCureStatus(int a1, ServerFlow *a2, unsigned int *a3);
extern bool PML_MoveIsDamaging(int id);
extern int HandlerKeenEyeGuard(int a1, ServerFlow *a2, int a3, int *a4);
extern int HandlerKeenEyeCheck(int a1, int a2, int a3, int *a4);
extern u8 PML_MoveGetType(int a1);
extern int j_j_BTL_SICKEVENT_CheckNotEffectByType(ServerFlow *a1, BattleMon *a2);
extern void HandlerWaterVeilActionEnd(int a1, ServerFlow *a2, int a3);
extern TypeEffectiveness GetTypeEffectiveness(int a1, int a2);
extern int GetTypeEffectivenessVsMon(int a1, int a2);
extern BattleMon *GetBattleMonFromBattlePos(TrainerAIEnv *a1, int a2);
extern int PokeTypePair_GetType1(int a1);
extern int PokeTypePair_GetType2(int a1);
extern BattleMon *PokeCon_GetPokeParam(PokeCon *a1, int a2);
extern int BattleMon_GetSpecies(BattleMon *a1);
extern bool BattleMon_IsIllusionEnabled(BattleMon *a1);
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
    unsigned __int16 *destDamage);
extern void ServerEvent_GetMoveParam(ServerFlow *a1, int a2, int a3, MoveParam *a4);
extern int HandlerSnowCloakWeather(int a1, int a2, int a3, int a4);
extern int HandlerThickFat(int a1, int a2, int a3, int a4);
extern int HandlerGuts(int a1, int a2, int a3);
extern int HandlerFlareBoost(int a1, int a2, int a3);
extern int HandlerQuickFeet(int a1, int a2, int a3);
extern int HandlerToxicBoost(int a1, int a2, int a3);
extern int HandlerPoisonHeal(int a1, int a2, int a3);
extern int HandlerAddStatusFailedCommon(int a1, int a2, int a3, int a4);
extern bool GetSideFromMonID(int a1);
extern int BattleField_GetWeather();
extern void *PML_ItemReadDataFile(unsigned int a1, int a2, HeapID a3);
extern ConditionData MakeBasicStatus(MoveCondition a1);
extern int PokeList_GetEVsAppliedAfterLimit(int a1, int a2, int a3, int a4);
extern void ApplyHeal(PartyPkm *a1, int a2, unsigned int a3, int a4);
extern int CheckPPGain(PartyPkm *a1, int a2, int a3);
extern int PokeParty_AddPP(PartyPkm *pkm, int moveIdx, int addend);
extern u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);
extern void PokeParty_RecalcStats(PartyPkm *a1);
extern int PokeList_ApplyFriendship(PartyPkm *a1, int a2, int a3, u16 a4, unsigned __int16 a5, HeapID a6);
extern int BattleMon_GetHPRatio(BattleMon *a1);

// New Effects
extern char ServerControl_CheckMoveExeSleepCure(ServerFlow *a1, BattleMon *a2);
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
extern char ServerControl_MoveExecuteFail(ServerFlow *a1, BattleMon *a2, int a3, int a4);
extern char ServerDisplay_MoveExecuteFailMessage(ServerFlow *a1, BattleMon *a2, int a3, unsigned int a4);
extern void ServerDisplay_AddEffectAtPosition(ServerFlow *a1, BattleMon *a2, int a3);
extern void ServerDisplay_CureStatus(ServerFlow *a1, BattleMon *a2, int a3, char *a4);
extern void ServerDisplay_AddMessageImpl(ServerCommandQueue *a1, int a2, __int16 a3, ...);
extern bool RollEffectChance(unsigned int a1);
extern int HandlerDrySkinCheck(int a1, ServerFlow *a2, int a3);
extern void HandlerDrySkinWeather(int a1, ServerFlow *a2, int a3);


extern int BattleMon_GetUsedItem(BattleMon *a1);

C_DECL_END

