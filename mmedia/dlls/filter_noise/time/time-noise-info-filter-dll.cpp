/**
\file       time-noise-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    uuu_time_filter_noise
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-includes_int.hpp"
#include "time-noise-info-filter-dll.hpp"

namespace dlls::filter_noise::time
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  counter_frame_ (0),
  synced_ (false)
{
  //  по умолчанию для всех реализаций стандартное свойство.
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< ::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));

  auto temp = ::libs::iproperties::helpers::create_event< ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp > (rprops_->impl_info_);
  str2props_.insert (str2prop_type::value_type (rprops_->impl_info_->get_mid (), temp));
}


InfoFilter::~InfoFilter ()
{
}


void
InfoFilter::sync_int (bool force)
{
  if (synced_ && !force)
  {
    return;
  }

  if (impl_)
  {
    U3_LOG_DATA_DBG ("time filtration: sync request");
    impl_->sync_int ();
  }

#if 0
  {
    auto& last = diff_props_.diffs_.back ();

    last.first = rprops_->bufs_.indx_sbuf_;

    last.second.op_.enable_        = true;
    last.second.op_.bound_filling_ = rprops_->bound_;
    last.second.op_.val_filling_   = 1;
    last.second.bindx_diff_        = rprops_->bufs_.indx_dbuf_;

    diff_impl_.set_props (&diff_props_);
  }

  {
    const auto                                                           morph_op = libs::ievents::props::videos::generic::morph::str2type_op (rprops_->id_morph_op_);
    ::libs::ievents::props::videos::generic::morph::MorphOperationParams morph_param (morph_op, rprops_->size_core_morph_op_, 0, 1);
    auto&                                                                last    = mops_props_.diffs_.back ();
    auto&                                                                last_op = last.second.ops_.back ();

    last.second.bindx_diff_ = rprops_->bufs_.indx_dbuf_;

    last_op.type_          = morph_op;
    last_op.size_spot_     = rprops_->size_core_morph_op_;
    last_op.bound_filling_ = 0;
    last_op.val_filling_   = 1;

    mops_impl_.set_props (&mops_props_);
  }
#endif
  synced_ = true;
}
}   // namespace dlls::filter_noise::time
