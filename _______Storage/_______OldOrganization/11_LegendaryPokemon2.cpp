#include "swan-master/swantypes.h"
#include "kPrint.h"

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long

// Uses esdb_newBattle.yml

// extern "C" int THUMB_BRANCH_getSizeofTrainerData()
// {
//   return 176;
// };

// extern "C" int THUMB_BRANCH_sub_20099E0(int* a1)
// {
//   return *(a1 + 420);
// };

// Uses esdb_newBattle.yml


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

    struct EscapeInfo
    {
        u32 count;
        u8 clientID[4];
    };

    struct ActionOrderWork
    {
        void *BattleMon;
        void *Action;
        int orderData;
        char clientID;
        char fDone;
        char InterruptActive;
        char field_F;
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
    struct SWAN_ALIGNED(8) ServerFlow
    {
        void *server;
        MainModule *mainModule;
        void *pokeCon;
        void *serverCommandQueue;
        int turnCount;
        int flowResult;
        int heapHandle;
        MoveRecord moveRecord;
        FaintRecord faintRecord;
        void *evolutionDataPtr;
        void *moveAnimCtrl;
        void *moveStealParam;
        void *magicCoatParam;
        void *hitCheckParam;
        EscapeInfo escapeInfo;
        int field_4C0;
        int field_4C4;
        int field_4C8;
        __int16 field_4CC;
        u8 field_4CE[6];
        u8 field_4D4[672];
        int SimulationCounter;
        int StatStageChangeCount;
        char IsTurnReadyToStart;
        char field_77D;
        char TurnCheckSeq;
        char defaultTargetPos;
        __int16 heapID;
        char actionOrderIndex;
        char actionOrderEndIndex;
        char ballTargetPos;
        char revivedPokeCount;
        char escapeAttempts;
        char field_787;
        char field_788;
        char thruDeadMsgPokeID;
        char flags;
        u8 field_78B[6];
        u8 revivePokeID[24];
        char pokeInFlag[24];
        char field_7C1[24];
        char switchCount[4];
        char field_7DD;
        char field_7DE;
        char field_7DF;
        ActionOrderWork actionOrderWork[6];
        ActionOrderWork TempActionOrderWork;
        void *setTargetOriginal;
        void *setTarget;
        void *setAlly;
        void *setEnemy;
        void *PokeSetDamaged;
        void *setStealTarget;
        void *PokeSetTemp;
        void *calcDamageAlly;
        void *calcDamageEnemy;
        u8 pokesetUnit[4592];
        int pokesetStackPtr;
        PokeSet pokeset;
        void *moveParam;
        void *moveParamOriginal;
        PosPoke PosPoke;
        char field_1AE2;
        char field_1AE3;
        HandlerParam_StrParams StrParam;
        CalcExpWork levelUpInfo[6];
        u8 eventWorkStack[548];
        u8 HEManager[512];
        __int16 PrevUsedMove;
        char field_1F7A;
        char field_1F7B;
        int actionIgnoreReason;
        EffectivenessCounter effectivenessCounter;
        EffectivenessRecorder effectivenessRecorder;
        u8 AttackingThisTurn[4];
        u8 TempWork[320];
        int field_2130;
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

    struct SWAN_PACKED SWAN_ALIGNED(1) BtlvScuDataSingles
    {
        void *BattleMon;
        u8 BattlePos;
        u8 ViewPos;
        u8 MonID;
        u8 ClientID;
        char AllyClientID;
    };

    struct BtlvScu_Field154
    {
        int field_0;
        int field_4;
        int field_8;
        int field_C;
        int field_10;
        char field_14;
        char field_15;
        char field_16;
        char field_17;
    };

    struct MessageWinVisibilityWork
    {
        void *window;
        s32 eva;
        s32 evb;
        s32 eva_step;
        s32 evb_step;
        u8 state;
        u8 timer;
    };

    struct AbilityPopup
    {
        void *scu;
        void *bmp;
        u16 ability;
        u8 side;
        u8 bgFrame;
        u8 monID;
        u8 seq;
        u8 *NCGRSrc;
        s32 posX;
        s32 speedX;
        u32 charPos;
        u8 moveTimer;
        u8 writeRaw;
        u8 flags;
    };

    struct StatusWindow
    {
        void *mon;
        void *scu;
        u8 battlePos;
        u8 viewPos;
        u8 dispFlag;
        u8 enableFlag;
    };

    // struct BtlvScu
    // {
    //     void *MessageWindow;
    //     void *MsgWinBitmap;
    //     void *LevelUpWin;
    //     void *LevelUpBitmap;
    //     int LevelUpWinCharPos;
    //     int AbilityPopupNCGR;
    //     _DWORD printsys;
    //     _DWORD dword1C;
    //     _BYTE byte20;
    //     _BYTE gap21[3];
    //     void *defaultfont;
    //     void *smallfont;
    //     void *callbackMgr;
    //     int printstream;
    //     StrBuf *strbuf1;
    //     StrBuf *strbuf2;
    //     StrBuf *strbuf3;
    //     u8 taskCounter[6];
    //     StatusWindow statusWindows[6];
    //     AbilityPopup abilityPopups[2];
    //     void *abilityPopupNCGRHead;
    //     int abilityPopupNCGR;
    //     int (*initFunc)(int *, BtlvScu *);
    //     int (*loopFunc)(int *, BtlvScu *);
    //     BtlvScu *work;
    //     int seq;
    //     u8 procWork[64];
    //     void *viewCore;
    //     MainModule *mainModule;
    //     void *pokeCon;
    //     u16 heapID;
    //     char printImmediateFlag;
    //     char printseq;
    //     u8 myID;
    //     char MessageFinishedNow;
    //     char field_142;
    //     char field_143;
    //     int printstate;
    //     __int16 printwait;
    //     __int16 printwaitorg;
    //     __int16 printwaitEOM;
    //     _BYTE byte14E;
    //     _BYTE BattleStartSeq;
    //     char SkipBattleStartFlag;
    //     MessageWinVisibilityWork messageWinVisibilityWork;
    //     void *levelUpMon;
    //     __int16 levelUpInfo;
    //     u16 field_172;
    //     u16 field_174;
    //     u16 field_176;
    //     u16 field_178;
    //     u16 field_17A;
    //     u16 field_17C;
    //     __int16 field_17E;
    // };

    struct BtlvScu
    {
        void *BmpWin1;
        void *Bitmap1;
        void *BmpWin2;
        void *Bitmap2;
        int field_10;
        int AbilityPopupNCGR;
        _DWORD printsys;
        _DWORD dword1C;
        _BYTE byte20;
        _BYTE gap21[3];
        void *font1;
        void *font2;
        void *callbackMgr;
        void *TCBExData;
        StrBuf *strbuf1;
        StrBuf *strbuf2;
        StrBuf *strbuf3;
        char field_40;
        char field_41;
        char field_42;
        char field_43;
        int field_44;
        int field_48[18];
        int field_90;
        void *field_94[9];
        _BYTE gapB8[32];
        _DWORD dwordD8;
        int field_DC;
        int (*field_E0)(int *, BtlvScu *);
        int (*field_E4)(int *, BtlvScu *);
        BtlvScu *field_E8;
        int field_EC;
        BtlvScuDataSingles field_F0;
        _BYTE gapF9[6];
        char field_FF;
        char field_100;
        char field_101;
        _BYTE gap102[3];
        char field_105;
        char ClientID;
        _BYTE gap107[41];
        void *viewCore;
        MainModule *mainModule;
        void *pokeCon;
        u16 heapID;
        char field_13E;
        char field_13F;
        u8 myID;
        char field_141;
        char field_142;
        char field_143;
        int field_144;
        __int16 field_148;
        __int16 field_14A;
        __int16 field_14C;
        _BYTE byte14E;
        _BYTE field_14F;
        char field_150;
        BtlvScu_Field154 field_154;
        void *field_16C;
        __int16 field_170;
        u16 field_172;
        u16 field_174;
        u16 field_176;
        u16 field_178;
        u16 field_17A;
        u16 field_17C;
        __int16 field_17E;
    };

    struct RecPlayerControl
    {
        char seq;
        char controlCode;
        char flags;
        char field_3;
        __int16 handlingTimer;
        u16 turnCount;
        u16 nextTurn;
        u16 maxTurnCount;
        u16 skipTurnCount;
    };

    struct Btlv_StringParam
    {
        u16 strID;
        u8 wait;
        u8 strTypeAndArgCount;
        int args[8];
    };

    struct UsableMoveStruct
    {
        void *mon;
        u8 isMoveUsable[4];
    };

    struct UsableMovesAndActions
    {
        UsableMoveStruct mons[3];
        void *action;
        void *action2;
    };

    struct PokeSelectParam
    {
        void *party;
        u8 numToSelect;
        u8 selectionStatus[6];
        u8 field_B;
    };

    struct PokeSelectResult
    {
        u8 selIdx[3];
        u8 outPokeIdx[3];
        u8 count;
        char numToSelect;
        char fCancel;
    };

    struct SWAN_PACKED SWAN_ALIGNED(4) BtlClientWk
    {
        MainModule *mainModule;
        void *pokeCon;
        void *currentMon;
        void *currentAction;
        void *recData;
        int recReader;
        RecPlayerControl recPlayer;
        int (*mainProc)(BtlClientWk *) SWAN_ALIGNED(4);
        EscapeInfo escapeInfo;
        void *battleField;
        __int64 randX;
        u64 randMul;
        u64 randAdd;
        void *adapter;
        void *btlvCore;
        Btlv_StringParam strParam;
        u8 gap7C[4];
        Btlv_StringParam secondaryStrParam;
        u8 gapA4[4];
        void *cmdCheckServer;
        UsableMovesAndActions UsableMovesForMonsOnField;
        char PrevRotation;
        int (*subproc)(BtlClientWk *, int *) SWAN_ALIGNED(4);
        int subseq;
        int (*ActionSelectProc)(BtlClientWk *a1, unsigned int *a2);
        unsigned int ActionSelectSeq;
        void *returnDataPtr;
        int returnDataSize;
        int dummyReturnData;
        u16 cmdLimitTime;
        u16 gameLimitTime;
        unsigned __int16 AIBagItems[4];
        void *VM;
        u64 AIrandX;
        u64 AIrandMul;
        u64 AIrandAdd;
        u8 bestMonToSwitchIn[6];
        u8 doTrainerMessage[4];
        SWAN_ALIGNED(4)
        void *actPokeParty;
        unsigned __int8 numBattlePositions;
        unsigned __int8 procPokeIdx;
        char prevPokeIdx;
        u8 firstPokeIdx;
        char fStdMsgChanged;
        char basePos;
        SWAN_ALIGNED(4)
        int actionParam[3];
        u8 LauncherCost[3];
        SWAN_ALIGNED(2)
        int cmdQueue;
        int ServerCmdArgs[16];
        int serverCmd;
        int ServerCmdProc;
        int ServerCmdSeq;
        PokeSelectParam pokeSelectParam;
        PokeSelectResult pokeSelectResult;
        SWAN_ALIGNED(2)
        u16 TrainerMsgHeapID;
        __int16 EnemyMonHP;
        u16 AITrainerMsgID;
        u16 SelItemWork[3];
        u8 myID;
        char myType;
        char state;
        char commWaitInfoOn;
        char bagMode;
        char WonderLauncherEnergy;
        u8 changeEscapeCode;
        u8 forceQuitActionSelect;
        u8 cmdCheckTimingCode;
        char currentActionCount;
        char moveInfoPokeIdx;
        char moveInfoMoveIdx;
        char actSelectFlags;
        char myChangePokeCount;
        char NumValidSwitchIns;
        u8 clientTurnCount;
        unsigned __int8 myChangePokePos[6];
        u8 pokestarSeqWork[140];
        char commonWait;
    };

    // Switch In
    // extern void *PokeCon_GetClientMonData(void *a1, int a2, unsigned int a3);
    // extern bool IsOpponentClientID(void *a1, char a2, char a3);
    // extern bool TrainerParam_HasTrainerInfo(void *a1, int a2);
    // extern void Btlv_StringParam_Setup(Btlv_StringParam *a1, char a2, __int16 a3);
    // extern void Btlv_StringParam_AddArg(Btlv_StringParam *a1, int a2);
    // extern int BattleClient_GetSwitchInStrID(BtlClientWk *a1);
    // extern void BtlvCore_DisplayMessageByType(void *a1, Btlv_StringParam *a2);
    // extern int BattleViewCmd_WaitMessage(void *a1);
    // extern unsigned int MainModule_GetClientPokePos(void *a1, int clientID, int partyIndex);
    // extern void sub_21D0088(void *a1, int a2, char a3, char a4);
    // extern int sub_21D00C4(void *a1);
    // extern void BattleClient_UpdateEnemyMonHP(BtlClientWk *a1);
    // extern void sub_21B9730(BtlClientWk *a1, void *a2, void *a3);

    // // Check Fainted
    extern int BattleMon_GetID(void *a1);
    // extern int BattleMon_GetSpecies(void *a1);
    // extern bool BattleMon_IsFainted(void *a1);
    // extern void j_FaintRecord_Add(FaintRecord *result, char a2);
    // extern int BtlSetup_IsBattleType(void *a1, int mask);
    // extern unsigned int j_MainModule_PokeIDToClientID(unsigned int a1);
    // extern void SCQueue_AddMessage(void *a1, int a2, __int16 a3, ...);
    // extern void SCQueue_AddCommon(void *a1, int a2, ...);
    // extern void ServerControl_ClearMonDependentEffects(ServerFlow *a1, void *a2, int a3);
    // extern void BattleMon_ClearForFainted(void *a1);
    // extern int MainModule_GetPlayerClientID(void *a1);
    // extern int BattleMon_GetValue(void *a1, int a2);
    // extern unsigned int GetEnemyMaxLevel(ServerFlow *a1);
    // extern void MainModule_ChangeFriendshipWhenFainted(void *a1, int a2, int a3);
    // extern int j_PosPoke_SwitchOut_0(int result, int a2);
    // extern bool MainModule_IsAllyClientID(int a1, int a2);
    // extern void RecordData_Increment(void *a1, int a2);
    // extern BtlType MainModule_GetBattleType(MainModule *a1);

    // // Get Switch Out ID
    // extern BattleStyle BtlSetup_GetBattleStyle(MainModule *a1);
    // extern int MainModule_GetCommMode(MainModule *a1);
    // extern unsigned int sub_21B1F40(BtlClientWk *a1);

    // Testing First Switch
    extern bool sub_21D1414(BtlvScu *a1, int *a2);
    extern int MainModule_ViewPosToBattlePos(MainModule *a1, char a2);
    extern int j_MainModule_BattlePosToClientID(MainModule *a1, int a2);
    extern int TrainerParam_GetClass(MainModule *a1, int a2);
    extern int sub_21DF8CC(unsigned int a1, int a2, int a3, int a4, int a5);
    extern void sub_21DFA28(int a1, int a2);
    extern void *PokeCon_GetFrontPokeData(void *a1, int a2);
    extern int sub_21D37D8(BtlvScu_Field154 *a1);
    extern void sub_21DF39C(unsigned int a1, int a2);
    extern void sub_21D1338(s32 a1);
    extern void sub_21D40CC(BtlvScu *a1, int *a2, int a3, unsigned int a4, int a5);
    extern bool BattleViewCmd_WaitEffect();
    extern void sub_21DFC54(int *a1);
    extern void sub_21D4F00(StrBuf *a1, int a2, unsigned int a3, ...);
    extern int sub_21D2F1C(BtlvScu *a1);
    extern void *BattleMon_GetViewSrcData(void *a1);
    extern void sub_21DF85C(void *a1, int a2);
    extern int GetPlayerClientID(MainModule *a1);
    extern void sub_21D39CC(int a1);
    extern void BattleViewCmd_AddAnim(int a1);
    extern bool sub_21DFC94(int a1);
    extern void sub_21D3758(BtlvScu_Field154 *a1);
    extern void sub_21D45D0(BtlvScu *a1);
    extern void sub_21DFC78(int a1);
    extern void sub_21D2E60(BtlvScu *a1, StrBuf *a2, int a3, int a4);
    extern int BattleMon_GetID(void *a1);

    int THUMB_BRANCH_sub_21D1638(int *a1, BtlvScu *a2)
    {
        BtlvScuDataSingles *v4; // r6
        int v6;                 // r0
        int Class;              // r0
        void *FrontPokeData;    // r0
        void *ViewSrcData;      // r0
        int v10;                // r0
        int PlayerClientID;     // r0
        void *v12;              // r0
        void *v13;              // r0
        int v16;                // [sp+0h] [bp-60h]
        int v15;                // [sp+4h] [bp-5Ch]
        int var58;              // [sp+8h] [bp-58h]
        int v17[8];             // [sp+Ch] [bp-54h] BYREF
        int v18[13];            // [sp+2Ch] [bp-34h] BYREF
        int check;
        int trainerId;
        int trainerClass;

        v4 = &a2->field_F0;
        if (a2->field_150)
        {
            return sub_21D1414(a2, a1);
        }
        v6 = *a1;
        // k::Printf("\n\nWe are in here. Testing. v6 is %d\n", v6);
        if (*a1 <= 0xB)
        {
            if (IsEqual(v6, 0))
            {
                v15 = MainModule_ViewPosToBattlePos(a2->mainModule, 1);
                var58 = j_MainModule_BattlePosToClientID(a2->mainModule, v15);
                Class = TrainerParam_GetClass(a2->mainModule, var58);
                sub_21DF8CC(Class, 9, 0, 0, 0);
                sub_21DFA28(9, 0);
                v4->ViewPos = 1;
                v4->ClientID = var58;
                v4->BattlePos = v15;
                FrontPokeData = PokeCon_GetFrontPokeData(a2->pokeCon, v4->BattlePos);
                v4->BattleMon = FrontPokeData;
                v4->MonID = BattleMon_GetID(FrontPokeData);
                goto LABEL_6;
            }
            else if (IsEqual(v6, 1))
            {
                if (!sub_21D37D8(&a2->field_154))
                {
                    return 0;
                }
                sub_21DF39C(v4->ViewPos, 567);
                sub_21D1338(2);
                goto LABEL_7;
            }
            else if (IsEqual(v6, 2))
            {
                if (BattleViewCmd_WaitEffect())
                {
                    return 0;
                }
                sub_21D40CC(a2, v18, v4->ClientID, 4u, 1);
                sub_21DFC54(v18);
                trainerId = a2->mainModule->btlSetup->TrainerSetups[1]->TrID;
                trainerClass = a2->mainModule->btlSetup->TrainerSetups[1]->TrClass;
                // k::Printf("\n\nsub_21, v6 = %d,  TrainerId is %d and TrainerClass is %d\n", v6, trainerId, trainerClass);

                if (trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerClass == 116 || trainerClass == 115 || trainerClass == 113 || trainerClass == 112 || trainerClass == 117 || trainerClass == 115 || trainerClass == 159 || trainerClass == 193 || trainerClass == 80 || trainerClass == 78 || trainerClass == 79 || trainerClass == 81)
                {
                    sub_21D4F00(a2->strbuf1, 232, 1u, v4->ClientID, v16);
                }
                else if (trainerId == 634){
                    sub_21D4F00(a2->strbuf1, 233, 1u, v4->ClientID, v16);
                }
                else
                {
                    sub_21D4F00(a2->strbuf1, 7, 1u, v4->ClientID, v16);
                }
                // sub_21D4F00(a2->strbuf1, 7, 1u, v4->ClientID, v16);
                goto LABEL_28;
            }
            else if (IsEqual(v6, 3))
            {
                if (!sub_21D2F1C(a2))
                {
                    return 0;
                }
                sub_21DF39C(v4->ViewPos, 568);
                goto LABEL_6;
            }
            else if (IsEqual(v6, 4))
            {
                if (!sub_21D37D8(&a2->field_154) || BattleViewCmd_WaitEffect())
                {
                    return 0;
                }

                trainerId = a2->mainModule->btlSetup->TrainerSetups[1]->TrID;
                trainerClass = a2->mainModule->btlSetup->TrainerSetups[1]->TrClass;
                // k::Printf("\n\nsub_21 TrainerId is %d and TrainerClass is %d\n", trainerId, trainerClass);

                if (trainerId == 491)
                {
                    check = 228;
                }
                else if (trainerId == 507)
                {
                    check = 229;
                }
                else if (trainerId == 508)
                {
                    check = 230;
                }
                else if (trainerId == 509)
                {
                    check = 231;
                }
                else if (trainerId == 634){
                    check = 234;
                }
                else
                {
                    check = 14;
                    sub_21D4F00(a2->strbuf1, check, 2u, 1, v4->MonID);
                    goto LABEL_28;
                }
                sub_21D4F00(a2->strbuf1, check, 1u, v4->MonID);
                goto LABEL_28;
            }

            else if (IsEqual(v6, 5))
            {
                if (!sub_21D2F1C(a2))
                {
                    return 0;
                }
                ViewSrcData = BattleMon_GetViewSrcData(v4->BattleMon);
                sub_21DF85C(ViewSrcData, v4->ViewPos);

                trainerId = a2->mainModule->btlSetup->TrainerSetups[1]->TrID;
                trainerClass = a2->mainModule->btlSetup->TrainerSetups[1]->TrClass;
                // k::Printf("\n\nsub_21 TrainerId is %d and TrainerClass is %d\n", trainerId, trainerClass);

                if ((trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerId == 634) && BattleMon_GetID(ViewSrcData) >=6){
                    check = 676;
                } else {
                    check = 569;
                }

                sub_21DF39C(v4->ViewPos, check);
                v10 = 1;
                goto LABEL_20;
            }
            else if (IsEqual(v6, 6))
            {
                if (!sub_21D37D8(&a2->field_154) || BattleViewCmd_WaitEffect())
                {
                    return 0;
                }
                PlayerClientID = GetPlayerClientID(a2->mainModule);
                sub_21D40CC(a2, v17, PlayerClientID, 4u, 0);
                sub_21DFC54(v17);
                goto LABEL_7;
            }
            else if (IsEqual(v6, 7))
            {
                sub_21D39CC((int)&a2->field_48[3 * a2->field_F0.BattlePos]);
                BattleViewCmd_AddAnim(562);
                goto LABEL_7;
            }
            else if (IsEqual(v6, 8))
            {
                if (BattleViewCmd_WaitEffect() || sub_21DFC94(0))
                {
                    return 0;
                }
                v4->ViewPos = 0;
                v4->BattlePos = MainModule_ViewPosToBattlePos(a2->mainModule, v4->ViewPos);
                v12 = PokeCon_GetFrontPokeData(a2->pokeCon, v4->BattlePos);
                v4->BattleMon = v12;
                v4->MonID = BattleMon_GetID(v12);
                v13 = BattleMon_GetViewSrcData(v4->BattleMon);
                sub_21DF85C(v13, v4->ViewPos);
                BattleViewCmd_AddAnim(564);
                sub_21D4F00(a2->strbuf1, 11, 1u, v4->MonID);
            LABEL_28:
                sub_21D2E60(a2, a2->strbuf1, 80, 0);
                goto LABEL_7;
            }
            else if (IsEqual(v6, 9))
            {
                if (!sub_21D2F1C(a2))
                {
                    return 0;
                }
                v10 = 0;
            LABEL_20:
                sub_21DFC78(v10);
            LABEL_6:
                sub_21D3758(&a2->field_154);
                goto LABEL_7;
            }
            else if (IsEqual(v6, 0xA))
            {
                if (!sub_21D37D8(&a2->field_154))
                {
                    return 0;
                }
                sub_21D45D0(a2);
            LABEL_7:
                ++*a1;
                return 0;
            }
            else if (IsEqual(v6, 0xB))
            {
                if (BattleViewCmd_WaitEffect())
                {
                    return 0;
                }
                sub_21D39CC((int)&a2->field_48[3 * v4->BattlePos]);
                return 1;
            }
            else
            {
                return 0;
            }
        }
        return 0;
    }

   
}