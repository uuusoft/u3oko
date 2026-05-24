#pragma once
/**
\file       modules-appl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.05.2017
\project    u3_module_appl
*/

namespace modules::uuu_appl
{
extern ::libs::helpers::sys::cpu::CpuInfo         g_cpu_informer;
extern ::libs::helpers::sys::ISysInfo::raw_ptr    g_sys_info;
extern ::libs::link::appl::InitApplication        g_init_appl;
extern ::libs::link::appl::IApplicationProxy::ptr g_module_appl;

bool check_process ();
void up_links (const std::string&, std::int32_t, char*[]);
bool work_cycle ();
}   // namespace modules::uuu_appl
