/**
\file       morph-operator-erosion.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       16.07.2018
\project    u3_vgen_mops_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-mops-lib-includes_int.hpp"
#include "morph-operator.hpp"

namespace dlls::gens::vgen_mops::lib::helpers
{
short
get_mkoeff_for_erosion_operation (const std::int16_t size_spot)
{
  std::int16_t ret = 1;

  if (size_spot <= 3)
  {
    std::int16_t       mval      = ::libs::optim::s16bit::conv::base::c3x3::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;

    ret = ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type > (::libs::optim::s16bit::conv::base::c3x3::cores::spot1, summ_spot);
    return ret;
  }

  if (size_spot <= 5)
  {
    std::int16_t       mval      = ::libs::optim::s16bit::conv::base::c5x5::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;

    ret = ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c5x5::cores::TCore > (
      ::libs::optim::s16bit::conv::base::c5x5::cores::spot1, summ_spot);
    return ret;
  }

  if (size_spot <= 7)
  {
    std::int16_t       mval      = ::libs::optim::s16bit::conv::base::c7x7::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;

    ret = ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c7x7::cores::TCore > (
      ::libs::optim::s16bit::conv::base::c7x7::cores::spot1, summ_spot);
    return ret;
  }

  if (size_spot <= 9)
  {
    std::int16_t       mval      = ::libs::optim::s16bit::conv::base::c9x9::cores::spot1.center_val ();
    const std::int32_t summ_spot = mval * size_spot * size_spot + 1;

    ret = ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c9x9::cores::TCore > (
      ::libs::optim::s16bit::conv::base::c9x9::cores::spot1, summ_spot);
    return ret;
  }

  std::int16_t       mval      = ::libs::optim::s16bit::conv::base::c11x11::cores::spot1.center_val ();
  const std::int32_t summ_spot = mval * size_spot * size_spot + 1;

  ret = ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c11x11::cores::TCore > (
    ::libs::optim::s16bit::conv::base::c11x11::cores::spot1, summ_spot);
  return ret;
}


void
MorphOperator::fill_koeffs_for_erosion_operation (
  const std::int16_t                 size_spot,
  ::libs::optim::io::MCallInfo&      cinfo,
  ::libs::optim::mcalls::InfoMFunct& tfunct)
{
  std::int16_t mull_koeff = get_mkoeff_for_erosion_operation (size_spot);

  if (size_spot <= 1)
  {
    tfunct.pfunc_ = &conv_mod_3x3_;
    cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c3x3::cores::spot1));
  }
  else if (size_spot <= 3)
  {
    tfunct.pfunc_ = &conv_mod_5x5_;
    cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c5x5::cores::spot1));
  }
  else if (size_spot <= 5)
  {
    tfunct.pfunc_ = &conv_mod_7x7_;
    cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c7x7::cores::spot1));
  }
  else if (size_spot <= 7)
  {
    tfunct.pfunc_ = &conv_mod_9x9_;
    cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c9x9::cores::spot1));
  }
  else
  {
    tfunct.pfunc_ = &conv_mod_11x11_;
    cinfo.params_.evals_.push_back (boost::any (&::libs::optim::s16bit::conv::base::c11x11::cores::spot1));
  }

  cinfo.params_.evals_.push_back (boost::any (mull_koeff));
}


void
MorphOperator::erosion_buf (
  const syn::NodeID&                id_node,
  const syn::MorphOperationParams&  op,
  ::libs::bufs::Bufs*               pbuf,
  ::utils::dbufs::video::IVideoBuf* pdst)
{
  auto tbuf = (*pbuf)[utils::dbufs::video::consts::offs::temp1];

  tbuf->clone (pdst, 100.0f);

  utils::dbufs::video::helpers::fill_edges (tbuf);

#if 0
  U3_ASSERT (tbuf->check (
    [] (std::size_t x, std::size_t y, std::int16_t val)
    {
      if (val > 1)
      {
        U3_LOG_DATA_WRN ("check tbuf" + VTOLOG (x) + VTOLOG (y) + VTOLOG (val));
        return false;
      }
      return true;
    }));
#endif

  U3_ASSERT (utils::dbufs::video::helpers::is_equal_dim (*tbuf, *pdst));

  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (tbuf, "tbuf dlls::gens::vgen_mops::lib::helpers"));
  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (pdst, "dst dlls::gens::vgen_mops::lib::helpers"));

  ::libs::optim::mcalls::InfoMFunct tfunct;

  fill_koeffs_for_erosion_operation (op.size_spot_, cinfo, tfunct);

  pthreads_->mthreads_call (
    id_node,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_mops::lib::helpers
