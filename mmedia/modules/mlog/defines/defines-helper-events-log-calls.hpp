#pragma once
/**
\file       defines-helper-events-log-calls.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2022
\project    mlog
*/

#ifndef U3_LOG_EVENTS_DEV
#  define U3_LOG_EVENTS_DEV(u3def_info)                                                                                                                    \
    {                                                                                                                                                      \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::develop }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_EXCEPT
#  define U3_LOG_EVENTS_EXCEPT(u3def_info)                                                                                                                   \
    {                                                                                                                                                        \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::exception }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_ERROR
#  define U3_LOG_EVENTS_ERROR(u3def_info)                                                                                                                \
    {                                                                                                                                                    \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::error }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_WRN
#  define U3_LOG_EVENTS_WRN(u3def_info)                                                                                                                    \
    {                                                                                                                                                      \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::warning }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_MARK
#  define U3_LOG_EVENTS_MARK(u3def_info)                                                                                                                \
    {                                                                                                                                                   \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::mark }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_INFO
#  define U3_LOG_EVENTS_INFO(u3def_info)                                                                                                                \
    {                                                                                                                                                   \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::info }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_TIMING
#  define U3_LOG_EVENTS_TIMING(u3def_info)                                                                                                                \
    {                                                                                                                                                     \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::timing }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_DATA
#  define U3_LOG_EVENTS_DATA(u3def_info)                                                                                                                \
    {                                                                                                                                                   \
      modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::data }(u3def_info); \
    }
#endif

#ifndef U3_LOG_EVENTS_DBG
#  ifdef U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#    define U3_LOG_EVENTS_DBG(u3def_info)                                                                                                                  \
      {                                                                                                                                                    \
        modules::mlog::ToLog { libs::properties::vers::links::mids::events2appl, ::libs::events_base::props::modules::log::LogLevels::debug }(u3def_info); \
      }
#  else
#    define U3_LOG_EVENTS_DBG(u3def_info)
#  endif
#endif
