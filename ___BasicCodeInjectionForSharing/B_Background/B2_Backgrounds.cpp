#include "kPrint.h"
#include "swantypes.h"
#include "zoneIdToBackground.h"

#define DEBUGGING_BACKGROUNDS true
#define ANIMATED_BACKGROUNDS_ENABLED true

#pragma region defintions
extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

// uses ESDB_15.yml

extern "C"
{
    struct EventWorkSave
    {
        u16 Works[431];
        u8 FlagBytes[383];
        u8 CanRespawnHiddenItems;
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

    extern EventWorkSave *GameData_GetEventWork(void *gameData);
    extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
    extern int howManyPokesAreAbleToFight(PokeParty *pPartyBlk);
    extern PokeParty *GameData_GetParty(void *data);

    u32 GetBackgroundsSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16435);
        return *lvl_cap_ptr;
    }

    //  Undella Town Hugh
    // 60 Aspertia Overlook 
    // 64 Route 20 Benga 
    // 65 Flocessy Rnanch 
    // 67 Alder's House 
    //  
    // 165 Colress's Room
    // 166 Ghetsis Room
    // 168 Deep Giant Chasm 
    // 169 Victory Road Entrance
    // 172 Victory Road Hugh 
    // 177 SHauntal Room 
    // 178 Marshal Room 
    // 179 Caitlyn Room 
    // 180 Grimsley Room 
    // 181 Iris Room 
    // 211 Virbank Dock Aphex
    // 212 Liberty Garden Aphex
    // 213 Undella Town Hugh

    const int CompletedBackgroundModels[67] = {
        9, // 0 nothing
        24,  // 1 AspertiaOverlook
        27,  // 2 Route20_West_benga
        28,  // 3 FlocessyRanch_South
        30,  // 4 AldersHouse
        32,  // 5 AspertiaClassRoom
        33,  // 6 AspertiaGymTrainerA
        34,  // 7 AspertiaGymTrainerB
        35,  // 8 AspertiaGymLeader
        37,  // 9 Virbank_gate
        45,  // 10 virbank_gym_trainers
        46,  // 11 VirbankGymLeader
        47,  // 12 virbank_brycen
        49,  // 13 PokeStarStudios_Interior
        50,  // 14 castelia_fountain
        51,  // 15 castelia_cafe
        52,  // 16 CasteliaInterior_RedTile
        53,  // 17 CasteliaBuilding_PurpleTile
        57,  // 18 castelia_backalley
        58,  // 19 castelia_sewers_grunt_battle
        59,  // 20 castelia_gardens
        65,  // 21 CasteliaGymTrainers
        66,  // 22 CasteliaGymLeader
        9,  // 23 RelicCastle_Interior
        73,  // 24 nimbasa_city
        75,  // 25 Nimbasa__big_stadium
        76,  // 26 Route5Streets
        85,  // 27 NimbasaOldGym_INPUT THE ASSETS
        86,  // 28 NimbasaGymTrainers
        87,  // 29 NimbasaGymLeader
        90,  // 30 DriftveilCity_PlasmaSanctuary_Exterior
        93,  // 31 driftveil_city_norman
        96,  // 32 driftveil_gym_generic
        97,  // 33 driftveil_gym_clay
        98,  // 34 RelicSanctum_volcaronas_room
        99,  // 35 PWTExterior__pwt_battle_bros
        102,  // 36 PlasmaFrigate_Deck_PWT
        104,  // 37 chargestone_entrance
        105,  // 38 chargestone_wattson
        110,  // 39 celestial_tower_rooftop
        111,  // 40 TwistMountain_Entrance
        113,  // 41 mistralton_gym_skyla
        115,  // 42 ReversalMountain_W2
        213,  // 43 UndellaTownHugh
        121,  // 44 abundant_shrine
        122,  // 45 MarineTube
        123,  // 46 humilau_city_streets
        129,  // 47 HumilauGymLeader
        133,  // 48 route_21_frigate
        138,  // 49 frigate_zinzollin_first
        140,  // 50 LacunosaTown_Streets
        141,  // 51 route_12
        142,  // 52 village_bridge_bridge
        153,  // 53 opelucid_gym_W2
        162,  // 54 Frozen_giant_chasm_ship
        164,  // 55 frigate_zinzollin_final
        165,  // 56 frigate_colress
        166,  // 57 frigate_shadow_triad
        168,  // 58 giant_chasm_kyurem
        172,  // 59 victory_road_final
        177,  // 60 POkemonLeague_Shauntel
        178,  // 61 pokemonLeague_marshall
        179,  // 62 PokemonLeague_caitlin
        180,  // 63 grimsleys_room_pokemonleague
        212,  // 64 liberty_island_aphex
        211,  // 65 Virbank_pier_AphexVersion
        214,  // 66 SM9_Rotom_Room
};

    u32 GetBackgroundsSetting_ForDebugging()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16436);
        return CompletedBackgroundModels[*lvl_cap_ptr];
    }

    u32 GetBackgroundSeason()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16437);
        return *lvl_cap_ptr;
    }

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

    /* 
    
    if (a1->battleBGID >= 80){
        if (a1->battleBGID >= 160){
            HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 4, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
        }
        else {
            HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 3, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
        }
    }
    else {
        HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 0, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
    }
    
    HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 0, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));

    */
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

    // Season THUMB_BRANCH_GameData_GetSeason(void *gameData)
    // {
    //     return (Season)GetBackgroundSeason();
    //     // return *(Season *)((u8 *)gameData + 0x1C8);
    // }
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

#if DEBUGGING_BACKGROUNDS
        fieldStatus->BattleBGID = GetBackgroundsSetting_ForDebugging();
        return;
#endif
        if (GetBackgroundsSetting())
        {
            return;
        }
        int random;
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nModifying Field Status for Trainer ID: %d", foe1TrID);
        // #endif
        int zoneId = fieldStatus->ZoneID;
        DayPart dayperiod = GetRealTimeDayPeriod((Season)fieldStatus->Season);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the GetRealTimeDayPeriod function");
        // #endif
        // Aspertia Gym Trainer 1
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 171)
        {
            fieldStatus->BattleBGID = 30;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Aspertia Gym Trainer 1 check");
        // #endif
        // Aspertia Gym Trainer 2
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 172)
        {
            fieldStatus->BattleBGID = 31;
            return;
        }

        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Aspertia Gym Trainer 2 check");
        // #endif
        // Cheren
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 156)
        {
            fieldStatus->BattleBGID = 32;
            return;
        }

        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Cheren check");
        // #endif
        // Roxie
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 157)
        {
            fieldStatus->BattleBGID = 42;
            fieldStatus->Hour = 23;
            fieldStatus->Minute = 0;
            fieldStatus->ZoneID = 457;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Roxie check");
        // #endif
        // // Colress PWT
        // if (foe1TrID == 739)
        // {
        //     fieldStatus->BattleBGID = 41;
        //     fieldStatus->Hour = 23;
        //     fieldStatus->Minute = 0;
        //     fieldStatus->ZoneID = 457;
        //     return;
        // }

        // Misty
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 765)
        {
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nMisty Battle Background Triggered");
            // #endif
            if (dayperiod == MORNING)
            {
                fieldStatus->BattleBGID = 35;
            }
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            if (dayperiod == DAY)
            {
                fieldStatus->BattleBGID = 35;
            }
            if (dayperiod == SUNSET)
            {
                fieldStatus->BattleBGID = 36;
            }
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            if (dayperiod == EVENING)
            {
                fieldStatus->BattleBGID = 37;
            }
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            if (dayperiod == NIGHT)
            {
                fieldStatus->BattleBGID = 37;
            }
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Misty check");
        //         #endif
        // Surge
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 766)
        {
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nSurge Battle Background Triggered");
            // #endif
            if (dayperiod == MORNING)
            {
                fieldStatus->BattleBGID = 51;
            }
            if (dayperiod == DAY)
            {
                fieldStatus->BattleBGID = 51;
            }
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            if (dayperiod == SUNSET)
            {
                fieldStatus->BattleBGID = 52;
            }
            if (dayperiod == EVENING)
            {
                fieldStatus->BattleBGID = 53;
            }
            if (dayperiod == NIGHT)
            {
                fieldStatus->BattleBGID = 53;
            }
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        // k::Printf("\nMade it past the Surge check");
        // #endif

        // Benga
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 773)
        {
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nBenga Battle Background Triggered");
            // #endif
            fieldStatus->BattleBGID = 49;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Benga check");
        // #endif
        // Fisherman Andrew and Hubert
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 210)
        {
            random = TrainerData_GetParam(foe1TrID, TR_CLASS);
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nFisherman Battle Background Triggered");
            // #endif
            fieldStatus->BattlePedestalID = 6;
            return;
        }
        
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 211)
        {
            fieldStatus->BattlePedestalID = 6;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Fisherman check");
        // #endif
        // Elesa
        if (foe1TrID == 153)
        {
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nElesa Battle Background Triggered");
            // #endif
            fieldStatus->BattleBGID = 70;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Elesa check");
        // #endif
        // Erika
        // if (foe1TrID == 767)
        // {
        //     // #if DEBUGGING_BACKGROUNDS
        //     //             k::Printf("\nErika Battle Background Triggered");
        //     // #endif
        //     fieldStatus->BattleBGID = 67;
        //     return;
        // }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Erika check");
        // #endif
        // Janine
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 768)
        {
            if (zoneId == 548){
                fieldStatus->BattleBGID = 75;
                return;
            }
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nJanine Battle Background Triggered");
            // #endif
        }
        // #if    DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Janine check");
        // #endif
        // Rood
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 346 && zoneId == 96)
        {
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nRood Battle Background Triggered");
            // #endif
            fieldStatus->BattleBGID = 74;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nMade it past the Rood check");
        // #endif
        // Clay
        random = TrainerData_GetParam(foe1TrID, TR_CLASS);
        if (foe1TrID == 158)
        {
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nClay Battle Background Triggered");
            // #endif
            fieldStatus->BattleBGID = 82;
            return;
        }
        // #if DEBUGGING_BACKGROUNDS
        // k::Printf("\nMade it past the Clay check");
        // #endif
        return;
    }

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
                                       // #if DEBUGGING_BACKGROUNDS
                                       //         k::Printf("\nBtlSetup_SetTrainerLocal called with Foe1 ID: %d, Foe2 ID: %d, Ally ID: %d, Style: %d", foe1TrId, foe2TrId, allyTrId, style);
                                       // #endif
        v16 = allyTrId;
        m_GameData = encSys->m_GameData;
        BtlSetup_Reset(setup);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nReset Battle Setup");
        // #endif

        SaveBtlFieldStatus(&fieldStatus, encSys->m_GameData, encSys->m_Field);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSaved Battle Field Status with BG ID: %d, Pedestal ID: %d, Zone ID: %d", fieldStatus.BattleBGID, fieldStatus.BattlePedestalID, fieldStatus.ZoneID);
        // #endif
        Param = TrainerData_GetParam(foe1TrId, TR_CLASS);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nGot Trainer Class: %d", Param);
        // #endif
        btlPedestalId = GetTrainerClassBattlePedestal(Param);
        if (btlPedestalId != 20)
        {
            fieldStatus.BattlePedestalID = btlPedestalId;
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSet Battle Pedestal ID to: %d", fieldStatus.BattlePedestalID);
        // #endif
        trClass = TrainerData_GetParam(foe1TrId, TR_CLASS);
        fieldStatus.BattleBGID = CheckOverridenTrainerBattleBG(trClass, fieldStatus.BattleBGID);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSet Battle BG ID to: %d", fieldStatus.BattleBGID);
        // #endif
        modifyFieldStatus(&fieldStatus, foe1TrId, style);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nModified Field Status to BG ID: %d, Pedestal ID: %d", fieldStatus.BattleBGID, fieldStatus.BattlePedestalID);
        // #endif
        if (style <= BTL_STYLE_ROTATION)
        {
            if (style == BTL_STYLE_SINGLE)
            {
                if (foe2TrId)
                {
                    // #if DEBUGGING_BACKGROUNDS
                    //                     k::Printf("\nSetting up 1v2 Battle");
                    // #endif
                    BtlSetup_SetTrainer1v2(setup, m_GameData, &fieldStatus, foe1TrId, foe2TrId, heapId);
                }
                else
                {
                    // #if DEBUGGING_BACKGROUNDS
                    //                     k::Printf("\nSetting up 1v1 Single Battle");
                    // #endif
                    BtlSetup_SetTrainer1v1Single(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                }
            }
            else
            {
                if (style == BTL_STYLE_DOUBLE && allyTrId)
                {
                    // #if DEBUGGING_BACKGROUNDS
                    //                     k::Printf("\nSetting up 2v2 Battle");
                    // #endif
                    BtlSetup_SetTrainer2v2(setup, m_GameData, &fieldStatus, allyTrId, foe1TrId, foe2TrId, heapId);
                }
                else
                {
                    if (style == BTL_STYLE_DOUBLE)
                    {
                        if (howManyPokesAreAbleToFight(GameData_GetParty(m_GameData)) < 2)
                        {
                            BtlSetup_SetTrainer1v1Single(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                        else
                        {
                            BtlSetup_SetTrainer1v1Double(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                    }

                    if (style == BTL_STYLE_TRIPLE)
                    {
                        if (howManyPokesAreAbleToFight(GameData_GetParty(m_GameData)) < 3)
                        {
                            BtlSetup_SetTrainer1v1Single(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                        else
                        {
                            BtlSetup_SetTrainer3v3(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                    }
                    if (style == BTL_STYLE_ROTATION)
                    {
                        if (howManyPokesAreAbleToFight(GameData_GetParty(m_GameData)) < 3)
                        {
                            BtlSetup_SetTrainer1v1Single(setup, m_GameData, &fieldStatus, foe1TrId, heapId);
                        }
                        else
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
    void THUMB_BRANCH_SAFESTACK_SaveBtlFieldStatus(BattleFieldStatus *status, void *gameData, void *field)
    {
        u16 PlayerStateZoneID;  // r4
        TileType TileTypeUnder; // r0
        int TileClass;          // r0
        void *player;           // [sp+0h] [bp-28h]
        RTCTime time;           // [sp+4h] [bp-24h] BYREF
                                // #if DEBUGGING_BACKGROUNDS
                                //         k::Printf("\nSaveBtlFieldStatus called");
                                // #endif
        PlayerStateZoneID = Field_GetPlayerStateZoneID(field);
        player = Field_GetPlayer(field);
        status->BattleBGID = GetZoneBattleBGID(PlayerStateZoneID);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSaveBtlFieldStatus: Initial Battle BG ID from Zone ID %d is %d",
        //                   PlayerStateZoneID,
        //                   status->BattleBGID);
        // #endif
        if (!GetBackgroundsSetting())
        {
            status->BattleBGID = ZoneIdToBackgroundID[PlayerStateZoneID];
        }
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSaveBtlFieldStatus: Modified Battle BG ID is %d", status->BattleBGID);
        // #endif
        TileTypeUnder = FieldPlayer_GetTileTypeUnder(player);
        TileClass = GetTileClass(TileTypeUnder);
        status->BattlePedestalID = GetTileEncountType(TileClass);
        status->ZoneID = PlayerStateZoneID;
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSaveBtlFieldStatus: Set Battle Pedestal ID to %d", status->BattlePedestalID);
        // #endif
        RTC_GetCachedTime(&time);
        status->Hour = time.Hour;
        status->Minute = time.Minute;
        status->BtlWeather = ConvFieldWeatherToBtl(field);
        status->Season = GameData_GetSeason(gameData);
        // #if DEBUGGING_BACKGROUNDS
        //         k::Printf("\nSaveBtlFieldStatus: Set Time to %02d:%02d, Weather to %d, Season to %d",
        //                   status->Hour,
        //                   status->Minute,
        //                   status->BtlWeather,
        //                   status->Season);
        // #endif


        if (!GetBackgroundsSetting())
        {
            // #if DEBUGGING_BACKGROUNDS
            //             k::Printf("\nSaveBtlFieldStatus: Checking for position based background changes");
            // #endif
            if (PlayerStateZoneID == 446    // Route 20
                || PlayerStateZoneID == 445 // Flocessy Ranch
                //|| PlayerStateZoneID == 385 // Lostlorn Forest
                || PlayerStateZoneID == 551 // Route 4
                || PlayerStateZoneID == 383 // Route 16
                || PlayerStateZoneID == 329 // Route 5
            )
            {
                // #if DEBUGGING_BACKGROUNDS
                //                 k::Printf("\nSaveBtlFieldStatus: Position based background change triggered");
                // #endif
                PlayerState *playerstate = GameData_GetPlayerState(gameData);
                VecFx32 *vec = PlayerState_GetWPos(playerstate);
                VecFx32 *print;

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
                if (PlayerStateZoneID == 329 && vec->z <= 28147712)
                {
                    status->BattleBGID = 63;
                }

                // Route 16
                if (PlayerStateZoneID == 383 && vec->x >= 31031296 && vec->z <= 28672000)
                {
                    status->BattleBGID = 65;
                }

                // // Lostlorn Forest
                // if (PlayerStateZoneID == 385 && vec->z <= 1925120)
                // {
                //     status->BattleBGID = 67;
                // }
            }
        }

        status->BattleBGID = GetBackgroundsSetting_ForDebugging();
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

    extern u32 PokeParty_GetParam(PartyPkm *pPkm, int field, void *extra);
    extern PartyPkm *PokeParty_GetPkm(PokeParty *party, int slot);
    extern u32 PokeParty_GetPkmCount(PokeParty *pPartyBlk);

    /* Some fuck ass function only called in EventTrainerEye_CheckAll to count the number of Pokemon that can battle */
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
#pragma endregion
}
