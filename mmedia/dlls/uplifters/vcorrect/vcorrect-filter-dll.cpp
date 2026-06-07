/**
\file       vcorrect-filter-dll.cpp
\brief      Filter for correct image
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcorrect-includes_int.hpp"
#include "vcorrect-info-filter-dll.hpp"
#include "vcorrect-filter-dll.hpp"

namespace dlls::uplifters::vcorrect
{
Filter::Filter ()
{
  finfo_.soft_impl_   = std::make_shared< soft::CorrectImageImpl > ();
  finfo_.active_impl_ = finfo_.soft_impl_;
  finfo_.soft_impl_->update_correction_property (finfo_.rprops_);
}


void
Filter::load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);
  U3_ASSERT (!finfo_.active_impl_.expired ());
  finfo_.active_impl_.lock ()->update_correction_property (finfo_.rprops_);
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);

  U3_LOG_DATA_DATA ("Filter::transform_int" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (info.frame_events_)));
  if (info.frame_events_)
  {
    for (const auto& event : *info.frame_events_)
    {
      auto devent = ::libs::iproperties::helpers::cast_event< syn::InterfCorrectImageEvent > (event);
      if (devent)
      {
        U3_LOG_DATA_MARK ("recive syn::InterfCorrectImageEvent -> update properties" + VTOLOG (devent->is_active ()));
        const auto enable_hardware = devent->is_active () && finfo_.rprops_ && (::libs::ievents::SelectorImpls::software != finfo_.rprops_->hint_correct_impl_);
        finfo_.hardware_impl_      = devent->get_interface ();
        finfo_.active_impl_        = enable_hardware ? finfo_.hardware_impl_ : finfo_.soft_impl_;
        U3_ASSERT (!finfo_.active_impl_.expired ());
        auto impl = finfo_.active_impl_.lock ();
        if (impl)
        {
          impl->update_correction_property (finfo_.rprops_);
        }
      }
    }
  }

  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    U3_LOG_DATA_DATA ("skip process correction")
    return;
  }

  syn::IVideoBuf::raw_ptr h16_buf = (*pbuf_)[utils::dbufs::video::consts::offs::hue];
  syn::IVideoBuf::raw_ptr s16_buf = (*pbuf_)[utils::dbufs::video::consts::offs::sat];
  syn::IVideoBuf::raw_ptr l16_buf = (*pbuf_)[utils::dbufs::video::consts::offs::lit];

  auto impl = finfo_.active_impl_.lock ();
  if (impl)
  {
    impl->process (
      transinfo_,
      id_obj_,
      h16_buf,
      s16_buf,
      l16_buf);
  }
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::stop_int ()
{
  finfo_.active_impl_ = finfo_.soft_impl_;
  finfo_.hardware_impl_.reset ();
}


void
Filter::init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}
}   // namespace dlls::uplifters::vcorrect
