/**
\file       idata-source-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       31.01.2022
\project    u3_gen_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "idata-source-impl.hpp"

namespace dlls::sources::gen_vgen
{
void
IDataSourceImpl::init ()
{
  const auto path     = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  auto       apppaths = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();

  ::libs::iproperties::xml::InitLoaderInfo loader_info (apppaths);
  ::libs::iproperties::xml::Loader         loader (loader_info);
  ::libs::helpers::files::NodeEnumFiles    files;

  types_.clear ();
  sources_.clear ();

  loader.get_enum (
    ::libs::iproperties::appl_paths::Paths::emulate_bins,
    files,
    std::string ("?") + libs::helpers::dlls::get_dll_suffix () + "?");

  types_.reserve (files.files_.size ());
  sources_.reserve (files.files_.size ());
  U3_LOG_DATA_DEV ("IDataSourceImpl::init" + VTOLOG (files.files_.size ()) + TOLOG (to_string (::libs::iproperties::appl_paths::Paths::emulate_bins)));

  for (const auto& ufile : files.files_)
  {
    try
    {
      const auto file = ::libs::helpers::dlls::undecorate_dll_name (ufile.name_);
      U3_LOG_DATA_DEV ("find file" + TOLOG (file));
      if ((file.length () <= 4) || (file.substr (0, 4) != "vss_"))
      {
        continue;
      }

      types_.emplace_back (file);
      sources_.emplace_back (std::vector< ::libs::imdata_events::events::DataSourceInfo > ());

      const std::string  path2file = path + "/" + ufile.name_;
      ObjSourceImplProxy rdriver;
      U3_XLOG_DBG ("prepare init driver:" + path2file);
      rdriver.init (ufile.name_);
      auto isource = rdriver.get_source_impl ();
      isource->get_sources (sources_.back ());
      U3_LOG_DATA_DEV ("IDataSourceImpl::init" + TOLOG (ufile.name_) + VTOLOG (sources_.size ()));
    }
    catch (const std::exception& e)
    {
      U3_LOG_DATA_EXCEPT ("IDataSourceImpl::init" + TOLOG (ufile.name_) + ", " + e.what ());
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
}   // namespace dlls::sources::gen_vgen
