#pragma once
/**
\file       call-trace.hpp
\author     Erashov Anton erashov2026@proton.me
\date       12.08.2026
*/

namespace libs::utility::log
{
class CallTrace final
{
  public:
  U3_ADD_DELETE_MOVE_COPY (CallTrace)

  explicit CallTrace (
    const std::string_view      info      = "",
    const std::thread::id&      thread_id = std::this_thread::get_id (),
    const std::source_location& place     = std::source_location::current ()) :

    place_ (std::move (place)),
    thread_id_ (thread_id),
    info_ (info)
  {
    U3_XLOG_MARK ("--->{}:{}", clear_func_name (place_.function_name ()), info_);
    ++call_deep_;
  }

  ~CallTrace ()
  {
    --call_deep_;
    U3_XLOG_MARK ("<---{}:{}", clear_func_name (place_.function_name ()), info_);
  }

  private:
  inline static std::array< std::string, 16 > deep2off = {
    "",
    "\t",
    "\t\t",
    "\t\t\t",
    "\t\t\t\t",
    "\t\t\t\t\t",
    "\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t\t\t\t\t",
    "\t\t\t\t\t\t\t\t\t\t\t\t\t\t",
    "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t"
  };

  std::int32_t
  get_deep (std::int32_t deep) const
  {
    return deep2off.size () > deep && deep > 0 ? deep : deep2off.size () - 1;
  }

  const std::source_location              place_;             //<
  const std::thread::id                   thread_id_;         //<
  const std::string                       info_;              //<
  inline static thread_local std::int32_t call_deep_ { 0 };   //<
};
}   // namespace libs::utility::log


#ifdef U3_CNTRL_DISABLED_CONSOLE_LOG
#  ifndef U3_CALL_TRACE_DBG
#    define U3_CALL_TRACE_DBG
#  endif
#  ifndef U3_CALL_TRACE_INFO_DBG
#    define U3_CALL_TRACE_INFO_DBG
#  endif
#  ifndef U3_CALL_TRACE
#    define U3_CALL_TRACE
#  endif
#  ifndef U3_CALL_TRACE_INFO
#    define U3_CALL_TRACE_INFO
#  endif
#else

#  ifndef U3_CALL_TRACE_DBG
#    ifdef U3_DBG_LOG_LEVEL_ENABLE
#      define U3_CALL_TRACE_DBG ::libs::utility::log::CallTrace trace;
#    else
#      define U3_CALL_TRACE_DBG
#    endif
#  endif

#  ifndef U3_CALL_TRACE_INFO_DBG
#    ifdef U3_DBG_LOG_LEVEL_ENABLE
#      define U3_CALL_TRACE_INFO_DBG(u3def_param, ...) ::libs::utility::log::CallTrace trace (std::format (u3def_param __VA_OPT__ (, ) __VA_ARGS__));
#    else
#      define U3_CALL_TRACE_INFO_DBG
#    endif
#  endif

#  ifndef U3_CALL_TRACE
#    define U3_CALL_TRACE ::libs::utility::log::CallTrace trace;
#  endif

#  ifndef U3_CALL_TRACE_INFO
#    define U3_CALL_TRACE_INFO(u3def_param, ...) ::libs::utility::log::CallTrace trace (std::format (u3def_param __VA_OPT__ (, ) __VA_ARGS__));
#  endif
#endif
