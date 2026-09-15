
#include "../definitions/A_CodeInjection.h"

extern "C" bool checksIfWildBattle(ServerFlow *a1)
{
    return a1->mainModule->btlSetup->btlType == 0;
}

extern "C" void triggerPreStatus(ServerFlow *a1, u8 pokePos, MoveCondition condition){
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
