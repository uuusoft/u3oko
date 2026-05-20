/**
\file       med3-impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med3-includes_int.hpp"
#include "med3-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::filter_noise::time::impl::med3
{
Med3Impl::Med3Impl ()
{
  pthreads_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
}


Med3Impl::~Med3Impl ()
{
}


void
Med3Impl::load_int ()
{
}


void
Med3Impl::sync_int ()
{
  sync_request_ = true;
}


void
Med3Impl::transform_int (
  const ::libs::core::graph::NodeID&                  id_node,
  ::libs::icore::impl::var1::obj::dll::TransformInfo& transform_info,
  InfoFilter&                                         finfo,
  ::libs::bufs::Bufs*                                 pbuf)
{
  if (sync_request_)
  {
    mbufs_.clear ();
    sync_request_ = false;
  }

  auto impl_info = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp > (finfo.rprops_->impl_info_);

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
      mbufs_.insert (std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, BuffMed3Impl > (ibuf, BuffMed3Impl (impl_info)));
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

    {
      ::libs::helpers::statistic::helpers::functors::AddOpTime lslock (
        finfo.expand_time_algs_,
        ::libs::core::graph::get_ext_graph_node_id (id_node),
        "sync_by_vbuf");

      mbuf.sync_by_vbuf (sbuf, cdiff, impl_info);
    }
  }
}
}   // namespace dlls::filter_noise::time::impl::med3
