/**
\file       gen-vgen-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::sources::gen_vgen
{
::libs::helpers::dlls::FreezerDlls Filter::frozen_dlls_;

Filter::Filter ()
{
  events2funcs_[syn::BufsEvent::gen_get_mid ()] =
    [this] (syn::CallInterfInfo& info) -> void {
    auto devent = ::libs::iproperties::helpers::cast_event< syn::BufsEvent > (info.event_);
    fill_buf (&finfo_, devent);
  };

  events2funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::CallInterfInfo& info) -> void {
    auto event = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (info.event_);
    if (event->is_start ())
    {
      update_source_driver (&finfo_);
    }
    else
    {
      if (auto source_impl = finfo_.proxy2hardware_.get_source_impl ())
      {
        source_impl->stop ();
      }
    }
  };

  events2funcs_[syn::ListDevicesDataEvent::gen_get_mid ()] =
    [this] (syn::CallInterfInfo& info) -> void {
    auto                                      event = ::libs::iproperties::helpers::cast_event< syn::ListDevicesDataEvent > (info.event_);
    syn::ListDevicesDataEvent::src_names_type types;

    idata_source_impl_.get_types (types);
    U3_LOG_DATA_DEV ("before clear" + VTOLOG (types.size ()));
    // Чистим от расширений, чтобы передавать далее кроссплатформенный вид
    for (auto& type : types)
    {
      type = type.substr (0, type.find (::libs::helpers::dlls::get_dll_suffix ()));
    }

    U3_LOG_DATA_DEV ("after clear" + VTOLOG (types.size ()));
    event->set_source_dll_names (std::move (types));

    auto source_dll_names = event->get_source_dll_names ();

    std::size_t indx = 0;
    for (const auto& source_dll_name : source_dll_names)
    {
      U3_LOG_DATA_DEV (VTOLOG (indx) + TOLOG (source_dll_name));
      syn::ListDevicesDataEvent::src_infos_type sources;

      idata_source_impl_.get_sources (source_dll_name, sources);
      event->set_devices_for_dll (indx, std::move (sources));
      ++indx;
    }
  };
}
}   // namespace dlls::sources::gen_vgen
