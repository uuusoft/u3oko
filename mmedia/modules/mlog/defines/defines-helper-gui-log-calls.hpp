#pragma once
/**
\file       defines-helper-gui-log-calls.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.06.2022
\project    mlog
*/

#ifndef U3_LOG_GUI_DEV
#  define U3_LOG_GUI_DEV(u3def_info)                                                                                                                \
    {                                                                                                                                               \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::develop }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_EXCEPT
#  define U3_LOG_GUI_EXCEPT(u3def_info)                                                                                                               \
    {                                                                                                                                                 \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::exception }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_ERROR
#  define U3_LOG_GUI_ERROR(u3def_info)                                                                                                            \
    {                                                                                                                                             \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::error }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_WRN
#  define U3_LOG_GUI_WRN(u3def_info)                                                                                                                \
    {                                                                                                                                               \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::warning }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_MARK
#  define U3_LOG_GUI_MARK(u3def_info)                                                                                                            \
    {                                                                                                                                            \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::mark }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_INFO
#  define U3_LOG_GUI_INFO(u3def_info)                                                                                                            \
    {                                                                                                                                            \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::info }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_TIMING
#  define U3_LOG_GUI_TIMING(u3def_info)                                                                                                            \
    {                                                                                                                                              \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::timing }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_DATA
#  define U3_LOG_GUI_DATA(u3def_info)                                                                                                            \
    {                                                                                                                                            \
      modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::data }(u3def_info); \
    }
#endif

#ifndef U3_LOG_GUI_DBG
#  ifdef U3_USE_DEB_LOG_LEVEL
#    define U3_LOG_GUI_DBG(u3def_info)                                                                                                              \
      {                                                                                                                                             \
        modules::mlog::ToLog { libs::properties::vers::links::mids::gui2appl, ::libs::ievents::props::modules::log::LogLevels::debug }(u3def_info); \
      }
#  else
#    define U3_LOG_GUI_DBG(u3def_info)
#  endif
#endif
