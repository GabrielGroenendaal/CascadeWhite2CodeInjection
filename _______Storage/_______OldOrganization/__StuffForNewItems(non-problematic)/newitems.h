
#include "newitems_structs.h"

bool IsEqual(int a1, int a2)
{
    char *c1 = (char *)&a1;
    char *c2 = (char *)&a2;

    for (u16 i = 0; i < 4; ++i)
    {
        if (c1[i] != c2[i])
            return false;
    }
    return true;
}

C_DECL_BEGIN

extern void PokeParty_SetParam(PartyPkm *a1, PkmField a2, int a3);
extern u32 PokeParty_GetParam(PartyPkm *a1, PkmField a2, void *extra);
extern void *PML_ItemReadDataFile(unsigned int a1, int a2, HeapID a3);
extern int PML_ItemGetParam(ItemData *a1, ItemField a2);
extern int PokeList_GetEVsAppliedAfterLimit(int a1, int a2, int a3, int a4);
extern void PokeList_ApplyHeal(PartyPkm *a1, int a2, unsigned int a3, int a4);
extern int PokeList_ApplyMaxPPIncrease(PartyPkm *a1, int a2, int a3);
extern int PokeParty_AddPP(PartyPkm *pkm, int moveIdx, int addend);
extern u32 PML_UtilGetPkmLvExp(u16 species, u16 form, int level);
extern void PokeParty_RecalcStats(PartyPkm *a1);
extern int PokeList_ApplyFriendship(PartyPkm *a1, int a2, int a3, u16 a4, unsigned __int16 a5, HeapID a6);
extern void *GFL_HeapFree(void *);

// Weird shit
extern void sub_219CF2C(PokeList *a1);
extern void GFL_BGSysLoadScr(G2DBG bg);
extern int sub_219B8F0(PokeList *a1);
extern bool PokeList_IsPPRestoringItem(PokeList *a1, unsigned int a2);
extern bool PokeList_CanItemWithBattleStatsBeUsed(PartyPkm *a1, unsigned int a2, int a3, unsigned __int16 a4);
extern ItemRestoreType PokeList_PrintItemRecoverMessage(PokeList *a1, u16 a2);
extern int PokeList_ApplyItemEffect(PartyPkm *a1, unsigned int a2, int a3, unsigned __int16 a4, int a5);
extern void sub_2038BF4(int a1);
extern void sub_219F290(PokeList *a1, PokeList_Plate *a2, PartyPkm *a3, int a4);
extern void sub_219F350(PokeList *a1, PokeList_Plate *a2);
extern void GFL_SndSEPlay(SoundResID sndId);
extern int PokeList_SubItem(PokeList *a1, u16 a2);
extern bool PokeList_DoesShayminNeedFormeChange(PokeList *a1);
extern int PokeList_ChangeShayminToSkyForme(PokeList *a1, PartyPkm *a2);
extern bool PokeList_IsRevealGlassMon(PokeList *a1, PartyPkm *a2);
extern b32 isOneShotDRObtained(void *pTrainerCard, int idx, void *pTrainerInfo);
extern int PokeList_ChangeRevealGlassMonForme(PokeList *a1, PartyPkm *a2);
extern int PokeList_GetKyuremUnfuseCase(PokeList *a1);
extern void sub_21A03EC(PokeList *a1, int a2);
extern void sub_21A03DC(PokeList *a1);
extern int PokeList_GetKyuremFuseCase(PokeList *a1);
extern int sub_219CE18(PokeList *a1, int a2);
extern int sub_219CE74(PokeList *a1, int a2);
extern void sub_219F7AC(PokeList *a1, PokeList_Message *a2, unsigned int a3);
extern void sub_219F880(PokeList *a1, PokeList_Message *a2, int a3);
extern void sub_219BBA8(PokeList *a1);
extern int PokeList_GetLearnMoveCase(PokeList *a1, PartyPkm *a2, char a3);
extern void PokeListMessage_CreateWordSetSystem(PokeList *a1, PokeList_Message *a2);
extern void PokeListMessage_LoadPokemonNicknameToStrBuf(PokeList *a1, PokeList_Message *a2, int a3, PartyPkm *a4);
extern int PokeListMessage_LoadMoveNameToStrBuf(PokeList *a1, PokeList_Message *a2, u8 a3, u16 a4);
extern void PokeList_PrintMessage(PokeList *a1, int a2, int a3, int a4);
extern int sub_219DE50(int result);
extern void PokeListMessage_ClearWordSetSystem(PokeList *a1, PokeList_Message *a2);
extern void sub_219E5C8(PokeList *a1, PartyPkm *a2);
extern int sub_219E620(PokeList *a1, PartyPkm *a2);
extern unsigned __int8 *sub_219DEC4(PokeList *a1);
extern unsigned __int8 *sub_219E0AC(PokeList *a1);
extern int sub_219E4F8(PokeList *a1);
extern int PML_ItemIsMail(u16 itemId);
extern int sub_219FA58(PokeList *a1, PokeList_Message *a2, int a3, int a4);
extern void PokeList_ChangeHeldItem(PokeList *a1, PartyPkm *a2, u32 a3);
extern int PokeListMessage_LoadItemNameToStrBuf(PokeList *a1, PokeList_Message *a2, int a3, int a4);
extern void PokeList_ChangeArceusForme(PokeList *a1, PartyPkm *a2, u16 a3);
extern void PokeList_ChangeGenesectForme(PokeList *a1, PartyPkm *a2, int a3);
extern bool PokeList_DoesGiratinaNeedFormeChange(PokeList *a1);
extern int PokeList_ChangeGiratinaToOriginForme(PokeList *a1, PartyPkm *a2);
extern MailData *sub_20097F4(int a1, int a2, int a3, HeapID a4);
extern MailData *sub_20097D0(int a1, int a2, int a3);
extern int PokeList_CheckEvolveSpecies(PokeList *a1, PartyPkm *a2, int a3);
extern BmpWin **sub_219FEA8(PokeList *a1, char *a2, int a3, u8 a4, unsigned __int8 a5, int a6);
extern void sub_219B1DC(PokeList *a1);
extern bool PokeList_IsItemSacredAsh(PokeList *a1, u16 a2);
extern unsigned int PokeList_GetFaintedPkmSlot(PokeList *a1);
extern void PokeList_PrintItemUseFailMessage_Default(PokeList *a1);
extern PartyPkm *PokeParty_GetPkm(PokeParty *party, int slot);
extern bool PokeList_GetItemCountByID(PokeList *a1, u16 a2);
extern void sub_219F83C(PokeList *a1, PokeList_Message *a2);
extern unsigned __int8 *sub_219DF48(PokeList *a1);
extern void sub_219E018(PokeList *a1);
extern char *sub_219F008(PokeList *a1, PokeList_Plate *a2, int a3);
extern void sub_219DE34(PokeList *a1);
extern int PokeList_IsGiratinaInOriginForme(PokeList *a1);
extern int PokeList_ChangeGiratinaToAlteredForme(PokeList *a1, PartyPkm *a2);
extern ItemType BagSave_GetPocketPtrByItem(BagSaveData *bag, u16 itemId, BagItem **pPocket, u32 *pPocketLimit);
extern BagItem* BagSave_GetItemHandleAddCheckCore(
    BagItem *pocket,
    u32 itemTypeMaxCount,
    u16 itemId,
    u16 quantity,
    u16 maxQuantity);
extern bool PokeParty_ChangeForme(PartyPkm *pkm, u32 forme);


// extern GameData GSYS_GetGameData(GameSystem *gsys);
// extern PokeParty *GameData_GetParty(GameData *pBaseBlk);
//
// extern PartyPkm *PokeParty_GetPkm(PokeParty *party, int slot);

C_DECL_END
