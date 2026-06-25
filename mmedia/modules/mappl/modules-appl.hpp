#pragma once
/**
\file       modules-appl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    mappl
*/

namespace modules::mappl
{
extern syn::CpuInfo                g_cpu_informer;
extern syn::ISysInfo::raw_ptr      g_sys_info;
extern syn::InitApplication        g_init_appl;
extern syn::IApplicationProxy::ptr g_module_appl;

bool check_process ();
void up_links (const std::string&, std::int32_t, char*[]);
bool work_cycle ();
}   // namespace modules::mappl
