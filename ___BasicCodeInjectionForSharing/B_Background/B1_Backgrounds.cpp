#include "swantypes.h"
#include "kPrint.h"
#include "../settings.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

#define ANIMATED_BACKGROUNDS_ENABLED 0

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
    489
};

bool IsInArray(int value){
    for (int i = 0; i < 1; i++){
        if (ZoneIDsNowWithLighting[i] == value){
            return true;
        }
    };
    return false;
}

extern "C"
{
     
    enum 	PlayerExState	 {FLD_PLAYER_EXSTATE_NONE = 0x0,FLD_PLAYER_EXSTATE_CYCLING = 0x1,FLD_PLAYER_EXSTATE_SURF = 0x2,FLD_PLAYER_EXSTATE_DIVE = 0x3,};

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

    struct 	VecFx32	 {fx32 x;fx32 y;fx32 z;};

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
    struct 	FieldPosition	 {VecFx32 Vector;RailPosition Rail;};
    struct 	ZoneSpawnInfo	{u32 ChangeType;u16 ZoneID;u16 WarpID;u16 WarpDir;u16 PosWeightBits;b32 IsRail;FieldPosition Pos;};
        extern int GetTileClass(TileType result);
    extern TileType FieldPlayer_GetTileTypeUnder(void *player);
    extern void RTC_GetCachedTime(RTCTime *time);
    extern int GetTileEncountType(int tileClass);
    extern unsigned int GetZoneBattleBGID(u16 a1);
    extern void *Field_GetPlayer(void *field);
    extern u16 Field_GetPlayerStateZoneID(void *field);
    extern int ConvFieldWeatherToBtl(void *field);
    extern int GameData_GetSeason(void *gameData);
    extern PlayerState * GameData_GetPlayerState(void *gameData);
    extern VecFx32 * PlayerState_GetWPos(PlayerState *playerState);
    extern void vecfx_normalize(const VecFx32 *vec, VecFx32 *normalized);
    extern void  FieldPlayer_GetWPos(void *player, VecFx32 *dest);
    struct AreaData {u16 Buildings;u16 Textures;u8 SrtAnime;u8 PatAnime;u8 IsExterior;u8 Lights;u8 EdgeColorTableId;u8 BbdMdlColors;};
    typedef u16 GXColor;
    struct 	VecFx16	 {__int16 x;__int16 y;__int16 z;};
    struct 	FieldLightInfo	 {u16 DayPart;s16 MinutesOffs;u8 LightIsEnabled[4];GXColor LightColors[4];VecFx16 LightPositions[4];GXColor GXDiffuse;GXColor GXAmbient;GXColor GXSpecular;GXColor GXEmission;GXColor GXFogColor;GXColor ClearColor;};
    struct 	FieldLightData	 {FieldLightInfo Entries[16];};
    extern int sub_201991C(int a1);
    extern FieldLightData* Normalize060File(int arcId, u16 datId, u32 *pEntryCount, HeapID heapId);
    extern int GetZoneStaticLightDataIndex(u16 zoneId);
    extern b32 AreaData_HasSeasons(u16 areaID);
    extern u32 ZoneData_GetAreaID(int zoneId);
    extern AreaData* AreaData_Create(HeapID heapId, u16 areaId, u16 areaSeasonShift);
    extern int  AreaData_GetLightsID(AreaData *ad);
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
    void THUMB_BRANCH_sub_2019830(u16 zoneId, int hours, int minutes, int a4, int areaIdSeasonShift, u16 *a6, HeapID heapId)
    {
        int v8;                       // r7
        FieldLightData *v9;           // r4
        u16 v10;                      // r0
        int ZoneStaticLightDataIndex; // r0
        int zoneIdToUse;
        u16 v12;                      // r6
        u16 AreaID;                   // r0
        HeapID v14;                   // r4
        u16 v15;                      // r0
        AreaData *v16;                // r5
        u16 LightsID;                 // r0
        int v18;                      // [sp+4h] [bp-1Ch]
        u32 pEntryCount[6];           // [sp+8h] [bp-18h] BYREF

        //k::Printf("\nzoneID is %d", zoneId);
        
        if (ANIMATED_BACKGROUNDS_ENABLED){
            zoneIdToUse = (IsInArray(zoneId)) ? 445 : zoneId; // Checks to see if we're overwriting the lighting
        } else {
            zoneIdToUse = zoneId;
        }
        //k::Printf("\nzoneIDToUse is %d", zoneIdToUse);
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
}