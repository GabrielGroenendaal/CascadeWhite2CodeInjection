#include "swan-master/codeinjection.h"
#include "NitoKernel/include/kPrint.h"

extern "C"
{
    extern char *ServerDisplay_AddCommon(ServerCommandQueue *a1, int a2, ...);

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

        char *bhwork;
        v10 = (HandlerParam_AddSideEffect *)BattleHandler_PushWork(a2, EFFECT_ADDSIDEEFFECT, (int)a3);
        v10->effect = a6;
        v10->side = a5;
        v10->cont = (ConditionData)a7;

        // k::Printf("%d", v10);

        bhwork = (char *)v10;
        BattleHandler_StrSetup((u16 *)&v10->exStr, 1u, a8);
        BattleHandler_AddArg((u16 *)&v10->exStr, a5);
        BattleHandler_PopWork(a2, (u32 *)bhwork);
    };

    int HandleFieldEffects(ServerFlow *a1)
    {
        char *bhwork;
        BattleFieldStatus *FieldStatus; // r0
        TrainerBattleSetup **trainerSetups;
        TrainerBattleSetup *currentTrainer;
        PlayerState *playerState;
        int zoneId;
        int trainerId;
        int trainerClass;

        FieldStatus = BtlSetup_GetFieldStatus(a1->mainModule);
        // zoneId = (int)FieldStatus->ZoneID;
        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = playerState->ZoneID;

        if (a1->mainModule->btlSetup->BtlType != 0)
        {
            trainerSetups = a1->mainModule->btlSetup->TrainerSetup;
            currentTrainer = trainerSetups[2];
            trainerId = currentTrainer->TrID;
            trainerClass = currentTrainer->TrClass;
        }

        // Trick Room Setter
        // Checks ZoneId for Relic Castle, currently
        if (zoneId == 503 || zoneId == 504 || zoneId == 505 || (zoneId >= 255 && zoneId <= 262) || (zoneId >= 160 && zoneId <= 190))
        {
            ServerDisplay_AddCommon(a1->serverCommandQueue, 48, 1, 0, 433, 0, 0);
            bhwork = BattleHandler_PushWork(a1, 4, 0);
            BattleHandler_StrSetup((u16 *)bhwork + 2, 1u, 203);
            BattleHandler_PopWork(a1, (u32 *)bhwork);
            ServerControl_FieldEffectCore(a1, 1, 255, 0);
        }

        // Chargestone Cave
        if (zoneId == 607 || zoneId == 195 || zoneId == 196 || zoneId == 197)
        {
            bhwork = BattleHandler_PushWork(a1, 4, 0);
            BattleHandler_StrSetup((u16 *)bhwork + 2, 1u, 204);
            BattleHandler_PopWork(a1, (u32 *)bhwork);
        }
        // Celestial Tower
        else if (zoneId == 339 || zoneId == 338 || zoneId == 340 || zoneId == 341 || zoneId == 462 || (zoneId >= 510 && zoneId <= 514) || (zoneId >= 569 && zoneId <= 572))
        {
            bhwork = BattleHandler_PushWork(a1, 4, 0);
            BattleHandler_StrSetup((u16 *)bhwork + 2, 1u, 205);
            BattleHandler_PopWork(a1, (u32 *)bhwork);
        }
        // Opelucid Gym
        else if (zoneId == 121)
        {
            bhwork = BattleHandler_PushWork(a1, 4, 0);
            BattleHandler_StrSetup((u16 *)bhwork + 2, 1u, 206);
            BattleHandler_PopWork(a1, (u32 *)bhwork);
        }

        // Skyla' Gym
        else if (zoneId == 108)
        {
            bhwork = BattleHandler_PushWork(a1, 4, 0);
            BattleHandler_StrSetup((u16 *)bhwork + 2, 1u, 207);
            BattleHandler_PopWork(a1, (u32 *)bhwork);
        }

        // PreSet Spikes
        // Checks TrainerId
        if (a1->mainModule->btlSetup->BtlType != 0)
        {
            if (trainerClass == 192)
            {
                ConditionData Permanent = Condition_MakePermanent();
                CreateSpikes(0, a1, 0, 0, 0, 6, Permanent, 148);
            }
        }
    
    // if (trainerClass && trainerClass == 192)
    // {
    //     ConditionData Permanent = Condition_MakePermanent();
    //     CreateSpikes(0, a1, 0, 0, 0, 6, Permanent, 148);
    // }

    // Overworld Weather Setter
    if (zoneId == 537 || zoneId == 538 || zoneId == 539 || zoneId == 540 || zoneId == 541 || zoneId == 542 || zoneId == 461 || zoneId == 376 || zoneId == 589)
    {
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

    ServerCommandQueue *ServerCommandQueue; // r1
    BattleFieldStatus *FieldStatus;         // r0
    SVCL_WORK *ClientWork;                  // r0
    SVCL_WORK *v5;                          // r4
    unsigned int v6;                        // r5
    BattleMon *PartyMember;                 // r0
    unsigned int j;                         // r5
    BattleMon *v9;                          // r0
    int v10;                                // r7
    int v12;                                // [sp+0h] [bp-20h]
    unsigned int i;                         // [sp+4h] [bp-1Ch]

    ServerCommandQueue = a1->serverCommandQueue;
    ServerCommandQueue->writePTR = 0;
    v12 = 0;
    ServerCommandQueue->readPTR = 0;
    v12 = HandleFieldEffects(a1);

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

int checkSkylaGym(BattleMon *a1)
{
    PlayerState *playerState;
    int zoneId;

    playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
    zoneId = playerState->ZoneID;
    if (zoneId == 108 && BattleMon_HasType(a1, TYPE_FLYING))
    {
        return 6144;
    }
    else
    {
        return 4096;
    }
}

int THUMB_BRANCH_ServerEvent_CalculateSpeed(ServerFlow *a1, BattleMon *a2, bool IsTrickRoomEnabled)
{
    int Value;
    int ID;
    int v8;
    PlayerState *playerState;
    int zoneId;
    int v9;
    unsigned int v10;

    int mulValue = checkSkylaGym(a2);

    Value = BattleMon_GetValue(a2, VALUE_SPEED_STAT);
    BattleEventVar_Push();
    ID = BattleMon_GetID(a2);
    BattleEventVar_SetConstValue(VAR_MON_ID, ID);
    BattleEventVar_SetConstValue(VAR_SPEED, Value);
    BattleEventVar_SetValue(VAR_GENERAL_USE_FLAG, 1);
    BattleEventVar_SetValue(VAR_TRICK_ROOM_FLAG, 0);
    BattleEventVar_SetMulValue(VAR_RATIO, mulValue, 410, 0x20000);

    BattleEvent_CallHandlers(a1, BattleEvent_CalcSpeed);
    v8 = BattleEventVar_GetValue(VAR_SPEED);
    v9 = BattleEventVar_GetValue(VAR_RATIO);
    v10 = fixed_round(v8, v9);

    //     playerState = GameData_GetPlayerState(*(GameData**)(g_GameBeaconSys+4));
    //     zoneId = playerState->ZoneID;
    //    if (zoneId == 96 && BattleMon_HasType(a2, TYPE_FLYING)){
    //         v10 = 150 * v10 / 100;
    //     }

    // v10 = checkSkylaGym(a1, a2, v10);

    if (BattleMon_CheckIfMoveCondition(a2, CONDITION_PARALYSIS) && BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG))
    {
        v10 = fixed_round(v8, 1024);
    }

    if (v10 > 10000)
    {
        LOWORD(v10) = 10000;
    }

    if (IsTrickRoomEnabled && BattleEventVar_GetValue(VAR_TRICK_ROOM_FLAG))
    {

        LOWORD(v10) = 10000 - v10;
    }

    BattleEventVar_Pop();
    return v10;
}

int THUMB_BRANCH_SAFESTACK_ServerEvent_GetAttackPower(
    ServerFlow *a1,
    BattleMon *AttackingMon,
    BattleMon *DefendingMon,
    MoveParam *a4,
    int criticalFlag)
{
    BattleMonValue v8;         // r4
    int ID;                    // r0
    int v10;                   // r0
    int Value;                 // r1
    unsigned __int16 RealStat; // r0
    int v13;                   // r4
    int v14;                   // r4
    int v15;                   // r0
    int v16;                   // r4

    v8 = VALUE_SPECIAL_ATTACK_STAT;
    if (PML_MoveGetCategory(a4->MoveID) != 2)
    {
        v8 = VALUE_ATTACK_STAT;
    }
    if (a4->MoveID == 206)
    {
        v8 = VALUE_DEFENSE_STAT;
    }

    BattleEventVar_Push();
    ID = BattleMon_GetID(AttackingMon);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
    v10 = BattleMon_GetID(DefendingMon);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v10);
    BattleEventVar_SetValue(VAR_SWAP_POKE_ID, 31);

    BattleEventVar_SetValue(VAR_GENERAL_USE_FLAG, 0);
    BattleEvent_CallHandlers(a1, BattleEvent_BeforeAttackerPower);
    Value = BattleEventVar_GetValue(VAR_SWAP_POKE_ID);

    if (Value != 31 || a4->MoveID == 492)
    {
        AttackingMon = PokeCon_GetPokeParam(a1->pokeCon, Value);
    }
    if (BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG) != 0)
    {
        RealStat = BattleMon_GetRealStat(AttackingMon, v8);
    }
    else if (criticalFlag)
    {

        RealStat = BattleMon_GetStatsForCritDamage(AttackingMon, v8);
    }
    else
    {

        RealStat = BattleMon_GetValue(AttackingMon, v8);

        if (v8 == VALUE_DEFENSE_STAGE && BattleMon_HasType(AttackingMon, TYPE_ICE) && ServerEvent_GetWeather(a1) == 3)
        {
            RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        }
    }
    v13 = RealStat;

    BattleEventVar_SetConstValue(VAR_MOVEID, a4->MoveID);
    BattleEventVar_SetConstValue(VAR_MOVETYPE, a4->moveType);
    BattleEventVar_SetConstValue(VAR_MOVECATEGORY, a4->category);
    BattleEventVar_SetValue(VAR_POWER, v13);
    BattleEventVar_SetMulValue(VAR_RATIO, 4096, 410, 0x20000);
    BattleEvent_CallHandlers(a1, BattleEvent_AttackerPower);

    v14 = BattleEventVar_GetValue(VAR_POWER);
    v15 = BattleEventVar_GetValue(VAR_RATIO);
    v16 = fixed_round(v14, v15);

    BattleEventVar_Pop();
    return v16;
}

int THUMB_BRANCH_SAFESTACK_ServerEvent_GetTargetDefenses(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4, int *a5)
{
    int v7;                    // r4
    int ID;                    // r0
    int v9;                    // r0
    int v10;                   // r0
    int Value;                 // r7
    unsigned __int16 RealStat; // r0
    int v13;                   // r7
    int v14;                   // r0
    int v15;                   // r0
    int v16;                   // r5
    int v17;                   // r6
    int category;              // [sp+8h] [bp-18h]
    BattleEventVar checkVar;

    v7 = 11;
    if (PML_MoveGetCategory(a4->MoveID) != 2)
    {
        v7 = 9;
    }
    category = a4->category;
    BattleEventVar_Push();
    ID = BattleMon_GetID(a2);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, ID);
    v9 = BattleMon_GetID(a3);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v9);
    BattleEventVar_SetConstValue(VAR_BATTLE_MON_STAT, v7);
    BattleEventVar_SetValue(VAR_BATTLE_MON_STAT_SWAP_FLAG, 0);
    BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);
    BattleEvent_CallHandlers(a1, BattleEvent_BeforeDefenderGuard);
    if ((BattleEventVar_GetValue(VAR_BATTLE_MON_STAT_SWAP_FLAG) & 1) != 0 || a4->MoveID == 473 || a4->MoveID == 540)
    {
        if (v7 == 9)
        {
            v7 = 11;
        }
        else
        {
            v7 = 9;
        }
        if (v7 == 9)
        {
            v10 = 1;
        }
        else
        {
            v10 = 2;
        }
        category = v10;
    }
    Value = (unsigned __int8)BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);
    BattleEventVar_Pop();
    if (Value)
    {
        RealStat = BattleMon_GetRealStat(a3, (BattleMonValue)v7);
    }
    else if ((int)a5)
    {
        RealStat = BattleMon_GetStatsForCritDamage(a3, v7);
    }
    else
    {
        RealStat = BattleMon_GetValue(a3, (BattleMonValue)v7);
    }
    v13 = RealStat;
    if (ServerEvent_GetWeather(a1) == 4 && BattleMon_HasType(a3, TYPE_ROCK) && v7 == 11)
    {
        v13 = (unsigned __int16)fixed_round(v13, 6144);
    }
    if (ServerEvent_GetWeather(a1) == 3 && BattleMon_HasType(a3, TYPE_ICE) && v7 == 9)
    {
        v13 = (unsigned __int16)fixed_round(v13, 6144);
    }

    BattleEventVar_Push();
    v14 = BattleMon_GetID(a2);
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v14);
    v15 = BattleMon_GetID(a3);
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v15);
    BattleEventVar_SetConstValue(VAR_MOVEID, a4->MoveID);
    BattleEventVar_SetConstValue(VAR_MOVETYPE, a4->moveType);
    BattleEventVar_SetConstValue(VAR_MOVECATEGORY, category);
    BattleEventVar_SetValue((BattleEventVar)(VAR_MOVEPOWER | VAR_DEFENDING_MON), v13);
    BattleEventVar_SetMulValue(VAR_RATIO, 4096, 410, 0x20000);
    BattleEvent_CallHandlers(a1, BattleEvent_DefenderGuard);
    v16 = (unsigned __int16)BattleEventVar_GetValue((BattleEventVar)(VAR_MOVEPOWER | VAR_DEFENDING_MON));
    v17 = BattleEventVar_GetValue(VAR_RATIO);
    BattleEventVar_Pop();

    return (unsigned __int16)fixed_round(v16, v17);
}

TypeEffectiveness THUMB_BRANCH_GetTypeEffectiveness(int a1, int a2)
{
    TypeEffectiveness result;
    PlayerState *playerState;
    int typeChart[18][18];
    int zoneId;
    unsigned int v3;

    if (a1 == 18 || a2 == 18)
    {
        result = EFFECTIVENESS_1;
        return result;
    }

    playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
    zoneId = playerState->ZoneID;

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
}