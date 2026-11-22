#pragma once
/**
\file       defines-helper-data-log-calls.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.06.2022
*/

#ifndef U3_LOG_DATA_DEV
#  define U3_LOG_DATA_DEV(u3def_format, ...)                         \
    {                                                                \
      modules::mlog::ToLog {                                         \
        ::libs::properties::vers::links::mids::mdata2appl,           \
        ::libs::events_base::props::modules::log::LogLevels::develop \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));     \
    }
#endif


#ifndef U3_LOG_DATA_EXCEPT
#  define U3_LOG_DATA_EXCEPT(u3def_format, ...)                        \
    {                                                                  \
      modules::mlog::ToLog {                                           \
        ::libs::properties::vers::links::mids::mdata2appl,             \
        ::libs::events_base::props::modules::log::LogLevels::exception \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));       \
    }
#endif


#ifndef U3_LOG_DATA_ERROR
#  define U3_LOG_DATA_ERROR(u3def_format, ...)                     \
    {                                                              \
      modules::mlog::ToLog {                                       \
        ::libs::properties::vers::links::mids::mdata2appl,         \
        ::libs::events_base::props::modules::log::LogLevels::error \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));   \
    }
#endif


#ifndef U3_LOG_DATA_WRN
#  define U3_LOG_DATA_WRN(u3def_format, ...)                         \
    {                                                                \
      modules::mlog::ToLog {                                         \
        ::libs::properties::vers::links::mids::mdata2appl,           \
        ::libs::events_base::props::modules::log::LogLevels::warning \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));     \
    }
#endif


#ifndef U3_LOG_DATA_MARK
#  define U3_LOG_DATA_MARK(u3def_format, ...)                     \
    {                                                             \
      modules::mlog::ToLog {                                      \
        ::libs::properties::vers::links::mids::mdata2appl,        \
        ::libs::events_base::props::modules::log::LogLevels::mark \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));  \
    }
#endif


#ifndef U3_LOG_DATA_INFO
#  define U3_LOG_DATA_INFO(u3def_format, ...)                     \
    {                                                             \
      modules::mlog::ToLog {                                      \
        ::libs::properties::vers::links::mids::mdata2appl,        \
        ::libs::events_base::props::modules::log::LogLevels::info \
      }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));  \
    }
#endif


#ifndef U3_LOG_DATA_DBG
#  ifdef U3_DBG_LOG_LEVEL_ENABLE
#    define U3_LOG_DATA_DBG(u3def_format, ...)                       \
      {                                                              \
        modules::mlog::ToLog {                                       \
          ::libs::properties::vers::links::mids::mdata2appl,         \
          ::libs::events_base::props::modules::log::LogLevels::debug \
        }(std::format (u3def_format __VA_OPT__ (, ) __VA_ARGS__));   \
      }
#  else
#    define U3_LOG_DATA_DBG(u3def_format, ...)
#  endif
#endif
