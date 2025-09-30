#include "../swan-master/swantypes.h"
#include "../kPrint.h"

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long

// Uses ESDB_For_LegendaryPokemon3.yml

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

    struct StatusWindow
    {
        void *mon;
        void *scu;
        u8 battlePos;
        u8 viewPos;
        u8 dispFlag;
        u8 enableFlag;
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

    struct BtlvScu
    {
        void *MessageWindow;
        void *MsgWinBitmap;
        void *LevelUpWin;
        void *LevelUpBitmap;
        int LevelUpWinCharPos;
        int AbilityPopupNCGR;
        _DWORD printsys;
        _DWORD dword1C;
        _BYTE byte20;
        _BYTE gap21[3];
        void *defaultfont;
        void *smallfont;
        void *callbackMgr;
        int printstream;
        StrBuf *strbuf1;
        StrBuf *strbuf2;
        StrBuf *strbuf3;
        u8 taskCounter[6];
        StatusWindow statusWindows[6];
        AbilityPopup abilityPopups[2];
        void *abilityPopupNCGRHead;
        int abilityPopupNCGR;
        int (*initFunc)(int *, BtlvScu *);
        int (*loopFunc)(int *, BtlvScu *);
        BtlvScu *work;
        int seq;
        u8 procWork[64];
        void *viewCore;
        MainModule *mainModule;
        void *pokeCon;
        u16 heapID;
        char printImmediateFlag;
        char printseq;
        u8 myID;
        char MessageFinishedNow;
        char field_142;
        char field_143;
        int printstate;
        __int16 printwait;
        __int16 printwaitorg;
        __int16 printwaitEOM;
        _BYTE byte14E;
        _BYTE BattleStartSeq;
        char SkipBattleStartFlag;
        MessageWinVisibilityWork messageWinVisibilityWork;
        void *levelUpMon;
        __int16 levelUpInfo;
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

    struct SwitchInAnimWork
    {
        StatusWindow *statusWin;
        u16 seq;
        u16 line;
        u8 *taskCounter;
    };

    struct SwitchOutAnimWork
    {
        StatusWindow *statusWin;
        u16 seq;
        u16 viewPos;
        u16 animID;
        u8 *taskCounter;
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

    extern PartyPkm *BattleMon_GetViewSrcData(void *a1);
    extern void *GFL_TCBExMgrAddTask(void *a1, void *a2, u32 a3, int a4);
    extern void BtlvEffect_AddMon(PartyPkm *a1, int a2);
    extern void *GFL_TCBExGetData(void *tcb);
    extern void TCBTask_SwitchIn(void *a1, int a2);
    extern void BtlvEffect_AddAnimAtPos(unsigned int a1, int a2);
    extern BattleMon *PokeCon_GetClientMonData(void *a1, int a2, unsigned int a3);
    extern int MainModule_BattlePosToViewPos(MainModule *a1, int a2);

    void THUMB_BRANCH_SAFESTACK_BtlvScu_StartSwitchIn(BtlvScu *a1, int a2, int a3, unsigned int a4, int a5)
    {
        void *v9;                 // r0
        SwitchInAnimWork *Data;   // r0
        BattleMon *ClientMonData; // r6
        int v12;                  // r4
        int trainerId;
        int animation;
        PartyPkm *ViewSrcData; // r0

        v9 = GFL_TCBExMgrAddTask(a1->callbackMgr, (void *)TCBTask_SwitchIn, 0xCu, 1);
        Data = (SwitchInAnimWork *)GFL_TCBExGetData(v9);
        Data->statusWin = &a1->statusWindows[a2];
        Data->taskCounter = &a1->taskCounter[1];
        Data->seq = 0;
        ++a1->taskCounter[1];
        ClientMonData = PokeCon_GetClientMonData(a1->pokeCon, a3, a4);
        v12 = MainModule_BattlePosToViewPos(a1->mainModule, a2);
        ViewSrcData = BattleMon_GetViewSrcData(ClientMonData);
        BtlvEffect_AddMon(ViewSrcData, v12);
        // // k::Printf("\n\na5 is %d\n\n", a5);
        if (!a5)
        {
            if (a1->mainModule->btlSetup->btlType != 0)
            {
                trainerId = a1->mainModule->btlSetup->TrainerSetups[1]->TrID;
                // // k::Printf("\n\nThe Pokemon's ID is %d and the species is %d\n\n", a2, ClientMonData->Species);
                if ((trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerId == 634) && a2 >= 6)
                {
                    animation = 677;
                }
                else
                {
                    animation = 621;
                }
            }
            else
            {
                animation = 621;
            }

            BtlvEffect_AddAnimAtPos(v12, animation);
        }
    }

    extern void TCBTask_SwitchOut(void *a1, int a2);
    extern void BtlvEffect_RemoveGauge(int a1);
    extern void BtlvEffect_RemoveMon(int a1);
    extern int MainModule_ViewPosToBattlePos(MainModule *a1, char a2);

    void THUMB_BRANCH_SAFESTACK_BtlvScu_StartSwitchOut(BtlvScu *a1, int a2, int a3, int a4)
    {
        int v6;                  // r4
        void *v7;                // r0
        SwitchOutAnimWork *Data; // r0
        int trainerId;
        int animation;

        v6 = a3;
        if (!a4 && a3)
        {
            v7 = GFL_TCBExMgrAddTask(a1->callbackMgr, (void *)TCBTask_SwitchOut, 0x10u, 1);
            Data = (SwitchOutAnimWork *)GFL_TCBExGetData(v7);
            Data->viewPos = a2;
            Data->statusWin = &a1->statusWindows[a2];
            Data->taskCounter = &a1->taskCounter[2];

            if (!v6)
            {
                // LOWORD(v6) = 620;
                v6 = (v6 & 0xFFFF) | 620;
            }

            if (a1->mainModule->btlSetup->btlType != 0)
            {
                trainerId = a1->mainModule->btlSetup->TrainerSetups[1]->TrID;
                // // k::Printf("\n\nThe trainer ID is %d.  The Pokemon ID is %d.\n\n", trainerId, MainModule_ViewPosToBattlePos(a1->mainModule, a2));
                if ((trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerId == 634) && MainModule_ViewPosToBattlePos(a1->mainModule, a2) >= 6)
                {
                    animation = 678;
                }
                else
                {
                    animation = 620;
                }
            }
            else
            {
                animation = 620;
            }

            Data->animID = animation;
            Data->seq = 0;
            ++*Data->taskCounter;
        }
        else
        {
            BtlvEffect_RemoveGauge(a2);
            BtlvEffect_RemoveMon(a2);
        }
    }

    extern int BtlvCore_WaitMessage(void *a1);
    extern int BattleClient_GetSwitchOutStrID(BtlClientWk *a1, int a2, _DWORD *a3);
    extern void Btlv_StringParam_Setup(Btlv_StringParam *a1, char a2, __int16 a3);
    extern void Btlv_StringParam_AddArg(Btlv_StringParam *a1, int a2);
    extern void BtlvCore_StartMessage(void *a1, Btlv_StringParam *a2);

    int THUMB_BRANCH_SAFESTACK_ServerCommand_SwitchOutMessage(BtlClientWk *a1, int *a2, int *a3)
    {
        int v4;                 // r1
        __int16 SwitchOutStrID; // r0
        unsigned int v9;        // [sp+0h] [bp-18h] BYREF
        int trainerId;

        v4 = *a2;
        if (v4)
        {
            if (v4 == 1 && BtlvCore_WaitMessage(a1->btlvCore))
            {
                return 1;
            }
        }
        else
        {
            SwitchOutStrID = BattleClient_GetSwitchOutStrID(a1, *a3, &v9);

            if (*a3 != a1->myID)
            {
                if (a1->mainModule->btlSetup->btlType != 0)
                {
                    trainerId = a1->mainModule->btlSetup->TrainerSetups[1]->TrID;
                    //  // k::Printf("\n\nThe trainer ID is %d. The client ID is %d.  The pokemon ID is %d. switchoutstrID is %d\n\n", trainerId, *a3, a3[1], SwitchOutStrID);
                    if (trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerId == 634)
                    {
                        SwitchOutStrID = 226;
                    }
                    else if (trainerId == 634)
                    {
                        SwitchOutStrID = 238;
                    }
                }
            }

            Btlv_StringParam_Setup(&a1->strParam, 1, SwitchOutStrID);
            if (v9 && (SwitchOutStrID != 226 || SwitchOutStrID != 238))
            {
                Btlv_StringParam_AddArg(&a1->strParam, *a3);
            }
            Btlv_StringParam_AddArg(&a1->strParam, a3[1]);
            BtlvCore_StartMessage(a1->btlvCore, &a1->strParam);
            ++*a2;
        }
        return 0;
    }

    // struct SWAN_PACKED SWAN_ALIGNED(1) BtlvScuDataSingles
    // {
    //     BattleMon *BattleMon;
    //     u8 BattlePos;
    //     u8 ViewPos;
    //     u8 MonID;
    //     u8 ClientID;
    //     char AllyClientID;
    // };

    // struct BtlvBallGaugeParam
    // {
    //     int type;
    //     int status[6];
    //     int pokestar;
    // };

    // extern bool BtlvScu_SkipBattleStartSingles(BtlvScu *a1, int *a2);
    // extern int  j_MainModule_BattlePosToClientID(MainModule *a1, int a2);
    // extern int TrainerParam_GetClass(MainModule *a1, int a2);
    // extern void BtlvEffect_SetupTrainerSprite(unsigned int a1, int a2, int a3, int a4, int a5);
    // extern void BtlvEffect_SetTrainerAnimSpeed(int a1, int a2);
    // extern BattleMon * PokeCon_GetMonDataAtBattlePos(void *a1, int a2);
    // extern int  BattleMon_GetID(BattleMon *a1);
    // extern int  MsgWinVisibility_Update(MessageWinVisibilityWork *a1);
    // extern void BattleStartFade(s32 a1);
    // extern bool BtlvEffect_IsExecuting();
    // extern void BtlvScu_CreateBallGauge(BtlvScu *a1, BtlvBallGaugeParam *a2, int a3, unsigned int a4, int a5);
    // extern void BtlvStr_MakeStringStandard(StrBuf *a1, int a2, unsigned int a3, ...);
    // extern void BtlvEffect_CreateBallGauge(BtlvBallGaugeParam *a1);
    // extern int BtlvScu_WaitMessage(BtlvScu *a1);
    // extern int MainModule_GetPlayerClientID(MainModule *a1);
    // extern void BtlvEffect_AddAnim(int a1);
    // extern void BtlvScu_ClearMessageWindow(BtlvScu *a1);
    // extern void StatusWindow_StartDisplay(StatusWindow *a1);
    // extern void MsgWinVisibility_Hide(MessageWinVisibilityWork *a1);
    // extern void BtlvEffect_RemoveBallGauge(int a1);
    // extern void BtlvScu_StartMessage(BtlvScu *a1, StrBuf *a2, int a3, int a4);
    // extern bool BtlvEffect_CheckBallGaugeIsExecuting(int a1);

    // int THUMB_BRANCH_BtlvScu_StartTrainerSinglesProc(int *a1, BtlvScu *a2)
    // {
    //     BtlvScuDataSingles *procWork;                // r6
    //     int v6;                        // r0
    //     int Class;                     // r0
    //     BattleMon *MonDataAtBattlePos; // r0
    //     PartyPkm *ViewSrcData;         // r0
    //     int v10;                       // r0
    //     int PlayerClientID;            // r0
    //     BattleMon *v12;                // r0
    //     PartyPkm *v13;                 // r0
    //     int v16;                       // [sp+0h] [bp-60h]
    //     int v15;                       // [sp+4h] [bp-5Ch]
    //     int var58;                     // [sp+8h] [bp-58h]
    //     int v17[8];                    // [sp+Ch] [bp-54h] BYREF
    //     int trainerId;
    //     int trainerClass;
    //     int check;
    //     BtlvBallGaugeParam v18; // [sp+2Ch] [bp-34h] BYREF

    //     procWork = (BtlvScuDataSingles*)a2->procWork;
    //     if (a2->SkipBattleStartFlag)
    //     {
    //         return BtlvScu_SkipBattleStartSingles(a2, a1);
    //     }
    //     v6 = *a1;

    //     if (*a1 <= 0xB)
    //     {
    //         if (IsEqual(v6, 0))
    //         {
    //             v15 = MainModule_ViewPosToBattlePos(a2->mainModule, 1);
    //             var58 = j_MainModule_BattlePosToClientID(a2->mainModule, v15);
    //             Class = TrainerParam_GetClass(a2->mainModule, var58);
    //             BtlvEffect_SetupTrainerSprite(Class, 9, 0, 0, 0);
    //             BtlvEffect_SetTrainerAnimSpeed(9, 0);
    //             procWork->ViewPos = 1;
    //             procWork->ClientID = var58;
    //             procWork->BattlePos = v15;
    //             MonDataAtBattlePos = PokeCon_GetMonDataAtBattlePos(a2->pokeCon, procWork->BattlePos);
    //             procWork->BattleMon = MonDataAtBattlePos;
    //             procWork->MonID = BattleMon_GetID(MonDataAtBattlePos);
    //             goto LABEL_6;
    //         }
    //         else if (IsEqual(v6, 1))
    //         {
    //             if (!MsgWinVisibility_Update(&a2->messageWinVisibilityWork))
    //             {
    //                 return 0;
    //             }
    //             BtlvEffect_AddAnimAtPos(procWork->ViewPos, 567);
    //             BattleStartFade(2);
    //             goto LABEL_7;
    //         }
    //         else if (IsEqual(v6, 2))
    //         {
    //             if (BtlvEffect_IsExecuting())
    //             {
    //                 return 0;
    //             }
    //             BtlvScu_CreateBallGauge(a2, &v18, procWork->ClientID, 4u, 1);
    //             BtlvEffect_CreateBallGauge(&v18);

    //             trainerId = a2->mainModule->btlSetup->TrainerSetups[1]->TrID;
    //             trainerClass = a2->mainModule->btlSetup->TrainerSetups[1]->TrClass;
    //             // k::Printf("\n\nsub_21, v6 = %d,  TrainerId is %d and TrainerClass is %d\n", v6, trainerId, trainerClass);

    //             if (trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerClass == 116 || trainerClass == 115 || trainerClass == 113 || trainerClass == 112 || trainerClass == 117 || trainerClass == 115 || trainerClass == 159 || trainerClass == 193 || trainerClass == 80 || trainerClass == 78 || trainerClass == 79 || trainerClass == 81)
    //             {
    //                 // sub_21D4F00(a2->strbuf1, 232, 1u, v4->ClientID, v16);
    //                 BtlvStr_MakeStringStandard(a2->strbuf1, 232, 1u, procWork->ClientID, v16);
    //             }
    //             else if (trainerId == 634)
    //             {
    //                 // sub_21D4F00(a2->strbuf1, 233, 1u, v4->ClientID, v16);
    //                 BtlvStr_MakeStringStandard(a2->strbuf1, 233, 1u, procWork->ClientID, v16);
    //             }
    //             else
    //             {
    //                 // sub_21D4F00(a2->strbuf1, 7, 1u, v4->ClientID, v16);
    //                 BtlvStr_MakeStringStandard(a2->strbuf1, 7, 1u, procWork->ClientID, v16);
    //             }
    //             // sub_21D4F00(a2->strbuf1, 7, 1u, v4->ClientID, v16);
    //             goto LABEL_28;
    //         }
    //         else if (IsEqual(v6, 3))
    //         {
    //             if (!BtlvScu_WaitMessage(a2))
    //             {
    //                 return 0;
    //             }
    //             BtlvEffect_AddAnimAtPos(procWork->ViewPos, 568);
    //             goto LABEL_6;
    //         }
    //         else if (IsEqual(v6, 4))
    //         {
    //             if (!MsgWinVisibility_Update(&a2->messageWinVisibilityWork) || BtlvEffect_IsExecuting())
    //             {
    //                 return 0;
    //             }

    //             trainerId = a2->mainModule->btlSetup->TrainerSetups[1]->TrID;
    //             trainerClass = a2->mainModule->btlSetup->TrainerSetups[1]->TrClass;
    //             // k::Printf("\n\nsub_21 TrainerId is %d and TrainerClass is %d\n", trainerId, trainerClass);

    //             if (trainerId == 491)
    //             {
    //                 check = 228;
    //             }
    //             else if (trainerId == 507)
    //             {
    //                 check = 229;
    //             }
    //             else if (trainerId == 508)
    //             {
    //                 check = 230;
    //             }
    //             else if (trainerId == 509)
    //             {
    //                 check = 231;
    //             }
    //             else if (trainerId == 634)
    //             {
    //                 check = 234;
    //             }
    //             else
    //             {
    //                 check = 14;
    //                 BtlvStr_MakeStringStandard(a2->strbuf1, check, 2u, 1, procWork->MonID);
    //                 goto LABEL_28;
    //             }
    //             BtlvStr_MakeStringStandard(a2->strbuf1, check, 1u, 1, procWork->MonID);
    //             goto LABEL_28;
    //         }

    //         else if (IsEqual(v6, 5))
    //         {
    //             if (!BtlvScu_WaitMessage(a2))
    //             {
    //                 return 0;
    //             }
    //             ViewSrcData = BattleMon_GetViewSrcData(procWork->BattleMon);
    //             BtlvEffect_AddMon(ViewSrcData, procWork->ViewPos);

    //             trainerId = a2->mainModule->btlSetup->TrainerSetups[1]->TrID;
    //             trainerClass = a2->mainModule->btlSetup->TrainerSetups[1]->TrClass;
    //             // k::Printf("\n\nsub_21 TrainerId is %d and TrainerClass is %d\n", trainerId, trainerClass);

    //             if ((trainerId == 491 || trainerId == 507 || trainerId == 508 || trainerId == 509 || trainerId == 634) && procWork->MonID >= 6)
    //             {
    //                 check = 676;
    //             }
    //             else
    //             {
    //                 check = 569;
    //             }

    //             BtlvEffect_AddAnimAtPos(procWork->ViewPos, check);
    //             v10 = 1;
    //             goto LABEL_20;
    //         }
    //         else if (IsEqual(v6, 6))
    //         {
    //             if (!MsgWinVisibility_Update(&a2->messageWinVisibilityWork) || BtlvEffect_IsExecuting())
    //             {
    //                 return 0;
    //             }
    //             PlayerClientID = MainModule_GetPlayerClientID(a2->mainModule);
    //             BtlvScu_CreateBallGauge(a2, (BtlvBallGaugeParam*)v17, PlayerClientID, 4u, 0);
    //             BtlvEffect_CreateBallGauge((BtlvBallGaugeParam*)v17);
    //             goto LABEL_7;
    //         }
    //         else if (IsEqual(v6, 7))
    //         {
    //             StatusWindow_StartDisplay(&a2->statusWindows[a2->procWork[4]]);
    //             BtlvEffect_AddAnim(562);
    //             goto LABEL_7;
    //         }
    //         else if (IsEqual(v6, 8))
    //         {
    //             if (BtlvEffect_IsExecuting() || BtlvEffect_CheckBallGaugeIsExecuting(0))
    //             {
    //                 return 0;
    //             }
    //             procWork->ViewPos = 0;
    //             procWork->BattlePos = MainModule_ViewPosToBattlePos(a2->mainModule, procWork->ViewPos);
    //             v12 = PokeCon_GetMonDataAtBattlePos(a2->pokeCon, procWork->BattlePos);
    //             procWork->BattleMon = v12;
    //             procWork->MonID = BattleMon_GetID(v12);
    //             v13 = BattleMon_GetViewSrcData(procWork->BattleMon);
    //             BtlvEffect_AddMon(v13, procWork->ViewPos);
    //             BtlvEffect_AddAnim(564);
    //             BtlvStr_MakeStringStandard(a2->strbuf1, 11, 1u, procWork->MonID);
    //         LABEL_28:
    //             BtlvScu_StartMessage(a2, a2->strbuf1, 80, 0);
    //             goto LABEL_7;
    //         }
    //         else if (IsEqual(v6, 9))
    //         {
    //             if (!BtlvScu_WaitMessage(a2))
    //             {
    //                 return 0;
    //             }
    //             v10 = 0;
    //         LABEL_20:
    //             BtlvEffect_RemoveBallGauge(v10);
    //         LABEL_6:
    //             MsgWinVisibility_Hide(&a2->messageWinVisibilityWork);
    //             goto LABEL_7;
    //         }
    //         else if (IsEqual(v6, 0xA))
    //         {
    //             if (!MsgWinVisibility_Update(&a2->messageWinVisibilityWork))
    //             {
    //                 return 0;
    //             }
    //             BtlvScu_ClearMessageWindow(a2);
    //         LABEL_7:
    //             ++*a1;
    //             return 0;
    //         }
    //         else if (IsEqual(v6, 0xB))
    //         {
    //             if (BtlvEffect_IsExecuting())
    //             {
    //                 return 0;
    //             }
    //             StatusWindow_StartDisplay(&a2->statusWindows[procWork->BattlePos]);
    //             return 1;
    //         }
    //         else
    //         {
    //             return 0;
    //         }
    //     }
    //     return 0;
    // }
}