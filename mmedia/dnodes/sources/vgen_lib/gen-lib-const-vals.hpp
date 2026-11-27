#pragma once
/**
\file       gen-lib-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace dnodes::sources::gen_lib::consts
{
inline constexpr std::string_view name_get_func { "get_source" };
inline constexpr std::string_view name_free_func { "free_source" };
}   // namespace dnodes::sources::gen_lib::consts

namespace dnodes::sources::gen_lib
{
// forward
class ISourceImpl;

using get_source_func_type     = bool (ISourceImpl** obj);
using free_source_func_type    = bool (ISourceImpl** obj);
using bfree_source_func_type   = std::function< free_source_func_type >;
using bcreate_source_func_type = std::function< get_source_func_type >;
}   // namespace dnodes::sources::gen_lib
