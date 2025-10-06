
#include "codeinjection_battlefield.h"
#include "kPrint.h"

// FIELD EFFECT EXPANSION

// Uses esdb_newBattle.yml

// extern "C" int THUMB_BRANCH_TrainerInfo_GetRegion(UnityTowerVisitor *a1)
// {
//   return a1->field_1A;
// };

extern "C"
{

    struct BattleFieldExt
    {
        int terrain;
        int terrainTurns;
        void *battleEventItems[8];
        ConditionData conditionData[8];
        u32 turnCount[8];
        u32 DependPokeID[8][6];
        u32 DependPokeCount[8];
        u32 effectEnableFlags[8];
    };

    BattleFieldExt battleFieldExt;
#define BATTLEFIELD_EXT (BattleField *)&battleFieldExt

    int BattleField_GetTerrain()
    {
        return battleFieldExt.terrain;
    }

    void BattleField_SetTerrain(int terrain, int turns)
    {
        battleFieldExt.terrain = terrain;
        battleFieldExt.terrainTurns = turns;
    }
    void BattleField_EndTerrain()
    {
        battleFieldExt.terrain = 0;
        battleFieldExt.terrainTurns = 0;
    }
    int BattleField_GetTerrainTurns()
    {
        return battleFieldExt.terrainTurns;
    }

    int TerrainPowerMod(ServerFlow *serverFlow, BattleMon *attackingMon, BattleMon *defendingMon, int terrain, int type)
    {
        switch (terrain)
        {
        case TERRAIN_ELECTRIC:
            if (!ServerControl_CheckFloating(serverFlow, attackingMon, 1))
                if (type == TYPE_ELECTRIC)
                    return 5325;
            break;
        case TERRAIN_GRASSY:
            if (!ServerControl_CheckFloating(serverFlow, attackingMon, 1))
                if (type == TYPE_GRASS)
                    return 5325;
            break;
        case TERRAIN_MISTY:
            if (!ServerControl_CheckFloating(serverFlow, defendingMon, 1)) // check the defender
                if (type == TYPE_DRAGON)
                    return 2048;
            break;
        case TERRAIN_PSYCHIC:
            if (!ServerControl_CheckFloating(serverFlow, attackingMon, 1))
                if (type == TYPE_PSYCHIC)
                    return 5325;
            break;
        }
        return 4096;
    }

    int ServerEvent_IncreaseMoveTerrainTurns(ServerFlow *serverFlow, int terrain, int attackingSlot)
    {
        BattleEventVar_Push();
        SET_UP_NEW_EVENT;
        BattleEventVar_SetConstValue(VAR_WEATHER, terrain);
        BattleEventVar_SetConstValue(NEW_VAR_ATTACKING_MON, attackingSlot);
        BattleEventVar_SetValue(VAR_EFFECT_TURN_COUNT, 0);
        BattleEvent_CallHandlers(serverFlow, EVENT_MOVE_TERRAIN_TURN_COUNT);
        int turnCount = BattleEventVar_GetValue(VAR_EFFECT_TURN_COUNT);
        BattleEventVar_Pop();
        return turnCount;
    }

    int ServerEvent_ChangeTerrain(ServerFlow *serverFlow, int terrain)
    {
        bool failFlag = 0;

        PokeSet *pokeSet = &serverFlow->switching_in_mons;
        j_PokeSet_SeekStart(pokeSet);
        for (BattleMon *currentMon = j_PokeSet_SeekNext(pokeSet); currentMon; currentMon = j_PokeSet_SeekNext(pokeSet))
        {
            int v4 = HEManager_PushState(&serverFlow->heManager);

            if (!BattleMon_IsFainted(currentMon))
            {
                BattleEventVar_Push();
                SET_UP_NEW_EVENT;
                int currentSlot = BattleMon_GetID(currentMon);
                BattleEventVar_SetConstValue(NEW_VAR_MON_ID, currentSlot);
                BattleEventVar_SetConstValue(VAR_WEATHER, terrain);
                BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
                BattleEvent_CallHandlers(serverFlow, EVENT_TERRAIN_CHANGE);
                failFlag = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
                if (failFlag)
                {
                    BattleEvent_CallHandlers(serverFlow, EVENT_TERRAIN_CHANGE_FAIL);
                }
                BattleEventVar_Pop();
            }

            HEManager_PopState(&serverFlow->heManager, v4);
        }

        return !failFlag;
    }
    void ServerEvent_ChangeTerrainAfter(ServerFlow *serverFlow, int terrain)
    {
        PokeSet *pokeSet = &serverFlow->switching_in_mons;
        j_PokeSet_SeekStart(pokeSet);
        for (BattleMon *currentMon = j_PokeSet_SeekNext(pokeSet); currentMon; currentMon = j_PokeSet_SeekNext(pokeSet))
        {
            int v4 = HEManager_PushState(&serverFlow->heManager);

            if (!BattleMon_IsFainted(currentMon))
            {
                BattleEventVar_Push();
                SET_UP_NEW_EVENT;
                int currentSlot = BattleMon_GetID(currentMon);
                BattleEventVar_SetConstValue(NEW_VAR_MON_ID, currentSlot);
                BattleEventVar_SetConstValue(VAR_WEATHER, terrain);
                BattleEvent_CallHandlers(serverFlow, EVENT_AFTER_TERRAIN_CHANGE);
                BattleEventVar_Pop();
            }

            HEManager_PopState(&serverFlow->heManager, v4);
        }
    }
    int ServerEvent_GetTerrain(ServerFlow *serverFlow)
    {
        BattleEventVar_Push();
        SET_UP_NEW_EVENT;
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEvent_CallHandlers(serverFlow, EVENT_TERRAIN_CHECK);
        int failFlag = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
        BattleEventVar_Pop();
        if (failFlag)
            return 0;
        return BattleField_GetTerrain();
    }
    void ServerEvent_GroundedByGravity(ServerFlow *serverFlow, BattleMon *battleMon)
    {
        BattleEventVar_Push();
        SET_UP_NEW_EVENT;
        int pokemonSlot = BattleMon_GetID(battleMon);
        BattleEventVar_SetConstValue(NEW_VAR_MON_ID, pokemonSlot);
        BattleEvent_CallHandlers(serverFlow, EVENT_GROUNDED_BY_GRAVITY);
        BattleEventVar_Pop();
    }

    bool ServerControl_ChangeTerrainCheck(ServerFlow *serverFlow, int terrain, int turns)
    {
        if (terrain > TERRAIN_PSYCHIC)
            return 0;

        return terrain != BattleField_GetTerrain() || turns == 255 && BattleField_GetTerrainTurns() != 255;
    }
    int ServerControl_ChangeTerrain(ServerFlow *serverFlow, int terrain, int turns)
    {
        if (!ServerControl_ChangeTerrainCheck(serverFlow, terrain, turns))
            return 0;

        if (!ServerEvent_ChangeTerrain(serverFlow, terrain))
            return 0;

        BattleField_SetTerrain(terrain, turns);
        return 1;
    }

    // typedef struct
    // {
    //     BattleEventType triggerValue;
    //     FIELD_HANDLER_FUNC function;
    // } FIELD_TRIGGERTABLE;

    // FIELD_TRIGGERTABLE FieldWeatherHandlers[] = {
    //     {EVENT_MOVE_DAMAGE_PROCESSING_2, (FIELD_HANDLER_FUNC)HandlerFieldWeather}};

    // FIELD_TRIGGERTABLE FieldTrickRoomHandlers[] = {
    //     {EVENT_CALC_SPEED, (FIELD_HANDLER_FUNC)HandlerFieldTrickRoom}};

    // FIELD_TRIGGERTABLE FieldGravityHandlers[] = {
    //     {EVENT_MOVE_ACCURACY, (FIELD_HANDLER_FUNC)HandlerFieldGravityAccuracy},
    //     {EVENT_CHECK_TYPE_EFFECTIVENESS, (FIELD_HANDLER_FUNC)HandlerFieldGravityGrounded}};

    // FIELD_TRIGGERTABLE FieldImprisonHandlers[] = {
    //     {EVENT_NULL, (FIELD_HANDLER_FUNC)HandlerFieldMagicRoom}};

    // FIELD_TRIGGERTABLE FieldWaterSportHandlers[] = {
    //     {EVENT_MOVE_POWER, (FIELD_HANDLER_FUNC)HandlerFieldWaterSport}};

    // FIELD_TRIGGERTABLE FieldMudSportHandlers[] = {
    //     {EVENT_MOVE_POWER, (FIELD_HANDLER_FUNC)HandlerFieldMudSport}};

    // FIELD_TRIGGERTABLE FieldWonderRoomHandlers[] = {
    //     {EVENT_BEFORE_DEFENDER_GUARD, (FIELD_HANDLER_FUNC)HandlerFieldWonderRoom}};

    // FIELD_TRIGGERTABLE FieldMagicRoomHandlers[] = {
    //     {EVENT_NULL, (FIELD_HANDLER_FUNC)HandlerFieldMagicRoom}};

    // FIELD_TRIGGERTABLE *EventAddFieldWeather(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldWeatherHandlers;
    // }

    // FIELD_TRIGGERTABLE *EventAddFieldTrickRoom(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldTrickRoomHandlers;
    // }

    // FIELD_TRIGGERTABLE *EventAddFieldGravity(int *a1)
    // {
    //     *a1 = 2;
    //     return FieldGravityHandlers;
    // }
    // FIELD_TRIGGERTABLE *EventAddFieldImprison(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldImprisonHandlers;
    // }
    // FIELD_TRIGGERTABLE *EventAddFieldWaterSport(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldWaterSportHandlers;
    // }
    // FIELD_TRIGGERTABLE *EventAddFieldMudSport(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldMudSportHandlers;
    // }
    // FIELD_TRIGGERTABLE *EventAddFieldWonderRoom(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldWonderRoomHandlers;
    // }
    // FIELD_TRIGGERTABLE *EventAddFieldMagicRoom(int *a1)
    // {
    //     *a1 = 1;
    //     return FieldMagicRoomHandlers;
    // }

    BattleEventHandlerTableEntry *EventAddFieldWeather(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D7C0;
    }
    BattleEventHandlerTableEntry *EventAddFieldTrickRoom(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D7B8;
    }
    BattleEventHandlerTableEntry *EventAddFieldGravity(int *a1)
    {
        *a1 = 2;
        return (BattleEventHandlerTableEntry *)0x0689D7C8;
    }
    BattleEventHandlerTableEntry *EventAddFieldImprison(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D7A0;
    }
    BattleEventHandlerTableEntry *EventAddFieldWaterSport(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D7A8;
    }
    BattleEventHandlerTableEntry *EventAddFieldMudSport(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D798;
    }
    BattleEventHandlerTableEntry *EventAddFieldWonderRoom(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D7B0;
    }
    BattleEventHandlerTableEntry *EventAddFieldMagicRoom(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x0689D790;
    }

    // GENERAL TERRAIN
    void HandlerTerrainPreventStatus(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        int terrain = BattleField_GetTerrain();
        if (terrain != TERRAIN_ELECTRIC && terrain != TERRAIN_MISTY)
            return;

        BattleMon *currentMon = Handler_GetBattleMon(serverFlow, BattleEventVar_GetValue(VAR_DEFENDING_MON));
        if (!ServerControl_CheckFloating(serverFlow, currentMon, 1))
        {
            if (terrain == TERRAIN_ELECTRIC)
            {
                if (BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_SLEEP ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_DROWSY)
                {
                    *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                }
            }
            else // MISTY TERRAIN
            {
                if (BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_PARALYSIS ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_SLEEP ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_FREEZE ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_BURN ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_POISON ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_CONFUSION ||
                    BattleEventVar_GetValue(VAR_CONDITION_ID) == CONDITION_DROWSY)
                {
                    *work = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                }
            }
        }
    }

    void HandlerTerrainStatusFailMessage(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        int terrain = BattleField_GetTerrain();
        if (terrain != TERRAIN_ELECTRIC && terrain != TERRAIN_MISTY)
            return;

        if (*work)
        {
            short msgID = BATTLE_ELECTRIC_TERRAIN_STATUS_MSGID;
            if (terrain == TERRAIN_MISTY)
                msgID = BATTLE_MISTY_TERRAIN_STATUS_MSGID;

            int defendingSlot = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            HandlerParam_Message *v6 = (HandlerParam_Message *)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, 31);
            BattleHandler_StrSetup(&v6->str, 2u, msgID);
            BattleHandler_AddArg(&v6->str, defendingSlot);
            BattleHandler_PopWork(serverFlow, v6);
        }
    }
    // ELECTRIC TERRAIN
    void CommonElectricTerrainCureStatus(ServerFlow *serverFlow, int pokemonSlot)
    {
        HandlerParam_CureCondition *v7;

        BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
        if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_SLEEP))
        {
            if (!ServerControl_CheckFloating(serverFlow, currentMon, 1))
            {
                v7 = (HandlerParam_CureCondition *)BattleHandler_PushWork(serverFlow, EFFECT_CURE_STATUS, pokemonSlot);
                v7->sickCode = CONDITION_SLEEP;
                v7->poke_cnt = 1;
                v7->pokeID[0] = pokemonSlot;
                // k::Printf("TERRAIN CURE\n");
                BattleHandler_PopWork(serverFlow, v7);
            }
        }
    }
    void HandlerElectricTerrainCheckSleep(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        // k::Printf("HandlerElectricTerrainEndSleep\n");
        if (BattleField_GetTerrain() != TERRAIN_ELECTRIC)
            return;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            if (!ServerControl_CheckFloating(serverFlow, currentMon, 1))
            {
                BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
    }
    void HandlerElectricTerrainTerrainChange(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (IS_NOT_NEW_EVENT)
            return;

        if (BattleField_GetTerrain() != TERRAIN_ELECTRIC)
            return;

        CommonElectricTerrainCureStatus(serverFlow, BattleEventVar_GetValue(NEW_VAR_MON_ID));
    }
    void HandlerElectricTerrainSwitchIn(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (BattleField_GetTerrain() != TERRAIN_ELECTRIC)
            return;

        CommonElectricTerrainCureStatus(serverFlow, BattleEventVar_GetValue(VAR_MON_ID));
    }
    void HandlerElectricTerrainActProcEnd(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (BattleField_GetTerrain() != TERRAIN_ELECTRIC)
            return;

        CommonElectricTerrainCureStatus(serverFlow, BattleEventVar_GetValue(VAR_MON_ID));
    }
    void HandlerElectricTerrainFloatingChange(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (BattleField_GetTerrain() != TERRAIN_ELECTRIC)
            return;

        CommonElectricTerrainCureStatus(serverFlow, BattleEventVar_GetValue(VAR_MON_ID));
    }
    void HandlerElectricTerrainFloatingChangeNEW(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (IS_NOT_NEW_EVENT)
            return;

        if (BattleField_GetTerrain() != TERRAIN_ELECTRIC)
            return;

        CommonElectricTerrainCureStatus(serverFlow, BattleEventVar_GetValue(NEW_VAR_MON_ID));
    }
    // GRASSY TERRAIN
    void HandlerGrassyTerrainHeal(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (BattleField_GetTerrain() != TERRAIN_GRASSY)
            return;

        HandlerParam_RecoverHP *v6;

        int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
        BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
        if (!ServerControl_CheckFloating(serverFlow, currentMon, 1))
        {
            if (!BattleMon_IsFullHP(currentMon))
            {
                v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(serverFlow, EFFECT_RECOVERHP, currentSlot);
                v6->pokeID = currentSlot;
                v6->recoverHP = DivideMaxHPZeroCheck(currentMon, 16);
                BattleHandler_StrSetup(&v6->exStr, 2u, 914);
                BattleHandler_AddArg(&v6->exStr, currentSlot);
                int SubID = BattleEventItem_GetSubID(a1);
                BattleHandler_AddArg(&v6->exStr, SubID);
                BattleHandler_PopWork(serverFlow, v6);
            }
        }
    }
    void HandlerGrassyTerrainQuakeMoves(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (BattleField_GetTerrain() != TERRAIN_GRASSY)
            return;

        if (pokemonSlot == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            int moveID = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (moveID == 89 ||
                moveID == 222 ||
                moveID == 523)
            {
                BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
                if (!ServerControl_CheckFloating(serverFlow, defendingMon, 1))
                {
                    int power = BattleEventVar_GetValue(VAR_MOVE_POWER);
                    BattleEventVar_RewriteValue(VAR_MOVE_POWER, power / 2);
                }
            }
        }
    }
    // MISTY TERRAIN (all in general)
    // PSYCHIC TERRAIN
    void HandlerPsychicTerrainPreventPrio(BattleEventItem *a1, ServerFlow *serverFlow, int pokemonSlot, int *work)
    {
        if (BattleField_GetTerrain() != TERRAIN_PSYCHIC)
            return;

        int currentMon = BattleEventVar_GetValue(VAR_DEFENDING_MON);
        // k::Printf("PREVENT PRIO -> TERRAIN: %d | ATTACKER: %d | DEFENDER: %d\n", BattleField_GetTerrain(), BattleEventVar_GetValue(VAR_ATTACKING_MON), currentMon);
        if (currentMon == BattleEventVar_GetValue(VAR_ATTACKING_MON))
            return;

        BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, currentMon);
        if (!ServerControl_CheckFloating(serverFlow, defendingMon, 1))
        {
            ActionOrderWork *action_order = serverFlow->actionOrderWork;
            u16 orderIdx = 0;

            BattleMon *attackingMon = Handler_GetBattleMon(serverFlow, BattleEventVar_GetValue(VAR_ATTACKING_MON));
            for (; orderIdx < 6; ++orderIdx)
                if (action_order[orderIdx].battleMon == attackingMon)
                    break;

            int priority = (action_order[orderIdx].field_8 >> 16) & 0x3FFFFF;
            priority -= 7;
            // k::Printf("PRIO: %d\n", priority);
            int special_priority = ((action_order[orderIdx].field_8 >> 13) & 0x7); // special priority takes into account item & ability prio boosts (1 = no added prio)
            special_priority -= 1;
            // k::Printf("SPECIAL PRIO: %d\n", special_priority);
            priority += special_priority;

            if (priority > 0)
                BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
        }
    }

    BattleEventHandlerTableEntry FieldTerrainHandlers[] = {
        // GENERAL TERRAIN
        {EVENT_ADD_CONDITION_CHECK_FAIL, (BattleEventHandler)HandlerTerrainPreventStatus},
        {EVENT_ADD_CONDITION_FAIL, (BattleEventHandler)HandlerTerrainStatusFailMessage},
        // ELECTRIC TERRAIN
        {EVENT_CHECK_SLEEP, (BattleEventHandler)HandlerElectricTerrainCheckSleep},
        {EVENT_AFTER_TERRAIN_CHANGE, (BattleEventHandler)HandlerElectricTerrainTerrainChange},
        {EVENT_SWITCH_IN, (BattleEventHandler)HandlerElectricTerrainSwitchIn},
        {EVENT_ACTION_PROCESSING_END, (BattleEventHandler)HandlerElectricTerrainActProcEnd},
        {EVENT_ITEM_REWRITE_DONE, (BattleEventHandler)HandlerElectricTerrainFloatingChange},
        {EVENT_AFTER_ABILITY_CHANGE, (BattleEventHandler)HandlerElectricTerrainFloatingChange},
        {EVENT_GROUNDED_BY_GRAVITY, (BattleEventHandler)HandlerElectricTerrainFloatingChangeNEW},
        // GRASSY TERRAIN
        {EVENT_TURN_CHECK_BEGIN, (BattleEventHandler)HandlerGrassyTerrainHeal},
        {EVENT_MOVE_BASE_POWER, (BattleEventHandler)HandlerGrassyTerrainQuakeMoves},
        // MISTY TERRAIN (all in general)
        // PSYCHIC TERRAIN
        {EVENT_ABILITY_CHECK_NO_EFFECT, (BattleEventHandler)HandlerPsychicTerrainPreventPrio},
    };

    BattleEventHandlerTableEntry *EventAddFieldTerrain(int *a1)
    {
        *a1 = 12;
        return FieldTerrainHandlers;
    }

    FieldEffectEventAddTable FieldEffectEventAddTableExt[] = {
        {FLDEFF_WEATHER, EventAddFieldWeather},
        {FLDEFF_TRICK_ROOM, EventAddFieldTrickRoom},
        {FLDEFF_GRAVITY, EventAddFieldGravity},
        {FLDEFF_IMPRISON, EventAddFieldImprison},
        {FLDEFF_WATER_SPORT, EventAddFieldWaterSport},
        {FLDEFF_MUD_SPORT, EventAddFieldMudSport},
        {FLDEFF_WONDER_ROOM, EventAddFieldWonderRoom},
        {FLDEFF_MAGIC_ROOM, EventAddFieldMagicRoom},
        {FLDEFF_MAGIC_ROOM, EventAddFieldMagicRoom},
#if ADD_NEW_ITEMS
        {(FieldEffect)FLDEFF_TERRAIN, EventAddFieldTerrain},
#endif
    };

    // #if ADD_NEW_ITEMS

    BattleEventItem *THUMB_BRANCH_j_j_FieldEffectEvent_AddItem(FieldEffect fieldEffect, int a2, ConditionData conditionData, int a4)
    {
        int enventFuncAmount[5];
        enventFuncAmount[1] = a4;

        for (u16 fieldEffectIdx = 0; fieldEffectIdx < ARRAY_COUNT(FieldEffectEventAddTableExt); ++fieldEffectIdx)
        {
            if (fieldEffect == FieldEffectEventAddTableExt[fieldEffectIdx].effect)
            {
                BattleEventHandlerTableEntry *battleEventEntry = FieldEffectEventAddTableExt[fieldEffectIdx].func(enventFuncAmount);
                BattleEventItem *result = BattleEvent_AddItem(EVENTITEM_FIELD, fieldEffect, EVENTPRI_FIELD_DEFAULT, 0, a2, battleEventEntry, enventFuncAmount[0]);
                return result;
            }
        }
        return nullptr;
    }

    void THUMB_BRANCH_BattleField_InitCore(BattleField *battleField, WeatherID weather)
    {
        for (int currentEffect = FLDEFF_WEATHER; currentEffect < DEFAULT_FIELD_EFFECT_AMOUNT; ++currentEffect)
        {
            BattleField_ClearFactorWork(battleField, (FieldEffect)currentEffect);
        }
        battleField->Weather = weather;
        battleField->WeatherTurns = 255;

        for (int currentEffect = FLDEFF_TERRAIN; currentEffect < FIELD_EFFECT_AMOUNT; ++currentEffect)
        {
            BattleField_ClearFactorWork(battleField, (FieldEffect)currentEffect);
        }
        battleFieldExt.terrain = 0; // TODO: Pre set terrain in battle, maybe... if its done in this function
        battleFieldExt.terrainTurns = 255;
    }

    void THUMB_BRANCH_BattleField_ClearFactorWork(BattleField *battleField, FieldEffect fieldEffect)
    {
        BattleField *currBattleField = battleField;
        FieldEffect currFieldEffect = fieldEffect;
        if (fieldEffect >= DEFAULT_FIELD_EFFECT_AMOUNT)
        {
            currBattleField = BATTLEFIELD_EXT;
            currFieldEffect = (FieldEffect)(fieldEffect - DEFAULT_FIELD_EFFECT_AMOUNT);
        }

        currBattleField->battleEventItems[currFieldEffect] = 0;

        currBattleField->conditionData[currFieldEffect] = Condition_MakeNull();
        currBattleField->TurnCount[currFieldEffect] = 0;
        currBattleField->DependPokeCount[currFieldEffect] = 0;
        currBattleField->EffectEnableFlags[currFieldEffect] = 0;

        int currentPoke = 0;
        while (currentPoke < 6)
        {
            currBattleField->DependPokeID[currFieldEffect][currentPoke] = 31;
            ++currentPoke;
        }
    }

    int THUMB_BRANCH_BattleField_AddEffectCore(BattleField *battleField, FieldEffect fieldEffect, ConditionData conditionData, int a4)
    {
        BattleField *currBattleField = battleField;
        FieldEffect currFieldEffect = fieldEffect;
        if (fieldEffect >= DEFAULT_FIELD_EFFECT_AMOUNT)
        {
            currBattleField = BATTLEFIELD_EXT;
            currFieldEffect = (FieldEffect)(fieldEffect - DEFAULT_FIELD_EFFECT_AMOUNT);
        }

        if (currBattleField->EffectEnableFlags[currFieldEffect])
            return 0;

        if (a4)
        {
            BattleEventItem *effectEvent = j_j_FieldEffectEvent_AddItem(fieldEffect, 0, conditionData, a4);
            currBattleField->battleEventItems[currFieldEffect] = effectEvent;
            if (!effectEvent)
                return 0;
        }

        currBattleField->EffectEnableFlags[currFieldEffect] = 1;
        currBattleField->conditionData[currFieldEffect] = conditionData;
        currBattleField->TurnCount[currFieldEffect] = 0;
        currBattleField->DependPokeCount[currFieldEffect] = 0;

        int currentPoke = 0;
        while (currentPoke < 6)
        {
            currBattleField->DependPokeID[currFieldEffect][currentPoke] = 31;
            ++currentPoke;
        }

        int pokemonSlot = Condition_GetMonID(conditionData);
        if (pokemonSlot != 31)
        {
            BattleField_AddDependPokeCore(battleField, fieldEffect, pokemonSlot);
        }
        return 1;
    }

    int THUMB_BRANCH_BattleField_RemoveEffectCore(BattleField *battleField, FieldEffect fieldEffect)
    {
        if (!BattleField_CheckFieldEffectCore(battleField, fieldEffect))
            return 0;

        BattleField *currBattleField = battleField;
        FieldEffect currFieldEffect = fieldEffect;
        if (fieldEffect >= DEFAULT_FIELD_EFFECT_AMOUNT)
        {
            currBattleField = BATTLEFIELD_EXT;
            currFieldEffect = (FieldEffect)(fieldEffect - DEFAULT_FIELD_EFFECT_AMOUNT);
        }

        BattleEventItem *battleEventItems = currBattleField->battleEventItems[currFieldEffect];
        if (battleEventItems)
        {
            BattleEventItem_Remove(battleEventItems);
            currBattleField->battleEventItems[currFieldEffect] = 0;
        }
        BattleField_ClearFactorWork(battleField, fieldEffect);

        return 1;
    }

    int THUMB_BRANCH_BattleField_AddDependPokeCore(BattleField *battleField, FieldEffect fieldEffect, int pokemonSlot)
    {
        BattleField *currBattleField = battleField;
        FieldEffect currFieldEffect = fieldEffect;
        if (fieldEffect >= DEFAULT_FIELD_EFFECT_AMOUNT)
        {
            currBattleField = BATTLEFIELD_EXT;
            currFieldEffect = (FieldEffect)(fieldEffect - DEFAULT_FIELD_EFFECT_AMOUNT);
        }

        if (BattleField_CheckFieldEffectCore(battleField, fieldEffect))
        {
            u32 pokeCount = currBattleField->DependPokeCount[currFieldEffect];
            if (pokeCount < 6)
            {
                int currentPoke = 0;
                if (!pokeCount)
                {
                    currBattleField->DependPokeID[currFieldEffect][pokeCount] = pokemonSlot;
                    currBattleField->DependPokeCount[currFieldEffect]++;
                    return 1;
                }
                while (pokemonSlot != currBattleField->DependPokeID[currFieldEffect][currentPoke])
                {
                    if (++currentPoke >= pokeCount)
                    {
                        currBattleField->DependPokeID[currFieldEffect][pokeCount] = pokemonSlot;
                        currBattleField->DependPokeCount[currFieldEffect]++;
                        return 1;
                    }
                }
            }
        }

        return 0;
    }

    void THUMB_BRANCH_BattleField_RemoveDependPokeEffectCore(BattleField *battleField, int pokemonSlot)
    {
        for (int currentEffect = FLDEFF_WEATHER; currentEffect < 8; ++currentEffect)
        {
            if (BattleField_CheckFieldEffectCore(battleField, (FieldEffect)currentEffect))
            {
                if (battleField->DependPokeCount[currentEffect])
                {
                    int currentPoke = 0;
                    while (pokemonSlot != battleField->DependPokeID[currentEffect][currentPoke]) // find slot to remove
                    {
                        if (++currentPoke >= battleField->DependPokeCount[currentEffect])
                        {
                            return;
                        }
                    }

                    for (; currentPoke < 5; ++currentPoke) // move back slots after removed slot by one
                    {
                        battleField->DependPokeID[currentEffect][currentPoke] = battleField->DependPokeID[currentEffect][currentPoke + 1];
                    }
                    battleField->DependPokeID[currentEffect][currentPoke] = 31; // set last slot to null
                    --battleField->DependPokeCount[currentEffect];              // remove 1 from the total count

                    u32 pokeCount = battleField->DependPokeCount[currentEffect];
                    if (pokeCount == 0) // remove field effect if the count is empty
                    {
                        BattleEventItem *battleEventItems = battleField->battleEventItems[currentEffect];
                        if (battleEventItems)
                        {
                            BattleEventItem_Remove(battleEventItems);
                            battleField->battleEventItems[currentEffect] = 0;
                        }
                        BattleField_ClearFactorWork(battleField, (FieldEffect)currentEffect);
                    }
                    else
                    {
                        int condPokemonSlot = Condition_GetMonID(battleField->conditionData[currentEffect]);
                        if (pokemonSlot == condPokemonSlot) // if the condition mon id is the one removed, set it to the first available mon
                        {
                            Condition_SetMonID(&battleField->conditionData[currentEffect], battleField->DependPokeID[currentEffect][0]);
                        }
                    }
                }
            }
        }
    }

    u32 THUMB_BRANCH_BattleField_CheckFieldEffectCore(BattleField *battleField, FieldEffect fieldEffect)
    {
        if (fieldEffect >= DEFAULT_FIELD_EFFECT_AMOUNT)
            return battleFieldExt.effectEnableFlags[fieldEffect - DEFAULT_FIELD_EFFECT_AMOUNT];

        return battleField->EffectEnableFlags[fieldEffect];
    }

    bool serverCommandFlag = false;
    int THUMB_BRANCH_ServerCommand_TurnCheckField(int a1)
    {
        serverCommandFlag = true;
        BattleField_TurnCheckCore(*(BattleField **)(a1 + 52), 0, 0);
        serverCommandFlag = false;
        return 1;
    }
    void THUMB_BRANCH_BattleField_TurnCheckCore(BattleField *battleField, int (*callback)(FieldEffect, ServerFlow *), ServerFlow *serverFlow)
    {
        for (int currentEffect = 1; currentEffect < FIELD_EFFECT_AMOUNT; ++currentEffect)
        {
            if (BattleField_CheckFieldEffectCore(battleField, (FieldEffect)currentEffect))
            {
                BattleField *currBattleField = battleField;
                FieldEffect currFieldEffect = (FieldEffect)currentEffect;
                if (currentEffect >= DEFAULT_FIELD_EFFECT_AMOUNT)
                {
                    currBattleField = BATTLEFIELD_EXT;
                    currFieldEffect = (FieldEffect)(currentEffect - DEFAULT_FIELD_EFFECT_AMOUNT);
                }

                u32 turnMax = Condition_GetTurnMax(currBattleField->conditionData[currFieldEffect]);
                if (turnMax)
                {
                    u32 turnCount = currBattleField->TurnCount[currFieldEffect];
                    if (currentEffect < DEFAULT_FIELD_EFFECT_AMOUNT || !serverCommandFlag)
                        turnCount += 1;

                    currBattleField->TurnCount[currFieldEffect] = turnCount;
                    if (currentEffect == FLDEFF_TERRAIN)
                    {
                        if (battleFieldExt.terrainTurns == 255)
                            continue; // ignore turns if terrain is permanent

                        battleFieldExt.terrainTurns = turnCount; // update terrain turns
                    }

                    if (turnCount >= turnMax)
                    {
                        if (currentEffect == FLDEFF_TERRAIN)
                        {
                            BattleField_EndTerrain(); // remove terrain data
                            ServerEvent_ChangeTerrain(serverFlow, TERRAIN_NULL);
                        }

                        BattleEventItem *events = currBattleField->battleEventItems[currFieldEffect];
                        if (events)
                        {
                            BattleEventItem_Remove(events);
                            currBattleField->battleEventItems[currFieldEffect] = 0;
                        }
                        BattleField_ClearFactorWork(battleField, (FieldEffect)currentEffect);
                        if (callback)
                        {
                            callback((FieldEffect)currentEffect, serverFlow);
                        }
                    }
                }
            }
        }
    }

    int THUMB_BRANCH_BattleHandler_AddFieldEffect(ServerFlow *serverFlow, HandlerParam_AddFieldEffect *params)
    {
        u8 prevTerrain = TERRAIN_NULL;
        u8 terrain = params->field_D;
        int pokemonSlot = params->header.flags << 19 >> 27;

        if (params->effect == FLDEFF_TERRAIN)
        {
            prevTerrain = BattleField_GetTerrain();
            u8 turns = Condition_GetTurnMax(params->cont);

            u8 extraTurns = ServerEvent_IncreaseMoveTerrainTurns(serverFlow, terrain, pokemonSlot);
            if (extraTurns)
            {
                turns += extraTurns;
                params->cont = Condition_MakeTurn(turns);
            }

            if (!ServerControl_ChangeTerrain(serverFlow, terrain, turns))
            {
                return 0;
            }
        }

        if (!prevTerrain && !ServerControl_FieldEffectCore(serverFlow, params->effect, params->cont, params->fAddDependPoke))
        {
            return 0;
        }

        if (params->effect == FLDEFF_TERRAIN)
        {
            int moveID = 0;
            switch (params->field_D)
            {
            case TERRAIN_ELECTRIC:
                moveID = ELECTRIC_TERRAIN_MOVE_ANIM;
                break;
            case TERRAIN_GRASSY:
                moveID = GRASSY_TERRAIN_MOVE_ANIM;
                break;
            case TERRAIN_MISTY:
                moveID = MISTY_TERRAIN_MOVE_ANIM;
                break;
            case TERRAIN_PSYCHIC:
                moveID = PSYCHIC_TERRAIN_MOVE_ANIM;
                break;
            }
            int pokePos = MainModule_PokeIDToPokePos(serverFlow->mainModule, serverFlow->pokeCon, pokemonSlot);
            ServerDisplay_AddCommon(serverFlow->serverCommandQueue, 48, pokePos, pokePos, moveID, 0, 0);
        }

        BattleHandler_SetString(serverFlow, &params->exStr);

        if (params->effect == FLDEFF_TERRAIN)
        {
            ServerEvent_ChangeTerrainAfter(serverFlow, terrain);
        }

        return 1;
    }

    int THUMB_BRANCH_BattleHandler_RemoveFieldEffect(ServerFlow *serverFlow, HandlerParam_RemoveFieldEffect *params)
    {
        if (params->effect == FLDEFF_TERRAIN)
        {
            BattleField_EndTerrain();
        }
        if (!BattleField_RemoveEffect(params->effect))
        {
            return 0;
        }
        ServerControl_FieldEffectEnd(serverFlow, params->effect);
        return 1;
    }

    void THUMB_BRANCH_ServerControl_FieldEffectEnd(ServerFlow *serverFlow, BattleFieldEffect fieldEffect)
    {
        int msgID = -1;
        // k::Printf("END FIELD EFFECT: %d\n", fieldEffect);
        if (fieldEffect <= FLDEFF_TERRAIN)
        {
            switch (fieldEffect)
            {
            case FLDEFF_TRICK_ROOM:
                msgID = 116;
                break;
            case FLDEFF_GRAVITY:
                msgID = 118;
                break;
            case FLDEFF_WONDER_ROOM:
                msgID = 179;
                break;
            case FLDEFF_MAGIC_ROOM:
                msgID = 181;
                break;
            case FLDEFF_TERRAIN:
                msgID = BATTLE_TERRAIN_END_MSGID;
                break;
            default:
                break;
            }
        }
        // k::Printf("MSG ID: %d\n", msgID);
        if (msgID >= 0)
        {
            ServerDisplay_AddMessageImpl(serverFlow->serverCommandQueue, 90, msgID, 0xFFFF0000);
        }
        ServerDisplay_AddCommon(serverFlow->serverCommandQueue, 36, fieldEffect);
        if (fieldEffect == EFFECT_MAGIC_ROOM)
        {
            ServerControl_SortBySpeed(serverFlow, serverFlow->PokeSetTemp);
            j_PokeSet_SeekStart(serverFlow->PokeSetTemp);
            for (BattleMon *currentMon = j_PokeSet_SeekNext(serverFlow->PokeSetTemp);
                 currentMon;
                 currentMon = j_PokeSet_SeekNext(serverFlow->PokeSetTemp))
            {
                if (BattleMon_CanBattle(currentMon))
                {
                    ServerControl_CheckItemReaction(serverFlow, currentMon, 0);
                }
            }
        }
    }

    int THUMB_BRANCH_BattleHandler_GravityCheck(ServerFlow *serverFlow, HandlerParam_Header *params)
    {
        u8 pokemonIDs[8];
        short pokePos = MainModule_PokeIDToPokePos(serverFlow->mainModule, serverFlow->pokeCon, params->flags << 19 >> 27);
        int pokeCount = Handler_ExpandPokeID(serverFlow, pokePos | 0x800, pokemonIDs);
        for (int i = 0; i < pokeCount; i = ++i)
        {
            BattleMon *battleMon = PokeCon_GetBattleMon(serverFlow->pokeCon, pokemonIDs[i]);
            bool grounded = false;
            if (BattleMon_GetConditionFlag(battleMon, CONDITIONFLAG_FLY))
            {
                ServerControl_HideTurnCancel((int)serverFlow, battleMon, 3);
                grounded = true;
            }
            if (ServerEvent_CheckFloating(serverFlow, battleMon, 1))
            {
                grounded = true;
            }
            if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_FLOATING))
            {
                ServerControl_CureCondition(serverFlow, battleMon, CONDITION_FLOATING, 0);
                grounded = true;
            }
            if (BattleMon_CheckIfMoveCondition(battleMon, CONDITION_TERA))
            {
                ServerControl_CureCondition(serverFlow, battleMon, CONDITION_TERA, 0);
                grounded = true;
            }
            if (grounded)
            {
                ServerDisplay_AddMessageImpl(serverFlow->serverCommandQueue, 91, 1083, pokemonIDs[i], -65536);
                //  k::Printf("GRAVITY TEXT\n");
                ServerEvent_GroundedByGravity(serverFlow, battleMon);
            }
        }
        return 1;
    }
    // #endif

    // SIDE EFFECT EXPANSION
    // Accessing the Sife Effect functions crashed the game so I rewrote the whole system
    // Thats why I branch the 2 access points to create a Side Effect BattleItem (BattleHandler_AddSideEffect & ItemEffect_StatusGuard)
    // and build from there
    BattleSideManager SideStatusExt;
    u8 removeSideEffExtFlags;

    int BattleSideStatus_GetCountFromBattleEventItem(BattleEventItem *a1, unsigned int currentSide)
    {
        int effect = BattleEventItem_GetSubID(a1);
        if (currentSide >= 2)
        {
            return 0;
        }
        else
        {
            if (effect <= DEFAULT_SIDE_CONDITION_AMOUNT)
                return SideStatus.Sides[currentSide].Conditions[effect].Count;
            else
                return SideStatusExt.Sides[currentSide].Conditions[effect - DEFAULT_SIDE_CONDITION_AMOUNT].Count;
        }
    }

    BattleEventHandlerTableEntry *EventAddSideReflect(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D878;
    }
    BattleEventHandlerTableEntry *EventAddSideLightScreen(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D898;
    }
    BattleEventHandlerTableEntry *EventAddSideSafeguard(int *a1)
    {
        *a1 = 2;
        return (BattleEventHandlerTableEntry *)0x689D8D0;
    }
    BattleEventHandlerTableEntry *EventAddSideMist(int *a1)
    {
        *a1 = 2;
        return (BattleEventHandlerTableEntry *)0x689D8E0;
    }
    BattleEventHandlerTableEntry *EventAddSideTailwind(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D8C0;
    }
    BattleEventHandlerTableEntry *EventAddSideLuckyChant(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D8B8;
    }
    // Heavy-Duty Boots hazard checks
    void HandlerSideSpikes(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    {
        HandlerParam_Damage *v9;

        int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
        if (currentSide == GetSideFromMonID(currentSlot) && !Handler_CheckFloating(serverFlow, currentSlot))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
            // if (DoesItemPreventHazardEffects(BattleMon_GetHeldItem(currentMon))) // Heavy-Duty Boots check
            //     return;

            if (BattleMon_GetHeldItem(currentMon) == IT0228_PROTECTIVE_GEAR || BattleMon_GetValue(currentMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            {
                return;
            }

            int spikeLayers = BattleSideStatus_GetCountFromBattleEventItem(a1, currentSide); // New Definition
            int dmgPercent = 0;
            switch (spikeLayers)
            {
            case 1:
                dmgPercent = 8;
                break;
            case 2:
                dmgPercent = 6;
                break;
            case 3:
                dmgPercent = 4;
                break;
            }

            v9 = (HandlerParam_Damage *)BattleHandler_PushWork(serverFlow, EFFECT_DAMAGE, 31);
            v9->pokeID = currentSlot;
            v9->damage = DivideMaxHPZeroCheck(currentMon, dmgPercent);
            BattleHandler_StrSetup(&v9->exStr, 2u, 851);
            BattleHandler_AddArg(&v9->exStr, currentSlot);
            BattleHandler_PopWork(serverFlow, v9);
        }
    }
    BattleEventHandlerTableEntry SideSpikesHandlers[] = {
        {EVENT_SWITCH_IN, HandlerSideSpikes},
    };
    BattleEventHandlerTableEntry *EventAddSideSpikes(int *a1)
    {
        *a1 = 1;
        return SideSpikesHandlers;
    }
    // Heavy-Duty Boots hazard checks
    void HandlerSideToxicSpikes(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    {
        HandlerParam_RemoveSideEffect *v7; // r1
        HandlerParam_RemoveSideEffect *v9; // r0
        HandlerParam_AddCondition *v10;    // r4

        int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
        if (currentSide == GetSideFromMonID(currentSlot) && !Handler_CheckFloating(serverFlow, currentSlot))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
            if (BattleMon_HasType(currentMon, TYPE_POISON))
            {
                v7 = (HandlerParam_RemoveSideEffect *)BattleHandler_PushWork(serverFlow, EFFECT_REMOVE_SIDE_EFFECT, currentSlot);
                v7->side = currentSide;
                v7->flags[0] = 3;
                for (unsigned int i = 1; i < 3; ++i)
                {
                    v9 = (HandlerParam_RemoveSideEffect *)((char *)v7 + i);
                    v9->flags[0] = 0;
                }
                if (v7->flags[0] > 1u)
                {
                    v7->flags[1] |= 0x80u;
                }
                BattleHandler_PopWork(serverFlow, v7);
            }
            else
            {
                if (BattleMon_GetHeldItem(currentMon) == IT0228_PROTECTIVE_GEAR || BattleMon_GetValue(currentMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
                {
                    return;
                }

                v10 = (HandlerParam_AddCondition *)BattleHandler_PushWork(serverFlow, EFFECT_ADDCONDITION, 31);
                v10->sickID = CONDITION_POISON;
                unsigned int battleCount = BattleSideStatus_GetCountFromBattleEventItem(a1, currentSide); // New Definition
                ConditionData permanent;
                if (battleCount <= 1)
                {
                    permanent = Condition_MakePermanent();
                }
                else
                {
                    permanent = Condition_MakeBadlyPoisoned();
                }
                v10->sickCont = permanent;
                v10->pokeID = currentSlot;
                BattleHandler_PopWork(serverFlow, v10);
            }
        }
    }
    BattleEventHandlerTableEntry SideToxicSpikesHandlers[] = {
        {EVENT_SWITCH_IN, HandlerSideToxicSpikes},
    };
    BattleEventHandlerTableEntry *EventAddSideToxicSpikes(int *a1)
    {
        *a1 = 1;
        return SideToxicSpikesHandlers;
    }
    // Heavy-Duty Boots hazard checks
    void HandlerSideStealthRock(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    {
        HandlerParam_Damage *v9;

        int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
        if (currentSide == GetSideFromMonID(currentSlot))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
            if (BattleMon_GetHeldItem(currentMon) == IT0228_PROTECTIVE_GEAR || BattleMon_GetValue(currentMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            {
                return;
            }

            int pokeType = BattleMon_GetPokeType(currentMon);
            TypeEffectiveness effectiveness = (TypeEffectiveness)GetTypeEffectivenessVsMon(TYPE_FLYING, pokeType);
            unsigned int dmgPercent = 0;

            if (IsEqual(effectiveness, EFFECTIVENESS_IMMUNE))
            {
                return;
            }
            else if (IsEqual(effectiveness, EFFECTIVENESS_1_4))
            {
                dmgPercent = 32;
            }
            else if (IsEqual(effectiveness, EFFECTIVENESS_1_2))
            {
                dmgPercent = 16;
            }
            else if (IsEqual(effectiveness, EFFECTIVENESS_1))
            {
                dmgPercent = 8;
            }
            else if (IsEqual(effectiveness, EFFECTIVENESS_2))
            {
                dmgPercent = 4;
            }
            else if (IsEqual(effectiveness, EFFECTIVENESS_4))
            {
                dmgPercent = 2;
            }

            v9 = (HandlerParam_Damage *)BattleHandler_PushWork(serverFlow, EFFECT_DAMAGE, 31);
            v9->pokeID = currentSlot;
            v9->damage = DivideMaxHPZeroCheck(currentMon, dmgPercent);
            BattleHandler_StrSetup(&v9->exStr, 2u, 854);
            BattleHandler_AddArg(&v9->exStr, currentSlot);
            BattleHandler_PopWork(serverFlow, v9);
        }
    }
    BattleEventHandlerTableEntry SideStealthRockHandlers[] = {
        {EVENT_SWITCH_IN, HandlerSideStealthRock},
    };
    BattleEventHandlerTableEntry *EventAddSideStealthRock(int *a1)
    {
        *a1 = 1;
        return SideStealthRockHandlers;
    }
    BattleEventHandlerTableEntry *EventAddSideWideGuard(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D888;
    }
    BattleEventHandlerTableEntry *EventAddSideQuickGuard(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D8A0;
    }
    BattleEventHandlerTableEntry *EventAddSideRainbow(int *a1)
    {
        *a1 = 3;
        return (BattleEventHandlerTableEntry *)0x689D8F0;
    }
    BattleEventHandlerTableEntry *EventAddSideSeaOfFire(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D880;
    }
    BattleEventHandlerTableEntry *EventAddSideSwamp(int *a1)
    {
        *a1 = 1;
        return (BattleEventHandlerTableEntry *)0x689D8A8;
    }

    // STICKY WEB
    // Heavy-Duty Boots hazard checks
    void HandlerSideStickyWeb(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    {
        HandlerParam_ChangeStatStage *v3;
        HandlerParam_Message *bhwork;
        HandlerParam_ChangeStatStage *v6;

        int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
        if (currentSide == GetSideFromMonID(currentSlot))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
            if (BattleMon_GetHeldItem(currentMon) == IT0228_PROTECTIVE_GEAR || BattleMon_GetValue(currentMon, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            {
                return;
            }

            if (Handler_CheckFloating(serverFlow, currentSlot))
                return;

            bhwork = (HandlerParam_Message *)BattleHandler_PushWork(serverFlow, EFFECT_MESSAGE, 0);
            BattleHandler_StrSetup(&bhwork->str, 1u, 227);
            BattleHandler_AddArg(&bhwork->str, currentSlot);
            BattleHandler_PopWork(serverFlow, bhwork);

            v3 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, currentSlot);
            v3->header.flags |= 0x08000000;
            v3->poke_cnt = 1;
            v3->pokeID[0] = currentSlot;
            v3->fMoveAnimation = 1;
            v3->rankType = STATSTAGE_SPEED;
            v3->rankVolume = -1;
            v3->pad = 0x40000000;
            BattleHandler_PopWork(serverFlow, v3);

            // if (currentMon->Ability == ABIL128_DEFIANT)
            // {
            //     v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, currentSlot);
            //     v6->header.flags |= 0x800000u;
            //     v6->rankType = STATSTAGE_ATTACK;
            //     v6->rankVolume = 2;
            //     v6->fMoveAnimation = 1;
            //     v6->poke_cnt = 1;
            //     v6->pokeID[0] = currentSlot;
            //     BattleHandler_PopWork(serverFlow, v6);
            // }
        }
    }
    BattleEventHandlerTableEntry SideStickyWebHandlers[] = {
        {EVENT_SWITCH_IN, HandlerSideStickyWeb}, // Rapid Spin implementation is in HandlerRapidSpin
    };
    BattleEventHandlerTableEntry *EventAddSideStickyWeb(int *a1)
    {
        *a1 = 1;
        return SideStickyWebHandlers;
    }

    StatStage GetHighestStat(BattleMon *a1)
    {
        int atk;
        int def;
        int spa;
        int spd;
        int spe;

        atk = BattleMon_GetValue(a1, VALUE_ATTACK_STAT);
        def = BattleMon_GetValue(a1, VALUE_DEFENSE_STAT);
        spa = BattleMon_GetValue(a1, VALUE_SPECIAL_ATTACK_STAT);
        spd = BattleMon_GetValue(a1, VALUE_SPECIAL_DEFENSE_STAT);
        spe = BattleMon_GetValue(a1, VALUE_SPEED_STAT);

        if (atk >= def && atk >= spa && atk >= spd && atk >= spe)
        {
            return STATSTAGE_ATTACK;
        }
        else if (def >= atk && def >= spa && def >= spd && def >= spe)
        {
            return STATSTAGE_DEFENSE;
        }
        else if (spa >= atk && spa >= def && spa >= spd && spa >= spe)
        {
            return STATSTAGE_SPECIAL_ATTACK;
        }
        else if (spd >= atk && spd >= def && spd >= spa && spd >= spe)
        {
            return STATSTAGE_SPECIAL_DEFENSE;
        }
        else if (spe >= atk && spe >= def && spe >= spa && spe >= spd)
        {
            return STATSTAGE_SPEED;
        }
        else
        {
            return STATSTAGE_ATTACK;
        }
    }

    void HandlerSideOppressive(BattleEventItem *a1, ServerFlow *serverFlow, int currentSide, int *work)
    {
        HandlerParam_ChangeStatStage *v3;
        HandlerParam_ChangeStatStage *v6;

        int currentSlot = BattleEventVar_GetValue(VAR_MON_ID);
        if (currentSide == GetSideFromMonID(currentSlot))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
            // if (DoesItemPreventHazardEffects(BattleMon_GetHeldItem(currentMon))) // Heavy-Duty Boots check
            //     return;

            v3 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, currentSlot);
            v3->header.flags |= 0x04000000;
            v3->poke_cnt = 1;
            v3->pokeID[0] = currentSlot;
            v3->fMoveAnimation = 1;
            v3->rankType = GetHighestStat(currentMon);
            v3->rankVolume = -2;
            v3->pad = 0x40000000;
            BattleHandler_PopWork(serverFlow, v3);

            // if (currentMon->Ability == ABIL128_DEFIANT)
            // {
            //     v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGESTATSTAGE, currentSlot);
            //     v6->header.flags |= 0x800000u;
            //     v6->rankType = STATSTAGE_ATTACK;
            //     v6->rankVolume = 2;
            //     v6->fMoveAnimation = 1;
            //     v6->poke_cnt = 1;
            //     v6->pokeID[0] = currentSlot;
            //     BattleHandler_PopWork(serverFlow, v6);
            // }
        }
    }
    BattleEventHandlerTableEntry SideOppressiveHandlers[] = {
        {EVENT_SWITCH_IN, HandlerSideOppressive}, // Rapid Spin implementation is in HandlerRapidSpin
    };

    BattleEventHandlerTableEntry *EventAddSideOppressive(int *a1)
    {
        *a1 = 1;
        return SideOppressiveHandlers;
    }

    SideEffectEventAddTable ExtSideEffectEventAddTable[] = {
        {SIDEEFF_REFLECT, EventAddSideReflect, 1},
        {SIDEEFF_LIGHT_SCREEN, EventAddSideLightScreen, 1},
        {SIDEEFF_SAFEGUARD, EventAddSideSafeguard, 1},
        {SIDEEFF_MIST, EventAddSideMist, 1},
        {SIDEEFF_TAILWIND, EventAddSideTailwind, 1},
        {SIDEEFF_LUCKY_CHANT, EventAddSideLuckyChant, 1},
        {SIDEEFF_SPIKES, EventAddSideSpikes, 3},
        {SIDEEFF_TOXIC_SPIKES, EventAddSideToxicSpikes, 2},
        {SIDEEFF_STEALTH_ROCK, EventAddSideStealthRock, 1},
        {SIDEEFF_WIDE_GUARD, EventAddSideWideGuard, 1},
        {SIDEEFF_QUICK_GUARD, EventAddSideQuickGuard, 1},
        {SIDEEFF_RAINBOW, EventAddSideRainbow, 1},
        {SIDEEFF_SEA_OF_FIRE, EventAddSideSeaOfFire, 1},
        {SIDEEFF_SWAMP, EventAddSideSwamp, 1},
        {SIDEEFF_STICKY_WEB, EventAddSideStickyWeb, 1},
        {SIDEEFF_OPPRESSIVE, EventAddSideOppressive, 1}};

    int *SideEffectEvent_AddItem(int currentSide, SideEffect effect, ConditionData condData)
    {
        __int16 effectCpy;                       // r5
        BattleSideCondition *sideCondition;      // r4
        unsigned int Count;                      // r0
        unsigned int i;                          // r6
        BattleEventHandlerTableEntry *eventFunc; // r0
        BattleEventItem *eventItem;              // r5
        ConditionData v9;                        // r0
        int v12[8];                              // [sp+10h] [bp-28h] BYREF
        ConditionData condDataCpy;               // [sp+30h] [bp-8h]

        v12[6] = currentSide;
        v12[7] = effect;
        condDataCpy = condData;
        effectCpy = effect;

        if (effect < DEFAULT_SIDE_CONDITION_AMOUNT)
            sideCondition = &SideStatus.Sides[currentSide].Conditions[effect];
        else
            sideCondition = &SideStatusExt.Sides[currentSide].Conditions[effect - DEFAULT_SIDE_CONDITION_AMOUNT];

        Count = sideCondition->Count;
        for (i = 0; i < ARRAY_COUNT(ExtSideEffectEventAddTable); ++i)
        {
            if (effect == ExtSideEffectEventAddTable[i].sideEffect)
            {
                if (!Count)
                {
                    eventFunc = ExtSideEffectEventAddTable[i].func(v12);
                    eventItem = BattleEvent_AddItem(EVENTITEM_SIDE, effectCpy, EVENTPRI_SIDE_DEFAULT, 0, currentSide, eventFunc, v12[0]);
                    BattleEventItem_SetWorkValue(eventItem, 6, condDataCpy);
                    sideCondition->Count = 1;
                    v9 = condDataCpy;
                    sideCondition->TurnCounter = 0;
                    sideCondition->conditionData = v9;
                    sideCondition->battleEventItem = eventItem;

                    return (int *)&eventItem->prev;
                }
                if (Count < ExtSideEffectEventAddTable[i].maxCount)
                {
                    ++sideCondition->Count;
                    return (int *)&sideCondition->battleEventItem->prev;
                }
            }
        }
        return 0;
    }
    int THUMB_BRANCH_BattleHandler_AddSideEffect(ServerFlow *a1, HandlerParam_AddSideEffect *a2)
    {
        int side;           // r3
        ConditionData cont; // [sp+4h] [bp-14h] BYREF

        side = a2->side;
        cont = a2->cont;
        ServerEvent_CheckSideEffectParam(a1, a2->header.flags << 19 >> 27, a2->effect, side, (int *)&cont);
        if (!SideEffectEvent_AddItem(a2->side, (SideEffect)a2->effect, cont))
        {
            return 0;
        }
        BattleHandler_SetString(a1, &a2->exStr);
        return 1;
    }
    int THUMB_BRANCH_ItemEffect_StatusGuard(ServerFlow *a1, BattleMon *a2)
    {
        int ID;                  // r0
        int SideFromMonID;       // r6
        ConditionData Turn;      // r0
        int v6;                  // r0
        HandlerParam_Header *v7; // r4

        ID = BattleMon_GetID(a2);
        SideFromMonID = GetSideFromMonID(ID);
        Turn = Condition_MakeTurn(5);
        SideEffectEvent_AddItem(SideFromMonID, SIDEEFF_MIST, Turn);
        if (!v6)
        {
            return 0;
        }
        v7 = BattleHandler_PushWork(a1, EFFECT_MESSAGE, 31);
        BattleHandler_StrSetup((HandlerParam_StrParams *)&v7[1], 1u, 136);
        BattleHandler_AddArg((HandlerParam_StrParams *)&v7[1], SideFromMonID);
        BattleHandler_PopWork(a1, v7);
        return 1;
    }

    void THUMB_BRANCH_BattleSideStatus_Clear()
    {
        sys_memset(&SideStatus, 0, 448u);
        sys_memset(&SideStatusExt, 0, 448u);
    }

    int THUMB_BRANCH_j_j_BattleSideStatus_GetCount(int currentSide, SideEffect effect)
    {
        if (effect < DEFAULT_SIDE_CONDITION_AMOUNT)
            return SideStatus.Sides[currentSide].Conditions[effect].Count;
        else
            return SideStatusExt.Sides[currentSide].Conditions[effect - DEFAULT_SIDE_CONDITION_AMOUNT].Count;
    }

    bool BattleSideStatus_IsEffectActive(int currentSide, SideEffect effect)
    {
        if (effect < DEFAULT_SIDE_CONDITION_AMOUNT)
            return SideStatus.Sides[currentSide].Conditions[effect].battleEventItem != 0;
        else
            return SideStatusExt.Sides[currentSide].Conditions[effect - DEFAULT_SIDE_CONDITION_AMOUNT].battleEventItem != 0;
    }
    bool THUMB_BRANCH_Handler_IsSideEffectActive(int a1, int currentSide, SideEffect effect)
    {
        return BattleSideStatus_IsEffectActive(currentSide, effect);
    }
    bool THUMB_BRANCH_j_j_BattleSideStatus_IsEffectActive(int currentSide, SideEffect effect)
    {
        return BattleSideStatus_IsEffectActive(currentSide, effect);
    }
    bool THUMB_BRANCH_j_j_BattleSideStatus_IsEffectActive_0(int currentSide, SideEffect effect)
    {
        return BattleSideStatus_IsEffectActive(currentSide, effect);
    }
    bool THUMB_BRANCH_j_j_BattleSideStatus_IsEffectActive_1(int currentSide, SideEffect effect)
    {
        return BattleSideStatus_IsEffectActive(currentSide, effect);
    }
    bool THUMB_BRANCH_j_j_BattleSideStatus_IsEffectActive_2(int currentSide, SideEffect effect)
    {
        return BattleSideStatus_IsEffectActive(currentSide, effect);
    }
    bool THUMB_BRANCH_j_j_BattleSideStatus_IsEffectActive_3(int currentSide, SideEffect effect)
    {
        return BattleSideStatus_IsEffectActive(currentSide, effect);
    }

    int THUMB_BRANCH_j_j_SideEvent_RemoveItem(int currentSide, SideEffect effect)
    {
        BattleSideCondition *sideCondition; // r4

        if (effect < DEFAULT_SIDE_CONDITION_AMOUNT)
            sideCondition = &SideStatus.Sides[currentSide].Conditions[effect];
        else
            sideCondition = &SideStatusExt.Sides[currentSide].Conditions[effect - DEFAULT_SIDE_CONDITION_AMOUNT];

        if (!sideCondition->battleEventItem)
        {
            return 0;
        }
        BattleEventItem_Remove(sideCondition->battleEventItem);
        sideCondition->battleEventItem = 0;
        sideCondition->Count = 0;

        int condDataInt = *((int *)&sideCondition->conditionData);
        condDataInt &= 0xFFFFFFF8;
        sideCondition->conditionData = *((ConditionData *)&condDataInt);

        return 1;
    }

    void THUMB_BRANCH_ServerControl_TurnCheckSide(ServerFlow *a1)
    {
        BattleSideCondition *sideCondition;
        unsigned int turnCounter;

        for (unsigned int currentSide = 0; currentSide < 2; ++currentSide)
        {
            for (unsigned int effect = 0; effect < ARRAY_COUNT(ExtSideEffectEventAddTable); ++effect)
            {
                if (effect < DEFAULT_SIDE_CONDITION_AMOUNT)
                    sideCondition = &SideStatus.Sides[currentSide].Conditions[effect];
                else
                    sideCondition = &SideStatusExt.Sides[currentSide].Conditions[effect - DEFAULT_SIDE_CONDITION_AMOUNT];

                int condDataInt = *((int *)&sideCondition->conditionData);

                if (sideCondition->Count != 0 && (condDataInt & 7) == 2)
                {
                    turnCounter = sideCondition->TurnCounter + 1;
                    sideCondition->TurnCounter = turnCounter;
                    if (turnCounter >= (condDataInt << 23) >> 26)
                    {
                        sideCondition->Count = 0;

                        condDataInt &= 0xFFFFFFF8;
                        sideCondition->conditionData = *((ConditionData *)&condDataInt);

                        BattleEventItem_Remove(sideCondition->battleEventItem);
                        sideCondition->battleEventItem = 0;
                        ServerControl_SideEffectEndMessage(currentSide, effect, a1);
                    }
                }
            }
        }
    }

    int THUMB_BRANCH_BattleHandler_RemoveSideEffectCore(ServerFlow *serverFlow, HandlerParam_RemoveSideEffect *params)
    {
        unsigned int flagIdx;
        bool effectFlagActive;

        int removedAnEffect = 0;
        for (u16 i = 0; i <= DEFAULT_SIDE_CONDITION_AMOUNT; ++i)
        {
            flagIdx = ((i >> 3) + 1);

            effectFlagActive = flagIdx < params->flags[0] && ((1 << (i & 7)) & params->flags[flagIdx]) != 0;
            if (effectFlagActive)
            {
                if (i >= DEFAULT_SIDE_CONDITION_AMOUNT) // if the unused flags are set we check the extended flags
                {
                    for (u16 j = DEFAULT_SIDE_CONDITION_AMOUNT; j < SIDE_CONDITION_AMOUNT; ++j)
                    {
                        u8 flag = 1 << (j - DEFAULT_SIDE_CONDITION_AMOUNT);
                        if (removeSideEffExtFlags & flag)
                        {
                            if (j_j_SideEvent_RemoveItem(params->side, j))
                            {
                                ServerControl_SideEffectEndMessageCore(serverFlow, SIDEEFF_STEALTH_ROCK, params->side);
                                removedAnEffect = 1;
                            }
                        }
                    }
                }
                else if (j_j_SideEvent_RemoveItem(params->side, i))
                {
                    ServerControl_SideEffectEndMessageCore(serverFlow, i, params->side);
                    removedAnEffect = 1;
                }
            }
        }

        removeSideEffExtFlags = 0;
        return removedAnEffect;
    }

    void THUMB_BRANCH_HandlerRapidSpin(BattleEventItem *a1, ServerFlow *serverFlow, int currentSlot, int *work)
    {
        HandlerParam_CureCondition *v6;
        HandlerParam_CureCondition *v7;
        HandlerParam_RemoveSideEffect *v10;

        if (currentSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            //   k::Printf("\n\nThis code is active!\n\n");
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, currentSlot);
            if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_LEECHSEED))
            {
                v6 = (HandlerParam_CureCondition *)BattleHandler_PushWork(serverFlow, EFFECT_CURE_STATUS, currentSlot);
                v6->poke_cnt = 1;
                v6->pokeID[0] = currentSlot;
                v6->sickCode = CONDITION_LEECHSEED;
                BattleHandler_PopWork(serverFlow, v6);
            }
            if (BattleMon_CheckIfMoveCondition(currentMon, CONDITION_BIND))
            {
                v7 = (HandlerParam_CureCondition *)BattleHandler_PushWork(serverFlow, EFFECT_CURE_STATUS, currentSlot);
                v7->poke_cnt = 1;
                v7->pokeID[0] = currentSlot;
                v7->sickCode = CONDITION_BIND;
                BattleHandler_PopWork(serverFlow, v7);
            }
            int currentSlotSide = GetSideFromMonID(currentSlot);

            bool isSpikesActive = BattleSideStatus_IsEffectActive(currentSlotSide, SIDEEFF_SPIKES);
            bool isToxSpikesActive = BattleSideStatus_IsEffectActive(currentSlotSide, SIDEEFF_TOXIC_SPIKES);
            bool isStealthRocksActive = BattleSideStatus_IsEffectActive(currentSlotSide, SIDEEFF_STEALTH_ROCK);
            bool isStickyWebActive = BattleSideStatus_IsEffectActive(currentSlotSide, (SideEffect)SIDEEFF_STICKY_WEB);
            if (isSpikesActive || isToxSpikesActive || isStealthRocksActive || isStickyWebActive)
            {
                v10 = (HandlerParam_RemoveSideEffect *)BattleHandler_PushWork(serverFlow, EFFECT_REMOVE_SIDE_EFFECT, currentSlot);
                v10->side = currentSlotSide;
                v10->flags[0] = 3;

                if (isSpikesActive && v10->flags[0] > 1u)
                {
                    v10->flags[1] |= 0b01000000;
                }
                if (isToxSpikesActive && v10->flags[0] > 1u)
                {
                    v10->flags[1] |= 0b10000000;
                }
                if (isStealthRocksActive && v10->flags[0] > 2u)
                {
                    v10->flags[2] |= 0b00000001;
                }
                if (isStickyWebActive && v10->flags[0] > 2u)
                {
                    v10->flags[2] |= 0b11000000; // we set the unused bits to indicate the use of the extended flags
                    removeSideEffExtFlags |= 1;
                }

                BattleHandler_PopWork(serverFlow, v10);
            }
        }
    }

    void THUMB_BRANCH_ServerControl_SideEffectEndMessageCore(ServerFlow *a1, unsigned int a2, int a3)
    {
        int v4; // r2

        v4 = -1;
        if (a2 <= 0xF)
        {
            if (IsEqual(a2, 0))
            {
                v4 = 126;
            }
            else if (IsEqual(a2, 1))
            {
                v4 = 130;
            }
            else if (IsEqual(a2, 2))
            {
                v4 = 134;
            }
            else if (IsEqual(a2, 3))
            {
                v4 = 138;
            }
            else if (IsEqual(a2, 4))
            {
                v4 = 142;
            }
            else if (IsEqual(a2, 5))
            {
                v4 = 146;
            }
            else if (IsEqual(a2, 6))
            {
                v4 = 150;
            }
            else if (IsEqual(a2, 7))
            {
                v4 = 154;
            }
            else if (IsEqual(a2, 8))
            {
                v4 = 158;
            }
            else if (IsEqual(a2, 0xB))
            {
                v4 = 166;
            }
            else if (IsEqual(a2, 0xC))
            {
                v4 = 170;
            }
            else if (IsEqual(a2, 0xD))
            {
                v4 = 174;
            }
            else if (IsEqual(a2, 0xE))
            {
                v4 = 212;
            }
        }
        if (v4 >= 0)
        {
            ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 90, v4, a3);
        }
    }

    extern void BattleField_EndWeather(BattleField *a1);
    extern int BtlvCore_WaitMessage(BtlvCore *a1);
    extern void BtlvCore_StartMessageStandard(BtlvCore *a1, int a2, _DWORD *a3);
    extern int BattleField_TurnCheckWeather();
    extern void ServerControl_ChangeWeatherAfter(ServerFlow *a1, int a2);
    extern int CalcWeatherDamage(BattleMon *a1, int a2);
    extern int ServerEvent_CheckWeatherReaction(ServerFlow *a1, BattleMon *a2, int a3);
    extern void ServerDisplay_WeatherDamage(ServerFlow *a1, BattleMon *r1_0, int a3, int a4);
    extern int ServerControl_CheckFainted(ServerFlow *a1, BattleMon *a2);
    extern void ServerControl_ViewEffect(ServerFlow *a1, int a2, int a3, int a4, int a5, unsigned __int16 a6);
    extern void j_j_PokeSet_SeekStart_6(PokeSet *a1);
    extern BattleMon *j_j_PokeSet_SeekNext_12(PokeSet *a1);
    extern bool ServerControl_ChangeWeatherCheck(ServerFlow *a1, unsigned int a2, int a3);
    extern int BattleField_GetWeatherTurns();

    u8 weather;
    int THUMB_BRANCH_ServerControl_ChangeWeather(ServerFlow *a1, unsigned int a2, int a3)
    {
        if (a2 == 10)
        {
            weather = 0;
            return 0;
        }
        if (a3 == 5)
        {
            a3 = 4;
        }
        if (!ServerControl_ChangeWeatherCheck(a1, a2, a3))
        {
            return 0;
        }
        if (a3 == 255)
        {
            weather = a2;
        }
        ServerControl_ChangeWeatherCore(a1, a2, a3);
        return 1;
    }

    bool THUMB_BRANCH_ServerControl_ChangeWeatherCheck(ServerFlow *a1, unsigned int a2, int a3)
    {
        if(a3 == 255){
            weather = a2;
        }
        if (a2 >= 5)
        {
            return 0;
        }
        return a2 != BattleField_GetWeather() || a3 == 255 && BattleField_GetWeatherTurns() != 255;
    }

    int PersonalServerEvent_CheckWeatherReaction(ServerFlow *a1, BattleMon *a2, int weatherType, int weatherDamage)
    {
        int v3;    // r3
        int ID;    // r0
        int v8;    // r5
        int Value; // r7
        int v10;   // r4
        int v12;   // [sp+0h] [bp-18h]

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetConstValue(VAR_WEATHER, weatherType);
        v8 = 0;
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEventVar_SetValue(VAR_DAMAGE, weatherDamage);
        BattleEvent_CallHandlers(a1, EVENT_WEATHER_REACTION);
        Value = BattleEventVar_GetValue(VAR_DAMAGE);
        v10 = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
        BattleEventVar_Pop();
        if (!v10)
        {
            return Value;
        }
        return v8;
    }

    int THUMB_BRANCH_ServerControl_TurnCheckWeather(ServerFlow *a1, PokeSet *a2)
    {
        int v3;         // r2
        int Weather;    // r6
        BattleMon *mon; // r4
        int v7;         // r7
        int v8;         // r3
        BattleMon *v9;  // r0
        int v11;        // [sp+Ch] [bp-1Ch]

        v3 = BattleField_TurnCheckWeather();
        if (v3)
        {
            ServerDisplay_AddCommon(a1->serverCommandQueue, 64, v3);
            if (weather)
            {
                ServerDisplay_AddCommon(a1->serverCommandQueue, 63, weather, 255);
            }
            ServerControl_ChangeWeatherAfter(a1, 0);
            return 0;
            //}
        }
        else
        {
            // MAYBE REMOVE
                // v11 = 0;
                // Weather = ServerEvent_GetWeather(a1);
                // j_j_PokeSet_SeekStart_6(a2);
                // _12 = j_j_PokeSet_SeekNext_12(a2);
                // if (_12)
                // {
                //     do
                //     {
                //     k::Printf("The dead mon is %d", _12->ID);
                //     if (!BattleMon_IsFainted(_12) && !BattleMon_GetConditionFlag(_12, CONDITIONFLAG_DIG) && !BattleMon_GetConditionFlag(_12, CONDITIONFLAG_DIVE))
                //     {
                //         v7 = HEManager_PushState(&a1->heManager);
                //         CalcWeatherDamage(_12, Weather);
                //         v8 = ServerEvent_CheckWeatherReaction(a1, _12, Weather);
                //         if (v8)
                //         {
                //             ServerDisplay_WeatherDamage(a1, _12, Weather, v8);
                //             v11 = 1;
                //         }
                //         HEManager_PopState(&a1->heManager, v7);
                //         // ServerControl_CheckFainted(a1, _12);
                //     }
                //     v9 = j_j_PokeSet_SeekNext_12(a2);
                //     _12 = v9;
                // } while (v9);
                // }
                // if (v11)
                // {
                //     ServerControl_ViewEffect(a1, 597, 6, 6, 0, 0);
                // }
            
            Weather = ServerEvent_GetWeather(a1);
            j_j_PokeSet_SeekStart_6(a2);
            for (mon = j_j_PokeSet_SeekNext_12(a2); mon; mon = j_j_PokeSet_SeekNext_12(a2))
            {
                if (!BattleMon_IsFainted(mon) && !BattleMon_GetConditionFlag(mon, CONDITIONFLAG_DIG) && !BattleMon_GetConditionFlag(mon, CONDITIONFLAG_DIVE))
                {
                    v7 = HEManager_PushState(&a1->heManager);
                    int v10 = CalcWeatherDamage(mon, Weather);
                    v8 = PersonalServerEvent_CheckWeatherReaction(a1, mon, Weather, v10);
                    if (v8)
                    {
                        ServerDisplay_WeatherDamage(a1, mon, Weather, v8);
                        v11 = 1;
                    }
                    HEManager_PopState(&a1->heManager, v7);
                    ServerControl_CheckFainted(a1, mon);
                }
            }
            if (v11)
            {
                ServerControl_ViewEffect(a1, 597, 6, 6, 0, 0);
            }
            return ServerControl_CheckExpGet(a1);
        }
    }
}