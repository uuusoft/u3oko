//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       uuu_appl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       10.05.2016
\copyright  www.uuusoft.com
\project    uuu_appl
\brief      Точка входа в исполняемый модуль ядра.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "uuu_appl.hpp"

namespace modules { namespace uuu_appl {

using ::libs::events::IEvent;

namespace bip = boost::interprocess;
namespace bpo = boost::program_options;

::libs::helpers::sys::cpu::CpuInfo         cpu_informer_;
::libs::helpers::sys::ISysInfo::raw_ptr    sys_info_ (nullptr);
::libs::link::appl::InitApplication        g_init_appl;
::libs::link::appl::IApplicationProxy::ptr g_module_appl;

bool
check_process ()
{
  sys_info_ = ::libs::helpers::sys::get_impl ();

  const ::libs::helpers::sys::cpu::TypeExtCpu _min_ext_cpu = ::libs::helpers::sys::cpu::TypeExtCpu::sse2;
  if (cpu_informer_.is_less (cpu_informer_.get_max (), _min_ext_cpu))
    {
      XULOG_WARNING ("check_process::failed::SSE2 or AVX1 or NEON requared");
      return false;
    }
  return true;
}


void
process_cmd_line (int _argc, char* _argv[])
{
  XULOG_INFO ("process_cmd_line::beg");
  bpo::options_description _desc ("Allowed options");

  _desc.add_options () (::libs::link::consts::text::id_lib_name.c_str (), bpo::value<std::string> ());
  _desc.add_options () (::libs::link::consts::text::id_company_name.c_str (), bpo::value<std::string> ());
  _desc.add_options () (::libs::link::consts::text::id_appl_name.c_str (), bpo::value<std::string> ());
  _desc.add_options () (::libs::link::consts::text::id_subsys_name.c_str (), bpo::value<std::string> ());
  XULOG_INFO ("process_cmd_line:: _argc=" << _argc << ", argv" << _argv);

  bpo::variables_map _var_map;

  {
#if defined(UUU_OS_WIN32_DESKTOP)
    std::vector<std::string>        _args = bpo::split_winmain (std::string (GetCommandLineA ()));
    bpo::basic_parsed_options<char> _pars = bpo::basic_command_line_parser<char> (_args).options (_desc).allow_unregistered ().run ();
    bpo::store (_pars, _var_map);
    bpo::notify (_var_map);
#else
    //bpo::basic_parsed_options<char> _pars = bpo::basic_command_line_parser<char> (_argc, _argv).options (_desc).allow_unregistered ().run ();
    //bpo::store (_pars, _var_map);
    //bpo::notify (_var_map);
#endif
  }

  if (_var_map.count (::libs::link::consts::text::id_lib_name) >= 1)
    {
      auto        _i_lib = _var_map.find (::libs::link::consts::text::id_lib_name);
      const auto& _v_lib = _i_lib->second;

      g_init_appl.name_lib_ = _v_lib.as<std::string> ();
      XULOG_INFO ("process_cmd_line:: name_lib=" << g_init_appl.name_lib_);
    }

  if (_var_map.count (::libs::link::consts::text::id_company_name) >= 1)
    {
      auto        _i_company = _var_map.find (::libs::link::consts::text::id_company_name);
      const auto& _v_company = _i_company->second;

      g_init_appl.name_company_ = _v_company.as<std::string> ();
      XULOG_INFO ("process_cmd_line:: name_company=" << g_init_appl.name_company_);
    }

  if (_var_map.count (::libs::link::consts::text::id_appl_name) >= 1)
    {
      auto        _i_appl = _var_map.find (::libs::link::consts::text::id_appl_name);
      const auto& _v_appl = _i_appl->second;

      g_init_appl.name_appl_ = _v_appl.as<std::string> ();
      XULOG_INFO ("process_cmd_line:: name_appl=" << g_init_appl.name_appl_);
    }

  if (_var_map.count (::libs::link::consts::text::id_subsys_name) >= 1)
    {
      auto        _i_subsys = _var_map.find (::libs::link::consts::text::id_subsys_name);
      const auto& _v_subsys = _i_subsys->second;

      g_init_appl.name_subsys_ = _v_subsys.as<std::string> ();
      XULOG_INFO ("process_cmd_line:: name_subsys=" << g_init_appl.name_subsys_);
    }

  XULOG_INFO ("process_cmd_line::end");
  return;
}


std::string
find_default_appl_lib (const std::string& _sfullpath)
{
  std::string             _ret = "appl_u3unknown";
  boost::filesystem::path _path (_sfullpath);

#if defined(UUU_OS_ANDROID)
  _path /= "lib";      // debug
#endif

  for (auto _it = boost::filesystem::directory_iterator (_path); _it != boost::filesystem::directory_iterator (); ++_it)
    {
      const std::string _filename = _it->path ().stem ().string ();
      XULOG_INFO ("check file for load main module, " << _filename);
      if (std::string::npos != _filename.find ("appl_"))
        {
          XULOG_INFO ("find main module, " << _filename);
          _ret = _filename;
          break;
        }
    }
  return _ret;
}


void
up_links (const std::string& _sfullpath, int _argc, char* _argv[])
{
  process_cmd_line (_argc, _argv);

  if (g_init_appl.name_lib_.empty ())
    {
      g_init_appl.name_lib_ = find_default_appl_lib (_sfullpath);
    }
  return;
}

}}      // namespace modules::uuu_appl
