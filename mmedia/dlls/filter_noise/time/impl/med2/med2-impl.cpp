/**
\file       med2-impl.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "time-noise-impl-med2-includes_int.hpp"
#include "med2-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::filter_noise::time::impl::med2
{
void
get_params (
  ::libs::optim::io::MCallInfo&                                                     info,
  ::libs::optim::io::ProxyBuf**                                                     src_dst,
  ::libs::optim::io::ProxyBuf**                                                     akk_mbuf,
  const ::libs::optim::io::ProxyBuf**                                               diff,
  ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::raw_ptr& impl_info,
  BuffMed2Impl**                                                                    parent)
{
  U3_CHECK (2 == info.params_.evals_.size (), "invald size evals");
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (2 == info.dsts_.size (), "dsts not equal 2");

  *diff = &info.srcs_[0];

  *src_dst  = &info.dsts_[0];
  *akk_mbuf = &info.dsts_[1];

  U3_CHECK (*src_dst, "empty src_dst");
  U3_CHECK (*akk_mbuf, "empty akk_mbuf");

  impl_info = boost::any_cast< ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::raw_ptr > (info.params_.evals_[0]);
  *parent   = boost::any_cast< BuffMed2Impl* > (info.params_.evals_[1]);

  U3_CHECK (impl_info, "empty impl_info");
  U3_CHECK (*parent, "empty parent");
  U3_CHECK (!impl_info->motion_detect_ || *diff, "empty diff");
}


void
ext_mcall (::libs::optim::io::MCallInfo& info)
{
  ::libs::optim::io::ProxyBuf*                                                     src_dst  = nullptr;
  ::libs::optim::io::ProxyBuf*                                                     akk_mbuf = nullptr;
  const ::libs::optim::io::ProxyBuf*                                               diff     = nullptr;
  BuffMed2Impl*                                                                    parent   = nullptr;
  ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp::raw_ptr impl_info;

  get_params (info, &src_dst, &akk_mbuf, &diff, impl_info, &parent);

  parent->sync_by_vbuf (src_dst, akk_mbuf, diff, impl_info);
}


Med2Impl::Med2Impl () :
  ext_call_ (&store_call_)
{
  pthreads_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
  //  заполняем его исскуственно.
  ext_call_.set (ext_mcall);
  ext_call_.set_algoritm_name ("dlls.filter_noise.time.impl.med2");
}


Med2Impl::~Med2Impl ()
{
}


void
Med2Impl::load_int ()
{
}


void
Med2Impl::sync_int ()
{
  sync_request_ = true;
}


void
Med2Impl::transform_int (
  const ::libs::core::graph::NodeID&                  id_node,
  ::libs::icore::impl::var1::obj::dll::TransformInfo& transform_info,
  InfoFilter&                                         finfo,
  ::libs::bufs::Bufs*                                 pbuf)
{
  if (sync_request_)
  {
    U3_LOG_DATA_DBG ("time filtration: sync bufs - free bufs");
    mbufs_.clear ();
    sync_request_ = false;
  }

  auto impl_info = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp > (finfo.rprops_->impl_info_);

  for (const auto& ibuf : finfo.rprops_->bufs_)
  {
    if (!utils::dbufs::video::consts::offs::is_valid (ibuf))
    {
      continue;
    }

    auto sbuf = (*pbuf)[ibuf];
    if (!sbuf || sbuf->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    if (mbufs_.end () == mbufs_.find (ibuf))
    {
      U3_LOG_DATA_DBG ("time filtration: create new for" + TOLOG (ibuf));
      mbufs_.insert (std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, BuffMed2Impl > (ibuf, BuffMed2Impl (impl_info)));
    }

    ::libs::helpers::statistic::helpers::functors::AddOpTime slock (
      finfo.expand_time_algs_,
      ::libs::core::graph::get_ext_graph_node_id (id_node),
      "one full buf " + ibuf);

    auto&      mbuf       = mbufs_[ibuf];
    const bool dbuf_valid = utils::dbufs::video::consts::offs::is_valid (finfo.rprops_->indx_diff_buf_);
    const auto indx_diff  = dbuf_valid ? finfo.rprops_->indx_diff_buf_ : utils::dbufs::video::consts::offs::temp2;
    auto       cdiff      = (*pbuf)[indx_diff];

    U3_CHECK (!impl_info->motion_detect_ || ::utils::dbufs::video::consts::offs::invalid != indx_diff, "invalid indx diff buf");
    U3_CHECK (!impl_info->motion_detect_ || cdiff, "invalid diff buf");

    {
      ::libs::helpers::statistic::helpers::functors::AddOpTime lslock (finfo.expand_time_algs_, ::libs::core::graph::get_ext_graph_node_id (id_node), "sync_by_vbuf");
      ::libs::optim::io::ProxyBuf                              src_dst (sbuf, "sbuf dlls::filter_noise::time::impl::med2");
      ::libs::optim::io::ProxyBuf                              diff (cdiff, "cdiff dlls::filter_noise::time::impl::med2");

      mbuf.update_int_bufs (&src_dst, &diff, impl_info);

      ::libs::optim::io::ProxyBuf  akk_mbuf (mbuf.shared_info_.akk_mbuf_.get (), "mbuf dlls::filter_noise::time::impl::med2");
      ::libs::optim::io::MCallInfo cinfo;

      cinfo.srcs_.push_back (diff);
      cinfo.dsts_.push_back (src_dst);
      cinfo.dsts_.push_back (akk_mbuf);

      cinfo.params_.evals_.push_back (impl_info);
      cinfo.params_.evals_.push_back (&mbuf);

      ::libs::optim::mcalls::InfoMFunct tfunct (&ext_call_);

      pthreads_->mthreads_call (id_node, tfunct, cinfo, transform_info.exptimes_);
    }
  }
}
}   // namespace dlls::filter_noise::time::impl::med2
