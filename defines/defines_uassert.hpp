//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_uassert.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/

#if defined(UUU_DEBUG) || defined(UUU_ENABLE_ASSERT_IN_RELEASE)

#ifndef PREFIX_TEXT_ASSERT
#define PREFIX_TEXT_ASSERT base_functs::consts::strings::str_assert << get_place_call (__FILE__, __LINE__) << ", "
#endif

#ifndef ENABLE_DEBUG_ASSERTS
#define ENABLE_DEBUG_ASSERTS
#endif

#define UASSERTIMPL(condition, info)             \
  if (!(condition))                              \
    {                                            \
      XULOG_ASSERT (PREFIX_TEXT_ASSERT << info); \
      TASSERT (condition);                       \
    }

#define UASSERT(condition) UASSERTIMPL (condition, "invalid state")

#define UASSERTM(condition, info) UASSERTIMPL (condition, info)

#define UASSERT_SIGNAL(info)                   \
  {                                            \
    XULOG_ASSERT (PREFIX_TEXT_ASSERT << info); \
    TASSERT (0);                               \
  }

#define UASSERT_SIGNAL_MSG(mmsg)                 \
  {                                              \
    XULOG_ASSERT ((PREFIX_TEXT_ASSERT << mmsg)); \
    TASSERT (0);                                 \
  }

#define UASSERT_SIGNAL_I64
#define UASSERT_SIGNAL_OPTIM

#else

#define UASSERTIMPL(condition, info)
#define UASSERT(condition)
#define UASSERTM(condition, info)
#define UASSERT_SIGNAL(info)
#define UASSERT_SIGNAL_MSG(mmsg)

#define UASSERT_SIGNAL_I64
#define UASSERT_SIGNAL_OPTIM

#endif
