/**
\file       modules-appl-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mappl
\brief      Базовый файл системы, для загрузки всех связанных с ней модулей
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"

#ifdef U3_OS_WIN32_DESKTOP
// EAI-REFACT
#  include <shellscalingapi.h>
#endif

#include <regex>
#include "module-appl-includes_int.hpp"
#include "modules-appl.hpp"

void
signal_stop_process (int signal)
{
  static std::atomic< std::uint32_t > stop_counter = 0;
  U3_XLOG_DBG ("signal_stop_process::---->" + VTOLOG (signal) + VTOLOG (stop_counter));
  if (::modules::mappl::g_module_appl && ::modules::mappl::g_module_appl->impl () && 0 == stop_counter)
  {
    U3_XLOG_MARK ("stop process::---->" + VTOLOG (signal));
    ::modules::mappl::g_module_appl->impl ()->appl_force_stop ();   // Без затей и блокировок, просто выставляем флаг.
  }
  if (stop_counter > 32)
  {
    std::abort ();   // debug
  }
  ++stop_counter;
}


void
signal_abort_process (int signal)
{
  static std::atomic< std::uint32_t > abort_counter = 0;
  if (0 == abort_counter % 1024)
  {
    U3_XLOG_WARN ("signal_abort_process" + VTOLOG (signal) + VTOLOG (abort_counter));
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    std::abort ();   // debug
#else
    std::exit (signal);
#endif
  }
  ++abort_counter;
}


void
prepare_process ()
{
  U3_XLOG_DBG ("prepare_process::---->");
  ::libs::ilink::appl::base::register_events_for_module ();
  auto istorage = ::libs::iproperties::helpers::get_storage ();

  istorage->set_prop (::libs::properties::consts::keys::demons_property, std::make_shared< ::modules::mappl::syn::IDemonsProperty > ());

  ::libs::utility::thread::set_thread_priority (
    std::this_thread::get_id (),
    ::libs::utility::thread::Priorities::time_critical);

#ifdef U3_OS_WIN32_DESKTOP
  SetProcessDpiAwareness (PROCESS_SYSTEM_DPI_AWARE);   // windows 8.1 or above
  ::libs::utility::platforms::win32::add_process_privilage ();

#  if defined(U3_CNTRL_DEBUG)
  SetErrorMode (0);
  // Флаг _CRTDBG_CHECK_ALWAYS_DF резко замедляет выполнение кода, возможно его стоит включать в исключительных случаях
  _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF /*| _CRTDBG_CHECK_ALWAYS_DF*/ | _CRTDBG_CHECK_CRT_DF | _CRTDBG_LEAK_CHECK_DF);
#  else
  SetErrorMode (SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);
#  endif
#endif

#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_MACX_DESKTOP) || defined(U3_OS_ORANGE_PI)
  U3_XLOG_DBG ("update ::libs::properties::consts::keys::shared_os_property");
  istorage->set_prop (::libs::properties::consts::keys::shared_os_property, std::make_shared< ::modules::mappl::syn::ISystemProperty > ());
  istorage->set_prop (::libs::properties::consts::keys::specific_os_property, std::make_shared< ::libs::iproperties::vers::system::SystemWin32Property > ());
#elif defined(U3_OS_ANDROID)
#else
#  error select OS
#endif
  U3_XLOG_DBG ("prepare_process::<----");
}


void
init_process (int argc, char* argv[])
{
  const std::string curfolder = ::libs::iproperties::appl_paths::get_current_folder ();
  U3_XLOG_TIME ("init_process::---->" + VTOLOG (argc) + TOLOG (curfolder));
  ::modules::mappl::up_links (curfolder, argc, argv);
  U3_XLOG_TIME ("init_process:: up links" + VTOLOG (argc) + TOLOG (curfolder));
  U3_CHECK (::modules::mappl::check_process (), "call check_process");
  U3_XLOG_TIME ("init_process::" + TOLOG (curfolder) + TOLOG (::modules::mappl::g_init_appl.lib_name_))
  ::modules::mappl::g_module_appl = std::make_shared< ::libs::link::appl::IApplicationProxy > (curfolder, ::modules::mappl::g_init_appl.lib_name_);
  ::modules::mappl::g_module_appl->impl ()->appl_init (::modules::mappl::g_init_appl);
}


void
work_process ()
{
  U3_XLOG_TIME ("work_process::---->");
  ::modules::mappl::g_module_appl->impl ()->appl_work ();
}


void
deinit_impl_application ()
{
  U3_XLOG_MARK ("deinit_impl_application::---->");
  auto applimpl = ::modules::mappl::g_module_appl->impl ();
  U3_ASSERT (applimpl);
  applimpl->appl_deinit ();
}


void
deinit_properties ()
{
  U3_XLOG_MARK ("deinit_properties::---->");
  const auto& istorage = ::libs::iproperties::helpers::get_storage ();
  U3_ASSERT (istorage);
  istorage->reset_prop (::libs::properties::consts::keys::shared_os_property);
  // istorage->reset_prop ( ::libs::properties::consts::keys::demons_property );
  U3_XLOG_DBG ("deinit_properties::<----");
}


void
deinit_links ()
{
  U3_XLOG_MARK ("deinit_links::---->");
  ::libs::ilink::LinkCreatorProxy::raw_ptr lproxy = ::libs::ilink::LinkCreatorProxy::instance ();
  U3_ASSERT (lproxy);
  // lproxy->impl ()->close_all ();
}


void
deinit_process ()
{
  U3_XLOG_MARK ("deinit_process::---->");
  deinit_impl_application ();
  deinit_properties ();
  deinit_links ();
}


void
setup_signals_catch ()
{
  U3_XLOG_MARK ("START setup_signals_catch");
  std::signal (SIGINT, signal_stop_process);
  std::signal (SIGTERM, signal_stop_process);
  std::signal (SIGILL, signal_abort_process);
  std::signal (SIGFPE, signal_abort_process);
  std::signal (SIGSEGV, signal_abort_process);
  std::signal (SIGABRT, signal_abort_process);
}


extern "C" BOOST_SYMBOL_EXPORT auto
main_impl (int argc, char* argv[]) -> int
{
  U3_XLOG_MARK ("main_impl::---->");
  try
  {
    setup_signals_catch ();
    prepare_process ();
    init_process (argc, argv);
    work_process ();
  }
  catch (boost::interprocess::interprocess_exception& excpt)
  {
    U3_XLOG_ERROR ("exception interprocess: " + std::string (boost::diagnostic_information (excpt)));
  }
  catch (boost::exception& excpt)
  {
    U3_XLOG_ERROR ("exception boost: " + std::string (boost::diagnostic_information (excpt)));
  }
  catch (std::exception& excpt)
  {
    U3_XLOG_ERROR ("exception: " + std::string (excpt.what ()));
  }
  catch (...)
  {
    U3_XLOG_ERROR ("unknown exception");
  }

  deinit_process ();
  U3_XLOG_MARK ("main_impl::<----");
  return 0;
}


auto
main (int argc, char* argv[]) -> int
{
  return main_impl (argc, argv);
}
