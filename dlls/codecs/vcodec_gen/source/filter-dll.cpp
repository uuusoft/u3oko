//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace codecs { namespace vcodec_gen {

browser::CodecBrower Filter::codec_browser_;
ForeverLoadDlls      Filter::freez_impls_;

Filter::Filter () :
  external_codec_ (false)
{
  pthreads_ = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
}


Filter::~Filter ()
{}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);

  auto _ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  flip_y_ = _ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CFlipYAlg::val_key));
  sync_props2int ();
  return;
}


void
Filter::transform_int (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::transform_int: beg");
  prepare_transform (_info);
  process_events (_info);

  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      XULOG_TRACE ("Filter::transform_int: skip");
      return;
    }

  try
    {
      if (finfo_.rprops_->code_mirror_y_)
        {
          flip_y ((*pbuff_)[finfo_.rprops_->buffs_.indx_sbuff_]);
        }

      process_frame (_info);

      if (finfo_.rprops_->decode_mirror_y_)
        {
          flip_y ((*pbuff_)[finfo_.rprops_->buffs_.indx_dbuff_]);
        }
    }
  catch (boost::exception& _e)
    {
      DATA_EXCEPT_LOG (boost::diagnostic_information (_e));
    }
  catch (std::exception& _e)
    {
      DATA_EXCEPT_LOG (_e.what ());
    }
  XULOG_TRACE ("Filter::transform_int: end");
  return;
}      // namespace vcodec_gen


void
Filter::flip_y (IVideoBuff::raw_ptr _buff)
{
  if (!_buff)
    {
      XULOG_WARNING ("try flip empty buffer, skip");
      return;
    }

  ::libs::optim::MCallInfo          _cinfo;
  ::libs::optim::mcalls::InfoMFunct _tfunct (&flip_y_);

  _cinfo.dsts_.push_back (::libs::optim::io::ProxyBuff (_buff));
  pthreads_->mcall (_tfunct, _cinfo, 1);
  return;
}


void
Filter::process_events (TransformInfo& _info)
{
  if (!_info.pframe_events_)
    {
      return;
    }

  XULOG_TRACE ("Filter::process_events: _info.pframe_events_->size=" << _info.pframe_events_->size ());
  for (const auto& _event : *_info.pframe_events_)
    {
      const auto _devent = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::interf::InterfCodecImageEvent> (_event);
      if (_devent)
        {
          XULOG_TRACE ("Filter::process_events: update active codec");
          finfo_.active_impl_ = _devent->is_active () ? _devent->get_interface () : _devent->get_interface ();      //debug
          UASSERT (!finfo_.active_impl_.expired ());
          auto _impl = finfo_.active_impl_.lock ();
          if (_impl)
            {
              _impl->update_codec_property (finfo_.rprops_);
            }
          external_codec_ = true;
        }
    }
  return;
}


void
Filter::call_int (CallInterfInfo& _info)
{
  super::prepare_call (_info);
  super::call_gen (_info);
  return;
}


void
Filter::init_pts (ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::PointFilter::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
  return;
}


bool
Filter::prepare_process_frame (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::prepare_process_frame: beg");
  const bool                 _decode_mode = ::libs::ievents::props::videos::generics::codec::TypeCodecMode::decoder == finfo_.rprops_->plane_.type_;
  const IVideoBuff::craw_ptr _sbuff       = (*pbuff_)[finfo_.rprops_->buffs_.indx_sbuff_];
  const IVideoBuff::craw_ptr _dbuff       = (*pbuff_)[finfo_.rprops_->buffs_.indx_dbuff_];

  if (!_decode_mode && !finfo_.fps_.is_action ())
    {
      XULOG_TRACE ("Filter::prepare_process_frame: skip due to frequency");
      return false;
    }

  //  Проверяем на необходимость производить действие над входным буфером.
  if (!_sbuff || _sbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
    {
      XULOG_TRACE ("Filter::prepare_process_frame: null source buffer, skip, " << finfo_.rprops_->buffs_.indx_sbuff_);
      return false;
    }

  XULOG_TRACE ("Filter::prepare_process_frame: full source buffer, " << finfo_.rprops_->buffs_.indx_sbuff_);
  //  Недействительный буфер назначения не допустим в любом случае.
  if (!_dbuff)
    {
      XULOG_WARNING ("Filter::prepare_process_frame: null destination buffer, skip, " << finfo_.rprops_->buffs_.indx_dbuff_);
      return false;
    }

  const bool _dest_is_empty = _dbuff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty);

  switch (finfo_.rprops_->write_codec_strategy_)
    {
    case OverrideCodecDataType::write_if_empty:
      if (!_dest_is_empty)
        {
          XULOG_TRACE ("Filter::prepare_process_frame: skip due to strategy OverrideCodecDataType::write_if_empty");
          return false;
        }
      break;
    case OverrideCodecDataType::write_if_not_empty:
      if (_dest_is_empty)
        {
          XULOG_TRACE ("Filter::prepare_process_frame: skip due to strategy OverrideCodecDataType::write_if_not_empty");
          return false;
        }
      break;
    case OverrideCodecDataType::allways_write:
      break;
    default:
      XULOG_WARNING ("Filter::prepare_process_frame: unknown write strategy, " << UUU_ICAST_INT (finfo_.rprops_->write_codec_strategy_));
      break;
    }

  if (_decode_mode)
    {
      XULOG_TRACE ("Filter::prepare_process_frame: decode");
      const HeaderIFrame* _head = UUU_CODECS_CAST<const HeaderIFrame*> (utils::dbuffs::video::helpers::get_const_data (_sbuff));
      if (!_head || !_head->check ())
        {
          XULOG_WARNING ("Filter::process_frame: invalid source buffer for decode, skip");
          return false;
        }

      const cuuid _guid (_head->base_part_.guid_);
      finfo_.rprops_->name_idll_ = codec_browser_.get_codec (_guid);
    }

  if (!finfo_.file_info_.check ())
    {
      XULOG_TRACE ("Filter::prepare_process_frame: call update int");
      update_int ();
    }

  if (!finfo_.rcodec_)
    {
      XULOG_WARNING ("Filter::prepare_process_frame: failed, empty codec, skip");
      return false;
    }
  XULOG_TRACE ("Filter::prepare_process_frame: end");
  return true;
}


void
Filter::process_frame (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::process_frame: beg");
  if (!prepare_process_frame (_info))
    {
      XULOG_TRACE ("Filter::process_frame: skip");
      return;
    }

  const bool _decode_mode = ::libs::ievents::props::videos::generics::codec::TypeCodecMode::decoder == finfo_.rprops_->plane_.type_;
  if (_decode_mode)
    {
      XULOG_TRACE ("Filter::process_frame: call impl decode");
      finfo_.rcodec_->decode (pbuff_, pbuff_, _info.pframe_events_);
    }
  else
    {
      XULOG_TRACE ("Filter::process_frame: call impl code");
      finfo_.rcodec_->code (pbuff_, pbuff_, _info.pframe_events_);
    }

  if (finfo_.rprops_->dump_compressed_to_file_)
    {
      auto                      _indx_buff = _decode_mode ? finfo_.rprops_->buffs_.indx_sbuff_ : finfo_.rprops_->buffs_.indx_dbuff_;
      const IVideoBuff::raw_ptr _out_buff  = (*pbuff_)[_indx_buff];
      XULOG_INFO ("Filter::process_frame: dump buffer to file, " << _indx_buff);
      codec_gen::helpers::dump_buffer2file (_out_buff, std::string ("uuu_codec_test") + (_decode_mode ? "d_" : "c_") + to_str (finfo_.counter_frames_) + ".jpg");
    }

  ++finfo_.counter_frames_;

  if (finfo_.rprops_->dump_counter_frame_ > 0)
    {
      if (0 == (finfo_.counter_frames_ % finfo_.rprops_->dump_counter_frame_))
        {
          XULOG_TRACE ("Filter::process_frame: dump statistic to file");
          log_statistic ();
        }
    }
  XULOG_TRACE ("Filter::process_frame: end");
  return;
}


void
Filter::free_impl_lib ()
{
  if (!finfo_.file_info_.lib_)
    {
      return;
    }
  //delete object from old library
  if (finfo_.rcodec_)
    {
      UASSERT (finfo_.file_info_.pf_free_codec_);
      finfo_.file_info_.pf_free_codec_ (finfo_.rcodec_);
    }
  //  free old library
  finfo_.file_info_.reset ();
  finfo_.init ();
  return;
}


void
Filter::update_int ()
{
  XULOG_TRACE ("Filter::update_int: beg");
  free_impl_lib ();

  if (finfo_.rprops_->name_idll_.empty ())
    {
      XULOG_WARNING ("failed, empty name codec dll/so");
      return;
    }

  helpers::load_codec_from_file (
    ::libs::ievents::props::videos::generics::codec::TypeCodecMode::coder == finfo_.rprops_->plane_.type_,
    finfo_.rprops_->name_idll_,
    finfo_.file_info_);

  if (finfo_.file_info_.lib_)
    {
      freez_impls_.add (finfo_.rprops_->name_idll_, finfo_.file_info_.lib_);
    }

  UASSERT (!finfo_.rcodec_);
  finfo_.file_info_.pf_create_codec_ (&finfo_.rcodec_);

  {
    codec_gen::InfoGenCodec _iinfo;
    _iinfo.finfo_ = fbinfo_;
    finfo_.rcodec_->init (_iinfo);
  }

  finfo_.rcodec_->set_codec_info (finfo_.rprops_);
  XULOG_TRACE ("Filter::update_int: end");
  return;
}


void
Filter::log_statistic ()
{
  std::string                     _txt;
  const codec_gen::StatisticInfo& _info = finfo_.rcodec_->get_statistic_info ();

  UASSERT (_info.self_test ());
  _txt.reserve (2 * 1024);

  _txt = ::libs::ievents::props::videos::generics::codec::TypeCodecMode::coder == finfo_.rprops_->plane_.type_ ? "coder" : "decoder";
  _txt += ", frame ";
  _txt += to_str (finfo_.counter_frames_);
  _txt += "\n";

  for (const auto& _stage : _info.stages_)
    {
      UASSERT (_stage.second.self_test ());
      _txt += _stage.first;
      _txt += ":\t min ";
      _txt += to_str (_stage.second.size_datas_[0]);
      _txt += ", \t";
      _txt += "max ";
      _txt += to_str (_stage.second.size_datas_[1]);
      _txt += ", \t";
      _txt += "avr ";
      _txt += to_str (_stage.second.size_datas_[2] / finfo_.rprops_->dump_counter_frame_);
      _txt += "\n";
    }

  DATA_LOG (_txt);
  finfo_.rcodec_->reset_statistic_info ();
  return;
}


void
Filter::sync_props2int ()
{
  return;
}

}}}      // namespace dlls::codecs::vcodec_gen
