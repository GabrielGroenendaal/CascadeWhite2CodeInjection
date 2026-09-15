
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
    #endif 