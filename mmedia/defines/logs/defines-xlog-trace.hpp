#pragma once
/**
\file       defines-xlog-trace.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_defines
*/

#ifndef U3_XLOG_IMPL
#  ifdef U3_OS_ANDROID
#    define U3_XLOG_IMPL(u3def_mark, u3def_param) ::android::log::android_log_write_helper (ANDROID_LOG_INFO, U3_FILE_LOG_TAG, std::string (u3def_param).c_str ());
#  else
#    define U3_XLOG_IMPL(u3def_mark, u3def_param) std::cout << u3def_mark << "." << U3_FILE_LOG_TAG << "| " << (u3def_param) << std::endl;
#  endif
#endif

#ifdef U3_CNTRL_DISABLED_CONSOLE_LOG
#  ifndef U3_XLOG_DEV
#    define U3_XLOG_DEV(u3def_param)
#  endif
#  ifndef U3_XLOG_ASSERT
#    define U3_XLOG_ASSERT(u3def_param)
#  endif
#  ifndef U3_XLOG_ERROR
#    define U3_XLOG_ERROR(u3def_param)
#  endif
#  ifndef U3_XLOG_UNIMPL
#    define U3_XLOG_UNIMPL(u3def_param)
#  endif
#  ifndef U3_XLOG_WARN
#    define U3_XLOG_WARN(u3def_param)
#  endif
#  ifndef U3_XLOG_MARK
#    define U3_XLOG_MARK(u3def_param)
#  endif
#  ifndef U3_XLOG_TIME
#    define U3_XLOG_TIME(u3def_param)
#  endif
#  ifndef U3_XLOG_DBG
#    define U3_XLOG_DBG(u3def_param)
#  endif
#else

#  ifndef U3_XLOG_DEV
#    define U3_XLOG_DEV(u3def_param) U3_XLOG_IMPL ("dev   |", u3def_param)
#  endif

#  ifndef U3_XLOG_ASSERT
#    define U3_XLOG_ASSERT(u3def_param) U3_XLOG_IMPL ("assert|", u3def_param)
#  endif

#  ifndef U3_XLOG_ERROR
#    define U3_XLOG_ERROR(u3def_param) U3_XLOG_IMPL ("error |", u3def_param)
#  endif

#  ifndef U3_XLOG_UNIMPL
#    define U3_XLOG_UNIMPL(u3def_param) U3_XLOG_IMPL ("unimpl|", u3def_param)
#  endif

#  ifndef U3_XLOG_WARN
#    define U3_XLOG_WARN(u3def_param) U3_XLOG_IMPL ("warn  |", u3def_param)
#  endif

#  ifndef U3_XLOG_MARK
#    define U3_XLOG_MARK(u3def_param) U3_XLOG_IMPL ("mark  |", u3def_param)
#  endif

#  ifndef U3_XLOG_TIME
#    define U3_XLOG_TIME(u3def_param) U3_XLOG_IMPL ("timing|", u3def_param)
#  endif

#  ifndef U3_XLOG_DBG
#    ifdef U3_USE_DEB_LOG_LEVEL
#      define U3_XLOG_DBG(u3def_param) U3_XLOG_DEV (u3def_param);
#    else
#      define U3_XLOG_DBG(u3def_param)
#    endif
#  endif

#endif
