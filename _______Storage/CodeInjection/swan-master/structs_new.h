#include "swantypes.h"
// #include "system/game_data.h"

typedef void *(*ABILITY_SETUP_FUNC)(int *);
typedef void *(*ABILITY_HANDLER_FUNC)();

typedef void *(*ITEM_SETUP_FUNC)(int *);
typedef void *(*ITEM_HANDLER_FUNC)();

typedef void *(*MOVE_SETUP_FUNC)(int *);
typedef void *(*MOVE_HANDLER_FUNC)();

typedef void *(*SIDE_SETUP_FUNC)(int *);
typedef void *(*SIDE_HANDLER_FUNC)();

STRUCT_DECLARE(BtlServerWk)
STRUCT_DECLARE(GameData)
STRUCT_DECLARE(PlayerState)
STRUCT_DECLARE(ConditionData)
STRUCT_DECLARE(PosPoke)

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
enum ActionIgnoreReason
{
    REASON_NONE = 0x0,
    REASON_OTHER_MOVE = 0x1,
    REASON_FALL_ASLEEP = 0x2,
    REASON_CONFUSION = 0x3,
    REASON_OVERLEVELED = 0x4,
    REASON_ASLEEP = 0x5,
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

enum BtlType
{
    BtlType_Wild = 0x0,
    BtlType_Trainer = 0x1,
    BtlType_Facility = 0x2,
    BtlType_Online = 0x3,
    BtlType_Demo = 0x4,
    BtlType_Max = 0x5,
};

enum BattleSetupType : unsigned __int8
{
    TYPE_STANDARD = 0x0,
    TYPE_NET_MULTI = 0x1,
    TYPE_NET_MULTI_VS_AI = 0x2,
    TYPE_AI_MULTI = 0x3,
    TYPE_AI_1V2 = 0x4,
    TYPE_AI_MULTI_VS_WILD = 0x5,
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
enum PkmField
{
    PF_PID = 0x0,
    PF_Species = 0x5,
    PF_Item = 0x6,
    PF_IdSet = 0x7,
    PF_Experience = 0x8,
    PF_Happiness = 0x9,
    PF_Ability = 0xA,
    PF_Markings = 0xB,
    PF_Region = 0xC,
    PF_EvHP = 0xD,
    PF_EvATK = 0xE,
    PF_EvDEF = 0xF,
    PF_EvSPE = 0x10,
    PF_EvSPA = 0x11,
    PF_EvSPD = 0x12,
    PF_ContestCool = 0x13,
    PF_ContestBeauty = 0x14,
    PF_ContestCute = 0x15,
    PF_ContestSmart = 0x16,
    PF_ContestTough = 0x17,
    PF_ContestSheen = 0x18,
    PF_RibbonChampionSinnoh = 0x19,
    PF_RibbonAbility = 0x1A,
    PF_RibbonAbilityGreat = 0x1B,
    PF_RibbonAbilityDouble = 0x1C,
    PF_RibbonAbilityMulti = 0x1D,
    PF_RibbonAbilityPair = 0x1E,
    PF_RibbonAbilityWorld = 0x1F,
    PF_RibbonAlert = 0x20,
    PF_RibbonShock = 0x21,
    PF_RibbonDowncast = 0x22,
    PF_RibbonCareless = 0x23,
    PF_RibbonRelax = 0x24,
    PF_RibbonSnooze = 0x25,
    PF_RibbonSmile = 0x26,
    PF_RibbonGorgeous = 0x27,
    PF_RibbonRoyal = 0x28,
    PF_RibbonGorgeousRoyal = 0x29,
    PF_RibbonFootprint = 0x2A,
    PF_RibbonRecord = 0x2B,
    PF_RibbonEvent = 0x2C,
    PF_RibbonLegend = 0x2D,
    PF_RibbonChampionWorld = 0x2E,
    PF_RibbonBirthday = 0x2F,
    PF_RibbonSpecial = 0x30,
    PF_RibbonSouvenir = 0x31,
    PF_RibbonWishing = 0x32,
    PF_RibbonClassic = 0x33,
    PF_RibbonPremier = 0x34,
    PF_Ribbon0x35 = 0x35,
    PF_Move1 = 0x36,
    PF_Move2 = 0x37,
    PF_Move3 = 0x38,
    PF_Move4 = 0x39,
    PF_Move1PP = 0x3A,
    PF_Move2PP = 0x3B,
    PF_Move3PP = 0x3C,
    PF_Move4PP = 0x3D,
    PF_Move1PPUp = 0x3E,
    PF_Move2PPUp = 0x3F,
    PF_Move3PPUp = 0x40,
    PF_Move4PPUp = 0x41,
    PF_Move1PPMax = 0x42,
    PF_Move2PPMax = 0x43,
    PF_Move3PPMax = 0x44,
    PF_Move4PPMax = 0x45,
    PF_IvHP = 0x46,
    PF_IvATK = 0x47,
    PF_IvDEF = 0x48,
    PF_IvSPE = 0x49,
    PF_IvSPA = 0x4A,
    PF_IvSPD = 0x4B,
    PF_IsEgg = 0x4C,
    PF_RibbonG3Cool = 0x4D,
    PF_RibbonG3CoolSuper = 0x4E,
    PF_RibbonG3CoolHyper = 0x4F,
    PF_RibbonG3CoolMaster = 0x50,
    PF_RibbonG3Beauty = 0x51,
    PF_RibbonG3BeautySuper = 0x52,
    PF_RibbonG3BeautyHyper = 0x53,
    PF_RibbonG3BeautyMaster = 0x54,
    PF_RibbonG3Cute = 0x55,
    PF_RibbonG3CuteSuper = 0x56,
    PF_RibbonG3CuteHyper = 0x57,
    PF_RibbonG3CuteMaster = 0x58,
    PF_RibbonG3Smart = 0x59,
    PF_RibbonG3SmartSuper = 0x5A,
    PF_RibbonG3SmartHyper = 0x5B,
    PF_RibbonG3SmartMaster = 0x5C,
    PF_RibbonG3Tough = 0x5D,
    PF_RibbonG3ToughSuper = 0x5E,
    PF_RibbonG3ToughHyper = 0x5F,
    PF_RibbonG3ToughMaster = 0x60,
    PF_RibbonChampionHoenn = 0x61,
    PF_RibbonWinning = 0x62,
    PF_RibbonVictory = 0x63,
    PF_RibbonArtist = 0x64,
    PF_RibbonEffort = 0x65,
    PF_RibbonChampionBattle = 0x66,
    PF_RibbonChampionRegional = 0x67,
    PF_RibbonChampionNational = 0x68,
    PF_RibbonCountry = 0x69,
    PF_RibbonNational = 0x6A,
    PF_RibbonEarth = 0x6B,
    PF_RibbonWorld = 0x6C,
    PF_FatefulEncounter = 0x6D,
    PF_Sex = 0x6E,
    PF_Forme = 0x6F,
    PF_Nature = 0x70,
    PF_IsHiddenAbility = 0x71,
    PF_NicknameStrBuf = 0x73,
    PF_NicknameRaw = 0x74,
    PF_HasNickname = 0x75,
    PF_MetGameVersion = 0x77,
    PF_RibbonG4Cool = 0x78,
    PF_RibbonG4CoolGreat = 0x79,
    PF_RibbonG4CoolUltra = 0x7A,
    PF_RibbonG4CoolMaster = 0x7B,
    PF_RibbonG4Beauty = 0x7C,
    PF_RibbonG4BeautyGreat = 0x7D,
    PF_RibbonG4BeautyUltra = 0x7E,
    PF_RibbonG4BeautyMaster = 0x7F,
    PF_RibbonG4Cute = 0x80,
    PF_RibbonG4CuteGreat = 0x81,
    PF_RibbonG4CuteUltra = 0x82,
    PF_RibbonG4CuteMaster = 0x83,
    PF_RibbonG4Smart = 0x84,
    PF_RibbonG4SmartGreat = 0x85,
    PF_RibbonG4SmartUltra = 0x86,
    PF_RibbonG4SmartMaster = 0x87,
    PF_RibbonG4Tough = 0x88,
    PF_RibbonG4ToughGreat = 0x89,
    PF_RibbonG4ToughUltra = 0x8A,
    PF_RibbonG4ToughMaster = 0x8B,
    PF_Ribbon0x8C = 0x8C,
    PF_OTNameStrBuf = 0x8D,
    PF_OTNameRaw = 0x8E,
    PF_HatchDateYear = 0x8F,
    PF_HatchDateMonth = 0x90,
    PF_HatchDateDay = 0x91,
    PF_MetYear = 0x92,
    PF_MetMonth = 0x93,
    PF_MetDay = 0x94,
    PF_HatchLocation = 0x95,
    PF_MetLocation = 0x96,
    PF_Pokerus = 0x97,
    PF_Pokeball = 0x98,
    PF_MetLevel = 0x99,
    PF_TrGender = 0x9A,
    PF_GroundTile = 0x9B,
    PF_StatusCond = 0x9D,
    PF_Level = 0x9E,
    PF_NowHP = 0xA0,
    PF_MaxHP = 0xA1,
    PF_ATK = 0xA2,
    PF_DEF = 0xA3,
    PF_SPE = 0xA4,
    PF_SPA = 0xA5,
    PF_SPD = 0xA6,
    PF_Mail = 0xA7,
    PF_IsSpeciesValid = 0xA9,
    PF_LegalSpecies = 0xAB,
    PF_IVsAll = 0xAC,
    PF_IsNotNidoran = 0xAD,
    PF_Type1 = 0xAE,
    PF_Type2 = 0xAF,
    PF_NicknameStrBufKeepFlags = 0xB0,
    PF_NicknameRawKeepFlags = 0xB1,
    PF_NPokemon = 0xB2,
    PF_PokestarFame = 0xB3,
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
enum BattleResult
{
    BTL_RESULT_DEFEAT = 0x0,
    BTL_RESULT_VICTORY = 0x1,
    BTL_RESULT_DRAW = 0x2,
    BTL_RESULT_FLEE = 0x3,
    BTL_RESULT_FLEE_FOE = 0x4,
    BTL_RESULT_CAPTURE = 0x5,
    BTL_RESULT_6 = 0x6,
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
enum MoveTarget
{
    TARGET_OTHER_SELECT = 0x0,
    TARGET_ALLY_USER_SELECT = 0x1,
    TARGET_ALLY_SELECT = 0x2,
    TARGET_ENEMY_SELECT = 0x3,
    TARGET_OTHER_ALL = 0x4,
    TARGET_ENEMY_ALL = 0x5,
    TARGET_ALLY_ALL = 0x6,
    TARGET_USER = 0x7,
    TARGET_ALL = 0x8,
    TARGET_ENEMY_RANDOM = 0x9,
    TARGET_FIELD = 0xA,
    TARGET_SIDE_ENEMY = 0xB,
    TARGET_SIDE_ALLY = 0xC,
    TARGET_UNKNOWN = 0xD,
};

enum BattleEventItemType
{
    EVENTITEM_MOVE = 0x0,
    EVENTITEM_POS = 0x1,
    EVENTITEM_SIDE = 0x2,
    EVENTITEM_FIELD = 0x3,
    EVENTITEM_ABILITY = 0x4,
    EVENTITEM_ITEM = 0x5,
    EVENTITEM_ISOLATED = 0x6,
    EVENTITEM_MAX = 0x7,
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

struct SWAN_ALIGNED(2) StrBuf
{
    u16 CharCapacity;
    u16 CharCount;
    u32 Magic;
    __int16 String[];
};

struct ZoneSpawnInfo
{
    u32 ChangeType;
    u16 ZoneID;
    u16 WarpID;
    u16 WarpDir;
    u16 PosWeightBits;
    b32 IsRail;
    char Pos[12];
};
struct TrainerBattleSetup
{
    _DWORD TrID;
    _DWORD TrClass;
    _DWORD TrAIBits;
    u16 TrItems[4];
    StrBuf *TrainerName;
    __int16 field_18[4];
    __int16 field_20[4];
};

struct ConditionData
{
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

struct BattleField
{
    int Weather;
    int WeatherTurns;
    void *BattleEventItems[8];
    ConditionData conditionData[8];
    u32 TurnCount[8];
    u32 DependPokeID[8][6];
    u32 DependPokeCount[8];
    u32 EffectEnableFlags[8];
};

struct EscapeInfo
{
    u32 count;
    u8 clientID[4];
};

struct SWAN_ALIGNED(2) MoveCore
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

struct Btlv_StringParam
{
    u16 strID;
    u8 wait;
    u8 strTypeAndArgCount;
    int args[8];
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

struct MoveDamageRec
{
    u16 moveID;
    u16 damage;
    u8 damageType;
    u8 moveType;
    u8 pokeID;
    u8 pokePos;
};
struct PkmBufferChunk
{
    char RawData[32];
};

struct PkmBuffer
{
    PkmBufferChunk Chunks[4];
};

struct SWAN_ALIGNED(4) BoxPkm
{
    u32 pid;
    u16 SanityFlags;
    u16 checksum;
    PkmBuffer ContentBuffer;
};

struct MailData
{
    u32 TID;
    _BYTE TrainerGender;
    _BYTE Region;
    _BYTE GameVersion;
    _BYTE byte7;
    char StringContent[16];
    __int16 field_18;
    __int16 field_1A;
    __int16 field_1C;
    _WORD word1E;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
};

struct PartyPkm
{
    BoxPkm Base;
    u32 StatusCond;
    u8 Level;
    u8 field_8D;
    u16 NowHP;
    u16 MaxHP;
    u16 ATK;
    u16 DEF;
    u16 SPE;
    u16 SPA;
    u16 SPD;
    MailData Mail;
    u32 field_D4;
    u32 field_D8;
};
struct PokeParty
{
    u32 PokemonCapacity;
    u32 PokemonCount;
    PartyPkm Pokemon[6];
    u8 PresentMemberBits;
    u8 _pad1;
    u16 _pad2;
};
struct SWAN_ALIGNED(4) BattleMon
{
    PartyPkm *partySrc;
    PartyPkm *disguiseSrc;
    int Experience;
    __int16 Species;
    __int16 MaxHP;
    __int16 CurrentHP;
    __int16 HeldItem;
    __int16 UsedItem;
    __int16 Ability;
    char Level;
    char ID;
    char BaseAttack;
    char flags;
    ConditionData Conditions[36];
    u8 MoveConditionCounter[36];
    char ConfrontRecCount;
    u8 ConfrontRec[24];
    _BYTE gapE9[5];
    __int16 Attack;
    __int16 Defense;
    __int16 SpecialAttack;
    __int16 SpecialDefense;
    __int16 Speed;
    char Type1;
    char Type2;
    char Sex;
    char field_FB;
    StatStageParam statStageParam;
    char field_103;
    MoveSet Moves[4];
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
    MoveDamageRec DamageRec[3][6];
    unsigned __int8 DamageRecCount[3];
    char DamageRecTurn;
    char DamageRecPtr;
    char field_1F1;
    __int16 SubstituteHP;
    __int16 comboMoveID;
    char comboPokeID;
    char field_1F7;
};

struct PokeSelectResult
{
    u8 selIdx[3];
    u8 outPokeIdx[3];
    u8 count;
    char field_7;
    char fCancel;
};
struct SWAN_ALIGNED(4) BattleEventItem
{
    BattleEventItem *prev;
    BattleEventItem *next;
    const char *handlerTable;
    char skipCheckHandler;
    BattleEventItemType factorType;
    int priority;
    int flags;
    int work[7];
    u16 subID;
    u8 dependID;
    u8 pokeID;
};

struct SWAN_ALIGNED(2) BattleFieldStatus
{
    u32 BattleBGID;
    _DWORD BattlePedestalID;
    _BYTE BtlWeather;
    u8 Season;
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

struct TrainerParam
{
    int pTrainerInfo;
    int Name;
    __int16 Class;
    __int16 ID;
    int AIFlags;
    u16 Items[4];
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
};

struct BattleParty
{
    BattleMon *pMember[6];
    u8 memberCount;
    u8 numCoverPos;
};

struct PokeSelectParam
{
    BattleParty *party;
    u8 numSelect;
    u8 prohibit[6];
    u8 bDisabledPutPosSequence;
};
struct PokeCon
{
    int* mainModule;
    BattleParty party[4];
    PokeParty *srcParty[4];
    BattleMon *activePokeParam[24];
    int fForServer;
};
struct BattleAction_Default
{
    unsigned __int32 cmd : 4;
    unsigned __int32 param : 28;
};
struct BattleAction_Fight
{
    unsigned __int32 cmd : 4;
    unsigned __int32 targetPos : 4;
    unsigned __int32 moveID : 16;
    unsigned __int32 pad : 8;
};
struct BattleAction_Item
{
    unsigned __int32 cmd : 4;
    unsigned __int32 targetIdx : 3;
    unsigned __int32 itemID : 16;
    unsigned __int32 param : 8;
    unsigned __int32 pad : 1;
};
struct BattleAction_Switch
{
    unsigned __int32 cmd : 4;
    unsigned __int32 posIdx : 3;
    unsigned __int32 memberIdx : 3;
    unsigned __int32 depleteFlag : 1;
    unsigned __int32 pad : 21;
};
struct BattleAction_Run
{
    unsigned __int32 cmd : 4;
    unsigned __int32 pad : 28;
};
union BattleActionParam
{
    BattleAction_Fight Attack;
    BattleAction_Item Item;
    BattleAction_Switch Switch;
    BattleAction_Run Run;
    BattleAction_Default Default;
};
struct SWAN_ALIGNED(4) BtlSetup
{
    BtlType btlType;
    BattleStyle BtlStyle;
    BattleFieldStatus m_FieldStatus;
    u16 BattleBGMID;
    __int16 WinBGMID;
    int field_1C;
    char commMode;
    char field_21;
    BattleSetupType BtlSetupType;
    char field_23;
    PokeParty *Parties[4];
    int m_PlayerInfo;
    int field_38;
    int field_3C;
    int field_40;
    u8 field_44[4];
    TrainerBattleSetup *TrainerSetups[4];
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    GameData *gameData;
    TrainerData *m_TrainerData;
    int *m_ItemWork;
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
    BattleResult battleResult;
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
    u8 field_DF;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
    int field_100[4];
    char field_110;
    int field_114;
    int field_118;
    int field_11C;
    int field_120;
    int field_124;
    char field_128;
    u8 field_129;
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
struct SWAN_ALIGNED(32) MainModule
{
    BtlSetup *btlSetup;
    int *BtlvCore;
    int *server[2];
    int *clients[4];
    TrainerParam trainerParam[4];
    int playerInfo;
    u8 field_C4[4];
    char pokeconClient[232];
    char pokeconServer[232];
    PokeParty *srcParty[4];
    PokeParty *srcPartyForServer[4];
    PokeParty *tempParty;
    BattleField *battleField;
    PartyPkm *TempPartyPkm;
    int field_2C4;
    int field_2C8;
    int field_2CC;
    int field_2D0;
    int field_2D4;
    _BYTE gap2D8[260];
    int field_3DC;
    int chatotChatterBlk[4];
    int randomSeed;
    int field_3F4;
    int field_3F8;
    int field_3FC;
    int field_400;
    int field_404;
    int field_408;
    int field_40C;
    int field_410;
    int field_414;
    int field_418;
    int field_41C;
    __int16 field_420;
    SWAN_PACKED SWAN_ALIGNED(1) int field_422;
    char field_426;
    char field_427;
    unsigned __int8 field_428[6];
    char field_42E;
    char field_42F;
    int winMoney;
    int bonusMoney;
    int loseMoney;
    int field_43C;
    __int16 field_440;
    __int16 CmdLimitTime;
    int serverResult;
    EscapeInfo escapeInfo;
    int subproc;
    int field_454;
    int field_458;
    int field_45C;
    int subseq;
    int field_464;
    HeapID heapID;
    char field_46A;
    char field_46B;
    char playerClientID;
    char field_46D;
    char field_46E;
    char field_46F;
    char field_470;
    char field_471;
    char CurrentTrainer;
    char field_473;
    int pokestarScriptPtr;
    int pokestarScriptHeapPtr;
    int field_47C;
};

struct SWAN_PACKED SWAN_ALIGNED(4) BtlClientWk
{
    MainModule *mainModule;
    int *pokeCon;
    int *procPoke;
    int *procAction;
    int *recData;
    int battleRecReader;
    char recPlayer[14];
    SWAN_ALIGNED(4)
    _DWORD dword28;
    EscapeInfo escapeInfo;
    BattleField *battleField;
    _BYTE gap38[24];
    int *adapter;
    int *BtlvCore;
    Btlv_StringParam strParam;
    int field_7C;
    Btlv_StringParam field_80;
    _BYTE gapA4[4];
    _DWORD cmdCheckServer;
    BattleMon *Party[6];
    int field_C4;
    int field_C8;
    char field_CC;
    int (*field_D0)(BtlClientWk *, int *) SWAN_ALIGNED(4);
    int field_D4;
    int (*ActionSelectProc)(BtlClientWk *a1, unsigned int *a2);
    unsigned int ActionSelectSeq;
    int *returnDataActionSelect;
    int returnDataActionSelectCount;
    int field_E8;
    _WORD cmdLimitTime;
    _WORD wordEE;
    unsigned __int16 AIBagItems[4];
    int *VM;
    _QWORD rand1;
    _QWORD rand2;
    _QWORD rand3;
    u8 field_114[6];
    u8 field_11A[4];
    SWAN_ALIGNED(4)
    BattleParty *actPokeParty;
    unsigned __int8 myCoverPosNum;
    unsigned __int8 procPokeIdx;
    char prevPokeIdx;
    u8 firstPokeIdx;
    char fStdMsgChanged;
    char field_129;
    char field_12A;
    SWAN_ALIGNED(2)
    BattleActionParam actionParam[3];
    u8 field_138[4];
    int cmdQueue;
    int ServerCmdArgs;
    _BYTE gap144[60];
    int serverCmd;
    int ServerCmd;
    int ServerCmdSeq;
    PokeSelectParam pokeSelectParam;
    PokeSelectResult pokeSelectResult;
    char field_1A1;
    HeapID TrainerMsgHeapID;
    char field_1A4;
    SWAN_ALIGNED(2)
    u16 field_1A6;
    _WORD SelItemWork[3];
    u8 myID;
    char field_1AF;
    _BYTE gap1B0;
    char commWaitInfoOn;
    char field_1B2;
    char field_1B3;
    _BYTE field_1B4;
    u8 forceQuitActionSelect;
    _BYTE cmdCheckTimingCode;
    char currentActionCount;
    char moveInfoPokeIdx;
    char moveInfoMoveIdx;
    char actSelectFlags;
    char myChangePokeCount;
    char field_1BC;
    u8 field_1BD;
    unsigned __int8 myChangePokePos[6];
    char field_1C4;
    char field_1C5;
    char field_1C6;
    char field_1C7;
    char field_1C8;
    char field_1C9;
    char field_1CA;
    SWAN_ALIGNED(2)
    int field_1CC;
    int field_1D0;
    _BYTE gap1D4[20];
    __int16 field_1E8;
    __int16 field_1EA;
    int field_1EC;
    int field_1F0;
    _BYTE gap1F4[16];
    int field_204;
    _BYTE gap208[12];
    int field_214;
    _BYTE gap218[4];
    _WORD word21C;
    SWAN_ALIGNED(4)
    int dword220;
    u16 field_224[22];
    char field_250;
};

struct ServerCommandQueue
{
    u32 writePtr;
    u32 readPtr;
    u8 buffer[3000];
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

struct SWAN_ALIGNED(4) HandlerParam_StrParams
{
    u16 ID;
    int type;
    int args[8];
};

struct SWAN_ALIGNED(4) HandlerParam_Switch
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
    MoveTarget targetType;
    int flags;
};



struct ZoneData
{
    char MapType;
    u8 NPCInfoCacheIdx;
    u16 AreaID;
    u16 MatrixID;
    u16 ScriptsID;
    u16 LevelScriptsID;
    u16 TextsID;
    u16 BGMSpr;
    u16 BGMSum;
    u16 BGMAut;
    u16 BGMWin;
    u16 EncID;
    u16 EntitiesID;
    u16 ParentZoneID;
    u16 LocNameInfo;
    u16 EnvFlags;
    u16 Flags1BattleBGMapTransition;
    u16 MatrixCamBounds;
    u16 NameIcon;
    int FlyX;
    int FlyY;
    int FlyZ;
};

struct ZoneDataSystem
{
    int *ZoneDataArc;
    ZoneData CurrentZone;
    u16 CurrentZoneID;
    __int16 _padCurrentZoneID;
    void *FogIndex;
    void *StaticLights;
    u16 FogIndexSize;
    u8 StaticLightsSize;
    u8 FlashIndexSize;
    void *FlashIndex;
    u8 EnableVersionSpecificZone[3];
    u8 EnableVersionSpecificArea[3];
    u16 Padding;
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

struct SWAN_ALIGNED(4) HandlerParam_ConsumeItem
{
    HandlerParam_Header header;
    int fNoAction;
    HandlerParam_StrParams exStr;
};

struct SWAN_ALIGNED(4) HandlerParam_AddCondition
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

struct HandlerParam_CureCondition
{
    HandlerParam_Header header;
    MoveCondition sickCode;
    u8 pokeID[12];
    u8 poke_cnt;
    u8 fStdMsgDisable;
    HandlerParam_StrParams exStr;
};

struct SWAN_ALIGNED(8) TrainerAIEnv
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
    _DWORD aiFlagsFromTrainerData;
    char flags;
    char scriptID;
    char chosenMoveIndex;
    char chosenTarget;
    unsigned __int8 randPerMoveIndex[4];
    unsigned __int16 knownMoves[6][4];
    u8 knownAbilities[6];
    _BYTE gap82[18];
    unsigned __int8 attackerPos;
    unsigned __int8 defenderPos;
    _DWORD BattleStyle;
    _DWORD BattleType;
    __int16 HeapID;
    _DWORD ScriptsHandle;
    _DWORD ItemArcHandle;
    int scriptPtr;
    MainModule *mainModule;
    int* serverFlow;
    PokeCon *pokeCon;
    BattleMon *attacker;
    BattleMon *defender;
    int result;
    int field_C8;
    int seededRandom;
    _QWORD time;
};

struct SWAN_ALIGNED(4) HandlerParam_Damage
{
    HandlerParam_Header header;
    u16 damage;
    u8 pokeID;
    char flags;
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

struct SWAN_ALIGNED(4) m_record
{
    u32 Turn;
    __int16 MoveID;
    u8 PokeID;
    u8 fEffective;
};

struct MoveRecord
{
    u32 ptr;
    m_record record[120];
};

struct MoveStealParam
{
    char stealCount;
    char stealPokeID[6];
    char targetPos[6];
    char targetPokeID[6];
};
struct HitCheckParam
{
    char countMax;
    char count;
    char fCheckEveryTime;
    char fMultiHitMove;
    char fPutAnimCmd;
    char MultiHitEffectiveness;
};

struct ActionOrderWork
{
    int *BattleMon;
    int *Action;
    u32 field_8;
    char field_C;
    char fDone;
    char field_E;
    char field_F;
};
struct SWAN_ALIGNED(4) PokeSet
{
    BattleMon *battleMon[6];
    u16 damage[6];
    u16 substituteDamage[6];
    u8 damageType[6];
    u16 sortWork[6];
    u8 count;
    u8 countMax;
    u8 getIdx;
    u8 targetPosCount;
};

struct SWAN_PACKED SWAN_ALIGNED(1) calc_damage_record
{
    u8 unk0;
    u16 damage;
    u8 pokeID;
};
struct CalcDamageRecord
{
    char real_hit_count;
    char substitute_hit_count;
    char total_hit_count;
    calc_damage_record record[6];
};

struct PokeSetStackUnit
{
    PokeSet TargetOriginal;
    PokeSet Target;
    PokeSet Ally;
    PokeSet Enemy;
    PokeSet Damaged;
    PokeSet StealTarget;
    PokeSet psetTemp;
    u64 MoveAnimCtrl;
    MoveParam moveParam;
    MoveParam MoveParamOriginal;
    HitCheckParam hitCheck;
    MoveStealParam moveStealParam;
    MoveStealParam MagicCoatParam;
    CalcDamageRecord calcDamageAlly;
    CalcDamageRecord calcDamageEnemy;
    char defaultTargetPos;
    char field_28D;
    char field_28E;
    char field_28F;
};
struct PosPokeState
{
    u8 fEnable;
    u8 clientID;
    u8 existPokeID;
};
struct PosPoke
{
    PosPokeState state[6];
    u8 lastPos[24];
};

struct EffectivenessCounter
{
    u16 NoEffectHits;
    u16 SuperEffectiveHits;
    u16 NotVeryEffectiveHits;
    u16 OpponentNoEffectHits;
    u16 OpponentSuperEffectiveHits;
    u16 OpponentNotVeryEffectiveHits;
};

struct SWAN_ALIGNED(8) ServerFlow
{
    BtlServerWk *server;
    MainModule *mainModule;
    PokeCon *pokeCon;
    ServerCommandQueue *serverCommandQueue;
    int turnCount;
    int flowResult;
    int heapHandle;
    MoveRecord moveRecord;
    FaintRecord faintRecord;
    int **evolutionDataPtr;
    int *moveAnimContr;
    MoveStealParam *moveStealParam;
    MoveStealParam *magicCoatParam;
    HitCheckParam *hitCheckParam;
    EscapeInfo escapeInfo;
    int field_4C0;
    int field_4C4;
    int field_4C8;
    __int16 field_4CC;
    __int16 field_4CE;
    int field_4D0;
    u8 field_4D4[672];
    int SimulationCounter;
    int moveSerial;
    char cmdBuildStep;
    char field_77D;
    char TurnCheckSeq;
    char defaultTargetPos;
    __int16 heapID;
    char numActOrder;
    char numEndActOrder;
    _BYTE field_784;
    char revivedPokeCount;
    char field_786;
    char field_787;
    char field_788;
    char thruDeadMsgPokeID;
    char field_78A;
    char gap78B;
    char field_78C;
    char field_78D;
    char field_78E;
    char field_78F;
    char field_790;
    u8 revivePokeID[24];
    char pokeInFlag[24];
    char field_7C1[24];
    char switchCount[4];
    char field_7DD;
    char field_7DE;
    char field_7DF;
    ActionOrderWork actionOrderWork[6];
    ActionOrderWork TempActionOrderWork;
    PokeSet *setTargetOriginal;
    PokeSet *setTarget;
    PokeSet *setAlly;
    PokeSet *setEnemy;
    PokeSet *PokeSetDamaged;
    PokeSet *setStealTarget;
    PokeSet *PokeSetTemp;
    CalcDamageRecord *calcDamageAlly;
    CalcDamageRecord *calcDamageEnemy;
    PokeSetStackUnit pokesetUnit[7];
    int pokesetStackPtr;
    char field_1A68;
    _BYTE gap1A69[71];
    MoveParam *moveParam;
    MoveParam *moveParamOriginal;
    PosPoke posPoke;
    char field_1AE2;
    char field_1AE3;
    HandlerParam_StrParams StrParam;
    int *levelUpInfo;
    _BYTE gap1B10[68];
    int field_1B54;
    _BYTE gap1B58[316];
    char field_1C88;
    char field_1C89;
    char field_1C8A;
    char field_1C97;
    _BYTE gap1C98[224];
    int HEManager;
    _BYTE gap1D7C[8];
    char field_1D84;
    char field_1D85;
    char field_1D86;
    char field_1D87;
    char field_1D88;
    char field_1D89;
    char field_1D8A;
    _BYTE gap1D8B[481];
    char field_1F6C;
    _BYTE gap1F6D[11];
    __int16 PrevUsedMove;
    char field_1F7A;
    char field_1F7B;
    ActionIgnoreReason actionIgnoreReason;
    EffectivenessCounter effectivenessCounter;
    int dmgAffRec;
    _BYTE gap1F90[8];
    char field_1F98;
    _BYTE gap1F99[83];
    u8 field_1FEC[4];
    u8 TempWork;
    char field_1FF1;
    _BYTE gap1FF2[318];
    int field_2130;
    _BYTE gap2134[8];
    char field_213C;
    char field_213D;
    char field_213E;
    char field_213F;
};

struct HandlerParam_ActivateItem
{
    HandlerParam_Header header;
    u8 pokeID;
    u8 bAteKinomi;
    u16 itemID;
};

struct SWAN_ALIGNED(4) HandlerParam_RemoveSideEffect
{
    HandlerParam_Header header;
    u8 flags[3];
    u8 side;
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