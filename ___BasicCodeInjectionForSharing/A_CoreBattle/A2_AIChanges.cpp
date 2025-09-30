#include "codeinjection_new.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// Uses esdb_newBattle.yml

extern "C"
{

#pragma region DamageCalcStateTracking

    struct keyPair
    {
        u32 dirty;
        u32 value;
    };

    keyPair calcTable[6][6][4] = {
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
         {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
    };

    int NumOfCalcs = 0;
    int NumOfCalcsAvoided = 0;

    void resetCalcTable()
    {
        for (int i = 0; i < 6; i++)
        {
            for (int k = 0; k < 6; k++)
            {
                for (int j = 0; j < 4; j++)
                {
                    calcTable[i][k][j].dirty = 0;
                    calcTable[i][k][j].value = 0;
                }
            }
        }
        k::Printf("\nThe number of calcs performed this turn was %d and the number of calcs avoided was %d\n", NumOfCalcs, NumOfCalcsAvoided);
        NumOfCalcs = 0;
        NumOfCalcsAvoided = 0;
    }

    u8 GetMovePos(BattleMon *mon, MoveID move)
    {
        int movecount = BattleMon_GetMoveCount(mon);
        int count = 0;
        if (movecount)
        {
            do
            {
                if (Move_GetID(mon, count) == move)
                {
                    return count;
                }
            } while (count < movecount);
        }
        return 5;
    }

    u32 checkCalcTable(ServerFlow *flow, BattleMon *attacker, BattleMon *defender, MoveID move)
    {
        int index1 = Handler_PokeIDToPokePos(flow, attacker->ID);
        int index2 = Handler_PokeIDToPokePos(flow, defender->ID);
        int index3 = GetMovePos(attacker, move);

        if (index3 > 4)
        {
            return 0;
        }

        NumOfCalcs++;
        if (calcTable[index1][index2][index3].dirty == 1)
        {
            NumOfCalcsAvoided++;
            return calcTable[index1][index2][index3].value;
        }
        return 0;
    }

    void saveToCalcTable(ServerFlow *flow, BattleMon *attacker, BattleMon *defender, MoveID move, u32 damage)
    {
        int index1 = Handler_PokeIDToPokePos(flow, attacker->ID);
        int index2 = Handler_PokeIDToPokePos(flow, defender->ID);
        int index3 = GetMovePos(attacker, move);

        calcTable[index1][index2][index3].dirty = 1;
        calcTable[index1][index2][index3].value = damage;
    }


    void THUMB_BRANCH_ServerControl_TurnCheckField(ServerFlow *a1)
    {
        resetCalcTable();
        BattleField_TurnCheck(TurnCheckCallback_Field, a1);
        SCQueue_AddCommon(a1->serverCommandQueue, 47, 0);
    }

#pragma endregion

#pragma region genericHelpers

    bool isInArray(int value, int type)
    {
        if (type == 0)
        {
            for (int i = 0; i < 22; i++)
            {
                if (BulletproofMoves[i] == value)
                {
                    return true;
                }
            }
            return false;
        }
        else if (type == 1)
        {
            for (int i = 0; i < 17; i++)
            {
                if (WindMoves[i] == value)
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    bool HasMoldBreaker(BattleMon *a1)
    {
        return (BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL104_MOLD_BREAKER || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL163_TURBOBLAZE || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL164_TERAVOLT);
    }

    u32 GetCritSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16415);

        // k::Printf("Current crit setting is %d\n", *lvl_cap_ptr);

        return *lvl_cap_ptr;
    }

    int GetCritRatio(int sniper)
    {
        if (GetCritSetting() == 0)
        {
            if (sniper == 1)
            {
                return 12288;
            }
            else
            {
                return 8192;
            }
        }
        else
        {
            if (sniper == 1)
            {
                return 9216;
            }
            else
            {
                return 6144;
            }
        }
    }

    int GetCritRatioSwitch()
    {
        if (GetCritSetting() == 0)
        {
            return 2;
        }
        else
        {
            return 1.5;
        }
    }

#pragma endregion

#pragma region TypeChecksAndEffectiveness
    int GetTypeEffectivenessAlteredSacredSword(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;

        if (a1 == TYPE_NONE || a2 == TYPE_NONE)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        if (a1 == TYPE_FIGHTING)
        {
            v3 = SacredSwordTypeChart[a1][a2];
            // //k::printf("\nFreezeDryChart entered\nv3 = %d\na1 = %d\na2 = %d\n\n", v3, a1, a2);
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
        }

        switch (v3)
        {
        case 0:
            result = EFFECTIVENESS_IMMUNE;
            break;
        case 2:
            result = EFFECTIVENESS_1_2;
            break;
        case 4:
            result = EFFECTIVENESS_1;
            break;
        case 8:
            result = EFFECTIVENESS_2;
            break;
        default:
            return 0;
        }
        return result;
    }

    int GetTypeEffectivenessAltered(int a1, int a2)
    {
        TypeEffectiveness result;
        int v3;
        PlayerState *playerState;
        int zoneId;
        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);

        if (a1 == TYPE_NONE || a2 == TYPE_NONE)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        if (a1 == TYPE_ICE)
        {
            v3 = FreezeDryTypeChart[a1][a2];
            // //k::printf("\nFreezeDryChart entered\nv3 = %d\na1 = %d\na2 = %d\n\n", v3, a1, a2);
        }
        else if (a1 == TYPE_FIGHTING)
        {
            if (a2 == TYPE_FLYING)
            {
                v3 = SkyUppercutTypeChart[a1][a2];
            }
            if (zoneId == 121)
            {
                v3 = opelucidTypeChart[a1][a2];
            }
            else
            {
                v3 = SkyUppercutTypeChart[a1][a2];
            }
            // //k::printf("\nSkyUppercutChart entered\nv3 = %d\na1 = %d\na2 = %d\n\n", v3, a1, a2);
        }

        else if (a1 == TYPE_POISON)
        {
            v3 = CorrosionTypeChart[a1][a2];
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
        }

        switch (v3)
        {
        case 0:
            result = EFFECTIVENESS_IMMUNE;
            break;
        case 2:
            result = EFFECTIVENESS_1_2;
            break;
        case 4:
            result = EFFECTIVENESS_1;
            break;
        case 8:
            result = EFFECTIVENESS_2;
            break;
        default:
            return 0;
        }
        return result;
    }

    int GetTypeEffectivenessVsMonAltered(int a1, int a2)
    {
        int TypeEffectiveness; // r4
        int v6;                // r0
        int v7;
        int v8;
        v8 = PokeTypePair_GetType1(a2);
        v7 = PokeTypePair_GetType2(a2);

        if (PokeTypePair_IsMonotype(a2))
        {
            return GetTypeEffectivenessAltered(a1, v8);
        }
        TypeEffectiveness = GetTypeEffectivenessAltered(a1, v8);
        v6 = GetTypeEffectivenessAltered(a1, v7);
        return GetTypeEffectivenessMultiplier(TypeEffectiveness, v6);
    }

    int GetTypeEffectivenessVsMonAlteredSacredSword(int a1, int a2)
    {
        int TypeEffectiveness; // r4
        int v6;                // r0
        int v7;
        int v8;
        v8 = PokeTypePair_GetType1(a2);
        v7 = PokeTypePair_GetType2(a2);

        if (PokeTypePair_IsMonotype(a2))
        {
            return GetTypeEffectivenessAlteredSacredSword(a1, v8);
        }
        TypeEffectiveness = GetTypeEffectivenessAlteredSacredSword(a1, v8);
        v6 = GetTypeEffectivenessAlteredSacredSword(a1, v7);
        return GetTypeEffectivenessMultiplier(TypeEffectiveness, v6);
    }

    TypeEffectiveness PersonalGetTypeEffectiveness(int a1, int a2)
    {
        TypeEffectiveness result;
        PlayerState *playerState;
        int typeChart[18][18];
        int zoneId;
        int v3;

        if (a1 == 18 || a2 == 18)
        {
            result = EFFECTIVENESS_1;
            return result;
        }

        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);

        if (zoneId == 607 || zoneId == 195 || zoneId == 196 || zoneId == 197)
        {
            v3 = chargestoneTypeChart[a1][a2];
        }
        else if (zoneId == 339 || zoneId == 338 || zoneId == 340 || zoneId == 341 || zoneId == 462 || (zoneId >= 510 && zoneId <= 514) || (zoneId >= 569 && zoneId <= 572))
        {
            v3 = celestialTypeChart[a1][a2];
        }
        else if (zoneId == 121)
        {
            v3 = opelucidTypeChart[a1][a2];
        }
        else
        {
            v3 = normalTypeChart[a1][a2];
        }

        switch (v3)
        {
        case 0:
            result = EFFECTIVENESS_IMMUNE;
            break;
        case 2:
            result = EFFECTIVENESS_1_2;
            break;
        case 4:
            result = EFFECTIVENESS_1;
            break;
        case 8:
            result = EFFECTIVENESS_2;
            break;
        default:
            result = EFFECTIVENESS_1;
        }
        return result;
    }

    TypeEffectiveness THUMB_BRANCH_SAFESTACK_ServerEvent_CheckDamageEffectiveness(
        ServerFlow *a1,
        BattleMon *a2,
        BattleMon *a3,
        int a4,
        unsigned __int8 a5)
    {
        int ID;    // r0
        int v9;    // r0
        int Value; // r5
        int ActualType;
        int v11;                  // r4
        TypeEffectiveness result; // r0

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
        v9 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v9);
        BattleEventVar_SetConstValue(VAR_POKE_TYPE, a5);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4);
        BattleEventVar_SetRewriteOnceValue(VAR_NO_TYPE_EFFECTIVENESS, 0);
        BattleEventVar_SetRewriteOnceValue(VAR_SET_TYPE_EFFECTIVENESS, 0);
        // j_j_BTL_SICKEVENT_CheckNotEffectByType(a1, a3);
        j_j_Condition_CheckUnaffectedByType(a1, a3);
        BattleEvent_CallHandlers(a1, EVENT_CHECK_TYPE_EFFECTIVENESS);
        Value = BattleEventVar_GetValue(VAR_NO_TYPE_EFFECTIVENESS);
        v11 = BattleEventVar_GetValue(VAR_SET_TYPE_EFFECTIVENESS);
        BattleEventVar_Pop();
        if (v11 >= 2)
        {
            // //k::printf("\nMon 1 Type 1 is %d\nMon 1 Type 2 is %d\nMon 2 Type 1 is %d\nMon 2 Type 2 is %d\na4 = %d", PokeTypePair_GetType1(BattleMon_GetPokeType(a2)), PokeTypePair_GetType2(BattleMon_GetPokeType(a2)), PokeTypePair_GetType1(BattleMon_GetPokeType(a3)), PokeTypePair_GetType2(BattleMon_GetPokeType(a3)), a4);
            // //k::printf("\n\nTypeEffectiveness is %d\na4 is %d\nActualType is %d\na5 as int is %d\nv11 is %d\n\n", GetTypeEffectivenessAltered(a4, ActualType), a4, ActualType, (int)a5, v11);
            return (TypeEffectiveness)GetTypeEffectivenessAltered(a4, a5);
        }
        else if (v11)
        {
            // //k::printf("\nWe're in here\n");
            return EFFECTIVENESS_1;
        }
        result = PersonalGetTypeEffectiveness(a4, a5);
        if (result == EFFECTIVENESS_IMMUNE)
        {
            if (Value)
            {
                return EFFECTIVENESS_1;
            }
        }
        return result;
    }

#pragma endregion

#pragma region FieldEffectsAndBattleStart

    void CreateSpikes(
        int a1,
        ServerFlow *a2,
        unsigned int *a3,
        int a4,
        unsigned __int8 a5,
        int a6,
        ConditionData a7,
        __int16 a8)
    {
        HandlerParam_AddSideEffect *v10;

        // char *bhwork;
        v10 = (HandlerParam_AddSideEffect *)BattleHandler_PushWork(a2, EFFECT_ADDSIDEEFFECT, (int)a3);
        v10->effect = a6;
        v10->side = a5;
        v10->cont = a7;

        // k::Printf("%d", v10);

        // bhwork = (char *)v10;
        BattleHandler_StrSetup(&v10->exStr, 1u, a8);
        BattleHandler_AddArg(&v10->exStr, a5);
        BattleHandler_PopWork(a2, v10);
    };

    int HandleFieldEffects(ServerFlow *a1)
    {

        HandlerParam_Message *bhwork;
        BtlSetup *btlsetup;
        BattleFieldStatus *FieldStatus; // r0
        TrainerBattleSetup **trainerSetups;
        TrainerBattleSetup *currentTrainer;
        PlayerState *playerState;
        int zoneId;
        int trainerId;
        int trainerClass;

        FieldStatus = BtlSetup_GetFieldStatus(a1->mainModule);
        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);

        // Trick Room Setter
        // Checks ZoneId for Relic Castle, currently
        if (zoneId == 503 || zoneId == 504 || zoneId == 505 || (zoneId >= 255 && zoneId <= 262) || (zoneId >= 160 && zoneId <= 190))
        {
            ServerDisplay_AddCommon(a1->serverCommandQueue, 48, 1, 0, 433, 0, 0);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 203);
            BattleHandler_PopWork(a1, bhwork);
            ServerControl_FieldEffectCore(a1, 1, Condition_MakePermanent(), 0);
        }

        // Chargestone Cave
        if (zoneId == 607 || zoneId == 195 || zoneId == 196 || zoneId == 197)
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE351_SHOCK_WAVE;
            addAnimation->pos_from = 3;
            addAnimation->pos_to = 0;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 204);
            BattleHandler_PopWork(a1, bhwork);
        }
        // Celestial Tower
        else if (zoneId == 339 || zoneId == 338 || zoneId == 340 || zoneId == 341 || zoneId == 462 || (zoneId >= 510 && zoneId <= 514) || (zoneId >= 569 && zoneId <= 572))
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE114_HAZE;
            addAnimation->pos_from = 6;
            addAnimation->pos_to = 6;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 205);
            BattleHandler_PopWork(a1, bhwork);
        }
        // Opelucid Gym
        else if (zoneId == 121)
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE137_GLARE;
            addAnimation->pos_from = 3;
            addAnimation->pos_to = 0;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 206);
            BattleHandler_PopWork(a1, bhwork);
        }

        // Skyla' Gym
        else if (zoneId == 108)
        {
            HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
            addAnimation->animNo = MOVE366_TAILWIND;
            addAnimation->pos_from = 6;
            addAnimation->pos_to = 6;
            BattleHandler_PopWork(a1, addAnimation);
            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(a1, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 207);
            BattleHandler_PopWork(a1, bhwork);
        }

        if (a1->mainModule->btlSetup->btlType != 0)
        {
            trainerSetups = a1->mainModule->btlSetup->TrainerSetups;

            currentTrainer = trainerSetups[1];

            trainerId = currentTrainer->TrID;
            trainerClass = currentTrainer->TrClass;

            // k::Printf("\n\nTrainer ID is %d\nTrainer Class is %d\n\n", trainerId, trainerClass);
            // PreSet Spikes
            // Checks TrainerId
            if (trainerClass == 192)
            {
                ConditionData Permanent = Condition_MakePermanent();
                HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
                addAnimation->animNo = MOVE191_SPIKES;
                addAnimation->pos_from = 3;
                addAnimation->pos_to = 0;
                BattleHandler_PopWork(a1, addAnimation);
                CreateSpikes(0, a1, 0, 0, 0, 6, Permanent, 148);
            }

            // Cobalion Fight
            if (trainerId == 491)
            {

                ConditionData Permanent = Condition_MakePermanent();
                HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a1, EFFECT_ADD_ANIMATION, 0);
                addAnimation->animNo = MOVE137_GLARE;
                addAnimation->pos_from = 1;
                addAnimation->pos_to = 0;
                BattleHandler_PopWork(a1, addAnimation);
                CreateSpikes(0, a1, 0, 0, 0, 15, Permanent, 208);
            }
        }

        // Overworld Weather Setter
        if (zoneId == 537 || zoneId == 538 || zoneId == 539 || zoneId == 540 || zoneId == 541 || zoneId == 542 || zoneId == 461 || zoneId == 376 || zoneId == 589)
        {
            // Setting Sun
            if (ServerControl_ChangeWeather(a1, 1, 255))
            {
                return 1;
            }
        }
        else if (FieldStatus->BtlWeather && ServerControl_ChangeWeather(a1, (unsigned __int8)FieldStatus->BtlWeather, 255))
        {
            return 1;
        }

        return 0;
    }

    // // SOURCE OF THE CRASH IS THIS FUNCTION //
    int THUMB_BRANCH_SAFESTACK_ServerFlow_SetupBeforeFirstTurn(ServerFlow *a1)
    {

        ServerCommandQueue *serverCommandQueue; // r1
        BattleFieldStatus *FieldStatus;         // r0
        SVCL_WORK *ClientWork;                  // r0
        SVCL_WORK *v5;                          // r4
        BtlServerWk *server;
        unsigned int v6;        // r5
        BattleMon *PartyMember; // r0
        unsigned int j;         // r5
        BattleMon *v9;          // r0
        int v10;                // r7
        int v12;                // [sp+0h] [bp-20h]
        unsigned int i;         // [sp+4h] [bp-1Ch]

        serverCommandQueue = a1->serverCommandQueue;
        serverCommandQueue->writePtr = 0;
        v12 = 0;
        serverCommandQueue->readPtr = 0;
        v12 = HandleFieldEffects(a1);
        v12 = 1;

        /* Some kind of initialization of the damage calc cache would be good here */
        resetCalcTable();

        for (i = 0; i < 4; ++i)
        {
            ClientWork = BattleServer_GetClientWork(a1->server, i);
            v5 = ClientWork;
            if (ClientWork)
            {
                v6 = 0;
                if (ClientWork->byte9)
                {
                    do
                    {
                        PartyMember = BattleParty_GetPartyMember(v5->party, v6);
                        if (PartyMember && !BattleMon_IsFainted(PartyMember))
                        {
                            ServerControl_SwitchInCore(a1, i, v6, v6);
                        }
                        ++v6;
                    } while (v6 < v5->byte9);
                }
                if (BtlSetup_GetBattleStyle(a1->mainModule) == BTL_STYLE_ROTATION)
                {
                    for (j = 0; j < 3; ++j)
                    {
                        v9 = BattleParty_GetPartyMember(v5->party, j);
                        v10 = (int)v9;
                        if (v9 && !BattleMon_IsFainted(v9))
                        {
                            MainModule_RegisterPokedexSeenFlag(a1->mainModule, i, v10);
                        }
                    }
                }
            }
        }
        if (ServerControl_AfterSwitchIn(a1))
        {
            return 1;
        }
        return v12;
    }

#pragma endregion

#pragma region SimulationDamageHelpers

    bool checkRetaliate(ServerFlow *a2, int MonID, int turn)
    {
        FaintRecord *record;
        int turnCount;
        int faintedId;
        int loopCount;
        record = Handler_GetFaintRecord(a2);

        turnCount = j_j_FaintRecord_GetCount(record, turn);
        loopCount = 0;

        if (turnCount)
        {
            while (loopCount <= turnCount)
            {
                faintedId = j_j_FaintRecord_GetPokeID(record, turn, loopCount);

                if (MainModule_IsAllyMonID(MonID, faintedId))
                {
                    return true;
                }
                ++loopCount;
            }
        }
        return false;
    }

    int CheckRatio(ServerFlow *a1, BattleMon *AttackingMon, BattleMon *DefendingMon, int MoveID)
    {

        // Reversal and Flail
        if (MoveID == MOVE175_FLAIL || MoveID == MOVE179_REVERSAL)
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);
            if (Value == 409600)
            {
                return 4096;
            }
            else if (Value < 409600 && Value >= 281600)
            {
                return 8192;
            }
            else if (Value < 281600 && Value >= 145000)
            {
                return 16384;
            }
            else if (Value < 145000 && Value >= 85300)
            {
                return 32768;
            }
            else if (Value < 85300 && Value >= 42700)
            {
                return 40960;
            }
            else if (Value < 42700 && Value >= 17100)
            {
                return 61440;
            }
            else
            {
                return 81920;
            }
        }

        // Water Spout and Eruption
        if (MoveID == MOVE323_WATER_SPOUT || MoveID == MOVE284_ERUPTION)
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return 4096;
            }
            else if (Value < 409600 && Value >= 384000)
            {
                return 3840;
            }
            else if (Value < 384000 && Value >= 358400)
            {
                return 3584;
            }
            else if (Value < 358400 && Value >= 332800)
            {
                return 3328;
            }
            else if (Value < 332800 && Value >= 307200)
            {
                return 3072;
            }
            else if (Value < 307200 && Value >= 281600)
            {
                return 2816;
            }
            else if (Value < 281600 && Value >= 256000)
            {
                return 2560;
            }
            else if (Value < 256000 && Value >= 230400)
            {
                return 2304;
            }
            else if (Value < 230400 && Value >= 204800)
            {
                return 2408;
            }
            else
            {
                return 0;
            }
        }

        // Electro Ball
        if (MoveID == MOVE486_ELECTRO_BALL)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) > Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // Gyro Ball
        if (MoveID == MOVE360_GYRO_BALL)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // //k::print("\nCheck #1");
        if (MoveID == MOVE474_VENOSHOCK)
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return 8192;
            }
        }

        /* Add checks here for Utility Umbrella and Overcoat */
        if (MoveID == MOVE076_SOLAR_BEAM || MoveID == MOVE554_SOLAR_BLADE)
        {
            if (ServerEvent_GetWeather(a1) != WEATHER_SUN && AttackingMon->HeldItem != IT0271_POWER_HERB && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL122_FLOWER_GIFT)
            {
                return 0;
            }
            else
            {
                if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT || AttackingMon->HeldItem == IT0544_UTILITY_UMBRELLA)
                {
                    return 0;
                }
            }
        }

        //  Skull Bash and Meteor Beam and Sky Attack
        if (MoveID == MOVE130_SKULL_BASH || MoveID == MOVE553_METEOR_BEAM || MoveID == MOVE143_SKY_ATTACK)
        {
            if (AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                if (RandomInRange(0, 100) > 60)
                {
                    return 0;
                }
            }
        }

        // Electro Shot
        /* Add check here for Utility Umbrella or Overcoat */
        if (MoveID == MOVE193_ELECTRO_SHOT)
        {
            if (ServerEvent_GetWeather(a1) != 2 && AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return 0;
            }
            else
            {
                if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT || AttackingMon->HeldItem == IT0544_UTILITY_UMBRELLA)
                {
                    return 0;
                }
            }
        }

        //  Hex, Beat Up, Infernal Parade, Barb Barrage
        if (MoveID == MOVE169_INFERNAL_PARADE || MoveID == MOVE272_BARB_BARRAGE || MoveID == MOVE251_BEAT_UP || MoveID == MOVE506_HEX || MoveID == MOVE244_BITTER_MALICE)
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return 8192;
            }
        }

        //  Acrobatics
        if (MoveID == MOVE512_ACROBATICS)
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == IT0556_FLYING_GEM)
            {
                return 8192;
            }
        }

        //  All 2 hit moves
        if (MoveID == MOVE003_DOUBLE_SLAP || MoveID == MOVE022_VINE_WHIPS || MoveID == MOVE458_DOUBLE_HIT || MoveID == MOVE024_DOUBLE_KICK || MoveID == MOVE011_DUAL_WINGBEAT || MoveID == MOVE041_TWINEEDLE || MoveID == MOVE155_BONEMERANG || MoveID == MOVE544_GEAR_GRIND || MoveID == MOVE530_DUAL_CHOP)
        {
            return 8192;
        }

        //  All 3 hit moves
        if (MoveID == MOVE167_TRIPLE_KICK || MoveID == MOVE471_TRIPLE_DIVE || MoveID == MOVE470_TRIPLE_AXEL || MoveID == MOVE161_TRI_ATTACK)
        {
            return 12288;
        }

        //  Brine
        if (MoveID == MOVE362_BRINE)
        {

            if (BattleMon_GetHPRatio(DefendingMon) <= 204800)
            {
                return 8192;
            }
            else
            {
                return 4096;
            }
        }

        if (MoveID == MOVE514_RETALIATE)
        {
            if (checkRetaliate(a1, AttackingMon->ID, 1u))
            {
                return 8192;
            }
        }

        // First Impression
        if (MoveID == MOVE373_1ST_IMPRESSION)
        {
            if (BattleMon_GetConditionFlag(AttackingMon, CONDITIONFLAG_ACTIONDONE))
            {
                return 0;
            }
        }

        //  Facade
        if (MoveID == MOVE263_FACADE)
        {
            if (BattleMon_GetStatus(AttackingMon))
            {
                return 8192;
            }
        }

        //  Wake Up Slap and Dream Eater
        if (MoveID == MOVE358_WAKE_UP_SLAP || MoveID == MOVE138_DREAM_EATER)
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return 8192;
            }
        }

        //  All multihit moves
        if (MoveID == MOVE004_COMET_PUNCH || MoveID == MOVE013_RAZOR_WINDS || MoveID == MOVE042_PIN_MISSILE ||
            MoveID == MOVE131_SPIKE_CANNON || MoveID == MOVE140_BARRAGE || MoveID == MOVE154_FURY_SWIPES || MoveID == MOVE198_BONE_RUSH ||
            MoveID == MOVE292_ARM_THRUST || MoveID == MOVE331_BULLET_SEED || MoveID == MOVE333_ICICLE_SPEAR || MoveID == MOVE350_ROCK_BLAST ||
            MoveID == MOVE541_TAIL_SLAP || MoveID == MOVE378_SCALE_SHOT)
        {
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL092_SKILL_LINK)
            {
                return 20480;
            }
            else if (AttackingMon->HeldItem == IT0317_LOADED_DICE || AttackingMon->HeldItem == IT0312_TERA_DICE)
            {
                return 16384;
            }
            else
            {
                return 8192;
            }
        }

        // Hyper Beam
        if (MoveID == MOVE063_HYPER_BEAM)
        {
            if (BattleMon_GetPreviousMove(AttackingMon) == MOVE063_HYPER_BEAM && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 0;
            }
        }

        // Giga Impact
        if (MoveID == MOVE416_GIGA_IMPACT)
        {
            if (BattleMon_GetPreviousMove(AttackingMon) == MOVE416_GIGA_IMPACT && !BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 0;
            }
        }

        // Stomping Tantrum / Uproar / Seething Chill / Thrash / Temper Flare
        if (MoveID == MOVE493_STOMPIN_TANTRUM || MoveID == MOVE253_UPROAR || MoveID == MOVE288_GRUDGE || MoveID == MOVE218_TEMPER_FLARE || MoveID == MOVE220_SEETHING_COLD || MoveID == MOVE037_THRASH)
        {
            if (BattleMon_GetTurnFlag(AttackingMon, TURNFLAG_MOVEFAILEDLASTTURN))
            {
                return 8192;
            }
        }

        // Weather Ball / Weather Crash
        if (MoveID == MOVE311_WEATHER_BALL || MoveID == MOVE271_WEATHER_CRASH)
        {
            if (AttackingMon->HeldItem != IT0544_UTILITY_UMBRELLA && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT && ServerEvent_GetWeather(a1) > 0)
            {
                if (ServerEvent_GetWeather(a1) > 0 || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL122_FLOWER_GIFT)
                {
                    return 8192;
                }
            }
        }

        // Payback, Revenge, and Avalanche
        if (MoveID == MOVE371_PAYBACK || MoveID == MOVE279_REVENGE || MoveID == MOVE419_AVALANCHE)
        {
            if (Handler_CalculateSpeed(a1, AttackingMon, 0) < Handler_CalculateSpeed(a1, DefendingMon, 0))
            {
                return 8192;
            }
        }

        // Spit Up
        if (MoveID == MOVE255_SPIT_UP)
        {
            if (!PML_ItemIsBerry(AttackingMon->HeldItem))
            {
                return 0;
            }
        }

        if (MoveID == MOVE282_KNOCK_OFF)
        {
            if (BattleMon_GetHeldItem(DefendingMon) && !HandlerCommon_CheckIfCanStealPokeItem(a1, AttackingMon->ID, DefendingMon->ID))
            {
                return 6144;
            }
        }

        if (MoveID == MOVE478_POWER_TRIP || MoveID == MOVE500_STORED_POWER)
        {
            int total;
            int temp;
            total = 0;
            for (int i = 0; i < 7; ++i)
            {
                temp = BattleMon_GetValue(AttackingMon, BattleMonValues[i]) - 6;
                if (temp > 0)
                {
                    total += temp;
                }
            }

            if (total)
            {
                return 4096 + (2048 * total);
            }
        }

        return 4096;
    }

#pragma endregion

#pragma region SimulationDamage
    int THUMB_BRANCH_SAFESTACK_Handler_SimulationDamage(ServerFlow *a1, int a2, int a3, int a4, bool isSimulation, bool something)
    {
        int TypeEffectiveness;   // r6
        BattleMon *DefendingMon; // [sp+14h] [bp-34h]
        BattleMon *AttackingMon; // [sp+18h] [bp-30h]
        __int16 moveParam[20];
        unsigned __int16 v12; // [sp+1Ch] [bp-2Ch] BYREF
        int v14;              // [sp+48h] [bp+0h]
        int v15;              // [sp+4Ch] [bp+4h]
        int v16;
        unsigned int ratio;
        int critFlag;
        int v17;
        int isMoldBreaker;
        int a4check;

        AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, a2);
        DefendingMon = PokeCon_GetBattleMon(a1->pokeCon, a3);

        if (!a4)
        {
            return 0;
        }

        v12 = checkCalcTable(a1, AttackingMon, DefendingMon, (MoveID)a4);
        if (v12)
        {
            return v12;
        }

        isMoldBreaker = HasMoldBreaker(AttackingMon);

        // Checks for Static Damage Moves
        if (a4 == MOVE101_NIGHT_SHADE && !BattleMon_HasType(DefendingMon, TYPE_NORMAL))
        {
            return AttackingMon->Level;
        }
        else if (a4 == MOVE069_SEISMIC_TOSS && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL113_SCRAPPY))
        {
            return AttackingMon->Level;
        }
        else if (a4 == MOVE149_PSYWAVE && (!BattleMon_HasType(DefendingMon, TYPE_DARK) || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL039_INNER_FOCUS))
        {
            return AttackingMon->Level;
        }
        else if (a4 == MOVE162_SUPER_FANG && (!BattleMon_HasType(DefendingMon, TYPE_GHOST) || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL113_SCRAPPY))
        {
            int losthealth = DefendingMon->CurrentHP / 2u;
            if (!losthealth)
            {
                losthealth = 1;
            }
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL093_STRONG_JAW)
            {
                return (losthealth + DefendingMon->CurrentHP / 4u);
            }
            else
            {
                return losthealth;
            }
        }
        else
        {
            a4check = a4;
        }

        if (!PML_MoveIsDamaging(a4))
        {
            int actualMove;

            // Copycat
            if (a4 == MOVE383_COPYCAT && (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL158_PRANKSTER || AttackingMon->HeldItem == IT0136_TRICKSTER_HERB || (Handler_CalculateSpeed(a1, AttackingMon, 0) > Handler_CalculateSpeed(a1, DefendingMon, 0))))
            {
                actualMove = Handler_GetPrevUsedMove(a1);
                if (actualMove && !j_j_IsNotAllowedCopycatMove(actualMove))
                {
                    a4check = actualMove;
                }
                else
                {
                    return 0;
                }
            }
            // Nature Power
            else if (a4 == MOVE267_NATURE_POWER)
            {
                int BattleTerrain = Handler_GetBattleTerrain(a1);

                // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

                if (BattleTerrain == 5u)
                {
                    a4check = 402;
                }
                else if (BattleTerrain == 11u)
                {
                    a4check = 89;
                }
                else if (BattleTerrain == 0xCu)
                {
                    a4check = 56;
                }
                else if (BattleTerrain == 7u)
                {
                    a4check = 59;
                }
                else if (BattleTerrain == 9u)
                {
                    a4check = 426;
                }
                else if (BattleTerrain == 0xAu)
                {
                    a4check = 157;
                }
                else if (BattleTerrain == 0xDu)
                {
                    a4check = 58;
                }
                else
                {
                    a4check = 161;
                }
            }
            else
            {
                return 0;
            }
        }

        ++a1->SimulationCounter;

        if (BattleMon_IsIllusionEnabled(DefendingMon))
        {
            DefendingMon = MainModule_GetIllusionDisguise(a1->mainModule, (int)a1->pokeCon, (int)DefendingMon);
        }

        TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, a4check);
        ratio = CheckRatio(a1, AttackingMon, DefendingMon, a4check);
        ServerEvent_GetMoveParam(a1, a4check, (int)AttackingMon, (MoveParam *)moveParam);

        if (a4check == MOVE165_STRUGGLE)
        {
            ((MoveParam *)moveParam)->moveType = 17;
        }
        if ((a4check == MOVE311_WEATHER_BALL || a4check == MOVE271_WEATHER_CRASH) && (BattleMon_GetHeldItem(AttackingMon) != IT0544_UTILITY_UMBRELLA || BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT))
        {
            v17 = ServerEvent_GetWeather(a1);
            if (v17 == 1)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE053_FLAMETHROWER);
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            else if (v17 == 2)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE057_SURF);
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            else if (v17 == 3)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE058_ICE_BEAM);
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            else if (v17 == 4)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE408_POWER_GEM);
                ((MoveParam *)moveParam)->moveType = TYPE_ROCK;
            }
        }

        if (a4check == MOVE363_NATURAL_GIFT)
        {
            if (PML_ItemIsBerry(BattleMon_GetHeldItem(AttackingMon)))
            {
                Types Type = (Types)ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_TYPE);
                if (IsEqual(Type, TYPE_FIGHTING))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE280_BRICK_BREAK);
                }
                else if (IsEqual(Type, TYPE_FLYING))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE332_AERIAL_ACE);
                }
                else if (IsEqual(Type, TYPE_FAIRY))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE066_SUBMISSION);
                }
                else if (IsEqual(Type, TYPE_FIRE))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE053_FLAMETHROWER);
                }
                else if (IsEqual(Type, TYPE_WATER))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE057_SURF);
                }
                else if (IsEqual(Type, TYPE_ELECTRIC))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE085_THUNDERBOLT);
                }
                else if (IsEqual(Type, TYPE_ROCK))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE408_POWER_GEM);
                }
                else if (IsEqual(Type, TYPE_GROUND))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE089_EARTHQUAKE);
                }
                else if (IsEqual(Type, TYPE_STEEL))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE360_GYRO_BALL);
                }
                else if (IsEqual(Type, TYPE_DRAGON))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE337_DRAGON_CLAW);
                }
                else if (IsEqual(Type, TYPE_ICE))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE058_ICE_BEAM);
                }
                else if (IsEqual(Type, TYPE_BUG))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE404_X_SCISSOR);
                }
                else if (IsEqual(Type, TYPE_POISON))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE440_CROSS_POISON);
                }
                else if (IsEqual(Type, TYPE_PSYCHIC))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE060_PSYBEAM);
                }
                else if (IsEqual(Type, TYPE_GHOST))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE421_SHADOW_CLAW);
                }
                else if (IsEqual(Type, TYPE_DARK))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE282_KNOCK_OFF);
                }
                else if (IsEqual(Type, TYPE_GRASS))
                {
                    TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE202_GIGA_DRAIN);
                }
                ((MoveParam *)moveParam)->moveType = ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_TYPE);

                if (90 == ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_POWER))
                {
                    ratio = 4608;
                }
                if (100 == ItemGetParam(BattleMon_GetHeldItem(AttackingMon), ITSTAT_NATURAL_GIFT_POWER))
                {
                    ratio = 5120;
                }
            }
        }
        if (a4check == MOVE546_TECHNO_BLAST)
        {
            if (AttackingMon->HeldItem == IT0119_CHILL_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE058_ICE_BEAM);
                ((MoveParam *)moveParam)->moveType = TYPE_ICE;
            }
            if (AttackingMon->HeldItem == IT0116_DOUSE_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE056_HYDRO_PUMP);
                ((MoveParam *)moveParam)->moveType = TYPE_WATER;
            }
            if (AttackingMon->HeldItem == IT0118_BURN_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE083_FIRE_SPIN);
                ((MoveParam *)moveParam)->moveType = TYPE_FIRE;
            }
            if (AttackingMon->HeldItem == IT0117_SHOCK_DRIVE)
            {
                TypeEffectiveness = Handler_SimulationEffectivenessCore(a1, a2, a3, MOVE085_THUNDERBOLT);
                ((MoveParam *)moveParam)->moveType = TYPE_ELECTRIC;
            }
        }
        if (a4check == MOVE327_SKY_UPPERCUT || a4check == MOVE357_FREEZE_DRY)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon));
        }

        if (a4check == MOVE533_SACRED_SWORD || a4check == MOVE547_RELIC_SONG)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAlteredSacredSword(((MoveParam *)moveParam)->moveType, BattleMon_GetPokeType(DefendingMon));
        }

        if (a4check == MOVE498_CHIP_AWAY)
        {
            TypeEffectiveness = 3;
        }

        if (!isMoldBreaker)
        {
            if (((MoveParam *)moveParam)->moveType == TYPE_FIRE && BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL021_WELL_BAKED_BODY)
            {
                ratio = 0;
            }
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL015_THUNDER_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL031_LIGHTNING_ROD) && ((MoveParam *)moveParam)->moveType == TYPE_ELECTRIC)
            {
                ratio = 0;
            }
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL114_STORM_DRAIN || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL087_DRY_SKIN) && ((MoveParam *)moveParam)->moveType == TYPE_WATER)
            {
                ratio = 0;
            }
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL157_SAP_SIPPER || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL087_DRY_SKIN) && ((MoveParam *)moveParam)->moveType == TYPE_GRASS)
            {
                ratio = 0;
            }
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL026_LEVITATE || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL087_DRY_SKIN) && ((MoveParam *)moveParam)->moveType == TYPE_GROUND)
            {
                ratio = 0;
            }
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL006_BULLETPROOF && isInArray(a4check, 0))
            {
                ratio = 0;
            }
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL051_WIND_RIDER && isInArray(a4check, 1))
            {
                ratio = 0;
            }
        }

        if (a4check == MOVE006_PAY_DAY || a4check == MOVE524_FROST_BREATH || a4check == MOVE440_CROSS_POISON || a4check == MOVE346_WICKED_BLOW || a4check == MOVE190_OCTAZOOKA || a4check == MOVE480_STORM_THROW || a4check == MOVE163_SLASH)
        {
            if (BattleMon_GetConditionFlag(DefendingMon, CONDITIONFLAG_DEFENSECURL))
            {
                critFlag = 0;
            }
            else if (Handler_IsSideEffectActive(a1, GetSideFromMonID(BattleEventVar_GetValue(VAR_DEFENDING_MON)), 5))
            {
                critFlag = 0;
            }
            else if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL004_BATTLE_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL075_SHELL_ARMOR)
            {
                if (!isMoldBreaker)
                {
                    critFlag = 0;
                }
                else
                {
                    critFlag = 1;
                }
            }
            critFlag = 1;
        }
        else
        {
            critFlag = 0;
        }

        ServerEvent_CalcDamage(
            a1,
            AttackingMon,
            DefendingMon,
            (MoveParam *)moveParam,
            TypeEffectiveness,
            ratio,
            critFlag,
            isSimulation,
            &v12);
        --a1->SimulationCounter;

        /* Store v12 somewhere here, using the turnCount, attackerId, defenderId and move as your keys */
        saveToCalcTable(a1, AttackingMon, DefendingMon, (MoveID)a4, v12);

        if (a4check == MOVE228_PURSUIT && (v12 * 2) >= DefendingMon->CurrentHP)
        {
            if (RandomInRange(1, 100) >= 75)
            {
                v12 *= 2;
            }
        }

        return v12;
    }

#pragma endregion

#pragma region SwitchInAIHelpers

    int checkForTechnician(BattleMon *AttackingMon, int MoveID, unsigned int a3)
    {
        if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL101_TECHNICIAN)
        {
            if (PML_MoveGetBasePower(MoveID) <= 60)
            {
                return a3 * 1.5;
            }
        }
        return a3;
    }

    int checkForAbilityAndItemBPChanges(BattleMon *AttackingMon, BattleMon *DefendingMon, int Type, int TypeEffectivenessVsMon, unsigned int a4)
    {

        int value;
        value = a4;

        // Abilities
        if (!HasMoldBreaker(AttackingMon))
        {
            // Heatproof
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL085_HEATPROOF && Type == TYPE_FIRE)
            {
                value *= .25;
            }
            // Thick Fat
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL047_THICK_FAT && (Type == TYPE_FIRE || Type == TYPE_ICE))
            {
                value *= .5;
            }
            // Dry Skin
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL087_DRY_SKIN || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL017_FLUFFY) && Type == TYPE_FIRE)
            {
                value *= 2;
            }
            // Toxic Boost
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL137_TOXIC_BOOST && Type == TYPE_POISON)
            {
                value *= .5;
            }

            // Filter and Solid Rock
            if ((BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL111_FILTER || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL116_SOLID_ROCK) && TypeEffectivenessVsMon > 3)
            {
                if (TypeEffectivenessVsMon == 4)
                {
                    value *= .75;
                }
                else
                {
                    value *= .75;
                    value *= .75;
                }
            }

            if ((BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL110_TENACITY) && TypeEffectivenessVsMon < 3)
            {
                value *= 2;
            }
            // Swift Swim
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL033_SWIFT_SWIM && Type == TYPE_WATER)
            {
                value *= .5;
            }
            // Slush Rush
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL077_SLUSH_RUSH && Type == TYPE_ICE)
            {
                value *= .5;
            }
            // Sand Force and Sand Rush
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL146_SAND_RUSH && Type == TYPE_ROCK)
            {
                value *= .5;
            }

            // Justified
            if (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL154_JUSTIFIED && Type == TYPE_DARK)
            {
                value *= .5;
            }
        }
        return value;
    }

    int checkForBPChanges(BattleMon *AttackingMon, BattleMon *DefendingMon, int MoveID, unsigned int a4, BtlClientWk *work)
    {
        int randomvalue;
        unsigned int value;
        ServerFlow *server;
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        //  k::Printf("\nCheck 1a: Check for BP Changes");
        server = BattleServer_GetServerFlow(work->mainModule->server);
        int isMoldBreaker = HasMoldBreaker(AttackingMon);

        // k::Printf("\nCheck 1b: Check for BP Changes");

        value = a4;

        if (IsEqual(MoveID, MOVE474_VENOSHOCK))
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_POISON))
            {
                return value * 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        //  k::Printf("\nCheck 2: Check for BP Changes");

        // Meteor Beam, Skull Bash, Sky Attack
        if (IsEqual(MoveID, MOVE130_SKULL_BASH) || IsEqual(MoveID, MOVE553_METEOR_BEAM) || IsEqual(MoveID, MOVE143_SKY_ATTACK))
        {
            if (AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return value / 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // k::Printf("\nCheck 3: Check for BP Changes");

        // Reversal and Flail
        // Set base power to 20
        if (IsEqual(MoveID, MOVE175_FLAIL) || IsEqual(MoveID, MOVE179_REVERSAL))
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return value;
            }
            else if (Value >= 281600)
            {
                return value * 2;
            }
            else if (Value < 281600 && Value >= 145000)
            {
                return value * 4;
            }
            else if (Value < 145000 && Value >= 85300)
            {
                return value * 8;
            }
            else if (Value < 85300 && Value >= 42700)
            {
                return value * 10;
            }
            else if (Value < 42700 && Value >= 17100)
            {
                return value * 15;
            }
            else
            {
                return value * 20;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // k::Printf("\nCheck 4: Check for BP Changes");

        // Water Spout and Eruption
        if (IsEqual(MoveID, MOVE323_WATER_SPOUT) || IsEqual(MoveID, MOVE284_ERUPTION))
        {
            int Value;
            Value = BattleMon_GetHPRatio(AttackingMon);

            if (Value == 409600)
            {
                return value;
            }
            else if (Value < 409600 && Value >= 384000)
            {
                return value / 16 * 15;
            }
            else if (Value < 384000 && Value >= 358400)
            {
                return value / 8 * 7;
            }
            else if (Value < 358400 && Value >= 332800)
            {
                return value / 16 * 13;
            }
            else if (Value < 332800 && Value >= 307200)
            {
                return value / 8 * 6;
            }
            else if (Value < 307200 && Value >= 281600)
            {
                return value / 16 * 11;
            }
            else if (Value < 281600 && Value >= 256000)
            {
                return value / 8 * 5;
            }
            else if (Value < 256000 && Value >= 230400)
            {
                return value / 16 * 9;
            }
            else if (Value < 230400 && Value >= 204800)
            {
                return value / 2;
            }
            else
            {
                return 0;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        //  k::Printf("\nCheck 5: Check for BP Changes");

        // Electro Ball
        if (IsEqual(MoveID, MOVE486_ELECTRO_BALL))
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) > Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
            else
            {
                return value;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // k::Printf("\nCheck 6: Check for BP Changes");

        // // Gyro Ball
        if (IsEqual(MoveID, MOVE360_GYRO_BALL))
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) < Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
            else
            {
                return value;
            }
        }

        // k::Printf("\nCheck 7: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // Electro Shot
        if (IsEqual(MoveID, MOVE193_ELECTRO_SHOT))
        {
            if (BattleField_GetWeather() != 2 && AttackingMon->HeldItem != IT0271_POWER_HERB)
            {
                return value / 2;
            }
        }
        // k::Printf("\nCheck 8: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // Solarbeam and Solar Blade
        if (IsEqual(MoveID, MOVE076_SOLAR_BEAM) || IsEqual(MoveID, MOVE554_SOLAR_BLADE))
        {
            if (BattleField_GetWeather() != 1 && AttackingMon->HeldItem != IT0271_POWER_HERB && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL034_CHLOROPHYLL && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL094_SOLAR_POWER && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) != ABIL122_FLOWER_GIFT)
            {
                return value / 2;
            }
        }
        // k::Printf("\nCheck 9: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        if (IsEqual(MoveID, MOVE506_HEX) || IsEqual(MoveID, MOVE272_BARB_BARRAGE) || IsEqual(MoveID, MOVE251_BEAT_UP) || IsEqual(MoveID, MOVE244_BITTER_MALICE) || IsEqual(MoveID, MOVE169_INFERNAL_PARADE))
        {
            if (BattleMon_GetStatus(DefendingMon))
            {
                return value * 2;
            }
        }
        //  k::Printf("\nCheck 10: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // Acrobatics
        if (IsEqual(MoveID, MOVE512_ACROBATICS))
        {
            if (!AttackingMon->HeldItem || AttackingMon->HeldItem == IT0556_FLYING_GEM)
            {
                return value * 2;
            }
        }
        // k::Printf("\nCheck 11: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        if (IsEqual(MoveID, MOVE003_DOUBLE_SLAP) || IsEqual(MoveID, MOVE022_VINE_WHIPS) || IsEqual(MoveID, MOVE458_DOUBLE_HIT) || IsEqual(MoveID, MOVE024_DOUBLE_KICK) || IsEqual(MoveID, MOVE011_DUAL_WINGBEAT) || IsEqual(MoveID, MOVE041_TWINEEDLE) || IsEqual(MoveID, MOVE155_BONEMERANG) || IsEqual(MoveID, MOVE544_GEAR_GRIND) || IsEqual(MoveID, MOVE530_DUAL_CHOP))
        {
            return value * 2;
        }
        // k::Printf("\nCheck 12: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // //k::print("\nCheck #7");
        //  All 3 hit moves
        if (IsEqual(MoveID, MOVE167_TRIPLE_KICK) || IsEqual(MoveID, MOVE470_TRIPLE_AXEL) || IsEqual(MoveID, MOVE471_TRIPLE_DIVE) || IsEqual(MoveID, MOVE161_TRI_ATTACK))
        {
            return value * 3;
        }
        // k::Printf("\nCheck 13: Check for BP Changes");
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // Wake Up Slap and Dream Eater
        if (IsEqual(MoveID, MOVE138_DREAM_EATER) || IsEqual(MoveID, MOVE358_WAKE_UP_SLAP))
        {
            if (BattleMon_CheckIfMoveCondition(DefendingMon, CONDITION_SLEEP))
            {
                return value * 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        if (IsEqual(MoveID, MOVE514_RETALIATE))
        {
            if (checkRetaliate(server, AttackingMon->ID, 0))
            {
                // //k::printf("\nWe have triggered this effect for retaliate with switch AI\n");
                return value * 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        // autocrit moves
        if (IsEqual(MoveID, MOVE440_CROSS_POISON) || IsEqual(MoveID, MOVE006_PAY_DAY) || IsEqual(MoveID, MOVE163_SLASH) || IsEqual(MoveID, MOVE480_STORM_THROW) || IsEqual(MoveID, MOVE190_OCTAZOOKA) || IsEqual(MoveID, MOVE524_FROST_BREATH) || IsEqual(MoveID, MOVE346_WICKED_BLOW))
        {
            if (BattleMon_GetConditionFlag(DefendingMon, CONDITIONFLAG_DEFENSECURL))
            {
                return value;
            }
            if (Handler_IsSideEffectActive(server, GetSideFromMonID(BattleMon_GetID(DefendingMon)), 5))
            {
                return value;
            }
            if (!isMoldBreaker && (BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL075_SHELL_ARMOR || BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY) == ABIL004_BATTLE_ARMOR))
            {
                return value;
            }
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL097_SNIPER)
            {
                return value * 3;
            }
            else
            {
                return value * 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        if (IsEqual(MoveID, MOVE013_RAZOR_WINDS) || IsEqual(MoveID, MOVE004_COMET_PUNCH) || IsEqual(MoveID, MOVE042_PIN_MISSILE) ||
            IsEqual(MoveID, MOVE131_SPIKE_CANNON) || IsEqual(MoveID, MOVE140_BARRAGE) || IsEqual(MoveID, MOVE154_FURY_SWIPES) || IsEqual(MoveID, MOVE198_BONE_RUSH) ||
            IsEqual(MoveID, MOVE292_ARM_THRUST) || IsEqual(MoveID, MOVE331_BULLET_SEED) || IsEqual(MoveID, MOVE333_ICICLE_SPEAR) || IsEqual(MoveID, MOVE350_ROCK_BLAST) ||
            IsEqual(MoveID, MOVE541_TAIL_SLAP) || IsEqual(MoveID, MOVE378_SCALE_SHOT))
        {
            if (BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL092_SKILL_LINK)
            {
                return value * 5;
            }
            else if (AttackingMon->HeldItem == IT0317_LOADED_DICE)
            {
                return value * 4;
            }
            else
            {
                return value * 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);

        if (IsEqual(MoveID, MOVE279_REVENGE) || IsEqual(MoveID, MOVE419_AVALANCHE) || IsEqual(MoveID, MOVE371_PAYBACK))
        {
            if (Handler_CalculateSpeed(server, AttackingMon, 0) < Handler_CalculateSpeed(server, DefendingMon, 0))
            {
                return value * 2;
            }
        }
        randomvalue = BattleMon_GetHeldItem(AttackingMon);
        if (IsEqual(MoveID, MOVE282_KNOCK_OFF))
        {
            if (BattleMon_GetHeldItem(DefendingMon) && !HandlerCommon_CheckIfCanStealPokeItem(server, AttackingMon->ID, DefendingMon->ID))
            {
                return value * 1.5;
            }
        }

        return value;
    }

    int checkForSTAB(BattleMon *a1, int a2, unsigned int a3)
    {
        if (BattleMon_HasType(a1, (Types)a2))
        {
            return a3 * 1.5;
        }
        else if (BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL145_SAVANT)
        {
            return a3 * 1.5;
        }
        else
        {
            return a3;
        }
    }

    bool CheckIfImmuneAbility(int Type, int MoveID, BattleMon *DefendingMon)
    {
        int ability;

        ability = BattleMon_GetValue(DefendingMon, VALUE_EFFECTIVE_ABILITY);

        if (Type == TYPE_WATER && (ability == ABIL114_STORM_DRAIN || ability == ABIL011_WATER_ABSORB || ability == ABIL087_DRY_SKIN))
        {
            return true;
        }
        if (Type == TYPE_GROUND && (ability == ABIL026_LEVITATE))
        {
            return true;
        }
        if (Type == TYPE_ELECTRIC && (ability == ABIL010_VOLT_ABSORB || ability == ABIL015_THUNDER_ARMOR || ability == ABIL078_MOTOR_DRIVE || ability == ABIL031_LIGHTNING_ROD))
        {
            return true;
        }
        if (Type == TYPE_GRASS && (ability == ABIL157_SAP_SIPPER))
        {
            return true;
        }
        if (Type == TYPE_FIRE && ((ability == ABIL018_FLASH_FIRE) || ability == ABIL021_WELL_BAKED_BODY))
        {
            return true;
        }
        if (ability == ABIL043_AMPLIFIER && getMoveFlag(MoveID, FLAG_SOUND))
        {
            return true;
        }
        if (ability == ABIL006_BULLETPROOF && isInArray(MoveID, 0))
        {
            return true;
        }
        if (ability == ABIL051_WIND_RIDER && isInArray(MoveID, 1))
        {
            return true;
        }
        return false;
    }

#pragma endregion

#pragma region SwitchInAI

    unsigned int THUMB_BRANCH_PickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4)
    {
        unsigned int v5;                     // r5
        BattleMon *MonData;                  // r6
        int ID;                              // r4
        unsigned int BasePower;              // r4
        unsigned int TypeEffectivenessVsMon; // r0
        unsigned int v10;                    // r0
        unsigned int result;                 // r0
        unsigned int j;                      // r5
        unsigned int k;                      // r6
        unsigned int v14;                    // r1
        unsigned int v15;                    // r0
        unsigned int v18;
        int randomvalue;
        u8 v16;                 // r1
        int Type;               // [sp+8h] [bp-38h]
        unsigned int MoveCount; // [sp+Ch] [bp-34h]
        unsigned int i;         // [sp+10h] [bp-30h]
        int PokeType;           // [sp+14h] [bp-2Ch]
        __int16 v23[6];         // [sp+1Ch] [bp-24h]
        BattleMon *v24;         // [sp+28h] [bp-18h]

        v24 = a4;
        PokeType = BattleMon_GetPokeType(a4);
        randomvalue = BattleMon_GetHeldItem(a4);
        // k::Printf("\nStep 1\n");
        for (i = 0; i < a3; i = (i + 1))
        {
            v5 = 0;
            randomvalue = BattleMon_GetHeldItem(a4);
            v23[i] = 0;
            MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
            randomvalue = BattleMon_GetHeldItem(a4);
            if (!BattleMon_IsFainted(MonData))
            {
                randomvalue = BattleMon_GetHeldItem(a4);
                MoveCount = BattleMon_GetMoveCount(MonData);
                if (MoveCount)
                {
                    randomvalue = BattleMon_GetHeldItem(a4);
                    do
                    {
                        randomvalue = BattleMon_GetHeldItem(a4);
                        if (Move_GetPP(MonData, v5))
                        {
                            randomvalue = BattleMon_GetHeldItem(a4);
                            ID = Move_GetID(MonData, v5);
                            randomvalue = BattleMon_GetHeldItem(a4);
                            if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
                            {
                                randomvalue = BattleMon_GetHeldItem(a4);
                                Type = PML_MoveGetType(ID);
                                BasePower = PML_MoveGetBasePower(ID);
                                // k:Printf("\nBase Power from %d is %d\n", ID, BasePower);
                                randomvalue = BattleMon_GetHeldItem(a4);
                                // Weather Ball Checks
                                if (ID == MOVE311_WEATHER_BALL || ID == MOVE271_WEATHER_CRASH)
                                {
                                    if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT && MonData->HeldItem != IT0544_UTILITY_UMBRELLA)
                                    {

                                        v18 = BattleField_GetWeather();

                                        if (v18 != 0)
                                        {
                                            BasePower = 100;
                                        }
                                        if (v18 == 1 || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL094_SOLAR_POWER || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL034_CHLOROPHYLL || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL122_FLOWER_GIFT)
                                        {
                                            BasePower = 100;
                                            Type = TYPE_FIRE;
                                        }
                                        else if (v18 == 2)
                                        {
                                            Type = TYPE_WATER;
                                        }
                                        else if (v18 == 3)
                                        {
                                            Type = TYPE_ICE;
                                        }
                                        else if (v18 == 4)
                                        {
                                            Type = TYPE_ROCK;
                                        }
                                    }
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);
                                if (ID == MOVE267_NATURE_POWER)
                                {
                                    int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

                                    // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

                                    if (BattleTerrain == 5u)
                                    {
                                        ID = 402;
                                    }
                                    else if (BattleTerrain == 11u)
                                    {
                                        ID = 89;
                                    }
                                    else if (BattleTerrain == 0xCu)
                                    {
                                        ID = 56;
                                    }
                                    else if (BattleTerrain == 7u)
                                    {
                                        ID = 59;
                                    }
                                    else if (BattleTerrain == 9u)
                                    {
                                        ID = 426;
                                    }
                                    else if (BattleTerrain == 0xAu)
                                    {
                                        ID = 157;
                                    }
                                    else if (BattleTerrain == 0xDu)
                                    {
                                        ID = 58;
                                    }
                                    else
                                    {
                                        ID = 161;
                                    }
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);

                                if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
                                {
                                    Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);
                                    BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ELECTRIC;
                                    BasePower *= 1.2;
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_ICE;
                                    BasePower *= 1.2;
                                }
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL060_AERILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FLYING;
                                    BasePower *= 1.2;
                                }
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL040_PIXILATE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_FAIRY;
                                    BasePower *= 1.2;
                                }
                                if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL096_NORMALIZE && Type == TYPE_NORMAL)
                                {
                                    Type = TYPE_NORMAL;
                                }
                                // //k::printf("\nBase Power from %d is %d, and the Type is %d\n", ID, BasePower, Type);

                                randomvalue = BattleMon_GetHeldItem(a4);
                                // if (BasePower < 0xA)
                                // {
                                //     BasePower = 60;
                                // }
                                if (ID == MOVE327_SKY_UPPERCUT || ID == MOVE357_FREEZE_DRY || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL007_CORROSION)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
                                    // //k::printf("\n 2. TypeEffectivenessVsMon is: %d for Move %d \n", TypeEffectivenessVsMon, a4);
                                }
                                else if (ID == MOVE533_SACRED_SWORD || MOVE547_RELIC_SONG)
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAlteredSacredSword(Type, PokeType);
                                }
                                else if (ID == MOVE498_CHIP_AWAY)
                                {
                                    TypeEffectivenessVsMon = 3;
                                }
                                else
                                {
                                    TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);

                                if (!HasMoldBreaker(MonData) && CheckIfImmuneAbility(Type, ID, a4))
                                {
                                    TypeEffectivenessVsMon = 0;
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);
                                if (TypeEffectivenessVsMon <= 5)
                                {
                                    randomvalue = BattleMon_GetHeldItem(a4);
                                    switch (TypeEffectivenessVsMon)
                                    {
                                    case 0:
                                        BasePower = 0;
                                        break;
                                    case 1:
                                        v10 = BasePower << 14;
                                        goto LABEL_11;
                                    case 2:
                                        v10 = BasePower << 15;
                                        goto LABEL_11;
                                    case 4:
                                        v10 = BasePower << 17;
                                        goto LABEL_11;
                                    case 5:
                                        v10 = BasePower << 18;
                                    LABEL_11:
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        k::Printf("\nStep 19\n");
                                        v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        v10 = checkForTechnician(MonData, ID, v10);
                                        // //k::printf("\n Base Power of %d after Tech changes is %d\n", ID, v10);
                                        v10 = checkForSTAB(MonData, Type, v10);
                                        v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);

                                        // //k::printf("\n Base Power of %d after STAB changes %d\n", ID, v10);
                                        BasePower = HIWORD(v10);
                                        // //k::printf("\n Base Power of %d after STAB and HIWORD changes %d\n", ID, BasePower);
                                        break;
                                    default:
                                        k::Printf("\nStep 19a\n");
                                        v10 = BasePower << 16;
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        // //k::printf("\n Base Power of %d before any changes is %d\n", ID, v10);
                                        v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        // //k::printf("\n Base Power of %d after BP changes is %d\n", ID, v10);
                                        v10 = checkForTechnician(MonData, ID, v10);
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        // //k::printf("\n Base Power of %d after Tech changes is %d\n", ID, v10);
                                        v10 = checkForSTAB(MonData, Type, v10);
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        // //k::printf("\n Base Power of %d after STAB changes %d\n", ID, v10);
                                        BasePower = HIWORD(v10);
                                        randomvalue = BattleMon_GetHeldItem(a4);
                                        // //k::printf("\n Base Power of %d after STAB and HIWORD changes %d\n", ID, BasePower);

                                        break;
                                    }
                                }
                                randomvalue = BattleMon_GetHeldItem(a4);
                                if (v23[i] < BasePower)
                                {
                                    // //k::printf("\n Base Power of %d is %d \n", ID, BasePower);
                                    v23[i] = BasePower;
                                }
                            }
                        }
                        v5 = (v5 + 1);
                    } while (v5 < MoveCount);

                    // before moving on to the next pokemon, the game will check if the pokemon has the ability illusion.
                    if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION)
                    {
                        // If it does, it will check the output of a modified version of this function that does not have the following check
                        if (PersonalPickBestMonToSwitchInto(a1, a2, a3, a4, 0) == a2[i])
                        {
                            // if the output is the same as the id of the pokemon, i.e. this Pokemon has the highest BP move and would switch in
                            // then it has a 33% chance to quarter the perceived BP of the illusion pokemon's move, heavily reducing its' chance of switching in.
                            if (RandomInRange(1, 100) >= 66)
                            {
                                v23[i] *= .25;
                            }
                        }
                        // If it's not the strongest BP move, then it instead has a chance to double its perceived BP to "skip ahead" of the switch order
                        // This only triggers though if it has a sufficiently powerful move.
                        else if (v23[i] >= 140)
                        {
                            if (RandomInRange(1, 100) >= 66)
                            {
                                v23[i] *= 2;
                            }
                        }
                    }
                }
            }
        }
        // k::Printf("\nStep 21\n");
        result = a3;
        for (j = 0; j < a3; result = a3)
        {
            //  k::Printf("\nStep %d\n", 21 + j);
            for (k = (j + 1); k < a3; k = (k + 1))
            {
                v14 = v23[k];
                v15 = v23[j];
                if (v15 < v14)
                {
                    v23[j] = v14;
                    v23[k] = v15;
                    v16 = a2[j];
                    a2[j] = a2[k];
                    a2[k] = v16;
                }
            }
            j = (unsigned __int8)(j + 1);
        }
        return result;
    }

#pragma endregion

#pragma region MidBattleSwitchAI

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ MID BATTLE SWITCH AI ----------------------------------------
        --------------------------------------------------------------------------------------------------

        This function decideds whether the user should switch if locked into an ineffective move with choice items.
        We are going to improve that functionality and then hijack the function to inject some additional condditions
        to look for.

        is one we're hijaking in order to add a few more conditions for mid-battle switch AI.

        Improvements to Choice/Encore Logic
            - Add in Encore lock switch AI that shares properties with the choice lock one
            - Add in checks for disable and torment
            - Improve the choice lock logic to refer to damage output to decide whether to switch
                - (Ideal) use SimulationDamage to check potential damage output and increase odds if at or under 25%.
                - (Sloppy) Judge entirely by effectiveness

        Switch out if Ineffective
            - Add a check that applies to any Pokemon even if they aren't in encore or choice locked that checks
            their damage output.
            - If it's below 25% with any of their moves, they have an initially small but slowly increasing chance to switch out after 3 turns.

        Switch out for Wish
            - If there is a wish active, the pokemon is healthy, high chance to switch out.

        Switch out for Future Sight
            - If a Future sight is active and the pokemon is healthy, high chance to switch out.


    */

    bool AlternateSwitchConditions(BtlClientWk *work, BattleMon *attackingMon, BattleMon *defendingMon)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        ServerFlow *flow;
        unsigned int k;

        flow = BattleServer_GetServerFlow(work->mainModule->server);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(flow, attackingMon->ID);
        pokeCount = Handler_ExpandPokeID(flow, ExistFrontPokePos | 0x100, opposingPokePos);
        int turnCount = attackingMon->TurnCount;
        int damage = 0;
        bool switchout = 0;

        k::Printf("\n\nMidBattleSwitchAI: Debug Point 1: We have entered the function and will determine whether or not our outgoing damage is sufficient\n\n-----------\n\n");

        for (k = 0; k < pokeCount; (k + 1))
        {
            int i = 0;
            defender = Handler_GetBattleMon(flow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(attackingMon);
            int currentHp = defender->CurrentHP;
            int moveDamage = 0;
            k::Printf("\nMidBattleSwitchAI: Debug Point 2 for Loop %d: We are checking the user's damage output vs %d\n", k, defender->Species);
            do
            {

                moveDamage = Handler_SimulationDamage(flow,
                                                      BattleMon_GetID(attackingMon),
                                                      BattleMon_GetID(defender),
                                                      Move_GetID(attackingMon, i), false, false);

                k::Printf("\nMidBattleSwitchAI: Debug Point 3 for Loop %d:: The damage of move %d is %d\n", k, Move_GetID(attackingMon, i), damage);

                if ((moveDamage * 2) >= currentHp)
                {
                    k::Printf("\nMidBattleSwitchAI: Debug Point 4 for Loop %d:: We have confirmed that move %d has a OHKO or 2HKO vs enemy %d.\n", k, Move_GetID(attackingMon, i), defender->Species);
                    return 0;
                }
                else
                {
                    k::Printf("\nMidBattleSwitchAI: Debug Point 5 for Loop %d:: We have confirmed that move %d doesn't deal a OHKO or 2HKO\nWe will now check if it is higher than the highest damage recorded yet\n", k, Move_GetID(attackingMon, i));

                    if (moveDamage > damage)
                    {
                        k::Printf("\nMidBattleSwitchAI: Debug Point 5 for Loop %d: move %d is now our highest damage yet\n", k, moveDamage);
                        damage = moveDamage;
                    }
                }
                i++;
            } while (i < MoveCount);

            if ((damage * 10) < defender->MaxHP)
            {
                k::Printf("\nMidBattleSwitchAI: Debug Point 6a for Loop %d: We deal less than 10%\n", k);

                if (turnCount >= 2)
                {
                    if (RandomInRange(1, 100) < (10 + (turnCount * 2)))
                    {
                        switchout = 1;
                    }
                }
            }

            /* Moderately Negliglbe Damage */
            else if ((damage * 8) < defender->MaxHP)
            {
                if (turnCount >= 3)
                {
                    if (RandomInRange(1, 100) < (5 + turnCount))
                    {
                        switchout = 1;
                    }
                }
            }

            /* Mildly Negliglbe Damage */
            else if ((damage * 4) < defender->MaxHP)
            {
                k::Printf("\nMidBattleSwitchAI: Debug Point 6c for Loop %d:: We have confirmed that move %d has a OHKO or 2HKO vs enemy %d.\n", k, Move_GetID(attackingMon, i), defender->Species);
                if (turnCount >= 4)
                {
                    if (RandomInRange(1, 100) < (1 + turnCount))
                    {
                        switchout = 1;
                    }
                }
            }

            /* If the attacker can deal at least 25% damage to one of the combatants on the field, they won't switch out, even if they can't deal that much damage to the other combatant.*/
            else
            {
                k::Printf("\nMidBattleSwitchAI: Debug Point 7 for Loop %d: Our move deals more than 25% maximum health but less than 50%.\nNo change of switchout\n", k, Move_GetID(attackingMon, i), defender->Species);

                return 0;
            }
        }
        k::Printf("\nMidBattleSwitchAI: Debug Point 8: If negligible damage to both pokemon, chance at a switch out. If at least 25 percent to one of them, no chance. Switchout is %d\n", switchout);

        return switchout;
    }

    bool THUMB_BRANCH_SAFESTACK_ShouldSwitchIfChoicedIntoIneffectiveMove(BtlClientWk *work, BattleMon *attackingMon, BattleMon *defendingMon)
    {
        ConditionData MoveCondition; // r0
        int Param;                   // r0
        int TypeEffectiveness;
        bool IsDamaging; // r6
        int PokeType;    // r0
        __int64 v10;     // kr00_8
        bool result;     // r0
        __int64 v12;     // r0
        __int64 v13;     // kr08_8
        __int64 v14;     // kr10_8
        int moveID;      // [sp+0h] [bp-28h]
        int temp;
        int Type; // [sp+4h] [bp-24h]

        /* Encore and Choice Item Check */
        if (!BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_CHOICELOCK) && !BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_ENCORE))
        {
            // If the two conditions this function is defined for are not relevant, switch to the other one.
            return AlternateSwitchConditions(work, attackingMon, defendingMon);
        }

        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_CHOICELOCK))
        {
            MoveCondition = BattleMon_GetMoveCondition(attackingMon, CONDITION_CHOICELOCK);
            Param = Condition_GetParam(MoveCondition);
        }
        else if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_ENCORE))
        {
            MoveCondition = BattleMon_GetMoveCondition(attackingMon, CONDITION_ENCORE);
            Param = Condition_GetParam(MoveCondition);
        }

        /* Set up Variables */
        moveID = Param;

        if (!Param)
        {
            return 0;
        }

        /* Torment Checks */
        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_TORMENT))
        {
            return 1;
        }

        /* Disable Checks */
        if (BattleMon_CheckIfMoveCondition(attackingMon, CONDITION_DISABLEMOVE))
        {
            ConditionData MoveConditionData = BattleMon_GetMoveCondition(attackingMon, CONDITION_DISABLEMOVE);
            if (moveID == Condition_GetParam(MoveConditionData))
            {
                return 1;
            }
        }

        /* PP Checks */
        if (!Move_GetPP(attackingMon, Move_SearchIndex(attackingMon, moveID)))
        {
            return 1;
        }

        /* Nature Power Check */
        if (moveID == MOVE267_NATURE_POWER)
        {
            int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(work->mainModule->server));

            // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

            if (BattleTerrain == 5u)
            {
                moveID = 402;
            }
            else if (BattleTerrain == 11u)
            {
                moveID = 89;
            }
            else if (BattleTerrain == 0xCu)
            {
                moveID = 56;
            }
            else if (BattleTerrain == 7u)
            {
                moveID = 59;
            }
            else if (BattleTerrain == 9u)
            {
                moveID = 426;
            }
            else if (BattleTerrain == 0xAu)
            {
                moveID = 157;
            }
            else if (BattleTerrain == 0xDu)
            {
                moveID = 58;
            }
            else
            {
                moveID = 161;
            }
        }

        /* Copycat Check */
        /* Checks for the move that copycat would call and if they have priority from abilities or items */
        if (moveID == MOVE383_COPYCAT && BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL158_PRANKSTER)
        {
            int actualMove = Handler_GetPrevUsedMove(BattleServer_GetServerFlow(work->mainModule->server));
            if (actualMove && !j_j_IsNotAllowedCopycatMove(actualMove))
            {
                moveID = actualMove;
            }
        }

        /* Updating Variables with any stuff that might have changed from move replacing Moves */
        IsDamaging = PML_MoveIsDamaging(Param);
        Type = PML_MoveGetType(moveID);
        PokeType = BattleMon_GetPokeType(defendingMon);
        if (!IsDamaging)
        {
            return 1;
        }

        /* Natural Gift Check */
        if (moveID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(attackingMon)))
        {
            Type = ItemGetParam(BattleMon_GetHeldItem(attackingMon), ITSTAT_NATURAL_GIFT_TYPE);
        }

        if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL040_PIXILATE && Type == TYPE_NORMAL)
        {
            Type = TYPE_FAIRY;
        }
        if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
        {
            Type = TYPE_ICE;
        }
        if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
        {
            Type = TYPE_ELECTRIC;
        }
        if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL060_AERILATE && Type == TYPE_NORMAL)
        {
            Type = TYPE_FLYING;
        }
        if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL096_NORMALIZE)
        {
            Type = TYPE_NORMAL;
        }

        /* Alternate Type Effectiveness Checks */
        if (moveID == MOVE327_SKY_UPPERCUT || moveID == MOVE357_FREEZE_DRY || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL007_CORROSION)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAltered(Type, PokeType);
        }
        else if (moveID == MOVE533_SACRED_SWORD || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL039_INNER_FOCUS || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL096_NORMALIZE || BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL113_SCRAPPY)
        {
            TypeEffectiveness = GetTypeEffectivenessVsMonAlteredSacredSword(Type, PokeType);
        }
        else if (moveID == MOVE498_CHIP_AWAY)
        {
            TypeEffectiveness = 3;
        }
        else
        {
            TypeEffectiveness = GetTypeEffectivenessVsMon(Type, PokeType);
        }

        /*

            ------------------------------------ CORE ENCORE / CHOICE LOGIC ----------------------------------------

            Right now we have a naive solution that only checks for effectiveness. Ideally, we're going to have a check
            here that checks for damage output in general. We don't want the AI switching out when they see a kill, even
            if the move they're using is 4x resisted.


            [EFFECTIVNESS CHECKS]
                - If the move has 0 effectiveness whatsoever, it will switch to any other pokemon that can at least
                deal damage.

                - If the move is 4x resisted, it will switch to any other pokemon that can deal at least 0.5x damage.
                    (For pokemon with tinted lens, it will use the 2x resisted logic instead)

                - If the move is 2x resisted, it will switch to any pokemon with a super effective move.
                If there are only allies with neutral moves, it's only a 25% chance.
                    (For pokemon with tinted lens, it will not switch at all)

            -

            [DAMAGE CALC CHECKS]
                - If the move has a killing blow, stay in.

                - The move has a 2HKO, stay in.

                - If the move deals 25% or less damage and neither of the previous two conditions are applicable, 70% chance to switch

                - If the move deals 0% damage due to no effectiveness, guaranteed switch out if any other pokemon has a move.

        */

        int moveDamage = Handler_SimulationDamage(BattleServer_GetServerFlow(work->mainModule->server),
                                                  BattleMon_GetID(attackingMon),
                                                  BattleMon_GetID(defendingMon),
                                                  Move_GetID(attackingMon, moveID), false, false);

        if (moveDamage == 0)
        {
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
            {
                return 1;
            }
            return 0;
        }
        if ((moveDamage * 2) <= defendingMon->CurrentHP)
        {
            return 0;
        }

        if ((moveDamage * 10) <= defendingMon->MaxHP)
        {
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
            {
                return 1;
            }
            return 0;
        }
        else if ((moveDamage * 5) <= defendingMon->MaxHP)
        {
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
            {
                if (RandomInRange(1, 100) >= 25)
                {
                    return 1;
                }
                return 0;
            }
            return 0;
        }
        else if ((moveDamage * 3) <= defendingMon->MaxHP)
        {
            if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
            {
                if (RandomInRange(1, 100) >= 40)
                {
                    return 1;
                }
                return 0;
            }
            return 0;
        }
        else
        {
            return 0;
        }

        // if (TypeEffectiveness == 0 || (!HasMoldBreaker(attackingMon) && CheckIfImmuneAbility(Type, moveID, defendingMon)))
        // {
        //     // Will always switch if there's another pokemon that can deal some damage
        //     if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 1))
        //     {
        //         return 1;
        //     }
        //     return 0;
        // }
        // // If the move is 4x resisted
        // else if (TypeEffectiveness == 1)
        // {
        //     // Will switch so long as there's anotehr pokemon that can deal better damage

        //     if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL110_TENACITY)
        //     {
        //         if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 4))
        //         {
        //             return 1;
        //         }
        //         if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 3))
        //         {
        //             if (RandomInRange(1, 100) >= 25)
        //             {
        //                 return 1;
        //             }
        //         }
        //         return 0;
        //     }
        //     if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 2))
        //     {
        //         return 1;
        //     }
        //     return 0;
        // }
        // // If the move is 2x resisted
        // else if (TypeEffectiveness == 2)
        // {
        //     // If the pokemon has tinted lens, it doesn't care about .5x resist
        //     if (BattleMon_GetValue(attackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL110_TENACITY)
        //     {
        //         return 0;
        //     }
        //     // If another pokemon in the party has a super effective move, guaranteed switch
        //     if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 4))
        //     {
        //         return 1;
        //     }
        //     // If the best another pokemon in the party has is a neutral move, 50% chance to switch
        //     if (CheckIfMonToSwitchToWithSEMove(work, defendingMon, 3))
        //     {
        //         if (RandomInRange(1, 100) >= 25)
        //         {
        //             return 1;
        //         }
        //     }
        // }
        // return 0;
    }

#pragma endregion

#pragma region AIScriptFunctions

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------------------- GUESS ABILITY --------------------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks to see what the Pokemon's ability is, and isn't fooled by anything.

    */

    int THUMB_BRANCH_SAFESTACK_GuessAbility(TrainerAIEnv *a1, int a2, int a3)
    {
        BattleMon *BattleMonFromBattlePos; // r6

        BattleMonFromBattlePos = GetBattleMonFromBattlePos(a1, a3);
        if (BattleMon_CheckIfMoveCondition(BattleMonFromBattlePos, CONDITION_GASTROACID))
        {
            return 0;
        }
        return BattleMon_GetValue(BattleMonFromBattlePos, VALUE_EFFECTIVE_ABILITY);
    }

    /*

        --------------------------------------------------------------------------------------------------
        --------------------------- CHECK MOVE CATEGORIES (FOR STATUS) -----------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks to see what a pokemon's primarily move category is. It first
            - checks the last move they used
            - if there is no last move, checks to see if all the moves they have are of the same category
            - if that's not true, then it checks what their current raw Attack vs Special Attack looks like

    */

    int CheckTargetMoves(BattleMon *a1)
    {
        int MoveCount;
        int LoopMoveID;
        int LoopMoveCategory;
        int LoopMoveCategoryCheck;
        int i;

        MoveCount = BattleMon_GetMoveCount(a1);
        LoopMoveCategoryCheck = 0;
        do
        {
            LoopMoveID = Move_GetID(a1, i);
            LoopMoveCategory = PML_MoveGetParam(LoopMoveID, MVDATA_CATEGORY);
            if (!LoopMoveCategoryCheck && !PML_MoveIsDamaging(LoopMoveID) && Move_GetPP(a1, i))
            {
                LoopMoveCategoryCheck = LoopMoveCategory;
            }

            if (LoopMoveCategory != LoopMoveCategoryCheck)
            {

                if (BattleMon_GetValue(a1, VALUE_ATTACK_STAT) >= BattleMon_GetValue(a1, VALUE_SPECIAL_ATTACK_STAT))
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
            i++;
        } while (i < MoveCount);
        return LoopMoveCategoryCheck;
    }

    int THUMB_BRANCH_AI094_GetPreviousMoveCategory(void *a1, TrainerAIEnv *a2)
    {
        int PreviousMoveID; // r1
        int LoopMoveID;
        int LoopMoveCategory;
        u32 LoopMoveCategoryCheck;

        k::Printf("\n\n--------\n\nWe are in the AI Function for checking the target's previous move category, which has been updated to check their general offensive bent.\n\n-----------\n\n");
        PreviousMoveID = BattleMon_GetPreviousMoveID(a2->defender);
        if (PreviousMoveID && !PML_MoveIsDamaging(PreviousMoveID))
        {
            a2->param = AIGetMoveParam(a2, PreviousMoveID, MVDATA_CATEGORY);
        }
        else
        {
            a2->param = CheckTargetMoves(a2->defender);
        }

        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------- CHECK FOR KILLING BLOWS (FOR SETUP) -----------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can kill them with any of their moves.
        If the target is faster than the user, and the setup move they're using doesn't boost speed past the
        target, then checks for even 50% damage.

    */

    int multiplySpeed(int moveID, int speed)
    {
        if (moveID == MOVE097_AGILITY || moveID == MOVE504_SHELL_SMASH || moveID == MOVE475_AUTOTOMIZE || moveID == MOVE397_ROCK_POLISH || moveID == MOVE366_TAILWIND || moveID == MOVE508_SHIFT_GEAR)
        {
            return speed * 2;
        }
        else if (moveID == MOVE289_VICTORY_DANCE || moveID == MOVE483_QUIVER_DANCE || moveID == MOVE349_DRAGON_DANCE || moveID == MOVE488_FLAME_CHARGE || moveID == MOVE104_DOUBLE_TEAM)
        {
            return speed * 1.5;
        }
        else
        {
            return speed;
        }
    }

    int THUMB_BRANCH_AI072_Nop(void *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        BattleMon *defender;
        u8 opposingPokePos[5];
        unsigned int k;

        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

        k::Printf("\n\n--------\n\nWe are in the AI Function for checking target's possible damage when using a set up move.\n\n-----------\n\n");
        for (k = 0; k < pokeCount; (k + 1))
        {
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(defender);
            int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
            k::Printf("\nCheck %d\n", k);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), false, false);

                // If the target is faster the the Pokemon using the set up move, doubles the damage
                // now checking for a 2HKO
                if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) > multiplySpeed(a2->moveID, Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1)))
                {
                    damage *= 2;
                }

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage))
                {
                    k = pokeCount;
                    break;
                }

                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------- CHECK FOR KILLING BLOWS (FOR PRIORITY) --------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can kill them with any of their moves.
        This is used to increase the score for priority moves if the user is slower than the target.

    */

    int THUMB_BRANCH_AI104_Nop(void *a1, TrainerAIEnv *a2)
    {

        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        BattleMon *defender;
        u8 opposingPokePos[5];
        unsigned int k;

        int moveId = a2->moveID;

        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
        k::Printf("\n\n--------\n\nWe are in the AI Function for checking target's possible damage when using a priority move.\n\n-----------\n\n");
        for (k = 0; k < pokeCount; (k + 1))
        {
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(defender);
            int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
            k::Printf("\nCheck %d\n", k);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), false, false);

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage))
                {
                    k = pokeCount;
                    break;
                }

                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------- CHECK ENEMY DAMAGE OUTPUT (FOR SETUP) ----------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can deal meaningful damage (33% of maximum health).
        This is used to potential increase the score for setup moves vs. enemies that cannot really hurt them.
    */

    int THUMB_BRANCH_AI060_Nop(void *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        unsigned int k;

        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

        k::Printf("\n\n--------\n\nWe are in the AI Function for checking target's possible damage when using a set up move for negligible damage.\n\n-----------\n\n");
        for (k = 0; k < pokeCount; (k + 1))
        {
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            int MoveCount = BattleMon_GetMoveCount(defender);
            // int currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
            int currentHp = DivideMaxHPZeroCheck(a2->attacker, 3u);
            k::Printf("\nCheck %d\n", k);
            do
            {
                int damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), false, false);

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage))
                {
                    k = pokeCount;
                    break;
                }

                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------- CHECK ENEMY DAMAGE OUTPUT (FOR DEBUFFS) --------------------------------
        --------------------------------------------------------------------------------------------------

        Checks to see if the target in front of them can deal meaningful damage.
        25% is the current arbitrary point set at which the AI will stop bothering with debuffing moves.
        Iterates through each move the target has and calcs against the user.
    */

    int THUMB_BRANCH_AI062_Nop(void *a1, TrainerAIEnv *a2)
    {
        int i = 0;
        int MoveCount = BattleMon_GetMoveCount(a2->defender);
        int currentHp = DivideMaxHPZeroCheck(a2->attacker, 4u);
        // BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
        k::Printf("\n\n--------\n\nWe are in the AI Function for checking user's possible damage when using debuff moves.\n\n-----------\n\n");
        do
        {
            k::Printf("\nCheck %d\n", i);
            int damage = Handler_SimulationDamage(a2->serverFlow,
                                                  BattleMon_GetID(a2->defender),
                                                  BattleMon_GetID(a2->attacker),
                                                  Move_GetID(a2->defender, i), false, false);

            // If currentHP is less than or equal to damage, performs the jump
            if (AIConditionalJump(a1, 6, currentHp, damage))
            {
                break;
            }

            // Else, incremenets and checks the next move.
            i++;
        } while (i < MoveCount);

        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ CHECK SLEEP TURNS -------------------------------------------
        --------------------------------------------------------------------------------------------------

        Checks to see if the number of remaining sleep turns is greater than one.
        Used for Sleep Talk, Snore, etc.
    */

    int THUMB_BRANCH_AI102_Nop(void *a1, TrainerAIEnv *a2)
    {
        BattleMon *attacker;
        attacker = a2->attacker;
        k::Printf("\n\n--------\n\nWe are in the AI Function for checking user's remaining sleep turns.\n\n-----------\n\n");
        if (BattleMon_CheckIfMoveCondition(attacker, CONDITION_SLEEP))
        {
            // checks that param 3 is less than param 4
            AIConditionalJump(a1, 0, attacker->MoveConditionCounter[CONDITION_SLEEP] + 1, Condition_GetTurnMax(&attacker->Conditions[CONDITION_SLEEP]));
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------- CHECK SPEED AGAINST MULTIPLES --------------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks the speed of every enemy pokemon on the field, rather than just the one in front of them.
    */

    int THUMB_BRANCH_AI103_Nop(void *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        unsigned int k;

        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
        k::Printf("\n\n--------\n\nWe are in the AI Function for checking user's speed against multiple enemies.\n\n-----------\n\n");
        for (k = 0; k < pokeCount; (k + 1))
        {
            k::Printf("\nCheck %d\n", k);
            int i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);

            if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
            {
                AIConditionalJump(a1, 0, 1, 2);
            }
        }
        return a2->result;
    }

#pragma endregion

#pragma region WIPIllusionChanges
    // struct	BattleParty SWAN_ALIGNED(4) {BattleMon *mons[6];u8 memberCount;u8 numCoverPos;char field_1A;char field_1B;};
    // extern int BattleMon_CanBattle(BattleMon *a1);
    // extern BattleStyle MainModule_GetBattleStyle(MainModule *a1);
    // extern int MainModule_GetNumBattlePositionsOfClient(MainModule *a1, int a2);
    // extern unsigned int BattleMon_IsIllusionEnabled(BattleMon *a1);
    // extern PartyPkm * BattleMon_GetViewSrcData(BattleMon *a1);
    // extern void BattleMon_SetIllusion(BattleMon *result, PartyPkm *a2);
    // extern void BattleMon_RemoveIllusion(BattleMon *result);
    // extern PartyPkm * BattleMon_GetSrcData(BattleMon *a1);
    // extern unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4, int flag);
    // extern int MainModule_BattlePosToClientID(MainModule *a1, int a2);
    // extern BattleMon* SwitchAI_DetermineOpponent(void *a1, __int16 a2);
    // extern unsigned int MainModule_GetClientPokePos(MainModule *a1, int clientID, int partyIndex);
    // extern BattleMon * PokeCon_GetBattleMon(void *a1, int a2);

    // The only difference with this function compared to the normal PersonalPickBestMonToSwitchInto is that
    // it does not have the variable BP calculation for illusion mons.  It also takes in a bool value on whether to ignore the illusion mon
    // unsigned int PersonalPickBestMonToSwitchInto(BtlClientWk *a1, u8 *a2, unsigned int a3, BattleMon *a4, int ignoreIllusionMon)
    // {
    //     unsigned int v5;                     // r5
    //     BattleMon *MonData;                  // r6
    //     int ID;                              // r4
    //     unsigned int BasePower;              // r4
    //     unsigned int TypeEffectivenessVsMon; // r0
    //     unsigned int v10;                    // r0
    //     unsigned int result;                 // r0
    //     unsigned int j;                      // r5
    //     unsigned int k;                      // r6
    //     unsigned int v14;                    // r1
    //     unsigned int v15;                    // r0
    //     unsigned int v18;
    //     int randomvalue;
    //     u8 v16;                 // r1
    //     int Type;               // [sp+8h] [bp-38h]
    //     unsigned int MoveCount; // [sp+Ch] [bp-34h]
    //     unsigned int i;         // [sp+10h] [bp-30h]
    //     int PokeType;           // [sp+14h] [bp-2Ch]
    //     __int16 v23[6];         // [sp+1Ch] [bp-24h]
    //     BattleMon *v24;         // [sp+28h] [bp-18h]

    //     v24 = a4;
    //     PokeType = BattleMon_GetPokeType(a4);
    //     randomvalue = BattleMon_GetHeldItem(a4);
    //     // k::Printf("\nStep 1\n");
    //     for (i = 0; i < a3; i = (i + 1))
    //     {
    //         v5 = 0;
    //         randomvalue = BattleMon_GetHeldItem(a4);
    //         v23[i] = 0;
    //         MonData = BattleParty_GetMonData(BattleClient_GetActParty(a1), a2[i]);
    //         randomvalue = BattleMon_GetHeldItem(a4);
    //         if (!(BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL149_ILLUSION && a2[i] == ignoreIllusionMon))
    //         {
    //             if (!BattleMon_IsFainted(MonData))
    //             {
    //                 randomvalue = BattleMon_GetHeldItem(a4);
    //                 MoveCount = BattleMon_GetMoveCount(MonData);
    //                 if (MoveCount)
    //                 {
    //                     randomvalue = BattleMon_GetHeldItem(a4);
    //                     do
    //                     {
    //                         randomvalue = BattleMon_GetHeldItem(a4);
    //                         if (Move_GetPP(MonData, v5))
    //                         {
    //                             randomvalue = BattleMon_GetHeldItem(a4);
    //                             ID = Move_GetID(MonData, v5);
    //                             randomvalue = BattleMon_GetHeldItem(a4);
    //                             if (PML_MoveIsDamaging(ID) && ID != MOVE120_SELF_DESTRUCT && ID != MOVE153_EXPLOSION)
    //                             {
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 Type = PML_MoveGetType(ID);
    //                                 BasePower = PML_MoveGetBasePower(ID);
    //                                 // k:Printf("\nBase Power from %d is %d\n", ID, BasePower);
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 // Weather Ball Checks
    //                                 if (ID == MOVE311_WEATHER_BALL)
    //                                 {
    //                                     v18 = BattleField_GetWeather();

    //                                     if (v18 != 0)
    //                                     {
    //                                         BasePower = 100;
    //                                     }
    //                                     if (v18 == 1)
    //                                     {
    //                                         Type = TYPE_FIRE;
    //                                     }
    //                                     else if (v18 == 2)
    //                                     {
    //                                         Type = TYPE_WATER;
    //                                     }
    //                                     else if (v18 == 3)
    //                                     {
    //                                         Type = TYPE_ICE;
    //                                     }
    //                                     else if (v18 == 4)
    //                                     {
    //                                         Type = TYPE_ROCK;
    //                                     }
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 if (ID == MOVE267_NATURE_POWER)
    //                                 {
    //                                     int BattleTerrain = Handler_GetBattleTerrain(BattleServer_GetServerFlow(a1->mainModule->server));

    //                                     // //k::printf("\n\nThe Battle Terrain is %d\n\n", BattleTerrain);

    //                                     if (BattleTerrain == 5u)
    //                                     {
    //                                         ID = 402;
    //                                     }
    //                                     else if (BattleTerrain == 11u)
    //                                     {
    //                                         ID = 89;
    //                                     }
    //                                     else if (BattleTerrain == 0xCu)
    //                                     {
    //                                         ID = 56;
    //                                     }
    //                                     else if (BattleTerrain == 7u)
    //                                     {
    //                                         ID = 59;
    //                                     }
    //                                     else if (BattleTerrain == 9u)
    //                                     {
    //                                         ID = 426;
    //                                     }
    //                                     else if (BattleTerrain == 0xAu)
    //                                     {
    //                                         ID = 157;
    //                                     }
    //                                     else if (BattleTerrain == 0xDu)
    //                                     {
    //                                         ID = 58;
    //                                     }
    //                                     else
    //                                     {
    //                                         ID = 161;
    //                                     }
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);

    //                                 if (ID == MOVE363_NATURAL_GIFT && PML_ItemIsBerry(BattleMon_GetHeldItem(MonData)))
    //                                 {
    //                                     Type = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_TYPE);
    //                                     BasePower = ItemGetParam(BattleMon_GetHeldItem(MonData), ITSTAT_NATURAL_GIFT_POWER);
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL012_GALVANIZE && Type == TYPE_NORMAL)
    //                                 {
    //                                     Type = TYPE_ELECTRIC;
    //                                     BasePower *= 1.2;
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL048_REFRIGERATE && Type == TYPE_NORMAL)
    //                                 {
    //                                     Type = TYPE_ICE;
    //                                     BasePower *= 1.2;
    //                                 }
    //                                 if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL060_AERILATE && Type == TYPE_NORMAL)
    //                                 {
    //                                     Type = TYPE_FLYING;
    //                                     BasePower *= 1.2;
    //                                 }
    //                                 if (BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL040_PIXILATE && Type == TYPE_NORMAL)
    //                                 {
    //                                     Type = TYPE_FAIRY;
    //                                     BasePower *= 1.2;
    //                                 }
    //                                 // //k::printf("\nBase Power from %d is %d, and the Type is %d\n", ID, BasePower, Type);

    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 // if (BasePower < 0xA)
    //                                 // {
    //                                 //     BasePower = 60;
    //                                 // }
    //                                 if (ID == MOVE327_SKY_UPPERCUT || ID == MOVE357_FREEZE_DRY || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL007_CORROSION)
    //                                 {
    //                                     TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAltered(Type, PokeType);
    //                                     // //k::printf("\n 2. TypeEffectivenessVsMon is: %d for Move %d \n", TypeEffectivenessVsMon, a4);
    //                                 }
    //                                 else if (ID == MOVE533_SACRED_SWORD)
    //                                 {
    //                                     TypeEffectivenessVsMon = GetTypeEffectivenessVsMonAlteredSacredSword(Type, PokeType);
    //                                 }
    //                                 else
    //                                 {
    //                                     TypeEffectivenessVsMon = GetTypeEffectivenessVsMon(Type, PokeType);
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);

    //                                 if (!(BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL104_MOLD_BREAKER || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL163_TURBOBLAZE || BattleMon_GetValue(MonData, VALUE_EFFECTIVE_ABILITY) == ABIL164_TERAVOLT) && CheckIfImmuneAbility(Type, ID, a4))
    //                                 {
    //                                     TypeEffectivenessVsMon = 0;
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 if (TypeEffectivenessVsMon <= 5)
    //                                 {
    //                                     randomvalue = BattleMon_GetHeldItem(a4);
    //                                     switch (TypeEffectivenessVsMon)
    //                                     {
    //                                     case 0:
    //                                         BasePower = 0;
    //                                         break;
    //                                     case 1:
    //                                         v10 = BasePower << 14;
    //                                         goto LABEL_11;
    //                                     case 2:
    //                                         v10 = BasePower << 15;
    //                                         goto LABEL_11;
    //                                     case 4:
    //                                         v10 = BasePower << 17;
    //                                         goto LABEL_11;
    //                                     case 5:
    //                                         v10 = BasePower << 18;
    //                                     LABEL_11:
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         k::Printf("\nStep 19\n");
    //                                         v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         v10 = checkForTechnician(MonData, ID, v10);
    //                                         // //k::printf("\n Base Power of %d after Tech changes is %d\n", ID, v10);
    //                                         v10 = checkForSTAB(MonData, Type, v10);
    //                                         v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);

    //                                         // //k::printf("\n Base Power of %d after STAB changes %d\n", ID, v10);
    //                                         BasePower = HIWORD(v10);
    //                                         // //k::printf("\n Base Power of %d after STAB and HIWORD changes %d\n", ID, BasePower);
    //                                         break;
    //                                     default:
    //                                         k::Printf("\nStep 19a\n");
    //                                         v10 = BasePower << 16;
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         // //k::printf("\n Base Power of %d before any changes is %d\n", ID, v10);
    //                                         v10 = checkForBPChanges(MonData, v24, ID, v10, a1);
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         // //k::printf("\n Base Power of %d after BP changes is %d\n", ID, v10);
    //                                         v10 = checkForTechnician(MonData, ID, v10);
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         // //k::printf("\n Base Power of %d after Tech changes is %d\n", ID, v10);
    //                                         v10 = checkForSTAB(MonData, Type, v10);
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         v10 = checkForAbilityAndItemBPChanges(MonData, v24, Type, TypeEffectivenessVsMon, v10);
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         // //k::printf("\n Base Power of %d after STAB changes %d\n", ID, v10);
    //                                         BasePower = HIWORD(v10);
    //                                         randomvalue = BattleMon_GetHeldItem(a4);
    //                                         // //k::printf("\n Base Power of %d after STAB and HIWORD changes %d\n", ID, BasePower);

    //                                         break;
    //                                     }
    //                                 }
    //                                 randomvalue = BattleMon_GetHeldItem(a4);
    //                                 if (v23[i] < BasePower)
    //                                 {
    //                                     // //k::printf("\n Base Power of %d is %d \n", ID, BasePower);
    //                                     v23[i] = BasePower;
    //                                 }
    //                             }
    //                         }
    //                         v5 = (v5 + 1);
    //                     } while (v5 < MoveCount);
    //                 }
    //             }
    //         }
    //     }
    //     // k::Printf("\nStep 21\n");
    //     result = a3;
    //     for (j = 0; j < a3; result = a3)
    //     {
    //         //  k::Printf("\nStep %d\n", 21 + j);
    //         for (k = (j + 1); k < a3; k = (k + 1))
    //         {
    //             v14 = v23[k];
    //             v15 = v23[j];
    //             if (v15 < v14)
    //             {
    //                 v23[j] = v14;
    //                 v23[k] = v15;
    //                 v16 = a2[j];
    //                 a2[j] = a2[k];
    //                 a2[k] = v16;
    //             }
    //         }
    //         j = (unsigned __int8)(j + 1);
    //     }

    //     // This is logic that is present in teh SwitchAI_Core with the output of this function, so I'm just nesting it in here
    //     // It checks to see if the pokemon is in reserve, returning the last value in the char array which is the highest value BP move
    //     int iterate = 0;
    //     while (SwitchAI_CheckReserve(a1, a2[iterate]))
    //     {
    //         if (++iterate >= a3)
    //         {
    //             return result;
    //         }
    //     }
    //     result = a2[iterate];
    //     return result;
    // }

    // void THUMB_BRANCH_MainModule_SetIllusionForParty(MainModule *a1, BattleParty *a2, int a3)
    // {
    //     int i;                          // r6
    //     int NumBattlePositionsOfClient; // r4
    //     int NumBattlePositionOfClient2;
    //     int illusionId;
    //     int clientId;
    //     unsigned int numOfMonsToCheckForSwitch;
    //     int j; // r0
    //     __int16 pokePos;
    //     BattleMon *v8; // r7
    //     BattleMon *opposingPokemon;
    //     PartyPkm *SrcData; // r0
    //     int v10;           // r4
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

    //                 clientId = MainModule_PokeIDToClientID(v8->ID);
    //                 numOfMonsToCheckForSwitch = GetNumBattleReadyPartyMons(a1->clients[clientId], validMonsInParty);

    //                 // finds the pokeposition of the pokemon
    //                 pokePos = MainModule_GetClientPokePos(a1, clientId, NumBattlePositionsOfClient);

    //                 // randomly picks an opposing pokemon (makes illusion even spookier in doubles)
    //                 opposingPokemon = SwitchAI_DetermineOpponent(a1->clients[clientId], pokePos);

    //                 // grabs the battleparty idx of the best switch in target
    //                 // this is a modified version of the PickBestMonToSwitchInto function, which normally has a random check for illusion pokemon to modify their BP.
    //                 illusionId = PersonalPickBestMonToSwitchInto(a1->clients[clientId], validMonsInParty, numOfMonsToCheckForSwitch, opposingPokemon, 10);

    //                 // checks to see if that is the illusion pokemon, if it isn't, continue.
    //                 if (illusionId == NumBattlePositionsOfClient)
    //                 {
    //                     // runs the modified PickBestMonToSwitchInto again with a flag that causes it to ignore the illusion pokemon's id, as if they are fainted.
    //                     // can never return nothing since, if there were no other pokemon to choose from, it would've been hit by the if statement earlier
    //                     // feeding in the specific id to ignore allows multiple illusion pokemon to function on the same team
    //                     illusionId = PersonalPickBestMonToSwitchInto(a1->clients[clientId], validMonsInParty, numOfMonsToCheckForSwitch, opposingPokemon, NumBattlePositionsOfClient);
    //                 }
    //                 SrcData = BattleMon_GetSrcData(a2->mons[illusionId]);
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
