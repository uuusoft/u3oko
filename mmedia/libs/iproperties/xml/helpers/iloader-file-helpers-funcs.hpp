#pragma once
/**
\file       iloader-file-helpers-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.02.2022
*/

namespace libs::iproperties::xml::helpers
{
using func_enum_files_type = std::function< void (syn::NodeEnumFiles&, const std::string& add_root) >;   //<

void
enum_files_function (
  syn::NodeEnumFiles&         node,
  const std::string&          add_root,
  const func_enum_files_type& funct);

void copy_files (
  Loader&                  loader,
  const appl_paths::Paths& path_type,
  const std::string&       source_folder,
  const std::string&       dest);
}   // namespace libs::iproperties::xml::helpers
