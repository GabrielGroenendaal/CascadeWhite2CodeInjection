#include "../definitions/A_CodeInjection.h"

extern "C" void HandlerAftermathNew(int a1, ServerFlow *a2, unsigned int *a3)
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

ABILITY_TRIGGERTABLE AftermathHandlers[] = {
    {EVENT_MOVE_FLINCH_CHANCE, (ABILITY_HANDLER_FUNC)HandlerAftermathNew}, // 22

};

// was: EventAddAftermathNew
extern "C" ABILITY_TRIGGERTABLE * e6a(_DWORD *a1)
{
    *a1 = 1;
    return AftermathHandlers;
}