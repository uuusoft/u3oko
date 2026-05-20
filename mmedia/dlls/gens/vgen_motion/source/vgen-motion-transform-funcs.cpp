/**
\file       vgen-motion-transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgd_motion
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-motion-includes_int.hpp"
#include "vgen-motion-info-filter-dll.hpp"
#include "vgen-motion-filter-dll.hpp"

namespace dlls::gens::vgen_motion
{
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

#if 0
    //debug
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
      prevbuf->clone (pcur_src, 100.0f);
      // req_copy2prev = false;
    }

    make_motion_est_buf (b2b, *pcur_src, *prevbuf, *pdst);

    prevbuf->clone (pcur_src, 100.0f);

    pdst->set_mem_var (
      ::utils::dbufs::MemVars::size_data,
      pdst->get_dim_var (::utils::dbufs::video::Dims::stride) * pdst->get_dim_var (::utils::dbufs::video::Dims::height));
  }
}
}   // namespace dlls::gens::vgen_motion
