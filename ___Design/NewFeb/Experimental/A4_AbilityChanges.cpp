

#include "settings.h"
#include "codeinjection_new.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define STAT_CHANGE_INTIMIDATE_FLAG 0x80000000
#define STAT_CHANGE_HOSTILE_FLAG 0x40000000
#define STAT_CHANGE_OPPORTUNIST_FLAG 0x20000000
#define STAT_CHANGE_PARTING_SHOT_FLAG 0x10000000

    // 0: not using override contact mechanics 
    // 1: using override contact mechanics 
    // 2: testing out the new static/flame body/poisontouch stuff
#define USING_ILLUSION false
#define TRYING_BATTLESCAN_EXPANSION false
#define USING_OVERRIDE_CONTACT false
#define CHANGING_DAMP false 
#define CHANGING_CONTACT_ABILITIES true 
#define CONSOLIDATING_ATES false 
// Uses esdb_newBattle.yml


#pragma region Notes
/* 
    
    
    ABILITY TABLE EDITS:    
        Somewhere in the code exists a table like the Move handle effect table. 
        We are going to edit this table to change the pointers for a bunch of abilities. 
        
        Luckily we don't need to carefully manage handlers too much. They're pretty plentiful. 

        [ ATE ABILITIES ]
            I mostly want to combine these to save space. 

            Refrigerate: 
                Double check that refrigerate doesn'tt work properly right now. If it does i'm even more confused .

                This is not currently assigned in the code 
                It's in theory attached to telepathy fsr. 
                Current Abil: 140 (8C in hex)
                Points To: EventAddTelepathy (89 1B 1C 02)
                Change to: EventAddStickyHold (39 11 1C 02) 
                
            Oblivious: 
                Abil No: 12 (0C in hex)
                Points To: EventAddOblivious (A5 EE 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)

            Super Luck: 
                Abil No: 105 (69 in hex)
                Points To: EventAddSuperLuck (55 F4 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)
            
            Magma Armor: 
                Abil No: 40 (28 in hex)
                Points To: EventAddMagmaArmor (21 ED 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)


        
        [ CLONE ABILITIES ]
            These abilities have the same effect as other abilities but a unique ABiL ID. 
            That's limited real estate so we should combine them. 

            Vital Spirit: 
                Abil No: 72 (48 in hex)
                Points To: EventAddInsomnia (E1 EC 1B 02)
                Change To: EventAddShieldDust (81 F2 1B 02)
                Name: Vital Spirit -> Resilient
            
            Illuminate
                Abil No. 35 (23 in hex)
                Points To: None 
                Change To: EventAddCompoundeyes (A5 E2 1B 02)
*/
/* 
    See if we can implement the following changes as hex edits to save space. 
    
        - Regenerator Nerf 
        - Stench Buff 
        - Dry Skin Nerf
        - Iron Fist Buff 
        - Weak Armor Buff 
*/
/* 
    ORPHANED ABILITY HANDLERS 

    Steadfast isn't being used 
    Defeatist isn't being used 
    Liquid Ooze isn't being used 
    Zen Mode isn't being used 
    Color Change isn't being used
    Ballistics isn't being used 
    Slow Start is barely being used 
    Natural Cure is barely being used 
    Shed Skin is barely being used 
    Overcoat is barely being used 

*/
#pragma endregion 


#pragma region definitions

extern "C" u8 SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u16 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)  return 1;
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

const u16 StrongJawMoves[12] = {
    MOVE044_BITE,
    MOVE158_HYPER_FANG,
    MOVE162_SUPER_FANG,
    MOVE170_SNAP_TRAP,
    MOVE265_PSYCHIC_FANGS,
    MOVE305_POISON_FANG,
    MOVE422_THUNDER_FANG,
    MOVE423_ICE_FANG,
    MOVE424_FIRE_FANG,
    MOVE242_CRUNCH,
    MOVE141_LEECH_LIFE,
    MOVE030_DEVOUR};

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

const u16 HyperCutterMoves[28] = {
    MOVE421_SHADOW_CLAW, MOVE533_SACRED_SWORD, MOVE534_RAZOR_SHELL, MOVE530_DUAL_CHOP, MOVE529_DRILL_RUN, MOVE554_SOLAR_BLADE,
    MOVE440_CROSS_POISON, MOVE427_PSYCHO_CUT, MOVE404_X_SCISSOR, MOVE400_NIGHT_SLASH, MOVE403_AIR_SLASH, MOVE384_PSYBLADE,
    MOVE348_LEAF_BLADE, MOVE337_DRAGON_CLAW, MOVE332_AERIAL_ACE, MOVE314_AIR_CUTTER, MOVE306_CRUSH_CLAW, MOVE232_METAL_CLAW,
    MOVE163_SLASH, MOVE154_FURY_SWIPES, MOVE065_DRILL_PECK, MOVE013_RAZOR_WINDS, MOVE210_FURY_CUTTER, MOVE015_CUT,
    MOVE075_RAZOR_LEAF, MOVE548_SECRET_SWORD, MOVE032_HORN_DRILL, MOVE064_AQUA_CUTTER};

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

const u16 nonStatusProtectMoves[4] = {
    MOVE376_SPIKY_SHIELD,
    MOVE462_SILK_TRAP,
    MOVE559_BANEFUL_BUNKER,
    MOVE262_OBSTRUCT};

#pragma endregion



extern "C" {
    #pragma region helpers

    int checkHigher(int a1, int a2)
    {
        if (a1 < a2)
        {
            return a2;
        }
        return a1;
    }

    typedef struct
    {
        BattleEventType triggerValue;
        ABILITY_HANDLER_FUNC function;
    } ABILITY_TRIGGERTABLE;

    bool checksIfWildBattle(ServerFlow *a1)
    {
        return a1->mainModule->btlSetup->btlType == 0;
    }

    bool checkIfConsumableItem(int a1)
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

    uint8_t getOverheatByte(BattleMon *a1)
    {
        return *((uint8_t *)a1 + 0xEA);
    }
    void setOverheatByte(BattleMon *a1, int a2)
    {
        *((uint8_t *)a1 + 0xEA) = a2;
    }
    uint8_t getOverheatLastTurnByte(BattleMon *a1)
    {
        return *((uint8_t *)a1 + 0xEB);
    }
    void setOverheatLastTurnByte(BattleMon *a1, int a2)
    {
        *((uint8_t *)a1 + 0xEB) = a2;
    }

    #pragma endregion

    #pragma region ExpandAbilities

    /* 
        Abilities we've overwritten 
            Damp 
            Limber
            Oblivious 
            Insomnia
            Color Change 
            Immunity
            Own Tempo
            Suction Cups 
            Illuminate 
            Magma Armor
            Water Veil
            Soundproof
            Pressure
            Early Bird (technically not really but still)
            Keen Eye 
            Cute Charm 
            Sticky Hold 
            Vital Spirit 
            Tangled Feet
            Steadfast
            Hydration
            Stall
            Leaf Guard 
            Klutz
            Super Luck
            Frisk
            Defeatist
            Telepathy
            Big Pecks
            Wonder Skin
            Zen Mode 

        Abilities we've renamed 
            White Smoke
            Analytic 
            Download
            Harvest
            Mummy
            Victory Star

        Abilities that currently aren't being used for Anything: 
            Liquid Ooze 
            Steadfast / Colossal 
            Wonder Guard (could theoretically use it on the AI at some point, but tbh i don't think it's a terribly interesting ability to play around)
        Abilities that are barely being used: 
            Slow Start 
            Wonder Guard 
            Minus (only exists as flavor to contrast Plus)
    */
    
    enum AbilID
    #ifdef __cplusplus
        : u32
    #endif
    {
        ABIL_NULL = 0x0,
        ABIL001_STENCH = 0x1,
        ABIL002_DRIZZLE = 0x2,
        ABIL003_SPEED_BOOST = 0x3,
        ABIL004_BATTLE_ARMOR = 0x4,
        ABIL005_STURDY = 0x5,
        ABIL006_BULLETPROOF = 0x6,         // ABIL006_DAMP 
        ABIL007_CORROSION = 0x7,           // ABIL007_LIMBER  
        ABIL008_SAND_VEIL = 0x8,    
        ABIL009_STATIC = 0x9,
        ABIL010_VOLT_ABSORB = 0xA,
        ABIL011_WATER_ABSORB = 0xB,
        ABIL012_GALVANIZE = 0xC,           // ABIL012_OBLIVIOUS
        ABIL013_CLOUD_NINE = 0xD,
        ABIL014_COMPOUNDEYES = 0xE,
        ABIL015_THUNDER_ARMOR = 0xF,       // ABIL015_INSOMNIA
        ABIL016_RKS_SYSTEM = 0x10,         // ABIL016_COLOR_CHANGE
        ABIL017_FLUFFY = 0x11,             // ABIL017_IMMUNITY
        ABIL018_FLASH_FIRE = 0x12,
        ABIL019_SHIELD_DUST = 0x13,
        ABIL020_QUICK_DRAW = 0x14,         // ABIL020_OWN_TEMPO
        ABIL021_WELL_BAKED_BODY = 0x15,    // ABIL021_SUCTION_CUPS
        ABIL022_INTIMIDATE = 0x16,
        ABIL023_SHADOW_TAG = 0x17,
        ABIL024_ROUGH_SKIN = 0x18,
        ABIL025_WONDER_GUARD = 0x19,
        ABIL026_LEVITATE = 0x1A,
        ABIL027_EFFECT_SPORE = 0x1B,
        ABIL028_SYNCHRONIZE = 0x1C,
        ABIL029_CLEAR_BODY = 0x1D,
        ABIL030_NATURAL_CURE = 0x1E,
        ABIL031_LIGHTNING_ROD = 0x1F,
        ABIL032_SERENE_GRACE = 0x20,
        ABIL033_SWIFT_SWIM = 0x21,
        ABIL034_CHLOROPHYLL = 0x22,
        ABIL035_KEEN_SENSES = 0x23,        // ABIL035_ILLUMINATE
        ABIL036_TRACE = 0x24,
        ABIL037_HUGE_POWER = 0x25,
        ABIL038_BERSERK = 0x26,            // ABIL038_POISON_POINT
        ABIL039_INNER_FOCUS = 0x27,
        ABIL040_PIXILATE = 0x28,           // ABIL040_MAGMA_ARMOR
        ABIL041_MERCILESS = 0x29,          // ABIL041_WATER_VEIL
        ABIL042_MAGNET_PULL = 0x2A,
        ABIL043_AMPLIFIER = 0x2B,          // ABIL043_SOUNDPROOF
        ABIL044_RAIN_DISH = 0x2C,          
        ABIL045_SAND_STREAM = 0x2D,
        ABIL046_NEUTRALIZING_GAS = 0x2E,   // ABIL046_PRESSURE
        ABIL047_THICK_FAT = 0x2F,
        ABIL048_REFRIGERATE = 0x30,        // ABIL048_EARLY_BIRD (not replaced in wakeup function)
        ABIL049_FLAME_BODY = 0x31,
        ABIL050_RUN_AWAY = 0x32,
        ABIL051_WIND_RIDER = 0x33,         // ABIL051_KEEN_EYE
        ABIL052_HYPER_CUTTER = 0x34,
        ABIL053_PICKUP = 0x35,
        ABIL054_TRUANT = 0x36,
        ABIL055_HUSTLE = 0x37,
        ABIL056_GOOEY = 0x38,              // ABIL056_CUTE_CHARM
        ABIL057_PLUS = 0x39,
        ABIL058_MINUS = 0x3A,
        ABIL059_FORECAST = 0x3B,
        ABIL060_AERILATE = 0x3C,           // ABIL060_STICKY_HOLD
        ABIL061_SHED_SKIN = 0x3D,
        ABIL062_GUTS = 0x3E,
        ABIL063_MARVEL_SCALE = 0x3F,
        ABIL064_LIQUID_OOZE = 0x40,
        ABIL065_OVERGROW = 0x41,
        ABIL066_BLAZE = 0x42,
        ABIL067_TORRENT = 0x43,
        ABIL068_SWARM = 0x44,
        ABIL069_ROCK_HEAD = 0x45,
        ABIL070_DROUGHT = 0x46,
        ABIL071_ARENA_TRAP = 0x47,
        ABIL072_RESILIENT = 0x48,          // ABIL072_VITAL_SPIRIT
        ABIL073_STRONG_BODY = 0x49,        // ABIL073_WHITE_SMOKE
        ABIL074_PURE_POWER = 0x4A,
        ABIL075_SHELL_ARMOR = 0x4B,
        ABIL076_AIR_LOCK = 0x4C,
        ABIL077_SLUSH_RUSH = 0x4D,         // ABIL077_TANGLED_FEET
        ABIL078_MOTOR_DRIVE = 0x4E,
        ABIL079_RIVALRY = 0x4F,
        ABIL080_COLOSSAL = 0x50,           // ABIL080_STEADFAST
        ABIL081_SNOW_CLOAK = 0x51,
        ABIL082_GLUTTONY = 0x52,
        ABIL083_ANGER_POINT = 0x53,
        ABIL084_UNBURDEN = 0x54,
        ABIL085_HEATPROOF = 0x55,
        ABIL086_SIMPLE = 0x56,
        ABIL087_DRY_SKIN = 0x57,
        ABIL088_EXPLOIT = 0x58,            // ABIL088_DOWNLOAD
        ABIL089_IRON_FIST = 0x59,
        ABIL090_POISON_HEAL = 0x5A,
        ABIL091_ADAPTABILITY = 0x5B,
        ABIL092_SKILL_LINK = 0x5C,
        ABIL093_STRONG_JAW = 0x5D,         // ABIL093_HYDRATION
        ABIL094_SOLAR_POWER = 0x5E,
        ABIL095_QUICK_FEET = 0x5F,
        ABIL096_NORMALIZE = 0x60,
        ABIL097_SNIPER = 0x61,
        ABIL098_MAGIC_GUARD = 0x62,
        ABIL099_NO_GUARD = 0x63,
        ABIL100_TOUGH_CLAWS = 0x64,        // ABIL100_STALL
        ABIL101_TECHNICIAN = 0x65,
        ABIL102_FUR_COAT = 0x66,           // ABIL102_LEAF_GUARD
        ABIL103_DISTRACTING = 0x67,        // ABIL103_KLUTZ
        ABIL104_MOLD_BREAKER = 0x68,
        ABIL105_MOISTURIZE = 0x69,         // ABIL105_SUPER_LUCK
        ABIL106_AFTERMATH = 0x6A,
        ABIL107_ANTICIPATION = 0x6B,
        ABIL108_FOREWARN = 0x6C,
        ABIL109_UNAWARE = 0x6D,
        ABIL110_TINTED_LENS = 0x6E,
        ABIL111_FILTER = 0x6F,
        ABIL112_SLOW_START = 0x70,
        ABIL113_SCRAPPY = 0x71,
        ABIL114_STORM_DRAIN = 0x72,
        ABIL115_ICE_BODY = 0x73,
        ABIL116_SOLID_ROCK = 0x74,
        ABIL117_SNOW_WARNING = 0x75,
        ABIL118_HONEY_GATHER = 0x76,
        ABIL119_STAKEOUT = 0x77,           // ABIL119_FRISK
        ABIL120_RECKLESS = 0x78,
        ABIL121_MULTITYPE = 0x79,
        ABIL122_FLOWER_GIFT = 0x7A,
        ABIL123_BAD_DREAMS = 0x7B,
        ABIL124_PICKPOCKET = 0x7C,
        ABIL125_SHEER_FORCE = 0x7D,
        ABIL126_CONTRARY = 0x7E,
        ABIL127_UNNERVE = 0x7F,
        ABIL128_DEFIANT = 0x80,
        ABIL129_MAJESTY = 0x81,            // ABIL129_DEFEATIST
        ABIL130_CURSED_BODY = 0x82,
        ABIL131_HEALER = 0x83,
        ABIL132_FRIEND_GUARD = 0x84,
        ABIL133_WEAK_ARMOR = 0x85,
        ABIL134_HEAVY_METAL = 0x86,
        ABIL135_LIGHT_METAL = 0x87,
        ABIL136_MULTISCALE = 0x88,
        ABIL137_TOXIC_BOOST = 0x89,
        ABIL138_FLARE_BOOST = 0x8A,
        ABIL139_GOURMAND = 0x8B,           // ABIL139_HARVEST
        ABIL140_ICE_SCALES = 0x8C,         // ABIL140_TELEPATHY
        ABIL141_MOODY = 0x8D,
        ABIL142_OVERCOAT = 0x8E,
        ABIL143_POISON_TOUCH = 0x8F,
        ABIL144_REGENERATOR = 0x90,
        ABIL145_SAVANT = 0x91,             // ABIL145_BIG_PECKS
        ABIL146_SAND_RUSH = 0x92,
        ABIL147_WONDER_SKIN = 0x93,        // Not overwritten, but it's handler is being used for Ice Scales now
        ABIL148_PATIENT = 0x94,            // ABIL148_ANALYTIC
        ABIL149_ILLUSION = 0x95,
        ABIL150_IMPOSTER = 0x96,
        ABIL151_INFILTRATOR = 0x97,
        ABIL152_CONTAGIOUS = 0x98,         // ABIL152_MUMMY
        ABIL153_MOXIE = 0x99,
        ABIL154_JUSTIFIED = 0x9A,
        ABIL155_RATTLED = 0x9B,
        ABIL156_MAGIC_BOUNCE = 0x9C,
        ABIL157_SAP_SIPPER = 0x9D,
        ABIL158_PRANKSTER = 0x9E,
        ABIL159_SAND_FORCE = 0x9F,
        ABIL160_IRON_BARBS = 0xA0,
        ABIL161_COLLECTIVE = 0xA1,         // ABIL161_ZEN_MODE
        ABIL162_ILLUMINATE = 0xA2,         // ABIL162_VICTORY_STAR
        ABIL163_TURBOBLAZE = 0xA3,
        ABIL164_TERAVOLT = 0xA4,

        #if ABILITY_EXPANSION 
        ABIL165_TERAVOLT = 0xA4,
        ABIL166_TERAVOLT = 0xA4,
        ABIL167_TERAVOLT = 0xA4,
        ABIL168_TERAVOLT = 0xA4,
        ABIL169_TERAVOLT = 0xA4,
        ABIL170_TERAVOLT = 0xA4,
        ABIL171_TERAVOLT = 0xA4,
        ABIL172_TERAVOLT = 0xA4,
        ABIL173_TERAVOLT = 0xA4,
        ABIL174_TERAVOLT = 0xA4,
        ABIL175_TERAVOLT = 0xA4,
        ABIL176_TERAVOLT = 0xA4,
        ABIL177_TERAVOLT = 0xA4,
        ABIL178_TERAVOLT = 0xA4,
        ABIL179_TERAVOLT = 0xA4,
        ABIL180_TERAVOLT = 0xA4,
        ABIL181_TERAVOLT = 0xA4,
        #endif
    };

    ABILITY_TRIGGERTABLE abilityEventAddTableExt[]{
    #if EXPAND_ABILITIES
        { ABIL_OBLIVIOUS, EventAddObliviousUpdated},
        { ABIL_OWN_TEMPO, EventAddOwnTempoUpdated},
        { ABIL_INNER_FOCUS, EventAddInnerFocusUpdated},
        { ABIL_SCRAPPY, EventAddScrappyUpdated},
        { ABIL_RATTLED, EventAddRattledUpdated},
    #endif
        { ABIL_AROMA_VEIL, EventAddAromaVeil, "Abilities/AromaVeil" },
        { ABIL_FLOWER_VEIL, EventAddFlowerVeil, "Abilities/FlowerVeil" },
        { ABIL_CHEEK_POUCH, EventAddCheekPouch, "Abilities/CheekPouch" },
        { ABIL_PROTEAN, EventAddProtean, "Abilities/Protean" },
        { ABIL_FUR_COAT, EventAddFurCoat, "Abilities/FurCoat" },
        { ABIL_MAGICIAN, EventAddMagician, "Abilities/Magician" },
        { ABIL_BULLETPROOF, EventAddBulletProof, "Abilities/BulletProof" },
        { ABIL_COMPETITIVE, EventAddCompetitive, "Abilities/Competitive" },
        { ABIL_STRONG_JAW, EventAddStrongJaw, "Abilities/StrongJaw" },
        { ABIL_REFRIGERATE, EventAddRefrigerate, "Abilities/Refrigerate" },
        { ABIL_SWEET_VEIL, EventAddSweetVeil, "Abilities/SweetVeil" },
        { ABIL_STANCE_CHANGE, EventAddStanceChange, "Abilities/StanceChange" },
        { ABIL_GALE_WINGS, EventAddGaleWings, "Abilities/GaleWings" },
        { ABIL_MEGA_LAUNCHER, EventAddMegaLauncher, "Abilities/MegaLauncher" },
        { ABIL_GRASS_PELT, EventAddGrassPelt, "Abilities/GrassPelt" },
        { ABIL_SYMBIOSIS, EventAddSymbiosis, "Abilities/Symbiosis" },
        { ABIL_TOUGH_CLAWS, EventAddToughClaws, "Abilities/ToughClaws" },
        { ABIL_PIXILATE, EventAddPixilate, "Abilities/Pixilate" },
        { ABIL_GOOEY, EventAddGooey, "Abilities/Gooey" },
        { ABIL_AERILATE , EventAddAerilate, "Abilities/Aerilate" },
        { ABIL_PARENTAL_BOND, EventAddParentalBond, "Abilities/ParentalBond" },
        { ABIL_DARK_AURA, EventAddDarkAura, "Abilities/DarkAura" },
        { ABIL_FAIRY_AURA, EventAddFairyAura, "Abilities/FairyAura" },
        { ABIL_AURA_BREAK, EventAddAuraBreak, "Abilities/AuraBreak" },
        { ABIL_PRIMORDIAL_SEA, EventAddPrimordialSea, "Abilities/PrimordialSea" },
        { ABIL_DESOLATE_LAND, EventAddDesolateLand, "Abilities/DesolateLand" },
        { ABIL_DELTA_STREAM, EventAddDeltaStream, "Abilities/DeltaStream" },
        { ABIL_STAMINA, EventAddStamina, "Abilities/Stamina" },
        { ABIL_WIMP_OUT, EventAddEmergencyExit, "Abilities/EmergencyExit" },
        { ABIL_EMERGENCY_EXIT, EventAddEmergencyExit, "Abilities/EmergencyExit" },
        { ABIL_WATER_COMPACTION, EventAddWaterCompaction, "Abilities/WaterCompaction" },
        { ABIL_MERCILESS, EventAddMerciless, "Abilities/Merciless" },
        { ABIL_SHIELDS_DOWN, EventAddShieldsDown, "Abilities/ShieldsDown" },
        { ABIL_STAKEOUT, EventAddStakeout, "Abilities/Stakeout" },
        { ABIL_WATER_BUBBLE, EventAddWaterBubble, "Abilities/BurnPrevention" },
        { ABIL_STEELWORKER, EventAddSteelworker, "Abilities/Steelworker" },
        { ABIL_BERSERK, EventAddBerserk, "Abilities/Berserk" },
        { ABIL_SLUSH_RUSH, EventAddSlushRush, "Abilities/SlushRush" },
        { ABIL_LIQUID_VOICE, EventAddLiquidVoice, "Abilities/LiquidVoice" },
        { ABIL_TRIAGE, EventAddTriage, "Abilities/Triage" },
        { ABIL_GALVANIZE, EventAddGalvanize, "Abilities/Galvanize" },
        { ABIL_SURGE_SURFER, EventAddSurgeSurfer, "Abilities/SurgeSurfer" },
        { ABIL_SCHOOLING, EventAddSchooling, "Abilities/Schooling" },
        { ABIL_DISGUISE, EventAddDisguise, "Abilities/Disguise" },
        { ABIL_BATTLE_BOND, EventAddBattleBond, "Abilities/BattleBond" },
        { ABIL_POWER_CONSTRUCT, EventAddPowerConstruct, "Abilities/PowerConstruct" },
        { ABIL_QUEENLY_MAGESTY, EventAddQueenlyMagesty, "Abilities/QueenlyMagesty" },
        { ABIL_INNARDS_OUT, EventAddInnardsOut, "Abilities/InnardsOut" },
        { ABIL_DANCER, EventAddDancer, "Abilities/Dancer" },
        { ABIL_BATTERY, EventAddBattery, "Abilities/Battery" },
        { ABIL_FLUFFY, EventAddFluffy, "Abilities/Fluffy" },
        { ABIL_DAZZLING, EventAddQueenlyMagesty, "Abilities/QueenlyMagesty" },
        { ABIL_SOUL_HEART, EventAddSoulHeart, "Abilities/SoulHeart" },
        { ABIL_TANGLING_HAIR, EventAddGooey, "Abilities/Gooey" },
        { ABIL_RECEIVER, EventAddReceiver, "Abilities/Receiver" },
        { ABIL_POWER_OF_ALCHEMY, EventAddReceiver, "Abilities/Receiver" },
        { ABIL_BEAST_BOOST, EventAddBeastBoost, "Abilities/BeastBoost" },
        { ABIL_ELECTRIC_SURGE, EventAddElectricSurge, "Abilities/ElectricSurge" },
        { ABIL_PSYCHIC_SURGE, EventAddPsychicSurge, "Abilities/PsychicSurge" },
        { ABIL_MISTY_SURGE, EventAddMistySurge, "Abilities/MistySurge" },
        { ABIL_GRASSY_SURGE, EventAddGrassySurge, "Abilities/GrassySurge" },
        { ABIL_FULL_METAL_BODY, EventAddClearBody, nullptr },
        { ABIL_SHADOW_SHIELD, EventAddMultiscale, nullptr },
        { ABIL_PRISM_ARMOR, EventAddPrismArmor, "Abilities/PrismArmor" },
        { ABIL_NEUROFORCE, EventAddNeuroforce, "Abilities/Neuroforce" },
        { ABIL_INTREPID_SWORD, EventAddIntrepidSword, "Abilities/IntrepidSword" },
        { ABIL_DAUNTLESS_SHIELD, EventAddDauntlessShield, "Abilities/DauntlessShield" },
        { ABIL_LIBERO, EventAddProtean, "Abilities/Protean" },
        { ABIL_BALL_FETCH, EventAddBallFetch, "Abilities/BallFetch" },
        { ABIL_COTTON_DOWN, EventAddCottonDown, "Abilities/CottonDown" },
        { ABIL_PROPELLER_TAIL, EventAddPropellerTail, "Abilities/PropellerTail" },
        { ABIL_MIRROR_ARMOR, EventAddMirrorArmor, "Abilities/MirrorArmor" },
        { ABIL_GULP_MISSILE, EventAddGulpMissile, "Abilities/GulpMissile" },
        { ABIL_STALWART, EventAddPropellerTail, "Abilities/PropellerTail" },
        { ABIL_STEAM_ENGINE, EventAddSteamEngine, "Abilities/SteamEngine" },
        { ABIL_PUNK_ROCK, EventAddPunkRock, "Abilities/PunkRock" },
        { ABIL_SAND_SPIT, EventAddSandSpit, "Abilities/SandSpit" },
        { ABIL_ICE_SCALES, EventAddIceScales, "Abilities/IceScales" },
        { ABIL_RIPEN, EventAddRipen, "Abilities/Ripen" },
        { ABIL_ICE_FACE, EventAddIceFace, "Abilities/IceFace" },
        { ABIL_POWER_SPOT, EventAddPowerSpot, "Abilities/PowerSpot" },
        { ABIL_MIMICRY, EventAddMimicry, "Abilities/Mimicry" },
        { ABIL_SCREEN_CLEANER, EventAddScreenCleaner, "Abilities/ScreenCleaner" },
        { ABIL_STEELY_SPIRIT, EventAddSteelySpirit, "Abilities/SteelySpirit" },
        { ABIL_PERISH_BODY, EventAddPerishBody, "Abilities/PerishBody" },
        { ABIL_WANDERING_SPIRIT, EventAddWanderingSpirit, "Abilities/WanderingSpirit" },
        { ABIL_GORILLA_TACTICS, EventAddGorillaTactics, "Abilities/GorillaTactics" },
        { ABIL_NEUTRALIZING_GAS, EventAddNeutralizingGas, "Abilities/NeutralizingGas" },
        { ABIL_PASTEL_VEIL, EventAddPastelVeil, "Abilities/PastelVeil" },
        { ABIL_HUNGER_SWITCH, EventAddHungerSwitch, "Abilities/HungerSwitch" },
        { ABIL_QUICK_DRAW, EventAddQuickDraw, "Abilities/QuickDraw" },
        { ABIL_UNSEEN_FIST, EventAddUnseenFist, "Abilities/UnseenFist" },
        { ABIL_CURIOUS_MEDICINE, EventAddCuriousMedicine, "Abilities/CuriousMedicine" },
        { ABIL_TRANSISTOR, EventAddTransistor, "Abilities/TypeBoost" },
        { ABIL_DRAGON_S_MAW, EventAddDragonsMaw, "Abilities/TypeBoost" },
        { ABIL_CHILLING_NEIGH, EventAddChillingNeigh, "Abilities/AsOne" },
        { ABIL_GRIM_NEIGH, EventAddGrimNeigh, "Abilities/AsOne" },
        { ABIL_AS_ONE_ICE, EventAddAsOne, "Abilities/AsOne" },
        { ABIL_AS_ONE_SHADOW, EventAddAsOne, "Abilities/AsOne" },
        { ABIL_LINGERING_AROMA, EventAddMummy, nullptr },
        { ABIL_SEED_SOWER, EventAddSeedSower, "Abilities/SeedSower" },
        { ABIL_THERMAL_EXCHANGE, EventAddThermalExchange, "Abilities/BurnPrevention" },
        { ABIL_ANGER_SHELL, EventAddAngerShell, "Abilities/AngerShell" },
        { ABIL_PURIFYING_SALT, EventAddPurifyingSalt, "Abilities/BurnPrevention" },
        { ABIL_WELL_BAKED_BODY, EventAddWellBakedBody, "Abilities/WellBakedBody" },
        { ABIL_WIND_RIDER, EventAddWindRider, "Abilities/WindBoosted" },
        { ABIL_GUARD_DOG, EventAddGuardDog, "Abilities/GuardDog" },
        { ABIL_ROCKY_PAYLOAD, EventAddRockyPayload, "Abilities/RockyPayload" },
        { ABIL_WIND_POWER, EventAddWindPower, "Abilities/WindBoosted" },
        { ABIL_ZERO_TO_HERO, EventAddZeroToHero, "Abilities/ZeroToHero" },
        { ABIL_COMMANDER, EventAddCommander, "Abilities/Commander" },
        { ABIL_ELECTROMORPHOSIS, EventAddElectromorphosis, "Abilities/WindBoosted" },
        { ABIL_PROTOSYNTHESIS, EventAddProtosynthesis, "Abilities/Paradox" },
        { ABIL_QUARK_DRIVE, EventAddQuarkDrive, "Abilities/Paradox" },
        { ABIL_GOOD_AS_GOLD, EventAddGoodAsGold, "Abilities/GoodAsGold" },
        { ABIL_VESSEL_OF_RUIN, EventAddVesselOfRuin, "Abilities/Ruin" },
        { ABIL_SWORD_OF_RUIN, EventAddSwordOfRuin, "Abilities/Ruin" },
        { ABIL_TABLETS_OF_RUIN, EventAddTabletsOfRuin, "Abilities/Ruin" },
        { ABIL_BEADS_OF_RUIN, EventAddBeadsOfRuin, "Abilities/Ruin" },
        { ABIL_ORICHALCUM_PULSE, EventAddOrichalcumPulse, "Abilities/OrichalcumPulse" },
        { ABIL_HADRON_ENGINE, EventAddHadronEngine, "Abilities/HadronEngine" },
        { ABIL_OPPORTUNIST , EventAddOpportunist, "Abilities/Opportunist" },
        { ABIL_CUD_CHEW, EventAddCudChew, "Abilities/CudChew" },
        { ABIL_SHARPNESS, EventAddSharpness, "Abilities/Sharpness" },
        { ABIL_SUPREME_OVERLORD, EventAddSupremeOverlord, "Abilities/SupremeOverlord" },
        { ABIL_COSTAR, EventAddCostar, "Abilities/Costar" },
        { ABIL_TOXIC_DEBRIS, EventAddToxicDebris, "Abilities/ToxicDebris" },
        { ABIL_ARMOR_TAIL, EventAddQueenlyMagesty, "Abilities/QueenlyMagesty" },
        { ABIL_EARTH_EATER, EventAddEarthEater, "Abilities/EarthEater" },
        { ABIL_MYCELIUM_MIGHT, EventAddMyceliumMight, "Abilities/MyceliumMight" },
        { ABIL_HOSPITALITY, EventAddHospitality, "Abilities/Hospitality" },
        { ABIL_MIND_S_EYE, EventAddMindsEye, "Abilities/MindsEye" },
        { ABIL_EMBODY_ASPECT_TEAL , EventAddEmbodyAspectTeal, "Abilities/EmbodyAspect" },
        { ABIL_EMBODY_ASPECT_HEARTHFLAME , EventAddEmbodyAspectHearthflame, "Abilities/EmbodyAspect" },
        { ABIL_EMBODY_ASPECT_WELLSPRING , EventAddEmbodyAspectWellspring, "Abilities/EmbodyAspect" },
        { ABIL_EMBODY_ASPECT_CORNERSTONE , EventAddEmbodyAspectCornerstorne, "Abilities/EmbodyAspect" },
        { ABIL_TOXIC_CHAIN, EventAddToxicChain, "Abilities/ToxicChain" },
        { ABIL_SUPERSWEET_SYRUP, EventAddSupersweetSyrup, "Abilities/SupersweetSyrup" },
        { ABIL_TERA_SHIFT, EventAddTeraShift, "Abilities/TeraShift" },
        { ABIL_TERA_SHELL, EventAddTeraShell, "Abilities/TeraShell" },
        { ABIL_TERAFORM_ZERO, EventAddTeraformZero, "Abilities/TeraformZero" },
        { ABIL_POISON_PUPPETEE, EventAddPoisonPuppeteer, "Abilities/PoisonPuppeteer" },
        { ABIL_PIERCING_DRILL, EventAddUnseenFist, "Abilities/UnseenFist" },
        { ABIL_DRAGONIZE, EventAddDragonize, "Abilities/Dragonize" },
        { ABIL_EELEVATE, EventAddEelevate, "Abilities/BeastBoost" },
        { ABIL_FIRE_MANE, EventAddFireMane, "Abilities/TypeBoost" },
        { ABIL_SPICY_SPRAY, EventAddSpicySpray, "Abilities/SpicySpray" },
    };
    
    extern "C" BattleEventItem * GetAbilityEvent(BattleMon * battleMon, AbilID ability, ABILITY_HANDLER_FUNC func) {
        u32 handlerAmount = 0;
        BattleEventHandlerTableEntry* battleHandlerItems = func(&handlerAmount);

        BattleEventPriority mainPrio = GetHandlerMainPriority(&handlerAmount);
        u32 subPrio = AbilityEvent_GetSubPriority(battleMon);
        u32 pokemonSlot = BattleMon_GetID(battleMon);
        return BattleEvent_AddItem(EVENTITEM_ABILITY, ability, mainPrio, subPrio, pokemonSlot, battleHandlerItems, handlerAmount);
    }

    extern "C" BattleEventItem* THUMB_BRANCH_AbilityEvent_AddItem(BattleMon* battleMon) {
        AbilID ability = BattleMon_GetValue(battleMon, VALUE_ABILITY);

        // Check for new or overriden abilities
        for (u32 abilityEvent = 0; abilityEvent < ARRAY_COUNT(abilityEventAddTableExt); ++abilityEvent) {
            
            AbilityEventAddTableExt* abilityAddEvent = &abilityEventAddTableExt[abilityEvent];
            if (ability == abilityAddEvent->ability) {
                return GetAbilityEvent(battleMon, ability, abilityAddEvent->func);
            }
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

    #pragma endregion

}