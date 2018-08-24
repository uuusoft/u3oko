#pragma once
/**
\file       defines_mem_cast.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Набор макросов преобразований указателя, чтобы контролировать применение reinterpret_cast.
*/
#ifndef UUU_CONVERT2VOID
#define UUU_CONVERT2VOID(MVAL) reinterpret_cast<void**> (MVAL)
#endif

#ifndef UUU_CONVERT2VOID_ptr
#define UUU_CONVERT2VOID_ptr(MVAL) reinterpret_cast<void*> (MVAL)
#endif

#ifndef UUU_MEM_CAST
#define UUU_MEM_CAST reinterpret_cast
#endif

#ifndef UUU_MEM_FUNCT_CAST
#define UUU_MEM_FUNCT_CAST reinterpret_cast
#endif

#ifndef UUU_C2CPP_CAST
#define UUU_C2CPP_CAST reinterpret_cast
#endif
