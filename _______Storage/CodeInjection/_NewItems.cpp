#include "swan-master/newitems.h"
#include "NitoKernel/include/kPrint.h"

extern "C"
{

 
    // a1 is the Party Pokemon
    // a2 is the item index for the item
    // a3 is 
    // a4 is 
    // a5 is the Heap ID

    int THUMB_BRANCH_PokeList_ApplyItemEffect(PartyPkm *a1, unsigned int a2, int a3, unsigned __int16 a4, int a5)
    {
        int v6;             // r7
        ItemData *DataFile; // r4
        int v8;             // r6
        int v9;             // r0
        int v10;            // r0
        u16 v11;            // r6
        u16 v12;            // r0
        u32 PkmLvExp;       // r0
        unsigned int v14;   // r0
        int v15;            // r0
        int i;              // r6
        int v17;            // r0
        int v18;            // r2
        int v19;            // r2
        int v20;            // r2
        int v21;            // r2
        int v22;            // r2
        int v23;            // r2
        signed __int32 v25; // r0
        int v26;            // r6
        int v27;            // r0
        int v28;            // r0
        int v29;            // r0
        u16 v30;            // [sp+8h] [bp-80h]
        int v33;            // [sp+14h] [bp-74h]
        int v34;            // [sp+18h] [bp-70h]
        int v35;            // [sp+1Ch] [bp-6Ch]
        int v36;            // [sp+20h] [bp-68h]
        int v37;            // [sp+24h] [bp-64h]
        int v38;            // [sp+28h] [bp-60h]
        int v39;            // [sp+2Ch] [bp-5Ch]
        signed int v40;     // [sp+30h] [bp-58h]
        int v41;            // [sp+34h] [bp-54h]
        int v42;            // [sp+38h] [bp-50h]
        int v43;            // [sp+3Ch] [bp-4Ch]
        int v44;            // [sp+40h] [bp-48h]
        int v45;            // [sp+44h] [bp-44h]
        int v46;            // [sp+48h] [bp-40h]
        int v47;            // [sp+4Ch] [bp-3Ch]
        u32 data;           // [sp+50h] [bp-38h]
        u32 Param;          // [sp+54h] [bp-34h]
        signed __int32 v50; // [sp+58h] [bp-30h]

        v30 = a2;
        v6 = 0;
        //k::printf("\n1. We have entered the function!\n\nOur Parameters are:\n a1: %d\n\n a2: %d\n\n a3: %d\n\n a4: %d \n\n a5: %d\n\nu16 a5 is %d\n\n", a1, a2, a3, a4, a5, (HeapID)a5);

        DataFile = (ItemData *)PML_ItemReadDataFile(a2, 0, 0x17);
        //k::printf("\n2. We have acquired Datafile\n");
        // Checks to see if there are any actual Battle relevant effects for the item
        if (PML_ItemGetParam(DataFile, ITSTAT_HAS_BATTLE_STATS) != 1)
        {
             //k::print("\n3. This means this isn't a battle item!\n");
            goto LABEL_85; // Frees up the heap and exits function
        }

        // v6 and v8 are basically state trackers users to navigate through the most confusing iteration process i've seen in gamefreak's code
    
        v8 = 0;

        // Gets a value between 0-17 to see if there is a status condition
        Param = PokeParty_GetParam(a1, PF_StatusCond, 0);
        data = Param;
         //k::printf("\n4. Check for Status Condition: %d\n", data);
        if (PML_ItemGetParam(DataFile, ITSTAT_AILMENT_SLP))
        {
            data = 0;
            v8 = 1;
        }
        if (PML_ItemGetParam(DataFile, ITSTAT_AILMENT_PSN))
        {
            data = 0;
            v8 = 1;
        }
        if (PML_ItemGetParam(DataFile, ITSTAT_AILMENT_BRN))
        {
            data = 0;
            v8 = 1;
        }
        if (PML_ItemGetParam(DataFile, ITSTAT_AILMENT_FRZ))
        {
            data = 0;
            v8 = 1;
        }
        if (PML_ItemGetParam(DataFile, ITSTAT_AILMENT_PAR))
        {
            data = 0;
            v8 = 1;
        }

        // if data = 0, it means the item cures a status
        if (Param != data)
        {
            PokeParty_SetParam(a1, PF_StatusCond, data);
            //k::printf("\n5. We got into the status cure function\n", data);
            v6 = 1;
        }

        // gets the current hp and max hp for the pokemon
        v42 = PokeParty_GetParam(a1, PF_NowHP, 0);
        v40 = PokeParty_GetParam(a1, PF_MaxHP, 0);
        //k::printf("\n5. Now we're checking for current HP %d and max HP %d\n", v42, v40);
        // checks to see if it's a reviving item
        if ((PML_ItemGetParam(DataFile, ITSTAT_BOOST_REVIVE) || PML_ItemGetParam(DataFile, ITSTAT_BOOST_SACRED_ASH)) && !PML_ItemGetParam(DataFile, ITSTAT_BOOST_RARECANDY))
        {
             //k::printf("\n6. This checks if we need to apply a heal to an unconcious pokemon\n");
            // checks to see if the current HP is 0
            if (!v42)
            {
                v9 = PML_ItemGetParam(DataFile, ITSTAT_HEAL_AMOUNT);
                PokeList_ApplyHeal(a1, 0, v40, v9);
                v6 = 1;
            }
        }
        // if not a reviving item
        else
        {   
            //k::printf("\n7. This checks if we need to apply a heal\n");
            // skips forward if it's not an HP recovering item
            if (!PML_ItemGetParam(DataFile, ITSTAT_FLAG_HPREPLENISH))
            {
                goto LABEL_25;
            }
            //k::printf("\n8. Now this heals only if current HP < max HP\n");
            // heals only if the current hp is less than the max HP
            if (v42 < v40)
            {
                v10 = PML_ItemGetParam(DataFile, ITSTAT_HEAL_AMOUNT);
                PokeList_ApplyHeal(a1, v42, v40, v10);
                //k::printf("\n9. Heal Successful!\n");
                v6 = 1;
            }
        }
        v8 = 1;
    LABEL_25:

        // Rare Candy Handler
        v50 = PokeParty_GetParam(a1, PF_Level, 0);
         //k::printf("\n10. The Pokemon Level is %d\n", v50);
        if (PML_ItemGetParam(DataFile, ITSTAT_BOOST_RARECANDY))
        {
            // Makes sure the current level is less than 100

             //k::print("\n11. We're at the rare candy handler\n");
            if (v50 < 100)
            {
                 //k::printf("\n12. We have checked the current level against 100!\n");
                v11 = PokeParty_GetParam(a1, PF_Species, 0);
                v12 = PokeParty_GetParam(a1, PF_Forme, 0);
                PkmLvExp = PML_UtilGetPkmLvExp(v11, v12, (v50 + 1)); // Gets the EXp needed to be current level + 1
                PokeParty_SetParam(a1, PF_Experience, PkmLvExp);
                //k::printf("\n13. We have applied the experience to the pokemon!\n");

                PokeParty_RecalcStats(a1);
                if (!v42)
                {
                    v14 = PokeParty_GetParam(a1, PF_MaxHP, 0);
                    PokeList_ApplyHeal(a1, 0, v14, v14 - v40);
                }
                v6 = 1;
            }
            v8 = 1;
        }
        //k::printf("\n14. We're checking if this is an evolution stone!\n");
        if (PML_ItemGetParam(DataFile, ITSTAT_BOOST_EVOSTONE))
        {
            v8 = 1;
        }
        //k::printf("\n15. We're checking if this is a PP Booster!\n");
        if (PML_ItemGetParam(DataFile, ITSTAT_BOOST_PP1))
        {
            if (PokeList_ApplyMaxPPIncrease(a1, a3, 1) == 1)
            {
                v6 = 1;
            }
        }
        else
        {
            //k::printf("\n16. We're checking if this is PP Max\n");
            if (!PML_ItemGetParam(DataFile, ITSTAT_BOOST_PPMAX))
            {
                goto LABEL_41;
            }
            if (PokeList_ApplyMaxPPIncrease(a1, a3, 3) == 1)
            {
                v6 = 1;
            }
        }
        v8 = 1;
    LABEL_41:
    //k::printf("\n17. We're at Label 41\n");
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_PPREPLENISH))
        {
                //k::printf("\n18. This item replenishes PP\n");

            v15 = PML_ItemGetParam(DataFile, ITSTAT_PP_GAIN);
            if (PokeParty_AddPP(a1, a3, v15) == 1)
            {
                v6 = 1;
            }
        }
        else
        {
            if (!PML_ItemGetParam(DataFile, ITSTAT_FLAG_PPREPLENISH_FULL))
            {
                goto LABEL_51;
            }
            for (i = 0; i < 4; ++i)
            {
                v17 = PML_ItemGetParam(DataFile, ITSTAT_PP_GAIN);
                if (PokeParty_AddPP(a1, i, v17) == 1)
                {
                    v6 = 1;
                }
            }
        }
        v8 = 1;
    LABEL_51:
    //k::printf("\n18. We're at label 51\n");
        v43 = PokeParty_GetParam(a1, PF_EvHP, 0);
        v41 = PokeParty_GetParam(a1, PF_EvATK, 0);
        v39 = PokeParty_GetParam(a1, PF_EvDEF, 0);
        v38 = PokeParty_GetParam(a1, PF_EvSPE, 0);
        v47 = PokeParty_GetParam(a1, PF_EvSPA, 0);
        v46 = PokeParty_GetParam(a1, PF_EvSPD, 0);
        v45 = PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_ABOVE100);
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_HP))
        {
            //k::printf("\n19. This increases HP EVs\n");
            v44 = PML_ItemGetParam(DataFile, ITSTAT_EV_HP);
            if (v44 > 0 && PokeParty_GetParam(a1, PF_Species, 0) == 292)
            {
            LABEL_85:
                //k::print("\n20. We're at label 85\n");
                GFL_HeapFree(DataFile);
                return 0;
            }
            v18 = PokeList_GetEVsAppliedAfterLimit(v43, v46 + v47 + v38 + v41 + v39, v44, v45);
            if (v18 != -1)
            {
                v43 = v18;
                PokeParty_SetParam(a1, PF_EvHP, v18);
                PokeParty_RecalcStats(a1);
                v6 = 1;
            }
            if (v44 > 0)
            {
                v8 = 1;
            }
        }
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_ATK))
        {
            //k::print("\n21. This increases atk EVs\n");
            v33 = PML_ItemGetParam(DataFile, ITSTAT_EV_ATK);
            v19 = PokeList_GetEVsAppliedAfterLimit(v41, v46 + v47 + v38 + v43 + v39, v33, v45);
            if (v19 != -1)
            {
                v41 = v19;
                PokeParty_SetParam(a1, PF_EvATK, v19);
                PokeParty_RecalcStats(a1);
                v6 = 1;
            }
            if (v33 > 0)
            {
                v8 = 1;
            }
        }

        // UNUSUAL CANDY //
        // We're using Defense EV increasing Items for our unusual candy, we could also check the specific value to make sure we're only targeting certain items
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_DEF)){
            if (v50 < 100)
            {
                v11 = PokeParty_GetParam(a1, PF_Species, 0);
                v12 = PokeParty_GetParam(a1, PF_Forme, 0);
                PkmLvExp = PML_UtilGetPkmLvExp(v11, v12, (v50 + 1)) - 1; // Gets the EXp needed to be current level + 1
                PokeParty_SetParam(a1, PF_Experience, PkmLvExp);
                PokeParty_RecalcStats(a1);
                v6 = 1;
            }
            v8 = 1;
        }
        // if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_DEF))
        // {
        //     v34 = PML_ItemGetParam(DataFile, ITSTAT_EV_DEF);
        //     v20 = CheckEVs(v39, v46 + v47 + v38 + v43 + v41, v34, v45);
        //     if (v20 != -1)
        //     {
        //         v39 = v20;
        //         PokeParty_SetParam(a1, PF_EvDEF, v20);
        //         PokeParty_RecalcStats(a1);
        //         v6 = 1;
        //     }
        //     if (v34 > 0)
        //     {
        //         v8 = 1;
        //     }
        // }

        // STRESS TESTER //
        // We're using Speed EV increasing items for our Stress Tester.
        // We could also check specific value to make sure we're targeting only certain items
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_SPE))
        {
             //k::print("\n24. This increases Speed EVs\n");
            v35 = PML_ItemGetParam(DataFile, ITSTAT_EV_SPE);
            PokeParty_SetParam(a1, PF_NowHP, v35);
             PokeParty_RecalcStats(a1);
            v6 = 1;
            if (v35 > 0)
            {
                v8 = 1;
            }
        }
        // if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_SPE))
        // {
        //     v35 = PML_ItemGetParam(DataFile, ITSTAT_EV_SPE);
        //     v21 = CheckEVs(v38, v46 + v47 + v39 + v43 + v41, v35, v45);
        //     if (v21 != -1)
        //     {
        //         v38 = v21;
        //         PokeParty_SetParam(a1, PF_EvSPE, v21);
        //         PokeParty_RecalcStats(a1);
        //         v6 = 1;
        //     }
        //     if (v35 > 0)
        //     {
        //         v8 = 1;
        //     }
        // }
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_SPA))
        {
            //k::print("\n25. This increases SpA EVs\n");
            v36 = PML_ItemGetParam(DataFile, ITSTAT_EV_SPA);
            v22 = PokeList_GetEVsAppliedAfterLimit(v47, v46 + v38 + v39 + v43 + v41, v36, v45);
            if (v22 != -1)
            {
                v47 = v22;
                PokeParty_SetParam(a1, PF_EvSPA, v22);
                PokeParty_RecalcStats(a1);
                v6 = 1;
            }
            if (v36 > 0)
            {
                v8 = 1;
            }
        }
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_SPD))
        {
            //k::print("\n26. This increases SpD EVs\n");
            v37 = PML_ItemGetParam(DataFile, ITSTAT_EV_SPD);
            v23 = PokeList_GetEVsAppliedAfterLimit(v46, v47 + v38 + v39 + v43 + v41, v37, v45);
            if (v23 != -1)
            {
                PokeParty_SetParam(a1, PF_EvSPD, v23);
                PokeParty_RecalcStats(a1);
                v6 = 1;
            }
            if (v37 > 0)
            {
                v8 = 1;
            }
        }
        //k::print("\n27. This increases Speed EVs\n");
        if (!v6 && v8 == 1)
        {
            goto LABEL_85;
        }
        //k::print("\n28 We made it past all the EVs, now happiness\n");
        v25 = PokeParty_GetParam(a1, PF_Happiness, 0);
        v26 = v25;
        //k::printf("\n29: Current Happiness is %d\n", v26);
        if (v25 >= 100)
        {
            //k::print("\n30. More Friendship shit\n");
            if (v25 >= 200)
            {
                 //k::print("\n31. Even More Friendship shit\n");
                if (v25 <= 255 && PML_ItemGetParam(DataFile, ITSTAT_FLAG_FRIENDSHIP_ADD3))
                {
                     //k::print("\n32. Even EVen More Friendship shit\n");
                    v29 = PML_ItemGetParam(DataFile, ITSTAT_FRIENDSHIP3);
                    PokeList_ApplyFriendship(a1, v26, v29, v30, a4, 0x17);
                    GFL_HeapFree(DataFile);
                    return v6;
                }
            }
            else if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_FRIENDSHIP_ADD2))
            {
                 //k::print("\n33. Even even More Friendship shit\n");
                v28 = PML_ItemGetParam(DataFile, ITSTAT_FRIENDSHIP2);
                PokeList_ApplyFriendship(a1, v26, v28, v30, a4, 0x17);
                GFL_HeapFree(DataFile);
                return v6;
            }
        }
        else if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_FRIENDSHIP_ADD1))
        {
             //k::print("\n34. So much more More Friendship shit\n");
            v27 = PML_ItemGetParam(DataFile, ITSTAT_FRIENDSHIP1);
            PokeList_ApplyFriendship(a1, v26, v27, v30, a4, 0x17);
            GFL_HeapFree(DataFile);
            return v6;
        }
        GFL_HeapFree(DataFile);
        return v6;
    }
}