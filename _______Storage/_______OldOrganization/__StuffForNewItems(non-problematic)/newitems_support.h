#include "newitems_support_structs.h"

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

extern bool BagSave_CheckAmount(BagSaveData *bag, u16 itemId, int quantity);
extern unsigned int GFL_FontGetBlockWidth(StrBuf *strbuf, GFLFont *font, int gapSize);
extern GFLBitmap * BmpWin_GetBitmap(BmpWin *bmpWin);
extern u32 GFL_BitmapGetWidth(GFLBitmap *bmp);
extern void  sub_21AD4CC(int a1, GFLBitmap *a2, u16 a3, int a4, StrBuf *strBuf, GFLFont *a5, u16 a7);
extern ShopUIWork * sub_2026548(void *a1);
extern void WordSetNumber(WordSetSystem *a1, int strbufIdx, int value, u32 magnitude, u32 b, bool isAscii);
extern void GFL_WordSetFormatStrbuf(WordSetSystem *wordSet, StrBuf *dest, StrBuf *source);
extern b32 PML_ItemIsTMHM(u16 itemNum);
extern void* GameData_GetPokedex(GameData *gameData);
extern u32 PokeParty_GetPkmCount(PokeParty *pPartyBlk);
extern PartyPkm* PokeParty_GetPkm(PokeParty *party, int slot);
extern u32 PokeParty_GetParam(PartyPkm *pPkm, PkmField field, void *extra);
extern bool PokeParty_ChangeForme(PartyPkm *pkm, u32 forme);
extern int PokeDex_RegistPkm(void *pDexAddress, PartyPkm *pkm);
extern PersonalData* PML_PersonalLoad(u16 species, u16 form, HeapID heapId);
extern BagSaveData * GameData_GetBag(GameData *gameData);
extern bool BagSave_CheckAmount(BagSaveData *bag, u16 itemId, int quantity);
extern u32 PassPower_ApplyLuckyShiny(u32 baseShinyRerollCount);
extern u32 FieldEncount_GenPID(EncountManager *mgr, PersonalData *personal, WildPokemonParam *mons);
extern bool PML_UtilPIDIsRare(u32 idSet, u32 pid);
extern void PokeParty_CreatePkm(
        PartyPkm *pkm,
        MonsNo species,
        u8 level,
        u32 tidSet,
        AbilLock abil,
        u32 ivs,
        u32 pid,
        u32 abil_mask);
extern void PokeParty_SetDefaultMoves(PartyPkm *pkm);
extern void PokeParty_SetHiddenAbil(PartyPkm *pPkm, u16 species, u16 forme);
extern void  PokeParty_SetParam(PartyPkm *pPkm, PkmField field, u32 data);
extern void FieldEncount_SetRandomHeldItem(
        PartyPkm *pPkm,
        PersonalData *pPersonalData,
        bool third_item,
        bool compoundeyes);
extern u8  getTrainerGender(void *pTrainerInfo);
extern wchar_t * GetPlayerName(int result);
extern void PokeParty_RecalcStats(PartyPkm *pPoke);
extern void PML_PersonalFree(PersonalData *personal);
extern u32 GFL_RandomLCAlt(u32 max);
extern u16 * GetGameDataPlayerInfo(GameData *gameData);
   extern EventWorkSave *GameData_GetEventWork(void *gameData);
    extern u16 * EventWork_GetWkPtr(EventWorkSave *eventWork, int swkId);
extern u32  PML_PersonalGetParam(PersonalData *personal, PersonalField field);
extern PersonalData *  PML_PersonalLoadBW2(u16 species, u16 form);
extern void * copyTrainerNameToNewStrbuf(wchar_t *pText, HeapID heapId);
extern StrBuf * GFL_MsgDataLoadStrbufNew(MsgData *msgData, int msgId);
extern void  GFL_StrBufFree(StrBuf *pStrbuf);
extern int g_PMLSpeciesNamesResident;
extern void PokeParty_SetupMetData(
        PartyPkm *pkm,
        PokemonObtainType obtain_type,
        void *pTrainerInfo,
        u16 location,
        HeapID heapId);
extern void PokeParty_PPRecover(PartyPkm *pkm);
extern void PokeParty_Recover(PartyPkm *pkm);
extern u16 * ScriptReadVar(void *vm, void *cmd);
extern GameData* FieldScriptEnv_GetGameData(void *cmd);
extern HeapID FieldScriptEnv_GetHeapID(void *env);
extern PokeParty * GameData_GetParty(GameData *pBaseBlk);
extern u16 ScriptReadAny(void *vm, void *cmd);
extern int PokeParty_GetCapacity(PokeParty *pPartyBlk);
extern void* FieldScriptEnv_GetGameSystem(void *cmd);
extern PartyPkm * PokeParty_NewTempPkm(MonsNo species, u32 level, u32 sidtid, AbilLock abil_num, HeapID heapId);
extern void GFL_HeapFree(void *heap);
extern bool PokeParty_AddPkm(PokeParty *party, PartyPkm *pPkm);


C_DECL_END