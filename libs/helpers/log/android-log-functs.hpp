#pragma once
/**
\file       android-log-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       07.08.2018
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      ��������� ���� ��� ��������� ����������� ����� boost::log � �� Android.
*/
#ifdef UUU_OS_ANDROID
#include <boost/log/attributes.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/expressions/keyword.hpp>
#endif

namespace libs { namespace helpers { namespace log { namespace android {

#ifdef UUU_OS_ANDROID

namespace logging = boost::log;
namespace sinks   = boost::log::sinks;
namespace expr    = boost::log::expressions;

BOOST_LOG_ATTRIBUTE_KEYWORD (severity, "Severity", android_LogPriority)
BOOST_LOG_ATTRIBUTE_KEYWORD (module, "Module", std::string)
/**
\brief
*/
struct android_sink_backend : public sinks::basic_sink_backend<logging::sinks::concurrent_feeding>
{
  void
  consume (const logging::record_view& rec)
  {
    auto                _psev      = rec[severity];
    auto                _pmsg      = rec[expr::smessage];
    auto                _pmodule   = rec[module];
    android_LogPriority log_sev    = _psev ? _psev.get () : android_LogPriority::ANDROID_LOG_INFO;
    const char*         log_msg    = _pmsg ? _pmsg.get ().c_str () : "uuu_failed_get_msg";
    const std::string&  log_module = _pmodule ? _pmodule.get () : std::string (UUU_LOG_TAG);

    __android_log_write (log_sev, log_module.c_str (), log_msg);
    return;
  }
};

typedef boost::log::sources::severity_logger<android_LogPriority> Logger;

inline void
init ()
{
  logging::add_common_attributes ();
  typedef sinks::synchronous_sink<android_sink_backend> android_sink;
  boost::shared_ptr<android_sink>                       sink = boost::make_shared<android_sink> ();
  //sink->set_filter(severity >= android_LogPriority::ANDROID_LOG_INFO);
  logging::core::get ()->add_sink (sink);
}


inline void
deinit ()
{
  logging::core::get ()->remove_all_sinks ();
  return;
}

#endif

}}}}      // namespace libs::helpers::log::android

#define SET_MODULE(logger, log_module)      //logger.add_attribute (::libs::helpers::log::android::module.get_name (), boost::log::attributes::constant<std::string> (log_module));
