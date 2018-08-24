#pragma once
/**
\file       define-check-mem.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.07.2018
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Различные вспомогательные макросы для проверки состояний или результатов вызовов функций.
*/
#if defined(UUU_DEBUG)

#ifndef UUU_CHECK_COPY_MEM
#define UUU_CHECK_COPY_MEM
#endif

#ifndef UUU_ENABLE_CHECK_RW_MEM
#define UUU_ENABLE_CHECK_RW_MEM
#endif

#ifndef UUU_ENABLE_CHECKED_CALL
#define UUU_ENABLE_CHECKED_CALL
#endif

#else

#ifndef UUU_CHECK_COPY_MEM
#define UUU_CHECK_COPY_MEM
#endif

#ifndef UUU_ENABLE_CHECK_RW_MEM
#define UUU_ENABLE_CHECK_RW_MEM
#endif

#ifndef UUU_ENABLE_CHECKED_CALL
#define UUU_ENABLE_CHECKED_CALL
#endif

#ifndef FAST_CHECK_ARGS_OPTIM_FUNCTS
#define FAST_CHECK_ARGS_OPTIM_FUNCTS
#endif

#endif
