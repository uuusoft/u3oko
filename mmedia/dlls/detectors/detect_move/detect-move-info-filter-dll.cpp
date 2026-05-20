/**
\file       detect-move-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_detect_move
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "detect-move-includes_int.hpp"
#include "detect-move-info-filter-dll.hpp"
#include "detect-move-filter-dll.hpp"

namespace dlls::detectors::detect_move
{
InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  synced_ (false)
{
  init ();
}


InfoFilter::~InfoFilter ()
{
}


void
InfoFilter::init ()
{
  rprops_ = ::libs::iproperties::helpers::create_event_in_list< syn::VideoDetectProp > (ef_props_);
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));

  {
    syn::InfoBuffVideoDiffProp detect_prop;

    detect_prop.op_.enable_        = true;
    detect_prop.op_.bound_filling_ = rprops_->bound_;
    detect_prop.op_.val_filling_   = ::dlls::detectors::detect_move::consts::val_filling;
    detect_prop.bindx_diff_        = rprops_->bufs_.indx_dbuf_;

    diff_props_.diffs_.clear ();
    diff_props_.diffs_.push_back ({ rprops_->bufs_.indx_sbuf_, detect_prop });
    diff_impl_.init ();
    diff_impl_.set_props (&diff_props_);
  }

  {
    auto morph_op = libs::ievents::props::videos::generic::morph::str2type_morph_op (rprops_->id_morph_op_);

    syn::MorphOperationParams morph_param (
      morph_op,
      rprops_->size_core_morph_op_,
      0,
      ::dlls::detectors::detect_move::consts::val_filling);

    syn::MorphBuffInfo morph_info (
      rprops_->bufs_.indx_dbuf_,
      rprops_->bufs_.indx_dbuf_,
      std::vector< syn::MorphOperationParams > (1, morph_param));

    mops_props_.diffs_.clear ();
    mops_props_.diffs_.push_back (morph_info);
    mops_impl_.init ();
    mops_impl_.set_props (&mops_props_);
  }
}


void
InfoFilter::sync_int (bool force)
{
  if (synced_ && !force)
  {
    return;
  }

  U3_LOG_DATA_DBG ("sync_int:update diff properties");
  {
    auto& last = diff_props_.diffs_.back ();

    last.first = rprops_->bufs_.indx_sbuf_;

    last.second.op_.enable_        = true;
    last.second.op_.bound_filling_ = rprops_->bound_;
    last.second.op_.val_filling_   = ::dlls::detectors::detect_move::consts::val_filling;
    last.second.bindx_diff_        = rprops_->bufs_.indx_dbuf_;

    diff_impl_.set_props (&diff_props_);
  }

  {
    const auto                morph_op = libs::ievents::props::videos::generic::morph::str2type_morph_op (rprops_->id_morph_op_);
    syn::MorphOperationParams morph_param (morph_op, rprops_->size_core_morph_op_, 0, 1);
    auto&                     last    = mops_props_.diffs_.back ();
    auto&                     last_op = last.morph_operations_.back ();

    last.sindx_diff_ = rprops_->bufs_.indx_dbuf_;
    last.bindx_diff_ = rprops_->bufs_.indx_dbuf_;

    last_op.morph_type_    = morph_op;
    last_op.size_spot_     = rprops_->size_core_morph_op_;
    last_op.bound_filling_ = 0;
    last_op.val_filling_   = ::dlls::detectors::detect_move::consts::val_filling;

    mops_impl_.set_props (&mops_props_);
  }

  synced_ = true;
}
}   // namespace dlls::detectors::detect_move
