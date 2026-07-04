/**
\file       morph-operator.cpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
\project    u3_vgen_mops_lib
*/
#include "vgen-mops-lib-includes_int.hpp"
#include "morph-operator.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_mops::lib::helpers
{
void
MorphOperator::init ()
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  conv_mod_3x3_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod3x3Alg::val_key));
  conv_mod_5x5_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod5x5Alg::val_key));
  conv_mod_7x7_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod7x7Alg::val_key));
  conv_mod_9x9_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod9x9Alg::val_key));
  conv_mod_11x11_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CConvMod11x11Alg::val_key));
}


void
MorphOperator::applay_operation2buf (
  const syn::NodeID&                id_node,
  const syn::MorphOperationParams&  op,
  ::libs::bufs::Bufs*               pbuf,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  pthreads_ = ::libs::iproperties::helpers::get_shared_prop_os ()->get_mcalls_lockfree ();

  switch (op.morph_type_)
  {
  case syn::MorphOps::empty:
    break;
  case syn::MorphOps::binary:
    break;
  case syn::MorphOps::dilation:
    dilation_buf (id_node, op, pbuf, pdst);
    break;
  case syn::MorphOps::erosion:
    erosion_buf (id_node, op, pbuf, pdst);
    break;
  default:
    U3_LOG_DATA_ERROR ("unknown type MorphOps" + VTOLOG (U3_CAST_UINT32_FORCE (op.morph_type_)));
    break;
  }
}


void
MorphOperator::set_transform_info (syn::TransformInfo* tranform_info)
{
  transinfo_ = tranform_info;
}


auto
get_mkoeff_for_erosion_operation (const std::int16_t size_spot) -> short
{
  std::int16_t ret = 1;

  if (size_spot <= 3)
  {
    std::int16_t       mval      = syn::c3x3::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c3x3::cores::values_core_type > (syn::c3x3::cores::spot1, summ_spot);
  }

  if (size_spot <= 5)
  {
    std::int16_t       mval      = syn::c5x5::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c5x5::cores::values_core_type > (syn::c5x5::cores::spot1, summ_spot);
  }

  if (size_spot <= 7)
  {
    std::int16_t       mval      = syn::c7x7::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c7x7::cores::values_core_type > (syn::c7x7::cores::spot1, summ_spot);
  }

  if (size_spot <= 9)
  {
    std::int16_t       mval      = syn::c9x9::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c9x9::cores::values_core_type > (syn::c9x9::cores::spot1, summ_spot);
  }

  std::int16_t       mval      = syn::c11x11::cores::spot1.center_val ();
  const std::int32_t summ_spot = mval * size_spot * size_spot + 1;
  return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c11x11::cores::values_core_type > (syn::c11x11::cores::spot1, summ_spot);
}


void
MorphOperator::fill_koeffs_for_erosion_operation (
  const std::int16_t                 size_spot,
  ::libs::optim::io::MCallInfo&      cinfo,
  ::libs::optim::mcalls::MTFuncInfo& tfunc)
{
  std::int16_t mull_koeff = get_mkoeff_for_erosion_operation (size_spot);

  if (size_spot <= 1)
  {
    tfunc.pfunc_ = &conv_mod_3x3_;
    cinfo.params_.evals_.emplace_back (&syn::c3x3::cores::spot1);
  }
  else if (size_spot <= 3)
  {
    tfunc.pfunc_ = &conv_mod_5x5_;
    cinfo.params_.evals_.emplace_back (&syn::c5x5::cores::spot1);
  }
  else if (size_spot <= 5)
  {
    tfunc.pfunc_ = &conv_mod_7x7_;
    cinfo.params_.evals_.emplace_back (&syn::c7x7::cores::spot1);
  }
  else if (size_spot <= 7)
  {
    tfunc.pfunc_ = &conv_mod_9x9_;
    cinfo.params_.evals_.emplace_back (&syn::c9x9::cores::spot1);
  }
  else
  {
    tfunc.pfunc_ = &conv_mod_11x11_;
    cinfo.params_.evals_.emplace_back (&syn::c11x11::cores::spot1);
  }

  cinfo.params_.evals_.emplace_back (mull_koeff);
}


void
MorphOperator::erosion_buf (
  const syn::NodeID&                id_node,
  const syn::MorphOperationParams&  op,
  ::libs::bufs::Bufs*               pbuf,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  auto tbuf = (*pbuf)[utils::dbufs::video::consts::offs::temp1];

  tbuf->clone (pdst, 100.0F);

  utils::dbufs::video::helpers::fill_edges (tbuf);

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  U3_ASSERT (tbuf->check (
    [] (std::size_t x, std::size_t y, std::int16_t val) {
      if (val > 1)
      {
        U3_LOG_DATA_WRN ("check tbuf" + VTOLOG (x) + VTOLOG (y) + VTOLOG (val));
        return false;
      }
      return true;
    }));
#endif

  U3_ASSERT (utils::dbufs::video::helpers::buf_dimension_equal (*tbuf, *pdst));

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.emplace_back (tbuf, "tbuf dlls::gens::vgen_mops::lib::helpers");
  cinfo.dsts_.emplace_back (pdst, "dst dlls::gens::vgen_mops::lib::helpers");

  ::libs::optim::mcalls::MTFuncInfo tfunc;

  fill_koeffs_for_erosion_operation (op.size_spot_, cinfo, tfunc);

  pthreads_->mthreads_call (
    id_node,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}


auto
get_mkoeff_for_dilation_operation (const std::int16_t size_spot) -> short
{
  if (size_spot <= 1)
  {
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c3x3::cores::values_core_type > (syn::c3x3::cores::all_1, 1);
  }

  if (size_spot <= 3)
  {
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c5x5::cores::values_core_type > (syn::c5x5::cores::all_1, 1);
  }

  if (size_spot <= 5)
  {
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c7x7::cores::values_core_type > (syn::c7x7::cores::all_1, 1);
  }

  if (size_spot <= 7)
  {
    return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c9x9::cores::values_core_type > (syn::c9x9::cores::all_1, 1);
  }

  return ::libs::optim::s16bit::conv::get_mkoeff_core< syn::c11x11::cores::values_core_type > (syn::c11x11::cores::all_1, 1);
}


void
MorphOperator::fill_koeffs_for_dilation_operation (
  const std::int16_t                 size_spot,
  ::libs::optim::io::MCallInfo&      cinfo,
  ::libs::optim::mcalls::MTFuncInfo& tfunc)
{
  std::int16_t mull_koeff = get_mkoeff_for_dilation_operation (size_spot);

  if (size_spot <= 1)
  {
    tfunc.pfunc_ = &conv_mod_3x3_;
    cinfo.params_.evals_.emplace_back (&syn::c3x3::cores::all_1);
  }
  else if (size_spot <= 3)
  {
    tfunc.pfunc_ = &conv_mod_5x5_;
    cinfo.params_.evals_.emplace_back (&syn::c5x5::cores::all_1);
  }
  else if (size_spot <= 5)
  {
    tfunc.pfunc_ = &conv_mod_7x7_;
    cinfo.params_.evals_.emplace_back (&syn::c7x7::cores::all_1);
  }
  else if (size_spot <= 7)
  {
    tfunc.pfunc_ = &conv_mod_9x9_;
    cinfo.params_.evals_.emplace_back (&syn::c9x9::cores::all_1);
  }
  else
  {
    tfunc.pfunc_ = &conv_mod_11x11_;
    cinfo.params_.evals_.emplace_back (&syn::c11x11::cores::all_1);
  }

  cinfo.params_.evals_.emplace_back (mull_koeff);
}


void
MorphOperator::dilation_buf (
  const syn::NodeID&                id_node,
  const syn::MorphOperationParams&  op,
  ::libs::bufs::Bufs*               pbuf,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  auto tbuf = (*pbuf)[utils::dbufs::video::consts::offs::temp1];

  tbuf->clone (pdst, 100.0F);

  utils::dbufs::video::helpers::fill_edges (tbuf);
  U3_ASSERT (utils::dbufs::video::helpers::buf_dimension_equal (*tbuf, *pdst));

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.emplace_back (tbuf, "tbuf dlls::gens::vgen_mops::lib::helpers");
  cinfo.dsts_.emplace_back (pdst, "pdst dlls::gens::vgen_mops::lib::helpers");

  ::libs::optim::mcalls::MTFuncInfo tfunc;

  fill_koeffs_for_dilation_operation (op.size_spot_, cinfo, tfunc);

  pthreads_->mthreads_call (
    id_node,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_mops::lib::helpers
