#ifndef __INCLUDE_ALL_H
#define __INCLUDE_ALL_H

#include <stdint.h>
#include <stddef.h>

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long
#define ARRAY_COUNT(arr) sizeof(arr) / sizeof(arr[0])

#ifdef __GNUC__
#define SWAN_PACKED __attribute__((__packed__))
#define SWAN_ALIGNED(x) __attribute__((aligned(x)))
#endif

#ifdef _MSC_VER //unsupported on MSVC
#define SWAN_PACKED
#define SWAN_ALIGNED(x)
#endif

#define NELEMS(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifdef __cplusplus
#define STRUCT_DECLARE(tag) struct tag;
#define UNION_DECLARE(tag) union tag;
#define ENUM_DECLARE(tag) enum tag : u32;
#else
#define STRUCT_DECLARE(tag) typedef struct tag tag;
#define UNION_DECLARE(tag) typedef union tag tag;
#define ENUM_DECLARE(tag) typedef enum tag tag;
#endif


typedef uint64_t u64;

typedef int64_t s64;

typedef uint32_t u32;

typedef int32_t s32;

typedef uint16_t u16;

typedef int16_t s16;

typedef uint8_t u8;

typedef int8_t s8;

typedef int32_t b32; //32-bit bool

typedef u16 HeapID;

u32& HIDWORD(u64& x)
{
    return *(reinterpret_cast<u32*>(&x) + 1);
}

u32& LODWORD(u64& x)
{
    return *(reinterpret_cast<u32*>(&x) + 0);
}

// u16& HIWORD(u32& x)
// {
//     return *(reinterpret_cast<u16*>(&x) + 1);
// }

// u16& LOWORD(u32& x)
// {
//     return *(reinterpret_cast<u16*>(&x) + 0);
// }

// u8& LOBYTE(u32& x)
// {
//     return *(reinterpret_cast<u8*>(&x) + 0);
// }

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

#define wchar_t short

#ifdef __GNUC__
#define SWAN_PACKED __attribute__((__packed__))
#endif

#ifdef _MSC_VER //unsupported on MSVC
#define SWAN_PACKED 
#endif

#if defined(_MSC_VER)
#define INLINE inline __forceinline
#elif defined(__GNUC__)
#define INLINE inline __attribute__((always_inline))
#endif

#ifdef __cplusplus
#define C_DECL_BEGIN extern "C" {
#define C_DECL_END } //extern "C"
#define SWAN_CPPTYPE(ns, typename) namespace ns { typedef typename typename; }
#define SWAN_CPPTYPE_EX(ns, cppTypename, typename) namespace ns { typedef typename cppTypename; }
#define SWAN_CPPONLY(code) code
#else
#define C_DECL_BEGIN
#define C_DECL_END
#define SWAN_CPPTYPE(ns, typename)
#define SWAN_CPPTYPE_EX(ns, cppTypename, typename)
#define SWAN_CPPONLY(code)
#endif

#endif

