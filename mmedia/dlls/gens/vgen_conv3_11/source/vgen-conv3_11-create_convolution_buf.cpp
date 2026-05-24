/**
\file       vgen-conv3_11-create_convolution_buf.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_core_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-conv3_11-includes_int.hpp"
#include "vgen-conv3_11-info-filter-dll.hpp"
#include "vgen-conv3_11-filter-dll.hpp"

namespace dlls::gens::vgen_conv3_11
{
short
get_mul_koeff_for_conv (const syn::BuffVideoConvolutionProp& ibuf, ::libs::optim::io::MCallInfo& cinfo)
{
  switch (ibuf.core_size_)
  {
  case 3:
    return ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type > (
      *boost::any_cast< const ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type* > (cinfo.params_.evals_[0]),
      ibuf.core_koeff_);
  case 5:
    return ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c5x5::cores::TCore > (
      *boost::any_cast< const ::libs::optim::s16bit::conv::base::c5x5::cores::TCore* > (cinfo.params_.evals_[0]),
      ibuf.core_koeff_);
  case 7:
    return ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c7x7::cores::TCore > (
      *boost::any_cast< const ::libs::optim::s16bit::conv::base::c7x7::cores::TCore* > (cinfo.params_.evals_[0]),
      ibuf.core_koeff_);
  case 9:
    return ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c9x9::cores::TCore > (
      *boost::any_cast< const ::libs::optim::s16bit::conv::base::c9x9::cores::TCore* > (cinfo.params_.evals_[0]),
      ibuf.core_koeff_);
  case 11:
    return ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c11x11::cores::TCore > (
      *boost::any_cast< const ::libs::optim::s16bit::conv::base::c11x11::cores::TCore* > (cinfo.params_.evals_[0]),
      ibuf.core_koeff_);
  default:
    U3_LOG_DATA_ERROR ("unknown syn::BuffVideoConvolutionProp core size" + VTOLOG (ibuf.core_size_));
    return ::libs::optim::s16bit::conv::get_mkoeff_core< ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type > (
      *boost::any_cast< const ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type* > (cinfo.params_.evals_[0]),
      ibuf.core_koeff_);
  }
}


void
Filter::fill_koeffs_for_conv (
  const syn::BuffVideoConvolutionProp& ibuf,
  ::libs::optim::io::MCallInfo&        cinfo,
  ::libs::optim::mcalls::InfoMFunct&   tfunct)
{
  if (ibuf.core_size_ <= 3)
  {
    switch (ibuf.convolution_type_)
    {
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_1:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::all_1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_m1:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::all_m1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus1:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::gaus1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus2:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::gaus2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus3:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::gaus3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas1:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::laplas1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas2:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::laplas2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas3:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::laplas3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::average:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::avg1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::spot:
      icore_3x3_ = &::libs::optim::s16bit::conv::base::c3x3::cores::spot1;
      break;
    default:
      icore_3x3_ = &core_3x3_;
      ::libs::optim::s16bit::conv::base::c3x3::cores::copy (ibuf.core_vals_, core_3x3_);
      break;
    }

    tfunct.pfunc_ = &conv_mod_3x3_;
    cinfo.params_.evals_.push_back (boost::any (const_cast< const ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type* > (icore_3x3_)));
  }
  else if (ibuf.core_size_ <= 5)
  {
    switch (ibuf.convolution_type_)
    {
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_1:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::all_1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_m1:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::all_m1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus1:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::gaus1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus2:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::gaus2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus3:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::gaus3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas1:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::laplas1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas2:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::laplas2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas3:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::laplas3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::average:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::avg1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::spot:
      icore_5x5_ = &::libs::optim::s16bit::conv::base::c5x5::cores::spot1;
      break;
    default:
      icore_5x5_ = &core_5x5_;
      ::libs::optim::s16bit::conv::base::c5x5::cores::copy (ibuf.core_vals_, core_5x5_);
      break;
    }

    tfunct.pfunc_ = &conv_mod_5x5_;
    cinfo.params_.evals_.push_back (boost::any (const_cast< const ::libs::optim::s16bit::conv::base::c5x5::cores::TCore* > (icore_5x5_)));
  }
  else if (ibuf.core_size_ <= 7)
  {
    switch (ibuf.convolution_type_)
    {
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_1:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::all_1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_m1:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::all_m1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus1:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::gaus1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus2:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::gaus2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus3:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::gaus3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas1:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::laplas1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas2:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::laplas2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas3:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::laplas3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::average:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::avg1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::spot:
      icore_7x7_ = &::libs::optim::s16bit::conv::base::c7x7::cores::spot1;
      break;
    default:
      icore_7x7_ = &core_7x7_;
      ::libs::optim::s16bit::conv::base::c7x7::cores::copy (ibuf.core_vals_, core_7x7_);
      break;
    }

    tfunct.pfunc_ = &conv_mod_7x7_;
    cinfo.params_.evals_.push_back (boost::any (const_cast< const ::libs::optim::s16bit::conv::base::c7x7::cores::TCore* > (icore_7x7_)));
  }
  else if (ibuf.core_size_ <= 9)
  {
    switch (ibuf.convolution_type_)
    {
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_1:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::all_1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_m1:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::all_m1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus1:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::gaus1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus2:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::gaus2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus3:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::gaus3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas1:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::laplas1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas2:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::laplas2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas3:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::laplas3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::average:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::avg1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::spot:
      icore_9x9_ = &::libs::optim::s16bit::conv::base::c9x9::cores::spot1;
      break;
    default:
      icore_9x9_ = &core_9x9_;
      ::libs::optim::s16bit::conv::base::c9x9::cores::copy (ibuf.core_vals_, core_9x9_);
      break;
    }

    tfunct.pfunc_ = &conv_mod_9x9_;
    cinfo.params_.evals_.push_back (boost::any (const_cast< const ::libs::optim::s16bit::conv::base::c9x9::cores::TCore* > (icore_9x9_)));
  }
  else
  {
    switch (ibuf.convolution_type_)
    {
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_1:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::all_1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::all_to_m1:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::all_m1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus1:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::gaus1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus2:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::gaus2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::gaus3:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::gaus3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas1:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::laplas1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas2:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::laplas2;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::laplas3:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::laplas3;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::average:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::avg1;
      break;
    case libs::ievents::props::videos::generic::convolution::Convs::spot:
      icore_11x11_ = &::libs::optim::s16bit::conv::base::c11x11::cores::spot1;
      break;
    default:
      icore_11x11_ = &core_11x11_;
      ::libs::optim::s16bit::conv::base::c11x11::cores::copy (ibuf.core_vals_, core_11x11_);
      break;
    }

    tfunct.pfunc_ = &conv_mod_11x11_;
    cinfo.params_.evals_.push_back (boost::any (const_cast< const ::libs::optim::s16bit::conv::base::c11x11::cores::TCore* > (icore_11x11_)));
  }

  const std::int16_t mull_koeff = get_mul_koeff_for_conv (ibuf, cinfo);
  cinfo.params_.evals_.push_back (boost::any (mull_koeff));
}


void
Filter::convolution_buf ()
{
  for (syn::BuffVideoConvolutionProp& buf : finfo_.rprops_->bufs_)
  {
    if (libs::ievents::props::videos::generic::convolution::Convs::skip == buf.convolution_type_)
    {
      continue;
    }

    buf.check ();

    utils::dbufs::video::IVideoBuf::raw_ptr src = (*pbuf_)[buf.indx_sbuf_];
    if (!src || src->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    ::libs::bufs::alloc_buf_by_indx (pbuf_, buf.indx_dbuf_, src);

    utils::dbufs::video::IVideoBuf::raw_ptr dst          = (*pbuf_)[buf.indx_dbuf_];
    const bool                              req_temp_buf = (buf.indx_dbuf_ == buf.indx_sbuf_) ? true : false;
    utils::dbufs::video::IVideoBuf::raw_ptr tbuf         = (*pbuf_)[utils::dbufs::video::consts::offs::temp1];

    // bin_buf( b2b, 0, 1, pdst );

    if (req_temp_buf)
    {
      tbuf->clone (src, 0.0f);
      // utils::dbufs::video::helpers::fill_edges( &tbuf );
    }

    ::libs::optim::io::MCallInfo cinfo;

    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (src, "src dlls::gens::vgen_conv3_11"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (req_temp_buf ? tbuf : dst, "tbuf dst dlls::gens::vgen_conv3_11"));

    ::libs::optim::mcalls::InfoMFunct tfunct;

    fill_koeffs_for_conv (buf, cinfo, tfunct);

    pthreads_->mthreads_call (id_obj_, tfunct, cinfo, transinfo_->exptimes_);

    if (req_temp_buf)
    {
      tbuf->set_mem_var (::utils::dbufs::MemVars::size_data, (*src)[::utils::dbufs::MemVars::size_data]);
      dst->clone (tbuf, 100.0f);
    }

    dst->set_mem_var (::utils::dbufs::MemVars::size_data, (*src)[::utils::dbufs::MemVars::size_data]);
  }
}
}   // namespace dlls::gens::vgen_conv3_11
