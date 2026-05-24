#pragma once
/**
\file       gen-lib-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_vgen_lib
*/

namespace dlls::sources::gen_lib::consts
{
extern const std::string name_get_funct;    //<
extern const std::string name_free_funct;   //<
}   // namespace dlls::sources::gen_lib::consts

namespace dlls::sources::gen_lib
{
// forward
class ISourceImpl;

using get_source_func_type     = bool (ISourceImpl** obj);
using free_source_func_type    = bool (ISourceImpl** obj);
using bfree_source_func_type   = ::boost::function< free_source_func_type >;
using bcreate_source_func_type = ::boost::function< get_source_func_type >;
}   // namespace dlls::sources::gen_lib
