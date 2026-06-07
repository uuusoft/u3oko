/**
\file       vcorrect-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.05.2017
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcorrect-includes_int.hpp"
#include "vcorrect-info-filter-dll.hpp"
#include "vcorrect-filter-dll.hpp"

namespace dlls::uplifters::vcorrect
{
InfoFilter::InfoFilter ()
{
  init ();
}


void
InfoFilter::init ()
{
  synced_ = false;
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoCorrectProp > (ef_props_);

  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
}


void
InfoFilter::sync_int (bool force)
{
  if (synced_ && !force)
  {
    return;
  }

  const auto use_hardware = ::libs::ievents::SelectorImpls::software != rprops_->hint_correct_impl_ && !hardware_impl_.expired ();
  active_impl_            = use_hardware ? hardware_impl_ : soft_impl_;

  syn::ICorrectImage::weak_ptr impls[] = {
    hardware_impl_,
    soft_impl_
  };

  for (auto& impl : impls)
  {
    if (auto pimpl = impl.lock ())
    {
      pimpl->update_correction_property (rprops_);
    }
  }

  synced_ = true;
}


bool
InfoFilter::load_int (const ::pugi::xml_named_node_iterator& node)
{
  synced_ = false;
  return super::load_int (node);
}
}   // namespace dlls::uplifters::vcorrect
