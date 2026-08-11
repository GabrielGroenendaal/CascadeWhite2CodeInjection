
#include "settings.h"
#include "codeinjection_new.h"
#include "kPrint.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)
#define STAT_CHANGE_INTIMIDATE_FLAG 0x80000000
#define STAT_CHANGE_HOSTILE_FLAG 0x40000000
#define STAT_CHANGE_OPPORTUNIST_FLAG 0x20000000
#define STAT_CHANGE_PARTING_SHOT_FLAG 0x10000000

    // 0: not using override contact mechanics 
    // 1: using override contact mechanics 
    // 2: testing out the new static/flame body/poisontouch stuff
#define USING_ILLUSION false
#define TRYING_BATTLESCAN_EXPANSION false
#define USING_OVERRIDE_CONTACT false
#define CHANGING_DAMP false 
#define CHANGING_CONTACT_ABILITIES true 
#define CONSOLIDATING_ATES false 
// Uses esdb_newBattle.yml


#pragma region Notes
/* 
    
    ABILITY TABLE EDITS:    
        Somewhere in the code exists a table like the Move handle effect table. 
        We are going to edit this table to change the pointers for a bunch of abilities. 
        
        Luckily we don't need to carefully manage handlers too much. They're pretty plentiful. 

        [ ATE ABILITIES ]
            I mostly want to combine these to save space. 

            Refrigerate: 
                Double check that refrigerate doesn'tt work properly right now. If it does i'm even more confused .

                This is not currently assigned in the code 
                It's in theory attached to telepathy fsr. 
                Current Abil: 140 (8C in hex)
                Points To: EventAddTelepathy (89 1B 1C 02)
                Change to: EventAddStickyHold (39 11 1C 02) 
                
            Oblivious: 
                Abil No: 12 (0C in hex)
                Points To: EventAddOblivious (A5 EE 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)

            Super Luck: 
                Abil No: 105 (69 in hex)
                Points To: EventAddSuperLuck (55 F4 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)
            
            Magma Armor: 
                Abil No: 40 (28 in hex)
                Points To: EventAddMagmaArmor (21 ED 1B 02)
                Change to: EventAddStickyHold (39 11 1C 02)


        
        [ CLONE ABILITIES ]
            These abilities have the same effect as other abilities but a unique ABiL ID. 
            That's limited real estate so we should combine them. 

            Vital Spirit: 
                Abil No: 72 (48 in hex)
                Points To: EventAddInsomnia (E1 EC 1B 02)
                Change To: EventAddShieldDust (81 F2 1B 02)
                Name: Vital Spirit -> Resilient
            
            Illuminate
                Abil No. 35 (23 in hex)
                Points To: None 
                Change To: EventAddCompoundeyes (A5 E2 1B 02)
*/
/* 
    See if we can implement the following changes as hex edits to save space. 
    
        - Regenerator Nerf 
        - Stench Buff 
        - Dry Skin Nerf
        - Iron Fist Buff 
        - Weak Armor Buff 
*/
/* 
    ORPHANED ABILITY HANDLERS 

    Steadfast isn't being used 
    Defeatist isn't being used 
    Liquid Ooze isn't being used 
    Zen Mode isn't being used 
    Color Change isn't being used
    Ballistics isn't being used 
    Slow Start is barely being used 
    Natural Cure is barely being used 
    Shed Skin is barely being used 
    Overcoat is barely being used 

*/
#pragma endregion 


#pragma region definitions

extern "C" u8 SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u16 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)  return 1;
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

const u16 StrongJawMoves[12] = {
    MOVE044_BITE,
    MOVE158_HYPER_FANG,
    MOVE162_SUPER_FANG,
    MOVE170_SNAP_TRAP,
    MOVE265_PSYCHIC_FANGS,
    MOVE305_POISON_FANG,
    MOVE422_THUNDER_FANG,
    MOVE423_ICE_FANG,
    MOVE424_FIRE_FANG,
    MOVE242_CRUNCH,
    MOVE141_LEECH_LIFE,
    MOVE030_DEVOUR};

// const u16 WindMoves[17] = {
//     MOVE403_AIR_SLASH,
//     MOVE542_HURRICANE,
//     MOVE257_HEAT_WAVE,
//     MOVE466_OMINOUS_WIND,
//     MOVE318_SILVER_WIND,
//     MOVE016_GUST,
//     MOVE059_BLIZZARD,
//     MOVE379_PETAL_BLIZZARD,
//     MOVE511_FAIRY_WIND,
//     MOVE180_DIAMOND_STORM,
//     MOVE013_RAZOR_WINDS,
//     MOVE177_AEROBLAST,
//     MOVE196_ICY_WIND,
//     MOVE366_TAILWIND,
//     MOVE239_TWISTER,
//     MOVE018_WHIRLWIND,
//     MOVE314_AIR_CUTTER};

unsigned __int16 MOLD_BREAKER_AFFECTED_ABILITIES[51] = {
    ABIL025_WONDER_GUARD,
    ABIL043_AMPLIFIER,
    ABIL026_LEVITATE,
    ABIL008_SAND_VEIL,
    ABIL081_SNOW_CLOAK,
    ABIL011_WATER_ABSORB,
    ABIL004_BATTLE_ARMOR,
    ABIL031_LIGHTNING_ROD,
    ABIL114_STORM_DRAIN,
    ABIL075_SHELL_ARMOR,
    ABIL109_UNAWARE,
    ABIL021_WELL_BAKED_BODY,
    ABIL086_SIMPLE,
    ABIL077_SLUSH_RUSH,
    ABIL116_SOLID_ROCK,
    ABIL111_FILTER,
    ABIL018_FLASH_FIRE,
    ABIL078_MOTOR_DRIVE,
    ABIL063_MARVEL_SCALE,
    ABIL047_THICK_FAT,
    ABIL085_HEATPROOF,
    ABIL073_STRONG_BODY,
    ABIL029_CLEAR_BODY,
    ABIL051_WIND_RIDER,
    ABIL052_HYPER_CUTTER,
    ABIL039_INNER_FOCUS,
    ABIL019_SHIELD_DUST,
    ABIL005_STURDY,
    ABIL006_BULLETPROOF,
    ABIL102_FUR_COAT,
    ABIL015_THUNDER_ARMOR,
    ABIL072_RESILIENT,
    ABIL017_FLUFFY,
    ABIL126_CONTRARY,
    ABIL132_FRIEND_GUARD,
    ABIL136_MULTISCALE,
    ABIL140_ICE_SCALES,
    ABIL147_WONDER_SKIN,
    ABIL156_MAGIC_BOUNCE,
    ABIL157_SAP_SIPPER,
    ABIL010_VOLT_ABSORB,
    ABIL087_DRY_SKIN,
    ABIL122_FLOWER_GIFT,
    ABIL134_HEAVY_METAL,
    ABIL135_LIGHT_METAL,
    ABIL143_POISON_TOUCH,
    ABIL113_SCRAPPY,
    ABIL056_GOOEY,
    ABIL009_STATIC,
    ABIL049_FLAME_BODY,
    ABIL027_EFFECT_SPORE,
};

const u16 HyperCutterMoves[28] = {
    MOVE421_SHADOW_CLAW, MOVE533_SACRED_SWORD, MOVE534_RAZOR_SHELL, MOVE530_DUAL_CHOP, MOVE529_DRILL_RUN, MOVE554_SOLAR_BLADE,
    MOVE440_CROSS_POISON, MOVE427_PSYCHO_CUT, MOVE404_X_SCISSOR, MOVE400_NIGHT_SLASH, MOVE403_AIR_SLASH, MOVE384_PSYBLADE,
    MOVE348_LEAF_BLADE, MOVE337_DRAGON_CLAW, MOVE332_AERIAL_ACE, MOVE314_AIR_CUTTER, MOVE306_CRUSH_CLAW, MOVE232_METAL_CLAW,
    MOVE163_SLASH, MOVE154_FURY_SWIPES, MOVE065_DRILL_PECK, MOVE013_RAZOR_WINDS, MOVE210_FURY_CUTTER, MOVE015_CUT,
    MOVE075_RAZOR_LEAF, MOVE548_SECRET_SWORD, MOVE032_HORN_DRILL, MOVE064_AQUA_CUTTER};

// const u16 BulletproofMoves[21] = {
//     MOVE491_ACID_SPRAY,
//     MOVE396_AURA_SPHERE,
//     MOVE140_BARRAGE,
//     MOVE331_BULLET_SEED,
//     MOVE121_EGG_BOMB,
//     MOVE486_ELECTRO_BALL,
//     MOVE412_ENERGY_BALL,
//     MOVE411_FOCUS_BLAST,
//     MOVE360_GYRO_BALL,
//     MOVE301_BOOMBURST,
//     MOVE443_MAGNET_BOMB,
//     MOVE426_MUD_BOMB,
//     MOVE190_OCTAZOOKA,
//     MOVE461_POLLEN_PUFF,
//     MOVE350_ROCK_BLAST,
//     MOVE439_ROCK_WRECKER,
//     MOVE402_SEED_BOMB,
//     MOVE247_SHADOW_BALL,
//     MOVE188_SLUDGE_BOMB,
//     MOVE311_WEATHER_BALL,
//     MOVE192_ZAP_CANNON};

const u16 nonStatusProtectMoves[4] = {
    MOVE376_SPIKY_SHIELD,
    MOVE462_SILK_TRAP,
    MOVE559_BANEFUL_BUNKER,
    MOVE262_OBSTRUCT};

#pragma endregion

extern "C"
{

#pragma region helpers

    int checkHigher(int a1, int a2)
    {
        if (a1 < a2)
        {
            return a2;
        }
        return a1;
    }
    // bool overrideContact(BattleMon *a1, MoveID a2)
    // {
    //     if (BattleMon_GetHeldItem(a1) == IT0293_SAFETY_GOGGLES || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
    //         return true;
    //     return false;
    // }
    
    typedef struct
    {
        BattleEventType triggerValue;
        ABILITY_HANDLER_FUNC function;
    } ABILITY_TRIGGERTABLE;

    bool checksIfWildBattle(ServerFlow *a1)
    {
        return a1->mainModule->btlSetup->btlType == 0;
    }

    bool checkIfConsumableItem(int a1)
    {
        // There is surely something we could do to simplify this
        return (PML_ItemIsBerry(a1) ||
                a1 == IT0290_FAIRY_GEM ||
                a1 == IT0043_BERRY_JUICE ||
                (a1 >= IT0545_ABSORB_BULB && a1 <= IT0564_NORMAL_GEM) ||
                a1 == IT0291_WEAKNESS_POLICY ||
                a1 == IT0274_MYSTERY_DEVICE ||
                a1 == IT0542_RED_CARD ||
                a1 == IT0292_CLRS_BOOSTER ||
                a1 == IT0294_PROTO_BOOSTER ||
                a1 == IT0286_CLRS_ARMOR ||
                a1 == IT0254_PROTO_ARMOR ||
                a1 == IT0315_PROTO_ACCELERATOR ||
                a1 == IT0318_CLRS_ACCELERATOR ||
                a1 == IT0314_CLRS_INVENTION ||
                a1 == IT0539_EJECT_PACK ||
                a1 == IT0547_EJECT_BUTTON ||
                a1 == IT0275_FOCUS_SASH ||
                a1 == IT0219_MENTAL_HERB ||
                a1 == IT0214_WHITE_HERB ||
                a1 == IT0271_POWER_HERB ||
                a1 == IT0541_AIR_BALLOON ||
                a1 == IT0136_TRICKSTER_HERB ||
                a1 == IT0230_FOCUS_BAND ||
                a1 == IT0299_TERA_C_BAND ||
                a1 == IT0288_STICKY_BARB ||
                a1 == IT0273_FLAME_ORB ||
                a1 == IT0272_TOXIC_ORB ||
                a1 == IT0306_TERA_B_POLICY ||
                a1 == IT0256_BLUNDER_POLICY ||
                a1 == IT0305_TERA_W_POLICY ||
                a1 == IT0302_TERA_SASH ||
                a1 == IT0304_TERA_CLAW ||
                a1 == IT0217_QUICK_CLAW ||
                a1 == IT0281_BLACK_SLUDGE ||
                a1 == IT0228_TERA_GEM ||
                a1 == IT0234_LEFTOVERS ||
                a1 == IT0311_TERA_LEFTOVERS || a1 == IT0255_ATTACK_INSURANCE || a1 == IT0309_TERA_INSURANCE);
    }

    uint8_t getOverheatByte(BattleMon *a1)
    {
        return *((uint8_t *)a1 + 0xEA);
    }
    void setOverheatByte(BattleMon *a1, int a2)
    {
        *((uint8_t *)a1 + 0xEA) = a2;
    }
    uint8_t getOverheatLastTurnByte(BattleMon *a1)
    {
        return *((uint8_t *)a1 + 0xEB);
    }
    void setOverheatLastTurnByte(BattleMon *a1, int a2)
    {
        *((uint8_t *)a1 + 0xEB) = a2;
    }

#pragma endregion


#pragma region newStuff 
    // RKS System 
    void HandlerRKSSystem(BattleEventItem * item, ServerFlow * serverFlow, u32 pokemonSlot, u32 * work) {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID)) {
            BattleMon* currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            u8 type = PokeTypePair_GetType1(BattleMon_GetPokeType(currentMon));
            u8 moveType = PML_MoveGetType(Move_GetID(currentMon, 0));
            if (type != moveType){
                HandlerParam_ChangeForm* changeForm;
                changeForm = (HandlerParam_ChangeForm*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
                changeForm->header.flags |= 0x800000;
                changeForm->monID = pokemonSlot;
                changeForm->form = moveType;
                BattleHandler_StrSetup(&changeForm->strParam, 1u, 230); // CHANGE THIS MESSAGE ID
                BattleHandler_AddArg(&changeForm->strParam, pokemonSlot);
                BattleHandler_PopWork(serverFlow, changeForm);
            }
        }
    }
    ABILITY_TRIGGERTABLE RKSHandlers[]{
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerRKSSystem},
        {EVENT_TURN_CHECK_DONE, (ABILITY_HANDLER_FUNC)HandlerRKSSystem},
    };
    ABILITY_TRIGGERTABLE * THUMB_BRANCH_EventAddColorChange(_DWORD * a1) {
        *a1 = 2;
        return RKSHandlers;
    }
    
    // MAJESTIC WARD 
    ABILITY_TRIGGERTABLE * THUMB_BRANCH_EventAddDefeatist(_DWORD * a1) {
        *a1 = 0;
        return RKSHandlers;
    }

    // ICE SCALES 
    void HandlerIceScales(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) == 2)
        {
            BattleEventVar_MulValue(VAR_RATIO, 2048);
        }
    }
    ABILITY_TRIGGERTABLE IceScalesHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerIceScales}, // 22
    };
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddWonderSkin(_DWORD *a1)
    {
        *a1 = 1;
        return IceScalesHandlers;
    }

    #if CHANGING_CONTACT_ABILITIES  
    void THUMB_BRANCH_CommonContactStatusAbility(
        ServerFlow *a1,
        unsigned int *a2,
        MoveCondition a3,
        ConditionData a4,
        unsigned __int8 a5)
    {
        unsigned __int16 Value; // r0
        BattleMon *attackingMon;
        HandlerParam_AddCondition *v9; // r5
        u8 monInQuestion = (((int)a2 == BattleEventVar_GetValue(VAR_DEFENDING_MON)) ? BattleEventVar_GetValue(VAR_ATTACKING_MON) : ((int)a2 == BattleEventVar_GetValue(VAR_ATTACKING_MON)) ? BattleEventVar_GetValue(VAR_DEFENDING_MON) : 255);
        if (monInQuestion != 255 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT) && !AbilityEvent_RollEffectChance((int)a1, a5))
            {
                v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, (int)a2);
                v9->header.flags |= 0x800000u;
                v9->sickID = a3;
                v9->sickCont = a4;
                v9->fAlmost = 0;
                v9->pokeID = monInQuestion;
                BattleHandler_PopWork(a1, v9);
            }
        }
    }
    #endif 

#pragma endregion 


#pragma region -AteAbilities

    #if CONSOLIDATING_ATES
    u8 ateGetType(u16 subID){
        if (subID == ABIL040_PIXILATE) return TYPE_FAIRY; 
        if (subID == ABIL105_MOISTURIZE) return TYPE_WATER; 
        if (subID == ABIL012_GALVANIZE) return TYPE_ELECTRIC; 
        if (subID == ABIL048_REFRIGERATE) return TYPE_ICE; 
        if (subID == ABIL060_AERILATE) return TYPE_FLYING; 
        return 0;
    }
    void HandlerAtePower(BattleEventItem* a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if ((PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == ateGetType(BattleEventItem_GetSubID(a1))) // physical
            {
                BattleEventVar_MulValue(VAR_RATIO, 4915); // 20% boost
            }
        }
    }
    void HandlerAteType(BattleEventItem* a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)   BattleEventVar_RewriteValue(VAR_MOVE_TYPE, BattleEventItem_GetSubID(a1));
        }
    }
    ABILITY_TRIGGERTABLE AteHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerAteType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStickyHold(_DWORD *a1)
    {
        *a1 = 2;
        return AteHandlers;
    }
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSuperLuck(_DWORD *a1)
    {
        *a1 = 2;
        return AteHandlers;
    }
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddTelepathy(_DWORD *a1)
    {
        *a1 = 2;
        return AteHandlers;
    }
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddMagmaArmor(_DWORD *a1)
    {
        *a1 = 2;
        return AteHandlers;
    }
    #else 
    void HandlerPixilateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)  BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_FAIRY);
        }
    }
    void HandlerAtePower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) // physical
            {
                BattleEventVar_MulValue(VAR_RATIO, 4915); // 20% boost
            }
        }
    }
    ABILITY_TRIGGERTABLE PixilateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerPixilateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddMagmaArmor(_DWORD *a1)
    {
        *a1 = 2;
        return PixilateHandlers;
    }

    void HandlerHydrateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID)){
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)  BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_WATER);
        }
    }
    ABILITY_TRIGGERTABLE HydrateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerHydrateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSuperLuck(_DWORD *a1)
    {
        *a1 = 2;
        return HydrateHandlers;
    }

    void HandlerAerilateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_FLYING);
            }
        }
    }
    ABILITY_TRIGGERTABLE AerilateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerAerilateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStickyHold(_DWORD *a1)
    {
        *a1 = 2;
        return AerilateHandlers;
    }

    void HandlerRefrigerateType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ICE);
            }
        }
    }
    ABILITY_TRIGGERTABLE RefrigerateHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerRefrigerateType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddTelepathy(_DWORD *a1)
    {
        *a1 = 2;
        return RefrigerateHandlers;
    }

    void HandlerGalvanizeType(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
            {
                BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_ELECTRIC);
            }
        }
    }
    ABILITY_TRIGGERTABLE GalvanizeHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerGalvanizeType}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerAtePower}};
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddOblivious(_DWORD *a1)
    {
        *a1 = 2;
        return GalvanizeHandlers;
    }
    #endif

#pragma endregion


#pragma region HandlersWeCouldHandleInCode
    // CHANGE THIS 
    // See if we can implement this in the code itself.
    // Heatproof
    void THUMB_BRANCH_HandlerHeatproofPower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == 9)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 1024);
            }
        }
    }
    /* Regenerator Nerf */
    // CHANGE THIS 
    // see if we can implement this directly in overlay_167 instead. 
    void THUMB_BRANCH_SAFESTACK_HandlerRegenerator(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;      // r6
        unsigned int v6;           // r4
        unsigned int v7;           // r0
        HandlerParam_ChangeHP *v8; // r0
        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            if (!BattleMon_IsFainted(PokeParam) && !BattleMon_IsFullHP(PokeParam))
            {
                v6 = DivideMaxHPZeroCheck(PokeParam, 4u);
                v7 = BattleMon_GetValue(PokeParam, VALUE_MAX_HP) - BattleMon_GetValue(PokeParam, VALUE_CURRENT_HP);
                if (v6 > v7)
                {
                    v6 = v7;
                }
                v8 = (HandlerParam_ChangeHP *)BattleHandler_PushWork(a2, EFFECT_CHANGEHP, (int)a3);
                v8->pokeID[0] = (int)a3;
                v8->volume[0] = v6;
                v8->poke_cnt = 1;
                v8->fEffectDisable = 1;
                BattleHandler_PopWork(a2, v8);
            }
        }
    }
    /* Iron Fist Buff*/
    // CHANGE THIS 
    // See if we can edit this directly in the code instead. 
    void THUMB_BRANCH_HandlerIronFist(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_PUNCH))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);
            }
        }
    }
    // WEAK ARMOR
    void THUMB_BRANCH_HandlerWeakArmor(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *PokeParam;             // r7
        u8 v6;                           // r6
        HandlerParam_ChangeStatStage *v7; // r0
        HandlerParam_ChangeStatStage *v8; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            v6 = 0;
            if (BattleMon_IsStatChangeValid(PokeParam, 2u, -1) || BattleMon_IsStatChangeValid(PokeParam, 5u, 2))
            {
                v6 = 1;
            }
            if (v6)
            {
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v7->poke_cnt = 1;
                    v7->pokeID[0] = (unsigned int)a3;
                    v7->fMoveAnimation = 1;
                    v7->rankType = STATSTAGE_DEFENSE;
                    v7->rankVolume = -1;
                    BattleHandler_PopWork(a2, v7);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)a3;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = 2;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
    }
#pragma endregion 

#pragma region Contact
#if USING_OVERRIDE_CONTACT
    bool overrideContact(BattleMon *a1, MoveID a2)
    {
        if (BattleMon_GetHeldItem(a1) == IT0293_SAFETY_GOGGLES || BattleMon_GetValue(a1, VALUE_EFFECTIVE_ABILITY) == ABIL142_OVERCOAT)
            return true;
        return false;
    }

    void THUMB_BRANCH_CommonContactStatusAbility(
        ServerFlow *a1,
        unsigned int *a2,
        MoveCondition a3,
        ConditionData a4,
        unsigned __int8 a5)
    {
        unsigned __int16 Value; // r0
        BattleMon *attackingMon;
        HandlerParam_AddCondition *v9; // r5
        u8 monInQuestion = (((int)a2 == BattleEventVar_GetValue(VAR_DEFENDING_MON)) ? BattleEventVar_GetValue(VAR_ATTACKING_MON) : ((int)a2 == BattleEventVar_GetValue(VAR_ATTACKING_MON)) ? BattleEventVar_GetValue(VAR_DEFENDING_MON) : 255);
        if (monInQuestion != 255 && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT) && !AbilityEvent_RollEffectChance((int)a1, a5))
            {
                v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, (int)a2);
                v9->header.flags |= 0x800000u;
                v9->sickID = a3;
                v9->sickCont = a4;
                v9->fAlmost = 0;
                v9->pokeID = monInQuestion;
                BattleHandler_PopWork(a1, v9);
            }
        }
    }
    void THUMB_BRANCH_HandlerMummy(int a1, ServerFlow *a2, unsigned int a3)
    {
        unsigned __int16 Value;         // r0
        unsigned int v6;                // r6
        BattleMon *BattleMon;           // r0
        HandlerParam_ChangeAbility *v8; // r4

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG) && !Handler_CheckMatchup((int)a2))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v6);

                if (overrideContact(BattleMon, (MoveID)Value))
                    return;

                if (BattleMon_GetValue(BattleMon, VALUE_ABILITY) != 152)
                {
                    v8 = (HandlerParam_ChangeAbility *)BattleHandler_PushWork(a2, EFFECT_CHANGEABILITY, a3);
                    v8->abilityID = 152;
                    v8->pokeID = v6;
                    BattleHandler_StrSetup(&v8->exStr, 2u, 463);
                    BattleHandler_AddArg(&v8->exStr, v8->pokeID);
                    if (!MainModule_IsAllyMonID(a3, v6))
                    {
                        v8->header.flags |= 0x800000u;
                    }
                    BattleHandler_PopWork(a2, v8);
                }
            }
        }
    }
    
    void THUMB_BRANCH_HandlerRoughSkin(int a1, ServerFlow *a2, unsigned int *a3)
    {
        unsigned __int16 Value;  // r0
        int v6;                  // r6
        BattleMon *BattleMon;    // r7
        HandlerParam_Damage *v8; // r4

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_ID);
            if (getMoveFlag(Value, FLAG_CONTACT))
            {
                v6 = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                BattleMon = Handler_GetBattleMon(a2, v6);

                if (overrideContact(BattleMon, (MoveID)Value))
                    return;

                if (!BattleMon_IsFainted(BattleMon))
                {
                    v8 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                    v8->header.flags |= 0x800000u;
                    v8->pokeID = v6;
                    v8->damage = DivideMaxHPZeroCheck(BattleMon, 8u);
                    BattleHandler_StrSetup(&v8->exStr, 2u, 430);
                    BattleHandler_AddArg(&v8->exStr, v6);
                    BattleHandler_PopWork(a2, v8);
                }
            }
        }
    }


#else 
    bool overrideContact(BattleMon *a1, MoveID a2)
    {
        return false;
    }
#endif
    void THUMB_BRANCH_HandlerEffectSpore(int a1, ServerFlow *a2, unsigned int *a3)
    {
        u8 v5;  // r0
        MoveCondition v6; // r4
        ConditionData v7; // r0
        BattleMon *mon;
        HandlerParam_AddCondition *v9; // r5
        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            mon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
            if (!BattleMon_HasType(mon, TYPE_GRASS) && BattleMon_GetHeldItem(mon) != IT0293_SAFETY_GOGGLES && BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY) != ABIL142_OVERCOAT)
            {
                v5 = BattleRandom(30u);
                if (v5 <= 20)
                {
                    v6 = CONDITION_PARALYSIS;
                    if (v5 <= 10)
                    {
                        v6 = CONDITION_SLEEP;
                    }
                }
                else
                {
                    v6 = CONDITION_POISON;
                }
                v7.raw = MakeBasicStatus(v6).raw;
                if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
                {
                    v9 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, (int)a3);
                    v9->header.flags |= 0x800000u;
                    v9->sickID = v6;
                    v9->sickCont = v7;
                    v9->fAlmost = 0;
                    v9->pokeID = BattleEventVar_GetValue(VAR_ATTACKING_MON);
                    BattleHandler_PopWork(a2, v9);
                }
            }
        }
    }
    void THUMB_BRANCH_HandlerCuteCharm(int a1, ServerFlow *a2, unsigned int *a3)
    {
        u8 v6;                           // r6
        BattleMon *PokeParam;             // r7
        HandlerParam_ChangeStatStage *v8; // r4
        if (a3 == (unsigned int *)BattleEventVar_GetValue(VAR_DEFENDING_MON) && !BattleEventVar_GetValue(VAR_SUBSTITUTE_FLAG))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
            {
                v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
                PokeParam = Handler_GetBattleMon(a2, v6);
                if (!BattleMon_IsFainted(PokeParam))
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
                    v8->poke_cnt = 1;
                    v8->pokeID[0] = (unsigned int)v6;
                    v8->fMoveAnimation = 1;
                    v8->rankType = STATSTAGE_SPEED;
                    v8->rankVolume = -1;
                    v8->pad = STAT_CHANGE_HOSTILE_FLAG;
                    BattleHandler_PopWork(a2, v8);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
        return;
    }
#pragma endregion

#pragma region StatChanges
    extern "C" b32 THUMB_BRANCH_SAFESTACK_ServerEvent_CheckStatStageChangeSuccess(ServerFlow *serverFlow, BattleMon *affectedMon, StatStage statStage, u32 attackingSlot, int volume, u32 moveSerial)
    {
        BattleEventVar_Push();
        u32 affectedSlot = BattleMon_GetID(affectedMon);
        BattleEventVar_SetConstValue(VAR_MON_ID, affectedSlot);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, attackingSlot);
        BattleEventVar_SetConstValue(VAR_MOVE_EFFECT, statStage);
        BattleEventVar_SetConstValue(VAR_VOLUME, volume);
        BattleEventVar_SetValue(VAR_INTIMFLAG, (moveSerial & STAT_CHANGE_INTIMIDATE_FLAG) != 0); // Intimidate Flag
        BattleEventVar_SetValue(VAR_HOSTILEFLAG, (moveSerial & STAT_CHANGE_HOSTILE_FLAG) != 0);  // Mirror Armor Flag
        // BattleEventVar_SetValue(VAR_OPPORTUNIST_FLAG, (moveSerial & STAT_CHANGE_OPPORTUNIST_FLAG) != 0);   // Opportunist Flag
        BattleEventVar_SetValue(VAR_DELAY_ATTACK_FLAG, (moveSerial & STAT_CHANGE_PARTING_SHOT_FLAG) != 0); // Parting Shot Flag
        BattleEventVar_SetConstValue(VAR_STAT_STAGE_CHANGE_COUNT, moveSerial & 0x0FFFFFFF);
        BattleEventVar_SetRewriteOnceValue(VAR_MOVE_FAIL_FLAG, 0);
        BattleEvent_CallHandlers(serverFlow, EVENT_STAT_STAGE_CHANGE_LAST_CHECK);
        u32 failFlag = BattleEventVar_GetValue(VAR_MOVE_FAIL_FLAG);
        BattleEventVar_Pop();

        if (!failFlag)
        {
            return 1;
        }
        return 0;
    }

    extern "C" void THUMB_BRANCH_ServerEvent_StatStageChangeFail(ServerFlow *serverFlow, BattleMon *currentMon, u32 moveSerial)
    {
        BattleEventVar_Push();
        u32 currentSlot = BattleMon_GetID(currentMon);
        BattleEventVar_SetConstValue(VAR_MON_ID, currentSlot);
        BattleEventVar_SetConstValue(VAR_INTIMFLAG, (moveSerial & STAT_CHANGE_INTIMIDATE_FLAG) != 0); // Intimidate Flag
        BattleEventVar_SetConstValue(VAR_HOSTILEFLAG, (moveSerial & STAT_CHANGE_HOSTILE_FLAG) != 0);  // Mirror Armor Flag
        // BattleEventVar_SetConstValue(VAR_OPPORTUNIST_FLAG, (moveSerial & STAT_CHANGE_OPPORTUNIST_FLAG) != 0);   // Opportunist Flag
        BattleEventVar_SetConstValue(VAR_DELAY_ATTACK_FLAG, (moveSerial & STAT_CHANGE_PARTING_SHOT_FLAG) != 0); // Parting Shot Flag
        BattleEventVar_SetConstValue(VAR_STAT_STAGE_CHANGE_COUNT, moveSerial & 0x0FFFFFFF);
        BattleEvent_CallHandlers(serverFlow, EVENT_STAT_STAGE_CHANGE_FAIL);
        BattleEventVar_Pop();
    }

    void HandlerIntimidateCheck(int a1, int a2, int a3, int *a4)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_INTIMFLAG))
            {
                if (BattleEventVar_GetValue(VAR_VOLUME) < 0)
                {

                    *a4 = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                }
            }
        }
    }

    void HandlerIntimidateGuard(int a1, ServerFlow *a2, int pokemonSlot, int *a4)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID) && BattleEventVar_GetValue(VAR_INTIMFLAG))
        {
            BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, pokemonSlot);
            HandlerParam_Message *message;
            message = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, pokemonSlot);
            BattleHandler_StrSetup(&message->str, 2u, 201);
            BattleHandler_AddArg(&message->str, pokemonSlot);
            BattleHandler_PopWork(a2, message);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
        }
    }

    void THUMB_BRANCH_CommonStatDropGuardCheck(int a1, int a2, int *a3, int a4)
    {
        if (a2 == BattleEventVar_GetValue(VAR_MON_ID) && (a2 != BattleEventVar_GetValue(VAR_ATTACKING_MON) || BattleEventVar_GetValue(VAR_HOSTILEFLAG) == 1) && (a4 == 8 || a4 == BattleEventVar_GetValue(VAR_MOVE_EFFECT)) && BattleEventVar_GetValue(VAR_VOLUME) < 0)
        {
            *a3 = BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
        }
    };

#pragma endregion
   
#pragma region Multiscale

    // Multiscale
    // We are simply removing the damage logic here and hard coding it in the damage calc
    void THUMB_BRANCH_HandlerMultiscale(int a1, int a2, int a3)
    {
        return;
    }

#pragma endregion


#pragma region Defiant
    void THUMB_BRANCH_HandlerDefiant(int a1, ServerFlow *a2, unsigned int a3)
    {
        unsigned __int8 Value;             // r0
        HandlerParam_ChangeStatStage *v13; // r0

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            Value = BattleEventVar_GetValue(VAR_ATTACKING_MON);
            // k::Printf("Defiant Handler: The INTIM flag is %d\nAnd the Hostile flag is %d\n", BattleEventVar_GetValue(VAR_INTIMFLAG), BattleEventVar_GetValue(VAR_HOSTILEFLAG));
            if ((BattleEventVar_GetValue(VAR_INTIMFLAG) || BattleEventVar_GetValue(VAR_HOSTILEFLAG) || !MainModule_IsAllyMonID(a3, Value)) && BattleEventVar_GetValue(VAR_VOLUME) < 0)
            {
                v13 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                v13->header.flags |= 0x800000u;
                v13->rankType = STATSTAGE_ATTACK;
                v13->rankVolume = 2;
                v13->fMoveAnimation = 1;
                v13->poke_cnt = 1;
                v13->pokeID[0] = a3;
                BattleHandler_PopWork(a2, v13);
            }
        }
    }
#pragma endregion

#pragma region Scrappy

    ABILITY_TRIGGERTABLE ScrappyHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerScrappy}, // 22
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerIntimidateCheck},
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerIntimidateGuard},

        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerHyperCutterCheck},

        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerHyperCutterGuard}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddScrappy(_DWORD *a1)
    {
        *a1 = 5;
        return ScrappyHandlers;
    }

#pragma endregion

#pragma region HyperCutter

    void HandlerHyperCutterDamage(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (SEARCH_ARRAY(HyperCutterMoves, BattleEventVar_GetValue(VAR_MOVE_ID)))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
            }
        }
    }

    ABILITY_TRIGGERTABLE hyperCutterHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerHyperCutterDamage}, // 22
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerHyperCutterCheck},
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerHyperCutterGuard}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHyperCutter(_DWORD *a1)
    {
        *a1 = 3;
        return hyperCutterHandlers;
    }

#pragma endregion

#pragma region Colossal
    // int THUMB_BRANCH_ServerControl_IsGuaranteedHit(ServerFlow *a1, BattleMon *a2, BattleMon *a3)
    // {
    //     int ID;                    // r0
    //     int v8;                    // r0
    //     int ConditionAffectedMove; // r4
    //     ID = BattleMon_GetID(a2);
    //     if (sub_21A2EA0(&a1->posPoke, a1->mainModule, ID) && (BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY) == ABIL099_NO_GUARD))
    //     {
    //         return 1;
    //     }
    //     v8 = BattleMon_GetID(a3);
    //     if (sub_21A2EB0(&a1->posPoke, a1->mainModule, v8) && (BattleMon_GetValue(a3, VALUE_EFFECTIVE_ABILITY) == ABIL099_NO_GUARD || BattleMon_GetValue(a3, VALUE_EFFECTIVE_ABILITY) == ABIL080_COLOSSAL))
    //     {
    //         return 1;
    //     }
    //     if (BattleMon_CheckIfMoveCondition(a2, CONDITION_MUSTHIT))
    //     {
    //         return 1;
    //     }
    //     if (BattleMon_CheckIfMoveCondition(a2, CONDITION_LOCKON))
    //     {
    //         ConditionAffectedMove = BattleMon_GetConditionAffectedMove(a2, CONDITION_LOCKON);
    //         if (ConditionAffectedMove == BattleMon_GetID(a3))
    //         {
    //             return 1;
    //         }
    //     }
    //     return 0;
    // }

    // void ColossalDefense(int a1, ServerFlow *a2, int a3)
    // {
    //     if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
    //     {
    //         BattleEventVar_MulValue(VAR_RATIO, 3072);
    //     }
    // }

    // ABILITY_TRIGGERTABLE ColossalHandlers[] = {
    //     {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)ColossalDefense}, // 41
    // };

    // ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSteadfast(_DWORD *a1)
    // {
    //     *a1 = 1;
    //     return ColossalHandlers;
    // }

#pragma endregion

#pragma region Unaware

    void THUMB_BRANCH_HandlerUnawareDefenseRank(int a1, int a2, int a3)
    {
        if ( a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) || a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) )
        {
            BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
        }
    }

    void THUMB_BRANCH_HandlerUnawareAttackRank(int a1, int a2, int a3)
    {
        if ( a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) || a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) )
        {
            BattleEventVar_RewriteValue(VAR_GENERAL_USE_FLAG, 1);
        }
    }
    //     ABILITY_TRIGGERTABLE UnawareHandlers[] = {
    //         {EVENT_MOVE_ACCURACY_STAGE, (ABILITY_HANDLER_FUNC)HandlerUnawareHitRank}, // 41
    //         {EVENT_BEFORE_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerUnawareAttackRank},
    //         {EVENT_BEFORE_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerUnawareDefenseRank},
    //         {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerOwnTempoStatus},
    //         {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerOwnTempoAddStatusFailed},
    //         {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerOwnTempoCureStatus},
    //         {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerOwnTempoActionEnd},
    //     };
    //     ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddUnaware(_DWORD *a1)
    //     {
    //         *a1 = 7;
    //         return UnawareHandlers;
    //     }
#pragma endregion

#pragma region Filter/Solid Rock
    void THUMB_BRANCH_HandlerSolidRock(int a1, int a2, int a3)
    {
        u8 Value; // r0
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            Value = BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS);
            BattleEventVar_MulValue(VAR_RATIO, ((Value == EFFECTIVENESS_2) ? 3072 : ((Value == EFFECTIVENESS_4) ? 2304 : 4096)));
        }
    }
#pragma endregion

#pragma region HeavyMetal
    void HandlerHeavyMetalDefense(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1)
            {
                BattleEventVar_MulValue(VAR_RATIO, 6144);
            }
        }
    }

    void HandlerHeavyMetalSpeed(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID)) // hail
        {
            BattleEventVar_MulValue(VAR_RATIO, 2730);
        }
    }

    ABILITY_TRIGGERTABLE HeavyMetalHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerHeavyMetalDefense}, // 22
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerHeavyMetalSpeed},
        {EVENT_WEIGHT_RATIO, (ABILITY_HANDLER_FUNC)HandlerHeavyMetal},
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHeavyMetal(_DWORD *a1)
    {
        *a1 = 3;
        return HeavyMetalHandlers;
    }
#pragma endregion

#pragma region LightMetal
    void HandlerLightMetalDefense(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_CATEGORY) == 1)
            {

                BattleEventVar_MulValue(VAR_RATIO, 2730);
            }
        }
    }

    void HandlerLightMetalSpeed(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID)) // hail
        {
            BattleEventVar_MulValue(VAR_RATIO, 6144);
        }
    }

    ABILITY_TRIGGERTABLE LightMetalHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerLightMetalDefense}, // 22
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerLightMetalSpeed},
        {EVENT_WEIGHT_RATIO, (ABILITY_HANDLER_FUNC)HandlerLightMetal},
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLightMetal(_DWORD *a1)
    {
        *a1 = 3;
        return LightMetalHandlers;
    }
#pragma endregion

#pragma region MoldBreaker

    bool THUMB_BRANCH_SAFESTACK_HandlerMoldBreakerSkipCheck(int a1, int a2, BattleEventType a3, int a4, unsigned __int16 a5)
    {
        // k::Printf("Mold Breaker Skip Check: Event %d, Move %d, EVENT_MOVE_SEQUENCE_END = %d\nis mold breaker effected ability = %d\n", a3, a5, a3 == EVENT_MOVE_SEQUENCE_END, SEARCH_ARRAY(MOLD_BREAKER_AFFECTED_ABILITIES, a5));
        return (a3 == EVENT_MOVE_SEQUENCE_END && SEARCH_ARRAY(MOLD_BREAKER_AFFECTED_ABILITIES, a5));
    }
    void HandlerMoldBreakerPower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 4505);
        }
    }

    ABILITY_TRIGGERTABLE MoldBreakerHandlers[] = {
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerSwitchIn}, // 22
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerSwitchIn},
        {EVENT_MOVE_SEQUENCE_START, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerStart},
        {EVENT_MOVE_SEQUENCE_END, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerEnd},
        {EVENT_ABILITY_NULLIFIED, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerConfirm},
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerMoldBreakerPower}, // 6
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddMoldBreaker(_DWORD *a1)
    {
        *a1 = 6;
        return MoldBreakerHandlers;
    }
#pragma endregion

#pragma region SandForce
    void THUMB_BRANCH_HandlerSandForce(int a1, int a2, int a3)
    {
        u8 Value; // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            Value = BattleEventVar_GetValue(VAR_MOVE_TYPE);
            if (Value == 4 || Value == 5 || Value == 8)
            {
                if (Handler_GetWeather(a2) == 4)
                {
                    BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5734);
                }
                else
                {
                    BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 4915);
                }
            }
        }
    }
#pragma endregion

#pragma region CloudNine

    void HandlerAirLockAccuracy(int a1, int a2, unsigned int a3)
    {
        BattleEventVar_MulValue(VAR_RATIO, 4915);
    }

    ABILITY_TRIGGERTABLE AirLockHandlers[] = {
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerAirLockSwitchIn}, // 22
        {EVENT_WEATHER_CHECK, (ABILITY_HANDLER_FUNC)HandlerAirLockChangeWeather},
        {EVENT_MOVE_ACCURACY, (ABILITY_HANDLER_FUNC)HandlerAirLockAccuracy},
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddAirLock(_DWORD *a1)
    {
        *a1 = 3;
        return AirLockHandlers;
    }
#pragma endregion



#pragma region FurCoat
    void HanderFurCoat(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) == 1)
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
    }

    ABILITY_TRIGGERTABLE FurCoatHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HanderFurCoat},   // 22
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLeafGuard(_DWORD *a1)
    {
        *a1 = 2;
        return FurCoatHandlers;
    }
#pragma endregion

#pragma region Normalize

    void HandlerNormalizePower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (PML_MoveGetType(BattleEventVar_GetValue(VAR_MOVE_ID)) == TYPE_NORMAL) // physical
            {
                BattleEventVar_MulValue(VAR_RATIO, 5325); // 20% boost
            }
        }
        // if (BattleEventVar_GetValue(VAR_MOVE_TYPE) != TYPE_NORMAL)
        // {
        //     BattleEventVar_RewriteValue(VAR_MOVE_TYPE, TYPE_NORMAL);
        // }
    }
    void HandlerNormalizeEffectiveness(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_NORMAL)
        {
            BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 1);
        }
    }

    ABILITY_TRIGGERTABLE NormalizeHandlers[] = {
        {EVENT_MOVE_PARAM, (ABILITY_HANDLER_FUNC)HandlerNormalize}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerNormalizePower},
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerNormalizeEffectiveness},

    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddNormalize(_DWORD *a1)
    {
        *a1 = 3;
        return NormalizeHandlers;
    }

#pragma endregion

#pragma region PinchAbilites
    void THUMB_BRANCH_CommonLowHPBoostAbility(ServerFlow *a1, int a2, int a3)
    {
        BattleMon *BattleMon; // r6
        if (a2 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon = Handler_GetBattleMon(a1, a2);
            if (a3 == BattleEventVar_GetValue(VAR_MOVE_TYPE))
            {
                BattleEventVar_MulValue(VAR_RATIO, ((BattleMon_GetValue(BattleMon, VALUE_CURRENT_HP) <= DivideMaxHp(BattleMon, 3u)) ? 6144 : 5120));
            }
        }
    }
#pragma endregion

#pragma region Infiltrator
    void HandlerInfiltratorPower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_TYPE_EFFECTIVENESS) > 3)
        {
            BattleEventVar_MulValue(VAR_RATIO, 4915);
        }
    }

    ABILITY_TRIGGERTABLE InfiltratorHandlers[] = {
        {EVENT_MOVE_SEQUENCE_START, (ABILITY_HANDLER_FUNC)HandlerInfiltratorStart},
        {EVENT_MOVE_SEQUENCE_END, (ABILITY_HANDLER_FUNC)HandlerInfiltratorEnd},
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerInfiltratorPower}, // 6
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddInfiltrator(_DWORD *a1)
    {
        *a1 = 3;
        return InfiltratorHandlers;
    }
#pragma endregion

#pragma region Merciless
    void MercilessOffense(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (BattleMon_GetStatus(Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON))))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5120);
            }
        }
    }

    void MercilessDefense(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleMon_GetStatus(Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON))))
            {
                BattleEventVar_MulValue(VAR_RATIO, 3072);
            }
        }
    }

    ABILITY_TRIGGERTABLE MercilessHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)MercilessOffense},               // 41
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)MercilessDefense}, // 41
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddWaterVeil(_DWORD *a1)
    {
        *a1 = 2;
        return MercilessHandlers;
    }
#pragma endregion

#pragma region StrongJaw

    void THUMB_BRANCH_HandlerSuperFang(int a1, ServerFlow *a2, int a3)
    {
        unsigned __int8 Value; // r0
        BattleMon *BattleMon;  // r0
        unsigned int v8;       // r0
        int v9;                // r1

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            Value = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            BattleMon = Handler_GetBattleMon(a2, Value);
            v8 = BattleMon_GetValue(BattleMon, VALUE_CURRENT_HP);
            v9 = (v8 + (v8 >> 31)) << 15 >> 16;
            if (!v9)
            {
                v9 = 1;
            }
            if (BattleMon_GetValue(Handler_GetBattleMon(a2, a3), VALUE_EFFECTIVE_ABILITY) == ABIL093_STRONG_JAW)
            {
                v9 = v9 + (v9 >> 1);
            }
            BattleEventVar_RewriteValue(VAR_FIXED_DAMAGE, v9);
        }
    }

    void HandlerStrongJaw(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (SEARCH_ARRAY(StrongJawMoves, (MoveID)BattleEventVar_GetValue(VAR_MOVE_ID)))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 6144);
            }
        }
    }
    ABILITY_TRIGGERTABLE StrongJawHandlers[]{
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerStrongJaw},
    };
    
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHydration(u32 *handlerAmount)
    {
        *handlerAmount = 1;
        return StrongJawHandlers;
    }
#pragma endregion

#pragma region Truant
    /* WE WILL EVENTUALLY WANT TO REFERENCE THIS WORK VALUE DIRECTLY TO DETERMINE WHETHER TRUANT IS ACTIVE */
    void THUMB_BRANCH_HandlerTruant(int a1, int a2, int a3, _DWORD *a4)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            BattleMon *mon = Handler_GetBattleMon((ServerFlow *)a2, a3);
            if (BattleMon_GetTurnFlag(mon, TURNFLAG_MOVEFAILEDLASTTURN)){
                *a4 = 0;
            }
            
            if (*a4)
            {
                if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) && BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
                {
                    a4[1] = BattleEventVar_RewriteValue(VAR_FAIL_CAUSE, MOVEFAIL_ABILITY);
                }
                *a4 = 0;
            }
            else
            {
                if (PML_MoveGetCategory(BattleEventVar_GetValue(VAR_MOVE_ID)) && BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE)
                {
                    *a4 = 1;
                }
            }
            if (BattleEventVar_GetValue(VAR_MOVE_ID) != MOVE165_STRUGGLE){
                *a4 = 0;
            }
        }
    }
#pragma endregion

#pragma region Overcoat

    void HandlerOvercoatPowders(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v7; // r0
        int moveId;
        int result;
        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            moveId = BattleEventVar_GetValue(VAR_MOVE_ID);

            if ((moveId == 78 || moveId == 79 || moveId == 147 || moveId == 476 || moveId == 77 || moveId == 139))
            {
                result = BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
                if (result)
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                    v7 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                    BattleHandler_StrSetup(&v7->str, 2u, 210);
                    BattleHandler_AddArg(&v7->str, (int)a3);
                    BattleHandler_PopWork(a2, v7);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
                }
            }
        }
    }

    int THUMB_BRANCH_SAFESTACK_ServerEvent_CheckNoEffect(
        ServerFlow *a1,
        MoveParam *a2,
        BattleEventType a3,
        BattleMon *a4,
        BattleMon *a5,
        int a6,
        _WORD *a7,
        int *a8)
    {
        u8 ID;        // r0
        u8 v12;       // r0
        u8 v13;       // r0
        u8 Value;     // r5
        int IfEnabled; // [sp+4h] [bp-1Ch]

        ID = BattleMon_GetID(a5);
        IfEnabled = sub_21B0874((EffectivenessRecorder *)a6, ID);
        BattleHandler_StrClear(a7);
        BattleEventVar_Push();
        v12 = BattleMon_GetID(a4);
        BattleEventVar_SetConstValue(VAR_ATTACKING_MON, v12);
        v13 = BattleMon_GetID(a5);
        BattleEventVar_SetConstValue(VAR_DEFENDING_MON, v13);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a2->MoveID);
        BattleEventVar_SetConstValue(VAR_MOVE_TYPE, a2->moveType);
        BattleEventVar_SetConstValue(VAR_MAGIC_COAT_FLAG, a2->flags & 1);
        BattleEventVar_SetConstValue(VAR_WORK_ADDRESS, (int)a7);
        BattleEventVar_SetConstValue(VAR_TYPE_EFFECTIVENESS, IfEnabled);
        BattleEventVar_SetRewriteOnceValue(VAR_NO_EFFECT_FLAG, 0);
        BattleEventVar_SetRewriteOnceValue(VAR_GENERAL_USE_FLAG, 0);
        BattleEvent_CallHandlers(a1, a3);
        Value = BattleEventVar_GetValue(VAR_NO_EFFECT_FLAG);
        *a8 = BattleEventVar_GetValue(VAR_GENERAL_USE_FLAG);
        BattleEventVar_Pop();

        int moveId = a2->MoveID;
        if ((moveId == 78 || moveId == 79 || moveId == 147 || moveId == 476 || moveId == 77 || moveId == 139) && BattleMon_HasType(a5, TYPE_GRASS))
        {
            Value = 1;
        }
        return Value;
    }

    ABILITY_TRIGGERTABLE OvercoatHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerOvercoatPowders}, // 24
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerOvercoat},               // 25
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddOvercoat(_DWORD *a1)
    {
        *a1 = 2;
        return OvercoatHandlers;
    }

#pragma endregion

#pragma region Unnerve

    /* Unnerve Buff */
    bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(BattleEventItem *a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
    {
        int PokeID;  // r0
        bool result; // r0

        result = 0;
        if (a3 == 5)
        {
            PokeID = BattleEventItem_GetPokeID(a1);
            if (!MainModule_IsAllyMonID(PokeID, a6))
            {
                if (checkIfConsumableItem(a5))
                {
                    return 1;
                }
            }
        }
        return result;
    }

#pragma endregion

#pragma region IceBody

    /* Ice Body Buff*/
    void HandlerIceBody(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *PokeParam;       // r7
        HandlerParam_RecoverHP *v8; // r5
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            v8 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
            v8->header.flags |= 0x800000u;
            v8->pokeID = a3;
            v8->recoverHP = DivideMaxHPZeroCheck(PokeParam, ((Handler_GetWeather((int)a2) == 3) ? 0x8u : 0x10u));
            BattleHandler_PopWork(a2, v8);
        }
    }

    ABILITY_TRIGGERTABLE IceBodyHandlers[] = {
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 22
        {EVENT_TURN_CHECK_BEGIN, (ABILITY_HANDLER_FUNC)HandlerIceBody},
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddIceBody(_DWORD *a1)
    {
        *a1 = 2;
        return IceBodyHandlers;
    }

#pragma endregion

#pragma region Stench
    /* STENCH */
    void THUMB_BRANCH_HandlerStench(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (!BattleEventVar_GetValue(VAR_DEFAULT_EFFECT_CHANCE))
            {
                BattleEventVar_RewriteValue(VAR_EFFECT_CHANCE, 20);
            }
        }
    }
#pragma endregion

#pragma region Intimidate
    /* INTIMIDATE */
    void THUMB_BRANCH_HandlerIntimidate(int a1, ServerFlow *a2, int a3)
    {
        u8 *TempWork;                     // r4
        u8 NumTargets;          // r5
        HandlerParam_ChangeStatStage *v7; // r1
        __int16 ExistFrontPokePos; // [sp+0h] [bp-18h]

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            TempWork = Handler_GetTempWork(a2);
            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, TempWork);
            if (NumTargets)
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);

                v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                // v7->header.flags |= 0x08000000;
                v7->rankType = STATSTAGE_ATTACK;
                v7->rankVolume = -1;
                v7->fMoveAnimation = 1;
                v7->poke_cnt = NumTargets;
                for (u8 frontCurrent = 0; frontCurrent < NumTargets; ++frontCurrent)
                {
                    v7->pokeID[frontCurrent] = TempWork[frontCurrent];
                }
                v7->pad = STAT_CHANGE_INTIMIDATE_FLAG;
                BattleHandler_PopWork(a2, v7);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }
#pragma endregion


#pragma region Aftermath
    /* Aftermath Buff */
    void THUMB_BRANCH_SAFESTACK_HandlerAftermath(int a1, ServerFlow *a2, unsigned int *a3)
    {
        BattleMon *aftermathMon;  // r0
        int v7;                   // r6
        BattleMon *explodedMon;   // r7
        HandlerParam_Damage *v9;  // r4
        __int16 ExistAdjacentPos; // [sp+0h] [bp-18h]
        u8 adjacentPos[5];
        u8 v6;
        u8 i;

        if ((int)a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {

            aftermathMon = Handler_GetBattleMon(a2, (int)a3);
            if (BattleMon_IsFainted(aftermathMon))
            {

                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);

                HandlerParam_AddAnimation *addAnimation = (HandlerParam_AddAnimation *)BattleHandler_PushWork(a2, EFFECT_ADD_ANIMATION, (int)a3);
                addAnimation->header.flags |= 0x800000u;
                addAnimation->animNo = MOVE153_EXPLOSION;
                addAnimation->pos_from = Handler_PokeIDToPokePos(a2, (int)a3);
                addAnimation->pos_to = 6;
                BattleHandler_PopWork(a2, addAnimation);

                ExistAdjacentPos = Handler_GetExistFrontPokePos(a2, (int)a3);
                v6 = Handler_ExpandPokeID(a2, ExistAdjacentPos | 0x200, adjacentPos);

                // k::Printf("\nAFTERMATH TRIGGERED:\nNumTargets = %d", v6);
                for (i = 0; i < v6; i++)
                {

                    explodedMon = Handler_GetBattleMon(a2, adjacentPos[i]);
                    // k::Printf("\nTarget = %d", explodedMon->ID);
                    v9 = (HandlerParam_Damage *)BattleHandler_PushWork(a2, EFFECT_DAMAGE, (int)a3);
                    v9->pokeID = adjacentPos[i];
                    v9->damage = DivideMaxHPZeroCheck(explodedMon, 3u);
                    v9->flags = v9->flags & 0xFE | 1;
                    BattleHandler_StrSetup(&v9->exStr, 2u, 402);
                    BattleHandler_AddArg(&v9->exStr, adjacentPos[i]);
                    BattleHandler_PopWork(a2, v9);
                }
            }
        }
    }
#pragma endregion

#pragma region ChangedRedirectAbilites

    void HandlerNewLightningRod(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_ELECTRIC))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_SPECIAL_ATTACK, 1);
        }
    }

    ABILITY_TRIGGERTABLE LightningRodHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerNewLightningRod}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLightningRod(_DWORD *a1)
    {
        *a1 = 1;
        return LightningRodHandlers;
    }

    void HandlerNewStormDrain(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_WATER))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_SPECIAL_ATTACK, 1);
        }
    }

    ABILITY_TRIGGERTABLE StormDrainHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerNewStormDrain}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStormDrain(_DWORD *a1)
    {
        *a1 = 1;
        return StormDrainHandlers;
    }

#pragma endregion

#pragma region Forewarn

    void HandlerForewarnMessage(int a1, ServerFlow *a2, unsigned int a3)
    {
        BattleMon *PokeParam;     // r7
        HandlerParam_Message *v1; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            PokeParam = Handler_GetBattleMon(a2, (int)a3);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
            v1 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup(&v1->str, 2u, 1228);
            BattleHandler_AddArg(&v1->str, a3);
            BattleHandler_PopWork(a2, v1);
            BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
        }
    }

    void HandlerForewarnNew(BattleEventItem *a1, ServerFlow *a2, int a3)
    {
        if ((a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) || MainModule_IsAllyMonID(a3, BattleEventVar_GetValue(VAR_MON_ID))) && BattleEventVar_GetValue(VAR_CRITICAL_FLAG))
        {
            BattleEventVar_MulValue(VAR_RATIO, 3072);
        }
    }

    ABILITY_TRIGGERTABLE ForewarnHandlers[] = {
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerForewarnMessage}, // 22
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerForewarnMessage},
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerForewarnNew},
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddForewarn(_DWORD *a1)
    {
        *a1 = 4;
        return ForewarnHandlers;
    }

#pragma endregion

#pragma region WellBakedBody
    void HandlerWellBakedBody(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_FIRE))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_DEFENSE, 2);
        }
    }

    ABILITY_TRIGGERTABLE WellBakedBodyHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerWellBakedBody}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSuctionCups(_DWORD *a1)
    {
        *a1 = 1;
        return WellBakedBodyHandlers;
    }

#pragma endregion

#pragma region Amplifier
    void HandlerAmplifier(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_SOUND))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
            }
        }
    }

    ABILITY_TRIGGERTABLE AmplifierHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerSoundproof}, // 22
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerAmplifier}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSoundproof(_DWORD *a1)
    {
        *a1 = 1;
        return AmplifierHandlers;
    }

#pragma endregion

#pragma region Rivalry

    void RivalryOffense(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *attackingMon; // r4
        unsigned __int8 Value;   // r0
        BattleMon *defendingMon; // r5
        u8 v8;                  // r4
        u8 v9;                  // r0

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            attackingMon = Handler_GetBattleMon(a2, a3);
            defendingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_DEFENDING_MON));
            v8 = BattleMon_GetPokeType(attackingMon);
            v9 = BattleMon_GetPokeType(defendingMon);

            if (PokeTypePair_HasSharedType(v8, v9))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5448);
            }
        }
    }

    void RivalryDefense(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *attackingMon; // r4
        unsigned __int8 Value;   // r0
        BattleMon *defendingMon; // r5
        u8 v8;                  // r4
        u8 v9;                  // r0

        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            defendingMon = Handler_GetBattleMon(a2, a3);
            attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
            v8 = BattleMon_GetPokeType(attackingMon);
            v9 = BattleMon_GetPokeType(defendingMon);

            if (PokeTypePair_HasSharedType(v8, v9))
            {
                BattleEventVar_MulValue(VAR_RATIO, 2730);
            }
        }
    }

    ABILITY_TRIGGERTABLE RivalryHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)RivalryOffense},               // 41
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)RivalryDefense}, // 41
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRivalry(_DWORD *a1)
    {
        *a1 = 2;
        return RivalryHandlers;
    }

#pragma endregion

#pragma region Distracting

    void HandlerDistracting(int a1, ServerFlow *a2, int a3)
    {
        u8 *TempWork;                     // r4
        u8 NumTargets;          // r5
        HandlerParam_ChangeStatStage *v7; // r1
        __int16 ExistFrontPokePos;        // [sp+0h] [bp-18h]

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
            {
                ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
                TempWork = Handler_GetTempWork(a2);
                NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, TempWork);
                if (NumTargets)
                {
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);

                    v7 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
                    // v7->header.flags |= 0x08000000;
                    v7->rankType = STATSTAGE_EVASION;
                    v7->rankVolume = -1;
                    v7->fMoveAnimation = 1;
                    v7->poke_cnt = NumTargets;
                    for (u8 frontCurrent = 0; frontCurrent < NumTargets; ++frontCurrent)
                    {
                        v7->pokeID[frontCurrent] = TempWork[frontCurrent];
                    }
                    v7->pad = VAR_HOSTILEFLAG;
                    BattleHandler_PopWork(a2, v7);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
                }
            }
        }
    }

    ABILITY_TRIGGERTABLE DistractingHandlers[] = {
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerDistracting},            // 41
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerDistracting}, // 41
    };
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddKlutz(_DWORD *a1)
    {
        *a1 = 2;
        return DistractingHandlers;
    }

#pragma endregion

#pragma region CoOpAbilities

    ABILITY_TRIGGERTABLE FriendGuardHandlers[] = {
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerFriendGuard}, // 0
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}};

    ABILITY_TRIGGERTABLE PlusMinusHandlers[] = {
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerPlusMinus},          // 2
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}, // 3
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddFriendGuard(_DWORD *a1)
    {
        *a1 = 2;
        return FriendGuardHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPlus(_DWORD *a1)
    {
        *a1 = 2;
        return PlusMinusHandlers;
    }

#pragma endregion

#pragma region NewHealer

    int HandlerNewHealer(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {

        u8 NumTargets;             // r0
        __int16 v7;                 // r0
        u8 currentTarget; // r4
        u8 currentTargetPosition;  // r1
        BattleMon *battleMon;       // r0
        BattleMon *Ally;
        HandlerParam_RecoverHP *v6; // r5
        u8 v13[5];                  // [sp+4h] [bp-1Ch] BYREF
        int v14;                    // [sp+8h] [bp-18h]

        NumTargets = BattleEventVar_GetValue(VAR_MON_ID);
        v14 = a4;
        if (a3 == NumTargets)
        {
            battleMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_MON_ID));
            if (!BattleMon_IsFullHP(battleMon))
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, a3);
                v6->pokeID = a3;
                v6->recoverHP = DivideMaxHPZeroCheck(battleMon, 0x10u);
                BattleHandler_PopWork(a2, v6);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
            v7 = Handler_PokeIDToPokePos(a2, a3);
            NumTargets = Handler_ExpandPokeID(a2, v7 | 0x700, v13);
            for (currentTarget = 0; currentTarget < NumTargets; currentTarget++)
            {
                currentTargetPosition = v13[currentTarget];
                Ally = Handler_GetBattleMon(a2, currentTargetPosition);
                if (!BattleMon_IsFullHP(Ally) && Ally->ID != battleMon->ID)
                {
                    v6 = (HandlerParam_RecoverHP *)BattleHandler_PushWork(a2, EFFECT_RECOVERHP, currentTargetPosition);
                    v6->pokeID = currentTargetPosition;
                    v6->recoverHP = DivideMaxHPZeroCheck(Ally, 0x10u);
                    BattleHandler_PopWork(a2, v6);
                }
            }
        }
        return NumTargets;
    }

    ABILITY_TRIGGERTABLE HealerHandlers[] = {
        {EVENT_TURN_CHECK_BEGIN, (ABILITY_HANDLER_FUNC)HandlerNewHealer},        // 4
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerTelepathy}, // 5
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddHealer(_DWORD *a1)
    {
        *a1 = 2;
        return HealerHandlers;
    }

#pragma endregion

#pragma region ToughClaws
    // Tough Claws
    void HandlerToughClaws(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5324);
            }
        }
    }

    ABILITY_TRIGGERTABLE ToughClawsHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerToughClaws}, // 6
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddStall(_DWORD *a1)
    {
        *a1 = 1;
        return ToughClawsHandlers;
    }
#pragma endregion


#pragma region Collective 

    void HandlerCollective(BattleEventItem * item, ServerFlow * serverFlow, u32 pokemonSlot, u32 * work) {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID)) {
            BattleMon* currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            //  0: Combee-Male 
            //  1: Combee-Female 
            //  2: Combee-Collective
            // 23: X -> Z
            // 24: Y -> Unown-Exclamation
            // 25: Z -> Unown-Question
            // 26: ! -> Unown-Exclamation Schooling 
            // 27: ? -> Unown-Question Schooling

            u8 currentForm = BattleMon_GetValue(currentMon, VALUE_FORM);
            u8 newForm = currentForm;
            u16 msgID = 264;

            // TODO: ADD WISHIWASHI
            if (BattleMon_GetSpecies(currentMon) == 201) {
                u32 currentHP = BattleMon_GetValue(currentMon, VALUE_CURRENT_HP);
                if (currentForm == 24 || currentForm == 25){
                    if (currentHP > DivideMaxHPZeroCheck(currentMon, 4u)) {
                        newForm = currentForm - 2;
                        msgID = 264;
                    }
                }
                if (currentForm == 26 || currentForm == 27){
                    if (currentHP <= DivideMaxHPZeroCheck(currentMon, 4u)) {
                        newForm = currentForm + 2;
                        msgID = 265;
                    }
                } 
            }

            if (BattleMon_GetSpecies(currentMon) == 415) {
                if (BattleMon_GetValue(currentMon, VALUE_SEX) == 0){
                    u32 currentHP = BattleMon_GetValue(currentMon, VALUE_CURRENT_HP);
                    if (currentForm == 0){
                        if (currentHP > DivideMaxHPZeroCheck(currentMon, 4u)) {
                            newForm = currentForm + 2;
                            msgID = 264;
                        }
                    }
                    if (currentForm == 2){
                        if (currentHP <= DivideMaxHPZeroCheck(currentMon, 4u)) {
                            newForm = currentForm - 2;
                            msgID = 265;
                        }
                    } 
                }
            }


            if (currentForm != newForm) {
                    HandlerParam_ChangeForm* changeForm;
                    changeForm = (HandlerParam_ChangeForm*)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_FORM, pokemonSlot);
                    changeForm->header.flags |= 0x800000;
                    changeForm->monID = pokemonSlot;
                    changeForm->form = newForm;
                    BattleHandler_StrSetup(&changeForm->strParam, 1u, msgID);
                    BattleHandler_AddArg(&changeForm->strParam, pokemonSlot);
                    BattleHandler_PopWork(serverFlow, changeForm);
                }

        }
    }

    ABILITY_TRIGGERTABLE CollectiveHandlers[]{
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerCollective},
        {EVENT_TURN_CHECK_DONE, (ABILITY_HANDLER_FUNC)HandlerCollective},
    };

    ABILITY_TRIGGERTABLE * THUMB_BRANCH_EventAddZenMode(_DWORD * a1) {
        *a1 = 2;
        return CollectiveHandlers;
    }

#pragma endregion 
#pragma region SlushRush

    void HandlerSlushRush(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && Handler_GetWeather(a2) == 3) // hail
        {
            BattleEventVar_MulValue(VAR_RATIO, 0x2000);
        }
    }

    void HandlerSlushRushPower(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ICE)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
        }
    }

    ABILITY_TRIGGERTABLE SlushRushHandlers[] = {
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSlushRush},              // 7
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 8
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSlushRushPower},
        {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorStatus},
        {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon},
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
        {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorActionEnd},
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddTangledFeet(_DWORD *a1)
    {
        *a1 = 8;
        return SlushRushHandlers;
    }

#pragma endregion

#pragma region ThickFat
    ABILITY_TRIGGERTABLE ThickFatHandlers[] = {
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerThickFat},           // 9
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 10
        {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorStatus},
        {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon},
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorCureStatus},
        {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerMagmaArmorActionEnd}
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddThickFat(_DWORD *a1)
    {
        *a1 = 7;
        return ThickFatHandlers;
    }
#pragma endregion

#pragma region PreStatusAbilities


    void triggerPreStatus(ServerFlow *a1, u8 pokePos, MoveCondition condition){
        HandlerParam_AddCondition *v6;
        v6 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, (int)pokePos);
        v6->sickID = condition;
        v6->sickCont = MakeBasicStatus(condition);
        v6->fAlmost = 0;
        v6->pokeID = (unsigned __int8)pokePos;
        BattleHandler_StrSetup(&v6->exStr, 1u, ((condition == CONDITION_PARALYSIS) ? 242 : ((condition==CONDITION_BURN) ? 201 : 202)));
        BattleHandler_AddArg(&v6->exStr, (int)pokePos);
        BattleHandler_PopWork(a1, v6);
    }

    void HandlerPreStatusForGuts(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *PokeParam; // r7

        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            PokeParam = Handler_GetBattleMon(a2, a3);
            u8 condition; 
            u8 textId; 

            if (PokeParam->Species == PK377_REGIROCK)
            {
                condition = CONDITION_PARALYSIS;
            }
            else {
                condition = ((BattleMon_HasType(PokeParam, TYPE_FIRE)) ? ((PokeParam->Sex == 0) ? CONDITION_POISON : CONDITION_PARALYSIS ) : ((PokeParam->Sex == 0) ? CONDITION_BURN : CONDITION_PARALYSIS ));
            }
            triggerPreStatus(a2, a3, (MoveCondition)condition);
        }
    }

    void HandlerPrePoisonOnAI(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            triggerPreStatus(a2, a3, CONDITION_POISON);
        }
    }

    void HandlerPreBurnOnAI(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            triggerPreStatus(a2, a3, CONDITION_BURN);
        }
    }

    void HandlerPreParalysisOnAI(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            triggerPreStatus(a2, a3, CONDITION_PARALYSIS);
        }
    }

    void HandlerPreStatusMarvelScaleOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *poke;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            poke = Handler_GetBattleMon(a2, a3);
            triggerPreStatus(a2, a3, ((poke->Sex == 0) ? CONDITION_POISON : CONDITION_PARALYSIS));
        }
    }

    void HandlerToxicBoostStatus(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_CONDITION_ID) == 5)
            {
                BattleEventVar_RewriteValue(VAR_DAMAGE, checkHigher(BattleEventVar_GetValue(VAR_DAMAGE) / 2, 1));
            }
        }
    }

    void HandlerToxicBoostDamage(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_POISON)
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
    }

    ABILITY_TRIGGERTABLE MarvelScaleHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerMarvelScale},         // 27
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreStatusMarvelScaleOnAI}, // 28
    };

    ABILITY_TRIGGERTABLE GutsHandlers[] = {
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerGuts},        // 11
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreStatusForGuts}, // 12

    };

    ABILITY_TRIGGERTABLE QuickFeetHandlers[] = {

        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerQuickFeet},       // 13
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreParalysisOnAI}, // 14
    };

    ABILITY_TRIGGERTABLE FlareBoostHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerFlareBoost}, // 15
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreBurnOnAI},
        {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerHeatproofStatus}, // 16
    };

    ABILITY_TRIGGERTABLE PoisonHealHandlers[] = {
        {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerPoisonHeal}, // 17
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},     // 18
    };

    ABILITY_TRIGGERTABLE ToxicBoostHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerToxicBoost},             // 42
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPrePoisonOnAI},           // 43
        {EVENT_CONDITION_DAMAGE, (ABILITY_HANDLER_FUNC)HandlerToxicBoostStatus}, // 44
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerToxicBoostDamage}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddGuts(_DWORD *a1)
    {
        *a1 = 2;
        return GutsHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddQuickFeet(_DWORD *a1)
    {
        *a1 = 2;
        return QuickFeetHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddFlareBoost(_DWORD *a1)
    {
        *a1 = 3;
        return FlareBoostHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPoisonHeal(_DWORD *a1)
    {
        *a1 = 2;
        return PoisonHealHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddToxicBoost(_DWORD *a1)
    {
        *a1 = 4;
        return ToxicBoostHandlers;
    }

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddMarvelScale(_DWORD *a1)
    {
        *a1 = 2;
        return MarvelScaleHandlers;
    }

#pragma endregion

#pragma region Fluffy

    void HandlerFluffyFire(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_FIRE)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
        }
    }

    void HandlerFluffy(int a1, ServerFlow *a2, int a3)
    {
        int ratio;
        BattleMon *attackingMon;
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
            {
#if USING_OVERRIDE_CONTACT
                attackingMon = Handler_GetBattleMon(a2, BattleEventVar_GetValue(VAR_ATTACKING_MON));
                if (overrideContact(attackingMon, (MoveID)Value))
                {
                    ratio = 4096;
                }
                else
                {
                    ratio = 2048;
                }
#else 
                ratio = 2048;
#endif
            }
            else
            {
                ratio = 4096;
            }
            BattleEventVar_MulValue(VAR_RATIO, ratio);
        }
    }

    ABILITY_TRIGGERTABLE FluffyHandlers[] = {
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerFluffyFire},
        {EVENT_MOVE_DAMAGE_PROCESSING_2, (ABILITY_HANDLER_FUNC)HandlerFluffy},   // 22
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSnowCloakWeather}, // 23
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddImmunity(_DWORD *a1)
    {
        *a1 = 3;
        return FluffyHandlers;
    }

#pragma endregion

#pragma region Corrosion
    void HandlerCorrosion(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_POISON && BattleEventVar_GetValue(VAR_POKE_TYPE) == TYPE_STEEL)
        {
            BattleEventVar_RewriteValue(VAR_SET_TYPE_EFFECTIVENESS, 2);
        }
    }

    ABILITY_TRIGGERTABLE CorrosionHandlers[] = {
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerCorrosion}, // 26
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddLimber(_DWORD *a1)
    {
        *a1 = 1;
        return CorrosionHandlers;
    }

#pragma endregion

#pragma region RainDish

    ABILITY_TRIGGERTABLE RainDishHandlers[] = {
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerRainDish},                // 29
        {EVENT_ADD_CONDITION_CHECK_FAIL, (ABILITY_HANDLER_FUNC)HandlerWaterVeil},       // 30
        {EVENT_ADD_CONDITION_FAIL, (ABILITY_HANDLER_FUNC)HandlerAddStatusFailedCommon}, // 31
        {EVENT_AFTER_ABILITY_CHANGE, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus}, // 32
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerWaterVeilCureStatus},            // 33
        {EVENT_ACTION_PROCESSING_END, (ABILITY_HANDLER_FUNC)HandlerWaterVeilActionEnd}, // 34
    };
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRainDish(_DWORD *a1)
    {
        *a1 = 6;
        return RainDishHandlers;
    }

#pragma endregion

#pragma region StrongBody

    ABILITY_TRIGGERTABLE StrongBodyHandlers[] = {
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerClearBodyCheck}, // 35
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerClearBodyGuard},       // 36
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerOvercoat},                   // 37
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddClearBody(_DWORD *a1)
    {
        *a1 = 3;
        return StrongBodyHandlers;
    }

#pragma endregion

#pragma region DrySkin

    void HandlerDrySkinDamage(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if (BattleEventVar_GetValue(VAR_MOVE_TYPE) == 9)
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
            }
        }
    }

    ABILITY_TRIGGERTABLE DrySkinHandlers[] = {
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerDrySkinWeather},      // 38
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerDrySkinDamage},             // 39
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerDrySkinCheck}, // 40
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddDrySkin(_DWORD *a1)
    {
        *a1 = 3;
        return DrySkinHandlers;
    }

#pragma endregion

#pragma region NewPickup

    void HandlerPickupNew(int a1, ServerFlow *a2, int a3)
    {
        BattleMon *BattleMon; // r6
        u16 UsedItem;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            BattleMon = Handler_GetBattleMon(a2, a3);
            UsedItem = BattleMon_GetUsedItem(BattleMon);

            if (UsedItem && BattleMon_GetHeldItem(BattleMon) == 0)
            {
                // See if we can add 
                ConditionData v10; 
                MakeCondition(CONDITION_EMBARGO, BattleMon, &v10);
                HandlerParam_AddCondition *v8 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a2, EFFECT_ADDCONDITION, a3);
                v8->pokeID = a3;
                v8->sickID = CONDITION_EMBARGO;
                v8->sickCont = v10;
                v8->fAlmost = 0;
                BattleHandler_StrSetup(&v8->exStr, 2u, 1333);
                BattleHandler_AddArg(&v8->exStr, v8->pokeID);
                BattleHandler_PopWork(a2, v8);

                HandlerParam_SetItem *v9 = (HandlerParam_SetItem *)BattleHandler_PushWork(a2, EFFECT_SET_HELD_ITEM, a3);
                v9->header.flags |= 0x800000u;
                v9->itemID = UsedItem;
                v9->pokeID = a3;
                v9->fClearConsume = 0;
                BattleHandler_StrSetup(&v9->exStr, 2u, 1162);
                BattleHandler_AddArg(&v9->exStr, a3);
                BattleHandler_AddArg(&v9->exStr, UsedItem);
                BattleHandler_PopWork(a2, v9);
            }
        }
    }

    ABILITY_TRIGGERTABLE PickupHandlers[] = {
        {EVENT_SWITCH_OUT_END, (ABILITY_HANDLER_FUNC)HandlerPickupNew}, // 41
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPickup(_DWORD *a1)
    {
        *a1 = 1;
        return PickupHandlers;
    }

#pragma endregion

#pragma region SwiftSwim
    void HandlerSwiftSwimResist(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_WATER)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
        }
    }

    ABILITY_TRIGGERTABLE SwiftSwimHandlers[] = {
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSwiftSwim},
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSwiftSwimResist} // 41
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSwiftSwim(_DWORD *a1)
    {
        *a1 = 2;
        return SwiftSwimHandlers;
    }

#pragma endregion

#pragma region SandRush
    void HandlerSandRushResist(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_ROCK)
        {
            BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 2048);
        }
    }

    ABILITY_TRIGGERTABLE SandRushHandlers[] = {
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerSandRush},              // FIX THIS
        {EVENT_WEATHER_REACTION, (ABILITY_HANDLER_FUNC)HandlerSandVeilWeather}, // 41
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerSandRushResist}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddSandRush(_DWORD *a1)
    {
        *a1 = 3;
        return SandRushHandlers;
    }
#pragma endregion

#pragma region Rattled

    void HandlerRattledIntimidateCheck(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleEventVar_GetValue(VAR_INTIMFLAG))
            {
                work[0] = 1;
            }
            else
            {
                work[0] = 0;
            }
        }
    }

    void HandlerRattledIntimidate(int a1, ServerFlow *a2, int a3, u32 *work)
    {
        HandlerParam_ChangeStatStage *v13; // r0
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && work[0])
        {
            work[0] = 0;
            v13 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, a3);
            v13->header.flags |= 0x800000u;
            v13->rankType = STATSTAGE_SPEED;
            v13->rankVolume = 3;
            v13->fMoveAnimation = 1;
            v13->poke_cnt = 1;
            v13->pokeID[0] = a3;
            BattleHandler_PopWork(a2, v13);
        }
    }
    ABILITY_TRIGGERTABLE RattledHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerRattled}, // 22
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerRattledIntimidateCheck},
        {EVENT_STAT_STAGE_CHANGE_APPLIED, (ABILITY_HANDLER_FUNC)HandlerRattledIntimidate}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddRattled(_DWORD *a1)
    {
        *a1 = 3;
        return RattledHandlers;
    }

#pragma endregion

#pragma region InnerFocus

    void HandlerInnerFocusAttack(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (BattleEventVar_GetValue(VAR_POKE_TYPE) == TYPE_DARK)
            {
                BattleEventVar_RewriteValue(VAR_NO_TYPE_EFFECTIVENESS, 1);
            }
        }
    }

    ABILITY_TRIGGERTABLE InnerFocusHandlers[] = {
        {EVENT_FLINCH_CHECK, (ABILITY_HANDLER_FUNC)HandlerInnerFocus}, // 22
        {EVENT_STAT_STAGE_CHANGE_LAST_CHECK, (ABILITY_HANDLER_FUNC)HandlerIntimidateCheck},
        {EVENT_STAT_STAGE_CHANGE_FAIL, (ABILITY_HANDLER_FUNC)HandlerIntimidateGuard},
        {EVENT_CHECK_TYPE_EFFECTIVENESS, (ABILITY_HANDLER_FUNC)HandlerInnerFocusAttack}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddInnerFocus(_DWORD *a1)
    {
        *a1 = 4;
        return InnerFocusHandlers;
    }

#pragma endregion

#pragma region ThunderArmor

    void HandlerThunderArmor(int a1, ServerFlow *a2, int a3)
    {
        if (CommonDamageRecoverCheck(a2, a3, TYPE_ELECTRIC))
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        }
    }

    ABILITY_TRIGGERTABLE ThunderArmorHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerThunderArmor}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddInsomnia(_DWORD *a1)
    {
        *a1 = 1;
        return ThunderArmorHandlers;
    }

#pragma endregion

#pragma region Bulletproof

    void HandlerBulletproof(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v9;
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_BOMB))// (SEARCH_ARRAY(BulletproofMoves, BattleEventVar_GetValue(VAR_MOVE_ID)))
            {
                BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);

                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                v9 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                BattleHandler_StrSetup(&v9->str, 2u, 1246);
                BattleHandler_AddArg(&v9->str, a3);
                BattleHandler_PopWork(a2, v9);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
            }
        }
    }

    ABILITY_TRIGGERTABLE BulletproofHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerBulletproof}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddDamp(_DWORD *a1)
    {
        *a1 = 1;
        return BulletproofHandlers;
    }

#pragma endregion

#pragma region WindRider
    /*



        --------------------------------------------------------------------------------------------------
        ------------------------------------ WIND RIDER --------------------------------------------------
        --------------------------------------------------------------------------------------------------



    */

    void HandlerWindRiderTailwind(int a1, ServerFlow *a2, int a3)
    {
        // HandlerParam_Message *v9;
        if ((BattleEventVar_GetValue(VAR_MON_ID) == a3 || MainModule_IsAllyMonID(a3, BattleEventVar_GetValue(VAR_MON_ID))) && BattleEventVar_GetValue(VAR_MOVE_ID) == MOVE366_TAILWIND)
        {
            CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        }
        // if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
        // {
        //     if (isInArray(BattleEventVar_GetValue(VAR_MOVE_ID), 1))
        //     {
        //         BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
        //         CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
        //     }
        // }
    }

    void HandlerWindRider(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON) && a3 != BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_WIND)) //if (SEARCH_ARRAY(WindMoves, BattleEventVar_GetValue(VAR_MOVE_ID)))
            {
                BattleEventVar_RewriteValue(VAR_NO_EFFECT_FLAG, 1);
                CommonTypeNoEffectRankUp(a2, a3, STATSTAGE_ATTACK, 1);
            }
        }
    }
    ABILITY_TRIGGERTABLE WindRiderHandlers[] = {
        {EVENT_ABILITY_CHECK_NO_EFFECT, (ABILITY_HANDLER_FUNC)HandlerWindRider}, // 22
        {EVENT_MOVE_EXECUTE_END, (ABILITY_HANDLER_FUNC)HandlerWindRiderTailwind}};

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddKeenEye(_DWORD *a1)
    {
        *a1 = 2;
        return WindRiderHandlers;
    }

#pragma endregion

#pragma region QuickDraw

    /*



        --------------------------------------------------------------------------------------------------
        ------------------------------------ QUICK DRAW --------------------------------------------------
        --------------------------------------------------------------------------------------------------



    */

    void HandlerQuickDraw(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_Message *v9;



        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (RollEffectChance(30u))
            {
                if (BattleEventVar_RewriteValue(VAR_PRIORITY, 2))
                {

                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, a3);
                    v9 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, a3);
                    BattleHandler_StrSetup(&v9->str, 2u, 1348); // replace with the actual id
                    BattleHandler_AddArg(&v9->str, a3);
                    BattleHandler_PopWork(a2, v9);
                    BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, a3);
                }
            }
        }
    }
    ABILITY_TRIGGERTABLE QuickDrawHandlers[] = {
        {EVENT_CHECK_SPECIAL_PRIORITY, (ABILITY_HANDLER_FUNC)HandlerQuickDraw}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddOwnTempo(_DWORD *a1)
    {
        *a1 = 1;
        return QuickDrawHandlers;
    }

#pragma endregion

#pragma region Stakeout

    /*



        --------------------------------------------------------------------------------------------------
        ------------------------------------ STAKEOUT --------------------------------------------------
        --------------------------------------------------------------------------------------------------



    */

    bool SwitchedInThisTurn(ServerFlow *serverFlow, BattleMon *battleMon, int defendingSlot)
    {
        // int *ActionOrderAttackingMon;
        // int *ActionOrderDefendingMon;
        // // if (serverFlow->turnCount == 0) {
        // //     for (u8 i = 0; i < 6; ++i) {
        // //         if (g_BattleField->firstTurnMons[i] == battleMon->ID) {
        // //             // A Pokémon that started the battle doesn't count as just switched in
        // //             return 0;
        // //         }
        // //     }
        // // }
        // ActionOrderAttackingMon = ActionOrder_SearchByMonID(a1, AttackingMon->ID);
        // ActionOrderDefendingMon = ActionOrder_SearchByMonID(a1, DefendingMon->ID);

        // if (ActionOrderAttackingMon > ActionOrderDefendingMon)
        // {
        //     return true;
        // }
        // else
        // {
        //     return false;
        // }
        unsigned int v11[6];
        return !battleMon->TurnCount && !Handler_GetThisTurnAction(serverFlow, defendingSlot, v11);
    }

    void HandlerStakeout(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon *attackingMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            u32 defendingSlot = BattleEventVar_GetValue(VAR_DEFENDING_MON);
            BattleMon *defendingMon = Handler_GetBattleMon(serverFlow, defendingSlot);

            if (SwitchedInThisTurn(serverFlow, defendingMon, defendingSlot))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 8192);
            }
        }
    }
    ABILITY_TRIGGERTABLE StakeoutHandlers[]{
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerStakeout},
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddFrisk(_DWORD *a1)
    {
        *a1 = 1;
        return StakeoutHandlers;
    }

#pragma endregion

#pragma region Pickpocket
    /*



        --------------------------------------------------------------------------------------------------
        ------------------------------------ PICKPOCKET --------------------------------------------------
        --------------------------------------------------------------------------------------------------



    */

    void HandlerMagician(BattleEventItem *item, ServerFlow *serverFlow, u32 pokemonSlot, u32 *work)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);
            if (!*work)
            {
                u32 targetSlot = BattleEventVar_GetValue(VAR_TARGET_MON_ID);
                if (targetSlot != 31 && getMoveFlag(BattleEventVar_GetValue(VAR_MOVE_ID), FLAG_CONTACT))
                {
                    BattleMon *targetMon = Handler_GetBattleMon(serverFlow, targetSlot);
                    if (BattleMon_GetHeldItem(targetMon))
                    {
                        if (!HandlerCommon_CheckIfCanStealPokeItem(serverFlow, pokemonSlot, targetSlot))
                        {
                            BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);
                            if (BattleMon_GetHeldItem(currentMon) == IT_NULL)
                            {
                                HandlerParam_SwapItem *swapItem;
                                swapItem = (HandlerParam_SwapItem *)BattleHandler_PushWork(serverFlow, EFFECT_SWAPITEM, pokemonSlot);
                                swapItem->pokeID = targetSlot;
                                BattleHandler_StrSetup(&swapItem->exStr, 2u, 1057);
                                BattleHandler_AddArg(&swapItem->exStr, pokemonSlot);
                                BattleHandler_AddArg(&swapItem->exStr, targetSlot);
                                ItemID heldItem = (ItemID)BattleMon_GetHeldItem(targetMon);
                                BattleHandler_AddArg(&swapItem->exStr, heldItem);
                                BattleHandler_PopWork(serverFlow, swapItem);
                            }
                            else
                            {
                                HandlerParam_SetItem *setItem;
                                setItem = (HandlerParam_SetItem *)BattleHandler_PushWork(serverFlow, EFFECT_SET_HELD_ITEM, pokemonSlot);
                                setItem->pokeID = targetSlot;
                                setItem->itemID = 0;
                                BattleHandler_StrSetup(&setItem->exStr, 2u, 1050); // Change the Text for this!
                                BattleHandler_AddArg(&setItem->exStr, pokemonSlot);
                                BattleHandler_AddArg(&setItem->exStr, targetSlot);
                                BattleHandler_AddArg(&setItem->exStr, BattleMon_GetHeldItem(targetMon));
                                BattleHandler_PopWork(serverFlow, setItem);
                            }
                            BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
                        }
                    }
                }
            }
        }
    }
    ABILITY_TRIGGERTABLE PickpocketHandlers[]{
        {EVENT_DAMAGE_PROCESSING_END_HIT_REAL, (ABILITY_HANDLER_FUNC)HandlerMagician},
    };
    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddPickpocket(_DWORD *a1)
    {
        *a1 = 1;
        return PickpocketHandlers;
    }

#pragma endregion


#pragma region Savant

    void HandlerSavant(int a1, ServerFlow *serverFlow, int pokemonSlot)
    {
        if (pokemonSlot == BattleEventVar_GetValue(VAR_MON_ID))
        {
            BattleMon *currentMon = Handler_GetBattleMon(serverFlow, pokemonSlot);

            MoveParam params;
            ServerEvent_GetMoveParam(serverFlow, BattleEventVar_GetValue(VAR_MOVE_ID), (int)currentMon, &params);

            if (params.moveType != TYPE_NONE &&
                PokeTypePair_MakeMonotype(params.moveType) != BattleMon_GetPokeType(currentMon))
            {
                if (!BattleMon_CheckIfMoveCondition(currentMon, CONDITION_TERA))
                {
                    BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPIN, pokemonSlot);

                    HandlerParam_ChangeType *changeType;
                    changeType = (HandlerParam_ChangeType *)BattleHandler_PushWork(serverFlow, EFFECT_CHANGE_TYPE, pokemonSlot);
                    changeType->nextType = PokeTypePair_MakeMonotype(params.moveType);
                    changeType->monID = pokemonSlot;
                    BattleHandler_PopWork(serverFlow, changeType);

                    BattleHandler_PushRun(serverFlow, EFFECT_ABILITYPOPUPOUT, pokemonSlot);
                }
            }
        }
    }

    ABILITY_TRIGGERTABLE SavantHandlers[] = {
        {EVENT_MOVE_EXECUTE_CHECK2, (ABILITY_HANDLER_FUNC)HandlerSavant}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddBigPecks(_DWORD *a1)
    {
        *a1 = 1;
        return SavantHandlers;
    }

#pragma endregion

#pragma region Trace

    void THUMB_BRANCH_SAFESTACK_HandlerTrace(int a1, ServerFlow *a2, unsigned int tracePokemonID, _DWORD *a4)
    {
        int tracePokemonSlot; // r5
        unsigned int Value;
        __int16 ExistFrontPokePos; // r0
        int opposingPokeSlot;      // r0
        int oppposingPokeID;       // r0
        u8 v9;                     // r7
        unsigned int i;
        unsigned int pokeCount;
        int traceAbilityId = 0;
        int traceAbilityPokemonId = 0;
        u8 opposingPokePos[5];
        BattleMon *traceVictim;          // r5
        BattleMon *traceUser;            // r0
        HandlerParam_ChangeAbility *v19; // r5
        _DWORD *v26;

        Value = BattleEventVar_GetValue(VAR_MON_ID);

        if (tracePokemonID == Value)
        {

            traceAbilityId = 0;
            traceAbilityPokemonId = 31;
            tracePokemonSlot = Handler_PokeIDToPokePos(a2, tracePokemonID);

            /* FIRST CHECK FOR AN ALLY */
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, (int)tracePokemonID);
            pokeCount = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x400, opposingPokePos);

            if (pokeCount)
            {
                for (i = 0; i < pokeCount; i++)
                {
                    // if (!(Handler_GetBattleStyle(a2) != BTL_STYLE_TRIPLE || IsPosInRangeTripleBattle(ExistFrontPokePos, tracePokemonSlot)))
                    // {
                    //     continue;
                    // }

                    traceVictim = Handler_GetBattleMon(a2, opposingPokePos[i]);
                    traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);
                    if (!j_j_IsTraceFailAbility(traceAbilityId))
                    {

                        traceAbilityPokemonId = BattleMon_GetID(traceVictim);
                    }
                }
            }

            /* NOW CHECK DIRECTLY ACROSS */
            if (!(traceAbilityId && (traceAbilityPokemonId != 31)))
            {

                opposingPokeSlot = sub_219C508(Handler_GetBattleStyle(a2), tracePokemonSlot);
                oppposingPokeID = Handler_PokePosToPokeID(a2, opposingPokeSlot);
                traceVictim = Handler_GetBattleMon(a2, oppposingPokeID);
                traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);

                if (j_j_IsTraceFailAbility(traceAbilityId))
                {
                    /* IF THE DIRECT ACROSS MON DOESN"T WORK, TRY ANY FOE */
                    ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, (int)tracePokemonID);
                    pokeCount = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, opposingPokePos);

                    for (i = 0; i < pokeCount; (i + 1))
                    {
                        if (opposingPokePos[i] != oppposingPokeID)
                        {

                            traceVictim = Handler_GetBattleMon(a2, opposingPokePos[i]);
                            traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);
                            if (!j_j_IsTraceFailAbility(traceAbilityId))
                            {

                                traceAbilityPokemonId = BattleMon_GetID(traceVictim);
                                i = pokeCount;
                            }
                        }
                    }
                    if (traceAbilityPokemonId == 31)
                    {
                        *a4 = 1;
                    }
                }
                else
                {
                    traceAbilityPokemonId = BattleMon_GetID(traceVictim);
                }
            }
        }
        // Called when another pokemon switches in and the trace pokemon did not trace an ability yet
        // This new logic SHOULD work with ally pokemon but we need to test this

        // else if (!MainModule_IsAllyMonID(Value, tracePokemonID) && *a4 == 1)
        else if (*a4 == 1)
        {

            traceAbilityId = 0;
            traceAbilityPokemonId = 0;
            tracePokemonSlot = Handler_PokeIDToPokePos(a2, Value);
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, (int)tracePokemonID);
            if (tracePokemonSlot != 6 && (Handler_GetBattleStyle(a2) != BTL_STYLE_TRIPLE || IsPosInRangeTripleBattle(ExistFrontPokePos, tracePokemonSlot)))
            {

                traceVictim = Handler_GetBattleMon(a2, Value);
                traceAbilityId = BattleMon_GetValue(traceVictim, VALUE_ABILITY);
                if (!j_j_IsTraceFailAbility(traceAbilityId))
                {
                    traceAbilityPokemonId = BattleMon_GetID(traceVictim);
                }
            }
        }

        if (traceAbilityPokemonId != 31 && traceAbilityId)
        {

            if ((int)tracePokemonID != 31)
            {

                v19 = (HandlerParam_ChangeAbility *)BattleHandler_PushWork(a2, EFFECT_CHANGEABILITY, (int)tracePokemonID);
                v19->pokeID = (int)tracePokemonID;
                v19->abilityID = traceAbilityId;
                v19->fSkipSwitchInEvent = 1;
                v19->header.flags |= 0x800000u;
                BattleHandler_StrSetup(&v19->exStr, 2u, 381);
                BattleHandler_AddArg(&v19->exStr, traceAbilityPokemonId);
                BattleHandler_AddArg(&v19->exStr, v19->abilityID);
                BattleHandler_PopWork(a2, v19);
            }
        }
    }

#pragma endregion

#pragma region BadDreams

    int THUMB_BRANCH_IsMonTrapped(BtlClientWk *a1, BattleMon *a2, _BYTE *a3, _WORD *a4)
    {
        int ID;               // r0
        __int16 v7;           // r0
        unsigned int v8;      // r7
        int Value;            // r4
        BattleMon *BattleMon; // [sp+8h] [bp-20h]
        unsigned int Count;   // [sp+Ch] [bp-1Ch]
        u8 ids[24];         // [sp+10h] [bp-18h] BYREF

        ID = BattleMon_GetID(a2);
        v7 = MainModule_PokeIDToPokePos(a1->mainModule, a1->pokeCon, ID);
        Count = MainModule_ExpandExistPokeID(a1->mainModule, a1->pokeCon, v7 | 0x100, ids);
        v8 = 0;
        if (BattleMon_HasType(a2, TYPE_GHOST))
        {
            return 4;
        }
        if (Count)
        {
            while (1)
            {
                BattleMon = PokeCon_GetBattleMon(a1->pokeCon, ids[v8]);
                Value = BattleMon_GetValue(BattleMon, VALUE_EFFECTIVE_ABILITY);
                BattleMon_GetID(BattleMon); // what's going on here

                if (Value == ABIL023_SHADOW_TAG && DoesMonHaveShadowTag((int)a1, a2) && !BattleMon_HasType(a2, TYPE_GHOST))
                {
                    break;
                }
                if (Value == ABIL123_BAD_DREAMS && BattleMon_CheckIfMoveCondition(a2, CONDITION_SLEEP))
                {
                    break;
                }
                if (Value == ABIL071_ARENA_TRAP && IsMonTrappedByArenaTrap(a1, a2) || Value == ABIL042_MAGNET_PULL && IsMonSteelType((int)a1, (int)a2))
                {
                    break;
                }
                v8 = (v8 + 1);
                if (v8 >= Count)
                {
                    goto LABEL_11;
                }
            }
            *a3 = BattleMon_GetID(BattleMon);
            *a4 = Value;
            return 0;
        }
        else
        {
        LABEL_11:
            if (BattleMon_CheckIfMoveCondition(a2, CONDITION_BLOCK) || BattleMon_CheckIfMoveCondition(a2, CONDITION_BIND))
            {
                *a3 = BattleMon_GetID(a2);
                *a4 = 0;
                return 3;
            }
            else
            {
                return 4;
            }
        }
    }

    void HandlerBadDreamsTrapping(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {
        __int16 ExistFrontPokePos; // r0
        unsigned int NumTargets;   // r6
        unsigned int v10;          // r4
        BattleMon *BattleMon;      // r0
        unsigned char v12[24];     // [sp+0h] [bp-18h] BYREF

        *v12 = a4;
        if (!MainModule_IsAllyMonID(BattleEventVar_GetValue(VAR_MON_ID), a3))
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, v12);
            v10 = 0;
            if (NumTargets)
            {
                while (1)
                {
                    BattleMon = Handler_GetBattleMon(a2, v12[v10]);
                    if (!BattleMon_CheckIfMoveCondition(BattleMon, CONDITION_SLEEP) || BattleMon_HasType(BattleMon, TYPE_GHOST))
                    {
                        break;
                    }
                    v10 = (v10 + 1);
                    if (v10 >= NumTargets)
                    {
                         BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                    }
                }
            }
            else
            {
                 BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
    }

    ABILITY_TRIGGERTABLE BadDreamsHandlers[] = {
        {EVENT_TURN_CHECK_END, (ABILITY_HANDLER_FUNC)HandlerBadDreams},      // 22
        {EVENT_PREVENT_RUN, (ABILITY_HANDLER_FUNC)HandlerBadDreamsTrapping}, // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddBadDreams(_DWORD *a1)
    {
        *a1 = 2;
        return BadDreamsHandlers;
    }

#pragma endregion

#pragma region ShadowTag

    int THUMB_BRANCH_SAFESTACK_HandlerShadowTag(int a1, ServerFlow *a2, unsigned int a3, int a4)
    {
        unsigned __int8 Value;     // r0
        int result;                // r0
        __int16 ExistFrontPokePos; // r0
        unsigned int NumTargets;   // r6
        unsigned int v10;          // r4
        BattleMon *BattleMon;      // r0
        unsigned char v12[24];     // [sp+0h] [bp-18h] BYREF

        *v12 = a4;
        Value = BattleEventVar_GetValue(VAR_MON_ID);
        result = MainModule_IsAllyMonID(Value, a3);
        if (!result)
        {
            ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
            NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, v12);
            v10 = 0;
            if (NumTargets)
            {
                while (1)
                {
                    BattleMon = Handler_GetBattleMon(a2, v12[v10]);
                    result = BattleMon_GetValue(BattleMon, VALUE_EFFECTIVE_ABILITY);
                    if (result == 23 || BattleMon_HasType(BattleMon, TYPE_GHOST))
                    {
                        break;
                    }
                    v10 = (v10 + 1);
                    if (v10 >= NumTargets)
                    {
                        return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
                    }
                }
            }
            else
            {
                return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
            }
        }
        return result;
    }
    // int THUMB_BRANCH_SAFESTACK_HandlerShadowTag(int a1, ServerFlow *a2, unsigned int a3, int a4)
    // {
    //     unsigned __int8 Value;     // r0
    //     int result;                // r0
    //     __int16 ExistFrontPokePos; // r0
    //     unsigned int NumTargets;   // r6
    //     unsigned int v10;          // r4
    //     BattleMon *BattleMon;      // r0
    //     u8 v12[5];                 // [sp+0h] [bp-18h] BYREF
    //     *v12 = a4;
    //     Value = BattleEventVar_GetValue(VAR_MON_ID);
    //     result = MainModule_IsAllyMonID(Value, a3);
    //     if (!result)
    //     {
    //         ExistFrontPokePos = Handler_GetExistFrontPokePos(a2, a3);
    //         NumTargets = Handler_ExpandPokeID(a2, ExistFrontPokePos | 0x100, v12);
    //         v10 = 0;
    //         if (NumTargets)
    //         {
    //             while (v10 < NumTargets)
    //             {
    //                 BattleMon = Handler_GetBattleMon(a2, v12[v10]);
    //                 if (BattleMon_GetValue(BattleMon, VALUE_EFFECTIVE_ABILITY) == ABIL023_SHADOW_TAG || BattleMon_HasType(BattleMon, TYPE_NORMAL) || BattleMon_HasType(BattleMon, TYPE_GHOST))
    //                 {
    //                     return result;
    //                 }
    //                 v10++;
    //             }
    //             return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    //         }
    //         else
    //         {
    //             return BattleEventVar_RewriteValue(VAR_MOVE_FAIL_FLAG, 1);
    //         }
    //     }
    //     return result;
    // }

#pragma endregion

#pragma region Justified
    void HandlerJustifiedDefense(int a1, int a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_DEFENDING_MON))
        {
            if ( BattleEventVar_GetValue(VAR_MOVE_TYPE) == TYPE_DARK)
            {
                BattleEventVar_MulValue(VAR_RATIO, 2048);
            }
        }
    }

    ABILITY_TRIGGERTABLE JustifiedHandlers[] = {
        {EVENT_MOVE_DAMAGE_REACTION_1, (ABILITY_HANDLER_FUNC)HandlerJustified}, // 22
        {EVENT_ATTACKER_POWER, (ABILITY_HANDLER_FUNC)HandlerJustifiedDefense},  // 22
    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddJustified(_DWORD *a1)
    {
        *a1 = 2;
        return JustifiedHandlers;
    }

#pragma endregion

#pragma region Analytic
    void THUMB_BRANCH_HandlerAnalytic(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (HandlerCommon_IsMonLastInTurnOrder(a2, a3))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 5325);
            }
        }
    }

#pragma endregion

#pragma region AngerPoint

    int THUMB_BRANCH_SAFESTACK_ServerControl_MoveExecuteCheck1(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        MoveFailCause v7;                      // r6
        ActionIgnoreReason actionIgnoreReason; // r0
        int v9;                                // r1
        ConditionData MoveConditionData;       // r0
        u16 PreviousMove;                      // r0                          // r0
        int v15;                               // [sp+Ch] [bp-24h]
        MoveCondition Status;                  // [sp+10h] [bp-20h]
        u8 abil;
        v15 = 0;
        ServerControl_CheckMoveExeSleepCure(a1, a2);
        Status = BattleMon_GetStatus(a2);
        abil = BattleMon_GetValue(a2, VALUE_EFFECTIVE_ABILITY);
        PreviousMove = BattleMon_GetPreviousMoveID(a2);
        if (Status != CONDITION_SLEEP || (v7 = MOVEFAIL_SLEEP, ServerEvent_MoveExecuteFail(a1, a2, a3, 2)))
        {
            v15 = ServerControl_CheckMoveExeFreezeThaw(a1, a2, a3);
            Status = BattleMon_GetStatus(a2);
            if (Status == CONDITION_FREEZE && !v15)
            {
                v7 = MOVEFAIL_FREEZE;
                goto LABEL_50;
            }
            actionIgnoreReason = a1->actionIgnoreReason;
            if (actionIgnoreReason == REASON_OVERLEVELED)
            {
                v7 = MOVEFAIL_IGNORE;
                goto LABEL_50;
            }
            if (actionIgnoreReason == REASON_FALL_ASLEEP)
            {
                v7 = MOVEFAIL_IGNORE_FALL_ASLEEP;
                goto LABEL_50;
            }
            if (!a4)
            {
                v9 = Move_SearchIndex(a2, a3);
                if (v9 != 4 && !Move_GetPP(a2, v9))
                {
                    v7 = MOVEFAIL_PPZERO;
                    goto LABEL_50;
                }
            }
            v7 = (MoveFailCause)ServerEvent_CheckMoveExecute(a1, a2, a3, EVENT_MOVE_EXECUTE_CHECK1);
            if (v7 == MOVEFAIL_NULL)
            {
                if (BattleMon_GetTurnFlag(a2, TURNFLAG_FLINCH))
                {
                    v7 = MOVEFAIL_FLINCH;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_DISABLEMOVE) && a3 != 165)
                {
                    MoveConditionData = BattleMon_GetMoveCondition(a2, CONDITION_DISABLEMOVE);
                    if (a3 == Condition_GetParam(MoveConditionData))
                    {
                        v7 = MOVEFAIL_DISABLE;
                        goto LABEL_50;
                    }
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_HEALBLOCK) && getMoveFlag(a3, FLAG_HEALING))
                {
                    v7 = MOVEFAIL_HEALBLOCK;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_GRAVITY) && getMoveFlag(a3, FLAG_GROUNDED_BY_GRAVITY))
                {
                    v7 = MOVEFAIL_GRAVITY;
                    goto LABEL_50;
                }
                if (a3 == 165)
                {
                    goto LABEL_60;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_ENCORE) && PreviousMove != 165 && PreviousMove != a3)
                {
                    v7 = MOVEFAIL_MOVELOCK;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_MOVELOCK) && a3 != PreviousMove){
                    v7 = MOVEFAIL_MOVELOCK;
                    goto LABEL_50;
                }
                if (BattleMon_CheckIfMoveCondition(a2, CONDITION_TAUNT) && !PML_MoveIsDamaging(a3))
                {
                    v7 = MOVEFAIL_TAUNT;
                    goto LABEL_50;
                }
                if (BattleField_CheckEffect(EFFECT_IMPRISON) && BattleField_CheckImprison(a1->pokeCon, a2, a3))
                {
                    v7 = MOVEFAIL_IMPRISON;
                }
                else
                {
                LABEL_60:
                    if (ServerControl_CheckConfusionHit(a1, a2))
                    {
                        v7 = MOVEFAIL_CONFUSION;
                    }
                    else if (Status == CONDITION_PARALYSIS)
                    {
                        if (abil == ABIL062_GUTS || abil == ABIL063_MARVEL_SCALE || abil == ABIL039_INNER_FOCUS)
                        {
                        }
                        else if (abil == ABIL095_QUICK_FEET && RollEffectChance(0x4u))
                        {
                            v7 = MOVEFAIL_PARALYSIS;
                        }
                        else
                        {
                            if (RollEffectChance(0x19u)) v7 = MOVEFAIL_PARALYSIS;
                        }
                    }
                    else if (ServerControl_CheckAttract(a1, a2))
                    {
                        v7 = MOVEFAIL_ATTRACT;
                    }
                }
            }
        }
    LABEL_50:
        if (v7)
        {
            ServerControl_MoveExecuteFail(a1, a2, a3, v7);
            return 1;
        }
        else
        {
            if (Status == CONDITION_SLEEP)
            {
                ServerDisplay_MoveExecuteFailMessage(a1, (int)a2, a3, 2u);
                ServerDisplay_AddEffectAtPosition(a1, a2, 598);
            }
            else if (v15)
            {
                if (Status == CONDITION_FREEZE)
                {
                    ServerDisplay_CureStatus(a1, a2, 3, 0);
                    ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 303, BattleMon_GetID(a2), a3, -65536);
                }
            }
            return 0;
        }
    }

    void THUMB_BRANCH_ServerControl_MoveUseNotEffective(ServerFlow *a1, int a2, int a3)
    {
        int v6; // r7
        BattleMon *mon;
        mon = Handler_GetBattleMon(a1, a2);
        TurnFlag_Set(mon, TURNFLAG_MOVEFAILED);
        v6 = HEManager_PushState((int *)&a1->heManager);
        ServerEvent_MoveUseEnd_Common(a1, a2, a3, EVENT_MOVE_EXECUTE_NOEFFECT);
        HEManager_PopState((int *)&a1->heManager, v6);
    }

    void THUMB_BRANCH_ServerEvent_CheckMoveExecuteFail(ServerFlow *a1, BattleMon *a2, int a3, int a4)
    {
        int ID; // r0
        TurnFlag_Set(a2, TURNFLAG_MOVEFAILED);

        BattleEventVar_Push();
        ID = BattleMon_GetID(a2);
        BattleEventVar_SetConstValue(VAR_MON_ID, ID);
        BattleEventVar_SetConstValue(VAR_MOVE_ID, a3);
        BattleEventVar_SetConstValue(VAR_FAIL_CAUSE, a4);
        BattleEvent_CallHandlers(a1, EVENT_MOVE_EXECUTE_FAIL);
        BattleEventVar_Pop();
    }

    #if TESTING_UNHOOKED_FUNCTIONS
    void THUMB_BRANCH_flowsub_CheckNoEffect_TypeAffinity(
    #else 
    void THUMB_BRANCH_ServerFlow_CheckNoEffect_TypeEffectiveness(
    #endif
        ServerFlow *a1,
        MoveParam *a2,
        BattleMon *attacker,
        PokeSet *targets,
        EffectivenessRecorder *effrec)
    {
        BattleMon *i;     // r5
        int v8;           // r7
        unsigned int v11; // r5
        EffectivenessRecorder_Init(effrec);
        j_j_PokeSet_SeekStart_7(targets);
        for (i = j_PokeSet_SeekNext_29(targets); i; i = j_PokeSet_SeekNext_28(targets))
        {
            v8 = ServerEvent_CheckMoveDamageEffectiveness(a1, attacker, i, a2, 1);
            EffectivenessRecorder_Add(effrec, BattleMon_GetID(i), v8);
            if (!v8)
            {
                // TurnFlag Added Here
                if (!MainModule_IsAllyMonID(i->ID, attacker->ID))  TurnFlag_Set(attacker, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_8(targets, i);
                EffectivenessCounter_CountUp(&a1->effectivenessCounter, a1, attacker, i, 0);
                v11 = j_MainModule_PokeIDToClientID(BattleMon_GetID(attacker));
                if (v11 == MainModule_GetPlayerClientID(a1->mainModule))
                {
                    RecordData_Increment(a1->mainModule, 75);
                }
            }
        }
    }

    
    // FIGURE OUT WHAT THE FUCK IS GOING ON HERE 
    #if TESTING_UNHOOKED_FUNCTIONS
    void THUMB_BRANCH_flowsub_CheckWazaAvoid(
    #else 
    void THUMB_BRANCH_ServerFlow_CheckNoEffect_Avoid(
    #endif
        ServerFlow *a1, 
        unsigned __int16 *a2, 
        BattleMon *a3, 
        PokeSet *a4)
    {
        BattleMon *i; // r4
        if (j_PokeSet_GetCountMax_4(a4) != 1 || j_PokeSet_Get_8(a4, 0) != a3)
        {
            j_PokeSet_SeekStart_20(a4);
            for (i = j_PokeSet_SeekNext_41(a4); i; i = j_PokeSet_SeekNext_40(a4))
            {
                if (!ServerEvent_SkipAvoidCheck(a1, a3, i, a2) && !ServerEvent_CheckHit(a1, a3, i, a2))
                {
                    if (!MainModule_IsAllyMonID(i->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                    j_PokeSet_Remove_10(a4, i);
                    ServerDisplay_MoveAvoid(a1, i);
                }
            }
        }
    };

    #if TESTING_UNHOOKED_FUNCTIONS
    void THUMB_BRANCH_flowsub_CheckPokeHideAvoid(
    #else 
    void THUMB_BRANCH_ServerFlow_CheckNoEffect_Hiding(
    #endif 
        ServerFlow *a1, 
        unsigned __int16 *a2, 
        BattleMon *a3, 
        PokeSet *a4)
    {
        BattleMon *i; // r4

        j_j_PokeSet_SeekStart_19(a4);
        for (i = j_j_PokeSet_SeekNext_38(a4); i; i = j_j_PokeSet_SeekNext_39(a4))
        {
            if (!ServerControl_IsGuaranteedHit(a1, a3, i))
            {
                if (ServerEvent_CheckHiding(a1, a3, i))
                {
                    if (!MainModule_IsAllyMonID(i->ID, a3->ID))  TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                    j_j_PokeSet_Remove_9(a4, i);
                    ServerDisplay_MoveAvoid(a1, i);
                }
            }
        }
    };

    void THUMB_BRANCH_SAFESTACK_flowsub_CheckNoEffect_Protect(ServerFlow *a1, unsigned __int16 *a2, BattleMon *a3, PokeSet *a4, int a5)
    {
        BattleMon *i; // r7
        BattleMon *j; // r7
        BattleMon *k; // r7
        BattleMon *m; // r7
        // int ID;       // r0
        j_PokeSet_SeekStart_10(a4);

        for (i = j_PokeSet_SeekNext_18(a4); i; i = j_PokeSet_SeekNext_19(a4))
        {
            if (!ServerControl_IsGuaranteedHit(a1, a3, i) && ServerControl_CheckNoEffectCore(a1, a2, (int)a3, i, a5, 43))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(i->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_0(a4, i);
            }
        }
        j_PokeSet_SeekStart_11(a4);
        for (j = j_PokeSet_SeekNext_20(a4); j; j = j_PokeSet_SeekNext_21(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, j, a5, 44))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(j->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_1(a4, j);
            }
        }

        if (getMoveFlag(*a2, FLAG_BLOCKED_BY_PROTECT))
        {
            j_PokeSet_SeekStart_12(a4);
            for (k = j_PokeSet_SeekNext_22(a4); k; k = j_PokeSet_SeekNext_23(a4))
            {
                if (BattleMon_GetTurnFlag(k, TURNFLAG_PROTECT) && !ServerEvent_CheckProtectBreak(a1, a3))
                {
                    if (!(SEARCH_ARRAY(nonStatusProtectMoves, BattleMon_GetPreviousMoveID(k)) && PML_MoveGetCategory(*a2) == 0))
                    {
                        // Add TurnFlag modification for the Attacking Pokemon here
                        if (!MainModule_IsAllyMonID(k->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                        j_PokeSet_Remove_2(a4, k);
                        //ID = BattleMon_GetID(k);
                        ServerDisplay_AddMessageImpl(a1->serverCommandQueue, 91, 523,  BattleMon_GetID(k), -65536);
                        if (BattleMon_GetPreviousMoveID(k) == MOVE376_SPIKY_SHIELD && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ) {
                            HandlerParam_Damage *v7 = (HandlerParam_Damage *)BattleHandler_PushWork(a1, EFFECT_DAMAGE, a3->ID);
                            v7->pokeID = a3->ID;
                            v7->damage = DivideMaxHPZeroCheck(a3, 8u);
                            BattleHandler_StrSetup(&v7->exStr, 2u, 1189);
                            BattleHandler_AddArg(&v7->exStr, v7->pokeID);
                            BattleHandler_PopWork(a1, v7);}

                        if (BattleMon_GetPreviousMoveID(k) == MOVE462_SILK_TRAP && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ) {
                            HandlerParam_ChangeStatStage *v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a1, EFFECT_CHANGESTATSTAGE, a3->ID);
                            v8->pokeID[0] = a3->ID;
                            v8->poke_cnt = 1;
                            v8->fMoveAnimation = 1;
                            v8->rankType = STATSTAGE_SPEED;
                            v8->rankVolume = -2;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1264);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID[0]);
                            BattleHandler_PopWork(a1, v8);}
                        
                        if (BattleMon_GetPreviousMoveID(k) == MOVE262_OBSTRUCT && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ){
                            HandlerParam_ChangeStatStage *v8 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a1, EFFECT_CHANGESTATSTAGE, a3->ID);
                            v8->pokeID[0] = a3->ID;
                            v8->poke_cnt = 1;
                            v8->fMoveAnimation = 1;
                            v8->rankType = STATSTAGE_DEFENSE;
                            v8->rankVolume = -2;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1339);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID[0]);
                            BattleHandler_PopWork(a1, v8);}
                        
                        if (BattleMon_GetPreviousMoveID(k) == MOVE559_BANEFUL_BUNKER && getMoveFlag(*a2, FLAG_CONTACT)
                            #if USING_OVERRIDE_CONTACT
                            && !overrideContact(k, (MoveID)*a2)
                            #endif
                        ){
                            HandlerParam_AddCondition *v8 = (HandlerParam_AddCondition *)BattleHandler_PushWork(a1, EFFECT_ADDCONDITION, a3->ID);
                            v8->pokeID = a3->ID;
                            v8->sickID = CONDITION_POISON;
                            v8->sickCont = MakeBasicStatus(CONDITION_POISON);
                            v8->fAlmost = 0;
                            BattleHandler_StrSetup(&v8->exStr, 2u, 1336);
                            BattleHandler_AddArg(&v8->exStr, v8->pokeID);
                            BattleHandler_PopWork(a1, v8);}
                    }
                }
            }
        }
        j_PokeSet_SeekStart_13(a4);
        for (m = j_PokeSet_SeekNext_24(a4); m; m = j_PokeSet_SeekNext_25(a4))
        {
            if (ServerControl_CheckNoEffectCore(a1, a2, (int)a3, m, a5, 45))
            {
                // Add TurnFlag modification for the Attacking Pokemon here
                if (!MainModule_IsAllyMonID(m->ID, a3->ID)) TurnFlag_Set(a3, TURNFLAG_MOVEFAILED);
                j_PokeSet_Remove_3(a4, m);
            }
        }
    }

    void THUMB_BRANCH_BattleMon_TurnCheck(BattleMon *a1)
    {
        u8 didMoveFail = BattleMon_GetTurnFlag(a1, TURNFLAG_MOVEFAILED);
        sys_memset(a1->TurnFlag, 0, 2u);
        if (a1->TurnCount < 9999u) ++a1->TurnCount;
        if (didMoveFail) TurnFlag_Set(a1, TURNFLAG_MOVEFAILEDLASTTURN);
        setOverheatLastTurnByte(a1, (getOverheatByte(a1)) ? 1 : 0);
        setOverheatByte(a1, 0);
        MoveDamageRec_ClearTurn(a1);
    }

    void HandlerAngerPointPower(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (BattleMon_GetTurnFlag(Handler_GetBattleMon(a2, a3), TURNFLAG_MOVEFAILEDLASTTURN))
            {
                BattleEventVar_MulValue(VAR_MOVE_POWER_RATIO, 6144);
            }
        }
    }

    void HandlerAngerPointSpeed(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            if (BattleMon_GetTurnFlag(Handler_GetBattleMon(a2, a3), TURNFLAG_MOVEFAILEDLASTTURN))
            {
                BattleEventVar_MulValue(VAR_RATIO, 6144);
            }
        }
    }

    void HandlerAngerPointMessage(int a1, ServerFlow *a2, int a3)
    {
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID))
        {
            if (BattleMon_GetTurnFlag(Handler_GetBattleMon(a2, a3), TURNFLAG_MOVEFAILED))
            {
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPIN, (int)a3);
                HandlerParam_Message *v1 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
                BattleHandler_StrSetup(&v1->str, 2u, 1243);
                BattleHandler_AddArg(&v1->str, a3);
                BattleHandler_PopWork(a2, v1);
                BattleHandler_PushRun(a2, EFFECT_ABILITYPOPUPOUT, (int)a3);
            }
        }
    }

    ABILITY_TRIGGERTABLE AngerPointHandlers[] = {
        {EVENT_MOVE_EXECUTE_END, (ABILITY_HANDLER_FUNC)HandlerAngerPointMessage},  // 22
        {EVENT_MOVE_EXECUTE_FAIL, (ABILITY_HANDLER_FUNC)HandlerAngerPointMessage}, // 22
        {EVENT_MOVE_POWER, (ABILITY_HANDLER_FUNC)HandlerAngerPointPower},
        {EVENT_CALC_SPEED, (ABILITY_HANDLER_FUNC)HandlerAngerPointSpeed},

    };

    ABILITY_TRIGGERTABLE *THUMB_BRANCH_EventAddAngerPoint(_DWORD *a1)
    {
        *a1 = 4;
        return AngerPointHandlers;
    }

#pragma endregion
}

#pragma region UIDefinitions
    struct MsgFileEntry
    {
        int Offset;
        u16 CharCount;
        u16 Padding;
    };
    struct SWAN_ALIGNED(4) MsgData
    {
        void *FileHandle;
        int RawData;
        MsgFileEntry CurrentEntry;
        int MsgOfsInArc;
        ArcTool *MsgArc;
        __int16 HeapID;
        u8 LanguageId;
        u8 IsAllPreload;
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
        PokeParty *pokeParty;
        PokeParty *AllyPokeParty;
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
        MsgData *msgData;
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
    enum InputButton
    {
        KEY_A = 0x1,
        KEY_B = 0x2,
        KEY_SELECT = 0x4,
        KEY_START = 0x8,
        KEY_RIGHT = 0x10,
        KEY_LEFT = 0x20,
        KEY_UP = 0x40,
        KEY_DOWN = 0x80,
        KEY_R = 0x100,
        KEY_L = 0x200,
        KEY_X = 0x400,
        KEY_Y = 0x800,
        KEY_TOUCH = 0x1000,
        KEY_LID = 0x2000,
    };
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
    extern "C" int PML_MoveGetMaxPP(int wazaId, unsigned int ppUpStage);
    extern "C" bool PML_MoveIsAlwaysHit(int wazaId);
    extern "C" int sub_202D8EC(PartyPkm *a1);
    extern "C" int BattleClient_GetMyID(void *a1);
    extern "C" PokeParty *MainModule_GetPokeParty(void *a1, int a2);
    extern "C" int MainModule_IsCompetitiveBattleType(void *a1);
    extern "C" PokeParty *MainModule_GetAllyPokeParty(void *a1, char a2);
    extern "C" int sub_219C86C(void *a1, char a2);
    extern "C" int MainModule_CheckNumFrontPos(void *a1, char a2);
    extern "C" char *sub_689B7C8(void *a1);
    extern "C" void *BtlvEffectMain_GetTCBManager();
    extern "C" void *BtlvEffectMain_GetPalAnm();
    extern "C" void *MainModule_GetGameData(void *a1);
    extern "C" int sub_21CF250(BtlvCore *a1);
    extern "C" InputButton GCTX_HIDGetHeldKeys();
    extern "C" int MainModule_IsPartnerBattle(MainModule *a1);
    extern "C" u32 PML_PersonalGetParamSingle(u16 species, u16 form, PersonalField field);
    extern "C" int sub_21FA27C(PokeListMain *a1, unsigned int a2);
    extern "C" int PokeList_IsAlreadyInBattle(PokeListMain *a1, int a2);
    extern "C" int PokeList_IsEgg(PokeListMain *a1);
    extern "C" int PokeList_IsAlreadySelectedForSwitchIn(PokeListMain *a1, int a2);
    extern "C" int PokeList_DetermineSwitchInFailCause(PokeListMain *a1);
    extern "C" StrBuf *GFL_MsgDataLoadStrbufNew(MsgData *msgData, int msgId);
    extern "C" void GFL_WordSetFormatStrbuf(void *wordSet, StrBuf *dest, StrBuf *source);
    extern "C" void loadPokemonNicknameToStrbuf(void *a1, int a2, PartyPkm *a3);
    extern "C" void GFL_StrBufFree(StrBuf *pStrbuf);
    extern "C" u32 GetScanSetting()
    {
        EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
        u16 *lvl_cap_ptr = EventWork_GetWkPtr(eventWork, 16438);
        return (*lvl_cap_ptr) ? 1 : 0;
    }
    #if TRYING_BATTLESCAN_EXPANSION
    #define FIELD_D8_ABILITY   0u
    #define FIELD_D8_POKETYPES    16u
    #define FIELD_D8_ABILITY_MASK    (0xFFFFu << FIELD_D8_ABILITY)   // 0x0000FFFF
    #define FIELD_D8_POKETYPES_MASK     (0xFFu   << FIELD_D8_POKETYPES)    // 0x00FF0000
    #define FIELD_D8_GASTRO_MASK   (1u << 24u)  // 0x01000000
    #define FIELD_D8_APPEARED_MASK  (1u << 25u)
    #define FIELD_D8_WILD_MASK  (1u << 26u)
    #define FIELD_D8_ILLUSION_MASK (1u << 27u)

    extern "C" u32 setBit(u32 value, u32 mask, u8 flag){
        value &= ~mask;
        if (flag) value |= mask;
        return value;
    }

    extern "C" u8 getBit(u32 value, u32 mask) {
        return (value & mask) != 0;
    }

    extern "C" u32 setU16(u32 value, u16 abil){
        value &= ~FIELD_D8_ABILITY_MASK;
        value |= ((u32)abil << FIELD_D8_ABILITY);
        return value;
    }
    extern "C" u16 getU16(u32 value){
        return (u16)((value & FIELD_D8_ABILITY_MASK) >> FIELD_D8_ABILITY);
    }

    extern "C" u32 setU8(u32 value, u8 types) {
        value &= ~FIELD_D8_POKETYPES_MASK;
        value |= ((u32)types << FIELD_D8_POKETYPES);
        return value;
    }
    extern "C" u8 getU8(u32 value) {
        return (u8)((value & FIELD_D8_POKETYPES_MASK) >> FIELD_D8_POKETYPES);
    }

    #endif 
    extern "C" u8 isWild(u32 value){
        #if TESTING_BATTLESCAN_EXPANSION
        return getBit(value, FIELD_D8_WILD_MASK);
        #else 
        return (value == 2);
        #endif 
    }
#pragma endregion 

#pragma region UIFunctions

extern "C" void findBattleMon(BtlvCore *a1, PokeParty *a2, int clientId)
{
    BattleParty party = a1->pokeCon->party[clientId];
    BattleMon *mon;
    u32 value;
    u8 i; 
    u8 j;

    /* WILD BATTLES */
    if (a1->mainModule->btlSetup->btlType == 0)
    {
        for (j = 0; j < party.memberCount; j++)
        {
            if (party.mons[j]->partySrc->Base.pid != a2->Pokemon[j].Base.pid) continue;
            #if TRYING_BATTLESCAN_EXPANSION 
            mon = party.mons[j];
            value = a2->Pokemon[j].field_D8;
            value = setBit(value, FIELD_D8_WILD_MASK, 1);
            value = setU16(value, BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY));
            value = setU8(value, BattleMon_GetPokeType(mon));
            value = setBit(value, FIELD_D8_GASTRO_MASK, BattleMon_CheckIfMoveCondition(mon, CONDITION_GASTROACID));
            a2->Pokemon[j].field_D8 = value;
            #else 
            a2->Pokemon[j].field_D8 = 2;
            #endif 
        }
        return;
    };

    for (i = 0; i < party.memberCount; i++)
    {
        if (party.mons[i]->partySrc->Base.pid != a2->Pokemon[i].Base.pid) continue;

        #if TRYING_BATTLESCAN_EXPANSION
        mon = party.mons[i];
        value = a2->Pokemon[i].field_D8; 
        value = setBit(value, FIELD_D8_APPEARED_MASK,  (mon->AppearedTurn == 10000));
        value = setU16(value, BattleMon_GetValue(mon, VALUE_EFFECTIVE_ABILITY));
        value = setU8(value, BattleMon_GetPokeType(mon));
        value = setBit(value, FIELD_D8_GASTRO_MASK, BattleMon_CheckIfMoveCondition(mon, CONDITION_GASTROACID));
        a2->Pokemon[i].field_D8 = value;
        #else 
        a2->Pokemon[i].field_D8 = (party.mons[i]->AppearedTurn == 10000) ? 1 : 0;
        #endif 
        
        if (party.mons[i]->Ability == ABIL149_ILLUSION)
        {
            for (j = 0; j < party.memberCount; j++)
            {
                if (party.mons[j]->partySrc->Base.pid != a2->Pokemon[j].Base.pid) continue;
                #if TRYING_BATTLESCAN_EXPANSION
                a2->Pokemon[j].field_D8 = setBit(a2->Pokemon[j].field_D8, FIELD_D8_ILLUSION_MASK, 1);
                #else 
                a2->Pokemon[j].field_D4 = 1;
                #endif 
            }
            break;
        }
    }
}

extern "C" void THUMB_BRANCH_SAFESTACK_StartBottomScreenMenu(BtlvCore *a1, BattlePokeListData *a2, int a3, char a4, __int16 a5)
{
    u8 v9;                  // r0
    int IsAllyInMultiBattle; // r0
    int v12;                 // [sp+0h] [bp-18h]
    u8 isRightBumper = (GCTX_HIDGetHeldKeys() & 256);
    u8 isLeftBumper = (GCTX_HIDGetHeldKeys() & 512);
    if (a3 != 0) { v12 = BattleClient_GetMyID(a1->client); }
    else if (isLeftBumper) { v12 = (MainModule_IsPartnerBattle(a1->mainModule)) ? ((a1->mainModule->btlSetup->btlType == 0) ? 1 : 3) : 1;}
    else if (isRightBumper) { v12 = (MainModule_IsPartnerBattle(a1->mainModule)) ? 1 : 1; }
    else { v12 = BattleClient_GetMyID(a1->client); }
    a2->pokeParty = MainModule_GetPokeParty(a1->mainModule, v12);
    if (v12 != BattleClient_GetMyID(a1->client)) findBattleMon(a1, a2->pokeParty, v12);
    v9 = a3 != 3 && MainModule_IsCompetitiveBattleType(a1->mainModule);
    a2->IsBagDisabled = v9;
    a2->AllyPokeParty = (v9) ?  MainModule_GetAllyPokeParty(a1->mainModule, v12) : 0;
    a2->ListMode = a3;
    a2->AllyClientID = (v9) ? sub_219C86C(a1->mainModule, v12) : 0;
    a2->NumPartyMembers = (BtlSetup_GetBattleStyle(a1->mainModule) == BTL_STYLE_ROTATION) ? 3 : MainModule_CheckNumFrontPos(a1->mainModule, v12);
    a2->field_3C = (isLeftBumper || isRightBumper) ? 1 : 0;
    a2->SelectedMon = (a3 == 4 || a3 == 5) ? a4 : 0;
    a2->InfoPokeIndex = a4;
    a2->IsSelectedMonTrapped = a5;
    a2->MoveInfoMoveIndex = 0;
    a2->heapID = a1->heapID;
    a2->Font = a1->Font1;
    a2->battleStyle = (BattleStyle)BtlSetup_GetBattleStyle(a1->mainModule);
    a2->cursorFlag = (int)sub_689B7C8(a1->btlvScd);
    a2->tcbmanager = BtlvEffectMain_GetTCBManager();
    a2->palAnm = BtlvEffectMain_GetPalAnm();
    a2->gameData = MainModule_GetGameData(a1->mainModule);
    a2->IsFinished = 0;
    a2->SoundEffectFlag = sub_21CF250(a1);
    a2->CommErrorFlag = 0;
    a2->EndFlag = 0;
}

extern "C" void THUMB_BRANCH_SAFESTACK_PokeList_LoadPokeData(PokeListMain *a1, PartyPkm *a2, PokeListData *a3)
{
    u32 Param;             // r0
    int ExpForPkm_Wrapper; // r0
    char v7;               // r1
    u8 i;        // r6
    PokeList_MoveData *v9; // r4
    char v10;              // r0
    u8 isEnemy;
    a3->partyPkm = a2;
    u8 PokeTypes; 
    if (a2)
    {
        a3->Species = PokeParty_GetParam(a2, PF_Species, 0);
        if (a3->Species)
        {
            // k::Printf("\nChecking the Pokeball and Nickname struccts for Pokemon #%d!\nPokeballl is %d\nPF_NicknameStr is %d\nPF_NicknameRaw is %d\nPF_NicknameStrKeepFlags is %d\nPF_NicknameRawKeepFlags is %d\nPF_HasNickname is %d\n",
            //     a3->Species,
            //     PokeParty_GetParam(a2, PF_Pokeball, 0),
            //     PokeParty_GetParam(a2, PF_NicknameStrBuf, 0),
            //     PokeParty_GetParam(a2, PF_NicknameRaw, 0),
            //     PokeParty_GetParam(a2, PF_NicknameStrBufKeepFlags, 0),
            //     PokeParty_GetParam(a2, PF_NicknameRawKeepFlags, 0),
            //     PokeParty_GetParam(a2, PF_HasNickname, 0)
            // );
            isEnemy = a1->pokeListSetupData->field_3C;
            #if TRYING_BATTLESCAN_EXPANSION
            a3->Species = (getBit(a2->field_D8, FIELD_D8_APPEARED_MASK) && isEnemy && GetScanSetting()) ? 0 : a3->Species;
            a3->Species = getBit(a2->field_D8, FIELD_D8_ILLUSION_MASK) ? 0 : a3->Species;
            #else 
            a3->Species = (a2->field_D8 == 1 && isEnemy && GetScanSetting()) ? 0 : a3->Species;
            a3->Species = (a2->field_D4 == 1) ? 0 : a3->Species;
            #endif
            a3->Forme = PokeParty_GetParam(a3->partyPkm, PF_Forme, 0);
            a3->CurrentHP = PokeParty_GetParam(a3->partyPkm, PF_NowHP, 0);
            a3->MaxHP = PokeParty_GetParam(a3->partyPkm, PF_MaxHP, 0);
            if (isEnemy && GetScanSetting()) 
            {
                a3->Attack = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_ATK);
                a3->Defense = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_DEF);
                a3->Speed = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPE);
                a3->SpecialAttack = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPA);
                a3->SpecialDefense = PML_PersonalGetParamSingle(a3->Species, a3->Forme, Personal_SPD);
            }
            else
            {
                a3->Attack = PokeParty_GetParam(a3->partyPkm, PF_ATK, 0);
                a3->Defense = PokeParty_GetParam(a3->partyPkm, PF_DEF, 0);
                a3->Speed = PokeParty_GetParam(a3->partyPkm, PF_SPE, 0);
                a3->SpecialAttack = PokeParty_GetParam(a3->partyPkm, PF_SPA, 0);
                a3->SpecialDefense = PokeParty_GetParam(a3->partyPkm, PF_SPD, 0);
            }
            #if TRYING_BATTLESCAN_EXPANSION
            PokeTypes = getU8(a2->field_D8);
            a3->Type1 = PokeTypePair_GetType1(PokeTypes); //PokeParty_GetParam(a3->partyPkm, PF_Type1, 0);
            a3->Type2 = PokeTypePair_GetType2(PokeTypes); 
            a3->Ability = (getBit(a2->field_D8, FIELD_D8_GASTRO_MASK) ? 0 : getU16(a2->field_D8));
            #else 
            a3->Type1 = PokeParty_GetParam(a3->partyPkm, PF_Type1, 0);
            a3->Type2 = PokeParty_GetParam(a3->partyPkm, PF_Type2, 0);
            a3->Ability = PokeParty_GetParam(a3->partyPkm, PF_Ability, 0);
            #endif 

            a3->Level = PokeParty_GetParam(a3->partyPkm, PF_Level, 0) & 0x7F | a3->Level & 0x80;
            a3->Level = (PokeParty_GetParam(a3->partyPkm, PF_IsNotNidoran, 0) == 1) ? a3->Level & 0x7F : a3->Level | 0x80;
            a3->SexStatusIsEgg = PokeParty_GetSex(a3->partyPkm) & 7 | a3->SexStatusIsEgg & 0xF8;
            a3->SexStatusIsEgg = (8 * sub_202D8EC(a3->partyPkm)) & 0x7F | a3->SexStatusIsEgg & 0x87;
            a3->SexStatusIsEgg = (PokeParty_GetParam(a3->partyPkm, PF_IsEgg, 0) << 7) | a3->SexStatusIsEgg & 0x7F;
            a3->Item = PokeParty_GetParam(a3->partyPkm, PF_Item, 0);
            a3->Experience = (isEnemy) ? 0 : PokeParty_GetParam(a3->partyPkm, PF_Experience, 0);
            ExpForPkm_Wrapper = getExpForPkm_Wrapper(a3->partyPkm);
            v7 = a3->Level;
            a3->ExpForLevel = (isEnemy) ? 0 : ExpForPkm_Wrapper;
            if ((v7 & 0x7F) != 100) ExpForPkm_Wrapper = PML_UtilGetPkmLvExp(a3->Species, a3->Forme, ((v7 & 0x7F) + 1));
            a3->ExpToNextLevel = (isEnemy) ? 0 : ExpForPkm_Wrapper;
            for (i = 0; i < 4; ++i)
            {
                u8 missingPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0) < (PML_MoveGetParam(PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0), MVDATA_BASEPP) + ((isWild(a2->field_D8)) ? 0 : 3));
                if (isEnemy && !missingPP && GetScanSetting()) continue;
                PokeList_MoveData *v9 = &a3->MoveData[i];
                v9->MoveID = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0);
                if (v9->MoveID)
                {
                    v9->CurrentPP = PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 58), 0);
                    v9->MaxPP = PML_MoveGetParam(PokeParty_GetParam(a3->partyPkm, (PkmField)(i + 54), 0), MVDATA_BASEPP) + ((isWild(a2->field_D8) || !isEnemy) ? 0 : 3);
                    v9->Type = PML_MoveGetParam(v9->MoveID, MVDATA_TYPE);
                    v9->Category = PML_MoveGetParam(v9->MoveID, MVDATA_CATEGORY);
                    v9->Accuracy = (PML_MoveIsAlwaysHit(v9->MoveID)) ? 0 :  PML_MoveGetParam(v9->MoveID, MVDATA_ACCURACY);
                    v9->Power = PML_MoveGetParam(v9->MoveID, MVDATA_POWER);
                }
                
            }
        }
    }
    else
    {
        a3->Species = 0;
    }
}

extern "C" int THUMB_BRANCH_SAFESTACK_PokeList_DetermineSwitchInFailCause(PokeListMain *a1)
{
    int SelectedMonID; // r0
    PokeListData *v3;  // r5

    SelectedMonID = PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon);
    v3 = &a1->pokeListData[SelectedMonID];
    if (a1->pokeListSetupData->field_3C)
    {
        return 7;
    }
    if (sub_21FA27C(a1, SelectedMonID))
    {
        return 1;
    }
    if (!v3->CurrentHP)
    {
        return 2;
    }
    if (PokeList_IsAlreadyInBattle(a1, a1->pokeListSetupData->SelectedMon))
    {
        return 3;
    }
    if (PokeList_IsEgg(a1))
    {
        return 5;
    }
    if (PokeList_IsAlreadySelectedForSwitchIn(a1, a1->pokeListSetupData->SelectedMon) == 1)
    {
        return 4;
    }
    if (a1->pokeListSetupData->IsSelectedMonTrapped)
    {
        return 6;
    }
    return 0;
}

extern "C" int THUMB_BRANCH_SAFESTACK_PokeList_LoadSwitchInFailMessage(PokeListMain *a1)
{
    StrBuf *StrbufNew; // r7
    int SelectedMonID; // r6
    unsigned int v4;   // r0
    int v5;            // r1
    MsgData *msgdata;  // r0
    int v7;            // r1
    MsgData *v8;       // r0

    SelectedMonID = PokeList_GetSelectedMonID(a1, a1->pokeListSetupData->SelectedMon);
    v4 = PokeList_DetermineSwitchInFailCause(a1);
    if (v4 <= 7)
    {
        if (v4 == 0)
        {
            return 1;
        }
        else if (v4 == 1)
        {
            v5 = 90;
            msgdata = a1->msgData;
            goto LABEL_4;
        }
        else if (v4 == 2)
        {
            v7 = 87;
            v8 = a1->msgData;
            goto LABEL_6;
        }
        else if (v4 == 3)
        {
            v7 = 86;
            v8 = a1->msgData;
            goto LABEL_6;
        }
        else if (v4 == 4)
        {
            v7 = 103;
            v8 = a1->msgData;
            goto LABEL_6;
        }
        else if (v4 == 7)
        {
            v5 = 108;
            msgdata = a1->msgData;
            goto LABEL_4;
        }
        else if (v4 == 5)
        {
            v5 = 89;
            msgdata = a1->msgData;
        LABEL_4:
            StrbufNew = GFL_MsgDataLoadStrbufNew(msgdata, v5);
        }
        else if (v4 == 6)
        {
            SelectedMonID = a1->pokeListSetupData->InfoPokeIndex;
            v7 = 88;
            v8 = a1->msgData;
        LABEL_6:
            StrbufNew = GFL_MsgDataLoadStrbufNew(v8, v7);
            loadPokemonNicknameToStrbuf(a1->WordSetSystem, 0, a1->pokeListData[SelectedMonID].partyPkm);
        }
        else if (v4 == 7)
        {
        }
        else
        {
        }
    }
    GFL_WordSetFormatStrbuf(a1->WordSetSystem, (StrBuf *)a1->StrBuf, StrbufNew);
    GFL_StrBufFree(StrbufNew);
    return 0;
}
#pragma endregion