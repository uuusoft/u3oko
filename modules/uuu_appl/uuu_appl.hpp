#pragma once
/**
\file       uuu_appl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_appl
\brief      empty brief
*/

namespace modules { namespace uuu_appl {

extern ::libs::helpers::sys::cpu::CpuInfo         cpu_informer_;
extern ::libs::helpers::sys::ISysInfo::raw_ptr    sys_info_;
extern ::libs::link::appl::InitApplication        g_init_appl;
extern ::libs::link::appl::IApplicationProxy::ptr g_module_appl;

bool check_process ();

void up_links (const std::string& _sfullpath, int _argc, char* _argv[]);

bool work_cycle ();

}}      // namespace modules::uuu_appl
