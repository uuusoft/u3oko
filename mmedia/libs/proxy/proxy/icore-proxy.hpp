#pragma once
/**
\file       icore-proxy.hpp
\date       15.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    uuu_proxy
*/
#include "mmedia/libs/icore/impl/var1/obj/dll/create_impl_func_type.hpp"   // REFACT

namespace libs::proxy
{
::boost::function< libs::icore::impl::var1::obj::dll::create_impl_func_type > get_create_data_path_module_funct (const std::string& plib_id);
}   // namespace libs::proxy
