/**
\file       iloader-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.02.2022
\project    u3_iproperties_lib
*/
#include "libs-iproperties-xml-includes_int.hpp"
#include "loader.hpp"

namespace libs::iproperties::xml
{
auto
ILoaderImpl::is_exist_file (
  const std::string&       file_name,
  const appl_paths::Paths& storage_type) const -> bool
{
  return is_exist_file_int (file_name, storage_type);
}


auto
ILoaderImpl::is_exist_folder (
  const std::string&       file_name,
  const appl_paths::Paths& storage_type) const -> bool
{
  return is_exist_folder_int (file_name, storage_type);
}


auto
ILoaderImpl::get (
  const std::string&                    file_name,
  const appl_paths::Paths&              storage_type,
  ::libs::utility::mem::IBlockMem::ptr& ret) -> bool
{
  return get_int (file_name, storage_type, ret);
}


void
ILoaderImpl::get_enum (
  const appl_paths::Paths&               storage_type,
  ::libs::utility::files::NodeEnumFiles& fenum,
  const std::string&                     mask)
{
  get_enum_int (storage_type, fenum, mask);
}
}   // namespace libs::iproperties::xml
