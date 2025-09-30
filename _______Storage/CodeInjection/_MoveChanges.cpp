#include "swan-master/codeinjection.h"
#include "NitoKernel/include/kPrint.h"

extern "C"
{

    void THUMB_BRANCH_HandlerSkullBash(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 556);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_DEFENSE;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_ATTACK;
            v6->rankVolume = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    void HandlerMeteorBeam(int a1, ServerFlow *a2, unsigned int *a3)
    {
        HandlerParam_Message *v5;         // r6
        HandlerParam_ChangeStatStage *v6; // r0

        if ((int)a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v5 = (HandlerParam_Message *)BattleHandler_PushWork(a2, EFFECT_MESSAGE, (int)a3);
            BattleHandler_StrSetup((u16 *)&v5->str, 2u, 556);
            BattleHandler_AddArg((u16 *)&v5->str, (int)a3);
            BattleHandler_PopWork(a2, v5);
            v6 = (HandlerParam_ChangeStatStage *)BattleHandler_PushWork(a2, EFFECT_CHANGESTATSTAGE, (int)a3);
            v6->poke_cnt = 1;
            v6->pokeID[0] = (int)a3;
            v6->rankType = STATSTAGE_SPECIAL_ATTACK;
            v6->rankVolume = 1;
            v6->fMoveAnimation = 1;
            BattleHandler_PopWork(a2, v6);
        }
    }

    int NewHandlerSkyUppercut(int a1, ServerFlow *a2, int a3)
    {
        int result;           // r0
        int v6;               // r6
        BattleMon *PokeParam; // r7

        if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON))
        {
            v6 = (unsigned __int8)BattleEventVar_GetValue(VAR_ATTACKING_MON);
            PokeParam = Handler_GetPokeParam(a2, v6);
            result = BattleEventVar_GetValue(VAR_POKE_TYPE);
            if (result == TYPE_FLYING)
            {
                return BattleEventVar_RewriteValue(VAR_TYPEEFFECTIVENESS, 1);
            }
        }
        return result;
    }

    int HandlerFreezeDry(int a1, int a2, int a3)
    {
    }

    // int HandlerNewTeleport()
    // {
    //     HandlerParam_AddPosEffect *v5;     // r6
    //     HandlerParam_SetConditionFlag *v6; // r0
    //     HandlerParam_Switch *v7;           // r0

    //     if (a3 == BattleEventVar_GetValue(VAR_ATTACKING_MON) && Handler_GetFightEnableBenchPokeNum(a2, a3))
    //     {
    //         if (Handler_CheckReservedMemberChangeAction(a2))
    //         {
    //             v5 = BattleHandler_PushWork(a2, EFFECT_ADDPOSEFFECT, a3);
    //             v5->effect = 4;
    //             v5->pos = Handler_PokeIDToPokePos(a2, a3);
    //             *(v5 + 3) = a3;
    //             *(&v5[1] + 12) = 1;
    //             BattleHandler_PopWork(a2, v5);
    //             v6 = BattleHandler_PushWork(a2, EFFECT_SETCONDITIONFLAG, a3);
    //             v6->pokeID = a3;
    //             v6->flag = CONDITIONFLAG_BATONPASS;
    //             v6->header.flags |= 0x1000000u;
    //             BattleHandler_PopWork(a2, v6);
    //             v7 = BattleHandler_PushWork(a2, EFFECT_SWITCH, a3);
    //             v7->pokeID = a3;
    //             v7->fIntrDisable = 1;
    //             v7->header.flags |= 0x1000000u;
    //             BattleHandler_PopWork(a2, v7);
    //         }
    //     }
    // }

    // int HandlerPartingShot()
    // {
    // }

    typedef struct
    {
        int triggerValue;
        MOVE_HANDLER_FUNC function;
    } MOVE_TRIGGERTABLE;

    MOVE_TRIGGERTABLE MoveTriggerTable[] =
        {
            {0x96, (MOVE_HANDLER_FUNC)HandlerMeteorBeam},
            {0xA0, (MOVE_HANDLER_FUNC)HandlerUturn},
            {0xA0, (MOVE_HANDLER_FUNC)HandlerUturn},
            {0x3E, (MOVE_HANDLER_FUNC)NewHandlerSkyUppercut},
            {0x3E, (MOVE_HANDLER_FUNC)HandlerFreezeDry}};

    // Meteor Beam
    int *THUMB_BRANCH_EventAddFreezeShock(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[0].triggerValue;
    }

    // Parting Shot
    int *THUMB_BRANCH_EventAddLockOn(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[1].triggerValue;
    }

    // Teleport
    int *THUMB_BRANCH_EventAddTeleport(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[2].triggerValue;
    }

    int *THUMB_BRANCH_EventAddSkyUppercut(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[3].triggerValue;
    }

    int *THUMB_BRANCH_EventAddMiracleEye(unsigned int *a1)
    {
        *a1 = 1;
        return (int *)&MoveTriggerTable[4].triggerValue;
    }
}