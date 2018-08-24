#pragma once
/**
\file       defines_check_state.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Различные вспомогательные макросы для проверки состояний или результатов вызовов функций.
*/
#if defined(UUU_FORCE_SKIP_CHECK_CALL)
#define CHECK_STATE(x, minfo)
#define CHECK_STATE_NA(x, minfo)
#define CHECK_STATE_RET(x, minfo, ret)
#define CHECK_STATE_VRET(x, minfo)
#else

#ifndef UUU_USE_EXCEPTION_FROM_CHECK_CALL
#define UUU_THROW_EXCEPTION_CHECK_CALL(info)
#else
#define UUU_THROW_EXCEPTION_CHECK_CALL(info) UUU_THROW_EXCEPTION (info)
#endif

#ifndef UUU_UASSERT_CHECK_CALL
#define UUU_UASSERT_CHECK_CALL(info) UASSERT_SIGNAL ("failed check, " << info);
#endif

#if defined(UUU_DEBUG)
#define CHECK_STATE(x, minfo)                 \
  if (!(x))                                   \
    {                                         \
      UUU_UASSERT_CHECK_CALL (minfo);         \
      UUU_THROW_EXCEPTION_CHECK_CALL (minfo); \
    }
#else
#define CHECK_STATE(x, minfo)                 \
  if (!(x))                                   \
    {                                         \
      UUU_UASSERT_CHECK_CALL (minfo);         \
      UUU_THROW_EXCEPTION_CHECK_CALL (minfo); \
    }
#endif

#if defined(UUU_DEBUG)
#define CHECK_STATE_NA(x, minfo)              \
  if (!(x))                                   \
    {                                         \
      UUU_THROW_EXCEPTION_CHECK_CALL (minfo); \
    }
#else
#define CHECK_STATE_NA(x, minfo)              \
  if (!(x))                                   \
    {                                         \
      UUU_THROW_EXCEPTION_CHECK_CALL (minfo); \
    }
#endif

#if defined(UUU_DEBUG)
#define CHECK_STATE_RET(x, minfo, ret) \
  if (!(x))                            \
    {                                  \
      XULOG_ERROR (minfo);             \
      return ret;                      \
    }
#else
#define CHECK_STATE_RET(x, minfo, ret) \
  if (!(x))                            \
    {                                  \
      XULOG_ERROR (minfo);             \
      return ret;                      \
    }
#endif

#if defined(UUU_DEBUG)
#define CHECK_STATE_VRET(x, minfo) \
  if (!(x))                        \
    {                              \
      XULOG_ERROR (minfo);         \
      return;                      \
    }
#else
#define CHECK_STATE_VRET(x, minfo) \
  if (!(x))                        \
    {                              \
      XULOG_ERROR (minfo);         \
      return;                      \
    }
#endif

#if defined(UUU_DEBUG)
#define CHECK_CALL(x, minfo)                  \
  if (!(x))                                   \
    {                                         \
      UUU_UASSERT_CHECK_CALL (minfo);         \
      UUU_THROW_EXCEPTION_CHECK_CALL (minfo); \
    }
#else
#define CHECK_CALL(x, minfo)                  \
  if (!(x))                                   \
    {                                         \
      UUU_UASSERT_CHECK_CALL (minfo);         \
      UUU_THROW_EXCEPTION_CHECK_CALL (minfo); \
    }
#endif

#if defined(UUU_DEBUG)
#define CHECK_CALL_NO_THROW(x)                      \
  if (!(x))                                         \
    {                                               \
      UUU_UASSERT_CHECK_CALL ("unexpectedly call"); \
    }
#else
#define CHECK_CALL_NO_THROW(x)                      \
  if (!(x))                                         \
    {                                               \
      UUU_UASSERT_CHECK_CALL ("unexpectedly call"); \
    }
#endif

#endif
