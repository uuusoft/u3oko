/**
\file       modules-appl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.05.2016
\project    mappl
*/
#include "module-appl-includes_int.hpp"
#include "modules-appl.hpp"

namespace modules::mappl
{
syn::CpuInfo                g_cpu_informer;
syn::ISysInfo::raw_ptr      g_sys_info (nullptr);
syn::InitApplication        g_init_appl;
syn::IApplicationProxy::ptr g_module_appl;

auto
check_process () -> bool
{
  g_sys_info = ::libs::utility::sys::get_impl ();

  const syn::CpuExts min_ext = syn::CpuExts::sse2;
  if (g_cpu_informer.is_less (g_cpu_informer.get_max (), min_ext))
  {
    U3_LOG_APPL_WRN ("check_process failed: minimum SSE2 or NEON required");
    return false;
  }
  return true;
}


void
process_cmd_line (std::int32_t argc, char* argv[])
{
  U3_XLOG_TIME ("process_cmd_line::" + VTOLOG (argc));
  boost::program_options::options_description options ("allowed options");

  options.add_options () (::libs::link::consts::text::id_lib_name, boost::program_options::value< std::string > ());
  options.add_options () (::libs::link::consts::text::id_company_name, boost::program_options::value< std::string > ());
  options.add_options () (::libs::link::consts::text::id_appl_name, boost::program_options::value< std::string > ());
  // options.add_options () (::libs::link::consts::text::id_subsys_name, boost::program_options::value< std::string > ());
  options.add_options () (::libs::link::consts::text::id_service_name, boost::program_options::value< std::string > ());
  options.add_options () (::libs::link::consts::text::id_delay_ms, boost::program_options::value< std::string > ());

  boost::program_options::variables_map mapvars;
  {
#ifdef U3_OS_WIN32_DESKTOP
    auto args = boost::program_options::split_winmain (std::string (GetCommandLineA ()));
    auto pars = boost::program_options::basic_command_line_parser< char > (args).options (options).allow_unregistered ().run ();

    boost::program_options::store (pars, mapvars);
    boost::program_options::notify (mapvars);
#else
    // boost::program_options::basic_parsed_options<char> pars = boost::program_options::basic_command_line_parser<char> (argc, argv).options (options).allow_unregistered ().run ();
    // boost::program_options::store (pars, mapvars);
    // boost::program_options::notify (mapvars);
#endif
  }

  if (mapvars.count (::libs::link::consts::text::id_delay_ms) >= 1)
  {
    const auto         sdelay = mapvars.find (::libs::link::consts::text::id_delay_ms)->second.as< std::string > ();
    const std::int32_t rdelay = std::stoi (sdelay);
    const auto         delay  = ::libs::utility::utils::ret_check_bound< std::int32_t > (rdelay, 0, 60 * 1000);
    U3_XLOG_WARN ("debug delay before start" + VTOLOG (delay) + "ms")
    std::this_thread::sleep_for (std::chrono::milliseconds (delay));
  }

  const std::pair< const std::string, std::string& > cmd_vals[] = {
    { ::libs::link::consts::text::id_lib_name, g_init_appl.lib_name_ },
    { ::libs::link::consts::text::id_company_name, g_init_appl.company_name_ },
    { ::libs::link::consts::text::id_appl_name, g_init_appl.appl_name_ },
    { ::libs::link::consts::text::id_service_name, g_init_appl.service_name_ }
  };

  for (const auto& cmd_val : cmd_vals)
  {
    U3_XLOG_MARK ("process_cmd_line:: check option" + TOLOG (cmd_val.first) + TOLOG (cmd_val.second));
    if (mapvars.count (cmd_val.first) < 1)
    {
      continue;
    }

    auto        itlib = mapvars.find (cmd_val.first);
    const auto& lib   = itlib->second;

    cmd_val.second = lib.as< std::string > ();
  }
}


auto
find_default_appl_lib (const std::string& fullpath) -> std::string
{
  boost::filesystem::path bpath (fullpath);
  std::string             ret = "find_default_appl_lib-module-appl-not-found";

  // EAI-REFACT
#if (U3_BUILD_MODULES_AS_LIBS == 1)
  ret = "appl_u3oko";
#else
#  ifdef U3_OS_ANDROID
  ret = "libappl_u3oko";
#  endif

  for (auto it = boost::filesystem::directory_iterator (bpath); it != boost::filesystem::directory_iterator (); ++it)
  {
    const auto filename = it->path ().stem ().string ();
    if (std::string::npos != filename.find ("appl_"))
    {
      return filename;
    }
  }
#endif
  return ret;
}


void
up_links (const std::string& fullpath, std::int32_t argc, char* argv[])
{
  process_cmd_line (argc, argv);
  if (g_init_appl.lib_name_.empty ())
  {
    g_init_appl.lib_name_ = find_default_appl_lib (fullpath);
  }
}
}   // namespace modules::mappl
