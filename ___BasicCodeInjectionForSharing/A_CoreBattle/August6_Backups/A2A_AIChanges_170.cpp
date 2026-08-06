

#include "settings.h"
#include "codeinjection_new.h"
extern "C" int SearchArray(const u16 *const arr, const u32 arrSize, const u32 value)
{
    for (u32 i = 0; i < arrSize; ++i)
    {
        if (arr[i] == value)
        {
            return 1;
        }
    }
    return 0;
}
#define SEARCH_ARRAY(arr, value) SearchArray(arr, ARRAY_COUNT(arr), value)

// THE IDEA IS THAT WE'RE PUTTING ALL THE STUFF FROM OVERLAY 170 HERE 
// THE FUNCTIONS IN THAT OVERLAY ARE NO LONGER TASKED WITH READING FROM THE STATIC VARIABLE 
// I THINK THAT THIS MIGHT ACTUALLY WORK 
extern "C" {
    
    MoveID NEW_PROTECT_COUNTER_MOVES[8] = {
        MOVE203_ENDURE, MOVE182_PROTECT, MOVE197_DETECT, MOVE469_WIDE_GUARD, MOVE376_SPIKY_SHIELD,
        MOVE462_SILK_TRAP, MOVE262_OBSTRUCT, MOVE559_BANEFUL_BUNKER};
    
    int THUMB_BRANCH_AI075_GetProtectCount(ScriptVM *a1, TrainerAIEnv *a2)
    {
        unsigned int v3;                   // r0
        int BattlePosFromCommandArg;       // r0
        BattleMon *BattleMonFromBattlePos; // r5
        u16 ConsecutiveMoveCount;          // r0
        u16 previousMove;
        v3 = VM_Read32(a1);
        BattlePosFromCommandArg = GetBattlePosFromCommandArg(a2, v3);
        BattleMonFromBattlePos = GetBattleMonFromBattlePos(a2, BattlePosFromCommandArg);
        previousMove = BattleMon_GetPreviousMoveID(BattleMonFromBattlePos);

        if (SEARCH_ARRAY((const u16*)NEW_PROTECT_COUNTER_MOVES, previousMove))//previousMove == MOVE182_PROTECT || previousMove == MOVE197_DETECT || previousMove == MOVE203_ENDURE || previousMove == MOVE469_WIDE_GUARD || previousMove == MOVE462_SILK_TRAP || previousMove == MOVE376_SPIKY_SHIELD || previousMove == MOVE559_BANEFUL_BUNKER || previousMove == MOVE262_OBSTRUCT)
        {
            ConsecutiveMoveCount = BattleMon_GetConsecutiveMoveCount(BattleMonFromBattlePos);
        }
        else
        {
            ConsecutiveMoveCount = 0;
        }
        a2->param = ConsecutiveMoveCount;
        return a2->result;
    }

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
        u8 MoveCount;
        u16 LoopMoveID;
        u8 LoopMoveCategory;
        u8 LoopMoveCategoryCheck;
        u8 i;

        MoveCount = BattleMon_GetMoveCount(a1);
        LoopMoveCategoryCheck = 0;
        i = 0;
        do
        {
            LoopMoveID = Move_GetID(a1, i);
            LoopMoveCategory = PML_MoveGetParam(LoopMoveID, MVDATA_CATEGORY);
            if (!LoopMoveCategory)
            {
                i++;
                continue;
            }
            if (!LoopMoveCategoryCheck && Move_GetPP(a1, i))
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

    int THUMB_BRANCH_AI094_GetPreviousMoveCategory(ScriptVM *a1, TrainerAIEnv *a2)
    {
        u8 LoopMoveCategoryResult;
        LoopMoveCategoryResult = CheckTargetMoves(a2->defender);
        a2->param = LoopMoveCategoryResult;
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        -------------------------- CHECK FOR KILLING BLOWS (FOR SETUP) -----------------------------------
        --------------------------------------------------------------------------------------------------

        Checks each pokemon in front of them to see if they can kill them with any of their moves.
        If the target is faster than the user, and the setup move they're using doesn't boost speed past the
        target, then checks for even 50% damage.

        Originally:
            AI072_Nop

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

    int THUMB_BRANCH_AI105_WillUserFaint_Setup(ScriptVM *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        u8 pokeCount;
        BattleMon *defender;
        u8 opposingPokePos[5];
        u8 k;
        int destination;

        destination = VM_Read32(a1);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
        for (k = 0; k < pokeCount; k++)
        {
            u8 i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            u8 MoveCount = BattleMon_GetMoveCount(defender);
            u16 currentHp = BattleMon_GetValue(a2->attacker, VALUE_CURRENT_HP);
            do
            {
                u16 damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), true, false);


                // If the target is faster the the Pokemon using the set up move, doubles the damage
                // now checking for a 2HKO
                if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) > multiplySpeed(a2->moveID, Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1)))
                {
                    damage *= 2;
                }

                // If currentHP is less than or equal to damage, performs the jump
                if (AIConditionalJump(a1, 6, currentHp, damage, destination))
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

        Originally:
            AI104_Nop
    */

    int THUMB_BRANCH_AI046_CheckDamageForPriority(ScriptVM *a1, TrainerAIEnv *a2)
    {

        __int16 ExistFrontPokePos; // r0
        u8 pokeCount;
        BattleMon *defender;
        BattleMon *reference;
        u8 opposingPokePos[5];
        u8 k;
        u8 battlePos;
        u16 moveId = a2->moveID;

        battlePos = GetBattlePosFromCommandArg(a2, VM_Read32(a1));
        reference = GetBattleMonFromBattlePos(a2, battlePos);
        int destination;

        destination = VM_Read32(a1);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, reference->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

        for (k = 0; k < pokeCount; k++)
        {
            u8 i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            u8 MoveCount = BattleMon_GetMoveCount(defender);
            u16 currentHp = BattleMon_GetValue(reference, VALUE_CURRENT_HP);
            do
            {
                u16 damage = Handler_SimulationDamage(a2->serverFlow,
                                                      BattleMon_GetID(defender),
                                                      BattleMon_GetID(a2->attacker),
                                                      Move_GetID(defender, i), true, false);


                // If currentHP is less than or equal to damage, performs the jump]
                if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) > Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
                {
                    if (AIConditionalJump(a1, 6, currentHp, damage, destination))
                    {
                        k = pokeCount;
                        break;
                    }
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

        Originally:
            AI060_Nop
    */
    int THUMB_BRANCH_AI100_TargetDealsNegligibleDamage_Setup(ScriptVM *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        u8 pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        u8 k;
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);
        int destination;

        destination = VM_Read32(a1);

        for (k = 0; k < pokeCount; k++)
        {
            u8 i = 0;
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);
            u8 MoveCount = BattleMon_GetMoveCount(defender);
            u16 currentHp = DivideMaxHPZeroCheck(a2->attacker, 3u);
            do
            {
                u16 damage = Handler_SimulationDamage(a2->serverFlow,
                                                    BattleMon_GetID(a2->defender),
                                                    BattleMon_GetID(a2->attacker),
                                                    Move_GetID(a2->defender, i), true, false);
   
                // If currentHP is less than or equal to damage, performs the jump
                if (currentHp <= damage)
                {
                    return a2->result;
                }
                // Else, incremenets and checks the next move.
                i++;
            } while (i < MoveCount);
        }
        AIConditionalJump(a1, 6, 1, 1, destination);
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------- CHECK ENEMY DAMAGE OUTPUT (FOR DEBUFFS) --------------------------------
        --------------------------------------------------------------------------------------------------

        Checks to see if the target in front of them can deal meaningful damage.
        25% is the current arbitrary point set at which the AI will stop bothering with debuffing moves.
        Iterates through each move the target has and calcs against the user.

        Originally:
            AI062_Nop
    */
    int THUMB_BRANCH_SAFESTACK_AI066_CheckEnemyDamageOutput_Debuffs(ScriptVM *a1, TrainerAIEnv *a2)
    {
        u8 i = 0;
        u8 MoveCount = BattleMon_GetMoveCount(a2->defender);
        u16 currentHp = DivideMaxHPZeroCheck(a2->attacker, 4u);

        int v7 = VM_Read32(a1);
        do
        {
            u16 damage = Handler_SimulationDamage(a2->serverFlow,
                                                BattleMon_GetID(a2->defender),
                                                BattleMon_GetID(a2->attacker),
                                                Move_GetID(a2->defender, i), true, false);
            
            // If currentHP is less than or equal to damage, performs the jump
            if (currentHp <= damage)
            {
                return a2->result;
            }
            // Else, incremenets and checks the next move.
            i++;
        } while (i < MoveCount);

        AIConditionalJump(a1, 6, 1, 1, v7);
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ------------------------------------ CHECK SLEEP TURNS -------------------------------------------
        --------------------------------------------------------------------------------------------------

        Checks to see if the number of remaining sleep turns is greater than one.
        Used for Sleep Talk, Snore, etc.

        Originally:
            AI102_Nop
    */

    int THUMB_BRANCH_AI068_CheckRemainingSleepTurns(ScriptVM *a1, TrainerAIEnv *a2)
    {
        BattleMon *attacker = a2->attacker;
        int destination = VM_Read32(a1);
        if (BattleMon_CheckIfMoveCondition(attacker, CONDITION_SLEEP))
        {
            AIConditionalJump(a1, 0, (attacker->MoveConditionCounter[CONDITION_SLEEP] + 1), Condition_GetTurnMax(&attacker->Conditions[CONDITION_SLEEP]), destination);
        }
        return a2->result;
    }

    /*

        --------------------------------------------------------------------------------------------------
        ----------------------------- CHECK SPEED AGAINST MULTIPLES --------------------------------------
        --------------------------------------------------------------------------------------------------

        This function checks the speed of every enemy pokemon on the field, rather than just the one in front of them.

        Originally:
            AI103_Nop
    */
    int THUMB_BRANCH_AI089_CheckAllPokemonSpeed(ScriptVM *a1, TrainerAIEnv *a2)
    {
        __int16 ExistFrontPokePos; // r0
        u8 pokeCount;
        u8 opposingPokePos[5];
        BattleMon *defender;
        u8 k;
        int destination = VM_Read32(a1);
        ExistFrontPokePos = Handler_GetExistFrontPokePos(a2->serverFlow, (int)a2->attacker->ID);
        pokeCount = Handler_ExpandPokeID(a2->serverFlow, ExistFrontPokePos | 0x100, opposingPokePos);

        for (k = 0; k < pokeCount; k++)
        {
            defender = Handler_GetBattleMon(a2->serverFlow, opposingPokePos[k]);

            if (Handler_CalculateSpeed(a2->serverFlow, defender, 1) < Handler_CalculateSpeed(a2->serverFlow, a2->attacker, 1))
            {
                return a2->result;
            }
        }
        AIConditionalJump(a1, 0, 1, 2, destination);
        return a2->result;
    }
}