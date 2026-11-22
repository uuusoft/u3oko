#pragma once
/**
\file       defines-helper-events-log-calls.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2022
*/

#ifndef U3_LOG_EVENTS_DEV
#  define U3_LOG_EVENTS_DEV(u3def_format, ...)                       \
    {                                                                \
      modules::mlog::ToLog {                                         \
        ::libs::properties::vers::links::mids::events2appl,          \
        ::libs::events_base::props::modules::log::LogLevels::develop \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));     \
    }
#endif


#ifndef U3_LOG_EVENTS_EXCEPT
#  define U3_LOG_EVENTS_EXCEPT(u3def_format, ...)                      \
    {                                                                  \
      modules::mlog::ToLog {                                           \
        ::libs::properties::vers::links::mids::events2appl,            \
        ::libs::events_base::props::modules::log::LogLevels::exception \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));       \
    }
#endif


#ifndef U3_LOG_EVENTS_ERROR
#  define U3_LOG_EVENTS_ERROR(u3def_format, ...)                   \
    {                                                              \
      modules::mlog::ToLog {                                       \
        ::libs::properties::vers::links::mids::events2appl,        \
        ::libs::events_base::props::modules::log::LogLevels::error \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));   \
    }
#endif


#ifndef U3_LOG_EVENTS_WRN
#  define U3_LOG_EVENTS_WRN(u3def_format, ...)                       \
    {                                                                \
      modules::mlog::ToLog {                                         \
        ::libs::properties::vers::links::mids::events2appl,          \
        ::libs::events_base::props::modules::log::LogLevels::warning \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));     \
    }
#endif


#ifndef U3_LOG_EVENTS_MARK
#  define U3_LOG_EVENTS_MARK(u3def_format, ...)                   \
    {                                                             \
      modules::mlog::ToLog {                                      \
        ::libs::properties::vers::links::mids::events2appl,       \
        ::libs::events_base::props::modules::log::LogLevels::mark \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));  \
    }
#endif


#ifndef U3_LOG_EVENTS_INFO
#  define U3_LOG_EVENTS_INFO(u3def_format, ...)                   \
    {                                                             \
      modules::mlog::ToLog {                                      \
        ::libs::properties::vers::links::mids::events2appl,       \
        ::libs::events_base::props::modules::log::LogLevels::info \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));  \
    }
#endif


#ifndef U3_LOG_EVENTS_DBG
#  ifdef U3_DBG_LOG_LEVEL_ENABLE
#    define U3_LOG_EVENTS_DBG(u3def_format, ...)                     \
      {                                                              \
        modules::mlog::ToLog {                                       \
          ::libs::properties::vers::links::mids::events2appl,        \
          ::libs::events_base::props::modules::log::LogLevels::debug \
        }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));   \
      }
#  else
#    define U3_LOG_EVENTS_DBG(u3def_format, ...)
#  endif
#endif
