#include "kPrint.h"
#include "swantypes.h"

#define ANIMATED_BACKGROUNDS_ENABLED 0

#pragma region defintions
extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

// uses ESDB_15.yml

extern "C"
{
    struct WildEncSlot
    {
        u16 IdAndForme;
        u8 LvMin;
        u8 LvMax;
    };
    struct EncData
    {
        u8 UserData[8];
        WildEncSlot Slots[56];
    };
    struct EncountSystem
    {
        void *m_Field;
        void *m_GameSystem;
        void *m_GameData;
        EncData *m_EncData;
        void *m_EffectEncountState;
    };

    enum BattleStyle
    {
        BTL_STYLE_SINGLE = 0x0,
        BTL_STYLE_DOUBLE = 0x1,
        BTL_STYLE_TRIPLE = 0x2,
        BTL_STYLE_ROTATION = 0x3,
    };
    enum Season
    {
        SEASON_SPRING = 0x0,
        SEASON_SUMMER = 0x1,
        SEASON_AUTUMN = 0x2,
        SEASON_WINTER = 0x3,
    };
    enum TrainerField
    {
        TR_POKE_TEMPLATE = 0x0,
        TR_CLASS = 0x1,
        TR_BATTLE_TYPE = 0x2,
        TR_POKE_COUNT = 0x3,
        TR_ITEM1 = 0x4,
        TR_ITEM2 = 0x5,
        TR_ITEM3 = 0x6,
        TR_ITEM4 = 0x7,
        TR_AI = 0x8,
        TR_HEALER = 0x9,
        TR_CASH = 0xA,
        TR_POST_BATTLE_ITEM = 0xB,
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
    struct NNSCmnResHeader
    {
        u32 Magic;
        s16 BOM;
        u16 Version;
        u32 FileSize;
        u16 HeaderSize;
        u16 BlockCount;
    };
    struct NNSG3DResData
    {
        NNSCmnResHeader Header;
        u32 BlockOffsets[];
    };
    struct G3DResource
    {
        s16 AllocState;
        s16 ResourceType;
        NNSG3DResData *ResourceData;
    };

    enum PlayerExState
    {
        FLD_PLAYER_EXSTATE_NONE = 0x0,
        FLD_PLAYER_EXSTATE_CYCLING = 0x1,
        FLD_PLAYER_EXSTATE_SURF = 0x2,
        FLD_PLAYER_EXSTATE_DIVE = 0x3,
    };

    struct RTCTime
    {
        u32 Hour;
        u32 Minute;
        u32 Second;
    };
    struct TileType
    {
        u16 Class;
        u16 Flags;
    };
    struct RailPosition
    {
        u16 ComponentID;
        u8 ComponentIsLine;
        u8 RailDirection;
        s16 PosSide;
        u16 PosFront;
    };
    typedef u16 fxangle;
    typedef s32 fx32;

    struct VecFx32
    {
        fx32 x;
        fx32 y;
        fx32 z;
    };

    struct PlayerState
    {
        u16 ZoneID;
        VecFx32 VecPos;
        RailPosition RailPos;
        fxangle RotationAngle;
        u8 field_1A;
        u8 IsPosRail;
        u16 NowOBJCODE;
        __int16 field_1E;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int field_34;
        int field_38;
        int field_3C;
        PlayerExState ExState;
    };
    struct FieldPosition
    {
        VecFx32 Vector;
        RailPosition Rail;
    };
    struct ZoneSpawnInfo
    {
        u32 ChangeType;
        u16 ZoneID;
        u16 WarpID;
        u16 WarpDir;
        u16 PosWeightBits;
        b32 IsRail;
        FieldPosition Pos;
    };
    enum DayPart
    {
        MORNING = 0x0,
        DAY = 0x1,
        SUNSET = 0x2,
        EVENING = 0x3,
        NIGHT = 0x4,
    };
#pragma endregion

#pragma region ZoneIdToBackgroundID
    const int ZoneIdToBackgroundID[615] = {
        9,  // 0 Black City
        9,  // 1 Black City
        9,  // 2 Black City
        9,  // 3 Black City
        9,  // 4 Black City
        9,  // 5 Black City
        6,  // 6 Striaton City
        9,  // 7 Striaton City Restaurant
        27, // 8 Striaton City Pokemon Center
        9,  // 9 Striaton City
        9,  // 10 Striaton City
        9,  // 11 Striaton City
        9,  // 12 Striaton City
        9,  // 13 Striaton City Restaurant
        9,  // 14 Striaton City Restaurant
        9,  // 15 Striaton City Restaurant
        2,  // 16 Nacrene City
        9,  // 17 Nacrene City
        9,  // 18 Nacrene City
        9,  // 19 Nacrene City
        27, // 20 Nacrene City Pokemon Center
        9,  // 21 Nacrene City
        9,  // 22 Nacrene City
        9,  // 23 Nacrene City
        9,  // 24 Nacrene City
        9,  // 25 Nacrene City
        9,  // 26 Nacrene City
        9,  // 27 Nacrene Gate
        54, // 28 Castelia Streets
        55, // 29 Castelia Gym
        54, // 30 Castelia City
        54, // 31 Castelia City
        54, // 32 Castelia City
        54, // 33 Castelia City
        54, // 34 Castelia City
        54, // 35 Castelia City
        54, // 36 Castelia City
        54, // 37 Castelia City
        54, // 38 Castelia City
        54, // 39 Castelia City
        54, // 40 Castelia City
        27, // 41 Pokemon Center
        43, // 42 Castelia Interior
        43, // 43 Castelia Interior
        43, // 44 Castelia Interior
        43, // 45 Castelia Battle Company
        44, // 46 Battle Company HQ
        43, // 47 Castelia Interior
        43, // 48 Castelia Interior
        43, // 49 Castelia Interior
        44, // 50 Castelia Interior
        9,  // 51 Castelia Gate
        9,  // 52 Royal Unova
        9,  // 53 Back Alley Cafe
        43, // 54 Castelia Interior
        44, // 55 Castelia Interior
        43, // 56 Castelia Interior
        43, // 57 Castelia Interior
        43, // 58 Castelia Interior
        43, // 59 Castelia Interior
        43, // 60 Castelia Interior
        43, // 61 Castelia Interior
        61, // 62 Nimbasa City (UPDATE UPDATE)
        69, // 63 Nimbasa Gym  (UPDATE UPDATE)
        61, // 64 Nimbasa Park
        27, // 65 Nimbasa Pokemon Center
        9,  // 66 Gear Station
        9,  // 67 Gear Station
        9,  // 68 Gear Station
        9,  // 69 Gear Station
        9,  // 70 Gear Station
        9,  // 71 Gear Station
        9,  // 72 Gear Station
        9,  // 73 Gear Station
        9,  // 74 Gear Station
        9,  // 75 Battle Subway
        9,  // 76 Battle Subway
        9,  // 77 Muscial Theater
        9,  // 78 Muscial Theater
        9,  // 79 Arena Lobby
        9,  // 80 Sports Arena
        9,  // 81 Football Field
        9,  // 82 Soccer Field
        9,  // 83 Soccer Field
        9,  // 84 Court Lobby
        9,  // 85 Court Stands
        9,  // 86 Tennis Court
        9,  // 87 Basketball Court
        61, // 88 Nimbasa City
        61, // 89 Nimbasa City
        61, // 90 Nimbasa Gate
        61, // 91 Nimbasa Gate
        16, // 92 Nimbasa Gate
        61, // 93 Nimbasa City (LOOK AT THIS A BATTLEFIELD)
        61, // 94 Nimbasa Interior
        61, // 95 Nimbasa Interior
        73, // 96 Driftveil City
        81, // 97 Driftveil Gym
        81, // 98 Driftveil Gym Lobby
        27, // 99 Driftveil Pokemon Center
        76, // 100 Driftveil Interior
        76, // 101 Driftveil Interior
        76, // 102 Driftveil Interior
        76, // 103 Driftveil Interior
        77, // 104 Plasma Sanctuary
        73, // 105 Driftveil Market
        73, // 106 Driftveil PWT Gate
        2,  // 107 Mistralton City
        9,  // 108 Mistralton Gym
        27, // 109 Mistralton Pokemon Center
        9,  // 110 Mistralton Interior
        9,  // 111 Mistralton Interior
        9,  // 112 Mistralton Interior
        2,  // 113 Icciruss City
        9,  // 114 Iccirus Gym
        27, // 115 Iccirus Pokemon Center
        9,  // 116 Iccirus Interior
        9,  // 117 Iccirus Interior
        9,  // 118 Iccirus Interior
        9,  // 119 Iccirus Interior
        2,  // 120 Opelucid City
        9,  // 121 Opelucid Gym
        27, // 122 Opelucid Pokemon Center
        9,  // 123 Opelucid Interior
        9,  // 124 Opelucid Interior
        9,  // 125 Opelucid Interior
        9,  // 126 Opelucid Interior
        9,  // 127 Opelucid Interior
        9,  // 128 Opelucid Interior
        9,  // 129 Opelucid Interior
        9,  // 130 Opelucid Interior
        9,  // 131 Opelucid Gate
        9,  // 132 Opelucid Gate
        9,  // 133 Opelucid Gate
        9,  // 134 Opelucid Interior
        9,  // 135 Opelucid Interior
        7,  // 136 Pokemon League
        9,  // 137 Pokemon League interior
        7,  // 138 Pokemon League Stairs
        7,  // 139 Pokemon League Stairs
        11, // 140 Pokemon League Shauntel's Room
        13, // 141 Pokemon League Grimsly's Room
        12, // 142 Pokemon League Marhsal's Room
        14, // 143 Pokemon League Caitlyn's Room
        16, // 144 Iris's Room
        9,  // 145 Pokemon League Interior
        9,  // 146 Pokemon league Pokemon Center
        9,  // 147 Unity Tower
        9,  // 148 Unity Tower Interior
        9,  // 149 Unity Tower Interior
        9,  // 150 Online Battlefield
        9,  // 151 Online Battlefield
        0,  // 152 Dreamyard
        9,  // 153 Dreamyard Underground
        0,  // 154 Pinwheel Forest Exterior
        6,  // 155 Pinwheel Forest Interior
        6,  // 156 Rumination Field
        57, // 157 Desert Resort Exterior
        58, // 158 Desert Resort Interior
        9,  // 159 Route Gate
        59, // 160 Relic Castle Upper Floors
        59, // 161 Relic Castle Upper Floors
        9,  // 162 Relic Castle Lower Floors
        9,  // 163 Relic Castle Lower Floors
        9,  // 164 Relic Castle Lower Floors
        9,  // 165 Relic Castle Lower Floors
        9,  // 166 Relic Castle Lower Floors
        9,  // 167 Relic Castle Lower Floors
        9,  // 168 Relic Castle Lower Floors
        9,  // 169 Relic Castle Lower Floors
        9,  // 170 Relic Castle Lower Floors
        9,  // 171 Relic Castle Lower Floors
        9,  // 172 Relic Castle Lower Floors
        9,  // 173 Relic Castle Lower Floors
        9,  // 174 Relic Castle Lower Floors
        9,  // 175 Relic Castle Lower Floors
        9,  // 176 Relic Castle Lower Floors
        9,  // 177 Relic Castle Lower Floors
        9,  // 178 Relic Castle Lower Floors
        9,  // 179 Relic Castle Lower Floors
        9,  // 180 Relic Castle Lower Floors
        9,  // 181 Relic Castle Lower Floors
        9,  // 182 Relic Castle Sanctum
        9,  // 183 Relic Castle Lower Floors
        9,  // 184 Relic Castle Lower Floors
        9,  // 185 Relic Castle Lower Floors
        9,  // 186 Relic Castle Lower Floors
        9,  // 187 Relic Castle Lower Floors
        9,  // 188 Relic Castle Lower Floors
        9,  // 189 Relic Castle Lower Floors
        9,  // 190 Relic Castle Lower Floors
        2,  // 191 PWT Exterior
        9,  // 192 PWT Interior
        9,  // 193 PWT Battlefield
        7,  // 194 Chargestone Cave Cave Mouth
        4,  // 195 Chargestone Cave
        4,  // 196 Chargestone Cave
        4,  // 197 Chargestone Cave
        7,  // 198 Twist Mountain Exterior
        7,  // 199 Twist Mountain Interior Basin
        4,  // 200 Twist Mountain Cave
        4,  // 201 Twist Mountain Cave
        4,  // 202 Twist Mountain Cave
        4,  // 203 Twist Mountain Cave
        9,  // 204 Twist Mountain Building
        1,  // 205 Dragonspiral Tower Iccirus Side
        1,  // 206 Dragonspiral Tower Exterior
        9,  // 207 Dragonspiral Interior
        9,  // 208 Dragonspiral Interior
        9,  // 209 Dragonspiral Interior
        9,  // 210 Dragonspiral Interior
        9,  // 211 Dragonspiral Interior
        9,  // 212 Dragonspiral Interior
        17, // 213 Dragonspiral Tower Sanctum
        7,  // 214 Victory Road Old Exterior
        5,  // 215 Victory Road Interior
        5,  // 216 Victory Road Interior
        5,  // 217 Victory Road Interior
        5,  // 218 Victory Road Interior
        5,  // 219 Victory Road Interior
        5,  // 220 Victory Road Interior
        5,  // 221 Victory Road Interior
        5,  // 222 Victory Road Interior
        5,  // 223 Victory Road Interior
        5,  // 224 Victory Road Interior
        5,  // 225 Victory Road Interior
        5,  // 226 Victory Road Interior
        5,  // 227 Victory Road Interior
        5,  // 228 Victory Road Exit
        5,  // 229 Trial Chamber
        7,  // 230 Giant Chasm Exterior
        5,  // 231 Giant Chasm Interior
        7,  // 232  Giant Chasm Exterior
        7,  // 233  Giant Chasm Exterior
        5,  // 234   Giant Chasm Interior
        51, // 235 Liberty Garden
        9,  // 236 Liberty Garden interior
        9,  // 237 Liberty Garden interior
        0,  // 238 P2 Laboratory
        9,  // 239 P2 Lab Interior
        8,  // 240 Undella Bay
        8,  // 241 Abyssal Ruins
        8,  // 242 Abyssal Ruins
        8,  // 243 Abyssal Ruins
        8,  // 244 Abyssal Ruins
        8,  // 245 Abyssal Ruins
        8,  // 246 Abyssal Ruins
        8,  // 247 Abyssal Ruins
        8,  // 248 Abyssal Ruins
        2,  // 249 Skyarrow Bridge
        9,  // 250 Bridge Gate
        9,  // 251 Bridge Gate
        9,  // 252 Bridge Gate
        72, // 253 Driftveil Drawbridge
        2,  // 254 Tubeline Bridge
        2,  // 255 Village Bridge Exterior
        9,  // 256 Village Bridge
        9,  // 257 Village Bridge
        9,  // 258 Village Bridge
        9,  // 259 Village Bridge
        9,  // 260 Village Bridge
        9,  // 261 Village Bridge
        9,  // 262 Village Bridge
        2,  // 263 Marvelous Bridge Exterior
        9,  // 264 N's Castle
        9,  // 265 N's Castle
        9,  // 266 N's Castle
        9,  // 267 N's Castle
        9,  // 268 N's Castle
        9,  // 269 N's Castle
        9,  // 270 N's Castle
        9,  // 271 N's Castle
        9,  // 272 N's Castle
        9,  // 273 N's Castle
        9,  // 274 N's Castle
        9,  // 275 N's Castle
        9,  // 276 N's Castle
        9,  // 277 N's Castle
        9,  // 278 N's Castle
        0,  // 279 Entralink
        6,  // 280 Entree Forest
        6,  // 281 Entree Forest
        6,  // 282 Entree Forest
        6,  // 283 Entree Forest
        6,  // 284 Entree Forest
        6,  // 285 Entree Forest
        6,  // 286 Entree Forest
        6,  // 287 Entree Forest
        6,  // 288 Entree Forest
        61, // 289 Nimbasa City (Outdated)
        73, // 290 Driftveil City (Outdated)
        2,  // 291 Mistralton City (Outdated)
        2,  // 292 Icirrus City (Outdated)
        2,  // 293 Opelucid City (Outdated)
        2,  // 294 Black City (Outdated)
        2,  // 295 White Forest (Outdated)
        2,  // 296 Cold Storage (Outdated)
        7,  // 297 Chargestone Cave (Outdated)
        7,  // 298 Twist Mountain (Outdated)
        7,  // 299 Dragonspiral Tower (Outdated)
        7,  // 300 Giant Chasm (Outdated)
        72, // 301 Driftveil Drawbridge (Outdated)
        2,  // 302 Tubeline Bridge (Outdated)
        2,  // 303 Marvelous Bridge (Outdated)
        62, // 304 Route 5 (Outdated)
        78, // 305 Route 6 (Outdated)
        1,  // 306 Route 7 (Outdated)
        1,  // 307 Route 8 (Outdated)
        1,  // 308 Route 9 (Outdated)
        1,  // 309 Route 11 (Outdated)
        1,  // 310 Route 12 (Outdated)
        1,  // 311 Route 13 (Outdated)
        1,  // 312 Route 14 (Outdated)
        1,  // 313 Route 15 (Outdated)
        64, // 314 Route 16 (Outdated)
        2,  // 315 Lacunosa Town (Outdated)
        2,  // 316 Undella Town (Outdated)
        0,  // 317 Route 1
        9,  // 318 Route Gate
        0,  // 319 Route 2
        9,  // 320 Accumula Gate
        0,  // 321 Route 3
        9,  // 322 Daycare Center
        9,  // 323 Route 3 Interior
        4,  // 324 Wellspring Cave
        4,  // 325 Wellspring Cave
        2,  // 326 Route 4 (Outdated)
        9,  // 327 Route 4 Interior
        9,  // 328 Route 4 Interior
        62, // 329 Route 5
        62, // 330 Route 5 Interior
        78, // 331 Route 6
        78, // 332 Route 6 Interior
        5,  // 333 Mistralton Cave
        5,  // 334 Mistralton Cave
        4,  // 335 Guidance Chamber
        78, // 336 Route 6 Interior
        0,  // 337 Route 7
        9,  // 338 Celestial Tower
        9,  // 339 Celestial Tower
        9,  // 340 Celestial Tower
        9,  // 341 Celestial Tower
        7,  // 342 Celestial Rooftop
        9,  // 343 Route 7 Interior
        9,  // 344 Route 7 Interior
        1,  // 345 Route 8
        1,  // 346 Moor of Iccirus
        9,  // 347 Bridge Gate
        0,  // 348 Route 9
        9,  // 349 Bridge Gate
        9,  // 350 Shoppping Mall
        9,  // 351 Shopping Mall
        5,  // 352 Challenger's Cave
        5,  // 353 Challenger's Cave
        5,  // 354 Challenger's Cave
        7,  // 355 Route 10
        7,  // 356 Route 10
        7,  // 357 Route 10
        7,  // 358 Route 10
        7,  // 359 Route 10
        7,  // 360 Route 10
        7,  // 361 Route 10
        7,  // 362 Route 10
        7,  // 363 Route 10
        7,  // 364 Route 10
        0,  // 365 Route 11
        9,  // 366 Bridge Gate
        9,  // 367 Route 11 Interior
        0,  // 368 Route 12
        9,  // 369 Bridge Gate
        0,  // 370 Route 13
        9,  // 371 Route 13 Interior
        9,  // 372 Undella Gate
        9,  // 373 Route 13 Interior
        0,  // 374 Route 14
        9,  // 375 Black Gate
        0,  // 376 Abundant Shrine
        9,  // 377 Abundant Shrine Interior
        2,  // 378 Route 15
        9,  // 379 Black Gate
        9,  // 380 Bridge Gate
        9,  // 381 Poketransfer Lab
        9,  // 382 Route 15 Interior
        64, // 383 Route 16
        9,  // 384 Bridge Gate
        66, // 385 Lostlorn Forest
        66, // 386 Lostlorn Forest
        0,  // 387 Route 18
        9,  // 388 Route 18 Interior
        2,  // 389 Nuvema Town
        9,  // 390 Nuvema Town Interior
        9,  // 391 Nuvema Town Interior
        9,  // 392 Nuvema Town Interior
        9,  // 393 Nuvema Town Interior
        9,  // 394 Nuvema Town Interior
        9,  // 395 Nuvema Town Interior
        9,  // 396 Nuvema Town Interior
        2,  // 397 Accumula Town
        27, // 398 Accumula Town Pokemon Center
        9,  // 399 Accumula Town Interior
        9,  // 400 Accumula Town Interior
        9,  // 401 Accumula Town Interior
        9,  // 402 Accumula Town Interior
        9,  // 403 Accumula Town Interior
        9,  // 404 Accumula Town Interior
        9,  // 405 Accumula Town Interior
        2,  // 406 Lacunosa Town
        27, // 407 Lacunosa Town Pokemon Center
        9,  // 408 Lacunosa Town Interior
        9,  // 409 Lacunosa Town Interior
        9,  // 410 Lacunosa Town Interior
        9,  // 411 Lacunosa Town Interior
        2,  // 412 Undella Town
        27, // 413 Undella Town Pokemon Center
        9,  // 414 Bridge Gate
        9,  // 415 Undella Town Interior
        9,  // 416 Undella Town Interior
        9,  // 417 Undella Town Interior
        71, // 418 Anville Town
        71, // 419 Anville Town Interior
        71, // 420 Anville Town Interior
        71, // 421 Anville Town Interior
        9,  // 422 Online Battle Arena (??)
        8,  // 423 Route 17
        6,  // 424 White Forest
        9,  // 425 White Forest Interior
        9,  // 426 White Forest Interior
        38, // 427 Aspertia City
        9,  // 428 Aspertia City Interior
        9,  // 429 Aspertia City Interior
        9,  // 430 Aspertia City Interior
        9,  // 431 Aspertia City Interior
        9,  // 432 Aspertia City Interior
        9,  // 433 Aspertia City Interior
        9,  // 434 Aspertia City Interior
        27, // 435 Asperita City Pokemon Center
        9,  // 436 Asperita City Gym
        73, // 437 Route 19
        9,  // 438 Aspertia Gate
        3,  // 439 Floccessy Town
        28, // 440 Alder's House
        9,  // 441 Flocessy Town Interior
        9,  // 442 Floccessy Town Interior
        27, // 443 Floccessy Town Pokemon Center
        25, // 444 Flocessy Ranch
        25, // 445 Floccessy Ranch
        23, // 446 Route 20
        33, // 447 Virbank Gate
        34, // 448 Virbank City
        9,  // 449 Virbank City Interior
        9,  // 450 Virbank City Interior
        9,  // 451 Virbank City Interior
        9,  // 452 Virbank City Interior
        33, // 453 Virbank City Pokestar Studios Gate
        27, // 454 Virbank City Pokemon Center
        9,  // 455 Virbank City Interior
        39, // 456 Virbank Complex (Outside)
        40, // 457 Virbank Complex (Inside)
        3,  // 458 Lentimas Town
        9,  // 459 Lentimas Town Interior
        27, // 460 Lentimas Town Pokemon Center
        7,  // 461 Reversal Mountain
        9,  // 462 Strange House
        8,  // 463 Route 20
        9,  // 464 Marine Tube
        2,  // 465 Humilau City
        9,  // 466 Humilau City Interior
        9,  // 467 Humilau City Interior
        9,  // 468 Humilau City Interior
        9,  // 469 Humilau City Interior
        9,  // 470 Humilau City Interior
        9,  // 471 Bridge Gate
        27, // 472 Humilau City Pokemon Center
        9,  // 473 Humilau City Gym
        0,  // 474 Route 22
        7,  // 475 Route 23
        9,  // 476 Route 23 Interior
        9,  // 477 Route 23 Interior
        9,  // 478 White Treehollow Lobby
        9,  // 479 Black Tower Lobby
        9,  // 480 White Treehollow
        9,  // 481 Black Tower
        9,  // 482 White Treehollow
        9,  // 483 Black Tower
        9,  // 484 Black Tower
        9,  // 485 White Treehollow
        9,  // 486 Black Tower
        9,  // 487 White Treehollow
        56, // 488 Castelia Gym Leader
        30, // 489 Aspertia Gym
        60, // 490 Join Avenue
        60, // 491 Join Avenue Interior
        9,  // 492 White Treehollow
        9,  // 493 Black Tower
        54, // 494 Castelia City Interior
        45, // 495 Castelia Sewers
        45, // 496 Castelia Sewers
        45, // 497 Castelia Sewers
        45, // 498 Castelia Sewers
        45, // 499 Castelia Sewers
        47, // 500 Castelia Gardens
        54, // 501 Castelia Back Alley
        41, // 502 Virbank Gym
        46, // 503 Relic Passage
        46, // 504 Relic Passage
        46, // 505 Relic Passage
        80, // 506 Clay Tunnel
        80, // 507 Clay Tunnel
        80, // 508 Clay Tunnel
        4,  // 509 Twist Mountain
        9,  // 510 Strange House
        9,  // 511 Strange House
        9,  // 512 Strange House
        9,  // 513 Strange House
        9,  // 514 Strange House
        4,  // 515 Seaside Cave
        4,  // 516 Seaside Cave
        4,  // 517 Cave of Being
        6,  // 518 Hidden Grotto
        9,  // 519 Route 4 Interior
        9,  // 520 Route 4 Interior
        9,  // 521 Route 4 Interior
        9,  // 522 Route 4 Interior
        9,  // 523 Route 4 Interior
        9,  // 524 Route 4 Interior
        9,  // 525 Route 4 Interior
        9,  // 526 Route 4 Interior
        9,  // 527 Route 4 Interior
        9,  // 528 Route 4 Interior
        9,  // 529 Route 4 Interior
        9,  // 530 Route 4 Interior
        4,  // 531 Reversal Mountain Interior (Water)
        4,  // 532 Reversal Mountain Interior (Water)
        4,  // 533 Reversal Mountain Interior (Water)
        4,  // 534 Reversal Mountain Interior (Water)
        4,  // 535 Reversal Mountain Interior (Water)
        4,  // 536 Reversal Mountain Interior (Water)
        4,  // 537 Reversal Mountain Interior (Magma)
        4,  // 538 Reversal Mountain Interior (Magma)
        4,  // 539 Reversal Mountain Interior (Magma)
        4,  // 540 Reversal Mountain Interior (Magma)
        4,  // 541 Reversal Mountain Interior (Magma)
        4,  // 542 Reversal Mountain Interior (Magma)
        76, // 543 Driftveil City Interior (Fancy)
        76, // 544 Driftveil City Interior (Fancy)
        76, // 545 Driftveil City Interior (Fancy)
        76, // 546 Driftveil City Interior (Fancy)
        76, // 547 Driftveil City Interior (Fancy)
        76, // 548 Driftveil City Interior (Fancy)
        76, // 549 Driftveil City Interior (Fancy)
        76, // 550 Driftveil City Interior (Fancy)
        48, // 551 Route 4 (White)
        9,  // 552 Plasma Frigate Exterior, PWT
        9,  // 553 Plasma Frigate Interior
        9,  // 554 Plasma Frigate Interior
        9,  // 555 Plasma Frigate Interior (Colress's Room)
        9,  // 556 Plasma Frigate Interior (Core Room 2)
        9,  // 557 Plasma Frigate Interior (Monitoring Room, Ninja Fight Arena)
        9,  // 558 Plasma Frigate Interior
        9,  // 559 Plasma Frigate Interior
        9,  // 560 Plasma Frigate Interior
        9,  // 561 Plasma Frigate Interior
        9,  // 562 Plasma Frigate Exterior, Giant Chasm
        9,  // 563 Plasma Frigate Interior
        9,  // 564 Plasma Frigate Interior (Core Room, Zinzolin Fight)
        4,  // 565 Guidance Chamber
        9,  // 566 Pokestar Studios Exterior
        9,  // 567 Pokestar Studios Interior
        9,  // 568 Pokestar Studios Interior
        9,  // 569 Strange House
        9,  // 570 Strange House
        9,  // 571 Strange House
        9,  // 572 Strange House
        7,  // 573 Victory Road Exterior
        9,  // 574 Pokestar Studios Interior
        9,  // 575 Plasma Frigate Interior
        9,  // 576 Plasma Frigate Interior
        9,  // 577 Plasma Frigate Interior
        9,  // 578 Plasma Frigate Interior
        9,  // 579 Plasma Frigate Interior
        9,  // 580 Plasma Frigate Interior
        9,  // 581 Plasma Frigate Interior
        9,  // 582 Plasma Frigate Interior
        9,  // 583 Plasma Frigate Interior
        7,  // 584 Nature Preserve
        68, // 585 Nimbasa City Old Gym (REPLACE)
        9,  // 586 Pokestar Studios Interior
        4,  // 587 Victory Road Ruins
        6,  // 588 Victory Road Forest
        7,  // 589 Victory Road Cliffs
        4,  // 590 Victory Road Caves
        4,  // 591 Victory Road Caves
        7,  // 592 Victory Road Cliffs
        4,  // 593 Victory Road Caves
        4,  // 594 Victory Road Ruins
        7,  // 595 Victory Road Cliffs
        4,  // 596 Victory Road Palace Path
        9,  // 597 Striaton City Memory
        9,  // 598 Nacrene Gym Memory
        9,  // 599 Undella Town Memory
        9,  // 600 Floccessy Town Memory
        9,  // 601 Opelucid Memory
        9,  // 602 Victory Road Pokemon Center
        9,  // 603 Plasma Sanctuary Memory
        5,  // 604 Giant Chasm Kyurem's Lair
        9,  // 605 Village Bridge Hidden Ruin
        9,  // 606 Musical Theater Memory
        4,  // 607 Chargestone Cave Memory
        9,  // 608 Lentimas Town Interior
        4,  // 609 Guidance Chamber Ruins (edit in CTRMap)
        4,  // 610 Guidance Chamber Ruins (edit in CTRMap)
        4,  // 611 Rocky Chamber (Edit in CTRMap)
        4,  // 612 Icy Chamber (Edit in CTRMap)
        4,  // 613 Guidance Chamber, Cobalion's Room
        29, // 614 Pledge Grove
    };
#pragma endregion

#pragma region ExternalFunctions
    extern int BtlSetup_Reset(void *a1);
    extern void SaveBtlFieldStatus(BattleFieldStatus *status, void *gameData, void *field);
    extern u32 TrainerData_GetParam(u16 trId, TrainerField field);
    extern int GetTrainerClassBattlePedestal(int trClass);
    extern int CheckOverridenTrainerBattleBG(int trClass, int defaultBgId);
    extern void BtlSetup_SetTrainer1v2(
        void *setup,
        void *gameData,
        BattleFieldStatus *fieldStatus,
        int trId1,
        int trId2,
        HeapID heapId);
    extern void BtlSetup_SetTrainer1v1Single(
        void *btlSetup,
        void *gameData,
        BattleFieldStatus *fieldStatus,
        int trId,
        HeapID heapId);
    extern void BtlSetup_SetTrainer2v2(
        void *setup,
        void *gameData,
        BattleFieldStatus *fieldStatus,
        int allyTrId,
        int foe1TrId,
        int foe2TrId,
        HeapID heapId);
    extern void BtlSetup_SetTrainer1v1Double(
        void *setup,
        void *gameData,
        BattleFieldStatus *fieldStatus,
        int trId,
        HeapID heapId);
    extern void BtlSetup_SetTrainer3v3(void *a1, void *a2, BattleFieldStatus *a3, int trId, HeapID a5);
    extern void BtlSetup_SetTrainerRotation(void *a1, void *a2, BattleFieldStatus *a3, int a4, HeapID heapId);
    extern int GetTileClass(TileType result);
    extern TileType FieldPlayer_GetTileTypeUnder(void *player);
    extern void RTC_GetCachedTime(RTCTime *time);
    extern int GetTileEncountType(int tileClass);
    extern unsigned int GetZoneBattleBGID(u16 a1);
    extern void *Field_GetPlayer(void *field);
    extern u16 Field_GetPlayerStateZoneID(void *field);
    extern int ConvFieldWeatherToBtl(void *field);
    extern Season GameData_GetSeason(void *gameData);
    extern PlayerState *GameData_GetPlayerState(void *gameData);
    extern VecFx32 *PlayerState_GetWPos(PlayerState *playerState);
    extern void vecfx_normalize(const VecFx32 *vec, VecFx32 *normalized);
    extern void FieldPlayer_GetWPos(void *player, VecFx32 *dest);
    extern DayPart GetRealTimeDayPeriod(Season season);
#pragma endregion

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------------TRAINER ID TO BACKGROUND ID ------------------------------------
        --------------------------------------------------------------------------------------------------

        This function maps the trainer ID to the background ID that should be used. This is used in a handful
        of areas:
        - Aspertia Gym
        - Virbank Gym
        - Nimbasa Gym
        - Driftveil Gym
        - Misty's Fight in Virbank City
        - Erika
        - Janine
        - Rood
        -
    */
    void modifyFieldStatus(BattleFieldStatus *fieldStatus, int foe1TrID, BattleStyle style)
    {
        if (!ANIMATED_BACKGROUNDS_ENABLED)
        {
            k::Printf("\nCheck values\n");
            return;
        }

        int zoneId = fieldStatus->ZoneID;
        DayPart dayperiod = GetRealTimeDayPeriod((Season)fieldStatus->Season);

        // Aspertia Gym Trainer 1
        if (foe1TrID == 171)
        {
            fieldStatus->BattleBGID = 30;
            return;
        }

        // Aspertia Gym Trainer 2
        if (foe1TrID == 172)
        {
            fieldStatus->BattleBGID = 31;
            return;
        }
        // Cheren
        if (foe1TrID == 156)
        {
            fieldStatus->BattleBGID = 32;
            return;
        }
        // Roxie
        if (foe1TrID == 157)
        {
            fieldStatus->BattleBGID = 42;
            fieldStatus->Hour = 23;
            fieldStatus->Minute = 0;
            fieldStatus->ZoneID = 457;
            return;
        }

        if (foe1TrID == 739)
        {
            fieldStatus->BattleBGID = 41;
            fieldStatus->Hour = 23;
            fieldStatus->Minute = 0;
            fieldStatus->ZoneID = 457;
            return;
        }

        // Misty
        if (foe1TrID == 765)
        {
            if (dayperiod == MORNING || dayperiod == DAY)
            {
                fieldStatus->BattleBGID = 35;
            }
            if (dayperiod == SUNSET)
            {
                fieldStatus->BattleBGID = 36;
            }
            if (dayperiod == EVENING || dayperiod == NIGHT)
            {
                fieldStatus->BattleBGID = 37;
            }
            return;
        }

        // Surge
        if (foe1TrID == 766)
        {
            if (dayperiod == MORNING || dayperiod == DAY)
            {
                fieldStatus->BattleBGID = 51;
            }
            if (dayperiod == SUNSET)
            {
                fieldStatus->BattleBGID = 52;
            }
            if (dayperiod == EVENING || dayperiod == NIGHT)
            {
                fieldStatus->BattleBGID = 53;
            }
            return;
        }
        // Benga
        if (foe1TrID == 773)
        {
            fieldStatus->BattleBGID = 49;
            return;
        }

        // Fisherman Andrew and Hubert
        if (foe1TrID == 210 || foe1TrID == 211)
        {
            fieldStatus->BattlePedestalID = 6;
            return;
        }

        // Elesa
        if (foe1TrID == 153)
        {
            fieldStatus->BattleBGID = 70;
            return;
        }

        // Erika
        if (foe1TrID == 767)
        {
            fieldStatus->BattleBGID = 67;
            return;
        }

        // Janine
        if (foe1TrID == 768 && zoneId == 96)
        {
            fieldStatus->BattleBGID = 75;
            return;
        }

        // Rood
        if (foe1TrID == 346 && zoneId == 96)
        {
            fieldStatus->BattleBGID = 74;
            return;
        }

        // Clay
        if (foe1TrID == 158)
        {
            fieldStatus->BattleBGID = 82;
            return;
        }

        // // Test Case
        // if (foe1TrID == 726)
        // {
        //     fieldStatus->BattleBGID = 77;
        //     return;
        // }

        // // Test Case
        // if (foe1TrID == 729)
        // {
        //     fieldStatus->BattleBGID = 1;
        //     return;
        // }

        // if (foe1TrID == 729 || foe1TrID == 726)
        // {
        //     fieldStatus->BattleBGID = 4;
        //     return;
        // }
    }
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

    extern int howManyPokesAreAbleToFight(PokeParty *pPartyBlk);
    extern PokeParty *GameData_GetParty(void *data);

#pragma region settingupTrainers
    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ SETUP TRAINERS ----------------------------------------------
        --------------------------------------------------------------------------------------------------

        This function will set up trainers. It is also where we will modify the BtlField based on trainer id.
    */
    void THUMB_BRANCH_SAFESTACK_BtlSetup_SetTrainerLocal(
        EncountSystem *encSys,
        void *setup,
        BattleStyle style,
        int allyTrId,
        int foe1TrId,
        int foe2TrId,
        HeapID heapId)
    {
        void *m_GameData;              // r7
        int Param;                     // r0
        int btlPedestalId;             // r0
        int trClass;                   // r0
        BattleFieldStatus fieldStatus; // [sp+18h] [bp-28h] BYREF
        int v16;                       // [sp+28h] [bp-18h]

        v16 = allyTrId;
        m_GameData = encSys->m_GameData;
        BtlSetup_Reset(setup);
        SaveBtlFieldStatus(&fieldStatus, encSys->m_GameData, encSys->m_Field);
        Param = TrainerData_GetParam(foe1TrId, TR_CLASS);
        btlPedestalId = GetTrainerClassBattlePedestal(Param);
        if (btlPedestalId != 20)
        {
            fieldStatus.BattlePedestalID = btlPedestalId;
        }
        trClass = TrainerData_GetParam(foe1TrId, TR_CLASS);
        fieldStatus.BattleBGID = CheckOverridenTrainerBattleBG(trClass, fieldStatus.BattleBGID);
        modifyFieldStatus(&fieldStatus, foe1TrId, style);
        if (foe1TrId >= 21 && foe1TrId <= 82)
        {
            fieldStatus.BattleBGID = foe1TrId;
        }
        k::Printf("\nfieldstatus zone id is %d and the trainer id is %d\n", fieldStatus.BattleBGID, foe1TrId);
        if (style <= BTL_STYLE_ROTATION)
        {
            if (style == BTL_STYLE_SINGLE)
            {
                if (foe2TrId)
                {
                    BtlSetup_SetTrainer1v2(setup, m_GameData, &fieldStatus, foe1TrId, foe2TrId, heapId);
                }
                else
                {
                    BtlSetup_SetTrainer1v1Single(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                }
            }
            else
            {
                if (style == BTL_STYLE_DOUBLE && allyTrId)
                {
                    BtlSetup_SetTrainer2v2(setup, m_GameData, &fieldStatus, allyTrId, foe1TrId, foe2TrId, heapId);
                }
                else
                {
                    k::Printf("\nIt's not a double or a tag battle");

                    if (howManyPokesAreAbleToFight(GameData_GetParty(m_GameData)) < 2)
                    {
                        k::Printf("\nThere aren't enough Pokemon to fight for a double battle. We only have %d", howManyPokesAreAbleToFight(GameData_GetParty(m_GameData)));
                        BtlSetup_SetTrainer1v1Single(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                    }
                    else
                    {
                        if (style == BTL_STYLE_DOUBLE)
                        {

                            BtlSetup_SetTrainer1v1Double(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }

                        if (style == BTL_STYLE_TRIPLE)
                        {
                            BtlSetup_SetTrainer3v3(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                        if (style == BTL_STYLE_ROTATION)
                        {
                            BtlSetup_SetTrainerRotation(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                    }
                }
            }
        }
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ SAVE BATTLEFIELD --------------------------------------------
        --------------------------------------------------------------------------------------------------

        This functions performs modifications to the background id based on position.
    */
    void THUMB_BRANCH_SaveBtlFieldStatus(BattleFieldStatus *status, void *gameData, void *field)
    {
        u16 PlayerStateZoneID;  // r4
        TileType TileTypeUnder; // r0
        int TileClass;          // r0
        void *player;           // [sp+0h] [bp-28h]
        RTCTime time;           // [sp+4h] [bp-24h] BYREF

        PlayerStateZoneID = Field_GetPlayerStateZoneID(field);
        player = Field_GetPlayer(field);
        status->BattleBGID = GetZoneBattleBGID(PlayerStateZoneID);
        // status->BattleBGID = ZoneIdToBackgroundID[PlayerStateZoneID];
        TileTypeUnder = FieldPlayer_GetTileTypeUnder(player);
        TileClass = GetTileClass(TileTypeUnder);
        status->BattlePedestalID = GetTileEncountType(TileClass);
        status->ZoneID = PlayerStateZoneID;
        RTC_GetCachedTime(&time);
        status->Hour = time.Hour;
        status->Minute = time.Minute;
        status->BtlWeather = ConvFieldWeatherToBtl(field);
        status->Season = GameData_GetSeason(gameData);

        if (ANIMATED_BACKGROUNDS_ENABLED)
        {
            if (PlayerStateZoneID == 446    // Route 20
                || PlayerStateZoneID == 445 // Flocessy Ranch
                || PlayerStateZoneID == 385 // Lostlorn Forest
                || PlayerStateZoneID == 551 // Route 4
                || PlayerStateZoneID == 383 // Route 16
                || PlayerStateZoneID == 329 // Route 5
            )
            {
                PlayerState *playerstate = GameData_GetPlayerState(gameData);
                VecFx32 *vec = PlayerState_GetWPos(playerstate);
                VecFx32 *print;
                // k::Printf("\nThis is the BattlefieldFunction; x is %d\ny is %d\nz is %d\n", vec->x, vec->y, vec->z);

                // Route 20
                if (PlayerStateZoneID == 446 && vec->y <= 0)
                {
                    status->BattleBGID = 24;
                }
                // Flocessy Ranch
                if (PlayerStateZoneID == 445 && vec->z < 2457600)
                {
                    status->BattleBGID = 26;
                }
                // Route 4
                if (PlayerStateZoneID == 551)
                {
                    if (vec->y < 0 && vec->z <= 37060608 && vec->z >= 35618816)
                    {
                        status->BattleBGID = 50;
                    }
                }
                // Route 5
                if (PlayerStateZoneID == 329 && vec->z >= 28147712)
                {
                    status->BattleBGID = 63;
                }

                // Route 16
                if (PlayerStateZoneID == 383 && vec->x >= 31031296 && vec->z >= 28672000)
                {
                    status->BattleBGID = 65;
                }

                // Lostlorn Forest
                if (PlayerStateZoneID == 385 && vec->z >= 1925120)
                {
                    status->BattleBGID = 67;
                }

                // Route 6
                // if (PlayerStateZoneID == 385 && vec->z >= 1925120)
                // {
                //     status->BattleBGID = 67;
                // }

                // Chargestone Cave
            }
        }
    }

#pragma endregion

#pragma region DoubleBattleFix
    enum FieldBattleType
    {
        FLD_BTLTYPE_SINGLE = 0x0,
        FLD_BTLTYPE_DOUBLE_SEPARATE = 0x1,
        FLD_BTLTYPE_DOUBLE_UNIFIED = 0x2,
        FLD_BTLTYPE_DOUBLE_MULTI = 0x3,
    };

    struct FieldScriptTrainerSetup
    {
        void *TrainerActor;
        int ClashDistance;
        int ClashDirection;
        int SCRID;
        int TrainerID;
        FieldBattleType BattleType;
    };

    struct SWAN_ALIGNED(4) GameEvent
    {
        GameEvent *ReturnEvent;
        void *Callback;
        u32 EventState;
        void *EventData;
        void *m_GameSystem;
    };

    struct FieldActorResGroup
    {
        u16 Res1;
        u16 Res2;
        u16 Animations[3];
    };

    struct FieldActorConfig
    {
        u16 UID;
        u8 EntityType;
        u8 SceneNodeType;
        u8 EnableShadow;
        u8 FootprintType;
        u8 EnableReflections;
        u8 BillboardSize;
        u8 SpriteAtlasSize;
        u8 SpriteControllerType;
        u8 Gender;
        u8 CollWidth;
        u8 CollHeight;
        s8 WPosOffsetX;
        s8 WPosOffsetY;
        s8 WPosOffsetZ;
        FieldActorResGroup RscIndices;
        u16 Padding;
    };

    struct GPosXYZ
    {
        u16 X;
        s16 Y;
        u16 Z;
    };

    struct ActorPositionRail
    {
        void *m_RailUnit;
        RailPosition m_RailPosition;
        int field_C;
    };

    struct FieldActor
    {
        u32 Flags;
        u32 MovementFlags;
        u16 ActorUID;
        u16 ZoneID;
        u16 ModelID;
        u16 MoveCode;
        u16 EvType;
        u16 SpawnFlag;
        u16 SCRID;
        u16 DefaultDir;
        u16 FaceDir;
        u16 MotionDir;
        u16 LastFaceDir;
        u16 LastMotionDir;
        u16 Param0;
        u16 Param1;
        u16 Param2;
        u16 NextAcmd;
        u16 AcmdState;
        u16 field_2A;
        s16 AreaW;
        s16 AreaH;
        GPosXYZ DefaultGPos;
        GPosXYZ InitGPos;
        GPosXYZ GPos;
        s16 field_42;
        VecFx32 WPos;
        VecFx32 WPosOffset;
        int field_5C;
        int field_60;
        int field_64;
        int field_68;
        int field_6C;
        int field_70;
        TileType CurrentTileUnder;
        TileType CurrentTileUnderOrigY;
        u8 CollisionWidth;
        u8 CollisionHeight;
        s8 ModelPosOffsetX;
        s8 ModelPosOffsetY;
        s8 ModelPosOffsetZ;
        u8 ShadowGroup;
        u16 _padShadowGroup;
        void *m_TCB;
        void *m_ActorSystem;
        void *MoveCodeVTable;
        void *SceneNodeVTable;
        ActorPositionRail DefaultRailPos;
        ActorPositionRail RailPos;
        int field_B4;
        int field_B8;
        int field_BC;
        int field_C0;
        int field_C4;
        int field_C8;
        char field_CC[24];
        FieldActorConfig m_Config;
    };

    unsigned short int &
    LOWORD(unsigned int &x)
    {
        return *(reinterpret_cast<unsigned short int *>(&x) + 0);
    }

    extern int sub_2182FD0(void *a1);
    extern GameEvent *CreateTrainerClashEvent(void *field, void *trainerActor);
    extern int EventTrainerEye_FindClashActor(void *field, void *exclude, void *setup);
    extern void *Field_GetGameSystem(void *field);
    extern GameData *GSYS_GetGameData(void *gsys);
    extern u32 sub_21A6584(void *actor);
    extern BattleStyle getBattleType(u16 trId);
    extern int GetNowFollowerAllyTrID(GameData *gameData);
    extern void SetupTrainerClashSlot(void *event, int trainerSlot, FieldScriptTrainerSetup *setup);
    extern FieldActor *sub_21A6614(void *a1, int a2);
    extern void InitFieldScriptTrainerSetup(
        FieldScriptTrainerSetup *setup,
        void *a2,
        u16 pClashDist,
        u16 pClashDir);

    // void *THUMB_BRANCH_EventTrainerEye_CheckAll(void *field)
    // {
    //     GameEvent *v2;                       // r6
    //     void *GameSystem;                    // r0
    //     GameData *GameData;                  // r7
    //     void *v5;                            // r0
    //     unsigned int partyPkmCount;          // r4
    //     BattleStyle BattleType;              // r0
    //     GameEvent *TrainerClashEvent;        // r0
    //     FieldBattleType v9;                  // r4
    //     GameEvent *v10;                      // r0
    //     int trSlot;                          // r1
    //     FieldScriptTrainerSetup *p_setupTr1; // r2
    //     FieldActor *v13;                           // r0
    //     FieldScriptTrainerSetup setupTr1;    // [sp+0h] [bp-48h] BYREF
    //     FieldScriptTrainerSetup setupTr2;    // [sp+18h] [bp-30h] BYREF

    //     v2 = 0;
    //     GameSystem = Field_GetGameSystem(field);
    //     GameData = GSYS_GetGameData(GameSystem);

    //     if (EventTrainerEye_FindClashActor(field, 0, &setupTr2) == 1)
    //     {
    //         v5 = Field_GetGameSystem(field);
    //         partyPkmCount = sub_2182FD0(v5);
    //         if (sub_21A6584(setupTr2.TrainerActor))
    //         {
    //             BattleType = BTL_STYLE_SINGLE;
    //         }
    //         else
    //         {
    //             BattleType = getBattleType(setupTr2.TrainerID);
    //         }
    //         if (BattleType == BTL_STYLE_SINGLE)
    //         {
    //             if (partyPkmCount && GetNowFollowerAllyTrID(GameData) && EventTrainerEye_FindClashActor(field, setupTr2.TrainerActor, &setupTr1) == 1)
    //             {
    //                 TrainerClashEvent = CreateTrainerClashEvent(field, setupTr2.TrainerActor);
    //                 v2 = TrainerClashEvent;
    //                 v9 = FLD_BTLTYPE_DOUBLE_MULTI;
    //             LABEL_10:
    //                 setupTr2.BattleType = v9;
    //                 SetupTrainerClashSlot(TrainerClashEvent, 0, &setupTr2);
    //                 setupTr1.BattleType = v9;
    //                 v10 = v2;
    //                 trSlot = 1;
    //                 p_setupTr1 = &setupTr1;
    //             LABEL_21:
    //                 SetupTrainerClashSlot(v10, trSlot, p_setupTr1);
    //                 // k::Printf("\nWe're going to do a bunch of diagnostics here\ntrSlot is %d\np_setupTr1 is %d and %d and %d and %d and %d and %d\nv10 is %d and %d and %d and %d and %d", trSlot, p_setupTr1, p_setupTr1->BattleType, p_setupTr1->ClashDirection, p_setupTr1->ClashDistance, p_setupTr1->TrainerActor, p_setupTr1->TrainerID, v10, v10->Callback, v10->EventData, v10->EventState, v10->m_GameSystem);
    //                 k::Printf("\nv2 = %d", v2);
    //                 return v2;
    //             }
    //             if (partyPkmCount >= 2 && EventTrainerEye_FindClashActor(field, setupTr2.TrainerActor, &setupTr1))
    //             {
    //                 TrainerClashEvent = CreateTrainerClashEvent(field, setupTr2.TrainerActor);
    //                 v2 = TrainerClashEvent;
    //                 v9 = FLD_BTLTYPE_DOUBLE_UNIFIED;
    //                 goto LABEL_10;
    //             }
    //         LABEL_20:
    //             v10 = CreateTrainerClashEvent(field, setupTr2.TrainerActor);
    //             trSlot = 0;
    //             v2 = v10;
    //             setupTr2.BattleType = FLD_BTLTYPE_SINGLE;
    //             p_setupTr1 = &setupTr2;
    //             goto LABEL_21;
    //         }
    //         if (BattleType == BTL_STYLE_DOUBLE)
    //         {
    //             if (partyPkmCount)
    //             {
    //                 v13 = sub_21A6614(setupTr2.TrainerActor, LOWORD((unsigned int&)setupTr2.TrainerID));
    //                 InitFieldScriptTrainerSetup(&setupTr1, v13, setupTr2.ClashDistance, setupTr2.ClashDirection);
    //                 TrainerClashEvent = CreateTrainerClashEvent(field, setupTr2.TrainerActor);
    //                 v2 = TrainerClashEvent;
    //                 v9 = FLD_BTLTYPE_DOUBLE_SEPARATE;
    //                 goto LABEL_10;
    //             }
    //         }
    //         else if ((unsigned int)(BattleType - 2) <= 1 && partyPkmCount)
    //         {
    //             goto LABEL_20;
    //         }
    //     }
    //     return v2;
    // }
    
    extern u32 PokeParty_GetParam(PartyPkm *pPkm, int field, void *extra);
    extern PartyPkm *PokeParty_GetPkm(PokeParty *party, int slot);
    extern u32 PokeParty_GetPkmCount(PokeParty *pPartyBlk);

    int THUMB_BRANCH_sub_2182FD0(void *a1)
    {
        GameData *GameData;      // r0
        signed __int32 PkmCount; // r7
        int v3;                  // r4
        int i;                   // r5
        PartyPkm *Pkm;           // r6
        PokeParty *party;        // [sp+0h] [bp-18h]

        GameData = GSYS_GetGameData(a1);
        party = GameData_GetParty(GameData);
        PkmCount = PokeParty_GetPkmCount(party);
        v3 = 0;
        for (i = 0; v3 < PkmCount; ++v3)
        {
            Pkm = PokeParty_GetPkm(party, v3);
            if (!PokeParty_GetParam(Pkm, 0x4C, 0) && PokeParty_GetParam(Pkm, 0xA0, 0))
            {
                ++i;
            }
        }
        return (i == 1) ? 3 : i;
    }
}
