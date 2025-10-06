#include "swantypes.h"
#include "kPrint.h"

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long
extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// uses ESDB_For_LegendaryPokemon3.yml

#pragma region Definitions
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

unsigned short int &LOWORD(unsigned int &x)
{
    return *(reinterpret_cast<unsigned short int *>(&x) + 0);
}


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


extern "C"
{

    struct SWAN_ALIGNED(4) m_record
    {
        u32 Turn;
        __int16 MoveID;
        u8 PokeID;
        u8 fEffective;
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

    const u32 teraItems[17] = {
        215, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313
    };

    struct MoveRecord
    {
        u32 ptr;
        m_record record[120];
    };

    struct FaintRecordUnit
    {
        u8 count;
        u8 fExpChecked[24];
        u8 faintedMonIDs[24];
    };

    struct FaintRecord
    {
        FaintRecordUnit turnRecord[4];
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

    enum MoveID
    {
        MOVE_NULL = 0x0,
        MOVE001_CONCUSS = 0x1,
        MOVE002_KARATE_CHOP = 0x2,
        MOVE003_DOUBLE_SLAP = 0x3,
        MOVE004_COMET_PUNCH = 0x4,
        MOVE005_MEGA_PUNCH = 0x5,
        MOVE006_PAY_DAY = 0x6,
        MOVE007_FIRE_PUNCH = 0x7,
        MOVE008_ICE_PUNCH = 0x8,
        MOVE009_THUNDER_PUNCH = 0x9,
        MOVE010_SCRATCH = 0xA,
        MOVE011_DUAL_WINGBEAT = 0xB,
        MOVE012_GUILLOTINE = 0xC,
        MOVE013_RAZOR_WINDS = 0xD,
        MOVE014_SWORDS_DANCE = 0xE,
        MOVE015_CUT = 0xF,
        MOVE016_GUST = 0x10,
        MOVE017_WING_ATTACK = 0x11,
        MOVE018_WHIRLWIND = 0x12,
        MOVE019_FLY = 0x13,
        MOVE020_BIND = 0x14,
        MOVE021_BRUTAL_SWING = 0x15,
        MOVE022_VINE_WHIPS = 0x16,
        MOVE023_STOMP = 0x17,
        MOVE024_DOUBLE_KICK = 0x18,
        MOVE025_HIGH_HORSEPOWER = 0x19,
        MOVE026_JUMP_KICK = 0x1A,
        MOVE027_HEADLONG_RUSH = 0x1B,
        MOVE028_SAND_ATTACK = 0x1C,
        MOVE029_HEADBUTT = 0x1D,
        MOVE030_HORN_ATTACK = 0x1E,
        MOVE031_FIRE_LASH = 0x1F,
        MOVE032_HORN_DRILL = 0x20,
        MOVE033_TACKLE = 0x21,
        MOVE034_BODY_SLAM = 0x22,
        MOVE035_WRAP = 0x23,
        MOVE036_TAKE_DOWN = 0x24,
        MOVE037_THRASH = 0x25,
        MOVE038_DOUBLE_EDGE = 0x26,
        MOVE039_TAIL_WHIP = 0x27,
        MOVE040_POISON_STING = 0x28,
        MOVE041_TWINEEDLE = 0x29,
        MOVE042_PIN_MISSILE = 0x2A,
        MOVE043_LEER = 0x2B,
        MOVE044_BITE = 0x2C,
        MOVE045_GROWL = 0x2D,
        MOVE046_ROAR = 0x2E,
        MOVE047_SING = 0x2F,
        MOVE048_SUPERSONIC = 0x30,
        MOVE049_SCORCHING_SWARM = 0x31,
        MOVE050_DISABLE = 0x32,
        MOVE051_PARABOLIC_ZAP = 0x33,
        MOVE052_EMBER = 0x34,
        MOVE053_FLAMETHROWER = 0x35,
        MOVE054_MIST = 0x36,
        MOVE055_WATER_GUN = 0x37,
        MOVE056_HYDRO_PUMP = 0x38,
        MOVE057_SURF = 0x39,
        MOVE058_ICE_BEAM = 0x3A,
        MOVE059_BLIZZARD = 0x3B,
        MOVE060_PSYBEAM = 0x3C,
        MOVE061_BUBBLE_BEAM = 0x3D,
        MOVE062_AURORA_BEAM = 0x3E,
        MOVE063_HYPER_BEAM = 0x3F,
        MOVE064_PECK = 0x40,
        MOVE065_DRILL_PECK = 0x41,
        MOVE066_SUBMISSION = 0x42,
        MOVE067_LOW_KICK = 0x43,
        MOVE068_COUNTER = 0x44,
        MOVE069_SEISMIC_TOSS = 0x45,
        MOVE070_STRENGTH = 0x46,
        MOVE071_ABSORB = 0x47,
        MOVE072_MEGA_DRAIN = 0x48,
        MOVE073_LEECH_SEED = 0x49,
        MOVE074_GROWTH = 0x4A,
        MOVE075_RAZOR_LEAF = 0x4B,
        MOVE076_SOLAR_BEAM = 0x4C,
        MOVE077_POISON_POWDER = 0x4D,
        MOVE078_STUN_SPORE = 0x4E,
        MOVE079_SLEEP_POWDER = 0x4F,
        MOVE080_PETAL_DANCE = 0x50,
        MOVE081_STRING_SHOT = 0x51,
        MOVE082_DRAGON_RAGE = 0x52,
        MOVE083_FIRE_SPIN = 0x53,
        MOVE084_THUNDER_SHOCK = 0x54,
        MOVE085_THUNDERBOLT = 0x55,
        MOVE086_THUNDER_WAVE = 0x56,
        MOVE087_THUNDER = 0x57,
        MOVE088_ROCK_THROW = 0x58,
        MOVE089_EARTHQUAKE = 0x59,
        MOVE090_FISSURE = 0x5A,
        MOVE091_DIG = 0x5B,
        MOVE092_TOXIC = 0x5C,
        MOVE093_CONFUSION = 0x5D,
        MOVE094_PSYCHIC = 0x5E,
        MOVE095_HYPNOSIS = 0x5F,
        MOVE096_MEDITATE = 0x60,
        MOVE097_AGILITY = 0x61,
        MOVE098_QUICK_ATTACK = 0x62,
        MOVE099_RAGE = 0x63,
        MOVE100_TELEPORT = 0x64,
        MOVE101_NIGHT_SHADE = 0x65,
        MOVE102_PSYCHIC_NOISE = 0x66,
        MOVE103_SCREECH = 0x67,
        MOVE104_DOUBLE_TEAM = 0x68,
        MOVE105_RECOVER = 0x69,
        MOVE106_HARDEN = 0x6A,
        MOVE107_MINIMIZE = 0x6B,
        MOVE108_SMOKESCREEN = 0x6C,
        MOVE109_CONFUSE_RAY = 0x6D,
        MOVE110_BREAKING_SWIPE = 0x6E,
        MOVE111_DEFENSE_CURL = 0x6F,
        MOVE112_BARRIER = 0x70,
        MOVE113_LIGHT_SCREEN = 0x71,
        MOVE114_HAZE = 0x72,
        MOVE115_REFLECT = 0x73,
        MOVE116_FOCUS_ENERGY = 0x74,
        MOVE117_HIDDEN_FORCE = 0x75,
        MOVE118_METRONOME = 0x76,
        MOVE119_MIRROR_MOVE = 0x77,
        MOVE120_SELF_DESTRUCT = 0x78,
        MOVE121_EGG_BOMB = 0x79,
        MOVE122_LICK = 0x7A,
        MOVE123_SMOG = 0x7B,
        MOVE124_SLUDGE = 0x7C,
        MOVE125_BONE_CLUB = 0x7D,
        MOVE126_FIRE_BLAST = 0x7E,
        MOVE127_WATERFALL = 0x7F,
        MOVE128_CLAMP = 0x80,
        MOVE129_SWIFT = 0x81,
        MOVE130_SKULL_BASH = 0x82,
        MOVE131_SPIKE_CANNON = 0x83,
        MOVE132_INFESTATION = 0x84,
        MOVE133_AMNESIA = 0x85,
        MOVE134_LUNGE = 0x86,
        MOVE135_SOFT_BOILED = 0x87,
        MOVE136_HIGH_JUMP_KICK = 0x88,
        MOVE137_GLARE = 0x89,
        MOVE138_DREAM_EATER = 0x8A,
        MOVE139_POISON_GAS = 0x8B,
        MOVE140_BARRAGE = 0x8C,
        MOVE141_LEECH_LIFE = 0x8D,
        MOVE142_LOVELY_KISS = 0x8E,
        MOVE143_SKY_ATTACK = 0x8F,
        MOVE144_PHANTOM_STRIKE = 0x90,
        MOVE145_CHILLING_WATER = 0x91,
        MOVE146_DIZZY_PUNCH = 0x92,
        MOVE147_SPORE = 0x93,
        MOVE148_SPARKLE = 0x94,
        MOVE149_PSYWAVE = 0x95,
        MOVE150_PLAY_ROUGH = 0x96,
        MOVE151_ACID_ARMOR = 0x97,
        MOVE152_CRABHAMMER = 0x98,
        MOVE153_EXPLOSION = 0x99,
        MOVE154_FURY_SWIPES = 0x9A,
        MOVE155_BONEMERANG = 0x9B,
        MOVE156_REST = 0x9C,
        MOVE157_ROCK_SLIDE = 0x9D,
        MOVE158_HYPER_FANG = 0x9E,
        MOVE159_NUZZLE = 0x9F,
        MOVE160_FLIP_TURN = 0xA0,
        MOVE161_TRI_ATTACK = 0xA1,
        MOVE162_SUPER_FANG = 0xA2,
        MOVE163_SLASH = 0xA3,
        MOVE164_SUBSTITUTE = 0xA4,
        MOVE165_STRUGGLE = 0xA5,
        MOVE166_SKETCH = 0xA6,
        MOVE167_TRIPLE_KICK = 0xA7,
        MOVE168_THIEF = 0xA8,
        MOVE169_INFERNAL_PARADE = 0xA9,
        MOVE170_SNAP_TRAP = 0xAA,
        MOVE171_NIGHTMARE = 0xAB,
        MOVE172_FLAME_WHEEL = 0xAC,
        MOVE173_SNORE = 0xAD,
        MOVE174_CURSE = 0xAE,
        MOVE175_FLAIL = 0xAF,
        MOVE176_SPIN_OUT = 0xB0,
        MOVE177_AEROBLAST = 0xB1,
        MOVE178_COTTON_SPORE = 0xB2,
        MOVE179_REVERSAL = 0xB3,
        MOVE180_DIAMOND_STORM = 0xB4,
        MOVE181_POWDER_SNOW = 0xB5,
        MOVE182_PROTECT = 0xB6,
        MOVE183_MACH_PUNCH = 0xB7,
        MOVE184_SCARY_FACE = 0xB8,
        MOVE185_FEINT_ATTACK = 0xB9,
        MOVE186_DRAINING_KISS = 0xBA,
        MOVE187_BELLY_DRUM = 0xBB,
        MOVE188_SLUDGE_BOMB = 0xBC,
        MOVE189_MUD_SLAP = 0xBD,
        MOVE190_OCTAZOOKA = 0xBE,
        MOVE191_SPIKES = 0xBF,
        MOVE192_ZAP_CANNON = 0xC0,
        MOVE193_ELECTRO_SHOT = 0xC1,
        MOVE194_DESTINY_BOND = 0xC2,
        MOVE195_PERISH_SONG = 0xC3,
        MOVE196_ICY_WIND = 0xC4,
        MOVE197_DETECT = 0xC5,
        MOVE198_BONE_RUSH = 0xC6,
        MOVE199_PARTING_SHOT = 0xC7,
        MOVE200_OUTRAGE = 0xC8,
        MOVE201_SANDSTORM = 0xC9,
        MOVE202_GIGA_DRAIN = 0xCA,
        MOVE203_ENDURE = 0xCB,
        MOVE204_CHARM = 0xCC,
        MOVE205_ACCELROCK = 0xCD,
        MOVE206_BODY_PRESS = 0xCE,
        MOVE207_SWAGGER = 0xCF,
        MOVE208_MILK_DRINK = 0xD0,
        MOVE209_SPARK = 0xD1,
        MOVE210_FURY_CUTTER = 0xD2,
        MOVE211_STEEL_WING = 0xD3,
        MOVE212_MEAN_LOOK = 0xD4,
        MOVE213_ATTRACT = 0xD5,
        MOVE214_SLEEP_TALK = 0xD6,
        MOVE215_HEAL_BELL = 0xD7,
        MOVE216_RETURN = 0xD8,
        MOVE217_PRESENT = 0xD9,
        MOVE218_TEMPER_FLARE = 0xDA,
        MOVE219_SAFEGUARD = 0xDB,
        MOVE220_SEETHING_COLD = 0xDC,
        MOVE221_MYSTICAL_FIRE = 0xDD,
        MOVE222_STICKY_WEB = 0xDE,
        MOVE223_DYNAMIC_PUNCH = 0xDF,
        MOVE224_MEGAHORN = 0xE0,
        MOVE225_DRAGON_BREATH = 0xE1,
        MOVE226_BATON_PASS = 0xE2,
        MOVE227_ENCORE = 0xE3,
        MOVE228_PURSUIT = 0xE4,
        MOVE229_RAPID_SPIN = 0xE5,
        MOVE230_SWEET_SCENT = 0xE6,
        MOVE231_IRON_TAIL = 0xE7,
        MOVE232_METAL_CLAW = 0xE8,
        MOVE233_VITAL_THROW = 0xE9,
        MOVE234_MORNING_SUN = 0xEA,
        MOVE235_SYNTHESIS = 0xEB,
        MOVE236_MOONLIGHT = 0xEC,
        MOVE237_HIDDEN_POWER = 0xED,
        MOVE238_CROSS_CHOP = 0xEE,
        MOVE239_TWISTER = 0xEF,
        MOVE240_RAIN_DANCE = 0xF0,
        MOVE241_SUNNY_DAY = 0xF1,
        MOVE242_CRUNCH = 0xF2,
        MOVE243_MIRROR_COAT = 0xF3,
        MOVE244_BITTER_MALICE = 0xF4,
        MOVE245_EXTREME_SPEED = 0xF5,
        MOVE246_ANCIENT_POWER = 0xF6,
        MOVE247_SHADOW_BALL = 0xF7,
        MOVE248_FUTURE_SIGHT = 0xF8,
        MOVE249_ROCK_SMASH = 0xF9,
        MOVE250_WHIRLPOOL = 0xFA,
        MOVE251_BEAT_UP = 0xFB,
        MOVE252_FAKE_OUT = 0xFC,
        MOVE253_UPROAR = 0xFD,
        MOVE254_STOCKPILE = 0xFE,
        MOVE255_SPIT_UP = 0xFF,
        MOVE256_SWALLOW = 0x100,
        MOVE257_HEAT_WAVE = 0x101,
        MOVE258_HAIL = 0x102,
        MOVE259_TORMENT = 0x103,
        MOVE260_FLATTER = 0x104,
        MOVE261_WILL_O_WISP = 0x105,
        MOVE262_OBSTRUCT = 0x106,
        MOVE263_FACADE = 0x107,
        MOVE264_FOCUS_PUNCH = 0x108,
        MOVE265_PSYCHIC_FANGS = 0x109,
        MOVE266_FOLLOW_ME = 0x10A,
        MOVE267_NATURE_POWER = 0x10B,
        MOVE268_CHARGE = 0x10C,
        MOVE269_TAUNT = 0x10D,
        MOVE270_HELPING_HAND = 0x10E,
        MOVE271_WEATHER_CRASH = 0x10F,
        MOVE272_BARB_BARRAGE = 0x110,
        MOVE273_WISH = 0x111,
        MOVE274_ASSIST = 0x112,
        MOVE275_INGRAIN = 0x113,
        MOVE276_SUPERPOWER = 0x114,
        MOVE277_MAGIC_COAT = 0x115,
        MOVE278_RECYCLE = 0x116,
        MOVE279_REVENGE = 0x117,
        MOVE280_BRICK_BREAK = 0x118,
        MOVE281_YAWN = 0x119,
        MOVE282_KNOCK_OFF = 0x11A,
        MOVE283_ENDEAVOR = 0x11B,
        MOVE284_ERUPTION = 0x11C,
        MOVE285_SKILL_SWAP = 0x11D,
        MOVE286_IMPRISON = 0x11E,
        MOVE287_REFRESH = 0x11F,
        MOVE288_GRUDGE = 0x120,
        MOVE289_VICTORY_DANCE = 0x121,
        MOVE290_SECRET_POWER = 0x122,
        MOVE291_DIVE = 0x123,
        MOVE292_ARM_THRUST = 0x124,
        MOVE293_TROP_KICK = 0x125,
        MOVE294_TAIL_GLOW = 0x126,
        MOVE295_DAZZLING_GLEAM = 0x127,
        MOVE296_MOONBLAST = 0x128,
        MOVE297_FEATHER_DANCE = 0x129,
        MOVE298_TEETER_DANCE = 0x12A,
        MOVE299_BLAZE_KICK = 0x12B,
        MOVE300_ESPER_WING = 0x12C,
        MOVE301_BOOMBURST = 0x12D,
        MOVE302_NEEDLE_ARM = 0x12E,
        MOVE303_SLACK_OFF = 0x12F,
        MOVE304_HYPER_VOICE = 0x130,
        MOVE305_POISON_FANG = 0x131,
        MOVE306_CRUSH_CLAW = 0x132,
        MOVE307_BLAST_BURN = 0x133,
        MOVE308_HYDRO_CANNON = 0x134,
        MOVE309_METEOR_MASH = 0x135,
        MOVE310_ASTONISH = 0x136,
        MOVE311_WEATHER_BALL = 0x137,
        MOVE312_AROMATHERAPY = 0x138,
        MOVE313_FAKE_TEARS = 0x139,
        MOVE314_AIR_CUTTER = 0x13A,
        MOVE315_OVERHEAT = 0x13B,
        MOVE316_EERIE_IMPULSE = 0x13C,
        MOVE317_ROCK_TOMB = 0x13D,
        MOVE318_SILVER_WIND = 0x13E,
        MOVE319_METAL_SOUND = 0x13F,
        MOVE320_GRASS_WHISTLE = 0x140,
        MOVE321_TICKLE = 0x141,
        MOVE322_COSMIC_POWER = 0x142,
        MOVE323_WATER_SPOUT = 0x143,
        MOVE324_SIGNAL_BEAM = 0x144,
        MOVE325_SHADOW_PUNCH = 0x145,
        MOVE326_EXTRASENSORY = 0x146,
        MOVE327_SKY_UPPERCUT = 0x147,
        MOVE328_SAND_TOMB = 0x148,
        MOVE329_SHEER_COLD = 0x149,
        MOVE330_MUDDY_WATER = 0x14A,
        MOVE331_BULLET_SEED = 0x14B,
        MOVE332_AERIAL_ACE = 0x14C,
        MOVE333_ICICLE_SPEAR = 0x14D,
        MOVE334_IRON_DEFENSE = 0x14E,
        MOVE335_BLOCK = 0x14F,
        MOVE336_HOWL = 0x150,
        MOVE337_DRAGON_CLAW = 0x151,
        MOVE338_FRENZY_PLANT = 0x152,
        MOVE339_BULK_UP = 0x153,
        MOVE340_BOUNCE = 0x154,
        MOVE341_MUD_SHOT = 0x155,
        MOVE342_POISON_TAIL = 0x156,
        MOVE343_COVET = 0x157,
        MOVE344_VOLT_TACKLE = 0x158,
        MOVE345_MAGICAL_LEAF = 0x159,
        MOVE346_WICKED_BLOW = 0x15A,
        MOVE347_CALM_MIND = 0x15B,
        MOVE348_LEAF_BLADE = 0x15C,
        MOVE349_DRAGON_DANCE = 0x15D,
        MOVE350_ROCK_BLAST = 0x15E,
        MOVE351_SHOCK_WAVE = 0x15F,
        MOVE352_WATER_PULSE = 0x160,
        MOVE353_DOOM_DESIRE = 0x161,
        MOVE354_PSYCHO_BOOST = 0x162,
        MOVE355_ROOST = 0x163,
        MOVE356_GRAVITY = 0x164,
        MOVE357_FREEZE_DRY = 0x165,
        MOVE358_WAKE_UP_SLAP = 0x166,
        MOVE359_HAMMER_ARM = 0x167,
        MOVE360_GYRO_BALL = 0x168,
        MOVE361_HEALING_WISH = 0x169,
        MOVE362_BRINE = 0x16A,
        MOVE363_NATURAL_GIFT = 0x16B,
        MOVE364_CONFIDE = 0x16C,
        MOVE365_PLUCK = 0x16D,
        MOVE366_TAILWIND = 0x16E,
        MOVE367_ACUPRESSURE = 0x16F,
        MOVE368_METAL_BURST = 0x170,
        MOVE369_U_TURN = 0x171,
        MOVE370_CLOSE_COMBAT = 0x172,
        MOVE371_PAYBACK = 0x173,
        MOVE372_ASSURANCE = 0x174,
        MOVE373_1ST_IMPRESSION = 0x175,
        MOVE374_FLING = 0x176,
        MOVE375_PSYCHO_SHIFT = 0x177,
        MOVE376_SPIKY_SHIELD = 0x178,
        MOVE377_ALLURING_VOICE = 0x179,
        MOVE378_SCALE_SHOT = 0x17A,
        MOVE379_PETAL_BLIZZARD = 0x17B,
        MOVE380_GASTRO_ACID = 0x17C,
        MOVE381_LUCKY_CHANT = 0x17D,
        MOVE382_ME_FIRST = 0x17E,
        MOVE383_COPYCAT = 0x17F,
        MOVE384_PSYBLADE = 0x180,
        MOVE385_CLANGING_SCALES = 0x181,
        MOVE386_WAVE_CRASH = 0x182,
        MOVE387_LAST_RESORT = 0x183,
        MOVE388_WORRY_SEED = 0x184,
        MOVE389_SUCKER_PUNCH = 0x185,
        MOVE390_TOXIC_SPIKES = 0x186,
        MOVE391_HEART_SWAP = 0x187,
        MOVE392_AQUA_RING = 0x188,
        MOVE393_MAGNET_RISE = 0x189,
        MOVE394_FLARE_BLITZ = 0x18A,
        MOVE395_FORCE_PALM = 0x18B,
        MOVE396_AURA_SPHERE = 0x18C,
        MOVE397_ROCK_POLISH = 0x18D,
        MOVE398_POISON_JAB = 0x18E,
        MOVE399_DARK_PULSE = 0x18F,
        MOVE400_NIGHT_SLASH = 0x190,
        MOVE401_AQUA_TAIL = 0x191,
        MOVE402_SEED_BOMB = 0x192,
        MOVE403_AIR_SLASH = 0x193,
        MOVE404_X_SCISSOR = 0x194,
        MOVE405_BUG_BUZZ = 0x195,
        MOVE406_DRAGON_PULSE = 0x196,
        MOVE407_DRAGON_RUSH = 0x197,
        MOVE408_POWER_GEM = 0x198,
        MOVE409_DRAIN_PUNCH = 0x199,
        MOVE410_VACUUM_WAVE = 0x19A,
        MOVE411_FOCUS_BLAST = 0x19B,
        MOVE412_ENERGY_BALL = 0x19C,
        MOVE413_BRAVE_BIRD = 0x19D,
        MOVE414_EARTH_POWER = 0x19E,
        MOVE415_SWITCHEROO = 0x19F,
        MOVE416_GIGA_IMPACT = 0x1A0,
        MOVE417_NASTY_PLOT = 0x1A1,
        MOVE418_BULLET_PUNCH = 0x1A2,
        MOVE419_AVALANCHE = 0x1A3,
        MOVE420_ICE_SHARD = 0x1A4,
        MOVE421_SHADOW_CLAW = 0x1A5,
        MOVE422_THUNDER_FANG = 0x1A6,
        MOVE423_ICE_FANG = 0x1A7,
        MOVE424_FIRE_FANG = 0x1A8,
        MOVE425_SHADOW_SNEAK = 0x1A9,
        MOVE426_MUD_BOMB = 0x1AA,
        MOVE427_PSYCHO_CUT = 0x1AB,
        MOVE428_ZEN_HEADBUTT = 0x1AC,
        MOVE429_MIRROR_SHOT = 0x1AD,
        MOVE430_FLASH_CANNON = 0x1AE,
        MOVE431_ROCK_CLIMB = 0x1AF,
        MOVE432_DEFOG = 0x1B0,
        MOVE433_TRICK_ROOM = 0x1B1,
        MOVE434_DRACO_METEOR = 0x1B2,
        MOVE435_DISCHARGE = 0x1B3,
        MOVE436_LAVA_PLUME = 0x1B4,
        MOVE437_LEAF_STORM = 0x1B5,
        MOVE438_POWER_WHIP = 0x1B6,
        MOVE439_ROCK_WRECKER = 0x1B7,
        MOVE440_CROSS_POISON = 0x1B8,
        MOVE441_GUNK_SHOT = 0x1B9,
        MOVE442_IRON_HEAD = 0x1BA,
        MOVE443_MAGNET_BOMB = 0x1BB,
        MOVE444_STONE_EDGE = 0x1BC,
        MOVE445_CAPTIVATE = 0x1BD,
        MOVE446_STEALTH_ROCK = 0x1BE,
        MOVE447_GRASS_KNOT = 0x1BF,
        MOVE448_CHATTER = 0x1C0,
        MOVE449_SPIRIT_BREAK = 0x1C1,
        MOVE450_BUG_BITE = 0x1C2,
        MOVE451_CHARGE_BEAM = 0x1C3,
        MOVE452_WOOD_HAMMER = 0x1C4,
        MOVE453_AQUA_JET = 0x1C5,
        MOVE454_ATTACK_ORDER = 0x1C6,
        MOVE455_DEFEND_ORDER = 0x1C7,
        MOVE456_HEAL_ORDER = 0x1C8,
        MOVE457_HEAD_SMASH = 0x1C9,
        MOVE458_DOUBLE_HIT = 0x1CA,
        MOVE459_STARBURST = 0x1CB,
        MOVE460_STEEL_BEAM = 0x1CC,
        MOVE461_POLLEN_PUFF = 0x1CD,
        MOVE462_SILK_TRAP = 0x1CE,
        MOVE463_MAGMA_STORM = 0x1CF,
        MOVE464_DARK_VOID = 0x1D0,
        MOVE465_SEED_FLARE = 0x1D1,
        MOVE466_OMINOUS_WIND = 0x1D2,
        MOVE467_SHADOW_FORCE = 0x1D3,
        MOVE468_HONE_CLAWS = 0x1D4,
        MOVE469_WIDE_GUARD = 0x1D5,
        MOVE470_TRIPLE_AXEL = 0x1D6,
        MOVE471_TRIPLE_DIVE = 0x1D7,
        MOVE472_LIQUIDATION = 0x1D8,
        MOVE473_PSYSHOCK = 0x1D9,
        MOVE474_VENOSHOCK = 0x1DA,
        MOVE475_AUTOTOMIZE = 0x1DB,
        MOVE476_RAGE_POWDER = 0x1DC,
        MOVE477_TELEKINESIS = 0x1DD,
        MOVE478_POWER_TRIP = 0x1DE,
        MOVE479_SMACK_DOWN = 0x1DF,
        MOVE480_STORM_THROW = 0x1E0,
        MOVE481_FLAME_BURST = 0x1E1,
        MOVE482_SLUDGE_WAVE = 0x1E2,
        MOVE483_QUIVER_DANCE = 0x1E3,
        MOVE484_HEAVY_SLAM = 0x1E4,
        MOVE485_SCORCHING_SANDS = 0x1E5,
        MOVE486_ELECTRO_BALL = 0x1E6,
        MOVE487_SOAK = 0x1E7,
        MOVE488_FLAME_CHARGE = 0x1E8,
        MOVE489_COIL = 0x1E9,
        MOVE490_LOW_SWEEP = 0x1EA,
        MOVE491_ACID_SPRAY = 0x1EB,
        MOVE492_FOUL_PLAY = 0x1EC,
        MOVE493_STOMPIN_TANTRUM = 0x1ED,
        MOVE494_ENTRAINMENT = 0x1EE,
        MOVE495_ICE_HAMMER = 0x1EF,
        MOVE496_DISARMING_VOICE = 0x1F0,
        MOVE497_ECHOED_VOICE = 0x1F1,
        MOVE498_CHIP_AWAY = 0x1F2,
        MOVE499_CLEAR_SMOG = 0x1F3,
        MOVE500_STORED_POWER = 0x1F4,
        MOVE501_QUICK_GUARD = 0x1F5,
        MOVE502_ALLY_SWITCH = 0x1F6,
        MOVE503_SCALD = 0x1F7,
        MOVE504_SHELL_SMASH = 0x1F8,
        MOVE505_HEAL_PULSE = 0x1F9,
        MOVE506_HEX = 0x1FA,
        MOVE507_SKY_DROP = 0x1FB,
        MOVE508_SHIFT_GEAR = 0x1FC,
        MOVE509_CIRCLE_THROW = 0x1FD,
        MOVE510_INCINERATE = 0x1FE,
        MOVE511_FAIRY_WIND = 0x1FF,
        MOVE512_ACROBATICS = 0x200,
        MOVE513_REFLECT_TYPE = 0x201,
        MOVE514_RETALIATE = 0x202,
        MOVE515_FINAL_GAMBIT = 0x203,
        MOVE516_BESTOW = 0x204,
        MOVE517_INFERNO = 0x205,
        MOVE518_WATER_PLEDGE = 0x206,
        MOVE519_FIRE_PLEDGE = 0x207,
        MOVE520_GRASS_PLEDGE = 0x208,
        MOVE521_VOLT_SWITCH = 0x209,
        MOVE522_STRUGGLE_BUG = 0x20A,
        MOVE523_BULLDOZE = 0x20B,
        MOVE524_FROST_BREATH = 0x20C,
        MOVE525_DRAGON_TAIL = 0x20D,
        MOVE526_WORK_UP = 0x20E,
        MOVE527_ELECTROWEB = 0x20F,
        MOVE528_WILD_CHARGE = 0x210,
        MOVE529_DRILL_RUN = 0x211,
        MOVE530_DUAL_CHOP = 0x212,
        MOVE531_HEART_STAMP = 0x213,
        MOVE532_HORN_LEECH = 0x214,
        MOVE533_SACRED_SWORD = 0x215,
        MOVE534_RAZOR_SHELL = 0x216,
        MOVE535_HEAT_CRASH = 0x217,
        MOVE536_LEAF_TORNADO = 0x218,
        MOVE537_STEAMROLLER = 0x219,
        MOVE538_COTTON_GUARD = 0x21A,
        MOVE539_NIGHT_DAZE = 0x21B,
        MOVE540_PSYSTRIKE = 0x21C,
        MOVE541_TAIL_SLAP = 0x21D,
        MOVE542_HURRICANE = 0x21E,
        MOVE543_HEAD_CHARGE = 0x21F,
        MOVE544_GEAR_GRIND = 0x220,
        MOVE545_SEARING_SHOT = 0x221,
        MOVE546_TECHNO_BLAST = 0x222,
        MOVE547_RELIC_SONG = 0x223,
        MOVE548_SECRET_SWORD = 0x224,
        MOVE549_GLACIATE = 0x225,
        MOVE550_ZING_ZAP = 0x226,
        MOVE551_BLUE_FLARE = 0x227,
        MOVE552_FIERY_DANCE = 0x228,
        MOVE553_METEOR_BEAM = 0x229,
        MOVE554_SOLAR_BLADE = 0x22A,
        MOVE555_SNARL = 0x22B,
        MOVE556_ICICLE_CRASH = 0x22C,
        MOVE557_V_CREATE = 0x22D,
        MOVE558_SKITTER_SMACK = 0x22E,
        MOVE559_BANEFUL_BUNKER = 0x22F,
        MOVE560_FLYING_PRESS = 0x230,
    };

    struct EscapeInfo
    {
        u32 count;
        u8 clientID[4];
    };

    struct SWAN_ALIGNED(4) PokeSet
    {
        void *mons[6];
        u16 damage[6];
        u16 substituteDamage[6];
        u8 damageType[6];
        u16 sortWork[6];
        u8 count;
        u8 countMax;
        u8 getIdx;
        u8 targetPosCount;
    };

    struct PosPokeState
    {
        u8 enabled;
        u8 clientID;
        u8 monID;
    };

    struct PosPoke
    {
        PosPokeState positions[6];
        u8 lastPos[24];
    };

    struct SWAN_ALIGNED(4) HandlerParam_StrParams
    {
        u16 strID;
        __int16 flags;
        int type;
        int args[8];
    };

    struct SWAN_ALIGNED(2) CalcExpWork
    {
        u32 level;
        u8 isBoosted;
        u8 hp;
        u8 atk;
        u8 def;
        u8 spatk;
        u8 spdef;
        u8 spe;
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

    struct EffectivenessRecorder
    {
        int effectiveness[24];
    };

    struct SWAN_ALIGNED(2) BattleFieldStatus
    {
        u32 BattleBGID;
        unsigned int BattlePedestalID;
        unsigned char BtlWeather;
        u8 Season;
        u16 ZoneID;
        u8 Hour;
        u8 Minute;
        char field_E;
        char field_F;
    };
    struct SWAN_ALIGNED(2) StrBuf
    {
        u16 CharCapacity;
        u16 CharCount;
        u32 Magic;
        __int16 String[];
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
    struct SWAN_ALIGNED(4) BtlSetup
    {
        u32 btlType;
        u32 BtlStyle;
        BattleFieldStatus m_FieldStatus;
        u16 BattleBGMID;
        __int16 WinBGMID;
        int field_1C;
        char commMode;
        char field_21;
        u8 BtlSetupType;
        char field_23;
        void *Parties[4];
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
        void *gameData;
        void *m_TrainerData;
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

    struct SWAN_ALIGNED(32) MainModule
    {
        BtlSetup *btlSetup;
        int *BtlvCore;
        void *server;
        int *clients[4];
        TrainerParam trainerParam[4];
        int playerInfo;
        u8 field_C4[4];
        char pokeconClient[232];
        char pokeconServer[232];
        void *srcParty[4];
        void *srcPartyForServer[4];
        void *tempParty;
        void *battleField;
        void *TempPartyPkm;
        int field_2C4;
        int field_2C8;
        int field_2CC;
        int field_2D0;
        int field_2D4;
        unsigned char gap2D8[260];
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
        u16 heapID;
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

    union SWAN_ALIGNED(4) ConditionData
    {
        u32 raw;
        void *permanent;
        void *poke;
        void *poketurn;
        void *turn;
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

    enum PokeType
    {
        TYPE_NORMAL = 0x0, // 0
        TYPE_FIGHT = 0x1,  // 1
        TYPE_FLY = 0x2,    // 2
        TYPE_POIS = 0x3,   // 3
        TYPE_GROUND = 0x4, // 4
        TYPE_ROCK = 0x5,   // 5
        TYPE_BUG = 0x6,    // 6
        TYPE_GHOST = 0x7,  // 7
        TYPE_STEEL = 0x8,  // 8
        TYPE_FIRE = 0x9,   // 9
        TYPE_WATER = 0xA,  // 10
        TYPE_GRASS = 0xB,  // 11
        TYPE_ELEC = 0xC,   // 12
        TYPE_PSY = 0xD,    // 13
        TYPE_ICE = 0xE,    // 14
        TYPE_DRAGON = 0xF, // 15
        TYPE_DARK = 0x10,  // 16
        TYPE_FAIRY = 0x11, // 17
        TYPE_NULL = 0x12,  // 18
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
    struct MoveDamageRec
    {
        u16 moveID;
        u16 damage;
        u8 damageType;
        u8 moveType;
        u8 pokeID;
        u8 pokePos;
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
        ConditionData *Conditions[36];
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
        StatStageParam StatStageParam;
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

    enum BattleEventVar
    {
        VAR_NULL = 0x0,
        VAR_1 = 0x1,
        VAR_MON_ID = 0x2,
        VAR_ATTACKING_MON = 0x3,
        VAR_DEFENDING_MON = 0x4,
        VAR_TARGET_COUNT = 0x5,
        VAR_TARGET_MON_ID = 0x6,
        VAR_7 = 0x7,
        VAR_8 = 0x8,
        VAR_9 = 0x9,
        VAR_A = 0xA,
        VAR_B = 0xB,
        VAR_ACTION = 0xC,
        VAR_POKE_POS = 0xD,
        VAR_ORIGINAL_TARGET = 0xE,
        VAR_PREVIOUS_ABILITY = 0xF,
        VAR_NEXT_ABILITY = 0x10,
        VAR_PRIORITY = 0x11,
        VAR_MOVE_ID = 0x12,
        VAR_MOVE_ID_2 = 0x13,
        VAR_ORIGINAL_MOVE = 0x14,
        VAR_POKE_TYPE = 0x15,
        VAR_MOVE_TYPE = 0x16,
        VAR_MOVE_INDEX = 0x17,
        VAR_MOVE_PRIORITY = 0x18,
        VAR_STAT_STAGE_CHANGE_COUNT = 0x19,
        VAR_MOVE_CATEGORY = 0x1A,
        VAR_TARGET_TYPE = 0x1B,
        VAR_USER_TYPE = 0x1C,
        VAR_CONDITION_ID = 0x1D,
        VAR_CONDITION_ADDRESS = 0x1E,
        VAR_MOVE_EFFECT = 0x1F,
        VAR_VOLUME = 0x20,
        VAR_SEMI_INVULN_TYPE = 0x21,
        VAR_FAIL_CAUSE = 0x22,
        VAR_23 = 0x23,
        VAR_EFFECT_TURN_COUNT = 0x24,
        VAR_DEFAULT_EFFECT_CHANCE = 0x25,
        VAR_EFFECT_CHANCE = 0x26,
        VAR_ACCURACY_STAGE = 0x27,
        VAR_EVASION_STAGE = 0x28,
        VAR_MAX_HIT_COUNT = 0x29,
        VAR_HIT_COUNT = 0x2A,
        VAR_ACCURACY = 0x2B,
        VAR_CRIT_STAGE = 0x2C,
        VAR_ITEM = 0x2D,
        VAR_ITEM_REACTION = 0x2E,
        VAR_SPEED = 0x2F,
        VAR_MOVE_POWER = 0x30,
        VAR_MOVE_POWER_RATIO = 0x31,
        VAR_DAMAGE = 0x32,
        VAR_POWER = 0x33,
        VAR_GUARD = 0x34,
        VAR_RATIO = 0x35,
        VAR_36 = 0x36,
        VAR_FIXED_DAMAGE = 0x37,
        VAR_TYPE_EFFECTIVENESS = 0x38,
        VAR_WEATHER = 0x39,
        VAR_ENDURE = 0x3A,
        VAR_SWAP_POKE_ID = 0x3B,
        VAR_BATTLE_MON_STAT = 0x3C,
        VAR_BATTLE_MON_STAT_SWAP_FLAG = 0x3D,
        VAR_ENABLE_MODE = 0x3E,
        VAR_WORK_ADDRESS = 0x3F,
        VAR_NO_EFFECT_FLAG = 0x40,
        VAR_MOVE_FAIL_FLAG = 0x41,
        VAR_AVOID_FLAG = 0x42,
        VAR_43 = 0x43,
        VAR_TYPE_MATCH_FLAG = 0x44,
        VAR_CRITICAL_FLAG = 0x45,
        VAR_SUBSTITUTE_FLAG = 0x46,
        VAR_SHIELD_DUST_FLAG = 0x47,
        VAR_SHEER_FORCE_FLAG = 0x48,
        VAR_49 = 0x49,
        VAR_TRICK_ROOM_FLAG = 0x4A,
        VAR_IGNORE_TYPE_EFFECTIVENESS = 0x4B,
        VAR_SET_TYPE_EFFECTIVENESS = 0x4C,
        VAR_DELAY_ATTACK_FLAG = 0x4D,
        VAR_MAGIC_COAT_FLAG = 0x4E,
        VAR_MESSAGE_FLAG = 0x4F,
        VAR_GENERAL_USE_FLAG = 0x51,
        VAR_SIDE = 0x52,
        VAR_SIDE_EFFECT = 0x53,
    };

    enum FlowResult
    {
        RESULT_TURN_STARTING = 0x0,
        RESULT_SWITCH = 0x1,
        RESULT_MON_FAINTED = 0x2,
        RESULT_EXP_GAINED = 0x3,
        RESULT_TEAM_FAINTED = 0x4,
        RESULT_ESCAPE = 0x5,
        RESULT_CAPTURE = 0x6,
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

    enum MoveTarget : unsigned __int8
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
        TARGET_LONG_RANGE = 0xE,
    };

    struct ClientIDRecord
    {
        u8 count;
        u8 clientID[4];
    };

    enum BattleEventType
    {
        EVENT_NULL = 0x0,
        EVENT_ACTION_PROCESSING_START = 0x1,
        EVENT_ACTION_PROCESSING_END = 0x2,
        EVENT_MOVE_SEQUENCE_START = 0x3,
        EVENT_MOVE_SEQUENCE_END = 0x4,
        EVENT_BYPASS_SUBSTITUTE = 0x5,
        EVENT_CHECK_DELAYED_MOVE = 0x6,
        EVENT_DECIDE_DELAYED_MOVE = 0x7,
        EVENT_MOVE_SEQUENCE_STEAL = 0x8,
        EVENT_MOVE_SEQUENCE_REFLECT = 0x9,
        EVENT_A = 0xA,
        EVENT_SKIP_RUN_CALC = 0xB,
        EVENT_PREVENT_RUN = 0xC,
        EVENT_RUN_EXIT_MESSAGE = 0xD,
        EVENT_CHECK_SLEEP = 0xE,
        EVENT_CHECK_SPECIAL_PRIORITY = 0xF,
        EVENT_GET_MOVE_PRIORITY = 0x11,
        EVENT_CHECK_FLOATING = 0x12,
        EVENT_CALC_SPEED = 0x13,
        EVENT_14 = 0x14,
        EVENT_BEFORE_ATTACKS = 0x15,
        EVENT_MOVE_REQUEST_FOR_ACTION_ORDER = 0x16,
        EVENT_MOVE_REQUEST_CHECK_FAIL = 0x17,
        EVENT_MOVE_REQUEST_PARAM = 0x18,
        EVENT_MOVE_REQUEST_MESSAGE = 0x19,
        EVENT_CHECK_MOVE_STEAL = 0x1A,
        EVENT_FLOATING_IMMUNE_TO_MOVE = 0x1B,
        EVENT_SKIP_AVOID_CHECK = 0x1C,
        EVENT_CHECK_MOVE_FAIL = 0x1D,
        EVENT_MOVE_EXECUTE_CHECK1 = 0x1E,
        EVENT_MOVE_EXECUTE_CHECK2 = 0x1F,
        EVENT_MOVE_EXECUTE_CHECK3 = 0x20,
        EVENT_MOVE_EXECUTE_FAIL = 0x21,
        EVENT_CHOOSE_MOVE = 0x22,
        EVENT_BREAK_OPPONENT_GUARD = 0x23,
        EVENT_MOVE_EXECUTE_START = 0x24,
        EVENT_MOVE_EXECUTE_EFFECTIVE = 0x25,
        EVENT_MOVE_EXECUTE_NOEFFECT = 0x26,
        EVENT_MOVE_EXECUTE_END = 0x27,
        EVENT_MOVE_PARAM = 0x28,
        EVENT_DECIDE_TARGET = 0x29,
        EVENT_REDIRECT_TARGET = 0x2A,
        EVENT_REDIRECT_TARGETEND = 0x2B,
        EVENT_NOEFFECT_CHECK = 0x2C,
        EVENT_ABILITY_CHECK_NO_EFFECT = 0x2D,
        EVENT_CHECK_PROTECT_BREAK = 0x2E,
        EVENT_AVOID_MOVE = 0x2F,
        EVENT_CHECK_DAMAGE_TO_RECOVER = 0x30,
        EVENT_APPLY_DAMAGE_TO_RECOVER = 0x31,
        EVENT_BYPASS_ACCURACY_CHECK = 0x32,
        EVENT_MOVE_ACCURACY_STAGE = 0x33,
        EVENT_MOVE_ACCURACY = 0x34,
        EVENT_MOVE_HIT_COUNT = 0x35,
        EVENT_CRITICAL_CHECK = 0x36,
        EVENT_MOVE_BASE_POWER = 0x37,
        EVENT_MOVE_POWER = 0x38,
        EVENT_BEFORE_ATTACKER_POWER = 0x39,
        EVENT_BEFORE_DEFENDER_GUARD = 0x3A,
        EVENT_ATTACKER_POWER = 0x3B,
        EVENT_DEFENDER_GUARD = 0x3C,
        EVENT_CHECK_TYPE_EFFECTIVENESS_ENABLE = 0x3D,
        EVENT_CHECK_TYPE_EFFECTIVENESS = 0x3E,
        EVENT_REWRITE_TYPE_EFFECTIVENESS = 0x3F,
        EVENT_TYPE_MATCH_CHECK = 0x40,
        EVENT_SAME_TYPE_ATTACK_BONUS = 0x41,
        EVENT_ATTACKER_TYPE = 0x42,
        EVENT_DEFENDER_TYPE = 0x43,
        EVENT_AFTER_DAMAGE_REACTION = 0x44,
        EVENT_DETERMINE_MOVE_DAMAGE = 0x45,
        EVENT_MOVE_DAMAGE_PROCESSING_1 = 0x46,
        EVENT_MOVE_DAMAGE_PROCESSING_2 = 0x47,
        EVENT_MOVE_DAMAGE_PROCESSING_END = 0x48,
        EVENT_MOVE_DAMAGE_PROCESSING_FINAL = 0x49,
        EVENT_PREVIOUS_MOVE_REACTION = 0x4A,
        EVENT_MOVE_DAMAGE_REACTION_1 = 0x4B,
        EVENT_MOVE_DAMAGE_REACTION_2 = 0x4C,
        EVENT_MOVE_DAMAGE_SIDE_AFTER = 0x4D,
        EVENT_DECREMENT_PP = 0x4E,
        EVENT_DECREMENT_PP_DONE = 0x4F,
        EVENT_CALC_RECOIL = 0x50,
        EVENT_ADD_STAT_STAGE_CHANGE_TARGET = 0x51,
        EVENT_ADD_STAT_STAGE_CHANGE_USER = 0x52,
        EVENT_SWITCH_OUT_INTERRUPT = 0x53,
        EVENT_SWITCH_OUT_END = 0x54,
        EVENT_SWITCH_IN = 0x55,
        EVENT_SWITCH_IN_PREVIOUS = 0x56,
        EVENT_AFTER_LAST_SWITCHIN = 0x57,
        EVENT_CHECK_ACTIVATION = 0x58,
        EVENT_GET_STAT_STAGE_CHANGE_VALUE = 0x59,
        EVENT_STAT_STAGE_CHANGE = 0x5A,
        EVENT_STAT_STAGE_CHANGE_LAST_CHECK = 0x5B,
        EVENT_STAT_STAGE_CHANGE_FAIL = 0x5C,
        EVENT_STAT_STAGE_CHANGE_APPLIED = 0x5D,
        EVENT_MOVE_STAT_STAGE_CHANGE_APPLIED = 0x5E,
        EVENT_MOVE_CONDITION_TURN_COUNT = 0x5F,
        EVENT_MOVE_CONDITION_SPECIAL = 0x60,
        EVENT_MOVE_CONDITION_MESSAGE = 0x61,
        EVENT_MOVE_CONDITION_PARAM = 0x62,
        EVENT_ADD_CONDITION_TYPE = 0x63,
        EVENT_ADD_CONDITION = 0x64,
        EVENT_ADD_CONDITION_CHECK_FAIL = 0x65,
        EVENT_ADD_CONDITION_APPLIED = 0x66,
        EVENT_ADD_CONDITION_FAIL = 0x67,
        EVENT_ADD_BASIC_STATUS = 0x68,
        EVENT_MOVE_CONDITION_APPLIED = 0x69,
        EVENT_ABILITY_NULLIFIED = 0x6A,
        EVENT_CONDITION_DAMAGE = 0x6B,
        EVENT_MOVE_FLINCH_CHANCE = 0x6C,
        EVENT_FLINCH_CHECK = 0x6D,
        EVENT_FLINCH_FAIL = 0x6E,
        EVENT_FLINCH_APPLIED = 0x6F,
        EVENT_OHKO_CHECK = 0x70,
        EVENT_OHKO_PREVENT = 0x71,
        EVENT_USE_ITEM = 0x72,
        EVENT_USE_ITEM_TEMP = 0x73,
        EVENT_ENDURE_CHECK = 0x74,
        EVENT_ENDURE = 0x75,
        EVENT_TURN_CHECK_BEGIN = 0x76,
        EVENT_TURN_CHECK_END = 0x77,
        EVENT_TURN_CHECK_DONE = 0x78,
        EVENT_NOTIFY_AIR_LOCK = 0x79,
        EVENT_WEATHER_CHECK = 0x7A,
        EVENT_WEIGHT_RATIO = 0x7B,
        EVENT_MOVE_WEATHER_TURN_COUNT = 0x7C,
        EVENT_WEATHER_CHANGE = 0x7D,
        EVENT_AFTER_WEATHER_CHANGE = 0x7E,
        EVENT_WEATHER_REACTION = 0x7F,
        EVENT_ENABLE_SIMPLE_DAMAGE = 0x80,
        EVENT_DAMAGE_PROCESSING_START = 0x81,
        EVENT_DAMAGE_PROCESSING_END_PREVIOUSHIT = 0x82,
        EVENT_DAMAGE_PROCESSING_END_HIT_REAL = 0x83,
        EVENT_DAMAGE_PROCESSING_END_HIT_1 = 0x84,
        EVENT_DAMAGE_PROCESSING_END_HIT_2 = 0x85,
        EVENT_DAMAGE_PROCESSING_END_HIT_3 = 0x86,
        EVENT_DAMAGE_PROCESSING_END_HIT_4 = 0x87,
        EVENT_DAMAGE_PROCESSING_END = 0x88,
        EVENT_BEFORE_ABILITY_CHANGE = 0x89,
        EVENT_AFTER_ABILITY_CHANGE = 0x8A,
        EVENT_CHECK_FORCE_SWITCH = 0x8B,
        EVENT_CALC_DRAIN = 0x8C,
        EVENT_CALC_DRAIN_END = 0x8D,
        EVENT_RECOVER_HP = 0x8F,
        EVENT_AFTER_ITEM_EQUIP = 0x90,
        EVENT_CHECK_ITEM_REACTION = 0x91,
        EVENT_ITEM_CONSUMED = 0x92,
        EVENT_CHECK_CHARGE_UP_FAIL = 0x93,
        EVENT_CHECK_CHARGE_UP_SKIP = 0x94,
        EVENT_CHARGE_UP_START = 0x95,
        EVENT_CHARGE_UP_START_DONE = 0x96,
        EVENT_CHARGE_UP_SKIP = 0x97,
        EVENT_CHARGE_UP_END = 0x98,
        EVENT_CHECK_HIDING = 0x99,
        EVENT_HELD_ITEM_CHECK = 0x9A,
        EVENT_HELD_ITEM_FAIL = 0x9B,
        EVENT_HELD_ITEM_DECIDE = 0x9C,
        EVENT_ITEM_REWRITE_DONE = 0x9D,
        EVENT_CALL_FIELD_EFFECT = 0x9E,
        EVENT_CHECK_SIDE_EFFECT_PARAM = 0x9F,
        EVENT_UNCATEGORIZED_MOVE = 0xA0,
        EVENT_UNCATEGORIZED_MOVE_NO_TARGET = 0xA1,
        EVENT_COMBINED_MOVE_CHECK = 0xA2,
        EVENT_NOTIFY_FAINTED = 0xA3,
        EVENT_AFTER_SHIFT = 0xA4,
    };

    struct MoveAnimCtrl
    {
        unsigned __int16 moveID;
        unsigned __int8 attackerPos;
        unsigned __int8 targetPos;
        unsigned __int8 effectIndex;
        unsigned __int8 flags;
        unsigned __int16 subEff;
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

    struct SWAN_PACKED SWAN_ALIGNED(1) calc_damage_record
    {
        u16 damage;
        unsigned __int16 targetID : 5;
        unsigned __int16 effectiveness : 3;
        unsigned __int16 unk : 1;
        unsigned __int16 isEndureActive : 1;
        unsigned __int16 unk2 : 3;
        unsigned __int16 isCritical : 1;
        unsigned __int16 isFixedDamage : 1;
        unsigned __int16 isSubstituteActive : 1;
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
    struct CalcDamageRecord
    {
        u8 real_hit_count;
        u8 substitute_hit_count;
        u8 total_hit_count;
        u8 pad;
        calc_damage_record record[6];
    };

    struct MoveStealParam
    {
        char stealCount;
        char stealMonID[6];
        char targetPos[6];
        char targetMonID[6];
    };

    struct SWAN_ALIGNED(4) PokeSetStackUnit
    {
        PokeSet TargetOriginal;
        PokeSet Target;
        PokeSet Ally;
        PokeSet Enemy;
        PokeSet Damaged;
        PokeSet StealTarget;
        PokeSet psetTemp;
        MoveAnimCtrl moveAnimCtrl;
        MoveParam moveParam;
        MoveParam MoveParamOriginal;
        HitCheckParam hitCheck;
        MoveStealParam moveStealParam;
        MoveStealParam magicCoatParam;
        CalcDamageRecord calcDamageAlly;
        CalcDamageRecord calcDamageEnemy;
        char defaultTargetPos;
        char field_28D;
        char field_28E;
        char field_28F;
    };

    struct LevelUpInfo
    {
        u8 level;
        u16 hp;
        u16 atk;
        u16 def;
        u16 spa;
        u16 spd;
        u16 spe;
    };

    struct HEManager
    {
        u32 state;
        u8 workBuffer[500];
    };

    struct EventWorkStack
    {
        u8 work[512];
        u16 size[16];
        u32 sp;
    };

    enum TurnFlag
#ifdef __cplusplus
        : u32
#endif
    {

        TURNFLAG_ACTIONSTART = 0x0,
        TURNFLAG_ACTIONDONE = 0x1,
        TURNFLAG_DAMAGED = 0x2,
        TURNFLAG_MOVEPROCDONE = 0x3,
        TURNFLAG_FLINCH = 0x4,
        // TURNFLAG_FOCUSPUNCHREADY = 0x5,
        TURNFLAG_MOVEFAILED = 0x5,
        // TURNFLAG_FOCUSPUNCHFAIL = 0x6,
        TURNFLAG_MOVEFAILEDLASTTURN = 0x6,
        TURNFLAG_PROTECT = 0x7,
        TURNFLAG_ITEMCONSUMED = 0x8,
        TURNFLAG_CANTUSEITEM = 0x9,
        TURNFLAG_COMBOMOVEREADY = 0xA,
        TURNFLAG_HIDEMOVEOFF = 0xB,
        TURNFLAG_MOVED = 0xC,
        TURNFLAG_TURNCHECKCONDITIONPASSED = 0xD,
        TURNFLAG_ACCURACYUP = 0xE,
        TURNFLAG_USINGFLING = 0xF,
    };
    struct BattleAction_Default
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 param : 28;
    };
    struct BattleAction_Attack
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 targetPos : 3;
        unsigned __int32 moveID : 19;
        unsigned __int32 moveInfoFlag : 1;
        unsigned __int32 pad : 5;
    };
    struct BattleAction_Item
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 targetIdx : 3;
        unsigned __int32 itemID : 20;
        unsigned __int32 moveIdx : 5;
    };
    struct BattleAction_Switch
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 battlePos : 3;
        unsigned __int32 partyIndex : 3;
        unsigned __int32 unkFlag : 1;
        unsigned __int32 pad : 21;
    };
    struct BattleAction_Run
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 escape : 28;
    };
    struct BattleAction_Rotate
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 rotation : 3;
        unsigned __int32 pad : 3;
        unsigned __int32 unkFlag : 1;
        unsigned __int32 pad2 : 21;
    };
    struct BattleAction_Shift
    {
        unsigned __int32 actionType : 4;
        unsigned __int32 shift : 28;
    };

    union BattleActionParam
    {
        u32 raw;
        BattleAction_Default Default;
        BattleAction_Attack Attack;
        BattleAction_Item Item;
        BattleAction_Switch Switch;
        BattleAction_Run Run;
        BattleAction_Shift Shift;
        BattleAction_Rotate Rotate;
    };

    struct ActionOrderWork
    {
        BattleMon *BattleMon;
        BattleActionParam *Action;
        int orderData;
        char clientID;
        char fDone;
        char InterruptActive;
        char field_F;
    };
    struct SWAN_ALIGNED(8) ServerFlow
    {
        void *server;
        MainModule *mainModule;
        void *pokeCon;
        void *serverCommandQueue;
        int turnCount;
        FlowResult flowResult;
        int heapHandle;
        MoveRecord moveRecord;
        FaintRecord faintRecord;
        void *evolutionDataPtr;
        MoveAnimCtrl *moveAnimCtrl;
        MoveStealParam *moveStealParam;
        MoveStealParam *magicCoatParam;
        HitCheckParam *hitCheckParam;
        EscapeInfo escapeInfo;
        LevelUpInfo levelUpInfo;
        ClientIDRecord clientIDRecord;
        int rotationHandlerWork[24][7];
        int SimulationCounter;
        int StatStageChangeCount;
        char cmdBuildStep;
        char actOrderStep;
        char turnCheckStep;
        char defaultTargetPos;
        __int16 heapID;
        char actionOrderIndex;
        char actionOrderEndIndex;
        _BYTE ballTargetPos;
        char revivedPokeCount;
        char escapeAttempts;
        char moveAnimIndex;
        char SwitchOutInterruptingMonCount;
        char thruDeadMsgPokeID;
        char flags;
        u8 SwitchOutInterruptingMonIDs[6];
        u8 RevivedMonIDs[24];
        char FaintedMonFlag[24];
        char WasInBattleFlag[24];
        char ClientSwitchCount[4];
        ActionOrderWork actionOrderWork[6];
        ActionOrderWork TempActionOrderWork;
        PokeSet *PokeSetTargetOriginal;
        PokeSet *PokeSetTarget;
        PokeSet *PokeSetAlly;
        PokeSet *PokeSetEnemy;
        PokeSet *PokeSetDamaged;
        PokeSet *PokeSetStealTarget;
        PokeSet *PokeSetTemp;
        CalcDamageRecord *CalcDamageAlly;
        CalcDamageRecord *CalcDamageEnemy;
        PokeSetStackUnit PokeSetStack[7];
        int PokeSetStackPtr;
        PokeSet PokeSetSwitchInProc;
        MoveParam *moveParam;
        MoveParam *moveParamOriginal;
        PosPoke posPoke;
        HandlerParam_StrParams StrParam;
        CalcExpWork calcExpWork[6];
        EventWorkStack eventWorkStack;
        HEManager heManager;
        MoveDamageRec moveDamageRec;
        __int16 PrevUsedMove;
        ActionIgnoreReason actionIgnoreReason;
        EffectivenessCounter effectivenessCounter;
        EffectivenessRecorder effectivenessRecorder;
        u8 flowFlags[4];
        u8 TempWork[320];
        int PokestarResult;
    };
    struct EventWorkSave
    {
        u16 Works[431];
        u8 FlagBytes[383];
        u8 CanRespawnHiddenItems;
    };

    enum BattleMonValue
    {
        VALUE_NULL = 0x0,
        VALUE_ATTACK_STAGE = 0x1,
        VALUE_DEFENSE_STAGE = 0x2,
        VALUE_SPECIAL_ATTACK_STAGE = 0x3,
        VALUE_SPECIAL_DEFENSE_STAGE = 0x4,
        VALUE_SPEED_STAGE = 0x5,
        VALUE_ACCURACY_STAGE = 0x6,
        VALUE_EVASION_STAGE = 0x7,
        VALUE_ATTACK_STAT = 0x8,
        VALUE_DEFENSE_STAT = 0x9,
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
        VALUE_BASE_ATTACK = 0x15,
    };
    enum MoveCondition
    {
        CONDITION_NONE = 0x0,
        CONDITION_PARALYSIS = 0x1,
        CONDITION_SLEEP = 0x2,
        CONDITION_FREEZE = 0x3,
        CONDITION_BURN = 0x4,
        CONDITION_POISON = 0x5,
        CONDITION_CONFUSION = 0x6,
        CONDITION_ATTRACT = 0x7,
        CONDITION_BIND = 0x8,
        CONDITION_NIGHTMARE = 0x9,
        CONDITION_CURSE = 0xA,
        CONDITION_TAUNT = 0xB,
        CONDITION_TORMENT = 0xC,
        CONDITION_DISABLE = 0xD,
        CONDITION_YAWN = 0xE,
        CONDITION_HEAL_BLOCK = 0xF,
        CONDITION_GASTRO_ACID = 0x10,
        CONDITION_FORESIGHT = 0x11,
        CONDITION_LEECH_SEED = 0x12,
        CONDITION_EMBARGO = 0x13,
        CONDITION_PERISH_SONG = 0x14,
        CONDITION_INGRAIN = 0x15,
        CONDITION_BLOCK = 0x16,
        CONDITION_ENCORE = 0x17,
        CONDITION_ROOST = 0x18,
        CONDITION_MOVE_LOCK = 0x19,
        CONDITION_CHARGE_LOCK = 0x1A,
        CONDITION_CHOICE_LOCK = 0x1B,
        CONDITION_MUST_HIT = 0x1C,
        CONDITION_LOCK_ON = 0x1D,
        CONDITION_FLOATING = 0x1E,
        CONDITION_KNOCKED_DOWN = 0x1F,
        CONDITION_TERA = 0x20,
        CONDITION_SKY_DROP = 0x21,
        CONDITION_TELEKINESIS = 0x22,
        CONDITION_AQUA_RING = 0x23,
        CONDITION_24 = 0x24,
    };
    enum AbilID
    {
        ABIL_NULL = 0x0,
        ABIL001_STENCH = 0x1,
        ABIL002_DRIZZLE = 0x2,
        ABIL003_SPEED_BOOST = 0x3,
        ABIL004_BATTLE_ARMOR = 0x4,
        ABIL005_STURDY = 0x5,
        ABIL006_BULLETPROOF = 0x6,
        ABIL007_CORROSION = 0x7,
        ABIL008_SAND_VEIL = 0x8,
        ABIL009_STATIC = 0x9,
        ABIL010_VOLT_ABSORB = 0xA,
        ABIL011_WATER_ABSORB = 0xB,
        ABIL012_GALVANIZE = 0xC,
        ABIL013_CLOUD_NINE = 0xD,
        ABIL014_KEEN_SENSES = 0xE,
        ABIL015_THUNDER_ARMOR = 0xF,
        ABIL016_BALLISTICS = 0x10,
        ABIL017_FLUFFY = 0x11,
        ABIL018_FLASH_FIRE = 0x12,
        ABIL019_RESILIENT = 0x13,
        ABIL020_QUICK_DRAW = 0x14,
        ABIL021_WELL_BAKED_BODY = 0x15,
        ABIL022_INTIMIDATE = 0x16,
        ABIL023_SHADOW_TAG = 0x17,
        ABIL024_ROUGH_SKIN = 0x18,
        ABIL025_WONDER_GUARD = 0x19,
        ABIL026_LEVITATE = 0x1A,
        ABIL027_EFFECT_SPORE = 0x1B,
        ABIL028_SYNCHRONIZE = 0x1C,
        ABIL029_STRONG_BODY = 0x1D,
        ABIL030_NATURAL_CURE = 0x1E,
        ABIL031_LIGHTNING_ROD = 0x1F,
        ABIL032_SERENE_GRACE = 0x20,
        ABIL033_SWIFT_SWIM = 0x21,
        ABIL034_CHLOROPHYLL = 0x22,
        ABIL035_ILLUMINATE = 0x23,
        ABIL036_TRACE = 0x24,
        ABIL037_HUGE_POWER = 0x25,
        ABIL038_BERSERK = 0x26,
        ABIL039_INNER_FOCUS = 0x27,
        ABIL040_PIXILATE = 0x28,
        ABIL041_MERCILESS = 0x29,
        ABIL042_MAGNET_PULL = 0x2A,
        ABIL043_AMPLIFIER = 0x2B,
        ABIL044_RAIN_DISH = 0x2C,
        ABIL045_SAND_STREAM = 0x2D,
        ABIL046_NEUTRALIZING_GAS = 0x2E,
        ABIL047_THICK_FAT = 0x2F,
        ABIL048_REFRIGERATE = 0x30,
        ABIL049_FLAME_BODY = 0x31,
        ABIL050_RUN_AWAY = 0x32,
        ABIL051_WIND_RIDER = 0x33,
        ABIL052_HYPER_CUTTER = 0x34,
        ABIL053_PICKUP = 0x35,
        ABIL054_TRUANT = 0x36,
        ABIL055_HUSTLE = 0x37,
        ABIL056_GOOEY = 0x38,
        ABIL057_PLUS = 0x39,
        ABIL058_MINUS = 0x3A,
        ABIL059_FORECAST = 0x3B,
        ABIL060_AERILATE = 0x3C,
        ABIL061_SHED_SKIN = 0x3D,
        ABIL062_GUTS = 0x3E,
        ABIL063_MARVEL_SCALE = 0x3F,
        ABIL064_LIQUID_OOZE = 0x40,
        ABIL065_OVERGROW = 0x41,
        ABIL066_BLAZE = 0x42,
        ABIL067_TORRENT = 0x43,
        ABIL068_SWARM = 0x44,
        ABIL069_DETERMINED = 0x45,
        ABIL070_DROUGHT = 0x46,
        ABIL071_ARENA_TRAP = 0x47,
        ABIL072_VITAL_SPIRIT = 0x48,
        ABIL073_WHITE_SMOKE = 0x49,
        ABIL074_PURE_POWER = 0x4A,
        ABIL075_SHELL_ARMOR = 0x4B,
        ABIL076_AIR_LOCK = 0x4C,
        ABIL077_SLUSH_RUSH = 0x4D,
        ABIL078_MOTOR_DRIVE = 0x4E,
        ABIL079_RIVALRY = 0x4F,
        ABIL080_COLOSSAL = 0x50,
        ABIL081_SNOW_CLOAK = 0x51,
        ABIL082_GLUTTONY = 0x52,
        ABIL083_ANGER_POINT = 0x53,
        ABIL084_UNBURDEN = 0x54,
        ABIL085_HEATPROOF = 0x55,
        ABIL086_SIMPLE = 0x56,
        ABIL087_DRY_SKIN = 0x57,
        ABIL088_EXPLOIT = 0x58,
        ABIL089_IRON_FIST = 0x59,
        ABIL090_POISON_HEAL = 0x5A,
        ABIL091_ADAPTABILITY = 0x5B,
        ABIL092_SKILL_LINK = 0x5C,
        ABIL093_STRONG_JAW = 0x5D,
        ABIL094_SOLAR_POWER = 0x5E,
        ABIL095_QUICK_FEET = 0x5F,
        ABIL096_NORMALIZE = 0x60,
        ABIL097_SNIPER = 0x61,
        ABIL098_MAGIC_GUARD = 0x62,
        ABIL099_NO_GUARD = 0x63,
        ABIL100_TOUGH_CLAWS = 0x64,
        ABIL101_TECHNICIAN = 0x65,
        ABIL102_FUR_COAT = 0x66,
        ABIL103_DISTRACTING = 0x67,
        ABIL104_MOLD_BREAKER = 0x68,
        ABIL105_MOISTURIZE = 0x69,
        ABIL106_AFTERMATH = 0x6A,
        ABIL107_ANTICIPATION = 0x6B,
        ABIL108_FOREWARN = 0x6C,
        ABIL109_UNAWARE = 0x6D,
        ABIL110_TENACITY = 0x6E,
        ABIL111_FILTER = 0x6F,
        ABIL112_SLOW_START = 0x70,
        ABIL113_SCRAPPY = 0x71,
        ABIL114_STORM_DRAIN = 0x72,
        ABIL115_ICE_BODY = 0x73,
        ABIL116_SOLID_ROCK = 0x74,
        ABIL117_SNOW_WARNING = 0x75,
        ABIL118_HONEY_GATHER = 0x76,
        ABIL119_STAKEOUT = 0x77,
        ABIL120_RECKLESS = 0x78,
        ABIL121_MULTITYPE = 0x79,
        ABIL122_FLOWER_GIFT = 0x7A,
        ABIL123_BAD_DREAMS = 0x7B,
        ABIL124_PICKPOCKET = 0x7C,
        ABIL125_SHEER_FORCE = 0x7D,
        ABIL126_CONTRARY = 0x7E,
        ABIL127_UNNERVE = 0x7F,
        ABIL128_DEFIANT = 0x80,
        ABIL129_DEFEATIST = 0x81,
        ABIL130_CURSED_BODY = 0x82,
        ABIL131_HEALER = 0x83,
        ABIL132_FRIEND_GUARD = 0x84,
        ABIL133_WEAK_ARMOR = 0x85,
        ABIL134_HEAVY_METAL = 0x86,
        ABIL135_LIGHT_METAL = 0x87,
        ABIL136_MAJESTIC_WARD = 0x88,
        ABIL137_TOXIC_BOOST = 0x89,
        ABIL138_FLARE_BOOST = 0x8A,
        ABIL139_GOURMAND = 0x8B,
        ABIL140_PERMAFROST = 0x8C,
        ABIL141_MOODY = 0x8D,
        ABIL142_OVERCOAT = 0x8E,
        ABIL143_POISON_TOUCH = 0x8F,
        ABIL144_REGENERATOR = 0x90,
        ABIL145_SAVANT = 0x91,
        ABIL146_SAND_RUSH = 0x92,
        ABIL147_WONDER_SKIN = 0x93,
        ABIL148_PATIENT = 0x94,
        ABIL149_ILLUSION = 0x95,
        ABIL150_IMPOSTER = 0x96,
        ABIL151_INFILTRATOR = 0x97,
        ABIL152_CONTAGIOUS = 0x98,
        ABIL153_MOXIE = 0x99,
        ABIL154_JUSTIFIED = 0x9A,
        ABIL155_RATTLED = 0x9B,
        ABIL156_MAGIC_BOUNCE = 0x9C,
        ABIL157_SAP_SIPPER = 0x9D,
        ABIL158_PRANKSTER = 0x9E,
        ABIL159_SAND_FORCE = 0x9F,
        ABIL160_IRON_BARBS = 0xA0,
        ABIL161_ZEN_MODE = 0xA1,
        ABIL162_ILLUMINATION = 0xA2,
        ABIL163_TURBOBLAZE = 0xA3,
        ABIL164_TERAVOLT = 0xA4,
    };

    enum MoveField
    {
        MVDATA_TYPE = 0x0,
        MVDATA_QUALITY = 0x1,
        MVDATA_CATEGORY = 0x2,
        MVDATA_POWER = 0x3,
        MVDATA_ACCURACY = 0x4,
        MVDATA_BASEPP = 0x5,
        MVDATA_PRIORITY = 0x6,
        MVDATA_CRIT_STAGE = 0x7,
        MVDATA_HIT_MAX = 0x8,
        MVDATA_HIT_MIN = 0x9,
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

    enum ConditionFlag
    {
        CONDITIONFLAG_ACTION_DONE = 0x0,
        CONDITIONFLAG_NO_SWITCH = 0x1,
        CONDITIONFLAG_CHARGE = 0x2,
        CONDITIONFLAG_FLY = 0x3,
        CONDITIONFLAG_DIVE = 0x4,
        CONDITIONFLAG_DIG = 0x5,
        CONDITIONFLAG_SHADOW_FORCE = 0x6,
        CONDITIONFLAG_DEFENSE_CURL = 0x7,
        CONDITIONFLAG_MINIMIZE = 0x8,
        CONDITIONFLAG_FOCUS_ENERGY = 0x9,
        CONDITIONFLAG_POWER_TRICK = 0xA,
        CONDITIONFLAG_MICLE_BERRY = 0xB,
        CONDITIONFLAG_NO_ACTION = 0xC,
        CONDITIONFLAG_FLASH_FIRE = 0xD,
        CONDITIONFLAG_BATON_PASS = 0xE,
        CONDITIONFLAG_NULL = 0xF,
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
    enum PersonalField
    {
        Personal_HP = 0x0,
        Personal_ATK = 0x1,
        Personal_DEF = 0x2,
        Personal_SPE = 0x3,
        Personal_SPA = 0x4,
        Personal_SPD = 0x5,
        Personal_Type1 = 0x6,
        Personal_Type2 = 0x7,
        Personal_CaptureRate = 0x8,
        Personal_BaseEXP = 0x9,
        Personal_EvHP = 0xA,
        Personal_EvATK = 0xB,
        Personal_EvDEF = 0xC,
        Personal_EvSPE = 0xD,
        Personal_EvSPA = 0xE,
        Personal_EvSPD = 0xF,
        Personal_Telekinesis = 0x10,
        Personal_WildItem50 = 0x11,
        Personal_WildItem5 = 0x12,
        Personal_WildItem1 = 0x13,
        Personal_GenderProb = 0x14,
        Personal_EggHappiness = 0x15,
        Personal_BaseHappiness = 0x16,
        Personal_GrowthRate = 0x17,
        Personal_EggGroup1 = 0x18,
        Personal_EggGroup2 = 0x19,
        Personal_Abil1 = 0x1A,
        Personal_Abil2 = 0x1B,
        Personal_AbilH = 0x1C,
        Personal_EscapeRate = 0x1D,
        Personal_FormeDataOffs = 0x1E,
        Personal_FormeSpritesOffset = 0x1F,
        Personal_FormeCount = 0x20,
        Personal_Color = 0x21,
        Personal_SpriteFlip = 0x22,
        Personal_SpriteForme = 0x23,
        Personal_EvoStage = 0x24,
        Personal_Height = 0x25,
        Personal_Weight = 0x26,
        Personal_TMHM1 = 0x27,
        Personal_TMHM2 = 0x28,
        Personal_TMHM3 = 0x29,
        Personal_TMHM4 = 0x2A,
        Personal_TypeTutor = 0x2B,
        Personal_SpecialTutor1 = 0x2C,
        Personal_SpecialTutor2 = 0x2D,
        Personal_SpecialTutor3 = 0x2E,
        Personal_SpecialTutor4 = 0x2F,
    };

#pragma endregion


#pragma region Functions
    extern void MoveEvent_ForceRemoveItemFromBattleMon(BattleMon *a1, int a2);
    extern int MoveEvent_AddItem(BattleMon *a1, int a2, int a3);
    extern u32 PML_MoveGetCategory(int wazaId);
    extern void BattleEventVar_Push();
    extern u32 BattleEventVar_SetConstValue(BattleEventVar a1, int a2);
    extern int BattleMon_GetID(BattleMon *a1);
    extern u32 BattleEventVar_SetValue(BattleEventVar a1, int a2);
    extern void BattleEvent_CallHandlers(ServerFlow *a1, BattleEventType a2);
    extern int BattleEventVar_GetValue(BattleEventVar a1);
    extern int ServerEvent_GetMovePower(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4);
    extern int ServerEvent_GetTargetDefenses(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4, int a5);
    extern int ServerEvent_GetAttackPower(
        ServerFlow *a1,
        BattleMon *AttackingMon,
        BattleMon *DefendingMon,
        MoveParam *a4,
        int criticalFlag);
    extern int BattleMon_GetValue(BattleMon *a1, BattleMonValue a2);
    extern unsigned int CalcBaseDamage(int power, int attack, int level, unsigned int defense);
    extern unsigned int fixed_round(int a1, int a2);
    extern int ServerEvent_GetWeather(ServerFlow *a1);
    extern int WeatherPowerMod(int a1, int a2);
    extern int MainModule_GetDebugFlag();
    extern bool ServerFlow_IsNotPokestarBattle(ServerFlow *a1);
    extern int BattleRandom(unsigned int a1);
    extern int ServerEvent_SameTypeAttackBonus(ServerFlow *a1, BattleMon *a2, PokeType a3);
    extern unsigned int TypeEffectivenessPowerMod(unsigned int result, unsigned int a2);
    extern MoveCondition BattleMon_GetStatus(BattleMon *a1);
    extern unsigned int BattleEventVar_SetMulValue(BattleEventVar a1, int a2, int a3, int a4);
    extern void BattleEventVar_Pop();
    extern EventWorkSave *GameData_GetEventWork(void *gameData);
    extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
    extern int BattleMon_GetPreviousMove(BattleMon *a1);
    extern bool BattleMon_GetTurnFlag(BattleMon *a1, TurnFlag a2);
    extern u32 PML_MoveGetParam(int wazaId, MoveField dataId);
    extern int BattleMon_GetCritStage(BattleMon *a1);
    extern u32 BattleEventVar_SetRewriteOnceValue(BattleEventVar a1, int a2);
    extern bool PML_MoveIsAlwaysCrit(int wazaId);
    extern bool BattleMon_GetConditionFlag(BattleMon *a1, ConditionFlag a2);

    bool HasMoldBreaker(BattleMon *a1)
    {
        return (BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL104_MOLD_BREAKER || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL163_TURBOBLAZE || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL164_TERAVOLT);
    }
    extern bool BattleMon_CheckIfMoveCondition(BattleMon *a1, MoveCondition a2);
    extern int Move_GetID(BattleMon *a1, int a2);
    extern u8 PML_MoveGetType(int a1);
    extern u32 PML_PersonalGetParamSingle(u16 species, u16 form, PersonalField field);
    extern int splitTypeCore(BattleMon *a1, u8 *a2, u8 *a3);

#pragma endregion

#pragma region CriticalHitChanges
    /*

        --------------------------------------------------------------------------------------------------
        ---------------------------------- CRITICAL HIT CHANGES ------------------------------------------
        --------------------------------------------------------------------------------------------------

    */
    u32 GetCritSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16415);
        return *lvl_cap_ptr;
    }

    int VANILLA_CRIT_CHANCES[5] = {0x10, 8, 4, 3, 2};
    int MODERN_CRIT_CHANCES[5] = {0x18, 8, 2, 0, 0};

    bool THUMB_BRANCH_RollCritical(int a1)
    {
        if (GetCritSetting() == 0)
        {
            return BattleRandom(VANILLA_CRIT_CHANCES[a1]) == 0;
        }
        else
        {
            return BattleRandom(MODERN_CRIT_CHANCES[a1]) == 0;
        }
    }

    bool personalRollCritical(int a1)
    {
        if (GetCritSetting() == 0)
        {
            return BattleRandom(VANILLA_CRIT_CHANCES[a1]) == 0;
        }
        else
        {
            return BattleRandom(MODERN_CRIT_CHANCES[a1]) == 0;
        }
    }

    bool THUMB_BRANCH_ServerEvent_CheckCritical(ServerFlow *a1, BattleMon *a2, BattleMon *a3, int a4)
    {
        __int16 Param; // r4
        int v8;        // r4
        int ID;        // r0
        int v10;       // r0
        bool v11;      // r4
        int Value;     // r0

        Param = PML_MoveGetParam(a4, MVDATA_CRIT_STAGE);
        v8 = (Param + BattleMon_GetCritStage(a2));
        BattleEventVar_Push();
        ID = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, ID);
        v10 = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v10);
        BattleEventVar_SetValue(VAR_CRIT_STAGE, v8);
        v11 = 0;
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEvent_CallHandlers(a1, EVENT_CRITICAL_CHECK);
        if (!BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG))
        {
            ;
            if (BattleMon_GetConditionFlag(a3, CONDITIONFLAG_DEFENSE_CURL))
            {
                v11 = 0;
            }
            else if (PML_MoveIsAlwaysCrit(a4))
            {
                v11 = 1;
            }
            else
            {
                Value = BattleEventVar_GetValue(VAR_CRIT_STAGE);
                if (Value > 4)
                {
                    // LOBYTE(Value) = 4;
                    Value = (Value & 0xFF) | 4;
                }
                v11 = personalRollCritical(Value);
            }
            if (MainModule_GetDebugFlag())
            {
                v11 = 1;
            }
        }
        BattleEventVar_Pop();
        return v11;
    }

#pragma endregion

#pragma region DamageCalc

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ CALC DAMAGE FUNCTION  ---------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    int THUMB_BRANCH_SAFESTACK_ServerEvent_CalcDamage(
        ServerFlow *a1,
        BattleMon *AttackingMon,
        BattleMon *DefendingMon,
        MoveParam *MoveParam,
        int TypeEffectiveness,
        int targetDmgRatio,
        int criticalFlag,
        int BattleDebugMode,
        _WORD *destDamage)
    {
        int ID;                // r0
        int v13;               // r0
        int defense;           // r7
        unsigned __int8 level; // r0
        int v16;               // r0
        unsigned int fxDamage; // r7
        int Weather;           // r0
        int weatherDmgRatio;   // r1
        int damageRoll;        // r0
        PokeType moveType;     // r2
        int v22;               // r0
        int v23;               // r4
        int v24;               // r4
        int v25;               // r0
        unsigned int Value;    // [sp+8h] [bp-28h]
        int v29;               // [sp+Ch] [bp-24h]
        int Category;          // [sp+10h] [bp-20h]
        int power;             // [sp+14h] [bp-1Ch]
        int attack;            // [sp+18h] [bp-18h]

        Category = PML_MoveGetCategory(MoveParam->MoveID);
        v29 = 0;
        BattleEventVar_Push();
        BattleEventVar_SetConstValue(VAR_TYPE_EFFECTIVENESS, TypeEffectiveness);
        ID = BattleMon_GetID(AttackingMon);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v13 = BattleMon_GetID(DefendingMon);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v13);
        BattleEventVar_SetConstValue(VAR_CRITICAL_FLAG, criticalFlag);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, MoveParam->moveType);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, MoveParam->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, Category);
        BattleEventVar_SetValue(VAR_FIXED_DAMAGE, 0);
        BattleEvent_CallHandlers(a1, EVENT_MOVE_DAMAGE_PROCESSING_1);
        Value = BattleEventVar_GetValue(VAR_FIXED_DAMAGE);
        if (Value)
        {
            v29 = 1;
        }
        else
        {
            power = ServerEvent_GetMovePower(a1, AttackingMon, DefendingMon, MoveParam);
            attack = ServerEvent_GetAttackPower(a1, AttackingMon, DefendingMon, MoveParam, criticalFlag);
            defense = ServerEvent_GetTargetDefenses(a1, AttackingMon, DefendingMon, MoveParam, criticalFlag);
            level = BattleMon_GetValue(AttackingMon, VALUE_LEVEL);
            v16 = CalcBaseDamage(power, attack, level, defense);
            fxDamage = v16;
            if (targetDmgRatio != 4096)
            {
                fxDamage = fixed_round(v16, targetDmgRatio);
            }

            Weather = ServerEvent_GetWeather(a1);
            weatherDmgRatio = WeatherPowerMod(Weather, MoveParam->moveType);

            // ADD
            // Overcoat / Utility Umbrella Logic
            //
            if (DefendingMon->HeldItem == 544 || (!HasMoldBreaker(AttackingMon) && BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)){
                weatherDmgRatio == 4096;
            }

            if (weatherDmgRatio != 4096)
            {
                fxDamage = fixed_round(fxDamage, weatherDmgRatio);
            }

            if (criticalFlag)
            {

                if (GetCritSetting() == 1 && MoveParam->MoveID != MOVE480_STORM_THROW && MoveParam->MoveID != MOVE524_FROST_BREATH && MoveParam->MoveID != MOVE006_PAY_DAY && MoveParam->MoveID != MOVE190_OCTAZOOKA && MoveParam->MoveID != MOVE346_WICKED_BLOW && MoveParam->MoveID != MOVE163_SLASH && MoveParam->MoveID != MOVE440_CROSS_POISON)
                {
                    fxDamage = fxDamage * 3;
                    fxDamage = fxDamage >> 2;
                }
                else
                {
                    fxDamage *= 2;
                }
            }

            if (!MainModule_GetDebugFlag() && ServerFlow_IsNotPokestarBattle(a1))
            {
                if (BattleDebugMode)
                {
                    damageRoll = 85;
                }
                else
                {
                    damageRoll = (100 - BattleRandom(16u));
                }

                fxDamage = damageRoll * fxDamage / 100;
            }

            moveType = (PokeType)MoveParam->moveType;
            if (moveType != TYPE_NULL)
            {

                int ratio;
                if (BattleMon_CheckIfMoveCondition(AttackingMon, CONDITION_TERA) || SEARCH_ARRAY(teraItems, AttackingMon->HeldItem)){
                    int teraType = PML_MoveGetType(Move_GetID(AttackingMon, 0));
                    int type1 = PML_PersonalGetParamSingle(AttackingMon->Species, AttackingMon->Form, Personal_Type1);
                    int type2 = PML_PersonalGetParamSingle(AttackingMon->Species, AttackingMon->Form, Personal_Type2);
                    if ((moveType == type1 && moveType == teraType) && (moveType == type2 && moveType == teraType)){
                        ratio = (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL091_ADAPTABILITY) ? 9216 : 8192;
                        fxDamage = fixed_round(fxDamage, ratio);
                    }
                    else if (moveType == teraType && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL091_ADAPTABILITY){
                        ratio = 8192;
                        fxDamage = fixed_round(fxDamage, ratio);
                    }
                    else if (moveType == type1 || moveType == type2 || moveType == teraType){
                        ratio = 6144;
                        fxDamage = fixed_round(fxDamage, ratio);
                    } else {
                        ratio = 4096;
                    }
                } 
                else if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL145_SAVANT)
                {
                    if (ServerEvent_SameTypeAttackBonus(a1, AttackingMon, moveType) == 4096)
                    {
                        ratio = 6144;
                        fxDamage = fixed_round(fxDamage, ratio);
                    }
                    else
                    {
                        ratio = ServerEvent_SameTypeAttackBonus(a1, AttackingMon, moveType);
                        fxDamage = fixed_round(fxDamage, ratio);
                    }
                    k::Printf("\nThe savant ratio is %d\n", ratio);
                }
                else
                {
                    v22 = ServerEvent_SameTypeAttackBonus(a1, AttackingMon, moveType);
                    fxDamage = fixed_round(fxDamage, v22);
                }
            }

            v23 = TypeEffectivenessPowerMod(fxDamage, TypeEffectiveness);

            if (Category == 1 && BattleMon_GetStatus(AttackingMon) == CONDITION_BURN && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL062_GUTS)
            {

                v23 = 50 * v23 / 100u;
            }

            // Check for Overheat and Sheer Cold
            if (Category == 2 && (BattleMon_GetPreviousMove(AttackingMon) == MOVE329_SHEER_COLD || BattleMon_GetPreviousMove(AttackingMon) == MOVE437_LEAF_STORM || BattleMon_GetPreviousMove(AttackingMon) == MOVE315_OVERHEAT || BattleMon_GetPreviousMove(AttackingMon) == MOVE434_DRACO_METEOR) && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                v23 = 50 * v23 / 100u;
                // k::Printf("\nBecause of Overheat, the new power of this move is %d\n\n", v23);
            }

            if (!v23)
            {
                v23 = 1;
            }

            BattleEventVar_SetMulValue(VAR_RATIO, 4096, 41, 0x20000);
            BattleEventVar_SetValue(VAR_DAMAGE, v23);
            BattleEvent_CallHandlers(a1, EVENT_MOVE_DAMAGE_PROCESSING_2);

            v24 = BattleEventVar_GetValue(VAR_RATIO);
            v25 = BattleEventVar_GetValue(VAR_DAMAGE);

            LOWORD(Value) = fixed_round(v25, v24);
        }

        BattleEvent_CallHandlers(a1, EVENT_MOVE_DAMAGE_PROCESSING_END);
        BattleEventVar_Pop();
        
        if (MoveParam->MoveID == MOVE247_SHADOW_BALL ){
            k::Printf("\nShadow Ball's damage is %d\n", Value);
        }
        *destDamage = Value;
        return v29;
    }

#pragma endregion

#pragma region InterruptSwitches

    int THUMB_BRANCH_ServerEvent_InterruptSwitch(ServerFlow *a1, BattleMon *a2)
    {
        unsigned int v3;      // r4
        unsigned int v4;      // r7
        BattleMon *BattleMon; // r0
        int v6;               // r6
        int Value;            // r0
        unsigned int v8;      // r4
        int ID;               // r0
        int moveID;
        // ServerFlow *v10;                  // r6
        int v11; // r1
        // ServerFlow *v14;                  // [sp+4h] [bp-44h]
        ActionOrderWork *ActionOrderWork; // [sp+8h] [bp-40h]
        char *p_actionOrderIndex;         // [sp+20h] [bp-28h]

        v3 = 0;
        if (a1->actionOrderIndex)
        {
            ActionOrderWork = a1->actionOrderWork;
            p_actionOrderIndex = &a1->actionOrderIndex;
            do
            {
                v4 = v3;
                BattleMon = a1->actionOrderWork[v4].BattleMon;

                // k::Printf("\nThis is a quick test to see if we are successfully catching a Battlemon\nv3 is %d, v4 is %d\nThis battlemon's id is %d, its species is %d, and its attack stat is %d\n",
                //          v3, v4, BattleMon_GetID(BattleMon), BattleMon->Species, BattleMon->Attack);

                if (BattleMon != a2 && !a1->actionOrderWork[v4].fDone)
                {
                    v6 = (((u32)ActionOrderWork[v4].Action) & 0xF) == 1 ? (((u32)ActionOrderWork[v4].Action) >> 7) : 0;

                    if (v6 == MOVE228_PURSUIT)
                    {
                        moveID = v6;
                        Value = BattleMon_GetValue(BattleMon, VALUE_SPEED_STAT);
                        if (MoveEvent_AddItem(a1->actionOrderWork[v4].BattleMon, moveID, Value))
                        {
                            a1->actionOrderWork[v4].InterruptActive = 1;
                        }
                    }
                    else if (v6 == MOVE467_SHADOW_FORCE || v6 == MOVE291_DIVE || v6 == MOVE019_FLY || v6 == MOVE091_DIG || v6 == MOVE340_BOUNCE)
                    {

                        if ((BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_SHADOW_FORCE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_DIG) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_DIVE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v4].BattleMon, CONDITIONFLAG_FLY)) ||
                            a1->actionOrderWork[v8].BattleMon->HeldItem == 271)
                        {
                            moveID = v6;
                            Value = BattleMon_GetValue(BattleMon, VALUE_SPEED_STAT);

                            if (MoveEvent_AddItem(a1->actionOrderWork[v4].BattleMon, moveID, Value))
                            {
                                a1->actionOrderWork[v4].InterruptActive = 1;
                            }
                        }
                    }
                }
                ++v3;
            } while (v3 < *p_actionOrderIndex);
        }
        v8 = 0;
        a1->SwitchOutInterruptingMonCount = 0;
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_TARGET_MON_ID, ID);
        BattleEvent_CallHandlers(a1, EVENT_SWITCH_OUT_INTERRUPT);
        BattleEventVar_Pop();
        if (a1->actionOrderIndex)
        {
            do
            {

                if (a1->actionOrderWork[v8].InterruptActive)
                {
                    if ((((u32)a1->actionOrderWork[v8].Action) & 0xF) == 1)
                    {
                        v11 = (((u32)a1->actionOrderWork[v8].Action) >> 7);
                    }
                    else
                    {
                        v11 = 0;
                    }

                    if (v11 == MOVE228_PURSUIT)
                    {
                        MoveEvent_ForceRemoveItemFromBattleMon(a1->actionOrderWork[v8].BattleMon, v11);
                    }

                    else if (v11 == MOVE467_SHADOW_FORCE || v11 == MOVE291_DIVE || v11 == MOVE019_FLY || v11 == MOVE091_DIG || v11 == MOVE340_BOUNCE)
                    {

                        if ((BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_SHADOW_FORCE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_DIG) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_DIVE) ||
                             BattleMon_GetConditionFlag(a1->actionOrderWork[v8].BattleMon, CONDITIONFLAG_FLY)) ||
                            a1->actionOrderWork[v8].BattleMon->HeldItem == 271)
                        {

                            MoveEvent_ForceRemoveItemFromBattleMon(a1->actionOrderWork[v8].BattleMon, v11);
                        }
                    }
                    a1->actionOrderWork[v8].InterruptActive = 0;
                }
                ++v8;
            } while (v8 < a1->actionOrderIndex);
        }
        return a1->SwitchOutInterruptingMonCount;
    }

#pragma endregion

#pragma region ExpandedTrainerPokemon

    extern u32 PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra);
    extern void PokeParty_SetParam(PartyPkm *pPkm, PkmField field, u32 data);
    extern void PokeParty_SetHiddenAbil(PartyPkm *pPkm, u16 species, u16 forme);
    extern u32 PML_PersonalGetParamSingle(u16 species, u16 form, PersonalField field);
    extern void PokeParty_SetNature(PartyPkm *pkm, u8 nature);
    extern unsigned int RandomInRange(unsigned int a1, unsigned int a2);

    u32 GetPPSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16435);
        return *lvl_cap_ptr;
    }

    struct FourthAbility
    {
        bool whiteListed;
        AbilID abilID4;
        AbilID abilID5;
        AbilID abilID6;
    };
    const FourthAbility WhiteListedPokemon[651]{
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH}, // PK_NULL = 0x0,

        // KANTO
        {1, ABIL070_DROUGHT, ABIL034_CHLOROPHYLL, ABIL122_FLOWER_GIFT},        // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},1_BULBASAUR = 0x1,
        {1, ABIL070_DROUGHT, ABIL034_CHLOROPHYLL, ABIL122_FLOWER_GIFT},        // PK002_IVYSAUR = 0x2,
        {1, ABIL070_DROUGHT, ABIL034_CHLOROPHYLL, ABIL122_FLOWER_GIFT},        // PK003_VENUSAUR = 0x3,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK004_CHARMANDER = 0x4,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK005_CHARMELEON = 0x5,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK006_CHARIZARD = 0x6,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL016_BALLISTICS},          // PK007_SQUIRTLE = 0x7,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL016_BALLISTICS},          // PK008_WARTORTLE = 0x8,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL016_BALLISTICS},          // PK009_BLASTOISE = 0x9,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK010_CATERPIE = 0xA,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK011_METAPOD = 0xB,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK012_BUTTERFREE = 0xC,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK013_WEEDLE = 0xD,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK014_KAKUNA = 0xE,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK015_BEEDRILL = 0xF,
        {0, ABIL_NULL, ABIL_NULL, ABIL_NULL},                                  // {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},016_PIDGEY = 0x10,
        {0, ABIL_NULL, ABIL_NULL, ABIL_NULL},                                  // PK017_PIDGEOTTO = 0x1{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL_NULL, ABIL_NULL, ABIL_NULL},                                  // PK018_PIDGEOT = 0x12,
        {0, ABIL_NULL, ABIL_NULL, ABIL_NULL},                                  // PK019_RATTATA = 0x13,
        {0, ABIL_NULL, ABIL_NULL, ABIL_NULL},                                  // PK020_RATICATE = 0x14,
        {1, ABIL097_SNIPER, ABIL097_SNIPER, ABIL097_SNIPER},                   // PK021_SPEAROW = 0x15,
        {1, ABIL097_SNIPER, ABIL097_SNIPER, ABIL097_SNIPER},                   // PK022_FEAROW = 0x16,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL001_STENCH},             // PK023_EKANS = 0x17,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL001_STENCH},             // PK024_ARBOK = 0x18,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK025_PIKACHU = 0x19,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK026_RAICHU = 0x1A,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK027_SANDSHREW = 0x1B,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK028_SANDSLASH = 0x1C,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK029_NIDORAN = 0x1D,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK030_NIDORINA = 0x1E,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK031_NIDOQUEEN = 0x1F,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK032_NIDORAN = 0x2{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},3_NIDORINO = 0x21,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK034_NIDOKING = 0x22,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK035_CLEFAIRY = 0x23,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK036_CLEFABLE = 0x24,
        {1, ABIL070_DROUGHT, ABIL149_ILLUSION, ABIL149_ILLUSION},              // PK037_VULPIX = 0x25,
        {1, ABIL070_DROUGHT, ABIL149_ILLUSION, ABIL149_ILLUSION},              // PK038_NINETALES = 0x26,
        {1, ABIL141_MOODY, ABIL017_FLUFFY, ABIL017_FLUFFY},                    // PK039_JIGGLYPUFF = 0x27,
        {1, ABIL141_MOODY, ABIL017_FLUFFY, ABIL017_FLUFFY},                    // PK040_WIGGLYTUFF = 0x28,
        {1, ABIL023_SHADOW_TAG, ABIL097_SNIPER, ABIL107_ANTICIPATION},         // PK041_ZUBAT = 0x29,
        {1, ABIL023_SHADOW_TAG, ABIL097_SNIPER, ABIL107_ANTICIPATION},         // PK042_GOLBAT = 0x2A,
        {1, ABIL001_STENCH, ABIL027_EFFECT_SPORE, ABIL070_DROUGHT},            // PK043_ODDISH = 0x2B,
        {1, ABIL001_STENCH, ABIL027_EFFECT_SPORE, ABIL070_DROUGHT},            // PK044_GLOOM = 0x2C,
        {1, ABIL001_STENCH, ABIL027_EFFECT_SPORE, ABIL070_DROUGHT},            // PK045_VILEPLUME = 0x2D,
        {1, ABIL027_EFFECT_SPORE, ABIL119_STAKEOUT, ABIL023_SHADOW_TAG},       // PK046_PARAS = 0x2E,
        {1, ABIL027_EFFECT_SPORE, ABIL119_STAKEOUT, ABIL023_SHADOW_TAG},       // PK047_PARASECT = 0x2F,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK048_VENONAT = 0x3{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},9_VENOMOTH = 0x31,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL008_SAND_VEIL},          // PK050_DIGLETT = 0x32,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL008_SAND_VEIL},          // PK051_DUGTRIO = 0x33,
        {1, ABIL124_PICKPOCKET, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},   // PK052_MEOWTH = 0x34,
        {1, ABIL124_PICKPOCKET, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},   // PK053_PERSIAN = 0x35,
        {1, ABIL002_DRIZZLE, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},      // PK054_PSYDUCK = 0x36,
        {1, ABIL002_DRIZZLE, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},      // PK055_GOLDUCK = 0x37,
        {1, ABIL055_HUSTLE, ABIL055_HUSTLE, ABIL055_HUSTLE},                   // PK056_MANKEY = 0x38,
        {1, ABIL055_HUSTLE, ABIL055_HUSTLE, ABIL055_HUSTLE},                   // PK057_PRIMEAPE = 0x39,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK058_GROWLITHE = 0x3A,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK059_ARCANINE = 0x3B,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK060_POLIWAG = 0x3C,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK061_POLIWHIRL = 0x3D,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK062_POLIWRATH = 0x3E,
        {1, ABIL107_ANTICIPATION, ABIL149_ILLUSION, ABIL149_ILLUSION},         // PK063_ABRA = 0x3F,
        {1, ABIL107_ANTICIPATION, ABIL149_ILLUSION, ABIL149_ILLUSION},         // PK064_KADABRA = 0x4{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL107_ANTICIPATION, ABIL149_ILLUSION, ABIL149_ILLUSION},         // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},5_ALAKAZAM = 0x41,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK066_MACHOP = 0x42,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK067_MACHOKE = 0x43,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK068_MACHAMP = 0x44,
        {1, ABIL001_STENCH, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP},             // PK069_BELLSPROUT = 0x45,
        {1, ABIL001_STENCH, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP},             // PK070_WEEPINBELL = 0x46,
        {1, ABIL001_STENCH, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP},             // PK071_VICTREEBEL = 0x47,
        {1, ABIL002_DRIZZLE, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP},            // PK072_TENTACOOL = 0x48,
        {1, ABIL002_DRIZZLE, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP},            // PK073_TENTACRUEL = 0x49,
        {1, ABIL106_AFTERMATH, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},        // PK074_GEODUDE = 0x4A,
        {1, ABIL106_AFTERMATH, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},        // PK075_GRAVELER = 0x4B,
        {1, ABIL106_AFTERMATH, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},        // PK076_GOLEM = 0x4C,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK077_PONYTA = 0x4D,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK078_RAPIDASH = 0x4E,
        {1, ABIL002_DRIZZLE, ABIL086_SIMPLE, ABIL086_SIMPLE},                  // PK079_SLOWPOKE = 0x4F,
        {1, ABIL002_DRIZZLE, ABIL086_SIMPLE, ABIL086_SIMPLE},                  // PK080_SLOWBRO = 0x50,
        {1, ABIL058_MINUS, ABIL057_PLUS, ABIL057_PLUS},                        // PK0{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_MAGNEMITE = 0x51,
        {1, ABIL058_MINUS, ABIL057_PLUS, ABIL057_PLUS},                        // PK082_MAGNETON = 0x52,
        {1, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},       // PK083_FARFETCH_D = 0x53,
        {1, ABIL045_SAND_STREAM, ABIL141_MOODY, ABIL008_SAND_VEIL},            // PK084_DODUO = 0x54,
        {1, ABIL045_SAND_STREAM, ABIL141_MOODY, ABIL008_SAND_VEIL},            // PK085_DODRIO = 0x55,
        {1, ABIL033_SWIFT_SWIM, ABIL031_LIGHTNING_ROD, ABIL081_SNOW_CLOAK},    // PK086_SEEL = 0x56,
        {1, ABIL033_SWIFT_SWIM, ABIL031_LIGHTNING_ROD, ABIL081_SNOW_CLOAK},    // PK087_DEWGONG = 0x57,
        {1, ABIL001_STENCH, ABIL143_POISON_TOUCH, ABIL143_POISON_TOUCH},       // PK088_GRIMER = 0x58,
        {1, ABIL001_STENCH, ABIL143_POISON_TOUCH, ABIL143_POISON_TOUCH},       // PK089_MUK = 0x59,
        {1, ABIL020_QUICK_DRAW, ABIL106_AFTERMATH, ABIL117_SNOW_WARNING},      // PK090_SHELLDER = 0x5A,
        {1, ABIL020_QUICK_DRAW, ABIL106_AFTERMATH, ABIL117_SNOW_WARNING},      // PK091_CLOYSTER = 0x5B,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL001_STENCH},             // PK092_GASTLY = 0x5C,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL001_STENCH},             // PK093_HAUNTER = 0x5D,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL001_STENCH},             // PK094_GENGAR = 0x5E,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL008_SAND_VEIL},        // PK095_ONIX = 0x5F,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL149_ILLUSION},           // PK096_DROWZEE = 0x6{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL149_ILLUSION},           //{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},K097_HYPNO = 0x61,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK098_KRABBY = 0x62,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK099_KINGLER = 0x63,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL106_AFTERMATH},                   // PK100_VOLTORB = 0x64,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL106_AFTERMATH},                   // PK101_ELECTRODE = 0x65,
        {1, ABIL141_MOODY, ABIL106_AFTERMATH, ABIL142_OVERCOAT},               // PK102_EXEGGCUTE = 0x66,
        {1, ABIL141_MOODY, ABIL106_AFTERMATH, ABIL142_OVERCOAT},               // PK103_EXEGGUTOR = 0x67,
        {1, ABIL020_QUICK_DRAW, ABIL045_SAND_STREAM, ABIL142_OVERCOAT},        // PK104_CUBONE = 0x68,
        {1, ABIL020_QUICK_DRAW, ABIL045_SAND_STREAM, ABIL142_OVERCOAT},        // PK105_MAROWAK = 0x69,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK106_HITMONLEE = 0x6A,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK107_HITMONCHAN = 0x6B,
        {1, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK108_LICKITUNG = 0x6C,
        {1, ABIL106_AFTERMATH, ABIL020_QUICK_DRAW, ABIL001_STENCH},            // PK109_KOFFING = 0x6D,
        {1, ABIL106_AFTERMATH, ABIL020_QUICK_DRAW, ABIL001_STENCH},            // PK110_WEEZING = 0x6E,
        {1, ABIL045_SAND_STREAM, ABIL038_BERSERK, ABIL038_BERSERK},            // PK111_RHYHORN = 0x6F,
        {1, ABIL045_SAND_STREAM, ABIL038_BERSERK, ABIL038_BERSERK},            // PK112_RHYDON = 0x7{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL037_HUGE_POWER, ABIL037_HUGE_POWER, ABIL037_HUGE_POWER},       // PK113_CHANSEY = 0x7{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL034_CHLOROPHYLL, ABIL034_CHLOROPHYLL, ABIL034_CHLOROPHYLL},    // PK114_TANGELA = 0x72,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK115_KANGASKHAN = 0x73,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},          // PK116_HORSEA = 0x74,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},          // PK117_SEADRA = 0x75,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK118_GOLDEEN = 0x76,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK119_SEAKING = 0x77,
        {1, ABIL002_DRIZZLE, ABIL149_ILLUSION, ABIL033_SWIFT_SWIM},            // PK120_STARYU = 0x78,
        {1, ABIL002_DRIZZLE, ABIL149_ILLUSION, ABIL033_SWIFT_SWIM},            // PK121_STARMIE = 0x79,
        {1, ABIL107_ANTICIPATION, ABIL141_MOODY, ABIL149_ILLUSION},            // PK122_MR_MIME = 0x7A,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK123_SCYTHER = 0x7B,
        {1, ABIL117_SNOW_WARNING, ABIL149_ILLUSION, ABIL081_SNOW_CLOAK},       // PK124_JYNX = 0x7C,
        {1, ABIL058_MINUS, ABIL083_ANGER_POINT, ABIL057_PLUS},                 // PK125_ELECTABUZZ = 0x7D,
        {1, ABIL020_QUICK_DRAW, ABIL070_DROUGHT, ABIL106_AFTERMATH},           // PK126_MAGMAR = 0x7E,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK127_PINSIR = 0x7F,
        {1, ABIL141_MOODY, ABIL038_BERSERK, ABIL038_BERSERK},                  // PK128_TAUROS = 0x8{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL141_MOODY, ABIL002_DRIZZLE, ABIL033_SWIFT_SWIM},               // PK129_MAGIKARP = 0x8{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL141_MOODY, ABIL002_DRIZZLE, ABIL033_SWIFT_SWIM},               // PK130_GYARADOS = 0x82,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL111_FILTER},         // PK131_LAPRAS = 0x83,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK132_DITTO = 0x84,
        {1, ABIL107_ANTICIPATION, ABIL141_MOODY, ABIL141_MOODY},               // PK133_EEVEE = 0x85,
        {1, ABIL107_ANTICIPATION, ABIL002_DRIZZLE, ABIL002_DRIZZLE},           // PK134_VAPOREON = 0x86,
        {1, ABIL107_ANTICIPATION, ABIL057_PLUS, ABIL058_MINUS},                // PK135_JOLTEON = 0x87,
        {1, ABIL107_ANTICIPATION, ABIL070_DROUGHT, ABIL070_DROUGHT},           // PK136_FLAREON = 0x88,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK137_PORYGON = 0x89,
        {1, ABIL033_SWIFT_SWIM, ABIL005_STURDY, ABIL005_STURDY},               // PK138_OMANYTE = 0x8A,
        {1, ABIL033_SWIFT_SWIM, ABIL005_STURDY, ABIL005_STURDY},               // PK139_OMASTAR = 0x8B,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK140_KABUTO = 0x8C,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK141_KABUTOPS = 0x8D,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK142_AERODACTYL = 0x8E,
        {1, ABIL096_NORMALIZE, ABIL096_NORMALIZE, ABIL096_NORMALIZE},          // PK143_SNORLAX = 0x8F,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL081_SNOW_CLOAK},     // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},4_ARTICUNO = 0x90,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK145_ZAPDOS = 0x9{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK146_MOLTRES = 0x92,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK147_DRATINI = 0x93,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK148_DRAGONAIR = 0x94,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK149_DRAGONITE = 0x95,
        {1, ABIL104_MOLD_BREAKER, ABIL127_UNNERVE, ABIL076_AIR_LOCK},  // PK150_MEWTWO = 0x96,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK151_MEW = 0x97,

        // JOHTO
        {1, ABIL122_FLOWER_GIFT, ABIL122_FLOWER_GIFT, ABIL122_FLOWER_GIFT}, // PK152_CHIKORITA = 0x98,
        {1, ABIL122_FLOWER_GIFT, ABIL122_FLOWER_GIFT, ABIL122_FLOWER_GIFT}, // PK153_BAYLEEF = 0x99,
        {1, ABIL122_FLOWER_GIFT, ABIL122_FLOWER_GIFT, ABIL122_FLOWER_GIFT}, // PK154_MEGANIUM = 0x9A,
        {1, ABIL070_DROUGHT, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},       // PK155_CYNDAQUIL = 0x9B,
        {1, ABIL070_DROUGHT, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},       // PK156_QUILAVA = 0x9C,
        {1, ABIL070_DROUGHT, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},       // PK157_TYPHLOSION = 0x9D,
        {1, ABIL002_DRIZZLE, ABIL119_STAKEOUT, ABIL119_STAKEOUT},           // PK158_TOTODILE = 0x9E,
        {1, ABIL002_DRIZZLE, ABIL119_STAKEOUT, ABIL119_STAKEOUT},           // PK159_CROCONAW = 0x9F,
        {1, ABIL002_DRIZZLE, ABIL119_STAKEOUT, ABIL119_STAKEOUT},           // PK16{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},FERALIGATR = 0xA0,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},          // PK161_SENTRET = 0xA{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},          // PK162_FURRET = 0xA2,
        {1, ABIL119_STAKEOUT, ABIL149_ILLUSION, ABIL023_SHADOW_TAG},        // PK163_HOOTHOOT = 0xA3,
        {1, ABIL119_STAKEOUT, ABIL149_ILLUSION, ABIL023_SHADOW_TAG},        // PK164_NOCTOWL = 0xA4,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK165_LEDYBA = 0xA5,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK166_LEDIAN = 0xA6,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL071_ARENA_TRAP},      // PK167_SPINARAK = 0xA7,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL071_ARENA_TRAP},      // PK168_ARIADOS = 0xA8,
        {1, ABIL023_SHADOW_TAG, ABIL097_SNIPER, ABIL107_ANTICIPATION},      // PK169_CROBAT = 0xA9,
        {1, ABIL002_DRIZZLE, ABIL058_MINUS, ABIL057_PLUS},                  // PK170_CHINCHOU = 0xAA,
        {1, ABIL002_DRIZZLE, ABIL058_MINUS, ABIL057_PLUS},                  // PK171_LANTURN = 0xAB,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                    // PK172_PICHU = 0xAC,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK173_CLEFFA = 0xAD,
        {1, ABIL141_MOODY, ABIL017_FLUFFY, ABIL017_FLUFFY},                 // PK174_IGGLYBUFF = 0xAE,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK175_TOGEPI = 0xAF,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK176_TOGETIC = 0xB{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL149_ILLUSION, ABIL149_ILLUSION, ABIL149_ILLUSION},          //{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},PK177_NATU = 0xB1,
        {1, ABIL149_ILLUSION, ABIL149_ILLUSION, ABIL149_ILLUSION},          // PK178_XATU = 0xB2,
        {1, ABIL057_PLUS, ABIL017_FLUFFY, ABIL058_MINUS},                   // PK179_MAREEP = 0xB3,
        {1, ABIL057_PLUS, ABIL017_FLUFFY, ABIL058_MINUS},                   // PK180_FLAAFFY = 0xB4,
        {1, ABIL057_PLUS, ABIL017_FLUFFY, ABIL058_MINUS},                   // PK181_AMPHAROS = 0xB5,
        {1, ABIL027_EFFECT_SPORE, ABIL070_DROUGHT, ABIL122_FLOWER_GIFT},    // PK182_BELLOSSOM = 0xB6,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK183_MARILL = 0xB7,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK184_AZUMARILL = 0xB8,
        {1, ABIL045_SAND_STREAM, ABIL119_STAKEOUT, ABIL119_STAKEOUT},       // PK185_SUDOWOODO = 0xB9,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},             // PK186_POLITOED = 0xBA,
        {1, ABIL070_DROUGHT, ABIL086_SIMPLE, ABIL086_SIMPLE},               // PK187_HOPPIP = 0xBB,
        {1, ABIL070_DROUGHT, ABIL086_SIMPLE, ABIL086_SIMPLE},               // PK188_SKIPLOOM = 0xBC,
        {1, ABIL070_DROUGHT, ABIL086_SIMPLE, ABIL086_SIMPLE},               // PK189_JUMPLUFF = 0xBD,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK190_AIPOM = 0xBE,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},             // PK191_SUNKERN = 0xBF,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},             // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},2_SUNFLORA = 0xC0,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                //{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},K193_YANMA = 0xC1,
        {1, ABIL002_DRIZZLE, ABIL086_SIMPLE, ABIL086_SIMPLE},               // PK194_WOOPER = 0xC2,
        {1, ABIL002_DRIZZLE, ABIL086_SIMPLE, ABIL086_SIMPLE},               // PK195_QUAGSIRE = 0xC3,
        {1, ABIL107_ANTICIPATION, ABIL149_ILLUSION, ABIL039_INNER_FOCUS},   // PK196_ESPEON = 0xC4,
        {1, ABIL107_ANTICIPATION, ABIL119_STAKEOUT, ABIL149_ILLUSION},      // PK197_UMBREON = 0xC5,
        {1, ABIL119_STAKEOUT, ABIL153_MOXIE, ABIL153_MOXIE},                // PK198_MURKROW = 0xC6,
        {1, ABIL002_DRIZZLE, ABIL086_SIMPLE, ABIL086_SIMPLE},               // PK199_SLOWKING = 0xC7,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},      // PK200_MISDREAVUS = 0xC8,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},      // PK201_UNOWN = 0xC9,
        {1, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},    // PK202_WOBBUFFET = 0xCA,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                   // PK203_GIRAFARIG = 0xCB,
        {1, ABIL106_AFTERMATH, ABIL020_QUICK_DRAW, ABIL016_BALLISTICS},     // PK204_PINECO = 0xCC,
        {1, ABIL106_AFTERMATH, ABIL020_QUICK_DRAW, ABIL016_BALLISTICS},     // PK205_FORRETRESS = 0xCD,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},     // PK206_DUNSPARCE = 0xCE,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},     // PK207_GLIGAR = 0xCF,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL008_SAND_VEIL},     // PK208_STEELIX = 0xD{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL062_GUTS, ABIL141_MOODY, ABIL083_ANGER_POINT},              // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},9_SNUBBULL = 0xD1,
        {1, ABIL062_GUTS, ABIL141_MOODY, ABIL083_ANGER_POINT},              // PK210_GRANBULL = 0xD2,
        {1, ABIL002_DRIZZLE, ABIL106_AFTERMATH, ABIL020_QUICK_DRAW},        // PK211_QWILFISH = 0xD3,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK212_SCIZOR = 0xD4,
        {1, ABIL045_SAND_STREAM, ABIL141_MOODY, ABIL141_MOODY},             // PK213_SHUCKLE = 0xD5,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK214_HERACROSS = 0xD6,
        {1, ABIL088_EXPLOIT, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},     // PK215_SNEASEL = 0xD7,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM}, // PK216_TEDDIURSA = 0xD8,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM}, // PK217_URSARING = 0xD9,
        {1, ABIL106_AFTERMATH, ABIL087_DRY_SKIN, ABIL070_DROUGHT},          // PK218_SLUGMA = 0xDA,
        {1, ABIL106_AFTERMATH, ABIL087_DRY_SKIN, ABIL070_DROUGHT},          // PK219_MAGCARGO = 0xDB,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL083_ANGER_POINT}, // PK220_SWINUB = 0xDC,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL083_ANGER_POINT}, // PK221_PILOSWINE = 0xDD,
        {1, ABIL045_SAND_STREAM, ABIL087_DRY_SKIN, ABIL055_HUSTLE},         // PK222_CORSOLA = 0xDE,
        {1, ABIL119_STAKEOUT, ABIL020_QUICK_DRAW, ABIL141_MOODY},           // PK223_REMORAID = 0xDF,
        {1, ABIL119_STAKEOUT, ABIL020_QUICK_DRAW, ABIL141_MOODY},           // PK2{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_OCTILLERY = 0xE0,
        {1, ABIL117_SNOW_WARNING, ABIL141_MOODY, ABIL081_SNOW_CLOAK},       // PK225_DELIBIRD = 0xE{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL002_DRIZZLE, ABIL001_STENCH, ABIL001_STENCH},               // PK226_MANTINE = 0xE2,
        {1, ABIL015_THUNDER_ARMOR, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},   // PK227_SKARMORY = 0xE3,
        {1, ABIL070_DROUGHT, ABIL022_INTIMIDATE, ABIL094_SOLAR_POWER},      // PK228_HOUNDOUR = 0xE4,
        {1, ABIL070_DROUGHT, ABIL022_INTIMIDATE, ABIL094_SOLAR_POWER},      // PK229_HOUNDOOM = 0xE5,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},       // PK230_KINGDRA = 0xE6,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},     // PK231_PHANPY = 0xE7,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},     // PK232_DONPHAN = 0xE8,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK233_PORYGON2 = 0xE9,
        {1, ABIL022_INTIMIDATE, ABIL149_ILLUSION, ABIL023_SHADOW_TAG},      // PK234_STANTLER = 0xEA,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                   // PK235_SMEARGLE = 0xEB,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK236_TYROGUE = 0xEC,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK237_HITMONTOP = 0xED,
        {1, ABIL117_SNOW_WARNING, ABIL149_ILLUSION, ABIL081_SNOW_CLOAK},    // PK238_SMOOCHUM = 0xEE,
        {1, ABIL058_MINUS, ABIL083_ANGER_POINT, ABIL057_PLUS},              // PK239_ELEKID = 0xEF,
        {1, ABIL020_QUICK_DRAW, ABIL070_DROUGHT, ABIL106_AFTERMATH},        //{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},K240_MAGBY = 0xF0,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // P{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},41_MILTANK = 0xF1,
        {1, ABIL037_HUGE_POWER, ABIL037_HUGE_POWER, ABIL037_HUGE_POWER},    // PK242_BLISSEY = 0xF2,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK243_RAIKOU = 0xF3,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK244_ENTEI = 0xF4,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK245_SUICUNE = 0xF5,
        {1, ABIL045_SAND_STREAM, ABIL116_SOLID_ROCK, ABIL116_SOLID_ROCK},   // PK246_LARVITAR = 0xF6,
        {1, ABIL045_SAND_STREAM, ABIL116_SOLID_ROCK, ABIL116_SOLID_ROCK},   // PK247_PUPITAR = 0xF7,
        {1, ABIL045_SAND_STREAM, ABIL116_SOLID_ROCK, ABIL116_SOLID_ROCK},   // PK248_TYRANITAR = 0xF8,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK249_LUGIA = 0xF9,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK250_HO_OH = 0xFA,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                // PK251_CELEBI = 0xFB,

        // HOENN
        {1, ABIL107_ANTICIPATION, ABIL097_SNIPER, ABIL097_SNIPER},             // PK252_TREECKO = 0xFC,
        {1, ABIL107_ANTICIPATION, ABIL097_SNIPER, ABIL097_SNIPER},             // PK253_GROVYLE = 0xFD,
        {1, ABIL107_ANTICIPATION, ABIL097_SNIPER, ABIL097_SNIPER},             // PK254_SCEPTILE = 0xFE,
        {1, ABIL003_SPEED_BOOST, ABIL070_DROUGHT, ABIL055_HUSTLE},             // PK255_TORCHIC = 0xFF,
        {1, ABIL003_SPEED_BOOST, ABIL070_DROUGHT, ABIL055_HUSTLE},             // PK25{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},COMBUSKEN = 0x100,
        {1, ABIL003_SPEED_BOOST, ABIL070_DROUGHT, ABIL055_HUSTLE},             // PK257_BLAZIKEN = 0x10{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL107_ANTICIPATION},       // PK258_MUDKIP = 0x102,
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL107_ANTICIPATION},       // PK259_MARSHTOMP = 0x103,
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL107_ANTICIPATION},       // PK260_SWAMPERT = 0x104,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},             // PK261_POOCHYENA = 0x105,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},             // PK262_MIGHTYENA = 0x106,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK263_ZIGZAGOON = 0x107,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK264_LINOONE = 0x108,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK265_WURMPLE = 0x109,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK266_SILCOON = 0x10A,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK267_BEAUTIFLY = 0x10B,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK268_CASCOON = 0x10C,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK269_DUSTOX = 0x10D,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK270_LOTAD = 0x10E,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK271_LOMBRE = 0x10F,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK2{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_LUDICOLO = 0x110,
        {1, ABIL070_DROUGHT, ABIL106_AFTERMATH, ABIL107_ANTICIPATION},         // P{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},73_SEEDOT = 0x111,
        {1, ABIL070_DROUGHT, ABIL106_AFTERMATH, ABIL107_ANTICIPATION},         // PK274_NUZLEAF = 0x112,
        {1, ABIL070_DROUGHT, ABIL106_AFTERMATH, ABIL107_ANTICIPATION},         // PK275_SHIFTRY = 0x113,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK276_TAILLOW = 0x114,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK277_SWELLOW = 0x115,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK278_WINGULL = 0x116,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK279_PELIPPER = 0x117,
        {1, ABIL149_ILLUSION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},     // PK280_RALTS = 0x118,
        {1, ABIL149_ILLUSION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},     // PK281_KIRLIA = 0x119,
        {1, ABIL149_ILLUSION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},     // PK282_GARDEVOIR = 0x11A,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK283_SURSKIT = 0x11B,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK284_MASQUERAIN = 0x11C,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK285_SHROOMISH = 0x11D,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK286_BRELOOM = 0x11E,
        {1, ABIL062_GUTS, ABIL062_GUTS, ABIL062_GUTS},                         // PK287_SLAKOTH = 0x11F,
        {1, ABIL062_GUTS, ABIL062_GUTS, ABIL062_GUTS},                         // PK2{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_VIGOROTH = 0x120,
        {1, ABIL062_GUTS, ABIL062_GUTS, ABIL062_GUTS},                         // PK289_SLAKING = 0x12{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL119_STAKEOUT, ABIL097_SNIPER, ABIL097_SNIPER},                 // PK290_NINCADA = 0x122,
        {1, ABIL119_STAKEOUT, ABIL097_SNIPER, ABIL097_SNIPER},                 // PK291_NINJASK = 0x123,
        {1, ABIL119_STAKEOUT, ABIL097_SNIPER, ABIL025_WONDER_GUARD},           // PK292_SHEDINJA = 0x124,
        {1, ABIL141_MOODY, ABIL083_ANGER_POINT, ABIL083_ANGER_POINT},          // PK293_WHISMUR = 0x125,
        {1, ABIL141_MOODY, ABIL083_ANGER_POINT, ABIL083_ANGER_POINT},          // PK294_LOUDRED = 0x126,
        {1, ABIL141_MOODY, ABIL083_ANGER_POINT, ABIL083_ANGER_POINT},          // PK295_EXPLOUD = 0x127,
        {1, ABIL113_SCRAPPY, ABIL113_SCRAPPY, ABIL113_SCRAPPY},                // PK296_MAKUHITA = 0x128,
        {1, ABIL113_SCRAPPY, ABIL113_SCRAPPY, ABIL113_SCRAPPY},                // PK297_HARIYAMA = 0x129,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK298_AZURILL = 0x12A,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK299_NOSEPASS = 0x12B,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK300_SKITTY = 0x12C,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK301_DELCATTY = 0x12D,
        {1, ABIL119_STAKEOUT, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},         // PK302_SABLEYE = 0x12E,
        {1, ABIL037_HUGE_POWER, ABIL071_ARENA_TRAP, ABIL071_ARENA_TRAP},       // PK303_MAWILE = 0x12F,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},K304_ARON = 0x130,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK305_LAIRON = 0x13{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK306_AGGRON = 0x132,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK307_MEDITITE = 0x133,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK308_MEDICHAM = 0x134,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK309_ELECTRIKE = 0x135,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK310_MANECTRIC = 0x136,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK311_PLUSLE = 0x137,
        {1, ABIL058_MINUS, ABIL057_PLUS, ABIL057_PLUS},                        // PK312_MINUN = 0x138,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK313_VOLBEAT = 0x139,
        {1, ABIL058_MINUS, ABIL057_PLUS, ABIL057_PLUS},                        // PK314_ILLUMISE = 0x13A,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK315_ROSELIA = 0x13B,
        {1, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK316_GULPIN = 0x13C,
        {1, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK317_SWALOT = 0x13D,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                //  PK318_CARVANHA = 0x13E,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                //  PK319_SHARPEDO = 0x13F,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                //   PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},0_WAILMER = 0x140,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                //   PK321_WAILORD = 0x14{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL106_AFTERMATH, ABIL086_SIMPLE, ABIL070_DROUGHT},               //   PK322_NUMEL = 0x142,
        {1, ABIL106_AFTERMATH, ABIL086_SIMPLE, ABIL070_DROUGHT},               //   PK323_CAMERUPT = 0x143,
        {1, ABIL106_AFTERMATH, ABIL086_SIMPLE, ABIL070_DROUGHT},               //  PK324_TORKOAL = 0x144,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK325_SPOINK = 0x145,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK326_GRUMPIG = 0x146,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      //   PK327_SPINDA = 0x147,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL008_SAND_VEIL},        // PK328_TRAPINCH = 0x148,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL008_SAND_VEIL},        // PK329_VIBRAVA = 0x149,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL008_SAND_VEIL},        // PK330_FLYGON = 0x14A,
        {1, ABIL119_STAKEOUT, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},           //  PK331_CACNEA = 0x14B,
        {1, ABIL119_STAKEOUT, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},           //  PK332_CACTURNE = 0x14C,
        {1, ABIL017_FLUFFY, ABIL017_FLUFFY, ABIL017_FLUFFY},                   //   PK333_SWABLU = 0x14D,
        {1, ABIL017_FLUFFY, ABIL017_FLUFFY, ABIL017_FLUFFY},                   //   PK334_ALTARIA = 0x14E,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK335_ZANGOOSE = 0x14F,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},6_SEVIPER = 0x150,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    //  PK337_LUNATONE = 0x15{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                //   PK338_SOLROCK = 0x152,
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},        // PK339_BARBOACH = 0x153,
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},        // PK340_WHISCASH = 0x154,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK341_CORPHISH = 0x155,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK342_CRAWDAUNT = 0x156,
        {1, ABIL045_SAND_STREAM, ABIL003_SPEED_BOOST, ABIL071_ARENA_TRAP},     //  PK343_BALTOY = 0x157,
        {1, ABIL045_SAND_STREAM, ABIL003_SPEED_BOOST, ABIL071_ARENA_TRAP},     //   PK344_CLAYDOL = 0x158,
        {1, ABIL045_SAND_STREAM, ABIL119_STAKEOUT, ABIL008_SAND_VEIL},         // PK345_LILEEP = 0x159,
        {1, ABIL045_SAND_STREAM, ABIL119_STAKEOUT, ABIL008_SAND_VEIL},         // PK346_CRADILY = 0x15A,
        {1, ABIL033_SWIFT_SWIM, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},       // PK347_ANORITH = 0x15B,
        {1, ABIL033_SWIFT_SWIM, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL},       // PK348_ARMALDO = 0x15C,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK349_FEEBAS = 0x15D,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK350_MILOTIC = 0x15E,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK351_CASTFORM = 0x15F,
        {1, ABIL023_SHADOW_TAG, ABIL107_ANTICIPATION, ABIL149_ILLUSION},       //  PK352_KECLEON = 0x16{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL023_SHADOW_TAG, ABIL107_ANTICIPATION, ABIL149_ILLUSION},       //  PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},3_SHUPPET = 0x161,
        {1, ABIL023_SHADOW_TAG, ABIL107_ANTICIPATION, ABIL149_ILLUSION},       //   PK354_BANETTE = 0x162,
        {1, ABIL023_SHADOW_TAG, ABIL107_ANTICIPATION, ABIL149_ILLUSION},       //   PK355_DUSKULL = 0x163,
        {1, ABIL023_SHADOW_TAG, ABIL107_ANTICIPATION, ABIL149_ILLUSION},       //   PK356_DUSCLOPS = 0x164,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK357_TROPIUS = 0x165,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK358_CHIMECHO = 0x166,
        {1, ABIL107_ANTICIPATION, ABIL119_STAKEOUT, ABIL097_SNIPER},           // PK359_ABSOL = 0x167,
        {1, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},       //   PK360_WYNAUT = 0x168,
        {1, ABIL141_MOODY, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},          //   PK361_SNORUNT = 0x169,
        {1, ABIL141_MOODY, ABIL117_SNOW_WARNING, ABIL106_AFTERMATH},           //   PK362_GLALIE = 0x16A,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL102_FUR_COAT},       // PK363_SPHEAL = 0x16B,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL102_FUR_COAT},       // PK364_SEALEO = 0x16C,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL102_FUR_COAT},       // PK365_WALREIN = 0x16D,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK366_CLAMPERL = 0x16E,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK367_HUNTAIL = 0x16F,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK368_GOREBYSS = 0x17{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL045_SAND_STREAM, ABIL002_DRIZZLE, ABIL002_DRIZZLE},            // PK36{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},RELICANTH = 0x171,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK370_LUVDISC = 0x172,
        {1, ABIL153_MOXIE, ABIL060_AERILATE, ABIL060_AERILATE},                // PK371_BAGON = 0x173,
        {1, ABIL153_MOXIE, ABIL060_AERILATE, ABIL060_AERILATE},                // PK372_SHELGON = 0x174,
        {1, ABIL153_MOXIE, ABIL060_AERILATE, ABIL060_AERILATE},                // PK373_SALAMENCE = 0x175,
        {1, ABIL003_SPEED_BOOST, ABIL134_HEAVY_METAL, ABIL134_HEAVY_METAL},    //   PK374_BELDUM = 0x176,
        {1, ABIL003_SPEED_BOOST, ABIL134_HEAVY_METAL, ABIL134_HEAVY_METAL},    //   PK375_METANG = 0x177,
        {1, ABIL003_SPEED_BOOST, ABIL134_HEAVY_METAL, ABIL134_HEAVY_METAL},    //   PK376_METAGROSS = 0x178,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK377_REGIROCK = 0x179,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK378_REGICE = 0x17A,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK379_REGISTEEL = 0x17B,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK380_LATIAS = 0x17C,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK381_LATIOS = 0x17D,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK382_KYOGRE = 0x17E,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK383_GROUDON = 0x17F,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK3{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_RAYQUAZA = 0x180,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK385_JIRACHI = 0x18{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK386_DEOXYS = 0x182,

        // SINNOH
        {1, ABIL045_SAND_STREAM, ABIL047_THICK_FAT, ABIL047_THICK_FAT},        // PK387_TURTWIG = 0x183,
        {1, ABIL045_SAND_STREAM, ABIL047_THICK_FAT, ABIL047_THICK_FAT},        // PK388_GROTLE = 0x184,
        {1, ABIL045_SAND_STREAM, ABIL047_THICK_FAT, ABIL047_THICK_FAT},        // PK389_TORTERRA = 0x185,
        {1, ABIL070_DROUGHT, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},      //  PK390_CHIMCHAR = 0x186,
        {1, ABIL070_DROUGHT, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},      //  PK391_MONFERNO = 0x187,
        {1, ABIL070_DROUGHT, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},      //  PK392_INFERNAPE = 0x188,
        {1, ABIL031_LIGHTNING_ROD, ABIL002_DRIZZLE, ABIL081_SNOW_CLOAK},       //  PK393_PIPLUP = 0x189,
        {1, ABIL031_LIGHTNING_ROD, ABIL002_DRIZZLE, ABIL081_SNOW_CLOAK},       //  PK394_PRINPLUP = 0x18A,
        {1, ABIL031_LIGHTNING_ROD, ABIL002_DRIZZLE, ABIL081_SNOW_CLOAK},       //   PK395_EMPOLEON = 0x18B,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK396_STARLY = 0x18C,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK397_STARAVIA = 0x18D,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK398_STARAPTOR = 0x18E,
        {1, ABIL086_SIMPLE, ABIL086_SIMPLE, ABIL086_SIMPLE},                   //   PK399_BIDOOF = 0x18F,
        {1, ABIL086_SIMPLE, ABIL086_SIMPLE, ABIL086_SIMPLE},                   //  PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},0_BIBAREL = 0x190,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK401_KRICKETOT = 0x19{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK402_KRICKETUNE = 0x192,
        {1, ABIL119_STAKEOUT, ABIL057_PLUS, ABIL058_MINUS},                    // PK403_SHINX = 0x193,
        {1, ABIL119_STAKEOUT, ABIL057_PLUS, ABIL058_MINUS},                    // PK404_LUXIO = 0x194,
        {1, ABIL119_STAKEOUT, ABIL057_PLUS, ABIL058_MINUS},                    // PK405_LUXRAY = 0x195,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK406_BUDEW = 0x196,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK407_ROSERADE = 0x197,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL146_SAND_RUSH},        // PK408_CRANIDOS = 0x198,
        {1, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH, ABIL146_SAND_RUSH},        // PK409_RAMPARDOS = 0x199,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK410_SHIELDON = 0x19A,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK411_BASTIODON = 0x19B,
        {1, ABIL107_ANTICIPATION, ABIL050_RUN_AWAY, ABIL050_RUN_AWAY}, //   PK412_BURMY = 0x19C,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, //   PK413_WORMADAM = 0x19D,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, //   PK414_MOTHIM = 0x19E,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK415_COMBEE = 0x19F,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK416_VESPIQUEN = 0x1A{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL102_FUR_COAT},                    // PK41{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},PACHIRISU = 0x1A1,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK418_BUIZEL = 0x1A2,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK419_FLOATZEL = 0x1A3,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK420_CHERUBI = 0x1A4,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK421_CHERRIM = 0x1A5,
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL001_STENCH},             // PK422_SHELLOS = 0x1A6,
        {1, ABIL002_DRIZZLE, ABIL045_SAND_STREAM, ABIL001_STENCH},             // PK423_GASTRODON = 0x1A7,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK424_AMBIPOM = 0x1A8,
        {1, ABIL106_AFTERMATH, ABIL051_WIND_RIDER, ABIL031_LIGHTNING_ROD},     // PK425_DRIFLOON = 0x1A9,
        {1, ABIL106_AFTERMATH, ABIL051_WIND_RIDER, ABIL031_LIGHTNING_ROD},     // PK426_DRIFBLIM = 0x1AA,
        {1, ABIL141_MOODY, ABIL017_FLUFFY, ABIL017_FLUFFY},                    // PK427_BUNEARY = 0x1AB,
        {1, ABIL141_MOODY, ABIL017_FLUFFY, ABIL017_FLUFFY},                    // PK428_LOPUNNY = 0x1AC,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},         //   PK429_MISMAGIUS = 0x1AD,
        {1, ABIL119_STAKEOUT, ABIL153_MOXIE, ABIL153_MOXIE},                   // PK430_HONCHKROW = 0x1AE,
        {1, ABIL141_MOODY, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},        // PK431_GLAMEOW = 0x1AF,
        {1, ABIL141_MOODY, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},        // PK432_PURUGLY = 0x1B{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK433_CHINGLING = 0x1B{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL106_AFTERMATH, ABIL001_STENCH, ABIL020_QUICK_DRAW},            //  PK434_STUNKY = 0x1B2,
        {1, ABIL106_AFTERMATH, ABIL001_STENCH, ABIL020_QUICK_DRAW},            //   PK435_SKUNTANK = 0x1B3,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                //   PK436_BRONZOR = 0x1B4,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                //   PK437_BRONZONG = 0x1B5,
        {1, ABIL045_SAND_STREAM, ABIL119_STAKEOUT, ABIL119_STAKEOUT},          // PK438_BONSLY = 0x1B6,
        {1, ABIL107_ANTICIPATION, ABIL141_MOODY, ABIL149_ILLUSION},            // PK439_MIME_JR = 0x1B7,
        {1, ABIL037_HUGE_POWER, ABIL037_HUGE_POWER, ABIL037_HUGE_POWER},       //   PK440_HAPPINY = 0x1B8,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK441_CHATOT = 0x1B9,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL158_PRANKSTER},          //  PK442_SPIRITOMB = 0x1BA,
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL159_SAND_FORCE},       //   PK443_GIBLE = 0x1BB,
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL159_SAND_FORCE},       //  PK444_GABITE = 0x1BC,
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL159_SAND_FORCE},       //   PK445_GARCHOMP = 0x1BD,
        {1, ABIL096_NORMALIZE, ABIL096_NORMALIZE, ABIL096_NORMALIZE},          // PK446_MUNCHLAX = 0x1BE,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK447_RIOLU = 0x1BF,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK448_LUCARIO = 0x1C0,
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},      //  PK449_HIPPOPOTAS = 0x1C0},
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},      //  PK450_HIPPOWDON = 0x1C2,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK451_SKORUPI = 0x1C3,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK452_DRAPION = 0x1C4,
        {1, ABIL033_SWIFT_SWIM, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},   //   PK453_CROAGUNK = 0x1C5,
        {1, ABIL033_SWIFT_SWIM, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},   //   PK454_TOXICROAK = 0x1C6,
        {1, ABIL071_ARENA_TRAP, ABIL119_STAKEOUT, ABIL119_STAKEOUT},           //   PK455_CARNIVINE = 0x1C7,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK456_FINNEON = 0x1C8,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK457_LUMINEON = 0x1C9,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK458_MANTYKE = 0x1CA,
        {1, ABIL117_SNOW_WARNING, ABIL077_SLUSH_RUSH, ABIL081_SNOW_CLOAK},     //   PK459_SNOVER = 0x1CB,
        {1, ABIL117_SNOW_WARNING, ABIL077_SLUSH_RUSH, ABIL081_SNOW_CLOAK},     //   PK460_ABOMASNOW = 0x1CC,
        {1, ABIL088_EXPLOIT, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},        // PK461_WEAVILE = 0x1CD,
        {1, ABIL058_MINUS, ABIL057_PLUS, ABIL057_PLUS},                        // PK462_MAGNEZONE = 0x1CE,
        {1, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK463_LICKILICKY = 0x1CF,
        {1, ABIL045_SAND_STREAM, ABIL038_BERSERK, ABIL038_BERSERK},            // PK464_RHYPERIOR = 0x1D0,
        {1, ABIL034_CHLOROPHYLL, ABIL034_CHLOROPHYLL, ABIL034_CHLOROPHYLL},    // PK460,TANGROWTH = 0x1D1,
        {1, ABIL058_MINUS, ABIL083_ANGER_POINT, ABIL057_PLUS},                 // PK466_ELECTIVIRE = 0x1D2,
        {1, ABIL020_QUICK_DRAW, ABIL070_DROUGHT, ABIL106_AFTERMATH},           //  PK467_MAGMORTAR = 0x1D3,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK468_TOGEKISS = 0x1D4,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK469_YANMEGA = 0x1D5,
        {1, ABIL107_ANTICIPATION, ABIL070_DROUGHT, ABIL122_FLOWER_GIFT},       //  PK470_LEAFEON = 0x1D6,
        {1, ABIL107_ANTICIPATION, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},   //   PK471_GLACEON = 0x1D7,
        {1, ABIL045_SAND_STREAM, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},        // PK472_GLISCOR = 0x1D8,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL083_ANGER_POINT},    //  PK473_MAMOSWINE = 0x1D9,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK474_PORYGON_Z = 0x1DA,
        {1, ABIL149_ILLUSION, ABIL107_ANTICIPATION, ABIL020_QUICK_DRAW},       //   PK475_GALLADE = 0x1DB,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    //   PK476_PROBOPASS = 0x1DC,
        {1, ABIL023_SHADOW_TAG, ABIL107_ANTICIPATION, ABIL149_ILLUSION},       //   PK477_DUSKNOIR = 0x1DD,
        {1, ABIL081_SNOW_CLOAK, ABIL117_SNOW_WARNING, ABIL149_ILLUSION},       //    PK478_FROSLASS = 0x1DE,
        {1, ABIL149_ILLUSION, ABIL057_PLUS, ABIL023_SHADOW_TAG},               //    PK479_ROTOM = 0x1DF,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK480_UXIE = 0x1E0,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK481_MESPRIT = 0x1E0,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK482_AZELF = 0x1E2,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK483_DIALGA = 0x1E3,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK484_PALKIA = 0x1E4,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK485_HEATRAN = 0x1E5,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK486_REGIGIGAS = 0x1E6,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK487_GIRATINA = 0x1E7,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK488_CRESSELIA = 0x1E8,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK489_PHIONE = 0x1E9,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //    PK490_MANAPHY = 0x1EA,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK491_DARKRAI = 0x1EB,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK492_SHAYMIN = 0x1EC,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK493_ARCEUS = 0x1ED,

        // UNOVA
        {1, ABIL126_CONTRARY, ABIL126_CONTRARY, ABIL126_CONTRARY},             // PK494_VICTINI = 0x1EE,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK495_SNIVY = 0x1EF,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK496_SERVINE = 0x1F0,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK497_SERPERIOR = 0x1F1,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK498_TEPIG = 0x1F2,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK499_PIGNITE = 0x1F3,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK500_EMBOAR = 0x1F4,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},          // PK501_OSHAWOTT = 0x1F5,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},          // PK502_DEWOTT = 0x1F6,
        {1, ABIL002_DRIZZLE, ABIL020_QUICK_DRAW, ABIL020_QUICK_DRAW},          // PK503_SAMUROTT = 0x1F7,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK504_PATRAT = 0x1F8,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK505_WATCHOG = 0x1F9,
        {1, ABIL077_SLUSH_RUSH, ABIL113_SCRAPPY, ABIL113_SCRAPPY},             // PK506_LILLIPUP = 0x1FA,
        {1, ABIL077_SLUSH_RUSH, ABIL113_SCRAPPY, ABIL113_SCRAPPY},             // PK507_HERDIER = 0x1FB,
        {1, ABIL077_SLUSH_RUSH, ABIL113_SCRAPPY, ABIL113_SCRAPPY},             // PK508_STOUTLAND = 0x1FC,
        {1, ABIL141_MOODY, ABIL158_PRANKSTER, ABIL158_PRANKSTER},              // PK509_PURRLOIN = 0x1FD,
        {1, ABIL141_MOODY, ABIL158_PRANKSTER, ABIL158_PRANKSTER},              // PK510_LIEPARD = 0x1FE,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK511_PANSAGE = 0x1FF,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK512_SIMISAGE = 0x200,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK513_PANSEAR = 0x201,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                // PK514_SIMISEAR = 0x202,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK515_PANPOUR = 0x203,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK516_SIMIPOUR = 0x204,
        {1, ABIL039_INNER_FOCUS, ABIL086_SIMPLE, ABIL149_ILLUSION},            // PK517_MUNNA = 0x205,
        {1, ABIL039_INNER_FOCUS, ABIL086_SIMPLE, ABIL149_ILLUSION},            // PK518_MUSHARNA = 0x206,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK519_PIDOVE = 0x207,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK520_TRANQUILL = 0x208,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK521_UNFEZANT = 0x209,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK522_BLITZLE = 0x20A,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK523_ZEBSTRIKA = 0x20B,
        {1, ABIL045_SAND_STREAM, ABIL070_DROUGHT, ABIL106_AFTERMATH},          // PK524_ROGGENROLA = 0x20C,
        {1, ABIL045_SAND_STREAM, ABIL070_DROUGHT, ABIL106_AFTERMATH},          // PK525_BOLDORE = 0x20D,
        {1, ABIL045_SAND_STREAM, ABIL070_DROUGHT, ABIL106_AFTERMATH},          // PK526_GIGALITH = 0x20E,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK527_WOOBAT = 0x20F,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK528_SWOOBAT = 0x21{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH},        // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},9_DRILBUR = 0x211,
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL146_SAND_RUSH},        // PK530_EXCADRILL = 0x212,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK531_AUDINO = 0x213,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK532_TIMBURR = 0x214,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK533_GURDURR = 0x215,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK534_CONKELDURR = 0x216,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK535_TYMPOLE = 0x217,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK536_PALPITOAD = 0x218,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK537_SEISMITOAD = 0x219,
        {1, ABIL107_ANTICIPATION, ABIL029_STRONG_BODY, ABIL029_STRONG_BODY},   // PK538_THROH = 0x21A,
        {1, ABIL107_ANTICIPATION, ABIL029_STRONG_BODY, ABIL029_STRONG_BODY},   // PK539_SAWK = 0x21B,
        {1, ABIL107_ANTICIPATION, ABIL034_CHLOROPHYLL, ABIL071_ARENA_TRAP},    // PK540_SEWADDLE = 0x21C,
        {1, ABIL107_ANTICIPATION, ABIL034_CHLOROPHYLL, ABIL071_ARENA_TRAP},    // PK541_SWADLOON = 0x21D,
        {1, ABIL107_ANTICIPATION, ABIL034_CHLOROPHYLL, ABIL071_ARENA_TRAP},    // PK542_LEAVANNY = 0x21E,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK543_VENIPEDE = 0x21F,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK544_WHIRLIPEDE = 0x22{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK54{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},SCOLIPEDE = 0x221,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK546_COTTONEE = 0x222,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK547_WHIMSICOTT = 0x223,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK548_PETILIL = 0x224,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK549_LILLIGANT = 0x225,
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK550_BASCULIN = 0x226,
        {1, ABIL119_STAKEOUT, ABIL045_SAND_STREAM, ABIL083_ANGER_POINT},       // PK551_SANDILE = 0x227,
        {1, ABIL119_STAKEOUT, ABIL045_SAND_STREAM, ABIL083_ANGER_POINT},       // PK552_KROKOROK = 0x228,
        {1, ABIL119_STAKEOUT, ABIL045_SAND_STREAM, ABIL083_ANGER_POINT},       // PK553_KROOKODILE = 0x229,
        {1, ABIL070_DROUGHT, ABIL050_RUN_AWAY, ABIL050_RUN_AWAY},              // PK554_DARUMAKA = 0x22A,
        {1, ABIL070_DROUGHT, ABIL161_ZEN_MODE, ABIL161_ZEN_MODE},              // PK555_DARMANITAN = 0x22B,
        {1, ABIL008_SAND_VEIL, ABIL034_CHLOROPHYLL, ABIL045_SAND_STREAM},      // PK556_MARACTUS = 0x22C,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK557_DWEBBLE = 0x22D,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK558_CRUSTLE = 0x22E,
        {1, ABIL020_QUICK_DRAW, ABIL153_MOXIE, ABIL153_MOXIE},                 // PK559_SCRAGGY = 0x22F,
        {1, ABIL020_QUICK_DRAW, ABIL153_MOXIE, ABIL153_MOXIE},                 // PK560_SCRAFTY = 0x23{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL149_ILLUSION, ABIL008_SAND_VEIL, ABIL008_SAND_VEIL},           // PK5{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_SIGILYPH = 0x231,
        {1, ABIL045_SAND_STREAM, ABIL149_ILLUSION, ABIL023_SHADOW_TAG},        // PK562_YAMASK = 0x232,
        {1, ABIL045_SAND_STREAM, ABIL149_ILLUSION, ABIL023_SHADOW_TAG},        // PK563_COFAGRIGUS = 0x233,
        {1, ABIL045_SAND_STREAM, ABIL002_DRIZZLE, ABIL002_DRIZZLE},            // PK564_TIRTOUGA = 0x234,
        {1, ABIL045_SAND_STREAM, ABIL002_DRIZZLE, ABIL002_DRIZZLE},            // PK565_CARRACOSTA = 0x235,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK566_ARCHEN = 0x236,
        {1, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},    // PK567_ARCHEOPS = 0x237,
        {1, ABIL001_STENCH, ABIL106_AFTERMATH, ABIL106_AFTERMATH},             // PK568_TRUBBISH = 0x238,
        {1, ABIL001_STENCH, ABIL106_AFTERMATH, ABIL106_AFTERMATH},             // PK569_GARBODOR = 0x239,
        {1, ABIL119_STAKEOUT, ABIL149_ILLUSION, ABIL149_ILLUSION},             // PK570_ZORUA = 0x23A,
        {1, ABIL119_STAKEOUT, ABIL149_ILLUSION, ABIL149_ILLUSION},             // PK571_ZOROARK = 0x23B,
        {1, ABIL158_PRANKSTER, ABIL158_PRANKSTER, ABIL158_PRANKSTER},          // PK572_MINCCINO = 0x23C,
        {1, ABIL158_PRANKSTER, ABIL158_PRANKSTER, ABIL158_PRANKSTER},          // PK573_CINCCINO = 0x23D,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL039_INNER_FOCUS},        // PK574_GOTHITA = 0x23E,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL039_INNER_FOCUS},        // PK575_GOTHORITA = 0x23F,
        {1, ABIL023_SHADOW_TAG, ABIL149_ILLUSION, ABIL039_INNER_FOCUS},        // PK576{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},OTHITELLE = 0x240,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},7_SOLOSIS = 0x241,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK578_DUOSION = 0x242,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK579_REUNICLUS = 0x243,
        {1, ABIL002_DRIZZLE, ABIL081_SNOW_CLOAK, ABIL081_SNOW_CLOAK},          //  PK580_DUCKLETT = 0x244,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL081_SNOW_CLOAK},     //  PK581_SWANNA = 0x245,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL106_AFTERMATH},      //  PK582_VANILLITE = 0x246,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL106_AFTERMATH},      //  PK583_VANILLISH = 0x247,
        {1, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK, ABIL106_AFTERMATH},      //  PK584_VANILLUXE = 0x248,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK585_DEERLING = 0x249,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK586_SAWSBUCK = 0x24A,
        {1, ABIL057_PLUS, ABIL058_MINUS, ABIL058_MINUS},                       // PK587_EMOLGA = 0x24B,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, //  PK588_KARRABLAST = 0x24C,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, //  PK589_ESCAVALIER = 0x24D,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},             // PK590_FOONGUS = 0x24E,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},             // PK591_AMOONGUSS = 0x24F,
        {1, ABIL002_DRIZZLE, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},          //  PK5{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_FRILLISH = 0x250,
        {1, ABIL002_DRIZZLE, ABIL023_SHADOW_TAG, ABIL023_SHADOW_TAG},          //   PK593_JELLICENT = 0x25{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL002_DRIZZLE, ABIL002_DRIZZLE, ABIL002_DRIZZLE},                // PK594_ALOMOMOLA = 0x252,
        {1, ABIL071_ARENA_TRAP, ABIL119_STAKEOUT, ABIL057_PLUS},               // PK595_JOLTIK = 0x253,
        {1, ABIL071_ARENA_TRAP, ABIL119_STAKEOUT, ABIL057_PLUS},               // PK596_GALVANTULA = 0x254,
        {1, ABIL106_AFTERMATH, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},    // PK597_FERROSEED = 0x255,
        {1, ABIL106_AFTERMATH, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION},    // PK598_FERROTHORN = 0x256,
        {1, ABIL026_LEVITATE, ABIL057_PLUS, ABIL058_MINUS},                    // PK599_KLINK = 0x257,
        {1, ABIL026_LEVITATE, ABIL057_PLUS, ABIL058_MINUS},                    // PK600_KLANG = 0x258,
        {1, ABIL026_LEVITATE, ABIL057_PLUS, ABIL058_MINUS},                    // PK601_KLINKLANG = 0x259,
        {1, ABIL119_STAKEOUT, ABIL057_PLUS, ABIL058_MINUS},                    // PK602_TYNAMO = 0x25A,
        {1, ABIL119_STAKEOUT, ABIL057_PLUS, ABIL058_MINUS},                    // PK603_EELEKTRIK = 0x25B,
        {1, ABIL119_STAKEOUT, ABIL057_PLUS, ABIL058_MINUS},                    // PK604_EELEKTROSS = 0x25C,
        {1, ABIL149_ILLUSION, ABIL057_PLUS, ABIL058_MINUS},                    // PK605_ELGYEM = 0x25D,
        {1, ABIL149_ILLUSION, ABIL057_PLUS, ABIL058_MINUS},                    // PK606_BEHEEYEM = 0x25E,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL070_DROUGHT},            //  PK607_LITWICK = 0x25F,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL070_DROUGHT},            //  PK{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},8_LAMPENT = 0x260,
        {1, ABIL149_ILLUSION, ABIL023_SHADOW_TAG, ABIL070_DROUGHT},            //  PK609_CHANDELURE = 0x26{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {1, ABIL110_TENACITY, ABIL005_STURDY, ABIL083_ANGER_POINT},            // PK610_AXEW = 0x262,
        {1, ABIL110_TENACITY, ABIL005_STURDY, ABIL083_ANGER_POINT},            //  PK611_FRAXURE = 0x263,
        {1, ABIL110_TENACITY, ABIL005_STURDY, ABIL083_ANGER_POINT},            //  PK612_HAXORUS = 0x264,
        {1, ABIL077_SLUSH_RUSH, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},     // PK613_CUBCHOO = 0x265,
        {1, ABIL077_SLUSH_RUSH, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},     // PK614_BEARTIC = 0x266,
        {1, ABIL106_AFTERMATH, ABIL117_SNOW_WARNING, ABIL081_SNOW_CLOAK},      // PK615_CRYOGONAL = 0x267,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, // PK616_SHELMET = 0x268,
        {1, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION, ABIL107_ANTICIPATION}, //   PK617_ACCELGOR = 0x269,
        {1, ABIL008_SAND_VEIL, ABIL045_SAND_STREAM, ABIL045_SAND_STREAM},      // PK618_STUNFISK = 0x26A,
        {1, ABIL107_ANTICIPATION, ABIL029_STRONG_BODY, ABIL029_STRONG_BODY},   // PK619_MIENFOO = 0x26B,
        {1, ABIL107_ANTICIPATION, ABIL029_STRONG_BODY, ABIL029_STRONG_BODY},   // PK620_MIENSHAO = 0x26C,
        {1, ABIL029_STRONG_BODY, ABIL029_STRONG_BODY, ABIL029_STRONG_BODY},    // PK621_DRUDDIGON = 0x26D,
        {1, ABIL045_SAND_STREAM, ABIL089_IRON_FIST, ABIL106_AFTERMATH},        // PK622_GOLETT = 0x26E,
        {1, ABIL045_SAND_STREAM, ABIL089_IRON_FIST, ABIL106_AFTERMATH},        // PK623_GOLURK = 0x26F,
        {1, ABIL003_SPEED_BOOST, ABIL119_STAKEOUT, ABIL119_STAKEOUT},          //  PK6{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_PAWNIARD = 0x270,
        {1, ABIL003_SPEED_BOOST, ABIL119_STAKEOUT, ABIL119_STAKEOUT},          // PK625_BISHARP = 0x27{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK626_BOUFFALANT = 0x272,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK627_RUFFLET = 0x273,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK628_BRAVIARY = 0x274,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},             // PK629_VULLABY = 0x275,
        {1, ABIL119_STAKEOUT, ABIL119_STAKEOUT, ABIL119_STAKEOUT},             // PK630_MANDIBUZZ = 0x276,
        {1, ABIL071_ARENA_TRAP, ABIL070_DROUGHT, ABIL119_STAKEOUT},            //  PK631_HEATMOR = 0x277,
        {1, ABIL119_STAKEOUT, ABIL071_ARENA_TRAP, ABIL085_HEATPROOF},          // PK632_DURANT = 0x278,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK633_DEINO = 0x279,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK634_ZWEILOUS = 0x27A,
        {1, ABIL141_MOODY, ABIL141_MOODY, ABIL141_MOODY},                      // PK635_HYDREIGON = 0x27B,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL001_STENCH},                 //  PK636_LARVESTA = 0x27C,
        {1, ABIL070_DROUGHT, ABIL070_DROUGHT, ABIL070_DROUGHT},                //  PK637_VOLCARONA = 0x27D,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK638_COBALION = 0x27E,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //  PK639_TERRAKION = 0x27F,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK6{0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},_VIRIZION = 0x280,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK641_TORNADUS = 0x281,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK642_THUNDURUS = 0x282,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK643_RESHIRAM = 0x283,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   //   PK644_ZEKROM = 0x284,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK645_LANDORUS = 0x285,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK646_KYUREM = 0x286,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK647_KELDEO = 0x287,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK648_MELOETTA = 0x288,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // PK649_GENESECT = 0x289,
        {0, ABIL001_STENCH, ABIL001_STENCH, ABIL001_STENCH},                   // MONSNO_MAX = 0x28A,
    };

    void THUMB_BRANCH_TrainerUtil_SetupPkm(u16 trId, PartyPkm *pkm, u16 forme, u8 genderAndAbil)
    {
        u32 v5;           // r7
        int v6;           // r4
        PersonalField v7; // r6
        u32 ParamSingle;  // r0
        u8 v9;            // r1
        u32 data;         // [sp+0h] [bp-20h]
        u16 species;      // [sp+8h] [bp-18h]
        u32 movePP;
        data = forme;
        v5 = 255;
        v6 = 0;
        species = PokeParty_GetParam(pkm, PF_Species, 0);

        do
        {
            if (PokeParty_GetParam(pkm, (PkmField)(v6 + 54), 0) == 218)
            {
                v5 = 0;
            }

            /* Variance PP Setting Implementation */

            if (GetPPSetting())
            {
                movePP = PokeParty_GetParam(pkm, (PkmField)(v6 + 58), 0);
                if (movePP < 5)
                {
                    PokeParty_SetParam(pkm, (PkmField)(v6 + 58), movePP + RandomInRange(1u, 2u));
                    k::Printf("\nThe PP for move %d is %d", PokeParty_GetParam(pkm, (PkmField)(v6 + 58), 0));
                }
                else
                {
                    PokeParty_SetParam(pkm, (PkmField)(v6 + 58), movePP + RandomInRange(1u, 4u));
                    k::Printf("\nThe PP for move %d is %d", PokeParty_GetParam(pkm, (PkmField)(v6 + 58), 0));
                }

                RandomInRange(1u, 4u);
            }
           
            ++v6;
        } while (v6 < 4);

        PokeParty_SetParam(pkm, PF_Happiness, v5);
        PokeParty_SetParam(pkm, PF_Forme, data);
        // if ((genderAndAbil & 0xF0) == 48)
        // {
        //     PokeParty_SetHiddenAbil(pkm, species, data);
        // }
        if ((genderAndAbil & 0xF0) == 16){
            k::Printf("\nCheck Ability 1 for Pokemon %d", species);
            ParamSingle = PML_PersonalGetParamSingle(species, data, Personal_Abil1);
            PokeParty_SetParam(pkm, PF_Ability, ParamSingle);
        }
        else if ((genderAndAbil & 0xF0) == 32){
            k::Printf("\nCheck Ability 2 for Pokemon %d", species);
            ParamSingle = PML_PersonalGetParamSingle(species, data, Personal_Abil2);
            PokeParty_SetParam(pkm, PF_Ability, ParamSingle);
        }
        else if ((genderAndAbil & 0xF0) == 48){
            k::Printf("\nCheck Ability 3 for Pokemon %d", species);
            PokeParty_SetHiddenAbil(pkm, species, data);
        }
        else if ((genderAndAbil & 0xF0) == 64){
            k::Printf("\nCheck Ability 4 for Pokemon %d", species);
            PokeParty_SetParam(pkm, PF_Ability, WhiteListedPokemon[species].abilID4);
        }
        else if ((genderAndAbil & 0xF0) == 80){
            k::Printf("\nCheck Ability 5 for Pokemon %d", species);
            PokeParty_SetParam(pkm, PF_Ability, WhiteListedPokemon[species].abilID5);
        }
        else if ((genderAndAbil & 0xF0) == 96){
            k::Printf("\nCheck Ability 6 for Pokemon %d", species);
            PokeParty_SetParam(pkm, PF_Ability, WhiteListedPokemon[species].abilID6);
        }
        else {
            k::Printf("\nCheck Ability default for Pokemon %d", species);
            ParamSingle = PML_PersonalGetParamSingle(species, data, Personal_Abil1);
            PokeParty_SetParam(pkm, PF_Ability, ParamSingle);
        }

        //  if ((genderAndAbil & 0xF0) != 0)
        // {
        //     k::Printf("\ngenderAndAbil == %d\n The whitelisted value is %d and the abil id is %d", (genderAndAbil & 0xF0), WhiteListedPokemon[species].whiteListed, WhiteListedPokemon[species].abilID4);

        //     if ((genderAndAbil & 0xF0) == 64 && WhiteListedPokemon[species].whiteListed)
        //     {
        //         k::Printf("\nCheck Ability 4 for Pokemon %d", species);

        //         PokeParty_SetParam(pkm, PF_Ability, WhiteListedPokemon[species].abilID4);
        //     }
        //     if ((genderAndAbil & 0xF0) == 80 && WhiteListedPokemon[species].whiteListed)
        //     {
        //         k::Printf("\nCheck Ability 5 for Pokemon %d", species);
        //         PokeParty_SetParam(pkm, PF_Ability, WhiteListedPokemon[species].abilID5);
        //     }
        //     else if ((genderAndAbil & 0xF0) == 96 && WhiteListedPokemon[species].whiteListed)
        //     {
        //         k::Printf("\nCheck Ability 6 for Pokemon %d", species);
        //         PokeParty_SetParam(pkm, PF_Ability, WhiteListedPokemon[species].abilID6);
        //     }
        //     else
        //     {
        //         k::Printf("\nCheck Ability vanilla for Pokemon %d", species);
        //         v7 = Personal_Abil1;
        //         if (PML_PersonalGetParamSingle(species, data, Personal_Abil2) && (genderAndAbil & 0xF0) == 32)
        //         {
        //             v7 = Personal_Abil2;
        //         }
        //         ParamSingle = PML_PersonalGetParamSingle(species, data, v7);
        //         PokeParty_SetParam(pkm, PF_Ability, ParamSingle);
        //     }
        // }

        // ADD
        // SHINY LOGIC
        /* Trainer Pokeballs */


        /* Trainer Shiny Pokemon */
        u32 result = PokeParty_GetParam(pkm, PF_PID, 0);
        result |= 0x80000000;
        PokeParty_SetParam(pkm, PF_PID, result);

        PokeParty_GetParam(pkm, PF_PID, 0);
        PokeParty_SetNature(pkm, v9);
    }

#pragma endregion

#pragma region UnfinishedIllusionChanges
    // struct	BattleParty SWAN_ALIGNED(4) {BattleMon *mons[6];u8 memberCount;u8 numCoverPos;char field_1A;char field_1B;};

    // extern int BattleMon_CanBattle(BattleMon *a1);
    // extern BattleStyle MainModule_GetBattleStyle(MainModule *a1);
    // extern int MainModule_GetNumBattlePositionsOfClient(MainModule *a1, int a2);
    // extern unsigned int BattleMon_IsIllusionEnabled(BattleMon *a1);
    // extern PartyPkm * BattleMon_GetViewSrcData(BattleMon *a1);
    // extern void BattleMon_SetIllusion(BattleMon *result, PartyPkm *a2);
    // extern void BattleMon_RemoveIllusion(BattleMon *result);
    // extern PartyPkm * BattleMon_GetSrcData(BattleMon *a1);
    // extern unsigned int PickBestMonToSwitchInto(void *a1, u8 *a2, unsigned int a3, BattleMon *a4);
    // extern int MainModule_BattlePosToClientID(MainModule *a1, int a2);
    // extern BattleMon* SwitchAI_DetermineOpponent(void *a1, __int16 a2);
    // extern unsigned int MainModule_PokeIDToClientID(int a1);
    // extern unsigned int MainModule_GetClientPokePos(MainModule *a1, int clientID, int partyIndex);
    // extern BattleMon * PokeCon_GetBattleMon(void *a1, int a2);
    // extern BattleMon * Handler_GetBattleMon(void *a1, int a2);

    // void THUMB_BRANCH_MainModule_SetIllusionForParty(MainModule *a1, BattleParty *a2, int a3)
    // {
    //     int i;                          // r6
    //     int NumBattlePositionsOfClient; // r4
    //     int NumBattlePositionOfClient2;
    //     unsigned int numOfMonsToCheckForSwitch;
    //     int j;                          // r0
    //     BattleMon *v8;                  // r7
    //     BattleMon *opposingPokemon;
    //     PartyPkm *SrcData;              // r0
    //     int v10;                        // r4
    //     unsigned char validMonsInParty[28];

    //     for (i = a2->memberCount - 1; i > 0; --i)
    //     {
    //         if (BattleMon_CanBattle(a2->mons[i]))
    //         {
    //             break;
    //         }
    //     }
    //     if (MainModule_GetBattleStyle(a1) == BTL_STYLE_ROTATION)
    //     {
    //         NumBattlePositionsOfClient = 3;
    //     }
    //     else
    //     {
    //         NumBattlePositionsOfClient = MainModule_GetNumBattlePositionsOfClient(a1, a3);
    //     }

    //     // Iterate over the party to compile a list of all the IDs of pokemon who are valid switch targets, including the illusion pokemon.
    //     // This whole function should run before a swap actually takes place in ServerControl_SwitchInCore
    //     NumBattlePositionOfClient2 = NumBattlePositionsOfClient;
    //     for (j = a2->memberCount; NumBattlePositionOfClient2 < j; ++NumBattlePositionOfClient2)
    //     {
    //         v8 = a2->mons[NumBattlePositionOfClient2];

    //         if (v8 && BattleMon_CanBattle(v8))
    //         {
    //             // stores the id of the pokemon and increments the count for number of mons to check
    //             validMonsInParty[numOfMonsToCheckForSwitch] = v8->ID;
    //             numOfMonsToCheckForSwitch++;
    //         }
    //         j = a2->memberCount;
    //     }

    //     for (j = a2->memberCount; NumBattlePositionsOfClient < j; ++NumBattlePositionsOfClient)
    //     {
    //         v8 = a2->mons[NumBattlePositionsOfClient];
    //         if (BattleMon_GetValue(v8, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
    //         {
    //             if (NumBattlePositionsOfClient >= i)
    //             {
    //                 if (BattleMon_GetViewSrcData(v8) != a1->TempPartyPkm)
    //                 {
    //                     BattleMon_RemoveIllusion(v8);
    //                 }
    //             }
    //             else
    //             {
    //                 __int16 pokePos = MainModule_GetClientPokePos(a1, MainModule_PokeIDToClientID(v8->ID), NumBattlePositionsOfClient);
    //                 opposingPokemon = SwitchAI_DetermineOpponent(a1->clients[MainModule_PokeIDToClientID(v8->ID)], pokePos);
    //                 int illusionId = PickBestMonToSwitchInto(a1->clients[MainModule_PokeIDToClientID(v8->ID)], validMonsInParty, numOfMonsToCheckForSwitch, opposingPokemon);
    //                 SrcData = BattleMon_GetSrcData(Handler_GetBattleMon(a1->server, illusionId));
    //                 BattleMon_SetIllusion(v8, SrcData);
    //             }
    //         }
    //         j = a2->memberCount;
    //     }
    //     v10 = 0;
    //     if (j > 0)
    //     {
    //         do
    //         {
    //             BattleMon_IsIllusionEnabled(a2->mons[v10++]);
    //         } while (v10 < a2->memberCount);
    //     }
    // }

#pragma endregion
}