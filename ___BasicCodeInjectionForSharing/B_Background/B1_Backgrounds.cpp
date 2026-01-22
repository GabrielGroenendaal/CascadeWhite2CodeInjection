#include "swantypes.h"
#include "kPrint.h"
#include "../settings.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// uses ESDB_14.yml

#pragma region definitions
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

int ZoneIDsNowWithLighting[] = {
    489,
    46,
    45,
    447};

bool IsInArray(int value)
{
    for (int i = 0; i < 4; i++)
    {
        if (ZoneIDsNowWithLighting[i] == value)
        {
            return true;
        }
    };
    return false;
}

extern "C"
{
    struct EventWorkSave
    {
        u16 Works[431];
        u8 FlagBytes[383];
        u8 CanRespawnHiddenItems;
    };

    extern EventWorkSave *GameData_GetEventWork(void *gameData);
    extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
    u32 GetBackgroundsSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16435);
        return *lvl_cap_ptr;
    }
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
    extern int GetTileClass(TileType result);
    extern TileType FieldPlayer_GetTileTypeUnder(void *player);
    extern void RTC_GetCachedTime(RTCTime *time);
    extern int GetTileEncountType(int tileClass);
    extern unsigned int GetZoneBattleBGID(u16 a1);
    extern void *Field_GetPlayer(void *field);
    extern u16 Field_GetPlayerStateZoneID(void *field);
    extern int ConvFieldWeatherToBtl(void *field);
    extern int GameData_GetSeason(void *gameData);
    extern PlayerState *GameData_GetPlayerState(void *gameData);
    extern VecFx32 *PlayerState_GetWPos(PlayerState *playerState);
    extern void vecfx_normalize(const VecFx32 *vec, VecFx32 *normalized);
    extern void FieldPlayer_GetWPos(void *player, VecFx32 *dest);
    struct AreaData
    {
        u16 Buildings;
        u16 Textures;
        u8 SrtAnime;
        u8 PatAnime;
        u8 IsExterior;
        u8 Lights;
        u8 EdgeColorTableId;
        u8 BbdMdlColors;
    };
    typedef u16 GXColor;
    struct VecFx16
    {
        __int16 x;
        __int16 y;
        __int16 z;
    };
    struct FieldLightInfo
    {
        u16 DayPart;
        s16 MinutesOffs;
        u8 LightIsEnabled[4];
        GXColor LightColors[4];
        VecFx16 LightPositions[4];
        GXColor GXDiffuse;
        GXColor GXAmbient;
        GXColor GXSpecular;
        GXColor GXEmission;
        GXColor GXFogColor;
        GXColor ClearColor;
    };
    struct FieldLightData
    {
        FieldLightInfo Entries[16];
    };
    extern int sub_201991C(int a1);
    extern FieldLightData *Normalize060File(int arcId, u16 datId, u32 *pEntryCount, HeapID heapId);
    extern int GetZoneStaticLightDataIndex(u16 zoneId);
    extern b32 AreaData_HasSeasons(u16 areaID);
    extern u32 ZoneData_GetAreaID(int zoneId);
    extern AreaData *AreaData_Create(HeapID heapId, u16 areaId, u16 areaSeasonShift);
    extern int AreaData_GetLightsID(AreaData *ad);
    extern void AreaData_Free(AreaData *ad);
    extern void sub_201998C(
        FieldLightData *lights,
        u32 lightEntryCount,
        int seconds,
        int areaIdSeasonShift,
        u16 *dest);
    extern void GFL_HeapFree(void *heap);

#pragma endregion

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------ DETERMINE BATTLE BG LIGHTING --------------------------------------
        --------------------------------------------------------------------------------------------------

        This is a helper function that determines what lighting to use for battles. For indoor battles where
        we still want to use the lightning, such as Battle Company, we will use this function.

    */
}

// struct ZoneData
// {
//     char MapType;
//     u8 NPCInfoCacheIdx;
//     u16 AreaID;
//     u16 MatrixID;
//     u16 ScriptsID;
//     u16 LevelScriptsID;
//     u16 TextsID;
//     u16 BGMSpr;
//     u16 BGMSum;
//     u16 BGMAut;
//     u16 BGMWin;
//     u16 EncID;
//     u16 EntitiesID;
//     u16 ParentZoneID;
//     u16 LocNameInfo;
//     u16 EnvFlags;
//     u16 Flags1BattleBGMapTransition;
//     u16 MatrixCamBounds;
//     u16 NameIcon;
//     int FlyX;
//     int FlyY;
//     int FlyZ;
// };

// struct ZoneDataSystem
// {
//     void *ZoneDataArc;
//     ZoneData CurrentZone;
//     u16 CurrentZoneID;
//     __int16 _padCurrentZoneID;
//     void *FogIndex;
//     void *StaticLights;
//     u16 FogIndexSize;
//     u8 StaticLightsSize;
//     u8 FlashIndexSize;
//     void *FlashIndex;
//     u8 EnableVersionSpecificZone[3];
//     u8 EnableVersionSpecificArea[3];
//     u16 Padding;
// };

// extern ZoneDataSystem *g_ZoneDataSystem;
// extern int GetVersionedMapChangeZoneNum(int zoneNum);

// extern "C" int THUMB_BRANCH_GetZoneStaticLightDataIndex(u16 zoneId)
// {
//     int v1;                         // r4
//     int v2;                         // r0
//     int v3;                         // r1
//     unsigned __int16 *StaticLights; // r3

//     v1 = 0xFFFFFFF;
//     v2 = GetVersionedMapChangeZoneNum(zoneId);
//     v3 = 0;
//     k::Printf("\nGetting Static Light Data Index for Zone ID %d (Versioned to %d)", zoneId, v2);
//     if (g_ZoneDataSystem->StaticLightsSize)
//     {
//         StaticLights = (unsigned short *)g_ZoneDataSystem->StaticLights;
//         while (v2 != StaticLights[2 * v3])
//         {
//             if (++v3 >= g_ZoneDataSystem->StaticLightsSize)
//             {
//                 return v1;
//             }
//         }
//         return StaticLights[2 * v3 + 1];
//     }
//     return v1;
// };

enum BtlType
{
    BtlType_Wild = 0x0,
    BtlType_Trainer = 0x1,
    BtlType_Facility = 0x2,
    BtlType_Online = 0x3,
    BtlType_Demo = 0x4,
    BtlType_Max = 0x5,
};

enum BattleStyle
{
    BTL_STYLE_SINGLE = 0x0,
    BTL_STYLE_DOUBLE = 0x1,
    BTL_STYLE_TRIPLE = 0x2,
    BTL_STYLE_ROTATION = 0x3,
};

struct SWAN_ALIGNED(4) BtlvEffect
{
    BattleStyle battleStyle;
    BtlType battleType;
    _DWORD battleBGID;
    _DWORD PlayerBattlePedestalID;
    u8 FieldLightIndex;
    u8 AreaIDSeasonShift;
    __int16 ZoneID;
    u8 Hour;
    u8 Minute;
    char field_16;
    char field_17;
    u16 trType[4];
    _DWORD IsPartnerBattle;
    void *btlvScu;
    void *mainModule;
    _WORD pokestar;
    _WORD pokestarField;
    _DWORD pwtFinal;
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

struct 	PokestarEventReactionData	 {s16 my_message;s16 enemy_message;s16 select_enemy_waza;s16 visual_effect;s16 reaction_point;s16 padding;};

struct 	PokestarEnemyPoke	 {s16 monsno;s16 sex;s16 level;s16 etc;};

struct 	PokestarEventData	 {s16 start_turn;s16 flag_provision;s16 situ_provision;s16 situ_provision_data;s16 bias;s16 point;s16 talk_msg[2][10];s16 stage_cast[10];PokestarEventReactionData reaction[4];};

struct 	PokestarScenario	 {s16 senario_no;s16 category;s16 difficult;s16 pokenum_limit;s16 director;s16 turn_max;s16 best_turn;s16 success_event;s16 win_provision;s16 poke_provision[2];s16 waza_provision;s16 trtype[4];s16 mytype[2];s16 battle_field;s16 battle_bgm;s16 win_bgm;s16 lose_bgm;s16 strange_bgm;s16 enemy_rank;s16 bg_change[3][2];PokestarEnemyPoke enemy_poke[6];s16 select_msg[2][9];s16 situation_msg[2][6];s16 turn_msg[2][20];PokestarEventData event[12];};


extern void* GFL_HeapAllocate(HeapID heapId, u32 size, b32 calloc, const char *sourceFile, u16 lineNo);
extern unsigned int BtlvEffect_GetPWTFinal(void *a1);
extern unsigned int BtlvEffect_GetRecordedBattleType(void *a1);
extern PokestarScenario* MainModule_GetPokestarScenario(void *a1);

// extern "C" BtlvEffect *THUMB_BRANCH_SAFESTACK_BtlvEffect_Create(
//     int a1,
//     int a2,
//     BattleFieldStatus *a3,
//     int a4,
//     u16 *a5,
//     void *a6,
//     void *a7,
//     __int16 a8)
// {
//     BtlvEffect *v9;       // r4
//     u32 BattleBGID;       // r0
//     int BattlePedestalID; // r1
//     int v12;              // r1
//     int i;                // r2
//     u16 v14;              // r1
//     BtlvEffect *v15;      // r0

//     k::Printf("\nBtlvEffect_Create called with Battle Style %d, Battle Type %d, IsPartnerBattle %d, AreaIDSeasonShift %d",
//               a1,
//               a2,
//               a4,
//               a8);
//     v9 = (BtlvEffect*)GFL_HeapAllocate((a8 & 0x7FFF | 0x8000), 0x34u, 0, "btlv_effect.c", 0x107u);
//     k::Printf("\nBtlvEffect_Create: Allocated BtlvEffect at %p", v9);
//     v9->battleStyle = (BattleStyle)a1;
//     v9->battleType = (BtlType)a2;
//     BattleBGID = a3->BattleBGID;
//     BattlePedestalID = a3->BattlePedestalID;
//     a3 = (a3 + 8);
//     v9->battleBGID = BattleBGID;
//     v9->PlayerBattlePedestalID = BattlePedestalID;
//     v12 = a3->BattlePedestalID;
//     *&v9->FieldLightIndex = a3->BattleBGID;
//     *&v9->Hour = v12;
//     v9->IsPartnerBattle = a4;
//     v9->btlvScu = a7;
//     v9->mainModule = a6;
//     v9->pwtFinal = BtlvEffect_GetPWTFinal(a6);
//     k::Printf("\nBtlvEffect_Create: Set Battle Style to %d, Battle Type to %d, IsPartnerBattle to %d, PWT Final to %d",
//               v9->battleStyle,
//               v9->battleType,
//               v9->IsPartnerBattle,
//               v9->pwtFinal);
//     v9->pokestar = BtlvEffect_GetRecordedBattleType(a6);
//     k::Printf("\nBtlvEffect_Create: Recorded Battle Type (Pokestar Type) is %d", v9->pokestar);
//     k::Printf("\nBtlvEffect_Create: Set Battle BG ID to %d, Pedestal ID to %d, Field Light Index to %d, Hour to %d, PWT Final to %d, Pokestar Type to %d",
//               v9->battleBGID,
//               v9->PlayerBattlePedestalID,
//               v9->FieldLightIndex,
//               v9->Hour,
//               v9->pwtFinal,
//               v9->pokestar);
//     if (v9->pokestar)
//     {
//         v9->pokestarField = MainModule_GetPokestarScenario(a6)->battle_field;
//     }
//     for (i = 0; i < 4; ++i)
//     {
//         v14 = a5[i];
//         v15 = (v9 + 2 * i);
//         v15->trType[0] = v14;
//     }
//     k::Printf("\nBtlvEffect_Create: Set Trainer Types to %d, %d, %d, %d",
//               v9->trType[0],
//               v9->trType[1],
//               v9->trType[2],
//               v9->trType[3]);
//     return v9;
// };

extern "C" void THUMB_BRANCH_SAFESTACK_sub_2019830(u16 zoneId, int hours, int minutes, int a4, int areaIdSeasonShift, u16 *a6, HeapID heapId)
{
    int v8;                       // r7
    FieldLightData *v9;           // r4
    u16 v10;                      // r0
    int ZoneStaticLightDataIndex; // r0
    int zoneIdToUse;
    u16 v12;            // r6
    u16 AreaID;         // r0
    HeapID v14;         // r4
    u16 v15;            // r0
    AreaData *v16;      // r5
    u16 LightsID;       // r0
    int v18;            // [sp+4h] [bp-1Ch]
    u32 pEntryCount[6]; // [sp+8h] [bp-18h] BYREF

    // k::Printf("\nzoneID is %d", zoneId);

    if (GetBackgroundsSetting())
    {
        // k::Printf("\nAnimated Battle Backgrounds Enabled - Using Outdoor Lighting");
        zoneIdToUse = (IsInArray(zoneId)) ? 445 : zoneId; // Checks to see if we're overwriting the lighting
    }
    else
    {
        zoneIdToUse = zoneId;
    }
    // k::Printf("\nzoneIDToUse is %d and original zone is %d", zoneIdToUse);
    v8 = 60 * minutes;
    v9 = 0;
    v18 = 3600 * hours;

    /* Redundant Check for Postion */
    // if (zoneId == 437){
    //     PlayerState* playerstate = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
    //     VecFx32* vec = PlayerState_GetWPos(playerstate);
    //     //k::Printf("\nx is %d\ny is %d\nz is %d\n", vec->x, vec->y, vec->z);
    // }

    if (a4)
    {
        v10 = sub_201991C(a4);
        v9 = Normalize060File(61, v10, pEntryCount, (HeapID)(heapId & 0x7FFF | 0x8000));
    }
    if (!v9)
    {
        ZoneStaticLightDataIndex = GetZoneStaticLightDataIndex(zoneIdToUse);
        if (ZoneStaticLightDataIndex != 0xFFFFFFF)
        {
            v9 = Normalize060File(81, ZoneStaticLightDataIndex, pEntryCount, (HeapID)(heapId & 0x7FFF | 0x8000));
        }
    }
    if (!v9)
    {
        v12 = 0;
        AreaID = ZoneData_GetAreaID(zoneIdToUse);
        if (AreaData_HasSeasons(zoneIdToUse))
        {
            v12 = areaIdSeasonShift;
        }
        v14 = (HeapID)(heapId & 0x7FFF | 0x8000);
        v15 = ZoneData_GetAreaID(zoneIdToUse);
        v16 = AreaData_Create(v14, v15, v12);
        LightsID = AreaData_GetLightsID(v16);
        v9 = Normalize060File(60, LightsID, pEntryCount, v14);
        AreaData_Free(v16);
    }
    sub_201998C(v9, pEntryCount[0], v8 + v18, areaIdSeasonShift, a6);
    GFL_HeapFree(v9);
}