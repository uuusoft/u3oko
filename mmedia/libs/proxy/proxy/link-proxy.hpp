#pragma once
/**
\file       link-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "mmedia/libs/link/appl/iapplication-proxy.hpp"

namespace libs::proxy::syn
{
using IApplicationProxy = ::libs::link::appl::IApplicationProxy;
}   // namespace libs::proxy::syn

namespace libs::proxy
{
auto get_create_module_func (const std::string&) -> syn::IApplicationProxy::create_func_type;
auto get_delete_module_func (const std::string&) -> syn::IApplicationProxy::delete_func_type;
}   // namespace libs::proxy
