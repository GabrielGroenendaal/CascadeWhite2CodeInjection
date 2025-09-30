#include "../swan-master/swantypes.h"
#include "../swan-master/system/game_data.h"

typedef void *(*ABILITY_SETUP_FUNC)(int *);
typedef void *(*ABILITY_HANDLER_FUNC)();

typedef void *(*ITEM_SETUP_FUNC)(int *);
typedef void *(*ITEM_HANDLER_FUNC)();

typedef void *(*MOVE_SETUP_FUNC)(int *);
typedef void *(*MOVE_HANDLER_FUNC)();

typedef void *(*SIDE_SETUP_FUNC)(int *);
typedef void *(*SIDE_HANDLER_FUNC)();

STRUCT_DECLARE(BattleMon)
STRUCT_DECLARE(BattleFieldStatus)
STRUCT_DECLARE(BtlSetup)
STRUCT_DECLARE(ServerFlow)
STRUCT_DECLARE(ServerCommandQueue)
STRUCT_DECLARE(SVCL_WORK)
STRUCT_DECLARE(MainModule)
STRUCT_DECLARE(BtlServerWk)
STRUCT_DECLARE(ZoneSpawnInfo)
STRUCT_DECLARE(GameData)
STRUCT_DECLARE(PlayerState)

const int dword_2199900 = 0x2199900;

enum TurnFlag
#ifdef __cplusplus
    : u32
#endif
{
    TURNFLAG_FLINCH = 4,
    TURNFLAG_FOCUSPUNCHFAIL = 6,
    TURNFLAG_ACTIONDONE = 1
};

enum BattleFieldEffect
#ifdef __cplusplus
    : u32
#endif
{
    EFFECT_WEATHER = 0x0,
    EFFECT_TRICK_ROOM = 0x1,
    EFFECT_GRAVITY = 0x2,
    EFFECT_IMPRISON = 0x3,
    EFFECT_WATER_SPORT = 0x4,
    EFFECT_MUD_SPORT = 0x5,
    EFFECT_WONDER_ROOM = 0x6,
    EFFECT_MAGIC_ROOM = 0x7,
};

enum BattleEventType
#ifdef __cplusplus
    : u32
#endif
{
    BattleEvent_CalcSpeed = 0x13,
    BattleEvent_MoveExecuteNoEffect = 0x26,
    BattleEvent_UncategorizedMoveNoTarget = 0xA1,
    BattleEvent_BeforeAttackerPower = 0x39,
    BattleEvent_BeforeDefenderGuard = 0x3A,
    BattleEvent_DefenderGuard = 0x3C,
    BattleEvent_AttackerPower = 0x3B,
    BattleEvent_CheckTypeEffectiveness = 0x3E,
    BattleEvent_MoveExecuteCheck1 = 0x1E,
    BattleEvent_MoveExecuteEnd = 0x27,
    BattleEvent_MoveHitCount = 0x35,
    BattleEvent_UseItem = 0x72,
    BattleEvent_DamageProcessingStart = 0x81,
    BattleEvent_DamageProcessingEndHitReal = 0x83
};

enum MoveFlag
#ifdef __cplusplus
    : u32
#endif
{
    FLAG_CONTACT = 0x0,
    FLAG_REQUIRES_CHARGE = 0x1,
    FLAG_RECHARGE = 0x2,
    FLAG_BLOCKED_BY_PROTECT = 0x3,
    FLAG_REFLECTED_BY_MAGIC_COAT = 0x4,
    FLAG_STOLEN_BY_SNATCH = 0x5,
    FLAG_COPIED_BY_MIRROR_MOVE = 0x6,
    FLAG_PUNCH = 0x7,
    FLAG_SOUND = 0x8,
    FLAG_GROUNDED_BY_GRAVITY = 0x9,
    FLAG_HEALING = 0xC
};

enum TypeEffectiveness
#ifdef __cplusplus
    : int
#endif
{
    EFFECTIVENESS_IMMUNE = 0,
    EFFECTIVENESS_1_4 = 1,
    EFFECTIVENESS_1_2 = 2,
    EFFECTIVENESS_1 = 3,
    EFFECTIVENESS_2 = 4,
    EFFECTIVENESS_4 = 5
};

enum BattleEventVar
#ifdef __cplusplus
    : u32
#endif
{
    VAR_MON_ID = 2,
    VAR_ATTACKING_MON = 3,
    VAR_DEFENDING_MON = 4,
    VAR_TARGETMONID = 6,
    VAR_POKE_POS = 0xD,
    VAR_PRIORITY = 0x11,
    VAR_MOVEID = 0x12,
    VAR_POKE_TYPE = 0x15,
    VAR_MOVETYPE = 0x16,
    VAR_MOVECATEGORY = 0x1A,
    VAR_CONDITIONID = 0x1D,
    VAR_CONDITIONADDRESS = 0x1E,
    VAR_STATBOOSTAMOUNT = 0x20,
    VAR_FLOATING = 0x21,
    VAR_FAILCAUSE = 0x22,
    VAR_EFFECTTURNCOUNT = 0x24,
    VAR_ADDEDEFFECT = 0x26,
    VAR_HIT_COUNT = 0x2A,
    VAR_CRITSTAGE = 0x2C,
    VAR_SPEED = 0x2F,
    VAR_MOVEPOWER = 0x30,
    VAR_MOVEPOWERRATIO = 0x31,
    VAR_POWER = 0x33,
    VAR_RATIO = 0x35,
    VAR_DAMAGE = 0x37,
    VAR_TYPEEFFECTIVENESS = 0x38,
    VAR_WEATHER = 0x39,
    VAR_ENDURE = 0x3A,
    VAR_SWAP_POKE_ID = 0x3B,
    VAR_BATTLE_MON_STAT = 0x3C,
    VAR_BATTLE_MON_STAT_SWAP_FLAG = 0x3D,
    VAR_NOEFFECTFLAG = 0x40,
    VAR_MOVEFAILFLAG = 0x41,
    VAR_SEMIINVULNERABLE = 0x42,
    VAR_CRITICALFLAG = 0x45,
    VAR_SUBSTITUTE = 0x46,
    VAR_EFFECTBLOCKED = 0x47,
    VAR_TRICK_ROOM_FLAG = 0x4A,
    VAR_NO_TYPE_EFFECTIVENESS = 0x4B,
    VAR_SET_TYPE_EFFECTIVENESS = 0x4C,
    VAR_SIDEEFFECT = 0x53,
    VAR_GENERAL_USE_FLAG = 0x51
};

enum SideEffect
#ifdef __cplusplus
    : u32
#endif
{
    SIDEEFF_REFLECT = 0x0,
    SIDEEFF_LIGHT_SCREEN = 0x1,
    SIDEEFF_SAFEGUARD = 0x2,
    SIDEEFF_MIST = 0x3,
    SIDEEFF_TAILWIND = 0x4,
    SIDEEFF_LUCKY_CHANT = 0x5,
    SIDEEFF_SPIKES = 0x6,
    SIDEEFF_TOXIC_SPIKES = 0x7,
    SIDEEFF_STEALTH_ROCK = 0x8,
    SIDEEFF_WIDE_GUARD = 0x9,
    SIDEEFF_QUICK_GUARD = 0xA,
    SIDEEFF_RAINBOW = 0xB,
    SIDEEFF_SEA_OF_FIRE = 0xC,
    SIDEEFF_SWAMP = 0xD,
};

enum BattleHandlerEffect
#ifdef __cplusplus
    : u32
#endif
{
    EFFECT_CHANGESTATSTAGE = 0xE,
    EFFECT_ABILITYPOPUPIN = 2,
    EFFECT_ABILITYPOPUPOUT = 3,
    EFFECT_CHANGEHP = 8,
    EFFECT_ADDSIDEEFFECT = 0x19,
    EFFECT_CONSUMEITEM = 0x23,
    EFFECT_MESSAGE = 4,
    EFFECT_RECOVERHP = 5,
    EFFECT_ADDCONDITION = 0xC,
    EFFECT_CURESTATUS = 0x8,
    EFFECT_DAMAGE = 0x7,
    EFFECT_REMOVE_SIDE_EFFECT = 0x1A,
    EFFECT_CURE_STATUS = 0xB,
    EFFECT_SET_HELD_ITEM = 0x20,
    EFFECT_ACTIVATEITEM = 0x22,
    EFFECT_SETANIMATIONID = 0x3A,
    EFFECT_SWAPITEM = 0x24,
    EFFECT_SWITCH = 0x29
};

enum BattleMonValue
#ifdef __cplusplus
    : u32
#endif
{
    VALUE_NULL = 0,
    VALUE_ATTACK_STAGE = 1,
    VALUE_DEFENSE_STAGE = 2,
    VALUE_SPECIAL_ATTACK_STAGE = 3,
    VALUE_SPECIAL_DEFENSE_STAGE = 4,
    VALUE_SPEED_STAGE = 5,
    VALUE_ACCURACY_STAGE = 6,
    VALUE_EVASION_STAGE = 7,
    VALUE_ATTACK_STAT = 8,
    VALUE_DEFENSE_STAT = 9,
    VALUE_SPECIAL_ATTACK_STAT = 0xA,
    VALUE_SPECIAL_DEFENSE_STAT = 0xB,
    VALUE_SPEED_STAT = 0xC,
    VALUE_CURRENT_HP = 0xD,
    VALUE_MAX_HP = 0xE,
    VALUE_LEVEL = 0xF,
    VALUE_ABILITY = 0x10,
    VALUE_EFFECTIVE_ABILITY = 0x11,
    VALUE_SEX = 0x12,
    VALUE_FORM = 0x13,
    VALUE_EXPERIENCE = 0x14,
    VALUE_15 = 0x15
};

enum StatStage
#ifdef __cplusplus
    : u32
#endif
{
    STATSTAGE_NULL = 0,
    STATSTAGE_ATTACK = 1,
    STATSTAGE_DEFENSE = 2,
    STATSTAGE_SPECIAL_ATTACK = 3,
    STATSTAGE_SPECIAL_DEFENSE = 4,
    STATSTAGE_SPEED = 5,
    STATSTAGE_ACCURACY = 6,
    STATSTAGE_EVASION = 7,
};

enum statValues
#ifdef __cplusplus
    : u32
#endif
{
    ATTACK = 1,
    DEFENSE = 2,
    SPECIAL_ATTACK = 3,
    SPECIAL_DEFENSE = 4,
    SPEED = 5,
    ACCURACY = 6,
    EVASIVENESS = 7,
};

enum Conditions
#ifdef __cplusplus
    : char
#endif
{
    CND_PARALYSIS = 1,
    CND_SLEEP = 2,
    CND_FREEZE = 3,
    CND_BURN = 4,
    CND_POISON = 5,
    CND_CONFUSION = 6,
    CND_INFATUATION = 7,
    CND_TAUNT = 11,
    CND_TORMENT = 12,
    CND_DISABLEMOVE = 13,
    CND_DROWSY = 14,
    CND_HEALBLOCK = 15,
    CND_ENCORE = 23,
    CND_EMBARGO = 35,
};

enum MoveCondition
#ifdef __cplusplus
    : u32
#endif
{
    CONDITION_NONE = 0,
    CONDITION_PARALYSIS = 1,
    CONDITION_SLEEP = 2,
    CONDITION_FREEZE = 3,
    CONDITION_BURN = 4,
    CONDITION_POISON = 5,
    CONDITION_CONFUSION = 6,
    CONDITION_INFATUATION = 7,
    CONDITION_BIND = 8,
    CONDITION_NIGHTMARE = 9,
    CONDITION_CURSE = 0xA,
    CONDITION_TAUNT = 0xB,
    CONDITION_TORMENT = 0xC,
    CONDITION_DISABLEMOVE = 0xD,
    CONDITION_DROWSY = 0xE,
    CONDITION_HEALBLOCK = 0xF,
    CONDITION_GASTROACID = 0x10,
    CONDITION_FORESIGHT = 0x11,
    CONDITION_LEECHSEED = 0x12,
    CONDITION_EMBARGO = 0x13,
    CONDITION_PERISHSONG = 0x14,
    CONDITION_INGRAIN = 0x15,
    CONDITION_BLOCK = 0x16,
    CONDITION_ENCORE = 0x17,
    CONDITION_ROOST = 0x18,
    CONDITION_MOVELOCK = 0x19,
    CONDITION_CHARGELOCK = 0x1A,
    CONDITION_CHOICELOCK = 0x1B,
    CONDITION_MUSTHIT = 0x1C,
    CONDITION_LOCKON = 0x1D,
    CONDITION_FLOATING = 0x1E,
    CONDITION_KNOCKEDDOWN = 0x1F,
    CONDITION_TELEKINESIS = 0x20,
    CONDITION_SKYDROP = 0x21,
    CONDITION_ACCURACYUP = 0x22,
    CONDITION_AQUARING = 0x23,
    CONDITION_24 = 0x24
};

enum Types
#ifdef __cplusplus
    : u8
#endif
{
    TYPE_NORMAL = 0,
    TYPE_FIGHTING = 1,
    TYPE_FLYING = 2,
    TYPE_POISON = 3,
    TYPE_GROUND = 4,
    TYPE_ROCK = 5,
    TYPE_BUG = 6,
    TYPE_GHOST = 7,
    TYPE_STEEL = 8,
    TYPE_FIRE = 9,
    TYPE_WATER = 10,
    TYPE_GRASS = 11,
    TYPE_ELECTRIC = 12,
    TYPE_PSYCHIC = 13,
    TYPE_ICE = 14,
    TYPE_DRAGON = 15,
    TYPE_DARK = 16,
    TYPE_FAIRY = 17,
    TYPE_NONE = 18,
};

enum WeatherID
#ifdef __cplusplus
    : u32
#endif
{
    WEATHER_SUN = 1,
    WEATHER_RAIN = 2,
    WEATHER_HAIL = 3,
    WEATHER_SAND = 4,
};

enum BattleStyle
#ifdef __cplusplus
    : u32
#endif
{
    BTL_STYLE_SINGLE = 0,
    BTL_STYLE_DOUBLE = 1,
    BTL_STYLE_TRIPLE = 2,
    BTL_STYLE_ROTATION = 3
};

enum ConditionFlag
#ifdef __cplusplus
    : u32
#endif
{
    CONDITIONFLAG_ACTIONDONE = 0,
    CONDITIONFLAG_NOSWITCH = 1,
    CONDITIONFLAG_CHARGE = 2,
    CONDITIONFLAG_FLY = 3,
    CONDITIONFLAG_DIVE = 4,
    CONDITIONFLAG_DIG = 5,
    CONDITIONFLAG_SHADOWFORCE = 6,
    CONDITIONFLAG_DEFENSECURL = 7,
    CONDITIONFLAG_MINIMIZE = 8,
    CONDITIONFLAG_FOCUSENERGY = 9,
    CONDITIONFLAG_POWERTRICK = 0xA,
    CONDITIONFLAG_MICLEBERRY = 0xB,
    CONDITIONFLAG_NOACTION = 0xC,
    CONDITIONFLAG_FLASHFIRE = 0xD,
    CONDITIONFLAG_BATONPASS = 0xE
};

enum ItemField
#ifdef __cplusplus
    : u32
#endif
{
    ITSTAT_PRICE = 0x0,
    ITSTAT_USE_EFFECT = 0x1,
    ITSTAT_USE_PARAM = 0x2,
    ITSTAT_FLAG1 = 0x3,
    ITSTAT_FLAG2 = 0x4,
    ITSTAT_POCKET_FIELD = 0x5,
    ITSTAT_EFFECT_FIELD = 0x6,
    ITSTAT_EFFECT_BATTLE = 0x7,
    ITSTAT_NATURAL_GIFT_EFFECT = 0x8,
    ITSTAT_FLING_EFFECT = 0x9,
    ITSTAT_FLING_POWER = 0xA,
    ITSTAT_NATURAL_GIFT_POWER = 0xB,
    ITSTAT_NATURAL_GIFT_TYPE = 0xC,
    ITSTAT_POCKET_BATTLE = 0xD,
    ITSTAT_HAS_BATTLE_STATS = 0xE,
    ITSTAT_CLASS = 0xF,
    ITSTAT_CONSUMABLE = 0x10,
    ITSTAT_SORT_IDX = 0x11,
    ITSTAT_AILMENT_SLP = 0x12,
    ITSTAT_AILMENT_PSN = 0x13,
    ITSTAT_AILMENT_BRN = 0x14,
    ITSTAT_AILMENT_FRZ = 0x15,
    ITSTAT_AILMENT_PAR = 0x16,
    ITSTAT_AILMENT_CFZ = 0x17,
    ITSTAT_AILMENT_INF = 0x18,
    ITSTAT_AILMENT_GSP = 0x19,
    ITSTAT_BOOST_REVIVE = 0x1A,
    ITSTAT_BOOST_SACRED_ASH = 0x1B,
    ITSTAT_BOOST_RARECANDY = 0x1C,
    ITSTAT_BOOST_EVOSTONE = 0x1D,
    ITSTAT_BOOST_ATK = 0x1E,
    ITSTAT_BOOST_DEF = 0x1F,
    ITSTAT_BOOST_SPA = 0x20,
    ITSTAT_BOOST_SPD = 0x21,
    ITSTAT_BOOST_SPE = 0x22,
    ITSTAT_BOOST_ACC = 0x23,
    ITSTAT_BOOST_CRIT = 0x24,
    ITSTAT_BOOST_PP1 = 0x25,
    ITSTAT_BOOST_PPMAX = 0x26,
    ITSTAT_FLAG_PPREPLENISH = 0x27,
    ITSTAT_FLAG_PPREPLENISH_FULL = 0x28,
    ITSTAT_FLAG_HPREPLENISH = 0x29,
    ITSTAT_FLAG_EVADD_HP = 0x2A,
    ITSTAT_FLAG_EVADD_ATK = 0x2B,
    ITSTAT_FLAG_EVADD_DEF = 0x2C,
    ITSTAT_FLAG_EVADD_SPE = 0x2D,
    ITSTAT_FLAG_EVADD_SPA = 0x2E,
    ITSTAT_FLAG_EVADD_SPD = 0x2F,
    ITSTAT_FLAG_EVADD_ABOVE100 = 0x30,
    ITSTAT_FLAG_FRIENDSHIP_ADD1 = 0x31,
    ITSTAT_FLAG_FRIENDSHIP_ADD2 = 0x32,
    ITSTAT_FLAG_FRIENDSHIP_ADD3 = 0x33,
    ITSTAT_EV_HP = 0x34,
    ITSTAT_EV_ATK = 0x35,
    ITSTAT_EV_DEF = 0x36,
    ITSTAT_EV_SPE = 0x37,
    ITSTAT_EV_SPA = 0x38,
    ITSTAT_EV_SPD = 0x39,
    ITSTAT_HEAL_AMOUNT = 0x3A,
    ITSTAT_PP_GAIN = 0x3B,
    ITSTAT_FRIENDSHIP1 = 0x3C,
    ITSTAT_FRIENDSHIP2 = 0x3D,
    ITSTAT_FRIENDSHIP3 = 0x3E,
};

enum MoveField
#ifdef __cplusplus
    : u16
#endif
{
    MVDATA_TYPE = 0,
    MVDATA_QUALITY = 1,
    MVDATA_CATEGORY = 2,
    MVDATA_POWER = 3,
    MVDATA_ACCURACY = 4,
    MVDATA_BASEPP = 5,
    MVDATA_PRIORITY = 6,
    MVDATA_CRIT_STAGE = 7,
    MVDATA_HIT_MAX = 8,
    MVDATA_HIT_MIN = 9,
    MVDATA_FLINCH_RATE = 0xA,
    MVDATA_INFLICT_STATUS = 0xB,
    MVDATA_INFLICT_CHANCE = 0xC,
    MVDATA_INFLICT_DURATION = 0xD,
    MVDATA_TURN_MIN = 0xE,
    MVDATA_TURN_MAX = 0xF,
    MVDATA_STAT1 = 0x10,
    MVDATA_STAT2 = 0x11,
    MVDATA_STAT3 = 0x12,
    MVDATA_STAT1_STAGE = 0x13,
    MVDATA_STAT2_STAGE = 0x14,
    MVDATA_STAT3_STAGE = 0x15,
    MVDATA_STAT1_CHANCE = 0x16,
    MVDATA_STAT2_CHANCE = 0x17,
    MVDATA_STAT3_CHANCE = 0x18,
    MVDATA_RECOIL = 0x19,
    MVDATA_HEAL = 0x1A,
    MVDATA_TARGET = 0x1B,
    MVDATA_WAZASEQ_ID = 0x1C,
    MVDATA_UNUSED = 0x1D,
    MVDATA_RECOIL_NEG = 0x1E,
    MVDATA_HEAL_NEG = 0x1F,
};

struct TrainerBattleSetup
{
    int TrID;
    int TrClass;
    int TrAIBits;
    u16 TrItems[4];
    int *TrainerName;
    __int16 field_18[4];
    __int16 field_20[4];
};

struct BattleEventItem
{
    BattleEventItem *prev;
    BattleEventItem *next;
    const char *handlerTable;
    char skipCheckHandler;
    u32 factorType;
    int currentStackPtr;
    int flags;
    int work[7];
    __int16 subID;
    char dependID;
    char pokeID;
};

struct BattleFieldStatus
{
    u32 BattleBGID;
    u32 BattlePedestalID;
    unsigned char BtlWeather;
    int Season;
    u16 ZoneID;
    u8 Hour;
    u8 Minute;
    char field_E;
    char field_F;
};
struct TrainerData
{
    u8 Flags;
    u8 Class;
    u8 BattleType;
    u8 PokemonCount;
    u16 Items[4];
    u32 AI;
    u8 Healer;
    u8 Money;
    u16 ItemAfterBattle;
};

struct MainModule
{
    BtlSetup *btlSetup;
    int field_4;
    BtlServerWk *server;
    char clients;
    char field_20;
    char field_24;
    TrainerData trainerData[4];
};

struct ServerCommandQueue
{
    int writePTR;
    int readPTR;
    int buffer;
};

struct BattleParty
{
    BattleMon *pMember[6];
    u8 memberCount;
    u8 numCoverPos;
};

struct SVCL_WORK
{
    int adapter;
    BattleParty *party;
    u8 byte8;
    u8 byte9;
    u8 byteA;
    u8 id;
};

struct BtlServerWk
{
    int a4;
};

struct ConditionData
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

struct FaintRecordUnit
{
    u8 count;
    u8 fExpChecked[24];
    u8 FaintPokeID[24];
};

struct FaintRecord
{
    FaintRecordUnit turnRecord[4];
};

struct HandlerParam_Header
{
    u32 flags;
};

struct HandlerParam_StrParams
{
    u16 ID;
    int type;
    int args[8];
};

struct HandlerParam_Switch
{
    HandlerParam_Header header;
    HandlerParam_StrParams preStr;
    HandlerParam_StrParams exStr;
    u8 pokeID;
    char fIntrDisable;
};

struct HandlerParam_ChangeHP
{
    HandlerParam_Header header;
    u8 poke_cnt;
    u8 fEffectDisable;
    u8 fItemReactionDisable;
    u8 pokeID[6];
    u32 volume[6];
    u32 damageCause;
};

struct HandlerParam_ChangeStatStage
{
    HandlerParam_Header header;
    StatStage rankType;
    u32 pad;
    s8 rankVolume;
    u8 pad2;
    u8 fMoveAnimation;
    u8 poke_cnt;
    u8 pokeID[6];
    HandlerParam_StrParams exStr;
};

struct HandlerParam_AddSideEffect
{
    HandlerParam_Header header;
    u32 effect;
    ConditionData cont;
    u8 side;
    HandlerParam_StrParams exStr;
};

struct HandlerParam_Message
{
    HandlerParam_Header header;
    HandlerParam_StrParams str;
};

struct MoveParam
{
    unsigned __int16 MoveID;
    unsigned __int16 OriginalMoveID;
    unsigned __int16 userType;
    unsigned __int8 moveType;
    char damageType;
    int category;
    int targetType;
    int flags;
};

struct BtlSetup
{
    u32 BtlType;
    BattleStyle BtlStyle;
    BattleFieldStatus m_FieldStatus;
    u16 BattleBGMID;
    __int16 WinBGMID;
    int field_1C;
    char commMode;
    char field_21;
    char field_22;
    char field_23;
    char *Parties;
    int m_PlayerInfo;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    TrainerBattleSetup *TrainerSetup[4];
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    char *m_TrainerData;
    int m_ItemWork;
    int field_7C;
    int m_Dex;
    int m_RecordData;
    int field_88;
    int field_8C;
    int field_90;
    char field_94;
    char field_95;
    char field_96;
    char field_97;
    char BadgeCount;
    char field_99;
    char field_9A;
    char field_9B;
    int field_9C;
    __int16 field_A0;
    __int16 field_A2;
    int EarnedMoney;
    char *BattleResult;
    char CapturedPkmIdx;
    char field_AD;
    __int16 field_AE;
    void *field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    u16 HPSum;
    u8 CurrentTurn;
    u8 SwitchCount;
    u8 NoEffectHits;
    u8 SuperEffectiveHits;
    u8 NotVeryEffectiveHits;
    u8 OpponentNoEffectHits;
    u8 OpponentNotVeryEffectiveHits;
    u8 BattlesWon;
    u8 OpponentFainted;
    u8 AllyFainted;
    u8 UniqueMovesUsed;
    char field_DD;
    char field_DE;
    char field_DF;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
    int field_100;
    int field_104;
    int field_108;
    int field_10C;
    char field_110;
    int field_114;
    int field_118;
    int field_11C;
    int field_120;
    int field_124;
    char field_128;
    int field_12C;
    int field_130;
    int field_134;
    __int16 field_138;
    __int16 field_13A;
    u8 KeySystemLevelAdjust;
    char field_13D;
    char field_13E;
    char field_13F;
    int field_140;
    int field_144;
    int field_148;
};

struct ZoneDataSystem
{
    char ZoneDataArc;
    char CurrentZone;
    u16 CurrentZoneId;
};
struct MoveCore

{
    u16 MoveID;
    u8 CurrentPP;
    u8 MaxPP;
    u8 PPUpCount;
    char UsedFlag;
};

struct MoveSet
{
    MoveCore truth;
    MoveCore surface;
    u8 fLinked;
};

// struct PartyPkm
// {
//     BoxPkm Base;
//     u32 StatusCond;
//     u8 Level;
//     u8 field_8D;
//     u16 NowHP;
//     u16 MaxHP;
//     u16 ATK;
//     u16 DEF;
//     u16 SPE;
//     u16 SPA;
//     u16 SPD;
//     MailData Mail;
//     u32 field_D4;
//     u32 field_D8;
// };

struct StatStageParam
{
    u8 AttackStage;
    u8 DefenseStage;
    u8 SpAttackStage;
    u8 SpDefenseStage;
    u8 SpeedStage;
    u8 AccuracyStage;
    u8 EvasionStage;
};

struct HandlerParam_SwapItem
{
    HandlerParam_Header header;
    u8 pokeID;
    u8 fIncRecordCount;
    HandlerParam_StrParams exStr;
    HandlerParam_StrParams exSubStr1;
    HandlerParam_StrParams exSubStr2;
};

struct HandlerParam_SetAnimationID
{
    HandlerParam_Header header;
    u8 animIndex;
};

struct BattleMon
{
    PartyPkm *partySrc;    // Lies
    PartyPkm *disguiseSrc; // Lies
    int Experience;
    __int16 Species;
    __int16 MaxHP;
    __int16 CurrentHP;
    __int16 HeldItem;
    __int16 UsedItem;
    __int16 Ability;
    char Level;
    char ID;
    char field_1A;
    char flags;
    u32 Conditions[36];
    u8 MoveConditionCounter[36];
    char ConfrontRecCount;
    u8 ConfrontRec[24];
    char *gapE9[5];
    __int16 Attack;
    __int16 Defense;
    __int16 SpecialAttack;
    __int16 SpecialDefense;
    __int16 Speed;
    char Type1;
    char Type2;
    char Sex;
    char field_FB;
    StatStageParam statStageParam; // DifferentType
    char field_103;
    MoveSet MoveSets[4];
    ; // Different Type
    __int16 CurrentAbility;
    __int16 Weight;
    char MoveCount;
    char Form;
    char CritStage;
    char UsedMoveCount;
    char PrevMoveType;
    char field_145;
    __int16 TurnCount;
    __int16 AppearedTurn;
    __int16 PreviousMove;
    __int16 PreviousMoveID;
    __int16 ConsecutiveMoveCounter;
    __int16 field_150;
    char prevTargetPos;
    u8 TurnFlag[2];
    u8 ConditionFlag[2];
    u8 Counters[5];
    char MoveDamageRec[3][6]; // Different Type
    unsigned __int8 DamageRecCount[3];
    char DamageRecTurn;
    char DamageRec;
    char field_1F1;
    __int16 SubstituteHP;
    __int16 comboMoveID;
    char comboPokeID;
    char field_1F7;
};

struct HandlerParam_ConsumeItem
{
    HandlerParam_Header header;
    int fNoAction;
    HandlerParam_StrParams exStr;
};
struct HandlerParam_AddCondition
{
    HandlerParam_Header header;
    MoveCondition sickID;
    ConditionData sickCont;
    u8 fAlmost;
    u8 reserved;
    u8 overwriteMode;
    u8 pokeID;
    u8 OverwriteMode;
    HandlerParam_StrParams exStr;
};

struct HandlerParam_CureStatus
{
    HandlerParam_Header header;
    MoveCondition sickCode;
    u8 pokeID[12];
    u8 poke_cnt;
    u8 fStdMsgDisable;
    HandlerParam_StrParams exStr;
};

struct BtlClientWk
{
    MainModule *mainModule;
};

struct TrainerAIEnv
{
    char aiState;
    unsigned __int8 consideredMoveIndex;
    unsigned __int16 moveID;
    int scores[4];
    char field_14;
    char field_15;
    char field_16;
    char field_17;
    char field_18;
    char field_19;
    char field_1A;
    char field_1B;
    char field_1C;
    char field_1D;
    char field_1E;
    char field_1F;
    char field_20;
    char field_21;
    char field_22;
    char field_23;
    unsigned __int16 bestScoreForTarget[6];
    char bestMoveIndexForTarget[6];
    int param;
    int aiFlags;
    char aiFlagsFromTrainerData;
    char flags;
    char scriptID;
    char chosenMoveIndex;
    char chosenTarget;
    unsigned __int8 randPerMoveIndex[4];
    unsigned __int16 defenderUsedMoves[6][4];
    char field_7C;
    char gap7D[23];
    unsigned __int8 attackerPos;
    unsigned __int8 defenderPos;
    char BattleStyle;
    char BattleType;
    __int16 HeapID;
    char ScriptsHandle;
    char ItemArcHandle;
    int scriptPtr;
    MainModule *mainModule;
    ServerFlow *serverFlow;
    char *pokeCon;
    BattleMon *attacker;
    BattleMon *defender;
    int result;
    int field_C8;
    int seededRandom;
    char time;
};

struct PokeCon
{
    MainModule *mainModule;
    BattleParty party[4];
    PokeParty *srcParty[4];
    BattleMon *activePokeParam[24];
    int fForServer;
};

struct HandlerParam_Damage
{
    HandlerParam_Header header;
    u16 damage;
    u8 pokeID;
    unsigned __int8 fAvoidHidePoke : 1;
    unsigned __int8 fExEffect : 1;
    unsigned __int8 fDisableDeadProcess : 1;
    unsigned __int8 pad : 5;
    u16 effectNo;
    u8 posFrom;
    u8 posTo;
    HandlerParam_StrParams exStr;
};

struct HandlerParam_RecoverHP
{
    HandlerParam_Header header;
    u16 recoverHP;
    u8 pokeID;
    u8 fFailCheckThru;
    HandlerParam_StrParams exStr;
};

struct ServerFlow
{
    BtlServerWk *server;
    MainModule *mainModule;
    PokeCon *pokeCon;
    ServerCommandQueue *serverCommandQueue;
    int turnCount;
    int flowResult;
    int heapHandle;
    int MoveRecord;
    int FaintRecord;
    int evolutionDataPtr;
};

struct ItemBattleStats
{
    u8 CureInflict;
    u8 Boost[4];
    u8 FunctionFlags0;
    u8 FunctionFlags1;
    char EVHP;
    char EVATK;
    char EVDEF;
    char EVSPE;
    char EVSPA;
    char EVSPD;
    u8 HealAmount;
    u8 PPGain;
    char Friendship1;
    char Friendship2;
    char Friendship3;
    char field_1F;
    char field_20;
};

struct ItemData
{
    u16 Price;
    u8 HeldEffect;
    u8 HeldArgument;
    u8 NaturalGiftEffect;
    u8 FlingEffect;
    u8 FlingPower;
    u8 NaturalGiftPower;
    u16 Packed;
    u8 EffectField;
    u8 EffectBattle;
    u8 HasBattleStats;
    u8 ItemClass;
    u8 Consumable;
    u8 SortIndex;
    ItemBattleStats BattleStats;
};

struct HandlerParam_ActivateItem
{
    HandlerParam_Header header;
    u8 pokeID;
    u8 bAteKinomi;
    u16 itemID;
};

struct HandlerParam_RemoveSideEffect
{
    HandlerParam_Header header;
    u8 flags[3];
    u8 side;
};

struct HandlerParam_CureCondition
{
    HandlerParam_Header header;
    MoveCondition sickCode;
    u8 pokeID[12];
    u8 poke_cnt;
    u8 fStdMsgDisable;
    HandlerParam_StrParams exStr;
};

struct HandlerParam_SetItem
{
    HandlerParam_Header header;
    u16 itemID;
    u8 pokeID;
    u8 fClearConsume;
    u8 fClearConsumeOtherPoke;
    u8 clearConsumePokeID;
    u8 fCallConsumedEvent;
    HandlerParam_StrParams exStr;
};
// struct SaveControl
// {
//     u8 Status;
//     u8 SaveDataAlreadyPresent;
//     u8 byte2;
//     u8 field_3[9];
//     u32 field_C;
//     char *SaveData;
//     u32 SaveExtra[21];
//     u32 dword68;
// };

// struct PlayerState
// {
//     u16 ZoneID;
//     char VecPos;
//     char RailPos;
//     char RotationAngle;
//     u8 field_1A;
//     u8 IsPosRail;
//     u16 NowOBJCODE;
//     __int16 field_1E;
//     int field_20;
//     int field_24;
//     int field_28;
//     int field_2C;
//     int field_30;
//     int field_34;
//     int field_38;
//     int field_3C;
//     char ExState;
// };

// struct ZoneSpawnInfo
// {
//     u32 ChangeType;
//     u16 ZoneID;
//     u16 WarpID;
//     u16 WarpDir;
//     u16 PosWeightBits;
//     b32 IsRail;
//     char Pos;
// };

// struct GameData
// {
//     SaveControl *m_SaveControl;
//     u8 field_4[272];
//     PlayerState m_PlayerState;
//     char *m_EventData;
//     char *m_PlayerSaveData;
//     ZoneSpawnInfo *NowZoneSpawnInfo;
//     ZoneSpawnInfo *WarpRememberZoneInfo;
//     ZoneSpawnInfo *NextSpawnZone;
//     ZoneSpawnInfo *EscapeRopeZone;
//     ZoneSpawnInfo EntralinkParentSpawnInfo;
//     void *m_MyItemSave;
//     char *m_Bag;
//     char *m_Party;
//     void *dword198;
//     char *m_BoxSaveAccessor;
//     void *dword1A0;
//     char *m_BGMInfo;
//     char *m_ActorSystem;
//     char *m_EventWork;
//     char *m_MapMatrix;
//     char *m_FieldSoundSystem;
//     BattleFieldStatus *m_FieldStatus;
//     char LastBattleResult;
//     u8 PauseEvents;
//     char field_1C1;
//     u8 field_1C2;
//     char field_1C3;
//     u32 TotalStepsTaken;
//     u8 NaturalSeason;
//     u8 NowWeather;
//     u8 LastFieldSubscreen;
//     u8 byte1CB;
//     u8 byte1CC;
//     char byte1CD;
//     u8 SkipFrameCounter;
//     u8 Is30FPSMode;
//     u16 field_1D0;
//     u8 ForceSeasonSync;
//     char field_1D3;
//     char field_1D4[76];
//     char *m_EncountState;
//     char char224;
//     char gap225[3];
//     char m_GimmickState;
// };

const int FLAIL_POWER_TABLE[6] = {
    0xC80001, 0x960004, 0x640009, 0x500010, 0x280020, 0x140030};

const int normalTypeChart[18][18] = {
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

const int chargestoneTypeChart[18][18] = {
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
    {4, 4, 8, 4, 2, 4, 4, 4, 4, 4, 8, 2, 2, 4, 4, 2, 4, 4},
    {4, 8, 4, 8, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 0, 4},
    {4, 4, 8, 4, 8, 4, 4, 4, 2, 2, 2, 8, 4, 4, 2, 8, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 4, 0},
    {4, 2, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 2},
    {4, 8, 4, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 8, 8, 4}};

const int opelucidTypeChart[18][18] = {
    {4, 4, 4, 4, 4, 2, 4, 0, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {8, 4, 2, 2, 4, 8, 2, 2, 8, 4, 4, 4, 4, 2, 8, 4, 8, 2},
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
    {4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 4, 2},
    {4, 2, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 2},
    {4, 8, 4, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 8, 8, 4}};

const int celestialTypeChart[18][18] = {
    {4, 4, 4, 4, 4, 2, 4, 0, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {8, 4, 2, 2, 4, 8, 2, 0, 8, 4, 4, 4, 4, 2, 8, 4, 8, 2},
    {4, 8, 4, 4, 4, 2, 8, 4, 2, 4, 4, 8, 2, 4, 4, 4, 4, 4},
    {4, 4, 4, 2, 2, 2, 4, 2, 0, 4, 4, 8, 4, 4, 4, 4, 4, 8},
    {4, 4, 0, 8, 4, 8, 2, 4, 8, 8, 4, 2, 8, 4, 4, 4, 4, 4},
    {4, 2, 8, 4, 2, 4, 8, 4, 2, 8, 4, 4, 4, 4, 8, 4, 4, 4},
    {4, 2, 2, 2, 4, 4, 4, 2, 2, 2, 4, 8, 4, 8, 4, 4, 8, 2},
    {2, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 4},
    {4, 4, 4, 4, 4, 8, 4, 4, 2, 2, 2, 4, 2, 4, 8, 4, 4, 8},
    {4, 4, 4, 4, 4, 2, 8, 4, 8, 2, 2, 8, 4, 4, 8, 2, 4, 4},
    {4, 4, 4, 4, 8, 8, 4, 4, 4, 8, 2, 2, 4, 4, 4, 2, 4, 4},
    {4, 4, 2, 2, 8, 8, 2, 4, 2, 2, 8, 2, 4, 4, 4, 2, 4, 4},
    {4, 4, 8, 4, 0, 4, 4, 4, 4, 4, 8, 2, 2, 4, 4, 2, 4, 4},
    {4, 8, 4, 8, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 2, 4},
    {4, 4, 8, 4, 8, 4, 4, 4, 2, 2, 2, 8, 4, 4, 2, 8, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 4, 0},
    {4, 2, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 2},
    {4, 8, 4, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 8, 8, 4}};

const int testTypeChart[18][18] = {
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}};

const int FreezeDryTypeChart[18][18] = {
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
    {4, 4, 8, 4, 8, 4, 4, 4, 2, 2, 8, 8, 4, 4, 2, 8, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 4, 0},
    {4, 2, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 8, 4, 4, 2, 2},
    {4, 8, 4, 2, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 8, 8, 4}};

const int SkyUppercutTypeChart[18][18] = {
    {4, 4, 4, 4, 4, 2, 4, 0, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {8, 4, 8, 2, 4, 8, 2, 0, 8, 4, 4, 4, 4, 2, 8, 4, 8, 2},
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

const int CorrosionTypeChart[18][18] = {
    {4, 4, 4, 4, 4, 2, 4, 0, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {8, 4, 2, 2, 4, 8, 2, 0, 8, 4, 4, 4, 4, 2, 8, 4, 8, 2},
    {4, 8, 4, 4, 4, 2, 8, 4, 2, 4, 4, 8, 2, 4, 4, 4, 4, 4},
    {4, 4, 4, 2, 2, 2, 4, 2, 8, 4, 4, 8, 4, 4, 4, 4, 4, 8},
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