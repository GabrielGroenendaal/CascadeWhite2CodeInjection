#include "newitems.h"
#include "kPrint.h"

extern "C"
{

    // a1 is the Party Pokemon
    // a2 is the item index for the item
    // a3 is
    // a4 is
    // a5 is the Heap ID
    #if TOGGLE_TMS
    void THUMB_BRANCH_PokeList_ItemUseMain(PokeList *a1)
    {
        PokeList_Party *v2;                 // r1
        unsigned int ItemUseType;           // r2
        int FaintedPkmSlot;                 // r1
        PartyPkm *Pkm;                      // r0
        unsigned int v6;                    // r1
        u16 Param;                          // r5
        PokeList *v8;                       // r0
        int v9;                             // r1
        int v10;                            // r2
        void *v11;                          // r3
        int SelectedSlot;                   // r1
        PartyPkm *v13;                      // r0
        u32 v14;                            // r0
        unsigned __int16 v15;               // r6
        int v16;                            // r1
        PartyPkm *v17;                      // r0
        u32 v18;                            // r7
        int v19;                            // r6
        PokeList *v20;                      // r0
        PokeList_Message *PokeList_Message; // r1
        int v22;                            // r2
        PokeList *v23;                      // r0
        int v24;                            // r1
        void *v25;                          // r3
        PokeList_Party *v26;                // r1

        v2 = a1->field_28C;
        ItemUseType = v2->ItemUseType;
        k::Printf("\n\nWe are in the basic Item Use Function and the item use is %d\n\n", ItemUseType);

        if (ItemUseType <= 27)
        {
            if (IsEqual(ItemUseType, 0) || IsEqual(ItemUseType, 6) || IsEqual(ItemUseType, 6) || IsEqual(ItemUseType, 9) || IsEqual(ItemUseType, 0xE) || IsEqual(ItemUseType, 0x10) || IsEqual(ItemUseType, 0x12) || IsEqual(ItemUseType, 0x15) || IsEqual(ItemUseType, 0x19) || IsEqual(ItemUseType, 0x1B))
            {
                k::Printf("\n\nWe got in before the function %d\n\n", ItemUseType);
                sub_219B1DC(a1);
                k::Printf("\n\nWe got in after the function %d\n\n", ItemUseType);
                a1->field_D = 2;
                return;
            }
            else if (IsEqual(ItemUseType, 1))
            {
                a1->field_10C = (int)sub_219FEA8(a1, a1->PokeList_Menu, 0, 22, 21u, 0);
                sub_219B1DC(a1);
                a1->field_D = 2;
                return;
            }
            else if (IsEqual(ItemUseType, 3))
            {
                a1->field_14 = 0;
                sub_219B1DC(a1);
                a1->field_D = 2;
                return;
            }
            else if (IsEqual(ItemUseType, 5))
            {
                k::Printf("\n\nDid we get in here?\n");
                if (PokeList_IsItemSacredAsh(a1, v2->ItemID))
                {
                    FaintedPkmSlot = PokeList_GetFaintedPkmSlot(a1);
                    if (FaintedPkmSlot == -1)
                    {
                        PokeList_PrintItemUseFailMessage_Default(a1);
                        a1->field_D = a1->field_C;
                        a1->field_C = 0;
                    }
                    else
                    {
                        a1->SelectedSlot = FaintedPkmSlot;
                        a1->SelectedPkm = PokeParty_GetPkm(a1->field_28C->pokeParty, FaintedPkmSlot);
                        PokeList_PrintItemRecoverMessage(a1, 0);
                        PokeList_ApplyItemEffect(a1->SelectedPkm, a1->field_28C->ItemID, 0, a1->field_28C->field_40, a1->heapId);
                        sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
                        a1->field_24 = 1;
                        a1->field_D = a1->field_C;
                        a1->field_C = 0;
                        PokeList_SubItem(a1, a1->field_28C->ItemID);
                    }
                }
                else if (PokeList_GetItemCountByID(a1, a1->field_28C->ItemID))
                {
                    sub_219B1DC(a1);
                    a1->field_D = 2;
                }
                else
                {
                    a1->field_28C->field_50 = 10;
                    sub_219F83C(a1, a1->pokeList_Message);
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 0, a1->field_28C->ItemID);
                    PokeList_PrintMessage(a1, 191, 1, (int)sub_219DE50);
                    PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                    a1->field_D = a1->field_C;
                    a1->field_C = 0;
                }
                return;
            }
            else if (IsEqual(ItemUseType, 7) || IsEqual(ItemUseType, 8))
            {
                a1->SelectedSlot = v2->SelectedSlot;
                Pkm = PokeParty_GetPkm(v2->pokeParty, v2->SelectedSlot);
                a1->SelectedPkm = Pkm;
                v6 = a1->field_28C->field_58;
                if (v6 >= 4)
                {
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
                    v11 = (void *)sub_219DF48;
                    v8 = a1;
                    v9 = 36;
                    v10 = 0;
                }
                else
                {
                    Param = PokeParty_GetParam(Pkm, (PkmField)(v6 + 54), 0);
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, Param);
                    v8 = a1;
                    v9 = 41;
                    v10 = 1;
                    v11 = (void *)sub_219E018;
                }
                PokeList_PrintMessage(v8, v9, v10, (int)v11);
                PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                SelectedSlot = a1->SelectedSlot;
                a1->field_D = 7;
                a1->field_C = 0;
                a1->field_14 = 0;
                sub_219F008(a1, a1->pokeList_Plate[SelectedSlot], 1);
                return;
            }
            else if (IsEqual(ItemUseType, 0xA))
            {
                a1->SelectedSlot = v2->SelectedSlot;
                v13 = PokeParty_GetPkm(v2->pokeParty, v2->SelectedSlot);
                a1->SelectedPkm = v13;
                if (a1->field_28C->ItemID)
                {
                    v14 = PokeParty_GetParam(v13, PF_Item, 0);
                    v15 = v14;
                    if (v14)
                    {
                        PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                        PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                        sub_219FA58(a1, a1->pokeList_Message, 1, v15);
                        PokeList_PrintMessage(a1, 59, 0, (int)sub_219E0AC);
                        PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                    }
                    else
                    {
                        PokeList_ChangeHeldItem(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                        sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
                        PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                        PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                        PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 1, a1->field_28C->ItemID);
                        PokeList_ChangeArceusForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                        PokeList_ChangeGenesectForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                        if (PokeList_DoesGiratinaNeedFormeChange(a1))
                        {
                            PokeList_ChangeGiratinaToOriginForme(a1, a1->SelectedPkm);
                            PokeList_PrintMessage(a1, 92, 1, (int)sub_219E4F8);
                            a1->field_274 = 1;
                        }
                        else
                        {
                            PokeList_PrintMessage(a1, 92, 1, (int)sub_219DE34);
                        }
                        PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                        a1->field_28C->ItemUseType = 0;
                    }
                }
                else
                {
                    a1->field_28C->ItemUseType = 0;
                    sub_219B1DC(a1);
                    a1->field_D = 2;
                }
                v16 = a1->SelectedSlot;
                a1->field_D = 7;
                a1->field_C = 0;
                a1->field_14 = 1;
                sub_219F008(a1, a1->pokeList_Plate[v16], 1);
                return;
            }
            else if (IsEqual(ItemUseType, 0xB) || IsEqual(ItemUseType, 0xC))
            {
                a1->SelectedSlot = v2->SelectedSlot;
                v17 = PokeParty_GetPkm(v2->pokeParty, v2->SelectedSlot);
                a1->SelectedPkm = v17;
                v18 = PokeParty_GetParam(v17, PF_Item, 0);
                PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                if (v18)
                {
                    v19 = 65;
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 1, v18);
                    PokeList_Message = a1->pokeList_Message;
                    v20 = a1;
                    v22 = 2;
                }
                else
                {
                    v19 = 92;
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    v20 = a1;
                    PokeList_Message = a1->pokeList_Message;
                    v22 = 1;
                }
                PokeListMessage_LoadItemNameToStrBuf(v20, PokeList_Message, v22, a1->field_28C->ItemID);
                PokeList_ChangeHeldItem(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
                PokeList_ChangeArceusForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                PokeList_ChangeGenesectForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                if (PokeList_IsGiratinaInOriginForme(a1) == 1)
                {
                    PokeList_ChangeGiratinaToAlteredForme(a1, a1->SelectedPkm);
                    PokeList_PrintMessage(a1, v19, 1, (int)sub_219E4F8);
                    a1->field_274 = 2;
                }
                else
                {
                    if (a1->field_28C->ItemUseType == 11)
                    {
                        v23 = a1;
                        v24 = v19;
                        v25 = (void *)sub_219DE50;
                    }
                    else
                    {
                        v25 = (void *)sub_219DE34;
                        v23 = a1;
                        v24 = v19;
                    }
                    PokeList_PrintMessage(v23, v24, 1, (int)v25);
                }
                PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                v26 = a1->field_28C;
                if (v26->ItemUseType == 11)
                {
                    v26->field_50 = 10;
                }
                else
                {
                    v26->ItemUseType = 0;
                }
                a1->field_D = 7;
                a1->field_C = 0;
                a1->field_14 = 1;
                return;
            }
            else if (IsEqual(ItemUseType, 16) || IsEqual(ItemUseType, 17))
            {
                a1->field_10C = (int)sub_219FEA8(a1, a1->PokeList_Menu, 0, 12, 0x15u, 0);
                a1->field_110 = (int)sub_219FEA8(a1, a1->PokeList_Menu, 1, 22, 0x15u, 1);
                sub_219B1DC(a1);
                a1->field_D = 2;
                return;
            }
            else
            {
                k::Printf("\n\nDid we reach the default?%d\n\n", ItemUseType);
                return;
            }
        }

        // Switch Statements
        // if (ItemUseType <= 27)
        // {

        //     k::Printf("\n\nWe got into the for loop %d\n\n", ItemUseType);
        //     switch (ItemUseType)
        //     {
        //     case 0:
        //     case 6:
        //     case 9:
        //     case 0xE:
        //     case 0x10:
        //     case 0x12:
        //     case 0x15:
        //     case 0x19:
        //     case 0x1B:
        //         k::Printf("\n\nWe got in before the function %d\n\n", ItemUseType);
        //         sub_219B1DC(a1);
        //         k::Printf("\n\nWe got in after the function %d\n\n", ItemUseType);
        //         a1->field_D = 2;
        //         break;
        //     case 1:
        //         a1->field_10C = (int)sub_219FEA8(a1, a1->PokeList_Menu, 0, 22, 21u, 0);
        //         sub_219B1DC(a1);
        //         a1->field_D = 2;
        //         break;
        //     case 3:
        //         a1->field_14 = 0;
        //         sub_219B1DC(a1);
        //         a1->field_D = 2;
        //         break;
        //     case 5:
        //         k::Printf("\n\nDid we get in here?\n");
        //         if (PokeList_IsItemSacredAsh(a1, v2->ItemID))
        //         {
        //             FaintedPkmSlot = PokeList_GetFaintedPkmSlot(a1);
        //             if (FaintedPkmSlot == -1)
        //             {
        //                 PokeList_PrintItemUseFailMessage_Default(a1);
        //                 a1->field_D = a1->field_C;
        //                 a1->field_C = 0;
        //             }
        //             else
        //             {
        //                 a1->SelectedSlot = FaintedPkmSlot;
        //                 a1->SelectedPkm = PokeParty_GetPkm(a1->field_28C->pokeParty, FaintedPkmSlot);
        //                 PokeList_PrintItemRecoverMessage(a1, 0);
        //                 PokeList_ApplyItemEffect(a1->SelectedPkm, a1->field_28C->ItemID, 0, a1->field_28C->field_40, a1->heapId);
        //                 sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
        //                 a1->field_24 = 1;
        //                 a1->field_D = a1->field_C;
        //                 a1->field_C = 0;
        //                 PokeList_SubItem(a1, a1->field_28C->ItemID);
        //             }
        //         }
        //         else if (PokeList_GetItemCountByID(a1, a1->field_28C->ItemID))
        //         {
        //             sub_219B1DC(a1);
        //             a1->field_D = 2;
        //         }
        //         else
        //         {
        //             a1->field_28C->field_50 = 10;
        //             sub_219F83C(a1, a1->pokeList_Message);
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 0, a1->field_28C->ItemID);
        //             PokeList_PrintMessage(a1, 191, 1, (int)sub_219DE50);
        //             PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //             a1->field_D = a1->field_C;
        //             a1->field_C = 0;
        //         }
        //         break;
        //     case 7:
        //     case 8:
        //         a1->SelectedSlot = v2->SelectedSlot;
        //         Pkm = PokeParty_GetPkm(v2->pokeParty, v2->SelectedSlot);
        //         a1->SelectedPkm = Pkm;
        //         v6 = a1->field_28C->field_58;
        //         if (v6 >= 4)
        //         {
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
        //             v11 = (void *)sub_219DF48;
        //             v8 = a1;
        //             v9 = 36;
        //             v10 = 0;
        //         }
        //         else
        //         {
        //             Param = PokeParty_GetParam(Pkm, (PkmField)(v6 + 54), 0);
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, Param);
        //             v8 = a1;
        //             v9 = 41;
        //             v10 = 1;
        //             v11 = (void *)sub_219E018;
        //         }
        //         PokeList_PrintMessage(v8, v9, v10, (int)v11);
        //         PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //         SelectedSlot = a1->SelectedSlot;
        //         a1->field_D = 7;
        //         a1->field_C = 0;
        //         a1->field_14 = 0;
        //         sub_219F008(a1, a1->pokeList_Plate[SelectedSlot], 1);
        //         break;
        //     case 0xA:
        //         a1->SelectedSlot = v2->SelectedSlot;
        //         v13 = PokeParty_GetPkm(v2->pokeParty, v2->SelectedSlot);
        //         a1->SelectedPkm = v13;
        //         if (a1->field_28C->ItemID)
        //         {
        //             v14 = PokeParty_GetParam(v13, PF_Item, 0);
        //             v15 = v14;
        //             if (v14)
        //             {
        //                 PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //                 PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //                 sub_219FA58(a1, a1->pokeList_Message, 1, v15);
        //                 PokeList_PrintMessage(a1, 59, 0, (int)sub_219E0AC);
        //                 PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //             }
        //             else
        //             {
        //                 PokeList_ChangeHeldItem(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //                 sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
        //                 PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //                 PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //                 PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 1, a1->field_28C->ItemID);
        //                 PokeList_ChangeArceusForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //                 PokeList_ChangeGenesectForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //                 if (PokeList_DoesGiratinaNeedFormeChange(a1))
        //                 {
        //                     PokeList_ChangeGiratinaToOriginForme(a1, a1->SelectedPkm);
        //                     PokeList_PrintMessage(a1, 92, 1, (int)sub_219E4F8);
        //                     a1->field_274 = 1;
        //                 }
        //                 else
        //                 {
        //                     PokeList_PrintMessage(a1, 92, 1, (int)sub_219DE34);
        //                 }
        //                 PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //                 a1->field_28C->ItemUseType = 0;
        //             }
        //         }
        //         else
        //         {
        //             a1->field_28C->ItemUseType = 0;
        //             sub_219B1DC(a1);
        //             a1->field_D = 2;
        //         }
        //         v16 = a1->SelectedSlot;
        //         a1->field_D = 7;
        //         a1->field_C = 0;
        //         a1->field_14 = 1;
        //         sub_219F008(a1, a1->pokeList_Plate[v16], 1);
        //         break;
        //     case 0xB:
        //     case 0xC:
        //         a1->SelectedSlot = v2->SelectedSlot;
        //         v17 = PokeParty_GetPkm(v2->pokeParty, v2->SelectedSlot);
        //         a1->SelectedPkm = v17;
        //         v18 = PokeParty_GetParam(v17, PF_Item, 0);
        //         PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //         if (v18)
        //         {
        //             v19 = 65;
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 1, v18);
        //             PokeList_Message = a1->pokeList_Message;
        //             v20 = a1;
        //             v22 = 2;
        //         }
        //         else
        //         {
        //             v19 = 92;
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             v20 = a1;
        //             PokeList_Message = a1->pokeList_Message;
        //             v22 = 1;
        //         }
        //         PokeListMessage_LoadItemNameToStrBuf(v20, PokeList_Message, v22, a1->field_28C->ItemID);
        //         PokeList_ChangeHeldItem(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //         sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
        //         PokeList_ChangeArceusForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //         PokeList_ChangeGenesectForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //         if (PokeList_IsGiratinaInOriginForme(a1) == 1)
        //         {
        //             PokeList_ChangeGiratinaToAlteredForme(a1, a1->SelectedPkm);
        //             PokeList_PrintMessage(a1, v19, 1, (int)sub_219E4F8);
        //             a1->field_274 = 2;
        //         }
        //         else
        //         {
        //             if (a1->field_28C->ItemUseType == 11)
        //             {
        //                 v23 = a1;
        //                 v24 = v19;
        //                 v25 = (void *)sub_219DE50;
        //             }
        //             else
        //             {
        //                 v25 = (void *)sub_219DE34;
        //                 v23 = a1;
        //                 v24 = v19;
        //             }
        //             PokeList_PrintMessage(v23, v24, 1, (int)v25);
        //         }
        //         PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //         v26 = a1->field_28C;
        //         if (v26->ItemUseType == 11)
        //         {
        //             v26->field_50 = 10;
        //         }
        //         else
        //         {
        //             v26->ItemUseType = 0;
        //         }
        //         a1->field_D = 7;
        //         a1->field_C = 0;
        //         a1->field_14 = 1;
        //         break;
        //     case 0x16:
        //     case 0x17:
        //         a1->field_10C = (int)sub_219FEA8(a1, a1->PokeList_Menu, 0, 12, 0x15u, 0);
        //         a1->field_110 = (int)sub_219FEA8(a1, a1->PokeList_Menu, 1, 22, 0x15u, 1);
        //         sub_219B1DC(a1);
        //         a1->field_D = 2;
        //         break;
        //     default:
        //         k::Printf("\n\nDid we reach the default?%d\n\n", ItemUseType);
        //         return;
        //     }
        // }
    }
    #endif

    void CheckPokemonForme(PokeList *a1, PokeList_Party *a2){
        PartyPkm *pkm;
        PokeParty *pokeparty;
        int itmID;

        itmID = a2->ItemID;
        pkm = a1->SelectedPkm;
        pokeparty = a1->field_28C->pokeParty;
        
        if (PokeParty_GetParam(pkm, PF_Species, 0)==585){
            // Dusk Stone
            if (itmID == 108) {
                PokeParty_ChangeForme(pkm, 2);
            } 
            // Shiny Stone
            else if (itmID == 107){
                PokeParty_ChangeForme(pkm, 3);
            } 
            // Fire Stone
            else if (itmID == 82) {
                PokeParty_ChangeForme(pkm, 1);
            } 
            // Leaf Stone
            else if (itmID == 85){
                PokeParty_ChangeForme(pkm, 0);
            } else {
                return;
            }
        }
        return;
    }

    void THUMB_BRANCH_sub_219B30C(PokeList *a1)
    {
        PokeList_Party *v2;  // r2
        unsigned int result; // r0
        PokeList_Party *partyResult;
        unsigned int ItemUseType; // r1
        ItemRestoreType v5;       // r6
        int v6;                   // r0
        int ItemID;               // r1
        int KyuremUnfuseCase;     // r0
        u32 Param;                // r0
        unsigned __int16 v10;     // r6
        MailData *v11;            // r6

       // k::Printf("\n\nNew Items go here!\n\n");
        v2 = a1->field_28C;
        if (v2->field_73 == 1)
        {
            result = 19;
            a1->field_C = 19;
            return;
        }
        ItemUseType = v2->ItemUseType;
        if (ItemUseType > 0x1B)
        {
            sub_219CF2C(a1);
            sub_219B8F0(a1);
            return;
        }
        // switch (*(&jpt_219B338 + ItemUseType))

        if (IsEqual(ItemUseType, 0) || IsEqual(ItemUseType, 1) || IsEqual(ItemUseType, 0x12) || IsEqual(ItemUseType, 0x15) || IsEqual(ItemUseType, 0x16) || IsEqual(ItemUseType, 0x17) || IsEqual(ItemUseType, 0x19))
        {
            sub_219CF2C(a1);
            GFL_BGSysLoadScr(G2D_BG0A);
            sub_219B8F0(a1);
            return;
        }
        else if (IsEqual(ItemUseType, 3) || IsEqual(ItemUseType, 0x1B))
        {
            a1->field_C = 19;
            v2->SelectedSlot = a1->SelectedSlot;
            a1->field_28C->field_50 = 0;
            return;
        }
        else if (IsEqual(ItemUseType, 5))
        {
            if (PokeList_IsPPRestoringItem(a1, v2->ItemID))
            {
                sub_219CF2C(a1);
                sub_219B8F0(a1);
                return;
            }
            if (PokeList_CanItemWithBattleStatsBeUsed(a1->SelectedPkm, a1->field_28C->ItemID, 0, a1->heapId))
            {
                v5 = PokeList_PrintItemRecoverMessage(a1, 0);
                v6 = PokeList_ApplyItemEffect(a1->SelectedPkm, a1->field_28C->ItemID, 0, a1->field_28C->field_40, a1->heapId);
                if (v5 == RESTORETYPE_RARE_CANDY)
                {
                    if (v6)
                    {
                        sub_2038BF4(9);
                    }
                    sub_219F290(a1, a1->pokeList_Plate[a1->SelectedSlot], a1->SelectedPkm, 0);
                }
                else
                {
                    if (v5 == RESTORETYPE_EV_HP_DECREASE || v5 == RESTORETYPE_EV_HP)
                    {
                        sub_219F290(a1, a1->pokeList_Plate[a1->SelectedSlot], a1->SelectedPkm, 0);
                    }
                    else
                    {
                        sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
                    }
                    GFL_SndSEPlay(SEQ_SE_RECOVERY);
                }
                PokeList_SubItem(a1, a1->field_28C->ItemID);
                return;
            }
            if (a1->field_28C->ItemID == 466 && PokeList_DoesShayminNeedFormeChange(a1))
            {
                PokeList_ChangeShayminToSkyForme(a1, a1->SelectedPkm);
                a1->field_28C->field_50 = 10;
                a1->field_C = 14;
                a1->field_274 = 3;
                return;
            }
            if (a1->field_28C->ItemID == 638 && PokeList_IsRevealGlassMon(a1, a1->SelectedPkm) && isOneShotDRObtained((void *)a1->field_28C->field_24, 6, (void *)a1->field_28C->field_28))
            {
                PokeList_ChangeRevealGlassMonForme(a1, a1->SelectedPkm);
                a1->field_28C->field_50 = 10;
                a1->field_C = 14;
                a1->field_274 = 6;
                return;
            }
            ItemID = a1->field_28C->ItemID;
            if (ItemID != 628)
            {
                if (ItemID == 629)
                {
                    KyuremUnfuseCase = PokeList_GetKyuremUnfuseCase(a1);
                    if (KyuremUnfuseCase == 5)
                    {
                        sub_21A03EC(a1, 2);
                        return;
                    }
                    if (KyuremUnfuseCase != 2 && KyuremUnfuseCase != 4)
                    {
                        a1->TargetedSlot = a1->SelectedSlot;
                        a1->field_28C->field_50 = 10;
                        a1->field_C = 14;
                        a1->field_274 = 5;
                        a1->field_27B = 2;
                        return;
                    }
                }
            LABEL_29:
                sub_21A03DC(a1);
                return;
            }
            result = PokeList_GetKyuremFuseCase(a1);
            if (result == 2 || result == 4)
            {
                goto LABEL_29;
            }
            if (result == 3)
            {
                sub_21A03EC(a1, 1);
            }
            else if (!result)
            {
                sub_219CE18(a1, a1->SelectedSlot);
                sub_219CE74(a1, a1->SelectedSlot);
                a1->TargetedSlot = a1->SelectedSlot;
                a1->field_28C->field_50 = 10;
                a1->field_C = 23;
                a1->field_14 = 0;
                sub_219F7AC(a1, a1->pokeList_Message, 0);
                sub_219F880(a1, a1->pokeList_Message, 18);
                sub_219BBA8(a1);
            }
            return;
        }
        else if (IsEqual(ItemUseType, 6))
        {
            result = PokeList_GetLearnMoveCase(a1, a1->SelectedPkm, v2->SelectedSlot);
            if (result <= 3)
            {
                if (IsEqual(result, 0u))
                {
                    a1->field_28C->field_50 = 10;
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
                    PokeList_PrintMessage(a1, 42, 1, (int)sub_219DE50);
                    PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                    sub_219E5C8(a1, a1->SelectedPkm);
                    result = sub_219E620(a1, a1->SelectedPkm);
                    #if TOGGLE_TM
                        PokeList_SubItem(a1, a1->field_28C->ItemID);
                    #endif
                    return;
                }
                else if (IsEqual(result, 1u))
                {
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
                    PokeList_PrintMessage(a1, 33, 0, (int)sub_219DEC4);
                    PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                    return;
                }
                else if (IsEqual(result, 2u))
                {
                    a1->field_28C->field_50 = 10;
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
                    PokeList_PrintMessage(a1, 43, 1, (int)sub_219DE50);
                    PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                    return;
                }
                else if (IsEqual(result, 3u))
                {
                    a1->field_28C->field_50 = 10;
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
                    PokeList_PrintMessage(a1, 44, 1, (int)sub_219DE50);
                    PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                    return;
                }
                else
                {
                    return;
                }
            }
            return;
        }
        else if (IsEqual(ItemUseType, 9))
        {
            Param = PokeParty_GetParam(a1->SelectedPkm, PF_Item, 0);
            v10 = Param;
            if (Param)
            {
                if (PML_ItemIsMail(Param) == 1)
                {
                    a1->field_28C->field_50 = 10;
                    PokeList_PrintMessage(a1, 58, 1, (int)sub_219DE50);
                }
                else
                {
                    PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                    PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                    sub_219FA58(a1, a1->pokeList_Message, 1, v10);
                    PokeList_PrintMessage(a1, 59, 0, (int)sub_219E0AC);
                    PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
                }
            }
            else if (PML_ItemIsMail(a1->field_28C->ItemID) == 1)
            {
                a1->field_C = 19;
                a1->field_28C->SelectedSlot = a1->SelectedSlot;
                a1->field_28C->field_50 = 6;
            }
            else
            {
                a1->field_28C->field_50 = 10;
                PokeList_ChangeHeldItem(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
                PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
                PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
                PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 1, a1->field_28C->ItemID);
                PokeList_ChangeArceusForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                PokeList_ChangeGenesectForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
                if (PokeList_DoesGiratinaNeedFormeChange(a1))
                {
                    PokeList_ChangeGiratinaToOriginForme(a1, a1->SelectedPkm);
                    PokeList_PrintMessage(a1, 92, 1, (int)sub_219E4F8);
                    a1->field_274 = 1;
                }
                else
                {
                    PokeList_PrintMessage(a1, 92, 1, (int)sub_219DE50);
                }
                PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
            }
            return;
        }
        else if (IsEqual(ItemUseType, 0xE))
        {
            if (PokeParty_GetParam(a1->SelectedPkm, PF_Item, 0))
            {
                PokeList_PrintMessage(a1, 109, 1, (int)sub_219DE50);
            }
            else
            {
                v11 = sub_20097F4(a1->field_28C->field_8, 0, a1->field_28C->field_6C, a1->heapId);
                PokeParty_SetParam(a1->SelectedPkm, PF_Mail, (int)v11);
                GFL_HeapFree(v11);
                PokeParty_SetParam(a1->SelectedPkm, PF_Item, a1->field_28C->ItemID);
                sub_20097D0(a1->field_28C->field_8, 0, a1->field_28C->field_6C);
                PokeList_PrintMessage(a1, 108, 1, (int)sub_219DE50);
            }
            return;
        }
        else if (IsEqual(ItemUseType, 0x10))
        {
            if (PokeList_CheckEvolveSpecies(a1, a1->SelectedPkm, v2->ItemID))
            {
                CheckPokemonForme(a1, v2);
                PokeList_SubItem(a1, a1->field_28C->ItemID);
                a1->field_C = 19;
                a1->field_28C->SelectedSlot = a1->SelectedSlot;
                a1->field_28C->field_50 = 8;
            }
            else
            {
                PokeList_PrintMessage(a1, 82, 1, (int)sub_219DE50);
            }
            return;
        }
        else
        {
            sub_219CF2C(a1);
            sub_219B8F0(a1);
            return;
        }

        // switch (ItemUseType)
        // {
        // case 0:
        // case 1:
        // case 0x12:
        // case 0x15:
        // case 0x16:
        // case 0x17:
        // case 0x19:
        //     sub_219CF2C(a1);
        //     GFL_BGSysLoadScr(G2D_BG0A);
        //     sub_219B8F0(a1);
        //     return;
        // case 3:
        // case 0x1B:
        //     a1->field_C = 19;
        //     v2->SelectedSlot = a1->SelectedSlot;
        //     a1->field_28C->field_50 = 0;
        //     return;
        // case 5:
        //     if (PokeList_IsPPRestoringItem(a1, v2->ItemID))
        //     {
        //         sub_219CF2C(a1);
        //         sub_219B8F0(a1);
        //         return;
        //     }
        //     if (PokeList_CanItemWithBattleStatsBeUsed(a1->SelectedPkm, a1->field_28C->ItemID, 0, a1->heapId))
        //     {
        //         v5 = PokeList_PrintItemRecoverMessage(a1, 0);
        //         v6 = PokeList_ApplyItemEffect(a1->SelectedPkm, a1->field_28C->ItemID, 0, a1->field_28C->field_40, a1->heapId);
        //         if (v5 == RESTORETYPE_RARE_CANDY)
        //         {
        //             if (v6)
        //             {
        //                 sub_2038BF4(9);
        //             }
        //             sub_219F290(a1, a1->pokeList_Plate[a1->SelectedSlot], a1->SelectedPkm, 0);
        //         }
        //         else
        //         {
        //             if (v5 == RESTORETYPE_EV_HP_DECREASE || v5 == RESTORETYPE_EV_HP)
        //             {
        //                 sub_219F290(a1, a1->pokeList_Plate[a1->SelectedSlot], a1->SelectedPkm, 0);
        //             }
        //             else
        //             {
        //                 sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
        //             }
        //             GFL_SndSEPlay(SEQ_SE_RECOVERY);
        //         }
        //         PokeList_SubItem(a1, a1->field_28C->ItemID);
        //         return;
        //     }
        //     if (a1->field_28C->ItemID == 466 && PokeList_DoesShayminNeedFormeChange(a1))
        //     {
        //         PokeList_ChangeShayminToSkyForme(a1, a1->SelectedPkm);
        //         a1->field_28C->field_50 = 10;
        //         a1->field_C = 14;
        //         a1->field_274 = 3;
        //         return;
        //     }
        //     if (a1->field_28C->ItemID == 638 && PokeList_IsRevealGlassMon(a1, a1->SelectedPkm) && isOneShotDRObtained((void *)a1->field_28C->field_24, 6, (void *)a1->field_28C->field_28))
        //     {
        //         PokeList_ChangeRevealGlassMonForme(a1, a1->SelectedPkm);
        //         a1->field_28C->field_50 = 10;
        //         a1->field_C = 14;
        //         a1->field_274 = 6;
        //         return;
        //     }
        //     ItemID = a1->field_28C->ItemID;
        //     if (ItemID != 628)
        //     {
        //         if (ItemID == 629)
        //         {
        //             KyuremUnfuseCase = PokeList_GetKyuremUnfuseCase(a1);
        //             if (KyuremUnfuseCase == 5)
        //             {
        //                 sub_21A03EC(a1, 2);
        //                 return;
        //             }
        //             if (KyuremUnfuseCase != 2 && KyuremUnfuseCase != 4)
        //             {
        //                 a1->TargetedSlot = a1->SelectedSlot;
        //                 a1->field_28C->field_50 = 10;
        //                 a1->field_C = 14;
        //                 a1->field_274 = 5;
        //                 a1->field_27B = 2;
        //                 return;
        //             }
        //         }
        //     LABEL_29:
        //         sub_21A03DC(a1);
        //         return;
        //     }
        //     result = PokeList_GetKyuremFuseCase(a1);
        //     if (result == 2 || result == 4)
        //     {
        //         goto LABEL_29;
        //     }
        //     if (result == 3)
        //     {
        //         sub_21A03EC(a1, 1);
        //     }
        //     else if (!result)
        //     {
        //         sub_219CE18(a1, a1->SelectedSlot);
        //         sub_219CE74(a1, a1->SelectedSlot);
        //         a1->TargetedSlot = a1->SelectedSlot;
        //         a1->field_28C->field_50 = 10;
        //         a1->field_C = 23;
        //         a1->field_14 = 0;
        //         sub_219F7AC(a1, a1->pokeList_Message, 0);
        //         sub_219F880(a1, a1->pokeList_Message, 18);
        //         sub_219BBA8(a1);
        //     }
        //     return;
        // case 6:
        //     result = PokeList_GetLearnMoveCase(a1, a1->SelectedPkm, v2->SelectedSlot);
        //     if (result <= 3)
        //     {
        //         // result = *(&jpt_219B7A4 + result);
        //         switch (result)
        //         {
        //         case 0u:
        //             a1->field_28C->field_50 = 10;
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
        //             PokeList_PrintMessage(a1, 42, 1, (int)sub_219DE50);
        //             PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //             sub_219E5C8(a1, a1->SelectedPkm);
        //             result = sub_219E620(a1, a1->SelectedPkm);
        //             break;
        //         case 1u:
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
        //             PokeList_PrintMessage(a1, 33, 0, (int)sub_219DEC4);
        //             PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //             break;
        //         case 2u:
        //             a1->field_28C->field_50 = 10;
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
        //             PokeList_PrintMessage(a1, 43, 1, (int)sub_219DE50);
        //             PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //             break;
        //         case 3u:
        //             a1->field_28C->field_50 = 10;
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             PokeListMessage_LoadMoveNameToStrBuf(a1, a1->pokeList_Message, 1u, a1->field_28C->MoveToLearn);
        //             PokeList_PrintMessage(a1, 44, 1, (int)sub_219DE50);
        //             PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //             break;
        //         default:
        //             return;
        //         }
        //     }
        //     return;
        // case 9:
        //     Param = PokeParty_GetParam(a1->SelectedPkm, PF_Item, 0);
        //     v10 = Param;
        //     if (Param)
        //     {
        //         if (PML_ItemIsMail(Param) == 1)
        //         {
        //             a1->field_28C->field_50 = 10;
        //             PokeList_PrintMessage(a1, 58, 1, (int)sub_219DE50);
        //         }
        //         else
        //         {
        //             PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //             PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //             sub_219FA58(a1, a1->pokeList_Message, 1, v10);
        //             PokeList_PrintMessage(a1, 59, 0, (int)sub_219E0AC);
        //             PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //         }
        //     }
        //     else if (PML_ItemIsMail(a1->field_28C->ItemID) == 1)
        //     {
        //         a1->field_C = 19;
        //         a1->field_28C->SelectedSlot = a1->SelectedSlot;
        //         a1->field_28C->field_50 = 6;
        //     }
        //     else
        //     {
        //         a1->field_28C->field_50 = 10;
        //         PokeList_ChangeHeldItem(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //         sub_219F350(a1, a1->pokeList_Plate[a1->SelectedSlot]);
        //         PokeListMessage_CreateWordSetSystem(a1, a1->pokeList_Message);
        //         PokeListMessage_LoadPokemonNicknameToStrBuf(a1, a1->pokeList_Message, 0, a1->SelectedPkm);
        //         PokeListMessage_LoadItemNameToStrBuf(a1, a1->pokeList_Message, 1, a1->field_28C->ItemID);
        //         PokeList_ChangeArceusForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //         PokeList_ChangeGenesectForme(a1, a1->SelectedPkm, a1->field_28C->ItemID);
        //         if (PokeList_DoesGiratinaNeedFormeChange(a1))
        //         {
        //             PokeList_ChangeGiratinaToOriginForme(a1, a1->SelectedPkm);
        //             PokeList_PrintMessage(a1, 92, 1, (int)sub_219E4F8);
        //             a1->field_274 = 1;
        //         }
        //         else
        //         {
        //             PokeList_PrintMessage(a1, 92, 1, (int)sub_219DE50);
        //         }
        //         PokeListMessage_ClearWordSetSystem(a1, a1->pokeList_Message);
        //     }
        //     return;
        // case 0xE:
        //     if (PokeParty_GetParam(a1->SelectedPkm, PF_Item, 0))
        //     {
        //         PokeList_PrintMessage(a1, 109, 1, (int)sub_219DE50);
        //     }
        //     else
        //     {
        //         v11 = sub_20097F4(a1->field_28C->field_8, 0, a1->field_28C->field_6C, a1->heapId);
        //         PokeParty_SetParam(a1->SelectedPkm, PF_Mail, (int)v11);
        //         GFL_HeapFree(v11);
        //         PokeParty_SetParam(a1->SelectedPkm, PF_Item, a1->field_28C->ItemID);
        //         sub_20097D0(a1->field_28C->field_8, 0, a1->field_28C->field_6C);
        //         PokeList_PrintMessage(a1, 108, 1, (int)sub_219DE50);
        //     }
        //     return;
        // case 0x10:
        //     if (PokeList_CheckEvolveSpecies(a1, a1->SelectedPkm, v2->ItemID))
        //     {
        //         PokeList_SubItem(a1, a1->field_28C->ItemID);
        //         a1->field_C = 19;
        //         a1->field_28C->SelectedSlot = a1->SelectedSlot;
        //         a1->field_28C->field_50 = 8;
        //     }
        //     else
        //     {
        //         PokeList_PrintMessage(a1, 82, 1, (int)sub_219DE50);
        //     }
        //     return;
        // default:
        //     sub_219CF2C(a1);
        //     sub_219B8F0(a1);
        //     return;
        // }
    }

    int THUMB_BRANCH_SAFESTACK_PokeList_ApplyItemEffect(PartyPkm *a1, unsigned int a2, int a3, unsigned __int16 a4, int a5)
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
        int v48;
        u32 data;           // [sp+50h] [bp-38h]
        u32 Param;          // [sp+54h] [bp-34h]
        signed __int32 v50; // [sp+58h] [bp-30h]

        v30 = a2;
        v6 = 0;
      //  k::Printf("\n111. We have entered the function!\n\nOur Parameters are:\n a1: %d\n\n a2: %d\n\n a3: %d\n\n a4: %d \n\n a5: %d\n\nu16 a5 is %d\n\n", a1, a2, a3, a4, a5, (HeapID)a5);

        DataFile = (ItemData *)PML_ItemReadDataFile(a2, 0, (HeapID)a5);
      //  k::Printf("\n2. We have acquired Datafile\n");
        // Checks to see if there are any actual Battle relevant effects for the item
        if (PML_ItemGetParam(DataFile, ITSTAT_HAS_BATTLE_STATS) != 1)
        {
       //     k::Print("\n3. This means this isn't a battle item!\n");
            goto LABEL_85; // Frees up the heap and exits function
        }

        // v6 and v8 are basically state trackers users to navigate through the most confusing iteration process i've seen in gamefreak's code

        v8 = 0;

        // Gets a value between 0-17 to see if there is a status condition
        Param = PokeParty_GetParam(a1, PF_StatusCond, 0);
        data = Param;
   //     k::Printf("\n4. Check for Status Condition: %d\n", data);
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
            // k::printf("\n5. We got into the status cure function\n", data);
            v6 = 1;
        }

        // gets the current hp and max hp for the pokemon
        v42 = PokeParty_GetParam(a1, PF_NowHP, 0);
        v40 = PokeParty_GetParam(a1, PF_MaxHP, 0);
        // k::printf("\n5. Now we're checking for current HP %d and max HP %d\n", v42, v40);
        //  checks to see if it's a reviving item
        if ((PML_ItemGetParam(DataFile, ITSTAT_BOOST_REVIVE) || PML_ItemGetParam(DataFile, ITSTAT_BOOST_SACRED_ASH)) && !PML_ItemGetParam(DataFile, ITSTAT_BOOST_RARECANDY))
        {
            // k::printf("\n6. This checks if we need to apply a heal to an unconcious pokemon\n");
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
            // k::printf("\n7. This checks if we need to apply a heal\n");
            //  skips forward if it's not an HP recovering item
            if (!PML_ItemGetParam(DataFile, ITSTAT_FLAG_HPREPLENISH))
            {
                goto LABEL_25;
            }
            // k::printf("\n8. Now this heals only if current HP < max HP\n");
            //  heals only if the current hp is less than the max HP
            if (v42 < v40)
            {
                v10 = PML_ItemGetParam(DataFile, ITSTAT_HEAL_AMOUNT);
                PokeList_ApplyHeal(a1, v42, v40, v10);
                // k::printf("\n9. Heal Successful!\n");
                v6 = 1;
            }
        }
        v8 = 1;
    LABEL_25:

        // Rare Candy Handler
        v50 = PokeParty_GetParam(a1, PF_Level, 0);
        // k::printf("\n10. The Pokemon Level is %d\n", v50);
        if (PML_ItemGetParam(DataFile, ITSTAT_BOOST_RARECANDY))
        {
            // Makes sure the current level is less than 100

            // k::print("\n11. We're at the rare candy handler\n");
            if (v50 < 100)
            {
                // k::printf("\n12. We have checked the current level against 100!\n");
                v11 = PokeParty_GetParam(a1, PF_Species, 0);
                v12 = PokeParty_GetParam(a1, PF_Forme, 0);
                PkmLvExp = PML_UtilGetPkmLvExp(v11, v12, (v50 + 1)); // Gets the EXp needed to be current level + 1
                PokeParty_SetParam(a1, PF_Experience, PkmLvExp);
                // k::printf("\n13. We have applied the experience to the pokemon!\n");

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
        // k::printf("\n14. We're checking if this is an evolution stone!\n");
        if (PML_ItemGetParam(DataFile, ITSTAT_BOOST_EVOSTONE))
        {
           // k::Printf("\n\nThe sort index for this item is %d\n\n", 5);
            // if (PokeParty_GetParam(a1, PF_Species, 0) == 585) {

            // }
            v8 = 1;
        }
        // k::printf("\n15. We're checking if this is a PP Booster!\n");
        if (PML_ItemGetParam(DataFile, ITSTAT_BOOST_PP1))
        {
            if (PokeList_ApplyMaxPPIncrease(a1, a3, 1) == 1)
            {
                v6 = 1;
            }
        }
        else
        {
            // k::printf("\n16. We're checking if this is PP Max\n");
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
        // k::printf("\n17. We're at Label 41\n");
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_PPREPLENISH))
        {
            // k::printf("\n18. This item replenishes PP\n");

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
        // k::printf("\n18. We're at label 51\n");
        v43 = PokeParty_GetParam(a1, PF_EvHP, 0);
        v41 = PokeParty_GetParam(a1, PF_EvATK, 0);
        v39 = PokeParty_GetParam(a1, PF_EvDEF, 0);
        v38 = PokeParty_GetParam(a1, PF_EvSPE, 0);
        v47 = PokeParty_GetParam(a1, PF_EvSPA, 0);
        v46 = PokeParty_GetParam(a1, PF_EvSPD, 0);
        v45 = PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_ABOVE100);
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_HP))
        {
            // k::printf("\n19. This increases HP EVs\n");
            v44 = PML_ItemGetParam(DataFile, ITSTAT_EV_HP);
            if (v44 > 0 && PokeParty_GetParam(a1, PF_Species, 0) == 292)
            {
            LABEL_85:
                // k::print("\n20. We're at label 85\n");
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
            // k::print("\n21. This increases atk EVs\n");
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
        if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_EVADD_DEF))
        {
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
            // k::print("\n24. This increases Speed EVs\n");
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
            // k::print("\n25. This increases SpA EVs\n");
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
            // k::print("\n26. This increases SpD EVs\n");
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
        // k::print("\n27. This increases Speed EVs\n");
        if (!v6 && v8 == 1)
        {
            goto LABEL_85;
        }
        // k::print("\n28 We made it past all the EVs, now happiness\n");
        v25 = PokeParty_GetParam(a1, PF_Happiness, 0);
        v26 = v25;
        // k::printf("\n29: Current Happiness is %d\n", v26);
        if (v25 >= 100)
        {
            // k::print("\n30. More Friendship shit\n");
            if (v25 >= 200)
            {
                // k::print("\n31. Even More Friendship shit\n");
                if (v25 <= 255 && PML_ItemGetParam(DataFile, ITSTAT_FLAG_FRIENDSHIP_ADD3))
                {
                    // k::print("\n32. Even EVen More Friendship shit\n");
                    v29 = PML_ItemGetParam(DataFile, ITSTAT_FRIENDSHIP3);
                    PokeList_ApplyFriendship(a1, v26, v29, v30, a4, (HeapID)a5);
                    GFL_HeapFree(DataFile);
                    return v6;
                }
            }
            else if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_FRIENDSHIP_ADD2))
            {
                // k::print("\n33. Even even More Friendship shit\n");
                v28 = PML_ItemGetParam(DataFile, ITSTAT_FRIENDSHIP2);
                PokeList_ApplyFriendship(a1, v26, v28, v30, a4, (HeapID)a5);
                GFL_HeapFree(DataFile);
                return v6;
            }
        }
        else if (PML_ItemGetParam(DataFile, ITSTAT_FLAG_FRIENDSHIP_ADD1))
        {
            // k::print("\n34. So much more More Friendship shit\n");
            v27 = PML_ItemGetParam(DataFile, ITSTAT_FRIENDSHIP1);
            PokeList_ApplyFriendship(a1, v26, v27, v30, a4, (HeapID)a5);
            GFL_HeapFree(DataFile);
            return v6;
        }
        GFL_HeapFree(DataFile);
        return v6;
    }

    #if TOGGLE_TMS
    BagItem *THUMB_BRANCH_SAFESTACK_BagSave_GetItemHandleAddCheck(BagSaveData *bag, u16 item_idx, u16 quantity, HeapID heapId)
    {
        u32 pPocketLimit; // [sp+4h] [bp-14h] BYREF
        BagItem *pPocket; // [sp+8h] [bp-10h] BYREF

        if (BagSave_GetPocketPtrByItem(bag, item_idx, &pPocket, &pPocketLimit) == ITEMTYPE_TM)
        {
            return BagSave_GetItemHandleAddCheckCore(pPocket, pPocketLimit, item_idx, quantity, 0x3E7u);
        }
        else
        {
            return BagSave_GetItemHandleAddCheckCore(pPocket, pPocketLimit, item_idx, quantity, 0x3E7u);
        }
    }

    u32 THUMB_BRANCH_PML_ItemGetMaxStorageCount(u16 itemIdx)
    {

        return 999;
    }
    #endif
}