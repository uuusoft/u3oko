//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       rang-filter.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_time_filter_noise
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "rang-filter.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang {
/**
  \brief      Вспомогательная функция для конвертации параметров подсистемы пула рабочих потоков в параметры фильтрации изображения в пространственной области.
  \param[in]  _info       параметры подсистемы пула рабочих потоков.
  \param[out] _iinfo      параметры области изображения, над которой будет работать данный поток.
  \param[out] _impl_info  параметры фильтрации, разделяемые между всеми потоками пула.
  \param[out] _ppimpls    реализации фильтрации для всех потоков пула.
  */
void
get_params (
  MCallInfo&                   _info,
  ProcessAlgInfo&              _iinfo,
  MedianSpaceFilterProp::ptr&  _impl_info,
  std::vector<IAlgImpl::ptr>** _ppimpls)
{
  _iinfo.reset ();

  CHECK_STATE (3 == _info.params_.evals_.size (), "failed, invald size evals");
  CHECK_STATE (2 == _info.srcs_.size (), "failed, src not equal 1");
  CHECK_STATE (1 == _info.dsts_.size (), "failed, dsts not equal 2");

  _iinfo.sbuff_ = &_info.srcs_[0];
  _iinfo.dbuff_ = &_info.srcs_[1];
  _iinfo.buff_  = &_info.dsts_[0];

  _impl_info        = boost::any_cast<MedianSpaceFilterProp::ptr> (_info.params_.evals_[0]);
  _iinfo.pfinfo_    = boost::any_cast<InfoFilter*> (_info.params_.evals_[1]);
  _iinfo.impl_info_ = _impl_info.get ();
  *_ppimpls         = boost::any_cast<std::vector<IAlgImpl::ptr>*> (_info.params_.evals_[2]);

  CHECK_STATE (*_ppimpls, "failed, empty impls");
  CHECK_STATE (_iinfo.check (), "failed check params");
  return;
}
/**
  \brief      Вспомогательная функция для вызова реализации фильтрации в пуле потоков над частью изображения.
  \param[in]  _info параметры фильтрации, которые нужно использовать над данной частью изображения.
  */
void
ext_mcall (MCallInfo& _info)
{
  ProcessAlgInfo              _icall_info;
  std::vector<IAlgImpl::ptr>* _pimpls = nullptr;
  MedianSpaceFilterProp::ptr  _impl_info;

  get_params (_info, _icall_info, _impl_info, &_pimpls);
  return (*_pimpls)[_info.indx_thread_]->process (_icall_info);
}


RangFilter::RangFilter () :
  ext_call_ (&store_call_)
{
  pthreads_ = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
  //  заполняем его исскуственно.
  ext_call_.set (ext_mcall);
  ext_call_.set_text ("dlls.filter_noise.space.impl.rang");
}


RangFilter::~RangFilter ()
{}


void
RangFilter::load_int ()
{
  return;
}


void
RangFilter::transform_int (InfoFilter& _finfo, ::libs::buffs::Buffs* _pbuff)
{
  XULOG_TRACE ("RangFilter::transform_int: beg");
  auto _impl_info = ::libs::iproperties::helpers::cast_event<MedianSpaceFilterProp> (_finfo.rprops_->impl_info_);

  if (!temp_src_buff_)
    {
      temp_src_buff_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_buffs_lockfree ()->impl ()->get ();
    }

  if (algs_.size () != pthreads_->get_count_threads ())
    {
      algs_.resize (pthreads_->get_count_threads ());

      std::for_each (
        algs_.begin (),
        algs_.end (),
        [this, &_finfo](IAlgImpl::ptr& _alg) {
          if (!_alg)
            {
              _alg = make_impl (_finfo);
            }
          return;
        });
    }

  for (const auto& _ibuff : _finfo.rprops_->buffs_)
    {
      if (!utils::dbuffs::video::consts::offs::is_valid (_ibuff))
        {
          UASSERT_SIGNAL ("failed");
          continue;
        }

      auto _sbuff = (*_pbuff)[_ibuff];

      if (!_sbuff || _sbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
        {
          continue;
        }

      AddTimeStatistic _sgrd (_finfo.expand_time_algs_, "one full buff " + _ibuff);
      const bool       _dbuff_valid = ::utils::dbuffs::video::consts::offs::is_valid (_finfo.rprops_->indx_cond_buff_);
      const auto       _indx_diff   = _dbuff_valid ? _finfo.rprops_->indx_cond_buff_ : utils::dbuffs::video::consts::offs::temp2;
      auto             _cdiff       = (*_pbuff)[_indx_diff];

      CHECK_STATE (_impl_info, "failed, empty impl info");
      CHECK_STATE (!_finfo.rprops_->use_cond_buff_ || ::utils::dbuffs::video::consts::offs::invalid != _indx_diff, "failed, invalid indx diff buffer");
      CHECK_STATE (!_finfo.rprops_->use_cond_buff_ || _cdiff, "failed, invalid diff buffer");

      utils::dbuffs::video::helpers::fill_convolution_edges (_sbuff);

      temp_src_buff_->clone (_sbuff, 0.0f);
      temp_src_buff_->swap (*_sbuff);

      _sbuff->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, (*temp_src_buff_)[::utils::dbuffs::TypeMemVar::size_data]);

      {
        ProxyBuff _src_dst (_sbuff);
        ProxyBuff _diff (_cdiff);
        ProxyBuff _src (temp_src_buff_.get ());
        MCallInfo _cinfo;

        _cinfo.srcs_.push_back (_src);
        _cinfo.srcs_.push_back (_diff);

        _cinfo.dsts_.push_back (_src_dst);

        _cinfo.params_.evals_.push_back (_impl_info);
        _cinfo.params_.evals_.push_back (&_finfo);
        _cinfo.params_.evals_.push_back (&algs_);

        ::libs::optim::mcalls::InfoMFunct _tfunct (&ext_call_);

        pthreads_->mcall (_tfunct, _cinfo);
      }
    }

  return;
}


IAlgImpl::ptr
RangFilter::make_impl (InfoFilter& _finfo)
{
  const auto _impl_info = ::libs::iproperties::helpers::cast_event<MedianSpaceFilterProp> (_finfo.rprops_->impl_info_);
  const auto _type      = _impl_info->sort_type_;
  //  самый часто используемый вариант сортировки, он же по умолчанию.
  if (TypeSortAlg::count == _type || TypeSortAlg::usual == _type)
    {
      return std::make_shared<vars::CountSortImpl> ();
    }

  if (TypeSortAlg::adaptive == _type)
    {
      return std::make_shared<vars::CountSortImpl> ();
    }

  if (TypeSortAlg::skip == _type)
    {
      return std::make_shared<vars::SkipSortImpl> ();
    }

  if (TypeSortAlg::standart == _type)
    {
      return std::make_shared<vars::StandartSortImpl> ();
    }

  if (TypeSortAlg::insert == _type)
    {
      return std::make_shared<vars::InsertSortImpl> ();
    }

  if (TypeSortAlg::rand == _type)
    {
      return std::make_shared<vars::RandSortImpl> ();
    }

  XULOG_WARNING("unknown type sort impl, " << UUU_ICAST_INT(_type));
  return std::make_shared<vars::CountSortImpl> ();
}

}}}}}      // namespace dlls::filter_noise::space::impl::rang
