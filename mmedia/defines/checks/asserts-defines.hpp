#pragma once
/**
\file       asserts-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/
#if defined(U3_CNTRL_DEBUG) || defined(U3_CNTRL_RELEASE_ASSERT)

#  ifndef U3_TEXT_PLACE_ASSERT
#    define U3_TEXT_PLACE_ASSERT std::string (".....") + get_place_call (__FILE__, __LINE__)
#  endif

#  ifndef U3_ASSERT_IMPL
#    define U3_ASSERT_IMPL(u3def_condition, u3def_info, u3def_enable_throw) \
      if (!(u3def_condition))                                               \
      {                                                                     \
        U3_XLOG_ASSERT (u3def_info + U3_TEXT_PLACE_ASSERT);                 \
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
#    define U3_ASSERT_SIGNAL(u3def_info)                    \
      {                                                     \
        U3_XLOG_ASSERT (u3def_info + U3_TEXT_PLACE_ASSERT); \
        U3_THROW_EXCEPTION (u3def_info);                    \
      }
#  endif

#  ifndef U3_ASSERT_SIGNAL_NT
#    define U3_ASSERT_SIGNAL_NT(u3def_info)                 \
      {                                                     \
        U3_XLOG_ASSERT (u3def_info + U3_TEXT_PLACE_ASSERT); \
      }
#  endif

#  ifndef U3_ASSERT_SIGNAL_I64
#    define U3_ASSERT_SIGNAL_I64                                            \
      {                                                                     \
        U3_XLOG_ASSERT (std::string ("signal_i64") + U3_TEXT_PLACE_ASSERT); \
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
