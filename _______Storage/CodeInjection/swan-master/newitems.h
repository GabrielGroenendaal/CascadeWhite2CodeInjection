#include "../swan-master/swantypes.h"
#include "../swan-master/newitems_structs.h"





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

C_DECL_END

