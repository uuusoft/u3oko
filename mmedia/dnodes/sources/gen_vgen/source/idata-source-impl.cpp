/**
\file       idata-source-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       31.01.2022
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "idata-source-impl.hpp"

namespace dnodes::sources::gen_vgen
{
void
IDataSourceImpl::init ()
{
  const auto path     = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  auto*      osprops  = ::libs::iproperties::helpers::get_shared_prop_os ();
  auto       apppaths = osprops->get_paths_lockfree ();

  ::libs::iproperties::xml::InitLoaderInfo loader_info (apppaths);
  ::libs::iproperties::xml::Loader         loader (loader_info);
  ::libs::utility::files::NodeEnumFiles    files;

  types_.clear ();
  sources_.clear ();

  loader.get_enum (
    ::libs::iproperties::appl_paths::Paths::emulate_bins,
    files,
    std::string ("?") + libs::utility::dlls::get_dll_suffix () + "?");

  types_.reserve (files.files_.size ());
  sources_.reserve (files.files_.size ());
  U3_LOG_DATA_MARK ("find dll sources:{}", files.files_.size ());
  for (const auto& ufile : files.files_)
  {
    try
    {
      const auto file = ::libs::utility::dlls::undecorate_dll_name (ufile.name_);
      U3_LOG_DATA_MARK ("check data source dll file {} {}", file, file.length ());
      if ((file.length () <= 4) || (!file.starts_with ("vss_")))
      {
        continue;
      }

      types_.emplace_back (file);
      sources_.emplace_back ();   //< reserved

      const std::string  path2file = path + "/" + ufile.name_;
      ObjSourceImplProxy rdriver { ufile.name_ };
      rdriver.get_source_impl ()->get_sources (sources_.back ());
      U3_LOG_DATA_MARK ("add source from dll {} {}", ufile.name_, sources_.size ());
    }
    catch (const std::exception& excpt)
    {
      U3_LOG_DATA_EXCEPT ("name:{} what:{}", ufile.name_, excpt.what ());
    }
  }
}


void
IDataSourceImpl::get_types_int (syn::ListDevicesDataEvent::src_names_type& types)
{
  types = types_;
}


void
IDataSourceImpl::get_sources_int (
  const std::string&                         ptype,
  syn::ListDevicesDataEvent::src_infos_type& sources)
{
  std::uint32_t i = 0;
  for (const auto& type : types_)
  {
    if (type == ptype)
    {
      sources = sources_[i];
      return;
    }
    ++i;
  }
}
}   // namespace dnodes::sources::gen_vgen
