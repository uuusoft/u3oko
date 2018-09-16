//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_appl
\brief      Базовый файл системы, для загрузки всех связанных с ней модулей.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include <regex>
#include "includes_int.hpp"
#include "uuu_appl.hpp"
#include "mmedia/libs/helpers/log/android-log-functs.hpp"

namespace bip = boost::interprocess;
namespace bpo = boost::program_options;

void
signal_stop_process (int)
{
  XULOG_INFO ("signal_stop_process, beg");
  if (::modules::uuu_appl::g_module_appl && ::modules::uuu_appl::g_module_appl->impl ())
    {
      auto _impl = ::modules::uuu_appl::g_module_appl->impl ();
      _impl->force_stop ();      // Без затей и блокировок, просто выставляем флаг.
    }
  XULOG_INFO ("signal_stop_process, end");
  return;
}


void
signal_abort_process (int _val)
{
  XULOG_INFO ("signal_abort_process, beg, " << _val);
  exit (_val);
  XULOG_INFO ("signal_abort_process, end");
  return;
}


void
prepare_process ()
{
  XULOG_INFO ("prepare_process: beg");
  ::libs::ilink::appl::base::register_events_for_module ();

  XULOG_TRACE ("prepare_process: prepare set prop demons_property");
  auto _istorage = ::libs::iproperties::helpers::get_storage ();

  _istorage->set_prop (::libs::properties::consts::keys::demons_property, std::make_shared<::libs::iproperties::vers::demon::IDemonsProperty> ());

#if defined(UUU_OS_WIN32_DESKTOP)

  SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL);
  ::libs::helpers::windows::add_process_privilage ();

#if defined(UUU_DEBUG)
  SetErrorMode (0);
  _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_CHECK_CRT_DF | _CRTDBG_LEAK_CHECK_DF);
#else
  SetErrorMode (SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
#endif

  _istorage->set_prop (::libs::properties::consts::keys::shared_os_property, std::make_shared<::libs::iproperties::vers::system::ISystemProperty> ());
  _istorage->set_prop (::libs::properties::consts::keys::specific_os_property, std::make_shared<::libs::iproperties::vers::system::SystemWin32Property> ());

#elif defined(UUU_OS_GNU_LINUX) || defined(UUU_OS_RASPBERRY)

  _istorage->set_prop (::libs::properties::consts::keys::shared_os_property, std::make_shared<::libs::iproperties::vers::system::ISystemProperty> ());
  _istorage->set_prop (::libs::properties::consts::keys::specific_os_property, std::make_shared<::libs::iproperties::vers::system::SystemWin32Property> ());

#elif defined(UUU_OS_ANDROID)
#else
#error select OS
#endif
  XULOG_INFO ("prepare_process: end");
  return;
}


void
init_process (int _argc, char* _argv[])
{
  XULOG_INFO ("init_process::modules::uuu_appl::g_appl.reset");
  const std::string             _cur_folder = ::libs::iproperties::appl_paths::get_current_folder ();
  const boost::filesystem::path _fullpath (_cur_folder);

  XULOG_INFO ("current folder: " << _cur_folder);

  ::modules::uuu_appl::up_links (_cur_folder, _argc, _argv);

  XULOG_TRACE ("prepare check process");
  CHECK_CALL (::modules::uuu_appl::check_process (), "failed, call check_process");
  XULOG_TRACE (::modules::uuu_appl::g_init_appl.name_lib_.c_str ());

  ::modules::uuu_appl::g_module_appl = std::make_shared<::libs::link::appl::IApplicationProxy> (_cur_folder.c_str (), ::modules::uuu_appl::g_init_appl.name_lib_.c_str ());

  {
    auto _impl = ::modules::uuu_appl::g_module_appl->impl ();
    _impl->ainit (::modules::uuu_appl::g_init_appl);
  }
  XULOG_INFO ("init_process::modules::uuu_appl::end");
  return;
}


void
work_process ()
{
  ::modules::uuu_appl::g_module_appl->impl ()->work ();
  return;
}


void
deinit_impl_application ()
{
  auto _impl_appl = ::modules::uuu_appl::g_module_appl->impl ();
  UASSERT (_impl_appl);
  XULOG_INFO ("deinit_process: deinit impl application");
  _impl_appl->deinit ();
  return;
}


void
deinit_properties ()
{
  const auto& _istorage = ::libs::iproperties::helpers::get_storage ();
  UASSERT (_istorage);
  XULOG_INFO ("deinit_process: reset os property");
  _istorage->reset_prop (::libs::properties::consts::keys::shared_os_property);
  //_istorage->reset_prop ( ::libs::properties::consts::keys::demons_property );
  return;
}


void
deinit_links ()
{
  ::libs::ilink::LinkCreatorProxy::raw_ptr _lproxy = ::libs::ilink::LinkCreatorProxy::instance ();
  UASSERT (_lproxy);
  XULOG_INFO ("deinit_process: close all links");
  //_lproxy->impl ()->close_all ();
  return;
}


void
deinit_process ()
{
  XULOG_INFO ("deinit_process: beg");
  deinit_impl_application ();
  deinit_properties ();
  deinit_links ();
  XULOG_INFO ("deinit_process: end");
  return;
}


void
setup_signal_catch ()
{
  std::signal (SIGINT, signal_stop_process);
  std::signal (SIGTERM, signal_stop_process);

  std::signal (SIGILL, signal_abort_process);
  std::signal (SIGFPE, signal_abort_process);
  std::signal (SIGSEGV, signal_abort_process);
  std::signal (SIGABRT, signal_abort_process);
  return;
}


extern "C" BOOST_SYMBOL_EXPORT int
main_impl (int _argc, char* _argv[])
{
#ifdef UUU_OS_ANDROID
  ::libs::helpers::log::android::init ();
  ::libs::helpers::log::android::Logger logger;
  SET_MODULE (logger, UUU_LOG_TAG);
#endif

  XULOG_INFO ("main_impl: beg");
  try
    {
      setup_signal_catch ();
      prepare_process ();
      init_process (_argc, _argv);
      work_process ();
    }
  catch (bip::interprocess_exception& _e)
    {
      XULOG_ERROR ("exception interprocess: " << boost::diagnostic_information (_e));
    }
  catch (boost::exception& _e)
    {
      XULOG_ERROR ("exception boost: " << boost::diagnostic_information (_e));
    }
  catch (std::exception& _e)
    {
      XULOG_ERROR ("exception: " << _e.what ());
    }
  catch (...)
    {
      XULOG_ERROR ("unknown exception");
    }

  deinit_process ();
  XULOG_INFO ("main_impl: end");
  return 0;
}


int
main (int _argc, char* _argv[])
{
  return main_impl (_argc, _argv);
}
