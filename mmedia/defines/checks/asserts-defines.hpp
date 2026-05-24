#pragma once
/**
\file       asserts-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_defines
*/
#if defined(U3_CNTRL_DEBUG) || defined(U3_CNTRL_RELEASE_ASSERT)

#  ifndef U3_TEXT_PREFIX_ASSERT
#    define U3_TEXT_PREFIX_ASSERT get_place_call (__FILE__, __LINE__) + std::string ("-")
#  endif

#  ifndef U3_ASSERT_IMPL
#    define U3_ASSERT_IMPL(u3def_condition, u3def_info, u3def_enable_throw) \
      if (!(u3def_condition))                                               \
      {                                                                     \
        U3_XLOG_ASSERT (U3_TEXT_PREFIX_ASSERT + u3def_info);                \
        if (u3def_enable_throw)                                             \
        {                                                                   \
          U3_THROW_EXCEPTION (u3def_info);                                  \
        }                                                                   \
      }
#  endif

#  ifndef U3_ASSERT
#    define U3_ASSERT(u3def_condition) U3_ASSERT_IMPL (u3def_condition, "invalid state", true)
#  endif

#  ifndef U3_ASSERT_NT
#    define U3_ASSERT_NT(u3def_condition, u3def_info) U3_ASSERT_IMPL (u3def_condition, std::string ("invalid state: ") + u3def_info, false)
#  endif

#  ifndef U3_ASSERT_SIGNAL
#    define U3_ASSERT_SIGNAL(u3def_info)                     \
      {                                                      \
        U3_XLOG_ASSERT (U3_TEXT_PREFIX_ASSERT + u3def_info); \
        U3_THROW_EXCEPTION (u3def_info);                     \
      }
#  endif

#  ifndef U3_ASSERT_SIGNAL_NT
#    define U3_ASSERT_SIGNAL_NT(u3def_info)                  \
      {                                                      \
        U3_XLOG_ASSERT (U3_TEXT_PREFIX_ASSERT + u3def_info); \
      }
#  endif

#  ifndef U3_ASSERT_SIGNAL_I64
#    define U3_ASSERT_SIGNAL_I64                \
      {                                         \
        U3_XLOG_ASSERT (U3_TEXT_PREFIX_ASSERT); \
      }
#  endif

#else

#  ifndef U3_ASSERT
#    define U3_ASSERT(u3def_condition)
#  endif

#  ifndef U3_ASSERT_SIGNAL
#    define U3_ASSERT_SIGNAL(u3def_info)
#  endif

#  ifndef U3_ASSERT_SIGNAL_I64
#    define U3_ASSERT_SIGNAL_I64
#  endif

#endif


#ifndef U3_ASSERT_TODO_OPTIM
#  define U3_ASSERT_TODO_OPTIM
#endif
