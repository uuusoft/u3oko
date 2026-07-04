#pragma once
/**
\file       defines-asserts.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/

/// old shit
/// Функция для формирования текстового описания точки вызова (имя функции + номер строки)
/// \param[in]  file имя файла
/// \param[in]  line номер строки
/// \return     текстовое описание точки вызова
inline std::string
get_place_call (const char* file, std::int32_t line)
{
  std::string ret;

  ret.reserve (256);
  ret += file;
  ret += ":";
  ret += std::to_string (line);
  return ret;
}

#if defined(U3_CNTRL_DEBUG) || defined(U3_CNTRL_RELEASE_ASSERT)

#  ifndef U3_TEXT_PLACE_ASSERT
#    define U3_TEXT_PLACE_ASSERT std::string (".....") + get_place_call (__FILE__, __LINE__)
#  endif

#  ifndef U3_ASSERT_IMPL
#    define U3_ASSERT_IMPL(u3def_cond, u3def_info, u3def_throw) \
      if (!(u3def_cond))                                        \
      {                                                         \
        U3_XLOG_ASSERT (u3def_info + U3_TEXT_PLACE_ASSERT);     \
        if (u3def_throw)                                        \
        {                                                       \
          U3_THROW_EXCEPT (u3def_info);                         \
        }                                                       \
      }
#  endif

#  ifndef U3_ASSERT
#    define U3_ASSERT(u3def_cond) U3_ASSERT_IMPL (u3def_cond, "STATE-FAILED", true)
#  endif

#  ifndef U3_ASSERT_NT
#    define U3_ASSERT_NT(u3def_cond, u3def_info) U3_ASSERT_IMPL (u3def_cond, std::string ("STATE-FAILED-SOFT: ") + u3def_info, false)
#  endif

#  ifndef U3_ASSERT_SIGNAL
#    define U3_ASSERT_SIGNAL(u3def_info)                    \
      {                                                     \
        U3_XLOG_ASSERT (u3def_info + U3_TEXT_PLACE_ASSERT); \
        U3_THROW_EXCEPT (u3def_info);                       \
      }
#  endif

#  ifndef U3_ASSERT_SIGNAL_NT
#    define U3_ASSERT_SIGNAL_NT(u3def_info)                 \
      {                                                     \
        U3_XLOG_ASSERT (u3def_info + U3_TEXT_PLACE_ASSERT); \
      }
#  endif

#  ifndef U3_ASSERT_SIGNAL_I64
#    define U3_ASSERT_SIGNAL_I64                                                           \
      {                                                                                    \
        U3_XLOG_ASSERT (std::string ("SIGNAL-I64-NOTIMPLEMENTED") + U3_TEXT_PLACE_ASSERT); \
      }
#  endif

#else
#  ifndef U3_ASSERT
#    define U3_ASSERT(u3def_cond)
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
