#include "../definitions/A_CodeInjection.h"

extern "C" void THUMB_BRANCH_SAFESTACK_HandlerTrace(int a1, ServerFlow *a2, unsigned int tracePokemonID, _DWORD *a4)
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
