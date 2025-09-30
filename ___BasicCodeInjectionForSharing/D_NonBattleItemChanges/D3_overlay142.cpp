#include <stdint.h>
#include <stddef.h>
#include "kPrint.h"
#include "swantypes.h"

extern u32 g_GameBeaconSys;
STRUCT_DECLARE(GameData)
#define GAME_DATA *(GameData **)(g_GameBeaconSys + 4)

#pragma region defintiions
enum ItemType
{
    ITEMTYPE_STD = 0x0,
    ITEMTYPE_EFFECT = 0x1,
    ITEMTYPE_TM = 0x2,
    ITEMTYPE_BERRY = 0x3,
    ITEMTYPE_KEY = 0x4,
    ITEMTYPE_FREE_SPACE = 0x5,
    ITEMTYPE_MAX = 0x6,
};
struct BagItem
{
    u16 ItemID;
    u16 Count;
};
struct BagSaveData
{
    BagItem Items[310];
    BagItem KeyItems[83];
    BagItem TMsHMs[109];
    BagItem Medicine[48];
    BagItem Berries[64];
    u32 FreeSpaceBits[21];
};
struct MsgFileEntry
{
    int Offset;
    u16 CharCount;
    u16 Padding;
};
struct EventWorkSave
{
    u16 Works[431];
    u8 FlagBytes[383];
    u8 CanRespawnHiddenItems;
};
struct MsgFileHeader
{
    u16 SectionCount;
    u16 LineCount;
    int DataBottomOfs;
    int Reserved;
};
struct MsgFileHandle
{
    MsgFileHeader Header;
    int DataTopOffsets[1];
};
struct SWAN_PACKED SWAN_ALIGNED(2) StrBuf
{
    u16 CharCapacity;
    u16 CharCount;
    int Magic;
    wchar_t String[1];
};
struct SWAN_ALIGNED(4) MsgData
{
    MsgFileHandle *FileHandle;
    int RawData;
    MsgFileEntry CurrentEntry;
    int MsgOfsInArc;
    void *MsgArc;
    u16 heapID;
    u8 LanguageId;
    u8 IsAllPreload;
};
struct WordSetBuffer
{
    char field_0;
    char field_1;
    char field_2;
    char field_3;
    char field_4;
    char Pad1;
    u16 Pad2;
    StrBuf *Strbuf;
};
struct WordSetSystem
{
    int WordSetCount;
    int HeapID;
    WordSetBuffer *Buffers;
    StrBuf *MainStrbuf;
    int field_10;
};

extern "C" void sub_204C150(int result, int a2);
extern "C" int sub_21999B8(int a1);
extern "C" void *sub_2199968(int a1, int a2);
extern "C" void sub_219DDE0(int a1, int a2);
extern "C" int sub_2048520(int a1);
extern "C" void sub_2047168(int a1, u8 a2);
extern "C" u16 PML_ItemGetTMWazaID(u16 itemId);
extern "C" ItemType BagSave_GetExistingItemPocket(BagSaveData *bag, u32 itemId);
extern "C" int PML_ItemGetHMID(unsigned int itemId);
extern "C" void GFL_MsgDataLoadStrbuf(MsgData *msgdata, int msgID, StrBuf *strbuf);
extern "C" u8 PML_ItemGetTMBitMask(u16 itemNum);
extern "C" void WordSetNumber(WordSetSystem *a1, int strbufIdx, int value, u32 magnitude, u32 b, bool isAscii);
extern "C" int loadMoveNameToStrbuf(WordSetSystem *pFontInfoBuf, u8 charCount, u16 tmMove);
extern "C" int GFL_WordSetFormatStrbuf(WordSetSystem *wordSet, StrBuf *dest, StrBuf *source);
extern "C" int sub_21A0130(int a1, int a2, int a3, __int16 a4, __int16 a5, unsigned __int16 a6);
extern "C" void sub_219F4F0(int a1, unsigned __int16 a2);
extern "C" void sub_2048270(int a1);
extern "C" int sub_21999F8(int a1, int a2, int a3);
extern "C" int sub_21A03EC(int a1);
extern "C" void sub_20484E0(unsigned __int8 *a1);
extern "C" int sub_2199A08(int a1, int a2, int a3);
extern "C" unsigned int GFL_FontGetBlockWidth(StrBuf *strbuf, int font, int gapSize);
extern "C" void setItemDescriptionTextToStrbuf(u16 *subStrBuf, int msgID, s16 blkGroupID);
extern "C" void sub_21A0174(int *a1);
extern "C" int sub_219E51C(int a1, unsigned __int16 a2);
extern "C" EventWorkSave *GameData_GetEventWork(void *gameData);
extern "C" u16 *GetSaveWkPtr(EventWorkSave *eventWork, int swkId);
extern "C" ItemType BagSave_GetPocketPtrByItem(BagSaveData *bag, u16 itemId, BagItem **pPocket, u32 *pPocketLimit);
extern "C" BagItem *BagSave_GetItemHandleAddCheckCore(
    BagItem *pocket,
    u32 itemTypeMaxCount,
    u16 itemId,
    u16 quantity,
    u16 maxQuantity);

extern "C" u32 getTMSetting()
{

    EventWorkSave *eventWork = GameData_GetEventWork(GAME_DATA);
    u16 *lvl_cap_ptr = GetSaveWkPtr(eventWork, 16437);
    return *lvl_cap_ptr;
}

bool isItemHM(int id)
{
    return (id >= 0x01A4 && id <= 0x01A9);
}

#pragma endregion

/*

        --------------------------------------------------------------------------------------------------
        -------------------- HANDLED THE BAG GRAPHIC FOR TMS AND OTHER ITEMS -----------------------------
        --------------------------------------------------------------------------------------------------

*/
extern "C" void THUMB_BRANCH_SetupTMInfo(int a1)
{
    unsigned int v1;         // r6
    unsigned int v3;         // r4
    int v4;                  // r0
    u16 *v5;                 // r0
    u16 *v6;                 // r4
    int v7;                  // r0
    int v8;                  // r0
    int v9;                  // r0
    int v10;                 // r0
    int HMID;                // r6
    int TMBitMask;           // r2
    unsigned int BlockWidth; // r0
    int tmMove;              // [sp+8h] [bp-20h]
    int ExistingItemPocket;  // [sp+Ch] [bp-1Ch]

    v1 = 0;
    v3 = 0;
    do
        sub_204C150(*(_DWORD *)(a1 + 4 * v1++ + 1748), 0);
    while (v1 < 3);
    do
        sub_204C150(*(_DWORD *)(a1 + 4 * v3++ + 1760), 0);
    while (v3 < 0x11);
    v4 = sub_21999B8(a1);
    v5 = (u16 *)sub_2199968(a1, v4);
    v6 = v5;

    if (v5 && *v5)
    {
        sub_219DDE0(a1, 1);
        v7 = sub_2048520(*(_DWORD *)(a1 + 1900));
        sub_2047168(v7, 0);
        v8 = sub_2048520(*(_DWORD *)(a1 + 1876));
        sub_2047168(v8, 0);
        v9 = sub_2048520(*(_DWORD *)(a1 + 1884));
        sub_2047168(v9, 0);
        v10 = sub_2048520(*(_DWORD *)(a1 + 1892));
        sub_2047168(v10, 0);
        tmMove = PML_ItemGetTMWazaID(*v6);
        ExistingItemPocket = BagSave_GetExistingItemPocket(*(BagSaveData **)(a1 + 24), *v6);
        if (tmMove)
        {
            HMID = PML_ItemGetHMID(*v6);
            if (HMID == 255)
            {
                GFL_MsgDataLoadStrbuf(*(MsgData **)(a1 + 1312), 69, *(StrBuf **)(a1 + 1320));
                TMBitMask = PML_ItemGetTMBitMask(*v6);
                WordSetNumber(*(WordSetSystem **)(a1 + 1316), 0, TMBitMask + 1, 2u, 2u, 1);
            }
            else
            {
                GFL_MsgDataLoadStrbuf(*(MsgData **)(a1 + 1312), 71, *(StrBuf **)(a1 + 1320));
                WordSetNumber(*(WordSetSystem **)(a1 + 1316), 0, HMID + 1, 2u, 2u, 1);
            }
            loadMoveNameToStrbuf(*(WordSetSystem **)(a1 + 1316), 1u, tmMove);
            GFL_WordSetFormatStrbuf(*(WordSetSystem **)(a1 + 1316), *(StrBuf **)(a1 + 1324), *(StrBuf **)(a1 + 1320));
            sub_21A0130(a1, a1 + 1876, *(_DWORD *)(a1 + 1324), 0, 4, 0x3DC0u);
            sub_219F4F0(a1, tmMove);
            sub_2048270(*(_DWORD *)(a1 + 1884));

            // ADD LOGIC CHECK FOR DISPLAYING THE AMOUNTS
            if (!getTMSetting() && !isItemHM(*v6))
            {
                GFL_MsgDataLoadStrbuf(*(MsgData **)(a1 + 1312), 131, *(StrBuf **)(a1 + 1320));
                WordSetNumber(*(WordSetSystem **)(a1 + 1316), 0, v6[1], 3u, 0, 1);
                GFL_WordSetFormatStrbuf(*(WordSetSystem **)(a1 + 1316), *(StrBuf **)(a1 + 1324), *(StrBuf **)(a1 + 1320));
                sub_21A0130(a1, a1 + 1884, *(_DWORD *)(a1 + 1324), 0, 4, 0x3DC0u);
            }
        }
        else
        {
            GFL_MsgDataLoadStrbuf(*(MsgData **)(a1 + 1312), 134, *(StrBuf **)(a1 + 1320));
            sub_21999F8(a1, 0, *v6);
            GFL_WordSetFormatStrbuf(*(WordSetSystem **)(a1 + 1316), *(StrBuf **)(a1 + 1324), *(StrBuf **)(a1 + 1320));
            sub_21A0130(a1, a1 + 1876, *(_DWORD *)(a1 + 1324), 0, 4, 0x3DC0u);
            if (sub_21A03EC((unsigned __int8)ExistingItemPocket))
            {
                GFL_MsgDataLoadStrbuf(*(MsgData **)(a1 + 1312), 131, *(StrBuf **)(a1 + 1320));
                WordSetNumber(*(WordSetSystem **)(a1 + 1316), 0, v6[1], 3u, 0, 1);
                GFL_WordSetFormatStrbuf(*(WordSetSystem **)(a1 + 1316), *(StrBuf **)(a1 + 1324), *(StrBuf **)(a1 + 1320));
                sub_21A0130(a1, a1 + 1884, *(_DWORD *)(a1 + 1324), 0, 4, 0x3DC0u);
            }
            else
            {
                sub_2048270(*(_DWORD *)(a1 + 1884));
            }
            sub_20484E0(*(unsigned __int8 **)(a1 + 1868));
        }

        // Adds the graphic at the top indicating the pocket of origin for free space
        if (*(_DWORD *)(a1 + 2092) == 5)
        {
            sub_2199A08(a1, 0, ExistingItemPocket);
            GFL_MsgDataLoadStrbuf(*(MsgData **)(a1 + 1312), 139, *(StrBuf **)(a1 + 1320));
            GFL_WordSetFormatStrbuf(*(WordSetSystem **)(a1 + 1316), *(StrBuf **)(a1 + 1324), *(StrBuf **)(a1 + 1320));
            BlockWidth = GFL_FontGetBlockWidth(*(StrBuf **)(a1 + 1324), *(_DWORD *)(a1 + 1332), 0);
            sub_21A0130(a1, a1 + 1900, *(_DWORD *)(a1 + 1324), (96 - BlockWidth) >> 1, 0, 0x3DC0u);
        }
        else
        {
            sub_20484E0(*(unsigned __int8 **)(a1 + 1900));
            sub_2048270(*(_DWORD *)(a1 + 1900));
        }
        setItemDescriptionTextToStrbuf(*(u16 **)(a1 + 1320), *v6, *(_WORD *)(a1 + 1356));
        sub_21A0130(a1, a1 + 1892, *(_DWORD *)(a1 + 1320), 0, 4, 0x3DC0u);
        sub_21A0174((int *)(a1 + 1900));
        sub_21A0174((int *)(a1 + 1876));
        sub_21A0174((int *)(a1 + 1884));
        sub_21A0174((int *)(a1 + 1892));
        sub_219E51C(a1, *v6);
    }
    else
    {
        sub_219DDE0(a1, 0);
    }
}

/*

        --------------------------------------------------------------------------------------------------
        -------------------- MAXIMUM POCKET AMOUNT (FOR SHOPS AND SCRIPTS) -------------------------------
        --------------------------------------------------------------------------------------------------

*/

extern "C" BagItem *THUMB_BRANCH_BagSave_GetItemHandleAddCheck(BagSaveData *bag, u16 item_idx, u16 quantity, u16 heapId)
{
    u32 pItemTypeMaxCount; // [sp+4h] [bp-14h] BYREF
    BagItem *pocket;       // [sp+8h] [bp-10h] BYREF

    if (BagSave_GetPocketPtrByItem(bag, item_idx, &pocket, &pItemTypeMaxCount) == ITEMTYPE_TM)
    {
        return BagSave_GetItemHandleAddCheckCore(pocket, pItemTypeMaxCount, item_idx, quantity, 0x3E7u);
    }
    else
    {
        return BagSave_GetItemHandleAddCheckCore(pocket, pItemTypeMaxCount, item_idx, quantity, 0x3E7u);
    }
}