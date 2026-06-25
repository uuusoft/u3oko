#pragma once
/**
\file       gen-vgen-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
*/
#include "mmedia/dlls/sources/vgen_lib/gen-lib-const-vals.hpp"

namespace libs::proxy
{
dlls::sources::gen_lib::bcreate_source_func_type get_create_source_funct (const std::string& plib_id);
dlls::sources::gen_lib::bfree_source_func_type   get_free_source_funct (const std::string& plib_id);
}   // namespace libs::proxy
