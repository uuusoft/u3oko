/**
\file       med1-impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med1-includes_int.hpp"
#include "med1-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::filter_noise::time::impl::med1
{
Med1Impl::Med1Impl ()
{
  pthreads_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
}


Med1Impl::~Med1Impl ()
{
}


void
Med1Impl::load_int ()
{
}


void
Med1Impl::sync_int ()
{
  sync_request_ = true;
}


void
Med1Impl::transform_int (
  const ::libs::core::graph::NodeID& id_node,
  syn::TransformInfo&                transform_info,
  InfoFilter&                        finfo,
  ::libs::bufs::Bufs*                pbuf)
{
  if (sync_request_)
  {
    mbufs_.clear ();
    sync_request_ = false;
  }

#if 0
  auto       impl_info  = ::libs::iproperties::helpers::cast_event< syn::MedianTimeFilterProp > (finfo.rprops_->impl_info_);
  const auto count_bufs = impl_info->count_bufs_;

  for (const auto& ibuf : finfo.rprops_->bufs_)
  {
    if (!utils::dbufs::video::consts::offs::is_valid (ibuf))
    {
      U3_ASSERT_SIGNAL ("failed");
      continue;
    }

    auto sbuf = (*pbuf)[ibuf];

    if (!sbuf || sbuf->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    if (mbufs_.end () == mbufs_.find (ibuf))
    {
      mbufs_.insert (std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, BuffMed1Impl > (ibuf, BuffMed1Impl (count_bufs)));
    }

    ::libs::helpers::statistic::helpers::functors::AddOpTime slock (
      finfo.expand_time_algs_,
      ::libs::core::graph::get_ext_graph_node_id (id_node),
      "one full buf " + ibuf);

    auto&      mbuf       = mbufs_[ibuf];
    const bool dbuf_valid = utils::dbufs::video::consts::offs::is_valid (finfo.rprops_->indx_diff_buf_);
    const auto indx_diff  = dbuf_valid ? finfo.rprops_->indx_diff_buf_ : utils::dbufs::video::consts::offs::temp2;
    auto       cdiff      = (*pbuf)[indx_diff];

    U3_CHECK (::utils::dbufs::video::consts::offs::invalid != indx_diff, "invalid indx diff buf");
    U3_CHECK (cdiff, "invalid diff buf");

    mbuf.sync_by_vbuf (sbuf);

    if (impl_info->motion_detect_)
    {
      mbuf.sync_by_dbuf (cdiff);
    }

    const std::size_t width  = sbuf->get_dim_var (::utils::dbufs::video::Dims::width);
    const std::size_t height = sbuf->get_dim_var (::utils::dbufs::video::Dims::height);

    for (std::size_t indxy = 0; indxy < height; ++indxy)
    {
      auto iline = ::utils::dbufs::video::helpers::get_line_data_as< short* > (sbuf, indxy);

      for (std::size_t indxx = 0; indxx < width; ++indxx)
      {
        const auto&        node = mbuf.get_node (indxx, indxy);
        const std::int16_t val  = node.get_relement (count_bufs / 2 + 1);

        iline[indxx] = val;
      }
    }
  }
#endif
}
}   // namespace dlls::filter_noise::time::impl::med1
