
#include "../definitions/A_CodeInjection.h"

extern "C" bool checkIfConsumableItem(int a1)
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

/* Unnerve Buff */
extern "C" bool THUMB_BRANCH_SAFESTACK_HandlerUnnerveSkipCheck(BattleEventItem *a1, int a2, int a3, int a4, u16 a5, unsigned __int8 a6)
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