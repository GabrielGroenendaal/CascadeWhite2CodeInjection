#include "codeinjection_new.h"
#include "kPrint.h"
#include "settings.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// Uses esdb_newBattle.yml

#pragma region Definitions
extern "C" int SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
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

const u16 WindMoves[17] = {
    MOVE403_AIR_SLASH,
    MOVE542_HURRICANE,
    MOVE257_HEAT_WAVE,
    MOVE466_OMINOUS_WIND,
    MOVE318_SILVER_WIND,
    MOVE016_GUST,
    MOVE059_BLIZZARD,
    MOVE379_PETAL_BLIZZARD,
    MOVE511_FAIRY_WIND,
    MOVE180_DIAMOND_STORM,
    MOVE013_RAZOR_WINDS,
    MOVE177_AEROBLAST,
    MOVE196_ICY_WIND,
    MOVE366_TAILWIND,
    MOVE239_TWISTER,
    MOVE018_WHIRLWIND,
    MOVE314_AIR_CUTTER};

const u16 BulletproofMoves[21] = {
    MOVE491_ACID_SPRAY,
    MOVE396_AURA_SPHERE,
    MOVE140_BARRAGE,
    MOVE331_BULLET_SEED,
    MOVE121_EGG_BOMB,
    MOVE486_ELECTRO_BALL,
    MOVE412_ENERGY_BALL,
    MOVE411_FOCUS_BLAST,
    MOVE360_GYRO_BALL,
    MOVE301_BOOMBURST,
    MOVE443_MAGNET_BOMB,
    MOVE426_MUD_BOMB,
    MOVE190_OCTAZOOKA,
    MOVE461_POLLEN_PUFF,
    MOVE350_ROCK_BLAST,
    MOVE439_ROCK_WRECKER,
    MOVE402_SEED_BOMB,
    MOVE247_SHADOW_BALL,
    MOVE188_SLUDGE_BOMB,
    MOVE311_WEATHER_BALL,
    MOVE192_ZAP_CANNON};

const u16 teraItems[19] = {
    IT0215_TERA_BADGE,
    IT0298_TERA_SPECS,
    IT0299_TERA_C_BAND,
    IT0300_TERA_SCARF,
    IT0301_TERA_ORB,
    IT0302_TERA_SASH,
    IT0303_TERA_F_BAND,
    IT0304_TERA_CLAW,
    IT0305_TERA_W_POLICY,
    IT0306_TERA_B_POLICY,
    IT0307_TERA_POWDER,
    IT0308_TERA_VEST,
    IT0309_TERA_INSURANCE,
    IT0310_TERA_DRILL,
    IT0311_TERA_LEFTOVERS,
    IT0312_TERA_DICE,
    IT0313_TERA_K_ROCK,
    IT0544_TERA_PLATE,
    IT0228_TERA_GEM,
};
const int FLAIL_POWER_TABLE[6] = {
    0xC80001, 0x960004, 0x640009, 0x500010, 0x280020, 0x140030};

#pragma endregion

#pragma region functionDefinitions

// extern "C" bool IsEqual(int a1, int a2)
// {
//     char *c1 = (char *)&a1;
//     char *c2 = (char *)&a2;

//     for (u16 i = 0; i < 4; ++i)
//     {
//         if (c1[i] != c2[i])
//             return false;
//     }
//     return true;
// }
// unsigned short int &HIWORD(unsigned int &x)
// {
//     return *(reinterpret_cast<unsigned short int *>(&x) + 1);
// }
// extern "C" int Handler_PokeIDToPokePos(ServerFlow *a1, unsigned int a2);
// extern BattleParty *BattleClient_GetActParty(BtlClientWk *a1);
// extern "C" int Move_GetID(BattleMon *a1, int a2);
// extern "C" int BattleMon_GetMoveCount(BattleMon *a1);
// extern "C" int BattleMon_CanBattle(BattleMon *a1);
// extern "C" int sub_219C424(MainModule *a1, int a2);
// extern "C" unsigned int BattleMon_IsIllusionEnabled(BattleMon *a1);
// extern "C" PartyPkm *BattleMon_GetViewSrcData(BattleMon *a1);
// extern "C" void BattleMon_SetIllusion(BattleMon *result, PartyPkm *a2);
// extern "C" void BattleMon_RemoveIllusion(BattleMon *result);
// extern "C" PartyPkm *BattleMon_GetSrcData(BattleMon *a1);
// extern "C" int MainModule_BattlePosToClientID(MainModule *a1, int a2);
// extern "C" BattleMon *SwitchAI_DetermineOpponent(void *a1, __int16 a2);
// extern "C" unsigned int MainModule_GetClientPokePos(MainModule *a1, int clientID, int partyIndex);
// extern "C" int SwitchAI_CheckReserve(BtlClientWk *a1, int a2);
// extern "C" int GetNumBattleReadyPartyMons(BtlClientWk *a1, u8 *a2);
// extern "C" int MainModule_PokeIDToClientID(int a1);
// extern "C" void BattleField_TurnCheck(void* a1, ServerFlow *a2);
// extern "C" void* TurnCheckCallback_Field;
// extern "C" void *ServerDisplay_AddCommon(ServerCommandQueue *a1, int a2, ...);
// extern "C" int BattleMon_GetValue(BattleMon *a1, BattleMonValue a2);
// extern "C" EventWorkSave *GameData_GetEventWork(void *gameData);
// extern "C" u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
// extern PlayerState *GameData_GetPlayerState(GameData *gameData);
// extern BtlSetup *MainModule_GetBtlSetup(MainModule *a1);
// extern int PlayerState_GetZoneID(PlayerState *a1);
// extern int PokeTypePair_GetType1(int a1);
// extern int PokeTypePair_GetType2(int a1);
// extern bool PokeTypePair_IsMonotype(int a1);
// extern TypeEffectiveness GetTypeEffectiveness(int a1, int a2);
// extern int GetTypeEffectivenessVsMon(int a1, int a2);
// extern int GetTypeEffectivenessMultiplier(int a1, int a2);
// extern unsigned int BattleEventVar_SetRewriteOnceValue(BattleEventVar a1, int a2);
// extern int BattleEventVar_RewriteValue(BattleEventVar a1, int a2);
// extern int BattleEventVar_Push();
// extern int BattleEventVar_Pop();
// extern int BattleMon_GetID(BattleMon *a1);
// extern unsigned int BattleEventVar_SetConstValue(BattleEventVar a1, int a2);
// extern int j_j_Condition_CheckUnaffectedByType(ServerFlow *a1, BattleMon *a2);
// extern int BattleEventVar_GetValue(BattleEventVar a1);
// extern int BattleEvent_CallHandlers(ServerFlow *a1, BattleEventType a2);
// extern HandlerParam_Header *BattleHandler_PushWork(ServerFlow *a1, BattleHandlerEffect a2, int a3);
// extern void BattleHandler_PopWork(ServerFlow *a1, void *a2);
// extern void BattleHandler_PushRun(ServerFlow *a1, BattleHandlerEffect a2, int a3);
// extern bool BattleMon_IsFullHP(BattleMon *a1);
// extern int BattleHandler_AddArg(HandlerParam_StrParams *result, int a2);
// extern void BattleHandler_StrSetup(HandlerParam_StrParams *result, unsigned __int8 a2, __int16 a3);
// extern ConditionData Condition_MakePermanent();
// extern ConditionData BattleMon_GetMoveCondition(BattleMon *a1, MoveCondition a2);
// extern bool ServerControl_ChangeWeatherCheck(ServerFlow *a1, unsigned int a2, int a3);
// extern BattleFieldStatus *BtlSetup_GetFieldStatus(MainModule *a1);
// extern int ServerControl_ChangeWeather(ServerFlow *a1, unsigned int a2, int a3);
// extern int ServerControl_ChangeWeatherCore(ServerFlow *a1, int a2, int a3);
// extern int ServerControl_FieldEffectCore(ServerFlow *a1, int a2, ConditionData a3, int a4);
// extern SVCL_WORK *BattleServer_GetClientWork(BtlServerWk *a1, int a2);
// extern int ServerControl_AfterSwitchIn(ServerFlow *a1);
// extern int ServerControl_SwitchInCore(ServerFlow *a1, int a2, unsigned int a3, int a4);
// extern BattleMon *BattleParty_GetPartyMember(BattleParty *a1, unsigned int a2);
// extern bool BattleMon_IsFainted(BattleMon *a1);
// extern int BattleMon_GetHeldItem(BattleMon *a1);
// extern int BtlSetup_GetBattleStyle(MainModule *a1);
// extern FaintRecord *Handler_GetFaintRecord(ServerFlow *a1);
// extern void MainModule_RegisterPokedexSeenFlag(MainModule *a1, int a2, int a3);
// extern int j_j_FaintRecord_GetCount(FaintRecord *a1, unsigned int turn);
// extern int j_j_FaintRecord_GetPokeID(FaintRecord *a1, unsigned int a2, unsigned int a3);
// extern bool MainModule_IsAllyMonID(unsigned int a1, unsigned int a2);
// extern int BattleMon_GetHPRatio(BattleMon *a1);
// extern int Handler_CalculateSpeed(ServerFlow *a1, BattleMon *a2, int a3);
// extern bool BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2);
// extern int ServerEvent_GetWeather(ServerFlow *a1);
// extern int Handler_GetPrevUsedMove(ServerFlow *a1);
// extern unsigned int RandomInRange(unsigned int a1, unsigned int a2);
// extern MoveCondition BattleMon_GetStatus(BattleMon *a1);
// extern bool BattleMon_HasType(BattleMon *a1, Types a2);
// extern bool BattleMon_GetConditionFlag(BattleMon *a1, ConditionFlag a2);
// extern int BattleMon_GetPreviousMoveID(BattleMon *a1);
// extern int BattleMon_GetPreviousMove(BattleMon *a1);
// extern bool BattleMon_GetTurnFlag(BattleMon *a1, TurnFlag a2);
// extern int PML_ItemIsBerry(u16 itemId);
// extern u32 div32(u32 numerator, u32 denominator);
// extern bool HandlerCommon_CheckIfCanStealPokeItem(ServerFlow *a1, unsigned int a2, int a3);
// extern BattleMon *PokeCon_GetBattleMon(void *a1, int a2);
// extern bool PML_MoveIsDamaging(int id);
// extern BattleMon *MainModule_GetIllusionDisguise(MainModule *a1, int a2, int a3);
// extern int Handler_SimulationEffectivenessCore(ServerFlow *a1, int a2, int a3, int a4);
// extern void ServerEvent_GetMoveParam(ServerFlow *a1, int a2, int a3, MoveParam *a4);
// extern int j_j_IsNotAllowedCopycatMove(int a1);
// extern int ItemGetParam(u16 a1, ItemField a2);
// extern int Handler_GetBattleTerrain(ServerFlow *a1);
// extern int BattleMon_GetPokeType(BattleMon *a1);
// extern bool Handler_IsSideEffectActive(ServerFlow *a1, int a2, int a3);
// extern bool GetSideFromMonID(unsigned int a1);
// extern int Move_GetPP(BattleMon *a1, unsigned int a2);
// extern u16 PML_MoveGetBasePower(int id);
// extern int ServerEvent_CalcDamage(
//     ServerFlow *a1,
//     BattleMon *AttackingMon,
//     BattleMon *DefendingMon,
//     MoveParam *MoveParam,
//     int TypeEffectiveness,
//     int targetDmgRatio,
//     int criticalFlag,
//     int BattleDebugMode,
//     _WORD *destDamage);
// extern u8 PML_MoveGetType(int a1);
// extern bool getMoveFlag(int a1, MoveFlag a2);
// extern ServerFlow *BattleServer_GetServerFlow(BtlServerWk *a1);
// extern int BattleField_GetWeather();
// extern BattleMon *BattleParty_GetMonData(BattleParty *a1, unsigned int a2);
// extern int BattleRandom(unsigned int a1);
// extern int CheckIfMonToSwitchToWithSEMove(BtlClientWk *a1, BattleMon *a2, int Effectiveness);
// extern int Condition_GetParam(ConditionData a1);
// extern int Move_SearchIndex(BattleMon *a1, int a2);
// extern int Handler_GetExistFrontPokePos(ServerFlow *a1, int a2);
// extern int Handler_SimulationDamage(ServerFlow *a1, int a2, int a3, int a4, bool a5, bool a6);
// extern BattleMon *Handler_GetBattleMon(ServerFlow *a1, int a2);
// extern int Handler_ExpandPokeID(ServerFlow *a1, __int16 a2, u8 *a3);
#pragma endregion

extern "C"
{

#pragma region DamageCalcStateTracking

#if DAMAGE_CACHE_ENABLED
    struct keyPair
    {
        u8 dirty;
        u16 value;
    };

    keyPair calcTable[6][6][4] = {
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
    };

    u16 NumOfCalcs = 0;
    u16 NumOfCalcsAvoided = 0;

    void resetCalcTable()
    {
        for (u8 i = 0; i < 6; i++)
        {
            for (u8 k = 0; k < 6; k++)
            {
                for (u8 j = 0; j < 4; j++)
                {
                    calcTable[i][k][j].dirty = 0;
                    calcTable[i][k][j].value = 0;
                }
            }
        }
#if DEBUGGING_DAMAGECALC && DEBUGGING_ALL
        k::Printf("\nThe number of calcs performed this turn was %d and the number of calcs avoided was %d\n", NumOfCalcs, NumOfCalcsAvoided);
#endif
        NumOfCalcs = 0;
        NumOfCalcsAvoided = 0;
    }

    u8 GetMovePos(BattleMon *mon, MoveID move)
    {
        int movecount = BattleMon_GetMoveCount(mon);
        int count = 0;
        if (movecount)
        {
            do
            {
                if (Move_GetID(mon, count) == move)
                {
                    return count;
                }
                count++;
            } while (count < movecount);
        }
        return 5;
    }

    u16 checkCalcTable(ServerFlow *flow, BattleMon *attacker, BattleMon *defender, MoveID move)
    {
        int index1 = Handler_PokeIDToPokePos(flow, attacker->ID);
        int index2 = Handler_PokeIDToPokePos(flow, defender->ID);
        int index3 = GetMovePos(attacker, move);
        if (index3 > 4)
        {
            return 0;
        }

        NumOfCalcs++;
        if (calcTable[index1][index2][index3].dirty == 1)
        {
            NumOfCalcsAvoided++;
            return calcTable[index1][index2][index3].value;
        }
        return 0;
    }

    void saveToCalcTable(ServerFlow *flow, BattleMon *attacker, BattleMon *defender, MoveID move, u32 damage)
    {
        int index1 = Handler_PokeIDToPokePos(flow, attacker->ID);
        int index2 = Handler_PokeIDToPokePos(flow, defender->ID);
        int index3 = GetMovePos(attacker, move);
        calcTable[index1][index2][index3].dirty = 1;
        calcTable[index1][index2][index3].value = damage;
    }

    void THUMB_BRANCH_ServerControl_TurnCheckField(ServerFlow *a1)
    {
        resetCalcTable();

        BattleField_TurnCheck(TurnCheckCallback_Field, a1);
        ServerDisplay_AddCommon(a1->serverCommandQueue, 47, 0);
    }
#endif

#pragma endregion

#pragma region genericHelpers

    u32 getSwitchSetting()
    {

        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16436);
        return *lvl_cap_ptr;
        // return *lvl_cap_ptr;
    }

    bool HasMoldBreaker(BattleMon *a1)
    {
        return (
            BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL104_MOLD_BREAKER || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL163_TURBOBLAZE || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL164_TERAVOLT || BattleMon_GetHeldItem(a1) == IT0223_ABILITY_DRILL || BattleMon_GetHeldItem(a1) == IT0310_TERA_DRILL);
    }

    const u16 autoCritMoves[9] = {
        MOVE314_AIR_CUTTER,
        MOVE440_CROSS_POISON,
        MOVE480_STORM_THROW,
        MOVE346_WICKED_BLOW,
        MOVE190_OCTAZOOKA,
        MOVE163_SLASH,
        MOVE006_PAY_DAY,
        MOVE524_FROST_BREATH,
        MOVE400_NIGHT_SLASH};

    enum FieldTypeChanges
    {
        FIELD_NONE = 0,
        FIELD_CHARGESTONE = 1,
        FIELD_CELESTIAL = 2,
        FIELD_OPELUCID = 3,
        FIELD_TRICK_ROOM = 4,
        FIELD_SKYLA = 5,
        FIELD_SUN = 6,
        FIELD_SMOKEBOMB = 7,
        FIELD_VICTORYSTAR = 8,
        FIELD_RAIN = 9
    };

    FieldTypeChanges checkForFieldEffects()
    {

        PlayerState *playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        int zoneId = PlayerState_GetZoneID(playerState);

        if (zoneId == 121)
        {
            return FIELD_OPELUCID;
        }
        // if (zoneId == 446)
        // {
        //     return FIELD_SMOKEBOMB;
        // }
        // if (zoneId == 437)
        // {
        //     return FIELD_VICTORYSTAR;
        // }
        if (zoneId == 607 || zoneId == 195 || zoneId == 196 || zoneId == 197)
        {

            return FIELD_CHARGESTONE;
        }
        if (zoneId == 339 || zoneId == 338 || zoneId == 340 || zoneId == 341 || zoneId == 462 || (zoneId >= 510 && zoneId <= 514) || (zoneId >= 569 && zoneId <= 572))
        {
            return FIELD_CELESTIAL;
        }
        if (zoneId == 108)
        {
            return FIELD_SKYLA;
        }
        if (zoneId == 503 || zoneId == 504 || zoneId == 505 || zoneId == 245 || zoneId == 248 || (zoneId >= 255 && zoneId <= 262) || (zoneId >= 160 && zoneId <= 190))
        {
            return FIELD_TRICK_ROOM;
        }
        if (zoneId == 463 || zoneId == 465 || zoneId == 376)
        {
            return FIELD_SUN;
        }
        if (zoneId == 473)
        {
            return FIELD_RAIN;
        }
        return FIELD_NONE;
    };

    const u8 normalTypeChart[18][18] = {
        {4, 4, 4, 4, 4, 2, 4, 0, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {8, 4, 2, 2, 4, 8, 2, 0, 8, 4, 4, 4, 4, 2, 8, 4, 8, 2},
        {4, 8, 4, 4, 4, 2, 8, 4, 2, 4, 4, 8, 2, 4, 4, 4, 4, 4},
        {4, 4, 4, 2, 2, 2, 4, 2, 0, 4, 4, 8, 4, 4, 4, 4, 4, 8},
        {4, 4, 0, 8, 4, 8, 2, 4, 8, 8, 4, 2, 8, 4, 4, 4, 4, 4},
        {4, 2, 8, 4, 2, 4, 8, 4, 2, 8, 4, 4, 4, 4, 8, 4, 4, 4},
        {4, 2, 2, 2, 4, 4, 4, 2, 2, 2, 4, 8, 4, 8, 4, 4, 8, 2},
        {0, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 4},
        {4, 4, 4, 4, 4, 8, 4, 4, 2, 2, 2, 4, 2, 4, 8, 4, 4, 8},
        {4, 4, 4, 4, 4, 2, 8, 4, 8, 2, 2, 8, 4, 4, 8, 2, 4, 4},
        {4, 4, 4, 4, 8, 8, 4, 4, 4, 8, 2, 2, 4, 4, 4, 2, 4, 4},
        {4, 4, 2, 2, 8, 8, 2, 4, 2, 2, 8, 2, 4, 4, 4, 2, 4, 4},
        {4, 4, 8, 4, 0, 4, 4, 4, 4, 4, 8, 2, 2, 4, 4, 2, 4, 4},
        {4, 8, 4, 8, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 0, 4},
        {4, 4, 8, 4, 8, 4, 4, 4, 2, 2, 2, 8, 4, 4, 2, 8, 4, 4},
        {4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 4, 0},
        {4, 2, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 2},
        {4, 8, 4, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 8, 8, 4}};

#pragma endregion

#pragma region TypeChecksAndEffectiveness

    int GetTypeEffectivenessAltered(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;
        FieldTypeChanges zoneId = checkForFieldEffects();

        if (a1 == TYPE_NONE || a2 == TYPE_NONE)
        {
            result = EFFECTIVENESS_1;
            return result;
        }
        // Freeze Dry
        else if (a1 == TYPE_ICE && a2 == TYPE_WATER)
        {
            v3 = 8;
        }
        // Corrosion
        else if (a1 == TYPE_POISON && a2 == TYPE_STEEL)
        {
            v3 = 8;
        }
        // Inner Focus
        else if (a1 == TYPE_PSYCHIC && a2 == TYPE_DARK)
        {
            v3 = 4;
        }
        // Scrappy and Relic Song
        else if (a1 == TYPE_NORMAL && a2 == TYPE_GHOST)
        {
            v3 = 4;
        }
        // Sacred Sword and Scrappy
        else if (a1 == TYPE_FIGHTING && a2 == TYPE_GHOST)
        {
            v3 = 4;
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
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
            return 0;
        }
        return result;
    }

    int GetTypeEffectivenessVsMonAltered(int a1, int a2)
    {
        int TypeEffectiveness; // r4
        int v6;                // r0
        int v7;
        int v8;
        v8 = PokeTypePair_GetType1(a2);
        v7 = PokeTypePair_GetType2(a2);

        if (PokeTypePair_IsMonotype(a2))
        {

            return GetTypeEffectivenessAltered(a1, v8);
        }
        TypeEffectiveness = GetTypeEffectivenessAltered(a1, v8);
        v6 = GetTypeEffectivenessAltered(a1, v7);
        return GetTypeEffectivenessMultiplier(TypeEffectiveness, v6);
    }

    int EvaluateTypeEffectiveness(int a1, int a2, bool isScrappy)
    {
        TypeEffectiveness result;
        int v3;
        FieldTypeChanges zoneId = checkForFieldEffects();

        if (a1 == TYPE_NONE || a2 == TYPE_NONE)
        {
            result = EFFECTIVENESS_1;
            return result;
        }
        else if (a1 == TYPE_FIGHTING && a2 == TYPE_FLYING)
        {
            v3 = 8;
        }
        else if ((a1 == TYPE_FIGHTING) && a2 == TYPE_GHOST)
        {
            if (isScrappy)
            {
                v3 = 4;
            }
            else if (zoneId == FIELD_OPELUCID)
            {
                v3 = 2;
            }
            else
            {
                v3 = 0;
            }
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
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
            return 0;
        }
        return result;
    }
    int EvaluateTypeEffectivenesssForFighting(int type1, int pokeType, bool isScrappy)
    {
        int TypeEffectiveness; // r4
        int v6;                // r0
        int v7;
        int v8;
        v8 = PokeTypePair_GetType1(pokeType);
        v7 = PokeTypePair_GetType2(pokeType);

        if (PokeTypePair_IsMonotype(pokeType))
        {
            return EvaluateTypeEffectiveness(type1, v8, isScrappy);
        }
        TypeEffectiveness = EvaluateTypeEffectiveness(type1, v8, isScrappy);
        v6 = EvaluateTypeEffectiveness(type1, v7, isScrappy);
        return GetTypeEffectivenessMultiplier(TypeEffectiveness, v6);
    }

    TypeEffectiveness THUMB_BRANCH_GetTypeEffectiveness(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;
        if (a1 == 18 || a2 == 18)
        {
            result = EFFECTIVENESS_1;
            return result;
        }
        FieldTypeChanges field = checkForFieldEffects();

        if (a1 == TYPE_ELECTRIC && a2 == TYPE_GROUND && field == FIELD_CHARGESTONE)
        {
            v3 = 2;
        }
        else if (a1 == TYPE_GHOST && a2 == TYPE_NORMAL && field == FIELD_CELESTIAL)
        {
            v3 = 2;
        }
        else if (a1 == TYPE_PSYCHIC && a2 == TYPE_DARK && field == FIELD_CELESTIAL)
        {
            v3 = 2;
        }
        else if (a1 == TYPE_DRAGON && a2 == TYPE_FAIRY && field == FIELD_OPELUCID)
        {
            v3 = 2;
        }
        else if (a1 == TYPE_FIGHTING && a2 == TYPE_GHOST && field == FIELD_OPELUCID)
        {
            v3 = 2;
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
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

    int THUMB_BRANCH_AI044_GetMoveEffectiveness(ScriptVM *a1, TrainerAIEnv *a2)
    {
        int ID; // r7
        int v5; // r0
        int v6; // r0
        u32 a4; // [sp+4h] [bp-1Ch]
        int v7;
        a4 = VM_Read32(a1);
        v7 = VM_Read32(a1);
        ID = BattleMon_GetID(a2->attacker);
        v5 = BattleMon_GetID(a2->defender);
        MoveEvent_AddItem(a2->attacker, a2->moveID, BattleMon_GetValue(a2->attacker, VALUE_SPEED_STAT));
        v6 = Handler_SimulationEffectivenessCore(a2->serverFlow, ID, v5, a2->moveID);
        MoveEvent_RemoveItem(a2->attacker, a2->moveID);
        AIConditionalJump(a1, 2u, v6, a4, v7);
        return a2->result;
    }

    TypeEffectiveness THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(ServerFlow *a1, BattleMon *a2, BattleMon *a3, int a4, unsigned __int8 a5)
    {
        int ID;    // r0
        int v9;    // r0
        int Value; // r5
        int ActualType;
        int v11;                  // r4
        TypeEffectiveness result; // r0

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v9 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v9);
        BattleEventVar_SetConstValue(VAR_POKE_TYPE, a5);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4);
        BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);
        BattleEventVar_SetRewriteOnceValue(VAR_SET_TYPE_EFFECTIVENESS, 0);
        j_j_Condition_CheckUnaffectedByType(a1, a3);
        BattleEvent_CallHandlers(a1, EVENT_CHECK_TYPE_EFFECTIVENESS);
        Value = BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS);
        v11 = BattleEventVar_GetValue(VAR_SET_TYPE_EFFECTIVENESS);
        BattleEventVar_Pop();
        if (Value == 4 ) {
            return EFFECTIVENESS_1;
        }
        if (v11 == 1)
        {
            return EFFECTIVENESS_1;
        }
        if (v11 == 2)
        {
            return EFFECTIVENESS_2;
        }
        // if (v11 >= 2)
        // {
        //     return (TypeEffectiveness)GetTypeEffectivenessAltered(a4, a5);
        // }
        // else if (v11)
        // {
        //     return EFFECTIVENESS_1;
        // }
        result = GetTypeEffectiveness(a4, a5);
        if (result == EFFECTIVENESS_IMMUNE)
        {
            if (Value)
            {
                return EFFECTIVENESS_1;
            }
        }
        return result;
    }

#pragma endregion

#pragma region FieldEffectsAndBattleStart

    void CreateSpikes(int a1, ServerFlow *a2, unsigned int *a3, int a4, unsigned __int8 a5, int a6, ConditionData a7, __int16 a8)
    {
        HandlerParam_AddSideEffect *v10;
        v10 = (HandlerParam_AddSideEffect *)BattleHandler_PushWork(a2, EFFECT_ADDSIDEEFFECT, (int)a3);
        v10->effect = a6;
        v10->side = a5;
        v10->cont = a7;
        BattleHandler_StrSetup(&v10->exStr, 1u, a8);
        BattleHandler_AddArg(&v10->exStr, a5);
        BattleHandler_PopWork(a2, v10);
    };

    int HandleFieldEffects(ServerFlow *a1)
    {

        HandlerParam_Message *bhwork;
        BtlSetup *btlsetup;
        BattleFieldStatus *FieldStatus; // r0
        TrainerBattleSetup **trainerSetups;
        TrainerBattleSetup *currentTrainer;
        int trainerId;
        int trainerClass;
        ConditionData random;

        FieldStatus = BtlSetup_GetFieldStatus(a1->mainModule);
        FieldTypeChanges field = checkForFieldEffects();

        ServerControl_ChangeWeather(a1, 10, 10);

        // Trick Room Setter
        // Checks ZoneId for Relic Castle, currently
        if (field == FIELD_TRICK_ROOM)
        {
            // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
            //         k::Printf("\nDEBUGGING TRICK ROOM FIELD\n");
            // #endif
            random = Condition_MakePermanent();
            ServerDisplay_AddCommon(a1->serverCommandQueue, 48, 1, 0, 433, 0, 0);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 203);
            BattleHandler_PopWork(a1, bhwork);
            ServerControl_FieldEffectCore(a1, 1, Condition_MakePermanent(), 0);
        }

#if TESTING_FIELDEFFECTS
        if (field == FIELD_SMOKEBOMB)
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE114_HAZE;
            addAnimation->pos_from = 6;
            addAnimation->pos_to = 6;
            BattleHandler_PopWork(a1, addAnimation);
            ServerDisplay_AddCommon(a1->serverCommandQueue, 48, 1, 0, 433, 0, 0); // IS THIS STILL CORRECT
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 203); // CHANGE THIS MESSAGE
            BattleHandler_PopWork(a1, bhwork);
            ServerControl_FieldEffectCore(a1, 10, Condition_MakePermanent(), 0);
        }
#endif

        // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
        //         k::Printf("\nTRICK ROOM CHECK COMPLETE\n");
        // #endif
        random = Condition_MakePermanent();
        // Chargestone Cave
        if (field == FIELD_CHARGESTONE)
        {
            //  #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
            //         k::Printf("\nDEBUGING CHARGESTONE FIELD\n");
            // #endif
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE351_SHOCK_WAVE;
            addAnimation->pos_from = 3;
            addAnimation->pos_to = 0;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 204);
            BattleHandler_PopWork(a1, bhwork);
            // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
            //         k::Printf("\nCHARGESTONE FIELD DIDN't CRASH\n");
            // #endif
        }
        // Celestial Tower
        else if (field == FIELD_CELESTIAL)
        {
            // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
            //         k::Printf("\nDEBUGGING CELESTIAL FIELD\n");
            // #endif
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE114_HAZE;
            addAnimation->pos_from = 6;
            addAnimation->pos_to = 6;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 205);
            BattleHandler_PopWork(a1, bhwork);
            // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
            //         k::Printf("\nCELESTIAL FIELD DIDN'T CRASH\n");
            // #endif
        }
        // Opelucid Gym
        else if (field == FIELD_OPELUCID)
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE137_GLARE;
            addAnimation->pos_from = 3;
            addAnimation->pos_to = 0;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 206);
            BattleHandler_PopWork(a1, bhwork);
        }

        // Skyla' Gym
        else if (field == FIELD_SKYLA)
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE366_TAILWIND;
            addAnimation->pos_from = 6;
            addAnimation->pos_to = 6;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 207);
            BattleHandler_PopWork(a1, bhwork);
        }
        else
        {
        }
        // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
        //         k::Printf("\nCHECKING FOR SPIKES SETUP\n");
        //         k::Printf("\nBTL TYPE IS: %d\n", a1->mainModule->btlSetup->btlType);
        // #endif
        if (a1->mainModule->btlSetup->btlType != 0)
        {
            trainerSetups = a1->mainModule->btlSetup->TrainerSetups;

            currentTrainer = trainerSetups[1];

            trainerId = currentTrainer->TrID;
            trainerClass = currentTrainer->TrClass;

            // PreSet Spikes
            // Checks TrainerId
            // if (trainerClass == 192)
            // {
            //     ConditionData Permanent = Condition_MakePermanent();
            //     HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            //     addAnimation->animNo = MOVE191_SPIKES;
            //     addAnimation->pos_from = 3;
            //     addAnimation->pos_to = 0;
            //     BattleHandler_PopWork(a1, addAnimation);
            //     CreateSpikes(0, a1, 0, 0, 0, SIDEEFF_SPIKES, Permanent, 148);
            // }

            // if (trainerClass == 192)
            // {
            //     ConditionData Permanent = Condition_MakePermanent();
            //     HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            //     addAnimation->animNo = MOVE114_HAZE;
            //     addAnimation->pos_from = 3;
            //     addAnimation->pos_to = 0;
            //     BattleHandler_PopWork(a1, addAnimation);
            //     CreateSpikes(0, a1, 0, 0, 0, SIDEEFF_SMOKEBOMB, Permanent, 257);
            // }

            if (trainerId == 582 || trainerId == 506)
            {
                // HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
                // addAnimation->animNo = MOVE381_LUCKY_CHANT;
                // addAnimation->pos_from = 6;
                // addAnimation->pos_to = 6;
                // BattleHandler_PopWork(a1, addAnimation);
                ServerDisplay_AddCommon(a1->serverCommandQueue, 48, 1, 0, 381, 0, 0); // IS THIS STILL CORRECT
                bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
                BattleHandler_StrSetup(&bhwork->str, 1u, 261); // CHANGE THIS MESSAGE
                BattleHandler_PopWork(a1, bhwork);
                ServerControl_FieldEffectCore(a1, 9, Condition_MakePermanent(), 0);
            }

            // Cobalion Fight
            if (trainerId == 491)
            {

                ConditionData Permanent = Condition_MakePermanent();
                HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
                addAnimation->animNo = MOVE137_GLARE;
                addAnimation->pos_from = 1;
                addAnimation->pos_to = 0;
                BattleHandler_PopWork(a1, addAnimation);
                CreateSpikes(0, a1, 0, 0, 0, SIDEEFF_OPPRESSIVE, Permanent, 208);
            }

            // Virizion Fight
            if (trainerId == 507)
            {

                ConditionData Permanent = Condition_MakePermanent();
                HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
                addAnimation->animNo = MOVE312_AROMATHERAPY;
                addAnimation->pos_from = 1;
                addAnimation->pos_to = 0;
                BattleHandler_PopWork(a1, addAnimation);
                CreateSpikes(0, a1, 0, 0, 0, SIDEEFF_FORESTWRATH, Permanent, 255);
            }
        }

        // Overworld Weather Setter
        if (field == FIELD_SUN)
        {
            // Setting Sun
            if (ServerControl_ChangeWeather(a1, 1, 255))
            {
                return 1;
            }
        }
        else if (field == FIELD_RAIN)
        {
            // Setting Rain
            if (ServerControl_ChangeWeather(a1, 2, 255))
            {
                return 1;
            }
        }
        else if (FieldStatus->BtlWeather && ServerControl_ChangeWeather(a1, (unsigned __int8)FieldStatus->BtlWeather, 255))
        {
            return 1;
        }

        return 0;
    }

    // // SOURCE OF THE CRASH IS THIS FUNCTION //
    int THUMB_BRANCH_SAFESTACK_ServerFlow_SetupBeforeFirstTurn(ServerFlow *a1)
    {

        ServerCommandQueue *serverCommandQueue; // r1
        BattleFieldStatus *FieldStatus;         // r0
        SVCL_WORK *ClientWork;                  // r0
        SVCL_WORK *v5;                          // r4
        BtlServerWk *server;
        unsigned int v6;        // r5
        BattleMon *PartyMember; // r0
        unsigned int j;         // r5
        BattleMon *v9;          // r0
        int v10;                // r7
        int v12;                // [sp+0h] [bp-20h]
        unsigned int i;         // [sp+4h] [bp-1Ch]

        serverCommandQueue = a1->serverCommandQueue;
        serverCommandQueue->writePtr = 0;
        v12 = 0;
        serverCommandQueue->readPtr = 0;
        // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
        //         k::Printf("\nSetting up field effects at the start of the battle\n");
        // #endif
        v12 = HandleFieldEffects(a1);
        // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
        //         k::Printf("\nCheck 1: Setting up field effects at the start of the battle\n");
        // #endif
        /* Some kind of initialization of the damage calc cache would be good here */
#if DAMAGE_CACHE_ENABLED
        resetCalcTable();
#endif
        for (i = 0; i < 4; ++i)
        {
            ClientWork = BattleServer_GetClientWork(a1->server, i);
            v5 = ClientWork;
            if (ClientWork)
            {
                v6 = 0;
                if (ClientWork->byte9)
                {
                    do
                    {
                        PartyMember = BattleParty_GetPartyMember(v5->party, v6);
                        if (PartyMember && !BattleMon_IsFainted(PartyMember))
                        {
                            ServerControl_SwitchInCore(a1, i, v6, v6);
                        }
                        ++v6;
                    } while (v6 < v5->byte9);
                }
                if (BtlSetup_GetBattleStyle(a1->mainModule) == BTL_STYLE_ROTATION)
                {
                    for (j = 0; j < 3; ++j)
                    {
                        v9 = BattleParty_GetPartyMember(v5->party, j);
                        v10 = (int)v9;
                        if (v9 && !BattleMon_IsFainted(v9))
                        {
                            MainModule_RegisterPokedexSeenFlag(a1->mainModule, i, v10);
                        }
                    }
                }
            }
        }
        // #if DEBUGGING_ALL && DEBUGGING_FIELDEFFECTS
        //         k::Printf("\nCheck 2: Setting up field effects at the start of the battle\n");
        // #endif
        if (ServerControl_AfterSwitchIn(a1))
        {
            return 1;
        }
        return v12;
    }

#pragma endregion

#pragma region SimulationDamageHelpers

    bool checkRetaliate(ServerFlow *a2, int MonID, int turn)
    {
        FaintRecord *record;
        int turnCount;
        int faintedId;
        int loopCount;
        record = Handler_GetFaintRecord(a2);

        turnCount = j_j_FaintRecord_GetCount(record, turn);
        loopCount = 0;

        if (turnCount)
        {
            while (loopCount <= turnCount)
            {
                faintedId = j_j_FaintRecord_GetPokeID(record, turn, loopCount);

                if (MainModule_IsAllyMonID(MonID, faintedId))
                {
#if DEBUGGING_DAMAGECALC && DEBUGGING_ALL
                    // k::Printf("\nSuccessfully checked and triggered the retaliate handler\n");
#endif
                    return true;
                }
                ++loopCount;
            }
        }
        return false;
    }

    int CheckRatio(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon, int MoveID)
    {
        // Reversal and Flail
        if (IsEqual(MoveID, MOVE175_FLAIL) || IsEqual(MoveID, MOVE179_REVERSAL))
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);
            if (Value == 409600)
            {
                return 4096;
            }
            else if (Value < 409600 && Value >= 281600)
            {
                return 8192;
            }
            else if (Value < 281600 && Value >= 145000)
            {
                return 16384;
            }
            else if (Value < 145000 && Value >= 85300)
            {
                return 32768;
            }
            else if (Value < 85300 && Value >= 42700)
            {
                return 40960;
            }
            else if (Value < 42700 && Value >= 17100)
            {
                return 61440;
            }
            else
            {
                return 81920;
            }
        }
        // Water Spout and Eruption
        if (IsEqual(MoveID, MOVE323_WATER_SPOUT) || IsEqual(MoveID, MOVE284_ERUPTION))
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);
            if (Value == 409600)
            {
                return 4096;
            }
            else if (Value < 409600 && Value >= 384000)
            {
                return 3840;
            }
            else if (Value < 384000 && Value >= 358400)
            {
                return 3584;
            }
            else if (Value < 358400 && Value >= 332800)
            {
                return 3328;
            }
            else if (Value < 332800 && Value >= 307200)
            {
                return 3072;
            }
            else if (Value < 307200 && Value >= 281600)
            {
                return 2816;
            }
            else if (Value < 281600 && Value >= 256000)
            {
                return 2560;
            }
            else if (Value < 256000 && Value >= 230400)
            {
                return 2304;
            }
            else if (Value < 230400 && Value >= 204800)
            {
                return 2408;
            }
            else
            {
                return 0;
            }
        }
        // Electro Ball
        if (IsEqual(MoveID, MOVE486_ELECTRO_BALL))
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) > Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        // //k::print("\nCheck #1");
        if (IsEqual(MoveID, MOVE474_VENOSHOCK))
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }

        if (IsEqual(MoveID, MOVE076_SOLAR_BEAM) || IsEqual(MoveID, MOVE554_SOLAR_BLADE))
        {
            if (ServerEvent_GetWeather(a1) != WEATHER_SUN && AttackingMon->HeldItem != IT0271_POWER_HERB && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL122_FLOWER_GIFT)
            {
                return 0;
            }
            return 4096;
        }
        //  Skull Bash and Meteor Beam and Sky Attack
        if (IsEqual(MoveID, MOVE130_SKULL_BASH) || IsEqual(MoveID, MOVE553_METEOR_BEAM) || IsEqual(MoveID, MOVE143_SKY_ATTACK))
        {
            if (AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                if (RandomInRange(0, 100) > 60)
                {
                    return 0;
                }
            }
            return 6144;
        }
        // Electro Shot
        if (IsEqual(MoveID, MOVE193_ELECTRO_SHOT))
        {
            if (ServerEvent_GetWeather(a1) != 2 && AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                if (RandomInRange(0, 100) > 60)
                {
                    return 0;
                }
            }
            return 6144;
        }
        //  Hex, Beat Up, Infernal Parade, Barb Barrage
        if (IsEqual(MoveID, MOVE169_INFERNAL_PARADE) || IsEqual(MoveID, MOVE272_BARB_BARRAGE) || IsEqual(MoveID, MOVE251_BEAT_UP) || IsEqual(MoveID, MOVE506_HEX) || IsEqual(MoveID, MOVE244_BITTER_MALICE))
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        //  Acrobatics
        if (MoveID == MOVE512_ACROBATICS)
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == IT0556_FLYING_GEM)
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        //  All 2 hit moves
        if (IsEqual(MoveID, MOVE003_DOUBLE_SLAP) || IsEqual(MoveID, MOVE022_VINE_WHIPS) || IsEqual(MoveID, MOVE458_DOUBLE_HIT) || IsEqual(MoveID, MOVE024_DOUBLE_KICK) || IsEqual(MoveID, MOVE011_DUAL_WINGBEAT) || IsEqual(MoveID, MOVE041_TWINEEDLE) || IsEqual(MoveID, MOVE155_BONEMERANG) || IsEqual(MoveID, MOVE544_GEAR_GRIND) || IsEqual(MoveID, MOVE530_DUAL_CHOP))
        {
            return 8192;
        }
        //  All 3 hit moves
        if (IsEqual(MoveID, MOVE167_TRIPLE_KICK) || IsEqual(MoveID, MOVE471_TRIPLE_DIVE) || IsEqual(MoveID, MOVE470_TRIPLE_AXEL) || IsEqual(MoveID, MOVE161_TRI_ATTACK))
        {
            return 12288;
        }
        //  Brine
        if (IsEqual(MoveID, MOVE362_BRINE))
        {
            if (BattleMon_GetHPRatio(DefendingMon) <= 204800)
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        if (IsEqual(MoveID, MOVE514_RETALIATE))
        {
            if (checkRetaliate(a1, AttackingMon->ID, 0u))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        // First Impression
        if (IsEqual(MoveID, MOVE373_1ST_IMPRESSION))
        {
            if (BattleMon_GetConditionFlag(AttackingMon, CONDITIONFLAG_ACTIONDONE))
            {
                return 0;
            }
            else
            {
                return 4096;
            }
        }
        //  Facade
        if (IsEqual(MoveID, MOVE263_FACADE))
        {
            if (BattleMon_GetStatus(AttackingMon))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        //  Wake Up Slap and Dream Eater
        if (IsEqual(MoveID, MOVE358_WAKE_UP_SLAP) || IsEqual(MoveID, MOVE138_DREAM_EATER))
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        //  All multihit moves
        if (IsEqual(MoveID, MOVE013_RAZOR_WINDS) || IsEqual(MoveID, MOVE004_COMET_PUNCH) || IsEqual(MoveID, MOVE042_PIN_MISSILE) ||
            IsEqual(MoveID, MOVE131_SPIKE_CANNON) || IsEqual(MoveID, MOVE140_BARRAGE) || IsEqual(MoveID, MOVE154_FURY_SWIPES) || IsEqual(MoveID, MOVE198_BONE_RUSH) ||
            IsEqual(MoveID, MOVE292_ARM_THRUST) || IsEqual(MoveID, MOVE331_BULLET_SEED) || IsEqual(MoveID, MOVE333_ICICLE_SPEAR) || IsEqual(MoveID, MOVE350_ROCK_BLAST) ||
            IsEqual(MoveID, MOVE541_TAIL_SLAP) || IsEqual(MoveID, MOVE378_SCALE_SHOT))
        {
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL092_SKILL_LINK)
            {
                return 20480;
            }
            else if (AttackingMon->HeldItem == IT0317_LOADED_DICE || AttackingMon->HeldItem == IT0312_TERA_DICE)
            {
                return 16384;
            }
            else
            {
                return 8192;
            }
        }
        // Hyper Beam
        if (IsEqual(MoveID, MOVE063_HYPER_BEAM))
        {
            if (BattleMon_GetPreviousMove(AttackingMon) == MOVE063_HYPER_BEAM && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 0;
            }
            else
            {
                return 4096;
            }
        }
        // Giga Impact
        if (IsEqual(MoveID, MOVE416_GIGA_IMPACT))
        {
            if (BattleMon_GetPreviousMove(AttackingMon) == MOVE416_GIGA_IMPACT && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 0;
            }
            else
            {
                return 4096;
            }
        }
        // Stomping Tantrum / Uproar / Seething Chill / Thrash / Temper Flare
        if (IsEqual(MoveID, MOVE493_STOMPIN_TANTRUM) || IsEqual(MoveID, MOVE253_UPROAR) || IsEqual(MoveID, MOVE288_GRUDGE) || IsEqual(MoveID, MOVE218_TEMPER_FLARE) || IsEqual(MoveID, MOVE220_SEETHING_COLD) || IsEqual(MoveID, MOVE037_THRASH))
        {
            if (BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        // Weather Ball / Weather Crash
        if (IsEqual(MoveID, MOVE311_WEATHER_BALL) || IsEqual(MoveID, MOVE271_WEATHER_CRASH))
        {
            if (ServerEvent_GetWeather(a1) > 0 || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL034_CHLOROPHYLL || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL094_SOLAR_POWER || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL122_FLOWER_GIFT)
            {
                return 8192;
            }

            return 4096;
        }
        // Payback, Revenge, and Avalanche
        if (IsEqual(MoveID, MOVE371_PAYBACK) || IsEqual(MoveID, MOVE279_REVENGE) || IsEqual(MoveID, MOVE419_AVALANCHE) || IsEqual(MoveID, MOVE360_GYRO_BALL))
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }
        // Spit Up
        if (IsEqual(MoveID, MOVE255_SPIT_UP))
        {
            if (!PML_ItemIsBerry(AttackingMon->HeldItem))
            {
                return 0;
            }
            else
            {
                return 4096;
            }
        }
        if (IsEqual(MoveID, MOVE282_KNOCK_OFF))
        {
            if (BattleMon_GetHeldItem(DefendingMon) && !HandlerCommon_CheckIfCanStealPokeItem(a1, AttackingMon->ID, DefendingMon->ID))
            {
                return 6144;
            }
            else
            {
                return 4096;
            }
        }
        if (IsEqual(MoveID, MOVE478_POWER_TRIP) || IsEqual(MoveID, MOVE500_STORED_POWER))
        {
            int total;
            int temp;
            total = 0;
            for (int i = 1; i < 8; ++i)
            {
                temp = BattleMon_GetValue(AttackingMon, (BattleMonValue)i) - 6;
                if (temp > 0)
                {
                    total += temp;
                }
            }
            if (total)
            {
                return 4096 + (2048 * total);
            }
        }
        return 4096;
    }

#pragma endregion

#pragma region SimulationDamage

    int THUMB_BRANCH_SAFESTACK_Handler_SimulationDamage(ServerFlow *a1, int a2, int a3, int a4, bool isSimulation, bool something)
    {
        int TypeEffectiveness;   // r6
        BattleMon *DefendingMon; // [sp+14h] [bp-34h]
        BattleMon *AttackingMon; // [sp+18h] [bp-30h]
        __int16 moveParam[20];
        unsigned __int16 v12; // [sp+1Ch] [bp-2Ch] BYREF
        int v14;              // [sp+48h] [bp+0h]
        int v15;              // [sp+4Ch] [bp+4h]
        int v16;
        unsigned int ratio;
        u8 critFlag;
        int v17;
        int isMoldBreaker;
        int a4check;
        AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, a2);
        DefendingMon = PokeCon_GetBattleMon(a1->pokeCon, a3);
        AbilID atkAbility = (AbilID)BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY);
        AbilID defAbility = (AbilID)BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY);
        if (!a4)
        {
            return 0;
        }
#if DAMAGE_CACHE_ENABLED
        v12 = checkCalcTable(a1, AttackingMon, DefendingMon, (MoveID)a4);
        if (v12)
        {
            return v12;
        }
#endif
        isMoldBreaker = HasMoldBreaker(AttackingMon);

        /*
            ----------------------------------------------------------------------------------
            ---------------------------- STATIC DAMAGE MOVES ---------------------------------
            ----------------------------------------------------------------------------------
        */

        if (IsEqual(a4, MOVE101_NIGHT_SHADE) && !BattleMon_HasType(DefendingMon, TYPE_NORMAL))
        {
            return AttackingMon->Level;
        }
        else if (IsEqual(a4, MOVE069_SEISMIC_TOSS) && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || IsEqual(atkAbility, ABIL113_SCRAPPY)))
        {
            return AttackingMon->Level;
        }
        else if (IsEqual(a4, MOVE149_PSYWAVE) && (!BattleMon_HasType(DefendingMon, TYPE_DARK) || IsEqual(atkAbility, ABIL039_INNER_FOCUS)))
        {
            return AttackingMon->Level;
        }
        else if (IsEqual(a4, MOVE162_SUPER_FANG) && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || IsEqual(atkAbility, ABIL113_SCRAPPY)))
        {
            int losthealth = div32(DefendingMon->CurrentHP, 2u);
            if (!losthealth)
            {
                losthealth = 1;
            }
            if (atkAbility == ABIL093_STRONG_JAW)
            {
                return (div32(DefendingMon->CurrentHP, 2u) + div32(DefendingMon->CurrentHP, 4u));
            }
            else
            {
                return losthealth;
            }
        }
        else
        {
            a4check = a4;
        }

        /*
            ----------------------------------------------------------------------------------
            ---------------------------- MOVE REPLACING MOVES --------------------------------
            ----------------------------------------------------------------------------------
        */

        if (!PML_MoveIsDamaging(a4check))
        {
            int actualMove;

            // Copycat
            if (IsEqual(a4check, MOVE383_COPYCAT) && (atkAbility || AttackingMon->HeldItem == IT0136_TRICKSTER_HERB || (Handler_CalculateSpeed(a1, AttackingMon, 0) > Handler_CalculateSpeed(a1, DefendingMon, 0))))
            {
                actualMove = Handler_GetPrevUsedMove(a1);
                if (actualMove && !j_j_IsNotAllowedCopycatMove(actualMove))
                {
                    a4check = actualMove;
                }
                else
                {
                    return 0;
                }
            }
            // Nature Power
            else if (IsEqual(a4check, MOVE267_NATURE_POWER))
            {
                int BattleTerrain = Handler_GetBattleTerrain(a1);

                // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

                if (BattleTerrain == 5u)
                {
                    a4check = 402;
                }
                else if (BattleTerrain == 11u)
                {
                    a4check = 89;
                }
                else if (BattleTerrain == 0xCu)
                {
                    a4check = 56;
                }
                else if (BattleTerrain == 7u)
                {
                    a4check = 59;
                }
                else if (BattleTerrain == 9u)
                {
                    a4check = 426;
                }
                else if (BattleTerrain == 0xAu)
                {
                    a4check = 157;
                }
                else if (BattleTerrain == 0xDu)
                {
                    a4check = 58;
                }
                else
                {
                    a4check = 161;
                }
            }
            else
            {
                return 0;
            }
        }

        ++a1->simulationCounter;

        if (BattleMon_IsIllusionEnabled(DefendingMon))
        {

            DefendingMon = MainModule_GetIllusionDisguise(a1->mainModule, (int)a1->pokeCon, (int)DefendingMon);
        }

        TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, a4check);

        ratio = CheckRatio(a1, AttackingMon, DefendingMon, a4check);

        ServerEvent_GetMoveParam(a1, a4check, (int)AttackingMon, (MoveParam *)moveParam);

        /*
            ----------------------------------------------------------------------------------
            ---------------------------- TYPE CHANGING MOVES ---------------------------------
            ----------------------------------------------------------------------------------
        */

        if (IsEqual(a4check, MOVE165_STRUGGLE))
        {
            ((MoveParam *)moveParam)->moveType = 18;
        }
        int fakemove = 0;
        if ((IsEqual(a4check, MOVE311_WEATHER_BALL) || IsEqual(a4check, MOVE271_WEATHER_CRASH)))
        {
            v17 = ServerEvent_GetWeather(a1);
            if (v17 == 1 || atkAbility == ABIL034_CHLOROPHYLL || atkAbility == ABIL122_FLOWER_GIFT || atkAbility == ABIL094_SOLAR_POWER)
            {
                fakemove = MOVE053_FLAMETHROWER;
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            else if (v17 == 2)
            {
                fakemove = MOVE057_SURF;
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            else if (v17 == 3)
            {
                fakemove = MOVE058_ICE_BEAM;
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            else if (v17 == 4)
            {
                fakemove = MOVE157_ROCK_SLIDE;
                ((MoveParam *)moveParam)->moveType = TYPE_ROCK;
            }
        }

        if (IsEqual(a4check, MOVE363_NATURAL_GIFT))
        {
            if (PML_ItemIsBerry(BattleMon_GetHeldItem(AttackingMon)))
            {
                Types Type = (Types)ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_TYPE);

                if (IsEqual(Type, TYPE_FIGHTING))
                {
                    fakemove = MOVE280_BRICK_BREAK;
                }
                else if (IsEqual(Type, TYPE_FLYING))
                {
                    fakemove = MOVE332_AERIAL_ACE;
                }
                else if (IsEqual(Type, TYPE_FAIRY))
                {
                    fakemove = MOVE296_MOONBLAST;
                }
                else if (IsEqual(Type, TYPE_FIRE))
                {
                    fakemove = MOVE053_FLAMETHROWER;
                }
                else if (IsEqual(Type, TYPE_WATER))
                {
                    fakemove = MOVE057_SURF;
                }
                else if (IsEqual(Type, TYPE_ELECTRIC))
                {
                    fakemove = MOVE085_THUNDERBOLT;
                }
                else if (IsEqual(Type, TYPE_ROCK))
                {
                    fakemove = MOVE157_ROCK_SLIDE;
                }
                else if (IsEqual(Type, TYPE_GROUND))
                {
                    fakemove = MOVE089_EARTHQUAKE;
                }
                else if (IsEqual(Type, TYPE_STEEL))
                {
                    fakemove = MOVE360_GYRO_BALL;
                }
                else if (IsEqual(Type, TYPE_DRAGON))
                {
                    fakemove = MOVE337_DRAGON_CLAW;
                }
                else if (IsEqual(Type, TYPE_ICE))
                {
                    fakemove = MOVE058_ICE_BEAM;
                }
                else if (IsEqual(Type, TYPE_BUG))
                {
                    fakemove = MOVE405_BUG_BUZZ;
                }
                else if (IsEqual(Type, TYPE_POISON))
                {
                    fakemove = MOVE440_CROSS_POISON;
                }
                else if (IsEqual(Type, TYPE_PSYCHIC))
                {
                    fakemove = MOVE060_PSYBEAM;
                }
                else if (IsEqual(Type, TYPE_GHOST))
                {
                    fakemove = MOVE247_SHADOW_BALL;
                }
                else if (IsEqual(Type, TYPE_DARK))
                {
                    fakemove = MOVE242_CRUNCH;
                }
                else if (IsEqual(Type, TYPE_GRASS))
                {
                    fakemove = MOVE379_PETAL_BLIZZARD;
                }
                ((MoveParam *)moveParam)->moveType = Type;

                if (90 == ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_POWER))
                {
                    ratio = 4608;
                }
                if (100 == ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_POWER))
                {
                    ratio = 5120;
                }
            }
        }

        if (IsEqual(a4check, MOVE546_TECHNO_BLAST))
        {
            if (IsEqual(AttackingMon->HeldItem, IT0119_CHILL_DRIVE))
            {
                fakemove = MOVE058_ICE_BEAM;
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            if (IsEqual(AttackingMon->HeldItem, IT0116_DOUSE_DRIVE))
            {
                fakemove = MOVE057_SURF;
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            if (IsEqual(AttackingMon->HeldItem, IT0118_BURN_DRIVE))
            {
                fakemove = MOVE053_FLAMETHROWER;
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            if (IsEqual(AttackingMon->HeldItem, IT0117_SHOCK_DRIVE))
            {
                fakemove = MOVE085_THUNDERBOLT;
                ((MoveParam *)moveParam)->moveType = TYPE_ELECTRIC;
            }
        }

        if (fakemove)
        {

            TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, fakemove);
        }

        /*
            ----------------------------------------------------------------------------------
            ----------------------- EFFECTIVENESS BYPASSING MOVES ----------------------------
            ----------------------------------------------------------------------------------
        */

        if (IsEqual(a4check, MOVE547_RELIC_SONG) || IsEqual(a4check, MOVE357_FREEZE_DRY) || IsEqual(a4check, MOVE533_SACRED_SWORD))
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon));
        }

        if (IsEqual(a4check, MOVE327_SKY_UPPERCUT))
        {
            TypeEffectiveness = EvaluateTypeEffectivenesssForFighting(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon), (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL113_SCRAPPY));
        }

        if (IsEqual(a4check, MOVE498_CHIP_AWAY))
        {
            TypeEffectiveness = 3;
        }

        /*
            ----------------------------------------------------------------------------------
            --------------------------------- IMMUNITIES -------------------------------------
            ----------------------------------------------------------------------------------
        */

        if (!isMoldBreaker)
        {
            if (((MoveParam *)moveParam)->moveType == TYPE_FIRE && (IsEqual(defAbility, ABIL021_WELL_BAKED_BODY) || IsEqual(defAbility, ABIL018_FLASH_FIRE)))
            {
                ratio = 0;
            }
            if ((IsEqual(defAbility, ABIL015_THUNDER_ARMOR) || IsEqual(defAbility, ABIL031_LIGHTNING_ROD) || IsEqual(defAbility, ABIL078_MOTOR_DRIVE) || IsEqual(defAbility, ABIL010_VOLT_ABSORB)) && ((MoveParam *)moveParam)->moveType == TYPE_ELECTRIC)
            {
                ratio = 0;
            }
            if ((IsEqual(defAbility, ABIL114_STORM_DRAIN) || IsEqual(defAbility, ABIL087_DRY_SKIN) || IsEqual(defAbility, ABIL011_WATER_ABSORB)) && ((MoveParam *)moveParam)->moveType == TYPE_WATER)
            {
                ratio = 0;
            }
            if (IsEqual(defAbility, ABIL157_SAP_SIPPER) && ((MoveParam *)moveParam)->moveType == TYPE_GRASS)
            {
                ratio = 0;
            }
            if (IsEqual(defAbility, ABIL026_LEVITATE) && ((MoveParam *)moveParam)->moveType == TYPE_GROUND)
            {
                ratio = 0;
            }
            if (IsEqual(defAbility, ABIL006_BULLETPROOF) && SEARCH_ARRAY(BulletproofMoves, a4check))
            {
                ratio = 0;
            }
            if (IsEqual(defAbility, ABIL051_WIND_RIDER) && SEARCH_ARRAY(WindMoves, a4check))
            {
                ratio = 0;
            }
            if (IsEqual(defAbility, ABIL043_AMPLIFIER) && getMoveFlag(a4check, FLAG_SOUND))
            {
                ratio = 0;
            }
        }

        /*
            ----------------------------------------------------------------------------------
            --------------------------------- CRIT CHECK -------------------------------------
            ----------------------------------------------------------------------------------
        */

        if (SEARCH_ARRAY(autoCritMoves, a4check))
        {
            if (BattleMon_GetConditionFlag(DefendingMon, CONDITIONFLAG_DEFENSECURL))
            {
                critFlag = 0;
            }
            else if (Handler_IsSideEffectActive(a1, GetSideFromMonID(BattleEventVar_GetValue(VAR_DEFENDING_MON)), 5))
            {
                critFlag = 0;
            }
            else if (IsEqual(defAbility, ABIL004_BATTLE_ARMOR) || IsEqual(defAbility, ABIL075_SHELL_ARMOR))
            {
                if (!isMoldBreaker)
                {
                    critFlag = 0;
                }
                else
                {
                    critFlag = 1;
                }
            }
            critFlag = 1;
        }
        else
        {
            critFlag = 0;
        }

        /*
            ----------------------------------------------------------------------------------
            --------------------------------- DAMAGE CALC ------------------------------------
            ----------------------------------------------------------------------------------
        */

        ServerEvent_CalcDamage(
            a1,
            AttackingMon,
            DefendingMon,
            (MoveParam *)moveParam,
            TypeEffectiveness,
            ratio,
            critFlag,
            isSimulation == 0,
            &v12);
        --a1->simulationCounter;

        // k::Printf("\nSimulated Damage for move %d is %d\n", a4check, v12);
#if DAMAGE_CACHE_ENABLED
        saveToCalcTable(a1, AttackingMon, DefendingMon, (MoveID)a4, v12);
#endif
        /*
            ----------------------------------------------------------------------------------
            ------------------------------- PURSUIT LOGIC ------------------------------------
            ----------------------------------------------------------------------------------
        */

        if (IsEqual(a4check, MOVE228_PURSUIT) && (v12 << 1) >= DefendingMon->CurrentHP)
        {

            if (RandomInRange(1, 100) >= 60)
            {
                v12 <<= 1;
            }
        }

        return v12;
    }

#pragma endregion

#pragma region SwitchInAIHelpers

    // int randomvalue = BattleMon_GetHeldItem(AttackingMon);
    int checkForTechnician(BattleMon *AttackingMon, int MoveID, unsigned int a3)
    {
        if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL101_TECHNICIAN)
        {
            if (PML_MoveGetBasePower(MoveID) <= 60)
            {
                return a3 + (a3 >> 1);
            }
        }
        return a3;
    }

    int checkForAbilityAndItemBPChanges(BattleMon *AttackingMon, BattleMon *DefendingMon, int Type, int TypeEffectivenessVsMon, unsigned int a4)
    {
        int value;
        value = a4;

        AbilID defAbility = (AbilID)BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY);
        AbilID atkAbility = (AbilID)BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY);
        if (!HasMoldBreaker(AttackingMon))
        {

            // Heatproof
            if (defAbility == ABIL085_HEATPROOF && Type == TYPE_FIRE)
            {
                value >>= 2;
            }

            // Thick Fat
            if (defAbility == ABIL047_THICK_FAT && (Type == TYPE_FIRE || Type == TYPE_ICE))
            {
                value >>= 1;
            }

            // Dry Skin
            if ((defAbility == ABIL087_DRY_SKIN || defAbility == ABIL017_FLUFFY) && Type == TYPE_FIRE)
            {
                value <<= 1;
            }

            // Toxic Boost
            if (defAbility == ABIL137_TOXIC_BOOST && Type == TYPE_POISON)
            {
                value >>= 1;
            }

            if ((atkAbility == ABIL110_TENACITY) && TypeEffectivenessVsMon < 3)
            {
                value <<= 1;
            }

            // Swift Swim
            if (defAbility == ABIL033_SWIFT_SWIM && Type == TYPE_WATER)
            {
                value >>= 1;
            }

            // Slush Rush
            if (defAbility == ABIL077_SLUSH_RUSH && Type == TYPE_ICE)
            {
                value >>= 1;
            }

            // Sand Rush
            if (defAbility == ABIL146_SAND_RUSH && Type == TYPE_ROCK)
            {
                value >>= 1;
            }

            // Justified
            if (defAbility == ABIL154_JUSTIFIED && Type == TYPE_DARK)
            {
                value >>= 1;
            }
        }

        return value;
    }

    int checkForBPChanges(BattleMon *AttackingMon, BattleMon *DefendingMon, int MoveID, unsigned int a4, BtlClientWk *work)
    {
        unsigned int value;
        ServerFlow *server = BattleServer_GetServerFlow(work->mainModule->server);
        int isMoldBreaker = HasMoldBreaker(AttackingMon);
        value = a4;

        if (IsEqual(MoveID, MOVE474_VENOSHOCK))
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        // Meteor Beam, Skull Bash, Sky Attack
        if (IsEqual(MoveID, MOVE130_SKULL_BASH) || IsEqual(MoveID, MOVE553_METEOR_BEAM) || IsEqual(MoveID, MOVE143_SKY_ATTACK))
        {
            if (AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return value >> 1;
            }
            else
            {
                return value;
            }
        }

        // Reversal and Flail
        // Set base power to 20
        if (IsEqual(MoveID, MOVE175_FLAIL) || IsEqual(MoveID, MOVE179_REVERSAL))
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return value;
            }
            else if (Value >= 281600)
            {
                return value << 1;
            }
            else if (Value < 281600 && Value >= 145000)
            {
                return value << 2;
            }
            else if (Value < 145000 && Value >= 85300)
            {
                return value << 3;
            }
            else if (Value < 85300 && Value >= 42700)
            {
                return (value << 3) + (value << 1);
            }
            else if (Value < 42700 && Value >= 17100)
            {
                return (value << 3) + (value << 2) + (value << 1) + value;
            }
            else
            {
                return (value << 4) + (value << 2);
            }
        }

        // Water Spout and Eruption
        if (IsEqual(MoveID, MOVE323_WATER_SPOUT) || IsEqual(MoveID, MOVE284_ERUPTION))
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return value;
            }
            else if (Value < 409600 && Value >= 384000)
            {
                return (value >> 4) * 15;
            }
            else if (Value < 384000 && Value >= 358400)
            {
                return (value >> 3) * 7;
            }
            else if (Value < 358400 && Value >= 332800)
            {
                return (value >> 4) * 13;
            }
            else if (Value < 332800 && Value >= 307200)
            {
                return (value >> 3) * 6;
            }
            else if (Value < 307200 && Value >= 281600)
            {
                return (value >> 4) * 11;
            }
            else if (Value < 281600 && Value >= 256000)
            {
                return (value >> 3) * 5;
            }
            else if (Value < 256000 && Value >= 230400)
            {
                return (value >> 4) * 9;
            }
            else if (Value < 230400 && Value >= 204800)
            {
                return (value >> 1);
            }
            else
            {
                return 0;
            }
        }

        // Electro Ball
        if (IsEqual(MoveID, MOVE486_ELECTRO_BALL))
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) > Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        // Electro Shot
        if (IsEqual(MoveID, MOVE193_ELECTRO_SHOT))
        {
            if (BattleField_GetWeather() != 2 && AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return value >> 1;
            }
            else
            {
                return value;
            }
        }

        // Solarbeam and Solar Blade
        if (IsEqual(MoveID, MOVE076_SOLAR_BEAM) || IsEqual(MoveID, MOVE554_SOLAR_BLADE))
        {
            if (BattleField_GetWeather() != 1 && AttackingMon->HeldItem != IT0271_POWER_HERB && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL122_FLOWER_GIFT)
            {
                return value >> 1;
            }
            else
            {
                return value;
            }
        }

        if (IsEqual(MoveID, MOVE506_HEX) || IsEqual(MoveID, MOVE272_BARB_BARRAGE) || IsEqual(MoveID, MOVE251_BEAT_UP) || IsEqual(MoveID, MOVE244_BITTER_MALICE) || IsEqual(MoveID, MOVE169_INFERNAL_PARADE))
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        // Acrobatics
        if (IsEqual(MoveID, MOVE512_ACROBATICS))
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == IT0556_FLYING_GEM)
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        if (IsEqual(MoveID, MOVE003_DOUBLE_SLAP) || IsEqual(MoveID, MOVE022_VINE_WHIPS) || IsEqual(MoveID, MOVE458_DOUBLE_HIT) || IsEqual(MoveID, MOVE024_DOUBLE_KICK) || IsEqual(MoveID, MOVE011_DUAL_WINGBEAT) || IsEqual(MoveID, MOVE041_TWINEEDLE) || IsEqual(MoveID, MOVE155_BONEMERANG) || IsEqual(MoveID, MOVE544_GEAR_GRIND) || IsEqual(MoveID, MOVE530_DUAL_CHOP))
        {
            return value << 1;
        }

        //  All 3 hit moves
        if (IsEqual(MoveID, MOVE167_TRIPLE_KICK) || IsEqual(MoveID, MOVE470_TRIPLE_AXEL) || IsEqual(MoveID, MOVE471_TRIPLE_DIVE) || IsEqual(MoveID, MOVE161_TRI_ATTACK))
        {
            return value + (value << 1);
        }

        // Wake Up Slap and Dream Eater
        if (IsEqual(MoveID, MOVE138_DREAM_EATER) || IsEqual(MoveID, MOVE358_WAKE_UP_SLAP))
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        if (IsEqual(MoveID, MOVE514_RETALIATE))
        {
            if (checkRetaliate(server, AttackingMon->ID, 0))
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        // autocrit moves
        if (SEARCH_ARRAY(autoCritMoves, MoveID))
        {
            if (BattleMon_GetConditionFlag(DefendingMon, CONDITIONFLAG_DEFENSECURL))
            {
                return value;
            }
            if (Handler_IsSideEffectActive(server, GetSideFromMonID(BattleMon_GetID(DefendingMon)), 5))
            {
                return value;
            }
            if (!isMoldBreaker && (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL075_SHELL_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL004_BATTLE_ARMOR))
            {
                return value;
            }
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL097_SNIPER)
            {
                return value + (value << 1);
            }
            else
            {
                return value << 1;
            }
        }

        if (IsEqual(MoveID, MOVE013_RAZOR_WINDS) || IsEqual(MoveID, MOVE004_COMET_PUNCH) || IsEqual(MoveID, MOVE042_PIN_MISSILE) ||
            IsEqual(MoveID, MOVE131_SPIKE_CANNON) || IsEqual(MoveID, MOVE140_BARRAGE) || IsEqual(MoveID, MOVE154_FURY_SWIPES) || IsEqual(MoveID, MOVE198_BONE_RUSH) ||
            IsEqual(MoveID, MOVE292_ARM_THRUST) || IsEqual(MoveID, MOVE331_BULLET_SEED) || IsEqual(MoveID, MOVE333_ICICLE_SPEAR) || IsEqual(MoveID, MOVE350_ROCK_BLAST) ||
            IsEqual(MoveID, MOVE541_TAIL_SLAP) || IsEqual(MoveID, MOVE378_SCALE_SHOT))
        {
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL092_SKILL_LINK)
            {
                return (value << 2) + (value << 1);
            }
            else if (AttackingMon->HeldItem == IT0317_LOADED_DICE)
            {
                return value << 2;
            }
            else
            {
                return value << 1;
            }
        }

        if (IsEqual(MoveID, MOVE360_GYRO_BALL) || IsEqual(MoveID, MOVE279_REVENGE) || IsEqual(MoveID, MOVE419_AVALANCHE) || IsEqual(MoveID, MOVE371_PAYBACK))
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) < Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value << 1;
            }
            else
            {
                return value;
            }
        }

        if (IsEqual(MoveID, MOVE282_KNOCK_OFF))
        {
            if (BattleMon_GetHeldItem(DefendingMon) && !HandlerCommon_CheckIfCanStealPokeItem(server, AttackingMon->ID, DefendingMon->ID))
            {
                return value + (value >> 1);
            }
            else
            {
                return value;
            }
        }

        if (IsEqual(MoveID, MOVE264_FOCUS_PUNCH))
        {
            return (value >> 1);
        }

        return value;
    }

    int checkForSTAB(BattleMon *a1, int a2, unsigned int a3)
    {
        if (BattleMon_HasType(a1, (Types)a2))
        {
            return a3 + (a3 >> 1);
        }
        else if (BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL145_SAVANT)
        {
            return a3 + (a3 >> 1);
        }
        else if (BattleMon_CheckIfMoveCondition(a1, CONDITION_TERA) || SEARCH_ARRAY(teraItems, a1->HeldItem))
        {
            if (a2 == PML_PersonalGetParamSingle(a1->Species, a1->Form, Personal_Type1) || a2 == PML_PersonalGetParamSingle(a1->Species, a1->Form, Personal_Type2))
            {
                return a3 + (a3 >> 1);
            }
            if (a2 == PML_MoveGetType(Move_GetID(a1, 0)))
            {
                return a3 + (a3 >> 1);
            }
            else
            {
                return a3;
            }
        }
        else
        {
            return a3;
        }
    }

    bool CheckIfImmuneAbility(int Type, int MoveID, BattleMon *DefendingMon)
    {
        int ability = BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY);

        if (Type == TYPE_WATER && (ability == ABIL114_STORM_DRAIN || ability == ABIL011_WATER_ABSORB || ability == ABIL087_DRY_SKIN))
        {
            return true;
        }
        if (Type == TYPE_GROUND && (ability == ABIL026_LEVITATE))
        {
            return true;
        }
        if (Type == TYPE_ELECTRIC && (ability == ABIL010_VOLT_ABSORB || ability == ABIL015_THUNDER_ARMOR || ability == ABIL078_MOTOR_DRIVE || ability == ABIL031_LIGHTNING_ROD))
        {
            return true;
        }
        if (Type == TYPE_GRASS && (ability == ABIL157_SAP_SIPPER))
        {
            return true;
        }
        if (Type == TYPE_FIRE && ((ability == ABIL018_FLASH_FIRE) || ability == ABIL021_WELL_BAKED_BODY))
        {
            return true;
        }
        if (!MoveID)
        {
            return false;
        }
        if (ability == ABIL043_AMPLIFIER && getMoveFlag(MoveID, FLAG_SOUND))
        {
            return true;
        }
        if (ability == ABIL006_BULLETPROOF && SEARCH_ARRAY(BulletproofMoves, MoveID))
        {
            return true;
        }
        if (ability == ABIL051_WIND_RIDER && SEARCH_ARRAY(WindMoves, MoveID))
        {
            return true;
        }
        return false;
    }

    // This function alters the switch-in AI based on defensive matchups.
    // It does not check moves; instead it checks typings
    // If the attacker is weak to either of the defender's types, applies a negative modifier. If the defender is 4x weak, it applies a massive modifier.
    // If the attacker is resistant or immune to both of the target's types, applies a positive modifer.
    // Accounts for Tera
    int checkForMatchup(BattleMon *attackingMon, BattleMon *defendingMon, unsigned int a3)
    {
        int defenderType1;
        int defenderType2;
        u8 defenderType1Effectiveness;
        u8 defenderType2Effectiveness;
        int attackerType;
        defenderType1 = PokeTypePair_GetType1(BattleMon_GetPokeType(defendingMon));
        defenderType2 = PokeTypePair_GetType2(BattleMon_GetPokeType(defendingMon));

        // Checks for Terastalization.
        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_TERA) || SEARCH_ARRAY(teraItems, attackingMon->HeldItem))
        {
            attackerType = PML_MoveGetType(Move_GetID(attackingMon, 0));
        }
        else
        {
            attackerType = BattleMon_GetPokeType(attackingMon);
        }

        defenderType1Effectiveness = (CheckIfImmuneAbility(defenderType1, 0, attackingMon)) ? 0 : GetTypeEffectivenessVsMon(defenderType1, attackerType);
        defenderType2Effectiveness = (CheckIfImmuneAbility(defenderType2, 0, attackingMon)) ? 0 : GetTypeEffectivenessVsMon(defenderType2, attackerType);

        if (defenderType1Effectiveness == 5 || defenderType2Effectiveness == 5)
        {
            // If the mon is 4x weak to either of the target's types, halves the seen BP.
            return (a3 >> 1);
        }
        if (defenderType1Effectiveness == 4 || defenderType2Effectiveness == 4)
        {
            // If the mon is 2x weak to either of the target's types, removes a quarter of the seen BP
            return (a3 >> 1) + (a3 >> 2);
        }
        if (defenderType1Effectiveness <= 1 && defenderType2Effectiveness <= 1)
        {
            // If the target heavily resists or is 4x immune to both of the target's types, boosts the BP by 50%
            return a3 + (a3 >> 1);
        }
        if (defenderType1Effectiveness <= 2 && defenderType2Effectiveness <= 2)
        {
            // If the mon at least resists both of the target's types
            return a3 + (a3 >> 2);
        }
        return a3;
    }
#pragma endregion

#pragma region SwitchInAI

#if DEBUGGING_ILLUSION

    void copyArray(u8 *arr, u8 *arrCopy)
    {
        for (int i = 0; i < 28; i++)
        {
            arrCopy[i] = arr[i];
        }
    }

    int illusionMonId;
    unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
    {
        unsigned int v5;    // r5
        BattleMon *MonData; // r6
        int ID;             // r4
        AbilID atkAbility;
        AbilID defAbility;
        unsigned int BasePower;              // r4
        unsigned int TypeEffectivenessVsMon; // r0
        unsigned int v10;                    // r0
        unsigned int result;                 // r0
        unsigned int j;                      // r5
        unsigned int k;                      // r6
        unsigned int v14;                    // r1
        unsigned int v15;                    // r0
        unsigned int v18;
        int randomvalue;
        u8 v16;                 // r1
        int Type;               // [sp+8h] [bp-38h]
        unsigned int MoveCount; // [sp+Ch] [bp-34h]
        unsigned int i;         // [sp+10h] [bp-30h]
        int PokeType;           // [sp+14h] [bp-2Ch]
        __int16 v23[6];         // [sp+1Ch] [bp-24h]

        unsigned int currentTarget;
        __int16 defenderPos;
        int numTargets;
        u8 defendingAllies[5];
        int currentTargetPosition;
        __int16 v23_temp[6];
        BattleMon *defendingMonChecked;

        if (getSwitchSetting() == 0)
        {
            numTargets = 1;
        }
        else
        {
            defenderPos = a1->myChangePokePos[0]; // MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, a4->ID);
            // k::Printf("Defender Pos: %d\n", defenderPos);
            numTargets = MainModule_ExpandExistPokeID(a1->mainModule, a1->pokeCon, defenderPos | 0x100, defendingAllies);
        }

        for (currentTarget = 0; currentTarget < numTargets; currentTarget++)
        {
            if (getSwitchSetting() == 0)
            {
                defendingMonChecked = a4;
            }
            else
            {
                currentTargetPosition = defendingAllies[currentTarget];
                defendingMonChecked = PokeCon_GetBattleMon(a1->pokeCon, currentTargetPosition);
            }
            PokeType = BattleMon_GetPokeType(defendingMonChecked);
            defAbility = (AbilID)BattleMon_GetValue(defendingMonChecked, VALUE_EFFECTIVE_ABILITY);

            for (i = 0; i < a3; i = (i + 1))
            {
                v5 = 0;
                v23_temp[i] = 0;
                MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
                atkAbility = (AbilID)BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY);
                if (!BattleMon_IsFainted(MonData))
                {
                    MoveCount = BattleMon_GetMoveCount(MonData);
                    if (MoveCount)
                    {
                        do
                        {
                            if (Move_GetPP(MonData, v5))
                            {
                                ID = Move_GetID(MonData, v5);

                                if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
                                {
                                    Type = PML_MoveGetType(ID);
                                    BasePower = PML_MoveGetBasePower(ID);

                                    // Weather Ball Checks
                                    if (ID == MOVE267_NATURE_POWER)
                                    {
                                        int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

                                        if (BattleTerrain == 5u)
                                        {
                                            ID = 402;
                                        }
                                        else if (BattleTerrain == 11u)
                                        {
                                            ID = 89;
                                        }
                                        else if (BattleTerrain == 0xCu)
                                        {
                                            ID = 56;
                                        }
                                        else if (BattleTerrain == 7u)
                                        {
                                            ID = 59;
                                        }
                                        else if (BattleTerrain == 9u)
                                        {
                                            ID = 426;
                                        }
                                        else if (BattleTerrain == 0xAu)
                                        {
                                            ID = 157;
                                        }
                                        else if (BattleTerrain == 0xDu)
                                        {
                                            ID = 58;
                                        }
                                        else
                                        {
                                            ID = 161;
                                        }
                                    }

                                    if (atkAbility == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_ELECTRIC;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }
                                    if (atkAbility == ABIL105_MOISTURIZE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_WATER;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }
                                    if (atkAbility == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_ICE;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }
                                    if (atkAbility == ABIL060_AERILATE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_FLYING;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }
                                    if (atkAbility == ABIL040_PIXILATE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_FAIRY;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }
                                    if (atkAbility == ABIL096_NORMALIZE)
                                    {
                                        Type = TYPE_NORMAL;
                                    }

                                    if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
                                    {
                                        Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);
                                        BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
                                    }

                                    // Weather Ball Checks
                                    if (ID == MOVE311_WEATHER_BALL || ID == MOVE271_WEATHER_CRASH)
                                    {

                                        v18 = BattleField_GetWeather();
                                        if (v18 != 0)
                                        {
                                            BasePower = 100;
                                        }
                                        if (v18 == 1 || atkAbility == ABIL094_SOLAR_POWER || atkAbility == ABIL034_CHLOROPHYLL || atkAbility == ABIL122_FLOWER_GIFT)
                                        {
                                            BasePower = 100;
                                            Type = TYPE_FIRE;
                                        }
                                        else if (v18 == 2)
                                        {
                                            Type = TYPE_WATER;
                                        }
                                        else if (v18 == 3)
                                        {
                                            Type = TYPE_ICE;
                                        }
                                        else if (v18 == 4)
                                        {
                                            Type = TYPE_ROCK;
                                        }
                                    }

                                    if (ID == MOVE546_TECHNO_BLAST)
                                    {
                                        if (MonData->HeldItem == IT0119_CHILL_DRIVE)
                                        {
                                            Type = TYPE_ICE;
                                        }
                                        if (MonData->HeldItem == IT0116_DOUSE_DRIVE)
                                        {
                                            Type = TYPE_WATER;
                                        }
                                        if (MonData->HeldItem == IT0118_BURN_DRIVE)
                                        {
                                            Type = TYPE_FIRE;
                                        }
                                        if (MonData->HeldItem == IT0117_SHOCK_DRIVE)
                                        {
                                            Type = TYPE_ELECTRIC;
                                        }
                                    }

                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);

                                    if (atkAbility == ABIL113_SCRAPPY && (Type == TYPE_NORMAL || Type == TYPE_FIGHTING))
                                    {
                                        TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    }
                                    if (ID == MOVE357_FREEZE_DRY || ID == MOVE547_RELIC_SONG || ID == MOVE533_SACRED_SWORD)
                                    {
                                        TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    }
                                    if ((Type == TYPE_POISON && atkAbility == ABIL007_CORROSION) || (Type == TYPE_PSYCHIC && atkAbility == ABIL039_INNER_FOCUS))
                                    {
                                        TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    }

                                    if (ID == MOVE327_SKY_UPPERCUT)
                                    {
                                        TypeEffectivenessVsMon = EvaluateTypeEffectivenesssForFighting(Type, PokeType, (atkAbility == ABIL113_SCRAPPY));
                                    }

                                    if (ID == MOVE498_CHIP_AWAY)
                                    {
                                        TypeEffectivenessVsMon = 3;
                                    }

                                    if (atkAbility == ABIL096_NORMALIZE && ID != MOVE363_NATURAL_GIFT && ID != MOVE546_TECHNO_BLAST && ID != MOVE311_WEATHER_BALL && ID != MOVE271_WEATHER_CRASH)
                                    {
                                        TypeEffectivenessVsMon = 3;
                                    }

                                    if (!HasMoldBreaker(MonData) && CheckIfImmuneAbility(Type, ID, defendingMonChecked))
                                    {
                                        TypeEffectivenessVsMon = 0;
                                    }

                                    if (TypeEffectivenessVsMon == 0)
                                    {
                                        BasePower = 0;
                                    }
                                    else if (TypeEffectivenessVsMon == 1)
                                    {
                                        v10 = BasePower << 14;
                                    }
                                    else if (TypeEffectivenessVsMon == 2)
                                    {
                                        v10 = BasePower << 15;
                                    }
                                    else if (TypeEffectivenessVsMon == 3)
                                    {
                                        v10 = BasePower << 16;
                                    }
                                    else if (TypeEffectivenessVsMon == 4)
                                    {
                                        v10 = BasePower << 17;
                                    }
                                    else if (TypeEffectivenessVsMon == 5)
                                    {
                                        v10 = BasePower << 18;
                                    }
                                    else
                                    {
                                    }

                                    if (BasePower > 0)
                                    {

                                        v10 = checkForBPChanges(MonData, defendingMonChecked, ID, v10, a1);

                                        v10 = checkForTechnician(MonData, ID, v10);

                                        v10 = checkForSTAB(MonData, Type, v10);
#if SWITCH_AI_CHANGES
                                        v10 = checkForMatchup(MonData, defendingMonChecked, v10);
#endif
                                        v10 = checkForAbilityAndItemBPChanges(MonData, defendingMonChecked, Type, TypeEffectivenessVsMon, v10);

                                        BasePower = HIWORD(v10);
                                    }

                                    if (v23[i] < BasePower)
                                    {
                                        v23[i] = BasePower;
                                    }
                                }
                            }
                            v5 = (v5 + 1);
                        } while (v5 < MoveCount);
                        v23[i] += v23_temp[i];
                    }
                }
            }
        }
        result = a3;
        for (j = 0; j < a3; result = a3)
        {
            for (k = (j + 1); k < a3; k = (k + 1))
            {
                v14 = v23[k];
                v15 = v23[j];
                if (v15 < v14)
                {
                    v23[j] = v14;
                    v23[k] = v15;
                    v16 = a2[j];
                    a2[j] = a2[k];
                    a2[k] = v16;
                }
            }
            j = (unsigned __int8)(j + 1);
        }

        if (a3 > 1)
        {
            if (BattleMon_GetValue(BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[0]), VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
            {
                illusionMonId = a2[1];
            }
            else
            {
                illusionMonId = a2[0];
            }
        }
        else
        {
            illusionMonId = a2[0];
        }

        return result;
    }
#endif
#if TESTING_DOUBLES_SWITCH_AI
    BattleMon *THUMB_BRANCH_SwitchAI_DetermineOpponent(BtlClientWk *a1, __int16 a2)
    {
        __int64 Count;          // r4
        u64 v4;             // r2
        unsigned __int8 v5; // r3
        u8 a4[4];           // [sp+0h] [bp-18h] BYREF

        int i;
        int lowestHealthRatio;
        int currentHealthRatio;
        BattleMon *currentMon;
        int lowestHealthRatioIndex;
        lowestHealthRatio = 500000;
        lowestHealthRatioIndex = 1000;

        if (getSwitchSetting() == 1)
        {
            BattleStyle battleStyle;
            battleStyle = (BattleStyle)BtlSetup_GetBattleStyle(a1->mainModule);
            int OppositeEnemyPos;
            OppositeEnemyPos = sub_219C508(battleStyle, a2);
            currentMon = PokeCon_GetFrontPokeData(a1->pokeCon, OppositeEnemyPos);
            return PokeCon_GetFrontPokeData(a1->pokeCon, OppositeEnemyPos);
        }
        else if (getSwitchSetting() == 2)
        {
            Count = MainModule_ExpandExistPokeID(a1->mainModule, a1->pokeCon, a2 | 0x100, a4);
            if (!Count)
            {
                return 0;
            }
            for (int i = 0; i < Count; i++)
            {
                currentMon = PokeCon_GetBattleMon(a1->pokeCon, a4[i]);
                currentHealthRatio = BattleMon_GetHPRatio(currentMon);
                if (currentHealthRatio < lowestHealthRatio)
                {
                    lowestHealthRatio = currentHealthRatio;
                    lowestHealthRatioIndex = i;
                }
                else if (currentHealthRatio == lowestHealthRatio)
                {
                    if (BattleRandom(100) < 50)
                    {
                        lowestHealthRatioIndex = i;
                    }
                }
                else
                {
                }
            }
            if (lowestHealthRatioIndex == 1000)
            {
                lowestHealthRatioIndex = BattleRandom(Count);
            }
            return PokeCon_GetBattleMon(a1->pokeCon, a4[lowestHealthRatioIndex]);
        }
        else
        {
            Count = MainModule_ExpandExistPokeID(a1->mainModule, a1->pokeCon, a2 | 0x100, a4);
            if (!Count)
            {
                return 0;
            }
            v4 = a1->rand3 + a1->rand2 * a1->rand1;
            a1->rand1 = v4;
            v5 = (HIDWORD(v4) * Count) >> 32;
            return PokeCon_GetBattleMon(a1->pokeCon, a4[v5]);
        }
    }
#endif

    unsigned int THUMB_BRANCH_SAFESTACK_PickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
    {
        unsigned int v5;    // r5
        BattleMon *MonData; // r6
        int ID;             // r4
        AbilID atkAbility;
        AbilID defAbility;
        unsigned int BasePower;              // r4
        unsigned int TypeEffectivenessVsMon; // r0
        unsigned int v10;                    // r0
        unsigned int result;                 // r0
        unsigned int j;                      // r5
        unsigned int k;                      // r6
        unsigned int v14;                    // r1
        unsigned int v15;                    // r0
        unsigned int v18;
        int randomvalue;
        u8 v16;                              // r1
        int Type;                            // [sp+8h] [bp-38h]
        unsigned int MoveCount;              // [sp+Ch] [bp-34h]
        unsigned int i;                      // [sp+10h] [bp-30h]
        int PokeType;                        // [sp+14h] [bp-2Ch]
        __int16 v23[6] = {0, 0, 0, 0, 0, 0}; // [sp+1Ch] [bp-24h]
        BattleMon *v24;                      // [sp+28h] [bp-18h]
        __int16 v23_temp[6];

        v24 = a4;

#if DEBUGGING_ILLUSION
        u8 *monsCopy = a2;
        copyArray(a2, monsCopy);
        int personalResult = PersonalPickBestMonToSwitchInto(a1, a2, a3, a4);
        personalResult = monsCopy[0];
#endif
        __int16 defenderPos;
        int numTargets;
        u8 defendingAllies[4];
        unsigned int currentTarget;
        int currentTargetPosition;
        BattleMon *defendingMonChecked;

        numTargets = 1;

        if (getSwitchSetting() == 1)
        {
            defenderPos = MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, a4->ID);
            numTargets = MainModule_ExpandExistPokeID(a1->mainModule, a1->pokeCon, defenderPos | 0x700, defendingAllies);
        }

        for (currentTarget = 0; currentTarget < numTargets; currentTarget++)
        {
            defendingMonChecked = a4;

            if (getSwitchSetting() == 1)
            {
                currentTargetPosition = defendingAllies[currentTarget];
                defendingMonChecked = PokeCon_GetBattleMon(a1->pokeCon, currentTargetPosition);
            }

            PokeType = BattleMon_GetPokeType(defendingMonChecked);
            defAbility = (AbilID)BattleMon_GetValue(defendingMonChecked, VALUE_EFFECTIVE_ABILITY);

            if (getSwitchSetting() == 1)
            {
                if (!IsPosInRangeTripleBattle(MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, defendingMonChecked->ID), MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, a4->ID)))
                {
                    continue;
                }
            }

            for (i = 0; i < a3; i = (i + 1))
            {
                v5 = 0;

                v23_temp[i] = 0;
                MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
                atkAbility = (AbilID)BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY);
                // k::Printf("Evaluating mon %d at position %d with ability %d\n", MonData->Species, MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, MonData->ID), BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY));

                if (!BattleMon_IsFainted(MonData))
                {
                    MoveCount = BattleMon_GetMoveCount(MonData);
                    if (MoveCount)
                    {
                        do
                        {
                            if (Move_GetPP(MonData, v5))
                            {
                                ID = Move_GetID(MonData, v5);
                                if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
                                {
                                    Type = PML_MoveGetType(ID);
                                    BasePower = PML_MoveGetBasePower(ID);

                                    // Weather Ball Checks
                                    if (ID == MOVE267_NATURE_POWER)
                                    {

                                        int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

                                        if (BattleTerrain == 5u)
                                        {
                                            ID = 402;
                                        }
                                        else if (BattleTerrain == 11u)
                                        {
                                            ID = 89;
                                        }
                                        else if (BattleTerrain == 0xCu)
                                        {
                                            ID = 56;
                                        }
                                        else if (BattleTerrain == 7u)
                                        {
                                            ID = 59;
                                        }
                                        else if (BattleTerrain == 9u)
                                        {
                                            ID = 426;
                                        }
                                        else if (BattleTerrain == 0xAu)
                                        {
                                            ID = 157;
                                        }
                                        else if (BattleTerrain == 0xDu)
                                        {
                                            ID = 58;
                                        }
                                        else
                                        {
                                            ID = 161;
                                        }
                                    }

                                    if (atkAbility == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_ELECTRIC;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }

                                    if (atkAbility == ABIL105_MOISTURIZE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_WATER;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }

                                    if (atkAbility == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_ICE;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }

                                    if (atkAbility == ABIL060_AERILATE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_FLYING;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }

                                    if (atkAbility == ABIL040_PIXILATE && Type == TYPE_NORMAL)
                                    {
                                        Type = TYPE_FAIRY;
                                        BasePower = fixed_round(BasePower, 4505);
                                    }

                                    if (atkAbility == ABIL096_NORMALIZE)
                                    {
                                        Type = TYPE_NORMAL;
                                    }

                                    if (ID == MOVE311_WEATHER_BALL || ID == MOVE271_WEATHER_CRASH)
                                    {

                                        v18 = BattleField_GetWeather();

                                        if (v18 != 0)
                                        {
                                            BasePower = 100;
                                        }
                                        if (v18 == 1 || atkAbility == ABIL094_SOLAR_POWER || atkAbility == ABIL034_CHLOROPHYLL || atkAbility == ABIL122_FLOWER_GIFT)
                                        {

                                            BasePower = 100;
                                            Type = TYPE_FIRE;
                                        }
                                        else if (v18 == 2)
                                        {
                                            Type = TYPE_WATER;
                                        }
                                        else if (v18 == 3)
                                        {
                                            Type = TYPE_ICE;
                                        }
                                        else if (v18 == 4)
                                        {
                                            Type = TYPE_ROCK;
                                        }
                                    }

                                    if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
                                    {

                                        Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);

                                        BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
                                    }

                                    if (ID == MOVE546_TECHNO_BLAST)
                                    {
                                        if (MonData->HeldItem == IT0119_CHILL_DRIVE)
                                        {
                                            Type = TYPE_ICE;
                                        }
                                        if (MonData->HeldItem == IT0116_DOUSE_DRIVE)
                                        {
                                            Type = TYPE_WATER;
                                        }
                                        if (MonData->HeldItem == IT0118_BURN_DRIVE)
                                        {
                                            Type = TYPE_FIRE;
                                        }
                                        if (MonData->HeldItem == IT0117_SHOCK_DRIVE)
                                        {
                                            Type = TYPE_ELECTRIC;
                                        }
                                    }

                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);

                                    if (atkAbility == ABIL113_SCRAPPY && (Type == TYPE_NORMAL || Type == TYPE_FIGHTING))
                                    {
                                        TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    }
                                    if (ID == MOVE357_FREEZE_DRY || ID == MOVE547_RELIC_SONG || ID == MOVE533_SACRED_SWORD)
                                    {
                                        TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    }
                                    if ((Type == TYPE_POISON && atkAbility == ABIL007_CORROSION) || (Type == TYPE_PSYCHIC && atkAbility == ABIL039_INNER_FOCUS))
                                    {
                                        TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    }

                                    if (ID == MOVE327_SKY_UPPERCUT)
                                    {
                                        TypeEffectivenessVsMon = EvaluateTypeEffectivenesssForFighting(Type, PokeType, (atkAbility == ABIL113_SCRAPPY));
                                    }

                                    if (ID == MOVE498_CHIP_AWAY)
                                    {
                                        TypeEffectivenessVsMon = 3;
                                    }

                                    if (atkAbility == ABIL096_NORMALIZE && ID != MOVE363_NATURAL_GIFT && ID != MOVE546_TECHNO_BLAST && ID != MOVE311_WEATHER_BALL && ID != MOVE271_WEATHER_CRASH)
                                    {
                                        TypeEffectivenessVsMon = 3;
                                    }

                                    if (!HasMoldBreaker(MonData) && CheckIfImmuneAbility(Type, ID, defendingMonChecked))
                                    {
                                        TypeEffectivenessVsMon = 0;
                                    }
                                    if (TypeEffectivenessVsMon == 0)
                                    {
                                        BasePower = 0;
                                    }
                                    else if (TypeEffectivenessVsMon == 1)
                                    {
                                        v10 = BasePower << 14;
                                    }
                                    else if (TypeEffectivenessVsMon == 2)
                                    {
                                        v10 = BasePower << 15;
                                    }
                                    else if (TypeEffectivenessVsMon == 3)
                                    {
                                        v10 = BasePower << 16;
                                    }
                                    else if (TypeEffectivenessVsMon == 4)
                                    {
                                        v10 = BasePower << 17;
                                    }
                                    else if (TypeEffectivenessVsMon == 5)
                                    {
                                        v10 = BasePower << 18;
                                    }
                                    else
                                    {
                                    }
                                    if (BasePower > 0)
                                    {
                                        v10 = checkForBPChanges(MonData, defendingMonChecked, ID, v10, a1);
                                        v10 = checkForTechnician(MonData, ID, v10);
                                        v10 = checkForSTAB(MonData, Type, v10);
#if SWITCH_AI_CHANGES
                                        v10 = checkForMatchup(MonData, defendingMonChecked, v10);
#endif
                                        v10 = checkForAbilityAndItemBPChanges(MonData, defendingMonChecked, Type, TypeEffectivenessVsMon, v10);
                                        BasePower = HIWORD(v10);
                                    }
                                    if (v23_temp[i] < BasePower)
                                    {
                                        v23_temp[i] = BasePower;
                                    }
                                }
                            }
                            v5 = (v5 + 1);
                        } while (v5 < MoveCount);
#if DEBUGGING_ILLUSION
                        // before moving on to the next pokemon, the game will check if the pokemon has the ability illusion.
                        if (atkAbility == ABIL149_ILLUSION)
                        {
                            int illusionBasePower = v23_temp[i];
                            if (personalResult == a2[i])
                            {
                                // if (BattleRandom(100) > 50)
                                if (BattleRandom(100) > 1)
                                {
                                    illusionBasePower = illusionBasePower >> 1;
                                }
                            }
                            else if (personalResult != a2[i] && illusionBasePower >= 80)
                            {
                                if (BattleRandom(100) > 1)
                                {
                                    illusionBasePower = illusionBasePower << 1;
                                }
                            }
                            else
                            {
                            }
                            v23_temp[i] = illusionBasePower;
                        }
#endif
                        v23[i] = v23[i] + v23_temp[i];
                    }
                }
            }
        }
        result = a3;
        for (j = 0; j < a3; result = a3)
        {
            //  k::Printf("\nStep %d\n", 21 + j);
            for (k = (j + 1); k < a3; k = (k + 1))
            {
                v14 = v23[k];
                v15 = v23[j];
                if (v15 < v14)
                {
                    v23[j] = v14;
                    v23[k] = v15;
                    v16 = a2[j];
                    a2[j] = a2[k];
                    a2[k] = v16;
                }
            }
            j = (unsigned __int8)(j + 1);
        }
        return result;
    }

#if USING_VANILLA_SWITCH_AI

#if DEBUGGING_ILLUSION
    unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
    {
        unsigned int v5;    // r5
        BattleMon *MonData; // r6
        int ID;             // r4
        AbilID atkAbility;
        AbilID defAbility;
        unsigned int BasePower;              // r4
        unsigned int TypeEffectivenessVsMon; // r0
        unsigned int v10;                    // r0
        unsigned int result;                 // r0
        unsigned int j;                      // r5
        unsigned int k;                      // r6
        unsigned int v14;                    // r1
        unsigned int v15;                    // r0
        unsigned int v18;
        int randomvalue;
        u8 v16;                 // r1
        int Type;               // [sp+8h] [bp-38h]
        unsigned int MoveCount; // [sp+Ch] [bp-34h]
        unsigned int i;         // [sp+10h] [bp-30h]
        int PokeType;           // [sp+14h] [bp-2Ch]
        __int16 v23[6];         // [sp+1Ch] [bp-24h]
        BattleMon *v24;         // [sp+28h] [bp-18h]

        v24 = a4;

        PokeType = BattleMon_GetPokeType(a4);
        defAbility = (AbilID)BattleMon_GetValue(a4, VALUE_EFFECTIVE_ABILITY);

        for (i = 0; i < a3; i = (i + 1))
        {
            v5 = 0;
            v23[i] = 0;
            MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
            atkAbility = (AbilID)BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY);
            if (!BattleMon_IsFainted(MonData))
            {
                MoveCount = BattleMon_GetMoveCount(MonData);
                if (MoveCount)
                {
                    do
                    {
                        if (Move_GetPP(MonData, v5))
                        {
                            ID = Move_GetID(MonData, v5);

                            if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
                            {
                                Type = PML_MoveGetType(ID);
                                BasePower = PML_MoveGetBasePower(ID);

                                // Weather Ball Checks
                                if (ID == MOVE267_NATURE_POWER)
                                {
                                    int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

                                    if (BattleTerrain == 5u)
                                    {
                                        ID = 402;
                                    }
                                    else if (BattleTerrain == 11u)
                                    {
                                        ID = 89;
                                    }
                                    else if (BattleTerrain == 0xCu)
                                    {
                                        ID = 56;
                                    }
                                    else if (BattleTerrain == 7u)
                                    {
                                        ID = 59;
                                    }
                                    else if (BattleTerrain == 9u)
                                    {
                                        ID = 426;
                                    }
                                    else if (BattleTerrain == 0xAu)
                                    {
                                        ID = 157;
                                    }
                                    else if (BattleTerrain == 0xDu)
                                    {
                                        ID = 58;
                                    }
                                    else
                                    {
                                        ID = 161;
                                    }
                                }

                                if (atkAbility == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ELECTRIC;
                                    BasePower = fixed_round(BasePower, 4505);
                                }
                                if (atkAbility == ABIL105_MOISTURIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_WATER;
                                    BasePower = fixed_round(BasePower, 4505);
                                }
                                if (atkAbility == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ICE;
                                    BasePower = fixed_round(BasePower, 4505);
                                }
                                if (atkAbility == ABIL060_AERILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FLYING;
                                    BasePower = fixed_round(BasePower, 4505);
                                }
                                if (atkAbility == ABIL040_PIXILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FAIRY;
                                    BasePower = fixed_round(BasePower, 4505);
                                }
                                if (atkAbility == ABIL096_NORMALIZE)
                                {
                                    Type = TYPE_NORMAL;
                                }

                                if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
                                {
                                    Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);
                                    BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
                                }

                                // Weather Ball Checks
                                if (ID == MOVE311_WEATHER_BALL || ID == MOVE271_WEATHER_CRASH)
                                {

                                    v18 = BattleField_GetWeather();
                                    if (v18 != 0)
                                    {
                                        BasePower = 100;
                                    }
                                    if (v18 == 1 || atkAbility == ABIL094_SOLAR_POWER || atkAbility == ABIL034_CHLOROPHYLL || atkAbility == ABIL122_FLOWER_GIFT)
                                    {
                                        BasePower = 100;
                                        Type = TYPE_FIRE;
                                    }
                                    else if (v18 == 2)
                                    {
                                        Type = TYPE_WATER;
                                    }
                                    else if (v18 == 3)
                                    {
                                        Type = TYPE_ICE;
                                    }
                                    else if (v18 == 4)
                                    {
                                        Type = TYPE_ROCK;
                                    }
                                }

                                if (ID == MOVE546_TECHNO_BLAST)
                                {
                                    if (MonData->HeldItem == IT0119_CHILL_DRIVE)
                                    {
                                        Type = TYPE_ICE;
                                    }
                                    if (MonData->HeldItem == IT0116_DOUSE_DRIVE)
                                    {
                                        Type = TYPE_WATER;
                                    }
                                    if (MonData->HeldItem == IT0118_BURN_DRIVE)
                                    {
                                        Type = TYPE_FIRE;
                                    }
                                    if (MonData->HeldItem == IT0117_SHOCK_DRIVE)
                                    {
                                        Type = TYPE_ELECTRIC;
                                    }
                                }

                                TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);

                                if (atkAbility == ABIL113_SCRAPPY && (Type == TYPE_NORMAL || Type == TYPE_FIGHTING))
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                }
                                if (ID == MOVE357_FREEZE_DRY || ID == MOVE547_RELIC_SONG || ID == MOVE533_SACRED_SWORD)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                }
                                if ((Type == TYPE_POISON && atkAbility == ABIL007_CORROSION) || (Type == TYPE_PSYCHIC && atkAbility == ABIL039_INNER_FOCUS))
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                }

                                if (ID == MOVE327_SKY_UPPERCUT)
                                {
                                    TypeEffectivenessVsMon = EvaluateTypeEffectivenesssForFighting(Type, PokeType, (atkAbility == ABIL113_SCRAPPY));
                                }

                                if (ID == MOVE498_CHIP_AWAY)
                                {
                                    TypeEffectivenessVsMon = 3;
                                }

                                if (atkAbility == ABIL096_NORMALIZE && ID != MOVE363_NATURAL_GIFT && ID != MOVE546_TECHNO_BLAST && ID != MOVE311_WEATHER_BALL && ID != MOVE271_WEATHER_CRASH)
                                {
                                    TypeEffectivenessVsMon = 3;
                                }

                                if (!HasMoldBreaker(MonData) && CheckIfImmuneAbility(Type, ID, a4))
                                {

                                    TypeEffectivenessVsMon = 0;
                                }

                                if (TypeEffectivenessVsMon == 0)
                                {
                                    BasePower = 0;
                                }
                                else if (TypeEffectivenessVsMon == 1)
                                {
                                    v10 = BasePower << 14;
                                }
                                else if (TypeEffectivenessVsMon == 2)
                                {
                                    v10 = BasePower << 15;
                                }
                                else if (TypeEffectivenessVsMon == 3)
                                {
                                    v10 = BasePower << 16;
                                }
                                else if (TypeEffectivenessVsMon == 4)
                                {
                                    v10 = BasePower << 17;
                                }
                                else if (TypeEffectivenessVsMon == 5)
                                {
                                    v10 = BasePower << 18;
                                }
                                else
                                {
                                }

                                if (BasePower > 0)
                                {

                                    v10 = checkForBPChanges(MonData, v24, ID, v10, a1);

                                    v10 = checkForTechnician(MonData, ID, v10);

                                    v10 = checkForSTAB(MonData, Type, v10);
#if SWITCH_AI_CHANGES
                                    v10 = checkForMatchup(MonData, v24, v10);
#endif
                                    v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);

                                    BasePower = HIWORD(v10);
                                }

                                if (v23[i] < BasePower)
                                {
                                    v23[i] = BasePower;
                                }
                            }
                        }
                        v5 = (v5 + 1);
                    } while (v5 < MoveCount);
                }
            }
        }
        result = a3;
        for (j = 0; j < a3; result = a3)
        {
            for (k = (j + 1); k < a3; k = (k + 1))
            {
                v14 = v23[k];
                v15 = v23[j];
                if (v15 < v14)
                {
                    v23[j] = v14;
                    v23[k] = v15;
                    v16 = a2[j];
                    a2[j] = a2[k];
                    a2[k] = v16;
                }
            }
            j = (unsigned __int8)(j + 1);
        }

        if (a3 > 1)
        {
            if (BattleMon_GetValue(BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[0]), VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
            {
                illusionMonId = a2[1];
            }
            else
            {
                illusionMonId = a2[0];
            }
        }
        else
        {
            illusionMonId = a2[0];
        }

        return result;
    }
#endif

    unsigned int THUMB_BRANCH_SAFESTACK_PickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
    {
        unsigned int v5;    // r5
        BattleMon *MonData; // r6
        int ID;             // r4
        AbilID atkAbility;
        AbilID defAbility;
        unsigned int BasePower;              // r4
        unsigned int TypeEffectivenessVsMon; // r0
        unsigned int v10;                    // r0
        unsigned int result;                 // r0
        unsigned int j;                      // r5
        unsigned int k;                      // r6
        unsigned int v14;                    // r1
        unsigned int v15;                    // r0
        unsigned int v18;
        int randomvalue;
        u8 v16;                 // r1
        int Type;               // [sp+8h] [bp-38h]
        unsigned int MoveCount; // [sp+Ch] [bp-34h]
        unsigned int i;         // [sp+10h] [bp-30h]
        int PokeType;           // [sp+14h] [bp-2Ch]
        __int16 v23[6];         // [sp+1Ch] [bp-24h]
        BattleMon *v24;         // [sp+28h] [bp-18h]

        v24 = a4;
        PokeType = BattleMon_GetPokeType(a4);
        u8 *monsCopy = a2;
        copyArray(a2, monsCopy);
        int personalResult = PersonalPickBestMonToSwitchInto(a1, a2, a3, a4);
        personalResult = monsCopy[0];
        defAbility = (AbilID)BattleMon_GetValue(a4, VALUE_EFFECTIVE_ABILITY);
        for (i = 0; i < a3; i = (i + 1))
        {
            v5 = 0;

            v23[i] = 0;
            MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
            atkAbility = (AbilID)BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY);
            if (!BattleMon_IsFainted(MonData))
            {
                MoveCount = BattleMon_GetMoveCount(MonData);
                if (MoveCount)
                {
                    do
                    {
                        if (Move_GetPP(MonData, v5))
                        {
                            ID = Move_GetID(MonData, v5);
                            if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
                            {
                                Type = PML_MoveGetType(ID);
                                BasePower = PML_MoveGetBasePower(ID);
                                // k:Printf("\nBase Power from %d is %d\n", ID, BasePower);

                                // Weather Ball Checks

                                if (ID == MOVE267_NATURE_POWER)
                                {

                                    int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

                                    if (BattleTerrain == 5u)
                                    {
                                        ID = 402;
                                    }
                                    else if (BattleTerrain == 11u)
                                    {
                                        ID = 89;
                                    }
                                    else if (BattleTerrain == 0xCu)
                                    {
                                        ID = 56;
                                    }
                                    else if (BattleTerrain == 7u)
                                    {
                                        ID = 59;
                                    }
                                    else if (BattleTerrain == 9u)
                                    {
                                        ID = 426;
                                    }
                                    else if (BattleTerrain == 0xAu)
                                    {
                                        ID = 157;
                                    }
                                    else if (BattleTerrain == 0xDu)
                                    {
                                        ID = 58;
                                    }
                                    else
                                    {
                                        ID = 161;
                                    }
                                }

                                if (atkAbility == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ELECTRIC;
                                    BasePower = fixed_round(BasePower, 4505);
                                }

                                if (atkAbility == ABIL105_MOISTURIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_WATER;
                                    BasePower = fixed_round(BasePower, 4505);
                                }

                                if (atkAbility == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ICE;
                                    BasePower = fixed_round(BasePower, 4505);
                                }

                                if (atkAbility == ABIL060_AERILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FLYING;
                                    BasePower = fixed_round(BasePower, 4505);
                                }

                                if (atkAbility == ABIL040_PIXILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FAIRY;
                                    BasePower = fixed_round(BasePower, 4505);
                                }

                                if (atkAbility == ABIL096_NORMALIZE)
                                {
                                    Type = TYPE_NORMAL;
                                }

                                if (ID == MOVE311_WEATHER_BALL || ID == MOVE271_WEATHER_CRASH)
                                {

                                    v18 = BattleField_GetWeather();

                                    if (v18 != 0)
                                    {
                                        BasePower = 100;
                                    }
                                    if (v18 == 1 || atkAbility == ABIL094_SOLAR_POWER || atkAbility == ABIL034_CHLOROPHYLL || atkAbility == ABIL122_FLOWER_GIFT)
                                    {

                                        BasePower = 100;
                                        Type = TYPE_FIRE;
                                    }
                                    else if (v18 == 2)
                                    {
                                        Type = TYPE_WATER;
                                    }
                                    else if (v18 == 3)
                                    {
                                        Type = TYPE_ICE;
                                    }
                                    else if (v18 == 4)
                                    {
                                        Type = TYPE_ROCK;
                                    }
                                }

                                if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
                                {

                                    Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);

                                    BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
                                }

                                if (ID == MOVE546_TECHNO_BLAST)
                                {
                                    if (MonData->HeldItem == IT0119_CHILL_DRIVE)
                                    {
                                        Type = TYPE_ICE;
                                    }
                                    if (MonData->HeldItem == IT0116_DOUSE_DRIVE)
                                    {
                                        Type = TYPE_WATER;
                                    }
                                    if (MonData->HeldItem == IT0118_BURN_DRIVE)
                                    {
                                        Type = TYPE_FIRE;
                                    }
                                    if (MonData->HeldItem == IT0117_SHOCK_DRIVE)
                                    {
                                        Type = TYPE_ELECTRIC;
                                    }
                                }

                                TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);

                                if (atkAbility == ABIL113_SCRAPPY && (Type == TYPE_NORMAL || Type == TYPE_FIGHTING))
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                }
                                if (ID == MOVE357_FREEZE_DRY || ID == MOVE547_RELIC_SONG || ID == MOVE533_SACRED_SWORD)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                }
                                if ((Type == TYPE_POISON && atkAbility == ABIL007_CORROSION) || (Type == TYPE_PSYCHIC && atkAbility == ABIL039_INNER_FOCUS))
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                }

                                if (ID == MOVE327_SKY_UPPERCUT)
                                {
                                    TypeEffectivenessVsMon = EvaluateTypeEffectivenesssForFighting(Type, PokeType, (atkAbility == ABIL113_SCRAPPY));
                                }

                                if (ID == MOVE498_CHIP_AWAY)
                                {
                                    TypeEffectivenessVsMon = 3;
                                }

                                if (atkAbility == ABIL096_NORMALIZE && ID != MOVE363_NATURAL_GIFT && ID != MOVE546_TECHNO_BLAST && ID != MOVE311_WEATHER_BALL && ID != MOVE271_WEATHER_CRASH)
                                {
                                    TypeEffectivenessVsMon = 3;
                                }

                                if (!HasMoldBreaker(MonData) && CheckIfImmuneAbility(Type, ID, a4))
                                {
                                    TypeEffectivenessVsMon = 0;
                                }
                                if (TypeEffectivenessVsMon == 0)
                                {
                                    BasePower = 0;
                                }
                                else if (TypeEffectivenessVsMon == 1)
                                {
                                    v10 = BasePower << 14;
                                }
                                else if (TypeEffectivenessVsMon == 2)
                                {
                                    v10 = BasePower << 15;
                                }
                                else if (TypeEffectivenessVsMon == 3)
                                {
                                    v10 = BasePower << 16;
                                }
                                else if (TypeEffectivenessVsMon == 4)
                                {
                                    v10 = BasePower << 17;
                                }
                                else if (TypeEffectivenessVsMon == 5)
                                {
                                    v10 = BasePower << 18;
                                }
                                else
                                {
                                }
                                if (BasePower > 0)
                                {
                                    v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
                                    v10 = checkForTechnician(MonData, ID, v10);
                                    v10 = checkForSTAB(MonData, Type, v10);
#if SWITCH_AI_CHANGES
                                    v10 = checkForMatchup(MonData, v24, v10);
#endif
                                    v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);
                                    BasePower = HIWORD(v10);
                                }
                                if (v23[i] < BasePower)
                                {
                                    v23[i] = BasePower;
                                }
                            }
                        }
                        v5 = (v5 + 1);
                    } while (v5 < MoveCount);

#if DEBUGGING_ILLUSION
                    // before moving on to the next pokemon, the game will check if the pokemon has the ability illusion.
                    if (atkAbility == ABIL149_ILLUSION)
                    {
#if DEBUGGING_ILLUSION && DEBUGGING_ALL
                        k::Printf("\nThe actual best switch in is %d\n", BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[actualBest])->Species);

                        k::Printf("\nFor Pokemon %d, their highest base power move is %d.\nWithout this pokemon of id=%d the switch ai would return %d.",
                                  BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[actualBest])->Species, v23[i], i, actualBest);
                        k::Printf("\nThe actual best switch in is %d with id %d while the current Pokemon we are assessing is %d with id %d\n", BattleParty_GetMonData(BattleClient_GetActParty(a1), personalResult)->Species, personalResult, MonData->Species, a2[i]);
#endif
                        int illusionBasePower = v23[i];
                        if (personalResult == a2[i])
                        {
#if DEBUGGING_ILLUSION && DEBUGGING_ALL
                            k::Printf("\nThe Illusion Pokemon is the best switch in");
#endif
                            if (BattleRandom(100) > 50)
                            {
#if DEBUGGING_ILLUSION && DEBUGGING_ALL
                                k::Printf(" but is going dodge their duties\n");
#endif
                                illusionBasePower = illusionBasePower >> 1;
                                // k::Printf("\nBasePower is now %d", illusionBasePower);
                            }
                        }
                        else if (personalResult != a2[i] && illusionBasePower >= 80)
                        {
#if DEBUGGING_ILLUSION && DEBUGGING_ALL
                            k::Printf("\nThe Illusion Pokemon is not the best switch in");
#endif
                            if (BattleRandom(100) > 50)
                            {
#if DEBUGGING_ILLUSION && DEBUGGING_ALL
                                k::Printf(" but is going to come in anyways\n");

#endif
                                illusionBasePower = illusionBasePower << 1;
                            }
                        }
                        else
                        {
                        }
                        v23[i] = illusionBasePower;
                    }
#endif
                }
            }
        }
        // k::Printf("\nStep 21\n");
        result = a3;
        for (j = 0; j < a3; result = a3)
        {
            //  k::Printf("\nStep %d\n", 21 + j);
            for (k = (j + 1); k < a3; k = (k + 1))
            {
                v14 = v23[k];
                v15 = v23[j];
                if (v15 < v14)
                {
                    v23[j] = v14;
                    v23[k] = v15;
                    v16 = a2[j];
                    a2[j] = a2[k];
                    a2[k] = v16;
                }
            }
            j = (unsigned __int8)(j + 1);
        }
        return result;
    }
#endif

#pragma endregion

#pragma region MidBattleSwitchAI

    //     /*

    //         --------------------------------------------------------------------------------------------------
    //         ------------------------------------ MID BATTLE SWITCH AI ----------------------------------------
    //         --------------------------------------------------------------------------------------------------

    //         This function decideds whether the user should switch if locked into an ineffective move with choice items.
    //         We are going to improve that functionality and then hijack the function to inject some additional condditions
    //         to look for.

    //         is one we're hijaking in order to add a few more conditions for mid-battle switch AI.

    //         Improvements to Choice/Encore Logic
    //             - Add in Encore lock switch AI that shares properties with the choice lock one
    //             - Add in checks for disable and torment
    //             - Improve the choice lock logic to refer to damage output to decide whether to switch
    //                 - (Ideal) use SimulationDamage to check potential damage output and increase odds if at or under 25%.
    //                 - (Sloppy) Judge entirely by effectiveness

    //         Switch out if Ineffective
    //             - Add a check that applies to any Pokemon even if they aren't in encore or choice locked that checks
    //             their damage output.
    //             - If it's below 25% with any of their moves, they have an initially small but slowly increasing chance to switch out after 3 turns.

    //         Switch out for Wish
    //             - If there is a wish active, the pokemon is healthy, high chance to switch out.

    //         Switch out for Future Sight
    //             - If a Future sight is active and the pokemon is healthy, high chance to switch out.

    //     */
    // unsigned int THUMB_BRANCH_checkReservePokemonDamage(TrainerAIEnv *a1, BattleMon *attackingMon, BattleMon *defendingMon, int a4)
    // {
    //     unsigned int v6; // r6
    //     int i;           // r4
    //     int v8;          // r0
    //     unsigned int v9; // r0
    //     int v12;         // [sp+Ch] [bp-1Ch]
    //     int ID;          // [sp+10h] [bp-18h]

    //     v6 = 0;
    //     ID = BattleMon_GetID(attackingMon);
    //     v12 = BattleMon_GetID(defendingMon);
    //     // AbilityEvent_AddItem(attackingMon);
    //     // ItemEvent_AddItem(attackingMon);
    //     for (i = 0; i < BattleMon_GetMoveCount(attackingMon); ++i)
    //     {
    //         v8 = Move_GetID(attackingMon, i);
    //         v9 = Handler_SimulationDamage(a1->serverFlow, ID, v12, v8, false, false);
    //         if (v9 > v6)
    //         {
    //             v6 = v9;
    //         }
    //     }
    //     // AbilityEvent_RemoveItem(attackingMon);
    //     // ItemEvent_RemoveItem(attackingMon);
    //     return v6;
    // }

    //     unsigned int PersonalCheckReservePokemonDamage(ServerFlow *a1, BattleMon *attackingMon, BattleMon *defendingMon, int a4)
    //     {
    //         unsigned int v6; // r6
    //         int i;           // r4
    //         int v8;          // r0
    //         unsigned int v9; // r0
    //         int v12;         // [sp+Ch] [bp-1Ch]
    //         int ID;          // [sp+10h] [bp-18h]

    // #if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
    //         k::Printf("\n\n--------Personal Check Reserve Pokemon Damage-----------\nIs being called for Pokemon %d against %d\n", attackingMon->Species, defendingMon->Species);
    // #endif
    //         v6 = 0;
    //         ID = BattleMon_GetID(attackingMon);
    //         v12 = BattleMon_GetID(defendingMon);
    //         // AbilityEvent_AddItem(attackingMon);
    //         // ItemEvent_AddItem(attackingMon);
    //         for (i = 0; i < BattleMon_GetMoveCount(attackingMon); ++i)
    //         {
    //             v8 = Move_GetID(attackingMon, i);
    //             v9 = Handler_SimulationDamage(a1, ID, v12, v8, false, false);
    //             if (v9 > v6)
    //             {
    //                 v6 = v9;
    //             }
    //         }
    //         // AbilityEvent_RemoveItem(attackingMon);
    //         // ItemEvent_RemoveItem(attackingMon);
    //         return v6;
    //     }

    //     int CheckIfMonToSwitchToWithBetterDamage(BtlClientWk *a1, BattleMon *defendingMon, int a3)
    //     {
    //         unsigned int PartyCount;     // r6
    //         BattleStyle battleStyle;     // r0
    //         unsigned int NumMonsOnField; // r4
    //         BattleMon *attackingMon;     // r0

    //         PartyCount = BattleParty_GetPartyCount(a1->actPokeParty);
    //         battleStyle = (BattleStyle) BtlSetup_GetBattleStyle(a1->mainModule);
    //         NumMonsOnField = GetNumMonsOnField(battleStyle, a1->myCoverPosNum);

    // #if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
    //         k::Printf("\n\n--------Check If Mon To Switch To With Better Damage-----------\nIs being called against %d\n", defendingMon->Species);
    // #endif
    //         if (NumMonsOnField >= PartyCount)
    //         {
    //             return 0;
    //         }
    //         while (1)
    //         {
    //             if (!SwitchAI_CheckReserve(a1, NumMonsOnField))
    //             {
    //                 attackingMon = BattleParty_GetMonData(a1->actPokeParty, NumMonsOnField);
    //                 if (a3 < PersonalCheckReservePokemonDamage(BattleServer_GetServerFlow(a1->mainModule->server), attackingMon, defendingMon, a3))
    //                 {
    //                     #if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
    //                     k::Printf("\nMidBattleSwitchAI: Debug Point 1: We have found    a pokemon %d that can deal more damage than current best %d\n", attackingMon->Species, defendingMon->Species);
    //                     #endif
    //                     break;
    //                 }
    //             }
    //             if (++NumMonsOnField >= PartyCount)
    //             {
    //                 return 0;
    //             }
    //         }
    //         #if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
    //         k::Printf("\nMidBattleSwitchAI: Debug Point 2: We have found a pokemon %d that can deal more damage than current best %d\n", attackingMon->Species, defendingMon->Species);
    //         #endif
    //         return 1;
    //     }

    bool AlternateSwitchConditions(BtlClientWk *work, BattleMon *attackingMon, BattleMon *defendingMon)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        ServerFlow *flow;
        unsigned int k;

        flow = BattleServer_GetServerFlow(work->mainModule->server);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(flow, attackingMon->ID);
        pokeCount = Handler_ExpandPokeID(flow, ExistFrontPokePos | 0x100, opposingPokePos);
        int turnCount = attackingMon->TurnCount;
        int damage = 0;
        bool switchout = 0;

        u8 count = BattleMon_GetMoveCount(attackingMon);
        if (count != 0)
        {
            for (int moveIndex = 0; moveIndex < count; moveIndex++)
            {
                MoveID moveId = (MoveID)Move_GetID(attackingMon, moveIndex);
                if (moveId == MOVE521_VOLT_SWITCH || moveId == MOVE369_U_TURN || moveId == MOVE199_PARTING_SHOT || moveId == MOVE205_ROLLOUT || moveId == MOVE226_BATON_PASS || moveId == MOVE160_FLIP_TURN)
                {

                    return 0;
                }
            }
        }

        for (k = 0; k < pokeCount; k += 1)
        {
            int i = 0;
            defender = Handler_GetBattleMon(flow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(attackingMon);
            int currentHp = defender->CurrentHP;
            int moveDamage = 0;
            do
            {

                // moveDamage = checkCalcTable(flow, attackingMon, defender, (MoveID)Move_GetID(attackingMon, i));
                // if (!moveDamage)
                // {
                moveDamage = Handler_SimulationDamage(flow,
                                                      BattleMon_GetID(attackingMon),
                                                      BattleMon_GetID(defender),
                                                      Move_GetID(attackingMon, i), true, false);
                // }

                if ((moveDamage << 1) >= currentHp)
                {

                    return 0;
                }
                else
                {

                    if (moveDamage > damage)
                    {

                        damage = moveDamage;
                    }
                }
                i++;
            } while (i < MoveCount);

            if (((damage << 3) + (damage << 1)) < defender->MaxHP)
            {

                if (turnCount >= 1)
                {

                    int random = RandomInRange(1, 100);

                    if (random < (10 + (turnCount << 2)))
                    {
                        switchout = 1;
                    }
                }
            }

            /* Moderately Negliglbe Damage */
            else if (((damage << 2) + (damage << 1)) < defender->MaxHP)
            {

                if (turnCount >= 3)
                {
                    if (RandomInRange(1, 100) < (5 + turnCount))
                    {
                        switchout = 1;
                    }
                }
            }

            /* Mildly Negliglbe Damage */
            else if ((damage << 2) < defender->MaxHP)
            {

                if (turnCount >= 4)
                {
                    if (RandomInRange(1, 100) < (1 + turnCount))
                    {
                        switchout = 1;
                    }
                }
            }

            /* If the attacker can deal at least 25% damage to one of the combatants on the field, they won't switch out, even if they can't deal that much damage to the other combatant.*/
            else
            {

                return 0;
            }
        }

        return (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 2)) ? switchout : 0;
    }

    bool THUMB_BRANCH_SAFESTACK_ShouldSwitchIfChoicedIntoIneffectiveMove(BtlClientWk *work, BattleMon *attackingMon, BattleMon *defendingMon)
    {
        ConditionData MoveCondition; // r0
        int Param;                   // r0
        int TypeEffectiveness;
        bool IsDamaging; // r6
        int PokeType;    // r0
        __int64 v10;     // kr00_8
        bool result;     // r0
        __int64 v12;     // r0
        __int64 v13;     // kr08_8
        __int64 v14;     // kr10_8
        int moveID;      // [sp+0h] [bp-28h]
        int temp;
        int Type; // [sp+4h] [bp-24h]
        AbilID atkAbility;
        AbilID defAbility;

        /* Encore and Choice Item Check */
        if (!BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_CHOICELOCK) && !BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_ENCORE))
        {

            // If the two conditions this function is defined for are not relevant, switch to the other one.
            // if (getSwitchSetting() != 1)
            // {
                return AlternateSwitchConditions(work, attackingMon, defendingMon);
            // }
            // else
            // {
            //     return 0;
            // }
        }

        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_CHOICELOCK))
        {
            MoveCondition = BattleMon_GetMoveCondition(attackingMon, CONDITION_CHOICELOCK);
            Param = Condition_GetParam(MoveCondition);
        }
        else if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_ENCORE))
        {
            MoveCondition = BattleMon_GetMoveCondition(attackingMon, CONDITION_ENCORE);
            Param = Condition_GetParam(MoveCondition);
        }

        /* Set up Variables */
        moveID = Param;
        atkAbility = (AbilID)BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY);
        defAbility = (AbilID)BattleMon_GetValue(defendingMon, VALUE_EFFECTIVE_ABILITY);

        if (!Param)
        {
            return 0;
        }

        /* Torment Checks */
        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_TORMENT))
        {
            return 1;
        }

        /* Disable Checks */
        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_DISABLEMOVE))
        {
            ConditionData MoveConditionData = BattleMon_GetMoveCondition(attackingMon, CONDITION_DISABLEMOVE);
            if (moveID == Condition_GetParam(MoveConditionData))
            {
                return 1;
            }
        }

        /* PP Checks */
        if (!Move_GetPP(attackingMon, Move_SearchIndex(attackingMon, moveID)))
        {
            return 1;
        }

        /* Updating Variables with any stuff that might have changed from move replacing Moves */
        IsDamaging = PML_MoveIsDamaging(Param);
        Type = PML_MoveGetType(moveID);
        PokeType = BattleMon_GetPokeType(defendingMon);
        if (!IsDamaging)
        {
            return 1;
        }

        /*

            ------------------------------------ CORE ENCORE / CHOICE LOGIC ----------------------------------------

            Right now we have a naive solution that only checks for effectiveness. Ideally, we're going to have a check
            here that checks for damage output in general. We don't want the AI switching out when they see a kill, even
            if the move they're using is 4x resisted.
            -

            [DAMAGE CALC CHECKS]
                - If the move has a killing blow, stay in.

                - The move has a 2HKO, stay in.

                - If the move deals 25% or less damage and neither of the previous two conditions are applicable, 70% chance to switch

                - If the move deals 0% damage due to no effectiveness, guaranteed switch out if any other pokemon has a move.

        */
        // int moveDamage = checkCalcTable(BattleServer_GetServerFlow(work->mainModule->server), attackingMon, defendingMon, (MoveID)moveID);
        // if (!moveDamage)
        // {
        int moveDamage = Handler_SimulationDamage(BattleServer_GetServerFlow(work->mainModule->server),
                                                  BattleMon_GetID(attackingMon),
                                                  BattleMon_GetID(defendingMon),
                                                  moveID, true, false);
        // }

#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
        k::Printf("\n\n--------ShouldSwitchIfChoicedIntoIneffectiveMove-----------\nIs being called for move %d, used by Pokemon %d against Pokemon %d, and deals %d damage\n", moveID, attackingMon->Species, defendingMon->Species, moveDamage);
#endif
        if (moveDamage == 0)
        {
#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
            k::Printf("The move deals 0 damage, we're going to switch\n");
#endif
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
            {
                return 1;
            }
            return 0;
        }
        // If the move's damage, doubled, is less than or equal to the defendingmon's current HP, don't switch out.
        if ((moveDamage << 1) >= defendingMon->CurrentHP)
        {
#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
            k::Printf("2x Damage: The move deals %d damage vs the defender's %d health, we're going to switch\n", (moveDamage << 1), defendingMon->CurrentHP);
#endif
            return 0;
        }

        // If the move's damage, multiplied by 10, is less than or equal to the defendingPokemon's maximum HP, will switch to any other pokemon.
        if (((moveDamage << 3) + (moveDamage << 1)) <= defendingMon->MaxHP)
        {
#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
            k::Printf("10x Damage: The move deals %d damage vs the defender's %d maximum health, we're going to switch\n", ((moveDamage << 3) + (moveDamage << 1)), defendingMon->MaxHP);
#endif
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
            {
                return 1;
            }
            return 0;
        }
        // If the move's damage, times 5, is less than or equal to the defending mon's maximum HP, extremely likely to switch out.
        else if (((moveDamage << 2) + moveDamage) <= defendingMon->MaxHP)
        {
#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
            k::Printf("5x Damage: The move deals %d damage vs the defender's %d maximum health, we might switch\n", ((moveDamage << 2) + moveDamage), defendingMon->MaxHP);
#endif
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 2))
            {
                if (RandomInRange(1, 100) >= 25)
                {
                    return 1;
                }
                return 0;
            }
            return 0;
        }
        // If the move's damage, times 3, is less than or equal to the defending mon's maximum HP, 60% chance to switch out.
        else if ((moveDamage + (moveDamage << 1)) <= defendingMon->MaxHP)
        {
#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
            k::Printf("3x Damage: The move deals %d damage vs the defender's %d maximum health, we might switch\n", (moveDamage + (moveDamage << 1)), defendingMon->MaxHP);
#endif
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 4))
            {
                if (RandomInRange(1, 100) >= 40)
                {
                    return 1;
                }
                return 0;
            }
            return 0;
        }
        else
        {
#if DEBUGGING_MIDTURN_SWITCH_AI && DEBUGGING_ALL
            k::Printf("The move dealt more than 33 percent and less than 50 percent. We won't switch\n");
#endif
            return 0;
        }
    }

#pragma endregion

#pragma region AIScriptFunctions

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------------- GUESS ABILITY --------------------------------------------
        --------------------------------------------------------------------------------------------------
          This function checks to see what the Pokemon's ability is, and isn't fooled by anything.
    */
    int THUMB_BRANCH_SAFESTACK_GuessAbility(TrainerAIEnv *a1, int a2, int a3)
    {
        BattleMon *BattleMonFromBattlePos; // r6

        // #if DEBUGGING_AI && DEBUGGING_ALL
        //         k::Printf("\n\n--------SAFESTACK_GuessAbility-----------\nIs being called for Pokemon in position %d on side %d\n", a3, a2);
        // #endif
        BattleMonFromBattlePos = GetBattleMonFromBattlePos(a1, a3);
        if (BattleMon_CheckIfMoveCondition(BattleMonFromBattlePos, CONDITION_GASTROACID))
        {
            return 0;
        }
        return BattleMon_GetValue(BattleMonFromBattlePos, VALUE_EFFECTIVE_ABILITY);
    }

    /*
        --------------------------------------------------------------------------------------------------
        --------------------------- CHECK MOVE CATEGORIES (FOR STATUS) -----------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks to see what a pokemon's primarily move category is. It first
            - checks the last move they used
            - if there is no last move, checks to see if all the moves they have are of the same category
            - if that's not true, then it checks what their current raw Attack vs Special Attack looks like

    */

    int CheckTargetMoves(BattleMon *a1)
    {
        int MoveCount;
        int LoopMoveID;
        int LoopMoveCategory;
        int LoopMoveCategoryCheck;
        int i;

        MoveCount = BattleMon_GetMoveCount(a1);
        LoopMoveCategoryCheck = 0;
        do
        {
            LoopMoveID = Move_GetID(a1, i);
            LoopMoveCategory = PML_MoveGetParam(LoopMoveID, MVDATA_CATEGORY);
            if (!LoopMoveCategory)
            {
                i++;
                continue;
            }
            if (!LoopMoveCategoryCheck && Move_GetPP(a1, i))
            {
                LoopMoveCategoryCheck = LoopMoveCategory;
            }

            if (LoopMoveCategory != LoopMoveCategoryCheck)
            {

                if (BattleMon_GetValue(a1, VALUE_ATTACK_STAT) >= BattleMon_GetValue(a1, VALUE_SPECIAL_ATTACK_STAT))
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
            i++;
        } while (i < MoveCount);
        return LoopMoveCategoryCheck;
    }

    int THUMB_BRANCH_AI094_GetPreviousMoveCategory(ScriptVM *a1, TrainerAIEnv *a2)
    {
        int LoopMoveCategoryResult;
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI094_GetPreviousMoveCategory-----------\nIs being called for move %d, used by Pokemon %d\n", a2->moveID, a2->attacker->Species);
#endif
        LoopMoveCategoryResult = CheckTargetMoves(a2->defender);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("The defending Pokemon %d is mainly the category %d\n\n", a2->defender->Species, LoopMoveCategoryResult);
#endif
        a2->param = LoopMoveCategoryResult;

        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------- CHECK FOR KILLING BLOWS (FOR SETUP) -----------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can kill them with any of their moves.
        If the target is faster than the user, and the setup move they're using doesn't boost speed past the
        target, then checks for even 50% damage.

        Originally:
            AI072_Nop

    */

    int multiplySpeed(int moveID, int speed)
    {
        if (moveID == MOVE097_AGILITY || moveID == MOVE504_SHELL_SMASH || moveID == MOVE475_AUTOTOMIZE || moveID == MOVE397_ROCK_POLISH || moveID == MOVE366_TAILWIND || moveID == MOVE508_SHIFT_GEAR)
        {
            return speed * 2;
        }
        else if (moveID == MOVE289_VICTORY_DANCE || moveID == MOVE483_QUIVER_DANCE || moveID == MOVE349_DRAGON_DANCE || moveID == MOVE488_FLAME_CHARGE || moveID == MOVE104_DOUBLE_TEAM)
        {
            return speed * 1.5;
        }
        else
        {
            return speed;
        }
    }

    int THUMB_BRANCH_AI105_WillUserFaint_Setup(ScriptVM *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        BattleMon *defender;
        u8 opposingPokePos[5];
        unsigned int k;
        int destination;

        destination = VM_Read32(a1);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI072_WillUserFaint_Setup-----------\nIs being called for move %d, used by Pokemon %d, checking %d targets.\n", a2->moveID, a2->attacker->Species, pokeCount);
#endif
        for (k = 0; k < pokeCount; k++)
        {
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(defender);
            int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), false, false);

#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf("Check %d is for move %d from %d, the damage against %d is %d. \n", i, Move_GetID(defender, i), defender->Species, a2->attacker->Species, damage);
#endif
                // If the target is faster the the Pokemon using the set up move, doubles the damage
                // now checking for a 2HKO
                if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) > multiplySpeed(a2->moveID, Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1)))
                {
#if DEBUGGING_AI && DEBUGGING_ALL
                    k::Printf("For speed boosting move %d, we need to do this extra check\n", a2->moveID);
#endif
                    damage *= 2;
                }

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage, destination))
                {
                    k = pokeCount;
                    break;
                }

                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------- CHECK FOR KILLING BLOWS (FOR PRIORITY) --------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can kill them with any of their moves.
        This is used to increase the score for priority moves if the user is slower than the target.

        Originally:
            AI104_Nop
    */

    int THUMB_BRANCH_AI046_CheckDamageForPriority(ScriptVM *a1, TrainerAIEnv *a2)
    {

        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        BattleMon *defender;
        BattleMon *reference;
        u8 opposingPokePos[5];
        unsigned int k;
        int battlePos;
        int moveId = a2->moveID;

        battlePos = GetBattlePosFromCommandArg(a2, VM_Read32(a1));
        reference = GetBattleMonFromBattlePos(a2, battlePos);
        int destination;

        destination = VM_Read32(a1);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, reference->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI0104_CheckDamageForPriority-----------\nIs being called for move %d, used by Pokemon %d, checking %d targets.\n", a2->moveID, a2->attacker->Species, pokeCount);
#endif
        for (k = 0; k < pokeCount; k++)
        {
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(defender);
            int currentHp = BattleMon_GetValue(reference, VALUE_CURRENT_HP);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(reference),
                                                      Move_GetID(defender, i), false, false);

#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf("Check %d isf or move %d from %d, the damage against %d is %d. \n", i, Move_GetID(defender, i), defender->Species, a2->attacker->Species, damage);
#endif
                // If currentHP is less than or equal to damage, performs the jump]
                if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
                {
                    if (AIConditionalJump(a1, 6, currentHp, damage, destination))
                    {
                        k = pokeCount;
                        break;
                    }
                }

#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf("Increment by 1\n");
#endif
                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------- CHECK ENEMY DAMAGE OUTPUT (FOR SETUP) ----------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can deal meaningful damage (33% of maximum health).
        This is used to potential increase the score for setup moves vs. enemies that cannot really hurt them.

        Originally:
            AI060_Nop
    */
    int THUMB_BRANCH_AI100_TargetDealsNegligibleDamage_Setup(ScriptVM *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        unsigned int k = 0x3C;
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
        int destination;

        destination = VM_Read32(a1);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI060_TargetDealsNegligibleDamage_Setup-----------\nIs being called for move %d, used by Pokemon %d, checking %d targets.\n", a2->moveID, a2->attacker->Species, pokeCount);
#endif

        for (k = 0; k < pokeCount; k++)
        {
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(defender);
            int currentHp = DivideMaxHPZeroCheck(a2->attacker, 3u);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), false, false);
#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf("Check %d isf or move %d from %d, the damage against %d is %d. \n", i, Move_GetID(defender, i), defender->Species, a2->attacker->Species, damage);
#endif
                // If currentHP is less than or equal to damage, performs the jump
                if (currentHp <= damage)
                {
                    return a2->result;
                }
#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf("Increment by 1\n");
#endif
                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        AIConditionalJump(a1, 6, 1, 1, destination);
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------- CHECK ENEMY DAMAGE OUTPUT (FOR DEBUFFS) --------------------------------
        --------------------------------------------------------------------------------------------------

        Checks to see if the target in front of them can deal meaningful damage.
        25% is the current arbitrary point set at which the AI will stop bothering with debuffing moves.
        Iterates through each move the target has and calcs against the user.

        Originally:
            AI062_Nop
    */
    int THUMB_BRANCH_SAFESTACK_AI066_CheckEnemyDamageOutput_Debuffs(ScriptVM *a1, TrainerAIEnv *a2)
    {
        int i = 0;
        int MoveCount = BattleMon_GetMoveCount(a2->defender);
        int currentHp = DivideMaxHPZeroCheck(a2->attacker, 4u);

#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\noffset for the jump is %x\n", a1->PC);
#endif

#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n\n", a2->moveID, a2->attacker->Species);
#endif
        int v7 = VM_Read32(a1);
        do
        {
            int damage = Handler_SimulationDamage(a2->serverFlow,
                                                  BattleMon_GetID(a2->defender),
                                                  BattleMon_GetID(a2->attacker),
                                                  Move_GetID(a2->defender, i), false, false);
#if DEBUGGING_AI && DEBUGGING_ALL
            k::Printf("Check %d is or move %d the damage against %d is %d. \n", i, Move_GetID(a2->defender, i), a2->attacker->Species, damage);
#endif

            // If currentHP is less than or equal to damage, performs the jump

            if (currentHp <= damage)
            {
#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf(" Taking too much damage, not going to jump\n\n");
                k::Printf("\noffset for the jump is %x\n", a1->PC);
#endif
                return a2->result;
            }
#if DEBUGGING_AI && DEBUGGING_ALL
            k::Printf("Increment by 1\n");
#endif
            // Else, incremenets and checks the next move.
            i++;
        } while (i < MoveCount);

        AIConditionalJump(a1, 6, 1, 1, v7);
        return a2->result;
    }

    //     int THUMB_BRANCH_AI042_GuessAbility(ScriptVM *a1, TrainerAIEnv *a2)
    //     {
    //         u32 v3;                      // r4
    //         int BattlePosFromCommandArg; // r0
    // #if DEBUGGING_AI && DEBUGGING_ALL
    //         k::Printf("\n\n--------AI042_GuessAbility-----------\n");
    // #endif
    //         v3 = VM_Read32(a1);
    //         BattlePosFromCommandArg = GetBattlePosFromCommandArg(a2, v3);
    //         a2->param = 1;
    //         return a2->result;
    //     }
    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ CHECK SLEEP TURNS -------------------------------------------
        --------------------------------------------------------------------------------------------------

        Checks to see if the number of remaining sleep turns is greater than one.
        Used for Sleep Talk, Snore, etc.

        Originally:
            AI102_Nop
    */
    int THUMB_BRANCH_AI068_CheckRemainingSleepTurns(ScriptVM *a1, TrainerAIEnv *a2)
    {
        BattleMon *attacker;
        attacker = a2->attacker;
        int destination;
        destination = VM_Read32(a1);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI102_CheckRemainingSleepTurns-----------\nIs being called for move %d, used by Pokemon %d\n\n", a2->moveID, a2->attacker->Species);
#endif
        if (BattleMon_CheckIfMoveCondition(attacker, CONDITION_SLEEP))
        {
            AIConditionalJump(a1, 0, (attacker->MoveConditionCounter[CONDITION_SLEEP] + 1), Condition_GetTurnMax(&attacker->Conditions[CONDITION_SLEEP]), destination);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------- CHECK SPEED AGAINST MULTIPLES --------------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks the speed of every enemy pokemon on the field, rather than just the one in front of them.

        Originally:
            AI103_Nop
    */
    int THUMB_BRANCH_AI089_CheckAllPokemonSpeed(ScriptVM *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        unsigned int k;
        int destination;
        destination = VM_Read32(a1);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI103_CheckAllPokemonSpeed-----------\nIs being called for move %d, used by Pokemon %d\n", a2->moveID, a2->attacker->Species);
#endif
        for (k = 0; k < pokeCount; k++)
        {

            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
#if DEBUGGING_AI && DEBUGGING_ALL
            k::Printf("Check %d for Pokemon %d\n", k, defender->ID);
#endif
            if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) < Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
            {
#if DEBUGGING_AI && DEBUGGING_ALL
                k::Printf(" - Jumping!\n\n");
#endif
                return a2->result;
            }
        }
        AIConditionalJump(a1, 0, 1, 2, destination);
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------- CHECK OWN DAMAGE AGAINST ALLY ----------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks the speed of every enemy pokemon on the field, rather than just the one in front of them.

        Originally:
            AI063_Nop
    */
    int THUMB_BRANCH_AI096_CheckOwnDamageIntoAlly(ScriptVM *a1, TrainerAIEnv *a2)
    {
        int destination;
        destination = VM_Read32(a1);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("\n\n--------AI063_CheckOwnDamageIntoAlly-----------\nIs being called for move %d, used by Pokemon %d attacking Pokemon %d\n", a2->moveID, a2->attacker->Species, a2->defender->Species);
#endif
        int damage = Handler_SimulationDamage(a2->serverFlow,
                                              BattleMon_GetID(a2->defender),
                                              BattleMon_GetID(a2->attacker),
                                              a2->moveID, false, false);
#if DEBUGGING_AI && DEBUGGING_ALL
        k::Printf("Pokemon %d HP is %d and the damage dealt by the move is %d\n\n", a2->defender->Species, BattleMon_GetValue(a2->defender, VALUE_CURRENT_HP), damage);
#endif
        AIConditionalJump(a1, 6, BattleMon_GetValue(a2->defender, VALUE_CURRENT_HP), damage, destination);
        return a2->result;
    }

#pragma endregion

#pragma region WIPIllusionChanges

#if DEBUGGING_ILLUSION
    extern int sub_219C424(MainModule *a1, int a2);

    // Test stoppping the illusion removal.
    void THUMB_BRANCH_MainModule_SetIllusionForParty(MainModule *a1, BattleParty *a2, int a3)
    {
        int i;                          // r6
        int NumBattlePositionsOfClient; // r4
        int j;                          // r0
        BattleMon *v8;                  // r7
        PartyPkm *SrcData;              // r0
        int v10;                        // r4

        for (i = a2->memberCount - 1; i > 0; --i)
        {
            if (BattleMon_CanBattle(a2->mons[i]))
            {
                break;
            }
        }
        if (BtlSetup_GetBattleStyle(a1) == BTL_STYLE_ROTATION)
        {
            NumBattlePositionsOfClient = 3;
        }
        else
        {
            NumBattlePositionsOfClient = sub_219C424(a1, a3);
        }
        for (j = a2->memberCount; NumBattlePositionsOfClient < j; ++NumBattlePositionsOfClient)
        {
            v8 = a2->mons[NumBattlePositionsOfClient];
            if (BattleMon_GetValue(v8, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
            {
                if (NumBattlePositionsOfClient >= i)
                {

                    // I think this part isn't working properly.
                    // if (BattleMon_GetViewSrcData(v8) != a1->TempPartyPkm)
                    // {
                    //     BattleMon_RemoveIllusion(v8);
                    // }
                }
                else
                {
                    // k::Printf("\nIllusion Mon ID is %d", illusionMonId);
                    SrcData = BattleMon_GetSrcData(a2->mons[illusionMonId]);
                    BattleMon_SetIllusion(v8, SrcData);
                }
            }
            j = a2->memberCount;
        }
        v10 = 0;
        if (j > 0)
        {
            do
            {
                BattleMon_IsIllusionEnabled(a2->mons[v10++]);
            } while (v10 < a2->memberCount);
        }
    }
#endif
#pragma endregion
}