#pragma once
/**
\file       load_funcs_atomic_value.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.02.2022
\project    u3_helpers_lib
*/

namespace libs::iproperties::xml::helpers
{
using func_enum_files_type = std::function< void (::libs::helpers::files::NodeEnumFiles&, const std::string& add_root) >;   //<

void
enum_files_function (
  ::libs::helpers::files::NodeEnumFiles& node,
  const std::string&                     add_root,
  const func_enum_files_type&            funct);

void copy_files (
  Loader&                  loader,
  const appl_paths::Paths& path_type,
  const std::string&       source_folder,
  const std::string&       dest);
}   // namespace libs::iproperties::xml::helpers
