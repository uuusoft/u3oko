#pragma once
/**
\file       defines-helper-http-log-calls.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2022
\project    u3_module_log
*/

#ifndef U3_LOG_HTTP_DEV
#  define U3_LOG_HTTP_DEV(u3def_info)                                                                                                                   \
    {                                                                                                                                                   \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::develop }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_EXCEPT
#  define U3_LOG_HTTP_EXCEPT(u3def_info)                                                                                                                  \
    {                                                                                                                                                     \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::exception }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_ERROR
#  define U3_LOG_HTTP_ERROR(u3def_info)                                                                                                               \
    {                                                                                                                                                 \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::error }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_WRN
#  define U3_LOG_HTTP_WRN(u3def_info)                                                                                                                   \
    {                                                                                                                                                   \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::warning }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_MARK
#  define U3_LOG_HTTP_MARK(u3def_info)                                                                                                               \
    {                                                                                                                                                \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::mark }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_INFO
#  define U3_LOG_HTTP_INFO(u3def_info)                                                                                                               \
    {                                                                                                                                                \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::info }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_TIMING
#  define U3_LOG_HTTP_TIMING(u3def_info)                                                                                                               \
    {                                                                                                                                                  \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::timing }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_DATA
#  define U3_LOG_HTTP_DATA(u3def_info)                                                                                                               \
    {                                                                                                                                                \
      modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::data }(u3def_info); \
    }
#endif

#ifndef U3_LOG_HTTP_DBG
#  ifdef U3_USE_DEB_LOG_LEVEL
#    define U3_LOG_HTTP_DBG(u3def_info)                                                                                                                 \
      {                                                                                                                                                 \
        modules::uuu_log::ToLog { libs::properties::vers::links::mids::http2appl, ::libs::ievents::props::modules::log::LogLevels::debug }(u3def_info); \
      }
#  else
#    define U3_LOG_HTTP_DBG(u3def_info)
#  endif
#endif
