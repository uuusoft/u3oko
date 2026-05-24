#pragma once
/**
\file       link-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_proxy_libs
*/
#include "mmedia/libs/link/appl/iapplication-proxy.hpp"

namespace libs::proxy
{
::libs::link::appl::IApplicationProxy::create_func_type get_create_module_funct (const std::string& plib_id);
::libs::link::appl::IApplicationProxy::delete_func_type get_delete_module_funct (const std::string& plib_id);
}   // namespace libs::proxy
