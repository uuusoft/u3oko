#pragma once
/**
\file       iproperties-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::proxy::syn
{
using FileNode = ::libs::utility::files::FileNode;
}

namespace libs::proxy
{
auto get_list_dlls_as_libs () -> std::vector< syn::FileNode >;
}   // namespace libs::proxy
