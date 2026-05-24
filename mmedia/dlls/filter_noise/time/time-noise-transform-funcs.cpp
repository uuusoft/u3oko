/**
\file       time-noise--transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-includes_int.hpp"
#include "time-noise-filter-dll.hpp"

namespace dlls::filter_noise::time
{
void
Filter::itransform ()
{
  finfo_.impl_->transform_int (id_obj_, *transinfo_, finfo_, pbuf_);

  ++finfo_.counter_frame_;

  if (finfo_.rprops_->dump_counter_frame_ <= 0)
  {
    return;
  }
  if (finfo_.counter_frame_ % finfo_.rprops_->dump_counter_frame_)
  {
    return;
  }
#if 0
  ::libs::helpers::statistic::ExpandedTimes::infos_type info;
  {
    auto             link2appl = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
    syn::TStatLogger dump (link2appl);
    dump (finfo_.expand_time_algs_);
  }
  ::libs::helpers::statistic::helpers::functors::TStatReset reset;
  reset (finfo_.expand_time_algs_);
#endif
}
}   // namespace dlls::filter_noise::time
