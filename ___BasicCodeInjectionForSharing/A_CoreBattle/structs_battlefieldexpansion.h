#ifndef __BATTLE_EXPANSION_H
#define __BATTLE_EXPANSION_H

#include "structs_new.h"

// NEW BATTLE HANDLE EFFECTS
#define EFFECT_CHANGE_TERRAIN 60
#define EFFECT_REMOVE_TERRAIN 61

// NEW BATTLE EVENTS
#define EVENT_ACCURACY_MISS EVENT_MOVE_ACCURACY_STAGE
#define EVENT_ABILITY_CHANGE_CHECK_FAIL EVENT_BEFORE_ABILITY_CHANGE
#define EVENT_TERRAIN_CHECK EVENT_WEATHER_CHECK
#define EVENT_TERRAIN_CHANGE EVENT_WEATHER_CHANGE
#define EVENT_TERRAIN_CHANGE_FAIL EVENT_AFTER_WEATHER_CHANGE
#define EVENT_AFTER_TERRAIN_CHANGE EVENT_AFTER_ABILITY_CHANGE
#define EVENT_MOVE_TERRAIN_TURN_COUNT EVENT_MOVE_WEATHER_TURN_COUNT
#define EVENT_GROUNDED_BY_GRAVITY EVENT_CHECK_FLOATING
#define EVENT_USE_ITEM_AFTER EVENT_USE_ITEM
// NEW BATTLE EVENT VARS (might need to change them if the event uses VAR_7, 8 & 9 like move seq start)
#define NEW_VAR_MON_ID VAR_7
#define NEW_VAR_ATTACKING_MON VAR_8
#define NEW_VAR_DEFENDING_MON VAR_9
// NEW BATTLE EVENT CHECKS
#define SET_UP_NEW_EVENT                                 \
    BattleEventVar_SetConstValue(VAR_MON_ID, -1);        \
    BattleEventVar_SetConstValue(VAR_ATTACKING_MON, -1); \
    BattleEventVar_SetConstValue(VAR_DEFENDING_MON, -1)
#define IS_NOT_NEW_EVENT BattleEventVar_GetValue(VAR_MON_ID) != -1 || BattleEventVar_GetValue(VAR_ATTACKING_MON) != -1 || BattleEventVar_GetValue(VAR_DEFENDING_MON) != -1

// NEW SIDE EFFECTS
#define DEFAULT_SIDE_CONDITION_AMOUNT 14
#define SIDEEFF_STICKY_WEB 14
#define SIDE_CONDITION_AMOUNT 15

// NEW FIELD EFFECTS
#define DEFAULT_FIELD_EFFECT_AMOUNT 8
#define FLDEFF_TERRAIN 8
#define FIELD_EFFECT_AMOUNT 9

#define DEFAULT_ABILITY_AMOUNT 165
#define ABIL165_AROMAVEIL 165
#define ABIL166_FLOWERVEIL 166
#define ABIL167_CHEEKPOUCH 167

// OTHER STUFF
#define FORCE_FAIL_MESSAGE 2 // ServerControl_AddConditionCheckFail

// BATTLE ENUMS
// BattleField Expansion

//
//
//    BATTLE FIELD EXPANSION
//
//
//
enum Terrain
{
    TERRAIN_NULL = 0,
    TERRAIN_ELECTRIC = 1,
    TERRAIN_GRASSY = 2,
    TERRAIN_MISTY = 3,
    TERRAIN_PSYCHIC = 4,
};

enum FieldEffect
{
    FLDEFF_WEATHER = 0x0,
    FLDEFF_TRICK_ROOM = 0x1,
    FLDEFF_GRAVITY = 0x2,
    FLDEFF_IMPRISON = 0x3,
    FLDEFF_WATER_SPORT = 0x4,
    FLDEFF_MUD_SPORT = 0x5,
    FLDEFF_WONDER_ROOM = 0x6,
    FLDEFF_MAGIC_ROOM = 0x7,
};

enum BattleEventPriority
{
    EVENTPRI_MOVE_DEFAULT = 0x0,
    EVENTPRI_POS_DEFAULT = 0x1,
    EVENTPRI_SIDE_DEFAULT = 0x2,
    EVENTPRI_FIELD_DEFAULT = 0x3,
    EVENTPRI_ABILITY_POISON_TOUCH = 0x4,
    EVENTPRI_ABILITY_DEFAULT = 0x5,
    EVENTPRI_ITEM_DEFAULT = 0x6,
    EVENTPRI_ABILITY_STALL = 0x7,
    EVENTPRI_MAX = 0x8,
};

struct HandlerParam_RemoveFieldEffect
{
    HandlerParam_Header header;
    BattleFieldEffect effect;
};

struct SWAN_ALIGNED(4) HandlerParam_AddFieldEffect
{
    HandlerParam_Header header;
    BattleFieldEffect effect;
    ConditionData cont;
    u8 fAddDependPoke;
    char field_D;
    char field_E;
    char field_F;
    HandlerParam_StrParams exStr;
};

struct BattleSideCondition
{
    BattleEventItem *battleEventItem;
    ConditionData conditionData;
    int TurnCounter;
    int Count;
};

struct BattleSideStatus
{
    BattleSideCondition Conditions[14];
};

struct BattleSideManager
{
    BattleSideStatus Sides[2];
};

// struct FIELD_TRIGGERTABLE
// {
//     BattleEventType triggerValue;
//     FIELD_HANDLER_FUNC function;
// };
typedef void (*BattleEventHandler)(BattleEventItem *item, ServerFlow *ServerFlow, int pokemonID, int *work);

struct BattleEventHandlerTableEntry
{
    BattleEventType EventType;
    BattleEventHandler Handler;
};


struct HandlerParam_SendLast
{
    HandlerParam_Header header;
    u8 pokeID;
    HandlerParam_StrParams exStr;
};

struct HandlerParam_InterruptPoke
{
    HandlerParam_Header header;
    u8 pokeID;
    HandlerParam_StrParams exStr;
};

typedef BattleEventHandlerTableEntry *(*FieldEffectEventAddFunc)(int *);

struct FieldEffectEventAddTable
{
    FieldEffect effect;
    FieldEffectEventAddFunc func;
};

typedef BattleEventHandlerTableEntry *(*SideEffectEventAddFunc)(int *);

struct SideEffectEventAddTable
{
    // actual data-type -> enum SideEffect
    int sideEffect;
    SideEffectEventAddFunc func;
    int maxCount;
};

#endif
