#include "kPrint.h"
#include "swantypes.h"

#define DEBUGGING_BACKGROUNDS true
#define ANIMATED_BACKGROUNDS_ENABLED true

#pragma region defintions
extern u32 g_GameBeaconSys;

STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

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

    enum BattleStyle : u32
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

    // enum HeapID : unsigned __int16 {HEAPID_SYSTEM = 0x0,HEAPID_USER = 0x1,HEAPID_GAMESYSTEM = 0x3,HEAPID_GAMEEVENT = 0x4,HEAPID_TRIAL_HOUSE = 0x5,HEAPID_SAVEDATA = 0x7,HEAPID_NET = 0x8,HEAPID_DEVICE_ALLOC = 0x9,HEAPID_STARTMENU = 0xB,HEAPID_DLP = 0xC,HEAPID_FIELDMAP = 0x15,HEAPID_TITLE = 0x16,HEAPID_POKELIST = 0x17,HEAPID_NAMEIN = 0x1E,HEAPID_IRC_BATTLE_MENU = 0x1F,HEAPID_TRAINER_CARD = 0x26,HEAPID_MUSICAL_EVENT = 0x2C,HEAPID_MUSICAL_DRESSUP = 0x2D,HEAPID_MUSICAL = 0x2E,HEAPID_DEBUG_GENDER_SELECT = 0x39,HEAPID_MICTEST = 0x49,HEAPID_FIELD_PARTICLE = 0x50,HEAPID_BATTLE_RETURN = 0x52,HEAPID_GAMESYNC = 0x67,HEAPID_DEMO3D = 0x6C,HEAPID_INTRO = 0x6F,HEAPID_FIELD_MENU = 0x70,HEAPID_BATTLE_LOAD = 0x76,HEAPID_CDEMO = 0x7F,HEAPID_SAVEDATA_DELETE = 0x81,HEAPID_FIELD_CLACT = 0x89,HEAPID_FIELD_WEATHER = 0x92,HEAPID_FIELD_PLACE_NAME = 0x93,HEAPID_FIELD_SCENEAREA = 0x96,HEAPID_HEAD_MASK = 0x7FFF,HEAPID_TAIL_BIT = 0x8000,};

    enum	BtlType	 : u32 {BtlType_Wild = 0x0,BtlType_Trainer = 0x1,BtlType_Facility = 0x2,BtlType_Online = 0x3,BtlType_Demo = 0x4,BtlType_Max = 0x5,};

    enum	BtlSetupFlag     {BTL_SETUP_FLAG_FISHING = 0x1,BTL_SETUP_FLAG_PC_NAME_DISCOVERED = 0x2,BTL_SETUP_FLAG_LEGENDARY = 0x4,BTL_SETUP_FLAG_ROAMING = 0x8,BTL_SETUP_FLAG_DREAM_WORLD = 0x10,BTL_SETUP_FLAG_DOUBLE = 0x20,BTL_SETUP_FLAG_ALL_BOXES_FULL = 0x40,BTL_SETUP_FLAG_STATIC_ENCOUNTER = 0x80,BTL_SETUP_FLAG_NO_AUTO_DEFEAT = 0x100,BTL_SETUP_FLAG_NPOKE = 0x2000,BTL_SETUP_FLAG_PHENOMENON = 0x4000,BTL_SETUP_FLAG_MUSHROOM = 0x8000,BTL_SETUP_FLAG_NO_CATCH_KYUREM = 0x10000,};

	struct BtlvEffect {BattleStyle battleStyle;BtlType battleType;_DWORD battleBGID;_DWORD PlayerBattlePedestalID;u8 FieldLightIndex;u8 AreaIDSeasonShift;__int16 ZoneID;u8 Hour;u8 Minute;char field_16;char field_17;u16 trType[4];_DWORD IsPartnerBattle;void *btlvScu;void *mainModule;_WORD pokestar;_WORD pokestarField;_DWORD pwtFinal;};
    struct	VecFx16 {__int16 x;__int16 y;__int16 z;};

    struct Light
    {
        VecFx16 Direction;
        __int16 Color;
    };
    struct 	BtlvEffectSetupParam {BattleStyle battleStyle;BtlType btlType;BattleFieldStatus bfs;u16 tr_type[4];bool isMultiBattle;void *scu;void *mainModule;u16 pokestar;u16 pokestar_field;bool pwt_final;};
    struct 	PokestarEventReactionData	 {s16 my_message;s16 enemy_message;s16 select_enemy_waza;s16 visual_effect;s16 reaction_point;s16 padding;};

    struct 	PokestarEnemyPoke	 {s16 monsno;s16 sex;s16 level;s16 etc;};
    struct 	PokestarEventData	 {s16 start_turn;s16 flag_provision;s16 situ_provision;s16 situ_provision_data;s16 bias;s16 point;s16 talk_msg[2][10];s16 stage_cast[10];PokestarEventReactionData reaction[4];};

    struct 	PokestarScenario {s16 senario_no;s16 category;s16 difficult;s16 pokenum_limit;s16 director;s16 turn_max;s16 best_turn;s16 success_event;s16 win_provision;s16 poke_provision[2];s16 waza_provision;s16 trtype[4];s16 mytype[2];s16 battle_field;s16 battle_bgm;s16 win_bgm;s16 lose_bgm;s16 strange_bgm;s16 enemy_rank;s16 bg_change[3][2];PokestarEnemyPoke enemy_poke[6];s16 select_msg[2][9];s16 situation_msg[2][6];s16 turn_msg[2][20];PokestarEventData event[12];};

    struct 	BtlvEffectMain {void *TCBManager;void *field_4;void *tcbs[32];int tcbCallback[32];int tcbGroups[32];void *EffVM;void *PalAnm;void *btlvMcss;void *btlvStageHandle;void *btlvFieldHandle;void *btlvCameraHandle;void *clact;void *btlvGauge;void *ballGaugeWork[2];void *btlvTimer;void *btlvBG;void *VTCB;BtlvEffectSetupParam SetupParam;int IsScriptVMRunning;int Flags;HeapID HeapID;__int16 field_1FA;int trainerBGMChangeFlag;int trainerIndex[8];int ShownAbilities[6];_BYTE gap238[8];int CameraMovementType;int IsScreenStateUnchangedThisFrame;int FramesSinceAction;int FramesBeforeCameraIdleMovement;int CameraMovementAnimID;};
    typedef void *(*TCBFunc)(void  *tcb, void *data);
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

    extern EventWorkSave *GameData_GetEventWork(void *gameData);
    extern u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
    extern int howManyPokesAreAbleToFight(PokeParty *pPartyBlk);
    extern PokeParty *GameData_GetParty(void *data);
    extern void*  GFL_HeapAllocate(HeapID heapId, u32 size, b32 calloc, const char *sourceFile, u16 lineNo);
    extern u32 GFL_TCBMgrCalcAllocSize(u32 tcbLimit);
    extern void* GFL_TCBMgrCreate(u32 taskCount, void *mgr);
    extern void* BtlvEffVM_Init(void *tcbMgr, int heapId);
    extern void* PalAnm_Create(HeapID a1);
    extern void PaletteTrans_AutoSet(void *palAnm, int a2);
    extern void sub_2026E30(void *a1, int a2, u32 size, int a4);
    extern void* BtlvMcss_Create(int a1, void *a2, int a3);
    extern unsigned int BtlvEffect_GetRecordedBattleType(void *a1);
    extern int MainModule_GetPokestarScenarioID(void *a1);
    
    int dword_21F3FB0[11] = {0x1010101, 0x1010101, 0x1000101, 0x1010101, 0x1010101, 0x1010100, 0x1010101, 0x1010101, 0x1010101, 0x101, 1};
    extern void sub_21E7210(void *result, int a2);
    extern void* BtlvStage_Create(int a1, int a2, int a3, HeapID a4, int pokestar);
    extern int BtlSetup_IsBattleType(void *a1, BtlSetupFlag mask);
    extern void* GFL_ArcSysReadHeapNew(int arcId, u16 datId, HeapID heapId);
    extern void sub_2019830(u16 zoneId, int hours, int minutes, int a4, int areaIdSeasonShift, u16 *a6, HeapID heapId);
    extern void* BtlvCamera_Create(int a1, HeapID a2);
    extern void GFL_G3DSysLightSet(int index, Light *light);
    extern void* BtlvClAct_Init(void *a1, HeapID a2, int a3);
    extern void* BtlvGauge_Create(void *a1, int a3, HeapID a2);
    extern void* BtlvField_Create(
        int battleType,
        int bgID,
        int SeasonShift,
        HeapID a4,
        int pokestar,
        int pokestarfield,
        int pwtFinal);
    extern void* BtlvTimer_Create(HeapID a2);
    extern void* BtlvBG_12_Create(void* a1, HeapID a2);
    extern void sub_21E9C64(void *a1, int a2, int a3);
    extern void ParticleSys_Init(HeapID a1);
    extern void* GFL_VBlankTCBAdd(TCBFunc callback, void *data, u32 priority);
    extern void PokeVoice_AllocMulti(int handleCount, HeapID heapId);
    extern void GFL_HeapFree(void *heap);
    extern void* MainModule_GetPokestarScriptPtr(void *a1);
    extern void BtlvMcss_SetOrthoMode(void *a1);
    extern void TCBTask_VBlank();
#define g_Effects (*(BtlvEffectMain **)0x21F4280)
#pragma endregion

    u32 GetBackgroundsSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16435);
        return *lvl_cap_ptr;
    }

    void THUMB_BRANCH_SAFESTACK_BtlvEffect_Init(BtlvEffect *a1, void *a2, HeapID a3)
    {
        HeapID heapId;                       // r6
        int adjustedBGID;
        BtlvEffectMain *v5;                  // r0
        BtlvEffectSetupParam *p_SetupParam;  // r2
        BtlvEffectMain *v7;                  // r12
        BtlvEffect *v8;                      // r3
        int v9;                              // r5
        BattleStyle battleStyle;             // r0
        BtlType battleType;                  // r1
        u32 v12;                             // r0
        int PokestarScenarioID;              // r1
        void* btlvMcss; // BtlvMcss *btlvMcss;                  // r0
        int v15;                             // r1
        int AreaIDSeasonShift;               // r5
        _BYTE *HeapNew;                      // r7
        int v18;                             // r1
        void *mainModule; // MainModule *mainModule;              // r0
        int IsBattleType;                    // r0
        void *v21; // BtlvFieldHandle *v21;                // r0
        int RecordedBattleType;              // r0
        PokestarScenario *PokestarScriptPtr; // r0
        int i;                               // r3
        BtlvEffectMain *v25; // BtlvEffectMain *v25;                 // r0
        void *v26; // MainModule *v26;                     // r0
        int v27;                             // r1
        Light light;                         // [sp+18h] [bp-30h] BYREF
        u16 a6;                              // [sp+20h] [bp-28h] BYREF
        
        *(u32 *)&heapId = a3;
        v5 = (BtlvEffectMain *)GFL_HeapAllocate(a3, 0x254u, 1, "btlv_effect.c", 0x15Cu);
        v7 = v5;
         p_SetupParam = &v5->SetupParam;
        g_Effects = v5;

        // v7 = v5;
        // g_Effects = v5;
        // BtlvEffectMain* g_Effects = (BtlvEffectMain*)0x21F4280;


        v8 = a1;
        v9 = 6;
        do
        {
            battleStyle = v8->battleStyle;
            battleType = v8->battleType;
            v8 = (BtlvEffect *)((char *)v8 + 8);
            p_SetupParam->battleStyle = battleStyle;
            p_SetupParam->btlType = battleType;
            p_SetupParam = (BtlvEffectSetupParam *)((char *)p_SetupParam + 8);
            --v9;
        } while (v9);
  

        p_SetupParam->battleStyle = v8->battleStyle;
        v7->HeapID = heapId;
        v12 = GFL_TCBMgrCalcAllocSize(0x20u);
        g_Effects->field_4 = (void *)GFL_HeapAllocate(heapId, v12, 1, "btlv_effect.c", 0x162u);
        g_Effects->TCBManager = GFL_TCBMgrCreate(0x20u, g_Effects->field_4);
        g_Effects->EffVM = BtlvEffVM_Init(g_Effects->TCBManager, *(int *)&heapId);
        g_Effects->PalAnm = PalAnm_Create(heapId);
        PaletteTrans_AutoSet(g_Effects->PalAnm, 1);
        sub_2026E30(g_Effects->PalAnm, 0, 0x200u, *(int *)&heapId);
        sub_2026E30(g_Effects->PalAnm, 1, 0x1E0u, *(int *)&heapId);
        sub_2026E30(g_Effects->PalAnm, 2, 0x200u, *(int *)&heapId);
        sub_2026E30(g_Effects->PalAnm, 3, 0x1E0u, *(int *)&heapId);
        g_Effects->btlvMcss = BtlvMcss_Create(a1->battleStyle, g_Effects->TCBManager, *(int *)&heapId);

        if (BtlvEffect_GetRecordedBattleType(a1->mainModule) == 2)
        {
            PokestarScenarioID = MainModule_GetPokestarScenarioID(a1->mainModule);
            btlvMcss = g_Effects->btlvMcss;
            v15 = *((unsigned __int8 *)dword_21F3FB0 + PokestarScenarioID);
        }
        else
        {
            btlvMcss = g_Effects->btlvMcss;
            v15 = 1;
        }
        sub_21E7210(btlvMcss, v15);
        AreaIDSeasonShift = 0;
        goto Label_StaticBackground;
        if (a1->battleBGID >= 80){
            if (a1->battleBGID >= 160){
                k::Printf("BattleBGID is %d, which is >= 160, so we will adjust it by subtracting 160 and use the appropriate heap.\n", a1->battleBGID);
                adjustedBGID = a1->battleBGID - 160;
                HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 4, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
            }
            else {
                k::Printf("BattleBGID is %d, which is >= 80 but < 160, so we will adjust it by subtracting 80 and use the appropriate heap.\n", a1->battleBGID);
                adjustedBGID = a1->battleBGID - 80;
                HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 3, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
            }
        }
        else {
            adjustedBGID = a1->battleBGID;
            HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 0, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
        }
        Label_StaticBackground:
        adjustedBGID = 24;
        k::Printf("BattleBGID is %d, which is >= 80 but < 160, so we will adjust it by subtracting 80 and use the appropriate heap.\n", a1->battleBGID);
        HeapNew = (_BYTE*)GFL_ArcSysReadHeapNew(151, 0, (HeapID)((g_Effects->HeapID & 0x7FFF | 0x8000)));
        v18 = 44 * adjustedBGID;
        if (2 * (unsigned __int8)HeapNew[v18 + 1])
        {
            AreaIDSeasonShift = a1->AreaIDSeasonShift;
        }
        g_Effects->btlvStageHandle = BtlvStage_Create(
            a1->battleStyle,
            (unsigned __int8)HeapNew[v18 + 22 + a1->PlayerBattlePedestalID],
            AreaIDSeasonShift,
            heapId,
            (unsigned __int16)a1->pokestar);
        mainModule = g_Effects->SetupParam.mainModule;
        if (mainModule)
        {
            IsBattleType = BtlSetup_IsBattleType(mainModule, (BtlSetupFlag)1024);
            v21 = BtlvField_Create(
                IsBattleType,
                (unsigned __int8)HeapNew[44 * adjustedBGID + 2 + a1->PlayerBattlePedestalID],
                AreaIDSeasonShift,
                heapId,
                (unsigned __int16)a1->pokestar,
                (unsigned __int16)a1->pokestarField,
                a1->pwtFinal);
        }
        else
        {
            v21 = BtlvField_Create(
                0,
                (unsigned __int8)HeapNew[44 * adjustedBGID + 2 + a1->PlayerBattlePedestalID],
                AreaIDSeasonShift,
                heapId,
                (unsigned __int16)a1->pokestar,
                (unsigned __int16)a1->pokestarField,
                a1->pwtFinal);
        }
        g_Effects->btlvFieldHandle = v21;
        if (HeapNew[44 * adjustedBGID])
        {
            sub_2019830(
                a1->ZoneID,
                a1->Hour,
                a1->Minute,
                a1->FieldLightIndex,
                0,
                &a6,
                g_Effects->HeapID);
            light.Color = a6;
            light.Direction.x = 0;
            light.Direction.y = -4096;
            light.Direction.z = 0;
            GFL_G3DSysLightSet(0, &light);
        }
        GFL_HeapFree(HeapNew);
        g_Effects->btlvCameraHandle = BtlvCamera_Create((int)g_Effects->TCBManager, heapId);
        RecordedBattleType = BtlvEffect_GetRecordedBattleType(g_Effects->SetupParam.mainModule);
        g_Effects->clact = BtlvClAct_Init(g_Effects->TCBManager, heapId, RecordedBattleType);
        g_Effects->btlvGauge = BtlvGauge_Create(a2, (unsigned __int16)a1->pokestar, heapId);
        g_Effects->btlvTimer = BtlvTimer_Create(heapId);
        g_Effects->btlvBG = BtlvBG_12_Create(g_Effects->TCBManager, heapId);
        if (BtlvEffect_GetRecordedBattleType(g_Effects->SetupParam.mainModule) == 1)
        {
            PokestarScriptPtr = (PokestarScenario *) MainModule_GetPokestarScriptPtr(g_Effects->SetupParam.mainModule);
            sub_21E9C64(g_Effects->clact, PokestarScriptPtr->turn_max, 0);
        }
        BtlvMcss_SetOrthoMode(g_Effects->btlvMcss);
        ParticleSys_Init(heapId);
        for (i = 0; i < 8; ++i)
        {
            v25 = (BtlvEffectMain *)((char *)g_Effects + 4 * i);
            v25->trainerIndex[0] = -1;
        }
        v26 = g_Effects->SetupParam.mainModule;
        if (v26)
        {
            if (BtlSetup_IsBattleType(v26, (BtlSetupFlag)2048))
            {
                v27 = 300;
            }
            else
            {
                v27 = 900;
            }
            g_Effects->FramesBeforeCameraIdleMovement = v27;
        }
        g_Effects->VTCB = GFL_VBlankTCBAdd((TCBFunc)TCBTask_VBlank, 0, 1u);
        PokeVoice_AllocMulti(2, g_Effects->HeapID);
    }
}