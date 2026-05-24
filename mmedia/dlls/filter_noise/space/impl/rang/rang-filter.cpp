/**
\file       rang-filter.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "space-noise-impl-rang-includes_int.hpp"
#include "rang-filter.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::filter_noise::space::impl::rang
{
/// Вспомогательная функция для конвертации параметров подсистемы пула рабочих потоков в параметры фильтрации изображения в пространственной области
/// \param[in]  info       параметры подсистемы пула рабочих потоков
/// \param[out] iinfo      параметры области изображения, над которой будет работать данный поток
/// \param[out] impl_info  параметры фильтрации, разделяемые между всеми потоками пула
/// \param[out] ppimpls    реализации фильтрации для всех потоков пула
void
get_params (
  ::libs::optim::io::MCallInfo&        info,
  ProcessAlgInfo&                      iinfo,
  syn::MedianSpaceFilterProp::raw_ptr& impl_info,
  std::vector< IAlgImpl::ptr >**       ppimpls)
{
  iinfo.reset ();

  U3_CHECK (3 == info.params_.evals_.size (), "invald size evals");
  U3_CHECK (2 == info.srcs_.size (), "src not equal 2");
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1");

  iinfo.sbuf_ = &info.srcs_[0];
  iinfo.dbuf_ = &info.srcs_[1];
  iinfo.buf_  = &info.dsts_[0];

  impl_info        = boost::any_cast< ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp::raw_ptr > (info.params_.evals_[0]);
  iinfo.pfinfo_    = boost::any_cast< InfoFilter* > (info.params_.evals_[1]);
  iinfo.impl_info_ = impl_info;
  *ppimpls         = boost::any_cast< std::vector< IAlgImpl::ptr >* > (info.params_.evals_[2]);

  U3_CHECK (*ppimpls, "empty impls");
  U3_CHECK (iinfo.check (), "check params");
}

/// Вспомогательная функция для вызова реализации фильтрации в пуле потоков над частью изображения
/// \param[in]  info параметры фильтрации, которые нужно использовать над данной частью изображения
void
ext_mcall (::libs::optim::io::MCallInfo& info)
{
  ProcessAlgInfo                                                                     icall_info;
  std::vector< IAlgImpl::ptr >*                                                      pimpls    = nullptr;
  ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp::raw_ptr impl_info = nullptr;

  get_params (info, icall_info, impl_info, &pimpls);
  U3_CHECK (info.indx_thread_ < (*pimpls).size (), "skip rand filter - mcall parameters changed:" + VTOLOG (info.indx_thread_) + VTOLOG ((*pimpls).size ()));   // проверяем на рассинхронизацию, если пользовать изменил параметры рабочих потоков
  return (*pimpls)[info.indx_thread_]->process (icall_info);
}


RangFilter::RangFilter () :
  ext_call_ (&store_call_),
  sort_type_ (::libs::ievents::props::videos::noises::space::ext::Sortings::unknown)
{
  pthreads_ = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
  //  заполняем его исскуственно.
  ext_call_.set (ext_mcall);
  ext_call_.set_algoritm_name ("dlls.filter_noise.space.impl.rang");
}


RangFilter::~RangFilter ()
{
}


void
RangFilter::load_int ()
{
}


void
RangFilter::transform_int (
  const ::libs::core::graph::NodeID& id_node,
  space::syn::TransformInfo&         transform_info,
  InfoFilter&                        finfo,
  ::libs::bufs::Bufs*                pbuf)
{
  auto impl_info = ::libs::iproperties::helpers::cast_event< syn::MedianSpaceFilterProp > (finfo.rprops_->impl_info_);
  if (!temp_src_buf_)
  {
    temp_src_buf_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ()->create (0);
  }

  // Если тип алгоритма был изменен - нужно пересоздать реализации
  const auto type = impl_info->sort_type_;
  if (type != sort_type_)
  {
    algs_.clear ();
  }

  if (algs_.size () != pthreads_->get_count_threads ())
  {
    algs_.resize (pthreads_->get_count_threads ());

    std::for_each (
      algs_.begin (),
      algs_.end (),
      [this, &finfo] (IAlgImpl::ptr& alg) {
        if (!alg)
        {
          alg = make_rang_impl (finfo);
        }
        return;
      });
  }

#if 0
  // debug для тестирования рассинхронизации количества рабочих потоков и данных под них
  std::this_thread::sleep_for (std::chrono::milliseconds (3000));
#endif

  for (const auto& ibuf : finfo.rprops_->bufs_)
  {
    if (!utils::dbufs::video::consts::offs::is_valid (ibuf))
    {
      U3_LOG_DATA_ERROR ("unvalid destination buf" + TOLOG (ibuf));
      continue;
    }

    auto sbuf = (*pbuf)[ibuf];
    if (!sbuf || sbuf->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    ::libs::helpers::statistic::helpers::functors::AddOpTime slock (
      finfo.expand_time_algs_,
      ::libs::core::graph::get_ext_graph_node_id (id_node),
      "one full buf " + ibuf);

    const bool dbuf_valid = ::utils::dbufs::video::consts::offs::is_valid (finfo.rprops_->indx_cond_buf_);
    const auto indx_diff  = dbuf_valid ? finfo.rprops_->indx_cond_buf_ : utils::dbufs::video::consts::offs::temp2;
    auto       cdiff      = (*pbuf)[indx_diff];

    U3_CHECK (impl_info, "empty impl info");
    U3_CHECK (!finfo.rprops_->use_cond_buf_ || ::utils::dbufs::video::consts::offs::invalid != indx_diff, "invalid indx diff buf");
    U3_CHECK (!finfo.rprops_->use_cond_buf_ || cdiff, "invalid diff buf");

    utils::dbufs::video::helpers::fill_edges (sbuf);

    temp_src_buf_->clone (sbuf, 0.0f);
    temp_src_buf_->swap (*sbuf);

    sbuf->set_mem_var (::utils::dbufs::MemVars::size_data, (*temp_src_buf_)[::utils::dbufs::MemVars::size_data]);

    {
      ::libs::optim::io::ProxyBuf  src_dst (sbuf, "sbuf dlls::filter_noise::space::impl::rang");
      ::libs::optim::io::ProxyBuf  diff (finfo.rprops_->use_cond_buf_ ? cdiff : nullptr, "cdiff dlls::filter_noise::space::impl::rang");
      ::libs::optim::io::ProxyBuf  src (temp_src_buf_.get (), "temp_src_buf dlls::filter_noise::space::impl::rang");
      ::libs::optim::io::MCallInfo cinfo;

      cinfo.srcs_.push_back (src);
      cinfo.srcs_.push_back (diff);

      cinfo.dsts_.push_back (src_dst);

      cinfo.params_.evals_.push_back (impl_info);
      cinfo.params_.evals_.push_back (&finfo);
      cinfo.params_.evals_.push_back (&algs_);

      ::libs::optim::mcalls::InfoMFunct tfunct (&ext_call_);

      pthreads_->mthreads_call (
        id_node,
        tfunct,
        cinfo,
        transform_info.exptimes_);
    }
  }
}


IAlgImpl::ptr
RangFilter::make_rang_impl (InfoFilter& finfo)
{
  const auto& impl_info = ::libs::iproperties::helpers::cast_event< syn::MedianSpaceFilterProp > (finfo.rprops_->impl_info_);

  sort_type_ = impl_info->sort_type_;

  switch (sort_type_)
  {
  //  самый часто используемый вариант сортировки, он же по умолчанию.
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::count:
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::usual:
    return std::make_shared< vars::CountSortImpl > ();
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::adaptive:
    return std::make_shared< vars::CountSortImpl > ();
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::skip:
    return std::make_shared< vars::SkipSortImpl > ();
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::standart:
    return std::make_shared< vars::StandartSortImpl > ();
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::insert:
    return std::make_shared< vars::InsertSortImpl > ();
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::rand:
    return std::make_shared< vars::RandSortImpl > ();
  case ::libs::ievents::props::videos::noises::space::ext::Sortings::unknown:
    return std::make_shared< vars::SkipSortImpl > ();
  }

  U3_LOG_DATA_WRN ("unknown type sort impl" + VTOLOG (U3_CAST_UINT32_FORCE (sort_type_)));
  return std::make_shared< vars::SkipSortImpl > ();
}
}   // namespace dlls::filter_noise::space::impl::rang
