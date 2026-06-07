/**
\file       rang-filter.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_noisez
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "space-noise-impl-rang-includes_int.hpp"
#include "rang-filter.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::noisez::space::impl::rang
{
/// Вспомогательная функция для конвертации параметров подсистемы пула рабочих потоков в параметры фильтрации изображения в пространственной области
/// \param[in]  info       параметры подсистемы пула рабочих потоков
/// \param[out] iinfo      параметры области изображения, над которой будет работать данный поток
/// \param[out] impl_info  параметры фильтрации, разделяемые между всеми потоками пула
/// \param[out] ppimpls    реализации фильтрации для всех потоков пула
void
get_params (
  ::libs::optim::io::MCallInfo&        mcinfo,
  ProcessAlgInfo&                      iinfo,
  syn::MedianSpaceFilterProp::raw_ptr& impl_info,
  RangFilter::algs_storage_type**      ppimpls)
// std::vector< IAlgImpl::ptr >**       ppimpls)
{
  iinfo.reset ();

  U3_CHECK (3 == mcinfo.params_.evals_.size (), "invald size evals");
  U3_CHECK (2 == mcinfo.srcs_.size (), "src not equal 2");
  U3_CHECK (1 == mcinfo.dsts_.size (), "dsts not equal 1");

  iinfo.sbuf_ = &mcinfo.srcs_[0];
  iinfo.dbuf_ = &mcinfo.srcs_[1];
  iinfo.buf_  = &mcinfo.dsts_[0];

  impl_info        = boost::any_cast< syn::MedianSpaceFilterProp::raw_ptr > (mcinfo.params_.evals_[0]);
  iinfo.pfinfo_    = boost::any_cast< InfoFilter* > (mcinfo.params_.evals_[1]);
  iinfo.impl_info_ = impl_info;
  *ppimpls         = boost::any_cast< RangFilter::algs_storage_type* > (mcinfo.params_.evals_[2]);
  //*ppimpls = boost::any_cast< algs_storage_typestd::vector< IAlgImpl::ptr >* > (mcinfo.params_.evals_[2]);

  U3_CHECK (*ppimpls, "empty impls");
  U3_CHECK (iinfo.check (), "check params");
}

/// Вспомогательная функция для вызова реализации фильтрации в пуле потоков над частью изображения
/// \param[in]  info параметры фильтрации, которые нужно использовать над данной частью изображения
void
ext_mcall (::libs::optim::io::MCallInfo& info)
{
  ProcessAlgInfo                      icall_info;
  RangFilter::algs_storage_type*      pimpls    = nullptr;
  syn::MedianSpaceFilterProp::raw_ptr impl_info = nullptr;

  get_params (info, icall_info, impl_info, &pimpls);
  auto& algs = (*pimpls)[impl_info->sort_type_];
  // проверяем на рассинхронизацию, если пользователь изменил параметры рабочих потоков
  U3_CHECK (info.indx_thread_ < algs.size (), "skip rang filter, parameters changed:" + VTOLOG (info.indx_thread_) + VTOLOG (algs.size ()) + TOLOG (to_string (impl_info->sort_type_)));
  algs.at (info.indx_thread_)->process (icall_info);
}


RangFilter::RangFilter ()
{
  pthreads_ = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
  //  заполняем его исскуственно.
  ext_call_.set (ext_mcall);
  ext_call_.set_algoritm_name ("dlls.noisez.space.impl.rang");
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
  if (!temp_src_buf_)
  {
    temp_src_buf_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ()->create (0);
  }

  for (auto& bufs : finfo.rprops_->bufs_)
  {
    syn::MedianSpaceFilterProp::raw_ptr impl_info = ::libs::iproperties::helpers::cast_event< syn::MedianSpaceFilterProp > (bufs.impl_info_);
    U3_CHECK (impl_info, "empty syn::MedianSpaceFilterProp");
    if (libs::ievents::props::videos::noises::space::ext::Sortings::skip == impl_info->sort_type_)
    {
      continue;
    }
    if (!syn::offs::is_valid (bufs.indx_sbuf_))
    {
      U3_LOG_DATA_ERROR ("unvalid destination buf" + TOLOG (bufs.indx_sbuf_));
      continue;
    }
    auto src = (*pbuf)[bufs.indx_sbuf_];
    if (!src || src->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    auto& algs = algs_[impl_info->sort_type_];
    if (algs.size () != pthreads_->get_count_threads ())
    {
      algs.resize (pthreads_->get_count_threads ());
      std::ranges::for_each (
        algs,
        [this, &finfo, &impl_info] (IAlgImpl::ptr& alg) {
          if (!alg)
          {
            alg = make_rang_impl (finfo, impl_info);
          }
        });
    }

    ::libs::helpers::statistic::helpers::functors::AddOpTime slock (
      finfo.expand_time_algs_,
      ::libs::core::graph::get_ext_graph_node_id (id_node),
      "one full buf " + bufs.indx_sbuf_);

    ::libs::bufs::alloc_buf_by_indx (pbuf, bufs.indx_dbuf_, src);

    auto       dst          = (*pbuf)[bufs.indx_dbuf_];
    const bool use_temp_buf = (bufs.indx_dbuf_ == bufs.indx_sbuf_) ? true : false;
    auto       tbuf         = (*pbuf)[syn::offs::temp1];

    const auto dbuf_valid = syn::offs::is_valid (impl_info->indx_cond_buf_);
    const auto indx_diff  = dbuf_valid ? impl_info->indx_cond_buf_ : syn::offs::temp2;
    auto       cdiff      = (*pbuf)[indx_diff];

    U3_CHECK (!impl_info->use_cond_buf_ || syn::offs::invalid != indx_diff, "invalid indx diff buf");
    U3_CHECK (!impl_info->use_cond_buf_ || cdiff, "invalid diff buf");

    utils::dbufs::video::helpers::fill_edges (src);

    if (use_temp_buf)
    {
      tbuf->clone (src, 0.0F);
    }

    {
      ::libs::optim::io::ProxyBuf  src_dst (use_temp_buf ? tbuf : dst, "sbuf dlls::noisez::space::impl::rang");
      ::libs::optim::io::ProxyBuf  diff (impl_info->use_cond_buf_ ? cdiff : nullptr, "cdiff dlls::noisez::space::impl::rang");
      ::libs::optim::io::ProxyBuf  proxy_src (src, "temp_src_buf dlls::noisez::space::impl::rang");
      ::libs::optim::io::MCallInfo cinfo;

      cinfo.srcs_.emplace_back (proxy_src);
      cinfo.srcs_.emplace_back (diff);
      cinfo.dsts_.emplace_back (src_dst);

      cinfo.params_.evals_.reserve (3);
      cinfo.params_.evals_.emplace_back (impl_info);
      cinfo.params_.evals_.emplace_back (&finfo);
      cinfo.params_.evals_.emplace_back (&algs_);

      ::libs::optim::mcalls::MTFuncInfo tfunc (&ext_call_);
      pthreads_->mthreads_call (
        id_node,
        tfunc,
        cinfo,
        transform_info.exptimes_);
    }

    if (use_temp_buf)
    {
      tbuf->set_mem_var (::utils::dbufs::MemVars::size_data, (*src)[::utils::dbufs::MemVars::size_data]);
      dst->clone (tbuf, 100.0F);
    }

    dst->set_mem_var (::utils::dbufs::MemVars::size_data, (*src)[::utils::dbufs::MemVars::size_data]);
  }
}


IAlgImpl::ptr
RangFilter::make_rang_impl (InfoFilter& finfo, syn::MedianSpaceFilterProp::raw_ptr impl_info)
{
  switch (impl_info->sort_type_)
  {
  //  самый часто используемый вариант сортировки, он же по умолчанию.
  case syn::Sortings::count:
  case syn::Sortings::usual:
    return std::make_shared< vars::CountSortImpl > ();
  case syn::Sortings::adaptive:
    return std::make_shared< vars::CountSortImpl > ();
  case syn::Sortings::skip:
    return std::make_shared< vars::SkipSortImpl > ();
  case syn::Sortings::standart:
    return std::make_shared< vars::StandartSortImpl > ();
  case syn::Sortings::insert:
    return std::make_shared< vars::InsertSortImpl > ();
  case syn::Sortings::rand:
    return std::make_shared< vars::RandSortImpl > ();
  case syn::Sortings::unknown:
    return std::make_shared< vars::SkipSortImpl > ();
  }

  U3_LOG_DATA_WRN ("unknown type sort impl" + VTOLOG (U3_CAST_UINT32_FORCE (impl_info->sort_type_)));
  return std::make_shared< vars::SkipSortImpl > ();
}
}   // namespace dlls::noisez::space::impl::rang
