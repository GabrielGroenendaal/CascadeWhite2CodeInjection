#include "_preStatus.h"

extern "C" void HandlerPreStatusMarvelScaleOnAI(int a1, ServerFlow *a2, int a3)
    {
        HandlerParam_AddCondition *v6;
        BattleMon *poke;
        if (a3 == BattleEventVar_GetValue(VAR_MON_ID) && a3 >= 6 && !checksIfWildBattle(a2))
        {
            poke = Handler_GetBattleMon(a2, a3);
            triggerPreStatus(a2, a3, ((poke->Sex == 0) ? CONDITION_POISON : CONDITION_PARALYSIS));
        }
    }

ABILITY_TRIGGERTABLE MarvelScaleHandlers[] = {
        {EVENT_DEFENDER_GUARD, (ABILITY_HANDLER_FUNC)HandlerMarvelScale},         // 27
        {EVENT_SWITCH_IN, (ABILITY_HANDLER_FUNC)HandlerPreStatusMarvelScaleOnAI}, // 28
    };

// was: THUMB_BRANCH_EventAddMarvelScale
extern "C" ABILITY_TRIGGERTABLE *e3f(_DWORD *a1)
    {
        *a1 = 2;
        return MarvelScaleHandlers;
    }