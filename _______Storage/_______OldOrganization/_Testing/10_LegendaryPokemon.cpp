#include "../swan-master/swantypes.h"
#include "../kPrint.h"

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long

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

// Uses ESDB_For_LegendaryPokemon.yml

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
    extern void *PokeCon_GetClientMonData(void *a1, int a2, unsigned int a3);
    extern bool IsOpponentClientID(void *a1, char a2, char a3);
    extern bool TrainerParam_HasTrainerInfo(void *a1, int a2);
    extern void Btlv_StringParam_Setup(Btlv_StringParam *a1, char a2, __int16 a3);
    extern void Btlv_StringParam_AddArg(Btlv_StringParam *a1, int a2);
    extern int BattleClient_GetSwitchInStrID(BtlClientWk *a1);
    extern void BtlvCore_DisplayMessageByType(void *a1, Btlv_StringParam *a2);
    extern int BattleViewCmd_WaitMessage(void *a1);
    extern unsigned int MainModule_GetClientPokePos(void *a1, int clientID, int partyIndex);
    extern void sub_21D0088(void *a1, int a2, char a3, char a4);
    extern int sub_21D00C4(void *a1);
    extern void BattleClient_UpdateEnemyMonHP(BtlClientWk *a1);
    extern void sub_21B9730(BtlClientWk *a1, void *a2, void *a3);

    // Check Fainted
    extern int BattleMon_GetID(void *a1);
    extern int BattleMon_GetSpecies(void *a1);
    extern bool BattleMon_IsFainted(void *a1);
    extern void j_FaintRecord_Add(FaintRecord *result, char a2);
    extern int BtlSetup_IsBattleType(void *a1, int mask);
    extern unsigned int j_MainModule_PokeIDToClientID(unsigned int a1);
    extern void SCQueue_AddMessage(void *a1, int a2, __int16 a3, ...);
    extern void SCQueue_AddCommon(void *a1, int a2, ...);
    extern void ServerControl_ClearMonDependentEffects(ServerFlow *a1, void *a2, int a3);
    extern void BattleMon_ClearForFainted(void *a1);
    extern int MainModule_GetPlayerClientID(void *a1);
    extern int BattleMon_GetValue(void *a1, int a2);
    extern unsigned int GetEnemyMaxLevel(ServerFlow *a1);
    extern void MainModule_ChangeFriendshipWhenFainted(void *a1, int a2, int a3);
    extern int j_PosPoke_SwitchOut_0(int result, int a2);
    extern bool MainModule_IsAllyClientID(int a1, int a2);
    extern void RecordData_Increment(void *a1, int a2);
    extern BtlType MainModule_GetBattleType(MainModule *a1);

    // Get Switch Out ID
    extern BattleStyle BtlSetup_GetBattleStyle(MainModule *a1);
    extern int MainModule_GetCommMode(MainModule *a1);
    extern unsigned int sub_21B1F40(BtlClientWk *a1);

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

    int THUMB_BRANCH_ServerControl_CheckFainted(ServerFlow *a1, void *a2)
    {
        int ID;             // r6
        unsigned int v5;    // r5
        int Value;          // r5
        int v7;             // r5
        int PlayerClientID; // r1
        void *mainModule;   // r0
        int check;
        int trainerId;
        int v10; // r1
        int a3;  // [sp+4h] [bp-1Ch]

        ID = BattleMon_GetID(a2);
        if (!a1->pokeInFlag[ID] && BattleMon_IsFainted(a2))
        {
            a1->pokeInFlag[ID] = 1;
            j_FaintRecord_Add(&a1->faintRecord, ID);

            if ((!BtlSetup_IsBattleType((void *)a1->mainModule, 512) || !j_MainModule_PokeIDToClientID(ID)) && a1->thruDeadMsgPokeID != ID)
            {
                // SCQueue_AddMessage(a1->serverCommandQueue, 91, 0, ID, -65536); // 0: [VAR PKNICK(0)] fainted!

                if (a1->mainModule->btlSetup->btlType != 0)
                {
                    trainerId = a1->mainModule->btlSetup->TrainerSetups[1]->TrID;

                    // k::Printf("\n\nCheck Fainted: TrainerID is %d and BattleMon id is %d and Pokemon Species is %d\n\n", trainerId, ID, BattleMon_GetSpecies(a2));

                    if (trainerId == 491 && ID >= 6)
                    {
                        if (BattleMon_GetSpecies(a2) == 638)
                        {

                            check = 1165;
                        }
                        else
                        {
                            check = 1168;
                        }
                    }
                    else if (trainerId == 507 && ID >= 6)
                    {
                        if (BattleMon_GetSpecies(a2) == 640)
                        {
                            check = 1171;
                        }
                        else
                        {
                            check = 1174;
                        }
                    }
                    else if (trainerId == 508 && ID >= 6)
                    {
                        if (BattleMon_GetSpecies(a2) == 639)
                        {
                            check = 1177;
                        }
                        else
                        {
                            check = 1180;
                        }
                    }

                    else if (trainerId == 509 && ID >= 6)
                    {
                        if (BattleMon_GetSpecies(a2) == 647)
                        {
                            check = 1183;
                        }
                        else
                        {
                            check = 1176;
                        }
                    }
                    else if (trainerId == 634 && ID >= 6)
                    {
                        check = 1234;
                    }
                    else
                    {
                        check = 0;
                    }
                } else {
                    check = 0;
                }

                SCQueue_AddMessage(a1->serverCommandQueue, 91, check, ID, -65536);
            }
            SCQueue_AddCommon(a1->serverCommandQueue, 57, ID);
            a3 = 0;
            ServerControl_ClearMonDependentEffects(a1, a2, 0);
            BattleMon_ClearForFainted(a2);
            v5 = j_MainModule_PokeIDToClientID(ID);
            if (v5 == MainModule_GetPlayerClientID(a1->mainModule))
            {
                Value = BattleMon_GetValue(a2, 15);
                if (Value + 30 <= (int)GetEnemyMaxLevel(a1))
                {
                    a3 = 1;
                }
                MainModule_ChangeFriendshipWhenFainted(a1->mainModule, (int)a2, a3);
            }
            j_PosPoke_SwitchOut_0((int)&a1->PosPoke, ID);
            v7 = j_MainModule_PokeIDToClientID(ID);
            PlayerClientID = MainModule_GetPlayerClientID(a1->mainModule);
            if (v7 == PlayerClientID)
            {
                mainModule = a1->mainModule;
                v10 = 76;
            }
            else
            {
                if (MainModule_IsAllyClientID(v7, PlayerClientID))
                {
                    // // k::Printf("Successfully returned 1. \n");
                    return 1;
                }
                RecordData_Increment(a1->mainModule, 25);
                mainModule = a1->mainModule;
                v10 = 82;
            }
            RecordData_Increment(mainModule, v10);
            // // k::Printf("Successfully returned 1. \n");
            return 1;
        }
        // // k::Printf("Successfully returned 0. \n");
        return 0;
    }

    u16 THUMB_BRANCH_sub_21D2DA4(BtlvScu *a1, int a2)
    {
        BtlType BattleType; // r0
        u16 result;         // r0
        int trainerId;
        int trainerClass;

        BattleType = MainModule_GetBattleType(a1->mainModule);
        //// k::Printf("\nCheck\n");
        if (BattleType > BtlType_Online)
        {
            result = 1;
            if (a2 != 1)
            {
                return 2;
            }
        }
        else
        {
            if (BattleType == BtlType_Trainer || BattleType == BtlType_Facility)
            {
                trainerId = a1->mainModule->btlSetup->TrainerSetups[1]->TrID;
                trainerClass = a1->mainModule->btlSetup->TrainerSetups[1]->TrClass;
                // // k::Printf("\nTrainerId is %d and trainerClass is %d\n", trainerId, trainerClass);
                if (trainerId == 491)
                {
                    if (a2 == 1)
                    {
                        result = 214;
                    }
                    else if (a2 == 2)
                    {
                        result = 215;
                    }
                    else
                    {
                        result = 216;
                    }
                }
                else if (trainerId == 507)
                {
                    if (a2 == 1)
                    {
                        result = 217;
                    }
                    else if (a2 == 2)
                    {
                        result = 218;
                    }
                    else
                    {
                        result = 219;
                    }
                }
                else if (trainerId == 508)
                {
                    if (a2 == 1)
                    {
                        result = 220;
                    }
                    else if (a2 == 2)
                    {
                        result = 221;
                    }
                    else
                    {
                        result = 222;
                    }
                }
                else if (trainerId == 509)
                {
                    if (a2 == 1)
                    {
                        result = 223;
                    }
                    else if (a2 == 2)
                    {
                        result = 224;
                    }
                    else
                    {
                        result = 225;
                    }
                }
                else if (trainerId == 635)
                {
                    if (a2 == 1)
                    {
                        result = 235;
                    }
                    else if (a2 == 2)
                    {
                        result = 236;
                    }
                    else
                    {
                        result = 237;
                    }
                }

                else
                {
                    if (a2 == 1)
                    {
                        result = 14;
                    }
                    else
                    {
                        result = 15;
                        if (a2 != 2)
                        {
                            result = 16;
                        }
                    }
                }
            }
            else if (BattleType == BtlType_Online)
            {
                if (a2 == 1)
                {
                    result = 17;
                }
                else
                {
                    result = 18;
                    if (a2 != 2)
                    {
                        result = 19;
                    }
                }
            }
            else
            {
                result = 1;
                if (a2 != 1)
                {
                    return 2;
                }
            }
        }
        return result;
    }

    int THUMB_BRANCH_SAFESTACK_ServerCommand_SwitchIn(BtlClientWk *a1, int *a2, int *a3)
    {
        int v5;                // r4
        int v6;                // r7
        int v7;                // r0
        void *ClientMonData;   // r0
        int ID;                // r7
        __int16 SwitchInStrID; // r0
        int ClientPokePos;     // r0

        v5 = (unsigned __int8)*a3;
        v6 = (unsigned __int8)a3[1];
        v7 = *a2;
        if (!*a2)
        {
            if (!(unsigned __int8)a3[3])
            {
                goto LABEL_14;
            }
            ClientMonData = PokeCon_GetClientMonData(a1->pokeCon, (unsigned __int8)*a3, (unsigned __int8)a3[1]);
            ID = BattleMon_GetID(ClientMonData);
            if (IsOpponentClientID(a1->mainModule, a1->myID, v5))
            {
                if (TrainerParam_HasTrainerInfo(a1->mainModule, v5))
                {

                    // // k::Printf("\n\nThis is the pokemon with ID %d switching in for trainer %d\n\n", ID, v5);
                    if (a1->mainModule->btlSetup->TrainerSetups[v5]->TrID == 491 && ID >= 6)
                    {
                        // // k::Printf("\nCheck 6\n\nID == %d and trainer class = %d\n\n", ID, a1->mainModule->btlSetup->TrainerSetups[v5]->TrClass);
                        if (BattleMon_GetSpecies(ClientMonData) == 638)
                        {
                            Btlv_StringParam_Setup(&a1->strParam, 1, 239);
                        }
                        else
                        {
                            Btlv_StringParam_Setup(&a1->strParam, 1, 228);
                        }

                        // Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                    // Virizion
                    else if (a1->mainModule->btlSetup->TrainerSetups[v5]->TrID == 507 && ID >= 6)
                    {
                        // // k::Printf("\nCheck 7");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 229);
                        // Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                    // Terrakion
                    else if (a1->mainModule->btlSetup->TrainerSetups[v5]->TrID == 508 && ID >= 6)
                    {
                        // // k::Printf("\nCheck 8");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 230);
                        // Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                    // Keldeo
                    else if (a1->mainModule->btlSetup->TrainerSetups[v5]->TrID == 509 && ID >= 6)
                    {
                        // // k::Printf("\nCheck 9");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 231);
                        // Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                    else if (a1->mainModule->btlSetup->TrainerSetups[v5]->TrID == 634 && ID >= 6)
                    {
                        // // k::Printf("\nCheck 9");
                        Btlv_StringParam_Setup(&a1->strParam, 1, 234);
                        // Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                    else
                    {
                        // // k::Printf("\nCheck 10");

                        Btlv_StringParam_Setup(&a1->strParam, 1, 14);
                        Btlv_StringParam_AddArg(&a1->strParam, v5);
                        goto LABEL_13;
                    }
                }
            }
            else if (a1->myID == v5)
            {
                SwitchInStrID = BattleClient_GetSwitchInStrID(a1);
                Btlv_StringParam_Setup(&a1->strParam, 1, SwitchInStrID);
            LABEL_13:
                Btlv_StringParam_AddArg(&a1->strParam, ID);
                BtlvCore_DisplayMessageByType(a1->btlvCore, &a1->strParam);
                goto LABEL_14;
            }
            Btlv_StringParam_Setup(&a1->strParam, 1, 17);
            Btlv_StringParam_AddArg(&a1->strParam, v5);
            goto LABEL_13;
        }
        if (v7 == 1)
        {
            if (!BattleViewCmd_WaitMessage(a1->btlvCore))
            {
                //// k::Printf("Successfully returned 0. \n");
                return 0;
            }
            ClientPokePos = MainModule_GetClientPokePos(a1->mainModule, v5, v6);
            sub_21D0088(a1->btlvCore, ClientPokePos, v5, v6);
        LABEL_14:
            ++*a2;
            //// k::Printf("Successfully returned 0. \n");
            return 0;
        }
        if (v7 != 2 || !sub_21D00C4(a1->btlvCore))
        {
            //// k::Printf("Successfully returned 0. \n");
            return 0;
        }
        BattleClient_UpdateEnemyMonHP(a1);
        if (v5 == MainModule_GetPlayerClientID(a1->mainModule))
        {
            sub_21B9730(a1, &a1->pokestarSeqWork, a1->actPokeParty);
        }
        //// k::Printf("Successfully returned 1. \n");
        return 1;
    }
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
        VAR_MOVE_SERIAL = 0x19,
        VAR_MOVE_CATEGORY = 0x1A,
        VAR_TARGET_TYPE = 0x1B,
        VAR_USER_TYPE = 0x1C,
        VAR_CONDITION_ID = 0x1D,
        VAR_CONDITION_ADDRESS = 0x1E,
        VAR_MOVE_EFFECT = 0x1F,
        VAR_STAT_STAGE_CHANGE_COUNT = 0x19,
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
        VAR_NO_TYPE_EFFECTIVENESS = 0x4B,
        VAR_SET_TYPE_EFFECTIVENESS = 0x4C,
        VAR_DELAY_ATTACK_FLAG = 0x4D,
        VAR_MAGIC_COAT_FLAG = 0x4E,
        VAR_MESSAGE_FLAG = 0x4F,
        VAR_GENERAL_USE_FLAG = 0x51,
        VAR_SIDE = 0x52,
        VAR_SIDE_EFFECT = 0x53,
        VAR_INTIMFLAG = 0x54,
        VAR_HOSTILEFLAG = 0x55,
        VAR_DISPLAYED = 0x56,
    };

    struct HandlerParam_Header
    {
        u32 flags;
    };

    enum StatStage
#ifdef __cplusplus
        : u32
#endif
    {
        STATSTAGE_NULL = 0,
        STATSTAGE_ATTACK = 1,
        STATSTAGE_DEFENSE = 2,
        STATSTAGE_SPECIAL_ATTACK = 3,
        STATSTAGE_SPECIAL_DEFENSE = 4,
        STATSTAGE_SPEED = 5,
        STATSTAGE_ACCURACY = 6,
        STATSTAGE_EVASION = 7,
    };

    struct HandlerParam_ChangeStatStage
    {
        HandlerParam_Header header;
        StatStage rankType;
        u32 pad;
        s8 rankVolume;
        u8 pad2;
        u8 fMoveAnimation;
        u8 poke_cnt;
        u8 pokeID[6];
        HandlerParam_StrParams exStr;
        // u8 isHostile;
    };

    extern void ServerDisplay_AbilityPopupAdd(ServerFlow *a1, void *a2);
    extern bool j_j_PosPoke_IsExist_3(PosPoke *a1, int a2);
    extern bool j_j_PosPoke_IsExist_4(PosPoke *a1, int a2);
    extern void *PokeCon_GetBattleMon(void *a1, int a2);
    extern bool BattleMon_IsStatChangeValid(void *a1, unsigned int a2, int a3);
    extern u32 BattleEventVar_SetConstValue(BattleEventVar a1, int a2);
    extern u32 BattleEventVar_SetValue(BattleEventVar a1, int a2);
    extern void *Handler_GetBattleMon(ServerFlow *a1, int a2);
    extern int BattleHandler_SetString(ServerFlow *a1, HandlerParam_StrParams *a2);
    extern void ServerDisplay_AbilityPopupRemove(ServerFlow *a1, void *a2);
    extern void BattleEventVar_Push();
    extern void BattleEventVar_Pop();
    extern void BattleEvent_CallHandlers(ServerFlow *a1, BattleEventType a2);
    extern u32 BattleEventVar_SetRewriteOnceValue(BattleEventVar a1, int a2);
    extern u32 HEManager_PushState(void *a1);
    extern int BattleEventVar_GetValue(BattleEventVar a1);
    extern void HEManager_PopState(void *result, int a2);

    int MyPosPoke_GetPokeExistPos(PosPoke *a1, int a2)
    {
        unsigned int i;   // r4
        PosPokeState *v3; // r3

        for (i = 0; i < 6; ++i)
        {
            v3 = &a1->positions[i];
         //   k::Printf("\nExistPokeID = %d", v3->monID);
            if (v3->enabled && a2 == v3->monID)
            {
                return i;
            }
        }
        return 6;
    }

    // int MyServerEvent_CheckStatStageChangeSuccess(ServerFlow *r0_0, void *a2, int a3, int a4, int a5, int a6, int intimFlag, int hostileFlag)
    // {
    //     int ID;    // r0
    //     int v10;   // r5
    //     int Value; // r6

    //     BattleEventVar_Push();
    //     ID = BattleMon_GetID(a2);
    //     BattleEventVar_SetConstValue(VAR_MON_ID, ID);
    //     BattleEventVar_SetConstValue(VAR_ATTACKING_MON, a4);
    //     BattleEventVar_SetConstValue(VAR_INTIMFLAG, intimFlag);
    //     BattleEventVar_SetConstValue(VAR_HOSTILEFLAG, hostileFlag);
    //     k::Printf("\nIntimFlag is %d and HostileFlag is %d\n", intimFlag, hostileFlag);
    //     BattleEventVar_SetConstValue(VAR_MOVE_EFFECT, a3);
    //     BattleEventVar_SetConstValue(VAR_VOLUME, a5);
    //     BattleEventVar_SetConstValue(VAR_STAT_STAGE_CHANGE_COUNT, a6);
    //     v10 = 0;
    //     BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
    //     BattleEvent_CallHandlers(r0_0, EVENT_STAT_STAGE_CHANGE_LAST_CHECK);
    //     Value = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
    //     BattleEventVar_Pop();
    //     k::Printf("\nValue = %d\n", Value);
    //     if (!Value)
    //     {
    //         return 1;
    //     }
    //     return 0;
    // }

    // void MyServerEvent_StatStageChangeApplied(ServerFlow *a1, int a2, void *a3, int a4, int a5, int intimFlag, int hostileFlag)
    // {
    //     int ID; // r0

    //     BattleEventVar_Push();
    //     BattleEventVar_SetConstValue(VAR_ATTACKING_MON, a2);
    //     ID = BattleMon_GetID(a3);
    //     BattleEventVar_SetConstValue(VAR_MON_ID, ID);
    //     BattleEventVar_SetConstValue(VAR_INTIMFLAG, intimFlag);
    //     BattleEventVar_SetConstValue(VAR_HOSTILEFLAG, hostileFlag);
    //      k::Printf("\nIntimFlag is %d and HostileFlag is %d\n", intimFlag, hostileFlag);
    //     BattleEventVar_SetConstValue(VAR_MOVE_EFFECT, a4);
    //     BattleEventVar_SetConstValue(VAR_VOLUME, a5);
    //     BattleEvent_CallHandlers(a1, EVENT_STAT_STAGE_CHANGE_APPLIED);
    //     BattleEventVar_Pop();
    // };

    // extern int ServerEvent_CheckSubstituteInteraction(ServerFlow *a1, void *a2, int a3, int a4, int a5, int a6);
    // extern void ServerDisplay_StatStageLimit(ServerFlow *a1, void *a2, int a3, int a4);
    // extern bool BattleMon_IsSubstituteActive(void *a1);
    // extern void ServerEvent_StatStageChangeFail(ServerFlow *a1, void *a2, int a3);
    // extern void ServerDisplay_StatStage(
    //     ServerFlow *a1,
    //     void *a2,
    //     unsigned int a3,
    //     int a4,
    //     unsigned __int16 a5,
    //     int a6);

    // int MyServerControl_StatStageChangeCore(
    //     ServerFlow *a1,
    //     int a2,
    //     void *a3,
    //     unsigned int a4,
    //     int a5,
    //     unsigned __int8 a6,
    //     unsigned __int16 a7,
    //     int a8,
    //     int a9,
    //     int a10,
    //     int intimFlag,
    //     int hostileFlag)
    // {
    //     int v13; // r6
    //     int v15; // r6
    //     int v17; // [sp+Ch] [bp-1Ch]
    //     u32 v18; // [sp+10h] [bp-18h]

    //     k::Printf("\nWe are in here, and intim flag is %d and the hostile flag is %d\n", intimFlag, hostileFlag);
    //     v13 = ServerEvent_CheckSubstituteInteraction(a1, a3, a4, a6, a7, a5);
    //     if (!BattleMon_IsStatChangeValid(a3, a4, v13))
    //     {
    //         if (a9)
    //         {
    //             ServerDisplay_StatStageLimit(a1, a3, a4, v13);
    //             a1->flags |= 0x10u;
    //         }
    //         return 0;
    //     }
    //     if (BattleMon_IsSubstituteActive(a3) && a2 != BattleMon_GetID(a3))
    //     {
    //         if (a9)
    //         {
    //             SCQueue_AddMessage(a1->serverCommandQueue, 91, 210); // 210: It doesn't affect\n[VAR PKNICK(0)]...
    //         }
    //         return 0;
    //     }
    //     v17 = 1;
    //     if (MyServerEvent_CheckStatStageChangeSuccess(a1, a3, a4, a2, v13, a8, intimFlag, hostileFlag))
    //     {
    //         ServerDisplay_StatStage(a1, a3, a4, v13, a7, a10);
    //         v18 = HEManager_PushState(&a1->HEManager);
    //         MyServerEvent_StatStageChangeApplied(a1, a2, a3, a4, v13, intimFlag, hostileFlag);
    //         HEManager_PopState(&a1->HEManager, v18);
    //     }
    //     else
    //     {
    //         if (a9)
    //         {
    //             v15 = HEManager_PushState(&a1->HEManager);
    //             ServerEvent_StatStageChangeFail(a1, a3, a8);
    //             HEManager_PopState(&a1->HEManager, v15);
    //         }
    //         return 0;
    //     }
    //     return v17;
    // }

    // int THUMB_BRANCH_SAFESTACK_BattleHandler_ChangeStatStage(ServerFlow *a1, HandlerParam_ChangeStatStage *a2, unsigned __int16 a3)
    // {
    //     int v5;          // r6
    //     void *v6;        // r7
    //     unsigned int i;  // r6
    //     void *v8;        // r7
    //     int v11;         // [sp+1Ch] [bp-24h]
    //     int v12;         // [sp+20h] [bp-20h]
    //     void *BattleMon; // [sp+24h] [bp-1Ch]

    //     BattleMon = PokeCon_GetBattleMon(a1->pokeCon, a2->header.flags << 19 >> 27);
    //     v12 = 0;
    //     v11 = 0;
    //     v5 = 0;
    //     k::Printf("\nCheck #1");
    //     if (a2->poke_cnt)
    //     {
    //         while (1)
    //         {
    //             if (j_j_PosPoke_IsExist_4(&a1->PosPoke, a2->pokeID[v5]))
    //             {
    //                 v6 = PokeCon_GetBattleMon(a1->pokeCon, a2->pokeID[v5]);
    //                 if (!BattleMon_IsFainted(v6) && BattleMon_IsStatChangeValid(v6, a2->rankType, a2->rankVolume))
    //                 {
    //                     break;
    //                 }
    //             }
    //             if (++v5 >= a2->poke_cnt)
    //             {
    //                 goto LABEL_7;
    //             }
    //         }
    //         v12 = 1;
    //     }
    //     k::Printf("\nCheck #2");
    // LABEL_7:
    //     if (v12 && (a2->header.flags & 0x800000) != 0)
    //     {
    //         ServerDisplay_AbilityPopupAdd(a1, BattleMon);
    //     }
    //     k::Printf("\nCheck #3");
    //     for (i = 0; i < a2->poke_cnt; ++i)
    //     {
    //         k::Printf("\nCheck #4");
    //         k::Printf("\nWhat is the information we have access to?\nID is %d\nBattlemon species is %d\nOutput of function is %d\n",
    //                   a2->pokeID[i],
    //                   BattleMon_GetSpecies(Handler_GetBattleMon(a1, a2->pokeID[i])),
    //                   MyPosPoke_GetPokeExistPos(&a1->PosPoke, a2->pokeID[i]));

    //         if (j_j_PosPoke_IsExist_4(&a1->PosPoke, a2->pokeID[i]))
    //         {
    //             k::Printf("\nCheck #5");
    //             v8 = PokeCon_GetBattleMon(a1->pokeCon, a2->pokeID[i]);
    //             if (!BattleMon_IsFainted(v8))
    //             {
    //                 k::Printf("\nCheck #6");
    //                 if (MyServerControl_StatStageChangeCore(
    //                         a1,
    //                         a2->header.flags << 19 >> 27,
    //                         v8,
    //                         a2->rankType,
    //                         a2->rankVolume,
    //                         0x1Fu,
    //                         a3,
    //                         a2->pad,
    //                         a2->fMoveAnimation,
    //                         a2->pad2 == 0,
    //                 ((a2->header.flags & 0x08000000) != 0),
    //                         ((a2->header.flags & 0x04000000) != 0)))
    //                 {
    //                     k::Printf("\nCheck #7");
    //                     BattleHandler_SetString(a1, &a2->exStr);
    //                     v11 = 1;
    //                 }
    //             }
    //         }
    //     }
    //     k::Printf("\nCheck #8");
    //     if (v12 && (a2->header.flags & 0x800000) != 0)
    //     {
    //         ServerDisplay_AbilityPopupRemove(a1, BattleMon);
    //     }
    //     return v11;
    // }
}