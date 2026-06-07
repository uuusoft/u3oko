/**
\file       vgen-motion-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgd_motion
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-motion-includes_int.hpp"
#include "vgen-motion-info-filter-dll.hpp"
#include "vgen-motion-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_motion
{
void
Filter::load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);

  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  cmp_get_const_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCmpGTConstAlg::val_key));
  motion_est1_   = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CMotionEst1Alg::val_key));
}


void
Filter::transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info)
{
  prepare_transform (info);
  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  // add offset for active data and corrected active data correct frame
  itransform ();
}


void
Filter::call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::make_motion_est_buf (
  syn::EventBufsInfoMotionEst& b2b,
  const syn::IVideoBuf&        cur_src,
  const syn::IVideoBuf&        prev_src,
  syn::IVideoBuf&              dst_vecs)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.emplace_back (const_cast< syn::IVideoBuf::raw_ptr > (&cur_src), "cur_src dlls::gens::vgen_motion");
  cinfo.srcs_.emplace_back (const_cast< syn::IVideoBuf::raw_ptr > (&prev_src), "prev_src dlls::gens::vgen_motion");
  cinfo.dsts_.emplace_back (&dst_vecs, "dst_vecs dlls::gens::vgen_motion");

  cinfo.params_.evals_.emplace_back (boost::any (&b2b));

  ::libs::optim::mcalls::MTFuncInfo tfunc (&motion_est1_);

  tfunc.src_align_.px_x_ = b2b.size_block_;
  tfunc.dst_align_.px_x_ = b2b.size_block_;
  tfunc.src_align_.px_y_ = b2b.size_block_;
  tfunc.dst_align_.px_y_ = 1;

  // tfunc.dest_div_koeffy_ = b2b.size_block_;
  // tfunc.dest_mul_koeffy_ = 1;

  pthreads_->mthreads_call (
    id_obj_,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}


void
fill_search_vecs (syn::EventBufsInfoMotionEst& b2b)
{
  b2b.search_vecs_.reserve (4 * b2b.size_search_ * b2b.size_search_);
  b2b.search_vecs_.clear ();

  for (std::int32_t indxy = 0; indxy < 2 * b2b.size_search_; ++indxy)
  {
    for (std::int32_t indxx = 0; indxx < 2 * b2b.size_search_; ++indxx)
    {
      const auto aindxx = U3_CAST_INT8 (indxx - b2b.size_search_);
      const auto aindxy = U3_CAST_INT8 (indxy - b2b.size_search_);

      b2b.search_vecs_.push_back (std::pair< std::int8_t, std::int8_t > (aindxx, aindxy));
    }
  }

  //  переупорядочиваем вектора по дистанции от центра.
  {
    syn::EventBufsInfoMotionEst::vectors_type temp;

    temp.swap (b2b.search_vecs_);

    b2b.search_vecs_.reserve (4 * b2b.size_search_ * b2b.size_search_);
    b2b.search_vecs_.clear ();

    for (std::uint32_t rad = 0; rad <= U3_CAST_UINT32 (b2b.size_search_ * b2b.size_search_); ++rad)
    {
      std::copy_if (
        temp.begin (),
        temp.end (),
        std::back_inserter (b2b.search_vecs_),
        [rad] (std::pair< std::int8_t, std::int8_t >& val) { return rad == U3_CAST_UINT32 (std::abs (val.first) + std::abs (val.second)); });
    }
  }
}


void
Filter::itransform ()
{
  for (syn::EventBufsInfoMotionEst& b2b : finfo_.rprops_->bufs_)
  {
    b2b.check ();

    if (b2b.search_vecs_.empty ())
    {
      fill_search_vecs (b2b);
    }

    syn::IVideoBuf::raw_ptr pcur_src = (*pbuf_)[b2b.indx_sbuf_];
    if (!pcur_src || pcur_src->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    ::libs::bufs::alloc_buf_by_indx (pbuf_, b2b.indx_dbuf_, pcur_src);

    syn::IVideoBuf::raw_ptr pdst    = (*pbuf_)[b2b.indx_dbuf_];
    std::uint32_t           dwidth  = pcur_src->get_dim_var (::utils::dbufs::video::Dims::width) / b2b.size_block_;
    std::uint32_t           dheight = pcur_src->get_dim_var (::utils::dbufs::video::Dims::height) / b2b.size_block_;

    pdst->buf_alloc (
      ::utils::dbufs::video::AllocBufInfo (
        dwidth,
        dheight,
        0,
        ::libs::helpers::uids::minor::id_val::y16,
        utils::dbufs::video::DimChecks::disable));

    pdst->set_flag (utils::dbufs::BufFlags::special, false);

#ifdef U3_FAKE_DISABLE
    // debug
    ::utils::dbufs::video::helpers::fill (pdst, 0);
#endif

    syn::IVideoBuf::ptr& prevbuf = indx2prev_buf_[b2b.indx_sbuf_];
    if (!prevbuf)
    {
      auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
      prevbuf   = ibuf->create (0);
    }

    // bool req_copy2prev = true;
    if (prevbuf->get_flag (::utils::dbufs::BufFlags::empty) || !utils::dbufs::video::helpers::is_equal_dim (*prevbuf, *pcur_src))
    {
      prevbuf->clone (pcur_src, 100.0F);
      // req_copy2prev = false;
    }

    make_motion_est_buf (b2b, *pcur_src, *prevbuf, *pdst);

    prevbuf->clone (pcur_src, 100.0F);

    pdst->set_mem_var (
      ::utils::dbufs::MemVars::size_data,
      pdst->get_dim_var (::utils::dbufs::video::Dims::stride) * pdst->get_dim_var (::utils::dbufs::video::Dims::height));
  }
}
}   // namespace dlls::gens::vgen_motion
