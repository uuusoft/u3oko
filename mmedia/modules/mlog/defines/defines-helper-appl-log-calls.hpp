#pragma once
/**
\file       defines-helper-appl-log-calls.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2022
\project    mlog
*/

#ifndef U3_LOG_APPL_DEV
#  define U3_LOG_APPL_DEV(u3def_info)                                                                                                                   \
    {                                                                                                                                                   \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::develop }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_EXCEPT
#  define U3_LOG_APPL_EXCEPT(u3def_info)                                                                                                                  \
    {                                                                                                                                                     \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::exception }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_ERROR
#  define U3_LOG_APPL_ERROR(u3def_info)                                                                                                               \
    {                                                                                                                                                 \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::error }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_WRN
#  define U3_LOG_APPL_WRN(u3def_info)                                                                                                                   \
    {                                                                                                                                                   \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::warning }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_MARK
#  define U3_LOG_APPL_MARK(u3def_info)                                                                                                               \
    {                                                                                                                                                \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::mark }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_INFO
#  define U3_LOG_APPL_INFO(u3def_info)                                                                                                               \
    {                                                                                                                                                \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::info }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_TIMING
#  define U3_LOG_APPL_TIMING(u3def_info)                                                                                                               \
    {                                                                                                                                                  \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::timing }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_DATA
#  define U3_LOG_APPL_DATA(u3def_info)                                                                                                               \
    {                                                                                                                                                \
      modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::data }(u3def_info); \
    }
#endif

#ifndef U3_LOG_APPL_DBG
#  ifdef U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#    define U3_LOG_APPL_DBG(u3def_info)                                                                                                                 \
      {                                                                                                                                                 \
        modules::mlog::ToLog { libs::properties::vers::links::mids::appl2log, ::libs::events_base::props::modules::log::LogLevels::debug }(u3def_info); \
      }
#  else
#    define U3_LOG_APPL_DBG(u3def_info)
#  endif
#endif
