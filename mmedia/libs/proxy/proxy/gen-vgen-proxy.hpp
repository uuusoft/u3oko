#pragma once
/**
\file       gen-vgen-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "mmedia/dnodes/sources/vgen_lib/gen-lib-const-vals.hpp"

namespace libs::proxy
{
auto get_create_source_func (const std::string&) -> ::dnodes::sources::gen_lib::bcreate_source_func_type;
auto get_free_source_func (const std::string&) -> ::dnodes::sources::gen_lib::bfree_source_func_type;
}   // namespace libs::proxy
