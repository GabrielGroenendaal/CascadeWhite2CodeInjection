#include "codeinjection_new.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

// Uses esdb_newBattle.yml

extern "C"
{

#pragma region SpeedChecks

    /* Checks to see if we're in Skyla's Gym, multiplying the speed of flying types if so */
    int checkSkylaGym(ServerFlow *a1, int a2)
    {
        PlayerState *playerState;
        int zoneId;

        playerState = GameData_GetPlayerState(*(GameData **)(g_GameBeaconSys + 4));
        zoneId = PlayerState_GetZoneID(playerState);
        if (zoneId == 439 && Handler_CheckFloating(a1, a2))
        {
            // k::Printf("\nSkyla's Wind is Blowing\n");
            return 6144;
        }
        else
        {
            return 4096;
        }
    }

    /*

       --------------------------------------------------------------------------------------------------
       ------------------------------------ CALCULATE SPEED  -------------------------------------------
       --------------------------------------------------------------------------------------------------

   */

    int THUMB_BRANCH_SAFESTACK_ServerEvent_CalculateSpeed(ServerFlow *a1, BattleMon *a2, bool IsTrickRoomEnabled)
    {
        int Value;
        int ID;
        int v8;
        PlayerState *playerState;
        int zoneId;
        int v9;
        unsigned int v10;

        Value = BattleMon_GetValue(a2, VALUE_SPEED_STAT);
        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        int mulValue = checkSkylaGym(a1, ID);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetConstValue(VAR_SPEED, Value);
        BattleEventVar_SetValue(VAR_GENERAL_USE_FLAG, 1);
        BattleEventVar_SetValue(VAR_TRICK_ROOM_FLAG, 0);
        BattleEventVar_SetMulValue(VAR_RATIO, mulValue, 410, 0x20000);

        BattleEvent_CallHandlers(a1, EVENT_CALC_SPEED);
        v8 = BattleEventVar_GetValue(VAR_SPEED);
        v9 = BattleEventVar_GetValue(VAR_RATIO);
        v10 = fixed_round(v8, v9);

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

#pragma endregion

#pragma region Power

    /*

       --------------------------------------------------------------------------------------------------
       ------------------------------------ GET ATTACK POWER --------------------------------------------
       --------------------------------------------------------------------------------------------------

       Here's where we hard code the effects of Foul Play, Body Press.
   */

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
        if (a4->MoveID == MOVE206_BODY_PRESS)
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
        BattleEvent_CallHandlers(a1, EVENT_BEFORE_ATTACKER_POWER);
        Value = BattleEventVar_GetValue(VAR_SWAP_POKE_ID);

        if (Value != 31 || a4->MoveID == MOVE492_FOUL_PLAY)
        {
            AttackingMon = PokeCon_GetBattleMon(a1->pokeCon, Value);
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
        }

        // If we're using body press and it's hailing, we get a boostie.
        if (v8 == VALUE_DEFENSE_STAGE && BattleMon_HasType(AttackingMon, TYPE_ICE) && ServerEvent_GetWeather(a1) == 3)
        {
            RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        }
        if (v8 == VALUE_DEFENSE_STAGE && AttackingMon->HeldItem == IT0538_EVIOLITE && Handler_CheckEvolution(a1, ID))
        {
            RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        }
        if (v8 == VALUE_DEFENSE_STAGE && (AttackingMon->HeldItem == IT0225_MASCOT_BADGE || AttackingMon->HeldItem == IT0215_TERA_BADGE))
        {
            RealStat = (unsigned __int16)fixed_round(RealStat, 8192);
        }
        if (v8 == VALUE_DEFENSE_STAGE && BattleMon_GetValue(AttackingMon, VALUE_EFFECTIVE_ABILITY) == ABIL063_MARVEL_SCALE && BattleMon_GetStatus(AttackingMon))
        {
            RealStat = (unsigned __int16)fixed_round(RealStat, 6144);
        }

        v13 = RealStat;

        // if (!Handler_IsSimulationMode(a1))
        // {
        //     k::Printf("\n\nThe realstat for the move %d is %d\n\n", a4->MoveID, v13);
        // }

        BattleEventVar_SetConstValue(VAR_MOVE_ID, a4->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4->moveType);
        BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, a4->category);
        BattleEventVar_SetValue(VAR_POWER, v13);
        BattleEventVar_SetMulValue(VAR_RATIO, 4096, 410, 0x20000);
        BattleEvent_CallHandlers(a1, EVENT_ATTACKER_POWER);

        v14 = BattleEventVar_GetValue(VAR_POWER);
        v15 = BattleEventVar_GetValue(VAR_RATIO);
        v16 = fixed_round(v14, v15);

        BattleEventVar_Pop();
        return v16;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ GET TARGET DEFENSES -----------------------------------------
        --------------------------------------------------------------------------------------------------

    */

    int THUMB_BRANCH_SAFESTACK_ServerEvent_GetTargetDefenses(ServerFlow *a1, BattleMon *a2, BattleMon *a3, MoveParam *a4, int a5)
    {
        BattleMonValue v7;         // r4
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

        v7 = VALUE_SPECIAL_DEFENSE_STAT;
        if (PML_MoveGetCategory(a4->MoveID) != 2)
        {
            v7 = VALUE_DEFENSE_STAT;
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
        BattleEvent_CallHandlers(a1, EVENT_BEFORE_DEFENDER_GUARD);

        /* Psyshock Check */
        if ((BattleEventVar_GetValue(VAR_BATTLE_MON_STAT_SWAP_FLAG) & 1) != 0 || a4->MoveID == 473 || a4->MoveID == 540)
        {
            if (v7 == VALUE_DEFENSE_STAT)
            {
                v7 = VALUE_SPECIAL_DEFENSE_STAT;
            }
            else
            {
                v7 = VALUE_DEFENSE_STAT;
            }
            if (v7 == VALUE_DEFENSE_STAT)
            {
                v10 = 1;
            }
            else
            {
                v10 = 2;
            }
            category = v10;
        }
        Value = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);

        BattleEventVar_Pop();
        if (Value)
        {
            RealStat = BattleMon_GetRealStat(a3, v7);
        }
        else if (a5)
        {
            RealStat = BattleMon_GetStatsForCritDamage(a3, v7);
        }
        else
        {
            RealStat = BattleMon_GetValue(a3, v7);
        }
        v13 = RealStat;

        /* Sand Boost for Rock Types*/
        if (ServerEvent_GetWeather(a1) == 4 && BattleMon_HasType(a3, TYPE_ROCK) && v7 == VALUE_SPECIAL_DEFENSE_STAT)
        {
            v13 = fixed_round(v13, 6144);
        }
        /* Defense Boost for Ice Types */
        if (ServerEvent_GetWeather(a1) == 3 && BattleMon_HasType(a3, TYPE_ICE) && v7 == VALUE_DEFENSE_STAT)
        {
            v13 = fixed_round(v13, 6144);
        }

        BattleEventVar_Push();
        v14 = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v14);
        v15 = BattleMon_GetID(a3);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v15);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a4->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a4->moveType);
        BattleEventVar_SetConstValue(VAR_MOVE_CATEGORY, category);
        BattleEventVar_SetValue(VAR_GUARD, v13);
        BattleEventVar_SetMulValue(VAR_RATIO, 4096, 410, 0x20000);
        BattleEvent_CallHandlers(a1, EVENT_DEFENDER_GUARD);
        v16 = BattleEventVar_GetValue(VAR_GUARD);
        v17 = BattleEventVar_GetValue(VAR_RATIO);
        BattleEventVar_Pop();

        return fixed_round(v16, v17);
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ GET TYPE EFFECTIVENSS ---------------------------------------
        --------------------------------------------------------------------------------------------------

        Checks for altered type effectiveness based on zone.

    */
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
        zoneId = PlayerState_GetZoneID(playerState);

        /* Chargestone Cave*/
        if (zoneId == 607 || zoneId == 195 || zoneId == 196 || zoneId == 197)
        {
            v3 = chargestoneTypeChart[a1][a2];
        }
        /* Celestial Tower*/
        else if (zoneId == 339 || zoneId == 338 || zoneId == 340 || zoneId == 341 || zoneId == 462 || (zoneId >= 510 && zoneId <= 514) || (zoneId >= 569 && zoneId <= 572))
        {
            v3 = celestialTypeChart[a1][a2];
        }
        /* Opelucid Gym */
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

#pragma endregion

}