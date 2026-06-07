#pragma once
/**
\file       check-state-defines.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_defines
\brief      Различные вспомогательные макросы для проверки состояний или результатов вызовов функций
*/

#ifdef U3_CNTRL_FORCE_SKIP_CHECK_CALL
#  define U3_CHECK(u3def_cond, u3def_minfo)
#  define U3_CHECK_NT(u3def_cond, u3def_mfino)
#else

#  ifndef U3_ASSERT_CHECK_CALL
#    define U3_ASSERT_CHECK_CALL(u3def_info) U3_ASSERT_SIGNAL (std::string ("check failed: ") + u3def_info)
#  endif

#  ifndef U3_ASSERT_CHECK_CALL_NT
#    define U3_ASSERT_CHECK_CALL_NT(u3def_info) U3_ASSERT_SIGNAL_NT (std::string ("check failed: ") + u3def_info)
#  endif

#  define U3_CHECK(u3def_cond, u3def_minfo) \
    if (!(u3def_cond))                      \
    {                                       \
      U3_ASSERT_CHECK_CALL (u3def_minfo);   \
    }

#  define U3_CHECK_NT(u3def_cond, u3def_minfo) \
    if (!(u3def_cond))                         \
    {                                          \
      U3_ASSERT_CHECK_CALL_NT (u3def_minfo);   \
    }

#endif
