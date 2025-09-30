#include "../swan-master/swantypes.h"
#include "../swan-master/system/game_data.h"


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

