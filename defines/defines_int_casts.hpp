#pragma once
/**
\file       defines_int_casts.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Набор макросов для разрешенных (на данный момент) преобразований типов через static_cast.
*/
#ifndef UUU_ICAST_CHAR
#define UUU_ICAST_CHAR(MVAL) static_cast<char> (MVAL)
#endif

#ifndef UUU_ICAST_UCHAR
#define UUU_ICAST_UCHAR(MVAL) static_cast<unsigned char> (MVAL)
#endif

#ifndef UUU_ICAST_SHORT
#define UUU_ICAST_SHORT(MVAL) static_cast<short> (MVAL)
#endif

#ifndef UUU_ICAST_USHORT
#define UUU_ICAST_USHORT(MVAL) static_cast<unsigned short> (MVAL)
#endif

#ifndef UUU_ICAST_INT
#define UUU_ICAST_INT(MVAL) static_cast<int> (MVAL)
#endif

#ifndef UUU_ICAST_INT_PTR
#define UUU_ICAST_INT_PTR(MVAL) static_cast<intptr_t> (MVAL)
#endif

#ifndef UUU_ICAST_UINT_PTR
#define UUU_ICAST_UINT_PTR(MVAL) static_cast<uintptr_t> (MVAL)
#endif

#ifndef UUU_ICAST_UINT
#define UUU_ICAST_UINT(MVAL) static_cast<unsigned int> (MVAL)
#endif

#ifndef UUU_ICAST_SIZE_T
#define UUU_ICAST_SIZE_T(MVAL) static_cast<std::size_t> (MVAL)
#endif

#ifndef UUU_ICAST_FLOAT
#define UUU_ICAST_FLOAT(MVAL) static_cast<float> (MVAL)
#endif

#ifndef UUU_ICAST_DOUBLE
#define UUU_ICAST_DOUBLE(MVAL) static_cast<double> (MVAL)
#endif

#ifndef UUU_ICAST_INT64
#define UUU_ICAST_INT64(MVAL) static_cast<signed long long> (MVAL)
#endif

#ifndef UUU_ICAST_UINT64
#define UUU_ICAST_UINT64(MVAL) static_cast<unsigned long long> (MVAL)
#endif
