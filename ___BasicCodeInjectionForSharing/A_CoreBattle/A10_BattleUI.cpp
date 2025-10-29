

// #include "codeinjection_battlefield.h"
#include "kPrint.h"
// #include "settings.h"
#include "swantypes.h"

#pragma region LoadPokeData
extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// extern "C" int THUMB_BRANCH_BattleClient_ActionSelect_Root(BtlClientWk *a1, unsigned int *a2)
// {
//     unsigned int v3;                                     // r1
//     BattleActionParam *v5;                               // r0
//     int(__fastcall * v6)(BtlClientWk *, unsigned int *); // r1
//     BtlClientWk *v7;                                     // r0
//     unsigned int v8;                                     // r0
//     bool v9;                                             // zf
//     BtlvCore *btlvCore;                                  // r0
//     int result;                                          // r0
//     unsigned int v12;                                    // r0
//     BattleMon *ClientPokeData;                           // r0
//     int ID;                                              // r0

//     v3 = *a2;
//     if (v3 <= 8)
//     {

//         if (IsEqual(v3, 0))
//         {
//             a1->procPoke = PokeCon_GetClientPokeData(a1->pokeCon, a1->myID, a1->procPokeIdx);
//             v5 = &a1->actionParam[a1->procPokeIdx];
//             a1->procAction = (int*) v5;
//             a1->currentActionCount = 0;
//             BattleAction_SetNull(v5);
//             if (AutoSelectAction(a1, a1->procPoke, a1->procAction))
//             {
//                 v6 = BattleClient_ActionSelectCheckFinish;
//                 v7 = a1;
//                 BattleClient_ActionSelect_SetSubProc(v7, v6);
//                 return 0;
//             }
//             if (BattleClient_CheckTrainerMsg(a1, &a1->AITrainerMsgID) == 1)
//             {
//                 v7 = a1;
//                 v6 = BattleClient_PlayGymLeaderFinalMusic;
//                 BattleClient_ActionSelect_SetSubProc(v7, v6);
//                 return 0;
//             }
//             v8 = *a2 + 1;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 1))
//         {
//             if (a1->prevPokeIdx != a1->procPokeIdx || a1->fStdMsgChanged)
//             {
//                 BattleClient_SetupActionSelectStartStr(a1, (BattleMon *)a1->procPoke, &a1->strParam);
//                 BtlvCore_StartMessageImmediate(a1->btlvCore, &a1->strParam);
//                 a1->fStdMsgChanged = 0;
//                 a1->prevPokeIdx = a1->procPokeIdx;
//                 v8 = *a2 + 1;
//                 *a2 = v8;
//             }
//             v8 = v3 + 2;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 2))
//         {
//             if (!BtlvCore_WaitMessage(a1->btlvCore))
//             {
//                 return 0;
//             }
//             ++*a2;
//             BtlvCore_StartActionSelect(a1->btlvCore, (BattleMon *)a1->procPoke, a1->procPokeIdx > a1->firstPokeIdx, a1->procAction);
//             v8 = *a2 + 1;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 3))
//         {
//             BtlvCore_StartActionSelect(a1->btlvCore, (BattleMon *)a1->procPoke, a1->procPokeIdx > a1->firstPokeIdx, a1->procAction);
//             v8 = *a2 + 1;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 4))
//         {
//             v9 = BattleClient_CheckActionSelectForceQuit(a1, BattleClient_ActionForceQuit) == 0;
//             btlvCore = (BtlvCore*)a1->btlvCore;
//             if (!v9)
//             {
//                 BtlvCore_QuitActionSelect(btlvCore);
//                 return 0;
//             }
//             v12 = BtlvCore_WaitActionSelect(btlvCore);
//             if (v12 > 4)
//             {
//                 return 0;
//             }
//             while (2)
//             {

//                 if (IsEqual(v12, 0)){
//                     return 0;
//                 }
//                 else if (IsEqual(v12, 1)){
//                     LauncherCost_Save(a1, a1->procPokeIdx, 0);
//                     v7 = a1;
//                     v6 = BattleClient_ActionSelectFight;
//                     BattleClient_ActionSelect_SetSubProc(v7, v6);
//                     return 0;
//                 }
//                 else if (IsEqual(v12, 2)){
//                     if (BattleMon_CheckIfMoveCondition((BattleMon *)a1->procPoke, CONDITION_SKY_DROP))
//                     {
//                         v8 = 6;
//                         *a2 = v8;
//                     }
//                     if (a1->bagMode == 1 && !MainModule_IsWonderLauncherEnabled(a1->mainModule))
//                     {
//                         BtlvCore_RestartUI(a1->btlvCore);
//                         v8 = 5;
//                         *a2 = v8;
//                     }
//                     if (MainModule_GetPokestarType(a1->mainModule) == 1)
//                     {
//                         v7 = a1;
//                         v6 = BattleClient_ActionSelectChooseSwitchPoke;
//                     }
//                     else
//                     {
//                         v7 = a1;
//                         v6 = BattleClient_ActionSelectItem;
//                     }
//                     BattleClient_ActionSelect_SetSubProc(v7, v6);
//                     return 0;

//                 }
//                 else if (IsEqual(v12, 3)){
//                      if (BattleMon_CheckIfMoveCondition((BattleMon *)a1->procPoke, CONDITION_SKY_DROP))
//                     {
//                         BtlvCore_RestartUI(a1->btlvCore);
//                         v8 = 6;
//                         *a2 = v8;
//                     }
//                     LauncherCost_Save(a1, a1->procPokeIdx, 0);
//                     v7 = a1;
//                     v6 = BattleClient_ActionSwitchPokemon;
//                     BattleClient_ActionSelect_SetSubProc(v7, v6);
//                     return 0;

//                 }
//                 else if (IsEqual(v12, 4)){

//                     if (a1->procPokeIdx == a1->firstPokeIdx)
//                     {
//                         if (BattleMon_CheckIfMoveCondition((BattleMon *)a1->procPoke, CONDITION_SKY_DROP) && MainModule_GetEscapeMode(a1->mainModule) != 2)
//                         {
//                             v8 = 6;
//                             *a2 = v8;
//                         }
//                         LauncherCost_Save(a1, a1->procPokeIdx, 0);
//                         v7 = a1;
//                         v6 = BattleClient_ActionSelectEscape;
//                         BattleClient_ActionSelect_SetSubProc(v7, v6);
//                         return 0;
//                     }
//                     if (!a1->procPokeIdx)
//                     {
//                         return 0;
//                     }
//                     while (1)
//                     {
//                         ClientPokeData = PokeCon_GetClientPokeData(a1->pokeCon, a1->myID, --a1->procPokeIdx);
//                         if (!AutoSelectAction(a1, ClientPokeData, 0))
//                         {
//                         }
//                         if (!a1->procPokeIdx)
//                         {
//                             return 0;
//                         }
//                     }
//                     a1->WonderLauncherEnergy += LauncherCost_Get(a1, a1->procPokeIdx);
//                     if (BattleAction_GetActionType(&a1->actionParam[a1->procPokeIdx]) == ACTION_SWITCH)
//                     {
//                         j_j_PokeSelectResult_Pop(&a1->pokeSelectResult);
//                     }
//                     if (BattleAction_GetActionType(&a1->actionParam[a1->procPokeIdx]) == ACTION_ITEM)
//                     {
//                         selItemWork_Restore(a1, a1->procPokeIdx);
//                     }
//                     BattleClient_ActionSelect_SetSubProc(a1, BattleClient_ActionSelect_Root);
//                     result = 0;

//                 }
//                 else {

//                 }

//                 return result;
//             }
//         }

//         else if (IsEqual(v3, 5))
//         {
//             if (!BtlvCore_RestartUIIfNotTransitioning(a1->btlvCore))
//             {
//                 return 0;
//             }
//             v8 = 3;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 6))
//         {
//             BtlvCore_RestartUIIfNotStandby(a1->btlvCore);
//             v8 = *a2 + 1;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 7))
//         {
//             if (!BtlvCore_RestartUIIfNotTransitioning(a1->btlvCore))
//             {
//                 return 0;
//             }
//             Btlv_StringParam_Setup(&a1->strParam, 1, 197);
//             ID = BattleMon_GetID(a1->procPoke);
//             Btlv_StringParam_AddArg(&a1->strParam, ID);
//             BattleClient_ActionSelect_StartMessage(a1, &a1->strParam);
//             v8 = *a2 + 1;
//             *a2 = v8;
//         }

//         else if (IsEqual(v3, 8))
//         {
//             if (!BtlvCore_WaitMessage(a1->btlvCore))
//             {
//                 return 0;
//             }
//             v8 = 1;
//             *a2 = v8;
//         }

//         else
//         {
//             return 0;
//         }
//     }
//     return 0;
// }

#pragma region Enums

enum PersonalField : unsigned __int8
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

enum PkmField : unsigned __int16
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

enum BattleStyle
{
    BTL_STYLE_SINGLE = 0x0,
    BTL_STYLE_DOUBLE = 0x1,
    BTL_STYLE_TRIPLE = 0x2,
    BTL_STYLE_ROTATION = 0x3,
};

#pragma endregion

#pragma region Structs

struct BtlvInput_VsRecorder
{
    int playTurn;
    int viewTurn;
    int MaxTurnCount;
    int stopFlag;
};
struct BattleScenarioData
{
    void *font;
    HeapID heapID;
    u8 end_flag;
    u8 pad;
    void *party;
    int scenario_num;
    int page_num;
    int time_out_flag;
    int comm_error_flag;
};
struct PokestarChoiceData
{
    void *font;
    HeapID heapID;
    u8 end_flag;
    u8 pad;
    int msgID;
    void *buf[4];
    int *result;
    int comm_error_flag;
};
struct SWAN_PACKED SWAN_ALIGNED(1) BattlePokeListData
{
    void *gameData;
    void *pokeParty;
    void *AllyPokeParty;
    void *Font;
    HeapID heapID;
    __int16 field_12;
    BattleStyle battleStyle;
    int IsBagDisabled;
    char AllyClientID;
    u8 SelectedPokeIndex[2];
    char ListMode;
    u8 SelectedMon;
    char InfoPokeIndex;
    char NumPartyMembers;
    char field_23;
    __int16 SelectedItem;
    __int16 IsSelectedMonTrapped;
    void *tcbmanager;
    void *palAnm;
    int IsFinished;
    int CommErrorFlag;
    char skill_item_use;
    char field_39;
    char field_3A;
    char field_3B;
    int field_3C;
    int SoundEffectFlag;
    int cursorFlag;
    u8 field_48[3];
    char MoveInfoMoveIndex;
    char EndFlag;
};

struct SWAN_PACKED SWAN_ALIGNED(2) BtlvCore
{
    void *mainModule;
    void *client;
    void *pokeCon;
    unsigned __int8 myID;
    u8 gapD[3];
    u32 processingCmd;
    bool (*mainProc)(BtlvCore *, int *a1, int);
    u32 mainSeq;
    int (*initFunc)(int *, BtlvCore *);
    int (*loopFunc)(int *, BtlvCore *);
    BtlvCore *work;
    int seq;
    u8 genericWork[128];
    void *strBuf;
    void *Font1;
    void *Font2;
    void *ActionParam;
    void *ActiveMon;
    int ActiveMonID;
    int PlayerAction;
    void *bagSave;
    void *ItemSelectFont;
    int bagMode;
    HeapID ItemSelectHeapID;
    u16 field_D6;
    int launcherSetup;
    char launcherEnergy;
    char launcherReserveEnergy;
    u16 SelectedItem;
    u8 cost;
    char EndFlag;
    char field_E2;
    char field_E3;
    int bagCursor;
    int timeOutFlag;
    int CommErrorFlag;
    char BallCatchMode;
    char IsWildBattle;
    u8 ret_page;
    char field_F3;
    int cursorFlag;
    int item_pos;
    int field_FC;
    int item_scr;
    int field_104;
    int IsOnlineBattle;
    BattlePokeListData pokeListData;
    char field_159;
    u8 gap15A[2];
    BattleScenarioData scenarioData;
    PokestarChoiceData pokestarChoiceData;
    void *pokeSelectResult;
    BtlvInput_VsRecorder btlvInput_VsRecorder;
    void **Party;
    u8 BottomScreenMenuSeq;
    char fUndoActionButton;
    char field_1B6;
    char field_1B7;
    char field_1B8;
    char field_1B9;
    char field_1BA;
    char field_1BB;
    void *CallbackMgr;
    void *btlvScu;
    void *btlvScd;
    HeapID heapID;
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

struct PokeList_MoveData
{
    __int16 MoveID;
    char CurrentPP;
    char MaxPP;
    char Type;
    char Category;
    char Accuracy;
    char Power;
};

struct PokeList_BmpWinData
{
    void *BmpWin;
    char field_4;
    char field_5;
    char field_6;
    char field_7;
};

struct PokeListData
{
    PartyPkm *partyPkm;
    __int16 Species;
    __int16 Attack;
    __int16 Defense;
    __int16 Speed;
    __int16 SpecialAttack;
    __int16 SpecialDefense;
    __int16 CurrentHP;
    __int16 MaxHP;
    char Type1;
    char Type2;
    char Level;
    char SexStatusIsEgg;
    __int16 Ability;
    __int16 Item;
    int Experience;
    int ExpForLevel;
    int ExpToNextLevel;
    int Forme;
    PokeList_MoveData MoveData[4];
};

struct ClAct_0x7C
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    _BYTE gap10[84];
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
};

struct SWAN_ALIGNED(4) ClActObj
{
    ClActObj *next;
    ClActObj *prev;
    void *unit;
    u16 posX;
    u16 posY;
    __int16 field_10;
    __int16 field_12;
    int scaleX;
    int scaleY;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    _BYTE gap2C[20];
    int field_40;
    _BYTE gap44[16];
    int field_54;
    __int16 rotation;
    __int16 animID;
    __int16 field_5C;
    __int16 field_5E;
    int Flags;
    int field_64;
    ClAct_0x7C field_68;
};

struct PokeListMain
{
    BattlePokeListData *pokeListSetupData;
    PokeListData pokeListData[6];
    u8 field_1CC[6];
    void *TCBManagerEx;
    void *PalAnm;
    _BYTE gap1DC[7324];
    int field_1E78;
    _BYTE gap1E7C[28];
    char field_1E98;
    char field_1E99;
    char field_1E9A;
    char field_1E9B;
    void *GFLFont;
    void *MsgData;
    void *WordSetSystem;
    void *StrBuf;
    void *PrintSys;
    int field_1EB0;
    int field_1EB4;
    int field_1EB8;
    ClActObj *field_1EBC[40];
    int field_1F5C;
    PokeList_BmpWinData field_1F60[2];
    PokeList_BmpWinData field_1F70[64];
    void *field_2170;
    char field_2174;
    char field_2175;
    char field_2176;
    char field_2177;
    int field_2178;
    int field_217C;
    char field_2180;
    int field_2184;
    int field_2188;
    int field_218C;
    char field_2190;
    char field_2191;
    _BYTE gap2192;
    char field_2193;
    int field_2194;
    _BYTE gap2198[768];
    char field_2498;
    char field_2499;
    char field_249A;
    char field_249B;
    __int16 field_249C;
    __int16 field_249E;
    _BYTE gap24A0[156];
    int field_253C;
    int field_2540;
};

struct EventWorkSave
{
    u16 Works[431];
    u8 FlagBytes[383];
    u8 CanRespawnHiddenItems;
};

#pragma endregion

#pragma region Functions

extern "C" u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);
extern "C" int sub_21F9E78(PokeListMain *a1, int a2);
extern "C" void sub_21F4A30(PokeListMain *a1, unsigned int a2, char a3, int a4);
extern "C" int PokeList_GetSelectedMonID(PokeListMain *a1, int a2);
extern "C" int sub_21F4F14(PokeListMain *a1);
extern "C" void sub_21F4F50(int a1);
extern "C" void PokeList_LoadPokeData(PokeListMain *a1, PartyPkm *a2, PokeListData *a3);
extern "C" PartyPkm *PokeParty_GetPkm(void *party, int slot);
extern "C" u32 PokeParty_GetPkmCount(void *pPartyBlk);
extern "C" u32 PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra);
extern "C" u32 getExpForPkm_Wrapper(void *pPkm);
extern "C" u32 PokeParty_GetSex(PartyPkm *pPkm);
extern "C" u32 PML_MoveGetParam(int wazaId, MoveField dataId);
extern "C" int PML_MoveGetMaxPP(int wazaId, unsigned int ppUpStage);
extern "C" bool PML_MoveIsAlwaysHit(int wazaId);
extern "C" int sub_202D8EC(PartyPkm *a1);
extern "C" int BattleClient_GetMyID(void *a1);
extern "C" void *MainModule_GetPokeParty(void *a1, int a2);
extern "C" int MainModule_IsNotTrainerOrWildBattle(void *a1);
extern "C" void *MainModule_GetAllyPokeParty(void *a1, char a2);
extern "C" int MainModule_IsAllyInMultiBattle(void *a1, char a2);
extern "C" BattleStyle MainModule_GetBattleStyle(void *a1);
extern "C" int MainModule_CheckNumBattlePos(void *a1, char a2);
extern "C" char *BtlvScd_GetCursorFlag(void *a1);
extern "C" void *BtlvEffect_GetTCBManager();
extern "C" void *BtlvEffect_GetPalAnm();
extern "C" void *MainModule_GetGameData(void *a1);
extern "C" int BtlvCore_GetSoundEffectFlag(BtlvCore *a1);
extern "C" u32 PML_PersonalGetParamSingle(u16 species, u16 form, PersonalField field);
extern "C" EventWorkSave *GameData_GetEventWork(void *gameData);
extern "C" u16 *EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);

#pragma endregion

// #pragma region Buttons
/* THIS FUNCTION APPEARS TO BE A HELPER FUNCTION FOR LOADING THE TILES FOR BUTTONS ON THE POKESUMMARY */
// extern "C" void THUMB_BRANCH_sub_21F4BA8(PokeListMain *a1, unsigned int a2)
// {
//     unsigned int i;    // r5
//     int v4;            // r0
//     PokeListMain *v5;  // r0
//     unsigned int v6;   // r1
//     char v7;           // r2
//     int v8;            // r3
//     unsigned int v9;   // r5
//     int v10;           // r0
//     PokeListMain *v11; // r0
//     unsigned int v12;  // r1
//     char v13;          // r2
//     int v14;           // r3
//     unsigned int j;    // r5
//     PokeListMain *v16; // r0
//     unsigned int v17;  // r1
//     char v18;          // r2
//     unsigned int v19;  // r5
//     char v20;          // r2
//     unsigned int k;    // r5
//     PokeListMain *v22; // r0
//     unsigned int v23;  // r1
//     char v24;          // r2
//     k::Printf("\n====sub_21F4BA8=== a2 = %d\n", a2);
//     if (a2 > 8)
//     {
//         return;
//     }
//     /* 0 means that we're in the pokelist overview, looking at every pokemon in the inventory */
//     if (a2 == 0)
//     {
//         for (i = 0; i < 6; i = (i + 1))
//         {
//             /* Runs a function, and then sets v7 and v8 depending on the results */
//             v4 = sub_21F9E78(a1, i);
//             if (v4)
//             {
//                 if (v4 == 1)
//                 {
//                     v5 = a1;
//                     v6 = i;
//                     v7 = 0;
//                     v8 = 0;
//                 }
//                 else
//                 {
//                     if (v4 != 2)
//                     {
//                         continue;
//                     }
//                     v5 = a1;
//                     v6 = i;
//                     v7 = 0;
//                     v8 = 1;
//                 }
//             }
//             else
//             {
//                 v5 = a1;
//                 v6 = i;
//                 v7 = 3;
//                 v8 = 1;
//             }
//             sub_21F4A30(v5, v6, v7, v8);
//         }
//         if ((a1->pokeListSetupData->ListMode - 1) > 1u)
//         {
//             sub_21F4A30(a1, 6u, 0, 0);
//             return;
//         }
//         sub_21F4F50((int)a1);
//         return;
//     }
//     /* 1 means that we have selected a Pokemon and am on the screen that shows Summary, Check Moves, Back, and potentially switch */
//     else if (a2 == 1)
//     {
//         sub_21F4A30(a1, 6u, 0, 0);
//         sub_21F4A30(a1, 7u, 0, 0);
//         if ((a1->pokeListData[PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon)].SexStatusIsEgg & 0x80) != 0)
//         {
//             sub_21F4A30(a1, 8u, 3, 0);
//             sub_21F4A30(a1, 0xAu, 3, 0);
//         }
//         else
//         {
//             sub_21F4A30(a1, 8u, 0, 0);
//             sub_21F4A30(a1, 0xAu, 0, 0);
//         }
//         return;
//     }
//     /* 2 is the Pokemon Summary */
//     else if (a2 == 2)
//     {
//         if (sub_21F4F14(a1))
//         {
//             sub_21F4A30(a1, 0xCu, 0, 0);
//             sub_21F4A30(a1, 0xDu, 0, 0);
//         }
//         else
//         {
//             sub_21F4A30(a1, 0xCu, 3, 0);
//             sub_21F4A30(a1, 0xDu, 3, 0);
//         }
//         sub_21F4A30(a1, 0xBu, 0, 0);
//         sub_21F4A30(a1, 6u, 0, 0);
//         return;
//     }
//     /* 3 is the Pokemon Moves */
//     else if (a2 == 3)
//     {
//         if (sub_21F4F14(a1))
//         {
//             sub_21F4A30(a1, 0xCu, 0, 0);
//             sub_21F4A30(a1, 0xDu, 0, 0);
//         }
//         else
//         {
//             sub_21F4A30(a1, 0xCu, 3, 0);
//             sub_21F4A30(a1, 0xDu, 3, 0);
//         }
//         for (j = 0; j < 4; j = (j + 1))
//         {
//             if (a1->pokeListData[PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon)].MoveData[j].MoveID)
//             {
//                 v16 = a1;
//                 v17 = (j + 14);
//                 v18 = 0;
//             }
//             else
//             {
//                 v16 = a1;
//                 v17 = (j + 14);
//                 v18 = 3;
//             }
//             sub_21F4A30(v16, v17, v18, 0);
//         }
//         sub_21F4A30(a1, 9u, 0, 0);
//         sub_21F4A30(a1, 6u, 0, 0);
//         return;
//     }
//     else if (a2 == 4)
//     {
//         v19 = 0;
//         sub_21F4A30(a1, 6u, 0, 0);
//         do
//         {
//             if (a1->pokeListSetupData->MoveInfoMoveIndex == v19)
//             {
//                 v20 = 2;
//             }
//             else
//             {
//                 v20 = 0;
//             }
//             sub_21F4A30(a1, (v19 + 28), v20, 0);
//             v19 = (v19 + 1);
//         } while (v19 < 4);
//         return;
//     }
//     else if (a2 == 5)
//     {
//         for (k = 0; k < 4; k = (k + 1))
//         {
//             if (a1->pokeListData[PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon)].MoveData[k].MoveID)
//             {
//                 v22 = a1;
//                 v23 = (k + 18);
//                 v24 = 0;
//             }
//             else
//             {
//                 v22 = a1;
//                 v23 = (k + 18);
//                 v24 = 3;
//             }
//             sub_21F4A30(v22, v23, v24, 0);
//         }
//         sub_21F4A30(a1, 6u, 0, 0);
//         return;
//     }
//     else if (a2 == 6)
//     {
//         sub_21F4A30(a1, 0x16u, 0, 0);
//         sub_21F4A30(a1, 0x17u, 0, 0);
//         sub_21F4A30(a1, 0x18u, 0, 0);
//         sub_21F4A30(a1, 0x19u, 0, 0);
//         sub_21F4A30(a1, 0x1Au, 0, 0);
//         sub_21F4A30(a1, 6u, 0, 0);
//         return;
//     }
//     else if (a2 == 7)
//     {
//         sub_21F4A30(a1, 0x1Bu, 0, 0);
//         sub_21F4A30(a1, 6u, 0, 0);
//         return;
//     }
//     else if (a2 == 8)
//     {
//         v9 = 0;
//     }
//     else
//     {
//         return;
//     }
//     while (1)
//     {
//         v10 = sub_21F9E78(a1, v9);
//         if (!v10)
//         {
//             break;
//         }
//         if (v10 == 1)
//         {
//             v11 = a1;
//             v12 = v9;
//             v13 = 0;
//             v14 = 0;
//             sub_21F4A30(v11, v12, v13, v14);
//         }
//         if (v10 == 2)
//         {
//             v11 = a1;
//             v12 = v9;
//             v13 = 0;
//             v14 = 1;
//             sub_21F4A30(v11, v12, v13, v14);
//         }
//         v9 = (v9 + 1);
//         if (v9 >= 6)
//         {
//             sub_21F4A30(a1, 6u, 0, 0);
//             return;
//         }
//     }
//     v11 = a1;
//     v12 = v9;
//     v13 = 3;
//     v14 = 1;
//     sub_21F4A30(v11, v12, v13, v14);
//     v9 = (v9 + 1);
//     if (v9 >= 6)
//     {
//         sub_21F4A30(a1, 6u, 0, 0);
//         return;
//     }
// }
// #pragma endregion

// #pragma region LoadingThePokeData
// extern "C" void THUMB_BRANCH_sub_21F9D14(PokeListMain *a1)
// {
//     unsigned int i;             // r4
//     PartyPkm *v3;               // r1
//     PokeListMain *v4;           // r0
//     unsigned int v5;            // r4
//     PokeListData *PokeListData; // r7
//     int v7;                     // r6
//     PartyPkm *Pkm;              // r1
//     PokeListMain *v9;           // r0
//     PartyPkm *v10;              // r1
//     PokeListMain *v11;          // r0
//     if (a1->pokeListSetupData->IsBagDisabled)
//     {
//         v5 = 0;
//         PokeListData = a1->pokeListData;
//         do
//         {
//             v7 = v5;
//             if (v5 >= PokeParty_GetPkmCount(a1->pokeListSetupData->pokeParty))
//             {
//                 v9 = a1;
//                 Pkm = 0;
//             }
//             else
//             {
//                 Pkm = PokeParty_GetPkm(a1->pokeListSetupData->pokeParty, v5);
//                 v9 = a1;
//             }
//             PokeList_LoadPokeData(v9, Pkm, &PokeListData[v7]);
//             if (v5 >= PokeParty_GetPkmCount(a1->pokeListSetupData->AllyPokeParty))
//             {
//                 v11 = a1;
//                 v10 = 0;
//             }
//             else
//             {
//                 v10 = PokeParty_GetPkm(a1->pokeListSetupData->AllyPokeParty, v5);
//                 v11 = a1;
//             }
//             PokeList_LoadPokeData(v11, v10, &PokeListData[v7 + 3]);
//             ++v5;
//         } while (v5 < 3);
//     }
//     else
//     {
//         for (i = 0; i < 6; ++i)
//         {
//             if (i >= PokeParty_GetPkmCount(a1->pokeListSetupData->pokeParty))
//             {
//                 v4 = a1;
//                 v3 = 0;
//             }
//             else
//             {
//                 v3 = PokeParty_GetPkm(a1->pokeListSetupData->pokeParty, i);
//                 v4 = a1;
//             }
//             PokeList_LoadPokeData(v4, v3, &a1->pokeListData[i]);
//         }
//     }
// }
// #pragma endregion

extern "C" u32 GetScanSetting()
{
    EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
    u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16438);
    return *lvl_cap_ptr;
}

/* THIS IS WHERE DATA IS ASSIGNED TO THE THING THAT CHECKS STUFF */
// extern "C" void THUMB_BRANCH_SAFESTACK_PokeList_LoadPokeData(PokeListMain *a1, PartyPkm *a2, PokeListData *a3)
// {
//     u32 Param;             // r0
//     char Level;            // r1
//     int ExpForPkm_Wrapper; // r0
//     char v7;               // r1
//     unsigned int i;        // r6
//     PokeList_MoveData *v9; // r4
//     char v10;              // r0

//     a3->partyPkm = a2;

//     if (a2)
//     {
//         a3->Species = PokeParty_GetParam(a2, PF_Species, 0);
//         a3->Forme = PokeParty_GetParam(a3->partyPkm, PF_Forme, 0);
//         if (a3->Species)
//         {
//             int isEnemy = a1->pokeListSetupData->field_3C;

//             if (isEnemy) // && !GetScanSetting())
//             {
//                 a3->Attack = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_ATK);
//                 a3->Defense = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_DEF);
//                 a3->Speed = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPE);
//                 a3->SpecialAttack = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPA);
//                 a3->SpecialDefense = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPD);
//                 a3->CurrentHP = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_HP);
//                 a3->MaxHP = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_HP);
//             }
//             else
//             {
//                 a3->Attack = PokeParty_GetParam(a3->partyPkm, PF_ATK, 0);
//                 a3->Defense = PokeParty_GetParam(a3->partyPkm, PF_DEF, 0);
//                 a3->Speed = PokeParty_GetParam(a3->partyPkm, PF_SPE, 0);
//                 a3->SpecialAttack = PokeParty_GetParam(a3->partyPkm, PF_SPA, 0);
//                 a3->SpecialDefense = PokeParty_GetParam(a3->partyPkm, PF_SPD, 0);
//                 a3->CurrentHP = PokeParty_GetParam(a3->partyPkm, PF_NowHP, 0);
//                 a3->MaxHP = PokeParty_GetParam(a3->partyPkm, PF_MaxHP, 0);
//             }

//             a3->Type1 = PokeParty_GetParam(a3->partyPkm, PF_Type1, 0);
//             a3->Type2 = PokeParty_GetParam(a3->partyPkm, PF_Type2, 0);
//             a3->Level = PokeParty_GetParam(a3->partyPkm, PF_Level, 0) & 0x7F | a3->Level & 0x80;
//             Param = PokeParty_GetParam(a3->partyPkm, PF_IsNotNidoran, 0);
//             Level = a3->Level;
//             if (Param == 1)
//             {
//                 a3->Level = Level & 0x7F;
//             }
//             else
//             {
//                 a3->Level = Level | 0x80;
//             }
//             a3->SexStatusIsEgg = PokeParty_GetSex(a3->partyPkm) & 7 | a3->SexStatusIsEgg & 0xF8;
//             a3->SexStatusIsEgg = (8 * sub_202D8EC(a3->partyPkm)) & 0x7F | a3->SexStatusIsEgg & 0x87;
//             a3->SexStatusIsEgg = (PokeParty_GetParam(a3->partyPkm, PF_IsEgg, 0) << 7) | a3->SexStatusIsEgg & 0x7F;
//             a3->Ability = PokeParty_GetParam(a3->partyPkm, PF_Ability, 0);
//             a3->Item = PokeParty_GetParam(a3->partyPkm, PF_Item, 0);

//             a3->Experience = 0;//PokeParty_GetParam(a3->partyPkm, PF_Experience, 0);
//             ExpForPkm_Wrapper = getExpForPkm_Wrapper(a3->partyPkm);
//             v7 = a3->Level;
//             a3->ExpForLevel = 0;//ExpForPkm_Wrapper;
//             if ((v7 & 0x7F) != 100)
//             {
//                 ExpForPkm_Wrapper = PML_UtilGetPkmLvExp(a3->Species, a3->Forme, ((v7 & 0x7F) + 1));
//             }
//             a3->ExpToNextLevel = 0;//ExpForPkm_Wrapper;
//             for (i = 0; i < 4; ++i)
//             {
                
//                 int currentPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0);
//                 int maxPP = v9->MaxPP = PML_MoveGetParam(v9->MoveID, MVDATA_BASEPP) + 3;
                
//                 if (isEnemy && !(currentPP < maxPP)){
//                     continue;
//                 }
                
//                 PokeList_MoveData *v9 = &a3->MoveData[i];
//                 v9->MoveID = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0);
//                 if (v9->MoveID)
//                 {
//                     v9->CurrentPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0);
//                     v9->MaxPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 62), 0);
//                     v9->MaxPP = PML_MoveGetMaxPP(v9->MoveID, v9->MaxPP);
//                     if (isEnemy){
//                         v9->MaxPP = maxPP;
//                     }
//                     v9->Type = PML_MoveGetParam(v9->MoveID, MVDATA_TYPE);
//                     v9->Category = PML_MoveGetParam(v9->MoveID, MVDATA_CATEGORY);
//                     if (PML_MoveIsAlwaysHit(v9->MoveID))
//                     {
//                         v10 = 0;
//                     }
//                     else
//                     {
//                         v10 = PML_MoveGetParam(v9->MoveID, MVDATA_ACCURACY);
//                     }
//                     v9->Accuracy = v10;
//                     v9->Power = PML_MoveGetParam(v9->MoveID, MVDATA_POWER);
//                 }
//             }
//         }
//     }
//     else
//     {
//         a3->Species = 0;
//     }
// }
#pragma endregion

// #pragma region InterceptingInput
// int THUMB_BRANCH_BattleClient_ActionSelectEscape(void *a1, unsigned int *r1_0)
// {
//     int EscapeMode;                    // r0
//     unsigned int v5;                   // r0
//     void *v6;                          // r0
//     int (*v7)(void *, unsigned int *); // r1
//     char v9[2];                        // [sp+0h] [bp-18h] BYREF
//     __int16 a2[11];                    // [sp+2h] [bp-16h] BYREF

//     if (*r1_0 <= 5)
//     {
//         switch (*(&jpt_21B42DA + *r1_0))
//         {
//         case 0:
//             EscapeMode = MainModule_GetEscapeMode(a1->mainModule);
//             if (!EscapeMode)
//             {
//                 goto LABEL_6;
//             }
//             if (EscapeMode != 1)
//             {
//                 if (EscapeMode == 2)
//                 {
//                     Btlv_StringParam_Setup(&a1->strParam, 1, 77);
//                     Btlv_StringParam_SetWait(&a1->strParam, 255);
//                     BattleClient_ActionSelect_StartMessage(a1, &a1->strParam);
//                     v5 = 3;
//                     goto LABEL_8;
//                 }
//             LABEL_6:
//                 if (AreAllMonsTrapped(a1, v9, a2) == 4)
//                 {
//                     goto LABEL_7;
//                 }
//                 if (a2[0])
//                 {
//                     Btlv_StringParam_Setup(&a1->strParam, 2, 869);
//                     Btlv_StringParam_AddArg(&a1->strParam, v9[0]);
//                     Btlv_StringParam_AddArg(&a1->strParam, a2[0]);
//                 }
//                 else
//                 {
//                     Btlv_StringParam_Setup(&a1->strParam, 1, 74);
//                 }
//                 BattleClient_ActionSelect_StartMessage(a1, &a1->strParam);
//                 v5 = 1;
//                 goto LABEL_8;
//             }
//             Btlv_StringParam_Setup(&a1->strParam, 1, 76);
//             BattleClient_ActionSelect_StartMessage(a1, &a1->strParam);
//             *r1_0 = 1;
//             return 0;
//         case 1:
//             if (!BtlvCore_WaitMessage(a1->btlvCore))
//             {
//                 return 0;
//             }
//             BattleClient_SetupActionSelectStartStr(a1, a1->currentMon, &a1->strParam);
//             BtlvCore_StartMessageImmediate(a1->btlvCore, &a1->strParam);
//             v5 = 2;
//             goto LABEL_8;
//         case 2:
//             if (BtlvCore_WaitMessage(a1->btlvCore))
//             {
//                 goto LABEL_24;
//             }
//             return 0;
//         case 3:
//             BtlvCore_WaitMessage(a1->btlvCore);
//             if (!BtlvCore_IsMessageFinishedNow(a1->btlvCore))
//             {
//                 return 0;
//             }
//             Btlv_StringParam_Setup(&a1->strParam, 3, 8);
//             Btlv_StringParam_Setup(&a1->secondaryStrParam, 3, 9);
//             BtlvCore_StartYesNo(a1->btlvCore, &a1->strParam.strID, &a1->secondaryStrParam.strID, 1);
//             v5 = 4;
//             goto LABEL_8;
//         case 4:
//             if (!BtlvCore_WaitMessage(a1->btlvCore))
//             {
//                 return 0;
//             }
//             if (!BtlvCore_WaitYesNo(a1->btlvCore, &a2[1]))
//             {
//                 if (!BattleClient_CheckIfOverCmdLimit(a1))
//                 {
//                     return 0;
//                 }
//                 v6 = a1;
//                 v7 = BattleClient_ActionForceQuit;
//                 goto LABEL_28;
//             }
//             if (*&a2[1])
//             {
//             LABEL_24:
//                 v6 = a1;
//                 v7 = BattleClient_ActionSelect_Root;
//             LABEL_28:
//                 BattleClient_SetSubProc(v6, v7);
//                 return 0;
//             }
//         LABEL_7:
//             v5 = 5;
//         LABEL_8:
//             *r1_0 = v5;
//             break;
//         case 5:
//             BattleAction_SetEscape(a1->currentAction);
//             a1->actSelectFlags |= 4u;
//             v7 = BattleClient_ActionSelectCheckFinish;
//             v6 = a1;
//             goto LABEL_28;
//         default:
//             return 0;
//         }
//     }
//     return 0;
// }

// #pragma endregion

// extern "C" bool THUMB_BRANCH_sub_21F4F14(PokeListMain *a1)
// {
//     unsigned int v1;  // r2
//     unsigned int i;   // r1
//     PokeListMain *v3; // r5

//     v1 = 0;
//     for (i = 0; i < 6; i = (i + 1))
//     {
//         v3 = (a1 + 76 * i);
//         k::Printf("\n\n=========sub_21F4F14=========\naPokeListMain is %d and v3 is %d\nPokeListMain->pokeListData[0].Species is %d\nv3->pokeListData[0].Species is %d\nThe loop is %d\n\n\n", (int)a1, (int) v3, a1->pokeListData[0].Species, v3->pokeListData[0].Species, i);
//         if (v3->pokeListData[0].Species && (v3->pokeListData[0].SexStatusIsEgg & 0x80) == 0)
//         {
//             v1 = (v1 + 1);
//         }
//     }
//     k::Printf("=========result=%d=========", (v1 >= 2));
//     return v1 >= 2;
// }