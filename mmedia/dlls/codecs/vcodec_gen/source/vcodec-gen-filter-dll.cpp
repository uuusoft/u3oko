/**
\file       vcodec-gen-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_gen
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "vcodec-gen-includes_int.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"
#include "vcodec-gen-filter-dll.hpp"

namespace dlls::codecs::vcodec_gen
{
browser::CodecBrower               Filter::codec_browser_;
::libs::utility::dlls::FreezerDlls Filter::frozen_dlls_;

Filter::Filter ()
{
  pthreads_ = ::libs::iproperties::helpers::get_shared_prop_os ()->get_mcalls_lockfree ();
}


Filter::~Filter ()
{
  free_impl_lib ();
}


void
Filter::load_int (
  ::libs::icore::impl::var1::obj::FilterInfo* info,
  const ::pugi::xml_named_node_iterator&      node)
{
  init_pts (&info->pts_);
  finfo_.load (node);

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  flip_y_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CFlipYAlg::val_key));
  sync_props2int ();
}


void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  process_events (info);

  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  try
  {
    if (finfo_.rprops_->code_flip_y_)
    {
      flip_y ((*pbuf_)[finfo_.rprops_->bufs_.indx_sbuf_]);
    }

    process_frame (info);

    if (finfo_.rprops_->decode_flip_y_)
    {
      flip_y ((*pbuf_)[finfo_.rprops_->bufs_.indx_dbuf_]);
    }
  }
  catch (U3_MARK_UNUSED boost::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (boost::diagnostic_information (excpt));
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
}


void
Filter::flip_y (syn::IVideoBuf::raw_ptr buf)
{
  if (!buf)
  {
    U3_LOG_DATA_WRN ("try flip empty buf, skip");
    return;
  }

  ::libs::optim::io::MCallInfo      cinfo;
  ::libs::optim::mcalls::MTFuncInfo tfunc (&flip_y_);

  cinfo.dsts_.emplace_back (buf, "Filter::flip_y");

  pthreads_->mthreads_call (
    id_obj_,
    tfunc,
    cinfo,
    transinfo_->exptimes_,
    1);
}


void
Filter::process_events (syn::TransformInfo& info)
{
  if (!info.frame_events_)
  {
    return;
  }

  for (const auto& event : *info.frame_events_)
  {
    auto* devent = ::libs::iproperties::helpers::cast_event< syn::InterfCodecImageEvent > (event);
    if (devent)
    {
      finfo_.active_codec_impl_ = devent->is_active () ? devent->get_interface () : devent->get_interface ();   // debug
      U3_ASSERT (!finfo_.active_codec_impl_.expired ());
      auto impl = finfo_.active_codec_impl_.lock ();
      if (impl)
      {
        impl->update_codec_property (finfo_.rprops_);
      }
      external_codec_ = true;
    }
  }
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


auto
Filter::prepare_process_frame (syn::TransformInfo& info) -> bool
{
  const bool                     decode = ::libs::events_base::props::videos::generic::codec::CodecModes::decoder == finfo_.rprops_->plane_.type_;
  const syn::IVideoBuf::craw_ptr sbuf   = (*pbuf_)[finfo_.rprops_->bufs_.indx_sbuf_];
  const syn::IVideoBuf::craw_ptr dbuf   = (*pbuf_)[finfo_.rprops_->bufs_.indx_dbuf_];

  if (!decode && !finfo_.fps_.is_action ())
  {
    return false;
  }
  //  Проверяем на необходимость производить действие над входным буфером.
  if (!sbuf || sbuf->get_flag (::utils::dbufs::BufFlags::empty))
  {
    return false;
  }
  //  Недействительный буфер назначения не допустим в любом случае.
  if (!dbuf)
  {
    U3_LOG_DATA_WRN ("null destination buf, skip" + TOLOG (finfo_.rprops_->bufs_.indx_dbuf_));
    return false;
  }

  const auto dst_empty = dbuf->get_flag (::utils::dbufs::BufFlags::empty);
  switch (finfo_.rprops_->write_codec_strategy_)
  {
  case syn::Writes::write_if_empty: {
    if (!dst_empty)
    {
      return false;
    }
    break;
  }
  case syn::Writes::write_if_not_empty: {
    if (dst_empty)
    {
      return false;
    }
    break;
  }
  case syn::Writes::allways_write: {
    break;
  }
  default: {
    U3_LOG_DATA_WRN ("unknown write strategy" + VTOLOG (U3_CAST_UINT32_FORCE (finfo_.rprops_->write_codec_strategy_)));
    break;
  }
  }

  if (decode)
  {
    const auto* head = ::libs::utility::casts::reinterpret_cast_helper< const syn::HeaderIFrame* > (utils::dbufs::video::helpers::get_const_data (sbuf));
    if (!head || !head->check ())
    {
      U3_LOG_DATA_WRN ("invalid source buf for decode, skip");
      return false;
    }

    finfo_.rprops_->dll_name_ = codec_browser_.get_codec (head->base_part_.guid_);
  }

  if (!finfo_.file_info_.check ())
  {
    update_int ();
  }

  if (!finfo_.dll_codec_)
  {
    U3_LOG_DATA_WRN ("empty codec, skip");
    return false;
  }
  return true;
}


void
Filter::process_frame (syn::TransformInfo& info)
{
  if (!prepare_process_frame (info))
  {
    return;
  }

  finfo_.dll_codec_->set_transform_info (&id_obj_, transinfo_);

  const bool decode = ::libs::events_base::props::videos::generic::codec::CodecModes::decoder == finfo_.rprops_->plane_.type_;
  if (decode)
  {
    finfo_.dll_codec_->decode (pbuf_, pbuf_, info.frame_events_);
  }
  else
  {
    finfo_.dll_codec_->code (pbuf_, pbuf_, info.frame_events_);
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    // EAI-DEBUG
    {
      U3_LOG_DATA_DBG ("debug->copy frame for send to storage");
      const syn::IVideoBuf::raw_ptr in_buf  = (*pbuf_)[finfo_.rprops_->bufs_.indx_dbuf_];
      const syn::IVideoBuf::raw_ptr out_buf = (*pbuf_)[::utils::dbufs::video::consts::offs::storage];
      out_buf->clone (in_buf, 100.0F);
    }
#endif
  }

  finfo_.dll_codec_->set_transform_info (nullptr, nullptr);

  if (finfo_.rprops_->dump_result2file_)
  {
    auto       indx_buf  = decode ? finfo_.rprops_->bufs_.indx_sbuf_ : finfo_.rprops_->bufs_.indx_dbuf_;
    const auto out_buf   = (*pbuf_)[indx_buf];
    const auto file_name = std::string ("u3_vcodec_test") + (decode ? "d_" : "c_") + std::to_string (finfo_.counter_frames_) + ".jpg";

    U3_LOG_DATA_DEV ("dump codec output" + TOLOG (file_name));
    codec_gen::helpers::dump_buf2file (out_buf, file_name);
  }

  ++finfo_.counter_frames_;

  if (finfo_.rprops_->dump_counter_frame_ > 0)
  {
    if (0 == (finfo_.counter_frames_ % finfo_.rprops_->dump_counter_frame_))
    {
      log_statistic ();
    }
  }
}


void
Filter::free_impl_lib () noexcept
{
  try
  {
    active_dll_name_.clear ();

    if (!finfo_.file_info_.lib_)
    {
      return;
    }

    // delete object from old library
    if (finfo_.dll_codec_)
    {
      U3_ASSERT (finfo_.file_info_.free_codec_);
      finfo_.file_info_.free_codec_ (finfo_.dll_codec_);
      finfo_.dll_codec_ = nullptr;
    }

    //  free old library
    finfo_.file_info_.reset ();
    // U3-TODO
    // finfo_.init (); // не работает в режиме libs only ломает работу
  }
  catch (...)
  {
    U3_LOG_DATA_EXCEPT ("...");
  }
}


void
Filter::sync_by_events (bool update)
{
  if (!update)
  {
    return;
  }

  if (finfo_.rprops_->dll_name_ != active_dll_name_)
  {
    update_int ();
  }
}


void
Filter::update_int ()
{
  free_impl_lib ();

  if (finfo_.rprops_->dll_name_.empty ())
  {
    U3_LOG_DATA_WRN ("empty name codec dll/so");
    return;
  }

  U3_LOG_DATA_DEV ("load codec" + TOLOG (finfo_.rprops_->dll_name_));
  helpers::load_codec_from_file (
    ::libs::events_base::props::videos::generic::codec::CodecModes::coder == finfo_.rprops_->plane_.type_,
    finfo_.rprops_->dll_name_,
    finfo_.file_info_);

  if (finfo_.file_info_.lib_)
  {
    frozen_dlls_.add (finfo_.rprops_->dll_name_, finfo_.file_info_.lib_);
  }

  finfo_.file_info_.create_codec_ (&finfo_.dll_codec_);
  U3_CHECK (finfo_.dll_codec_, "create codec" + finfo_.rprops_->dll_name_);

  {
    codec_gen::InfoGenCodec iinfo;
    iinfo.codec_finfo_ = fbinfo_;
    finfo_.dll_codec_->init (iinfo);
  }

  finfo_.dll_codec_->set_codec_info (finfo_.rprops_);
  active_dll_name_ = finfo_.rprops_->dll_name_;
}


void
Filter::log_statistic ()
{
  std::string                     txt;
  const codec_gen::StatisticInfo& info = finfo_.dll_codec_->get_statistic_info ();

  U3_ASSERT (info.self_test ());
  txt.reserve (static_cast< std::string::size_type > (2 * 1024));

  txt = ::libs::events_base::props::videos::generic::codec::CodecModes::coder == finfo_.rprops_->plane_.type_ ? "coder" : "decoder";
  txt += ", frame ";
  txt += std::to_string (finfo_.counter_frames_);
  txt += "\n";

  for (const auto& stage : info.stages_)
  {
    U3_ASSERT (stage.second.self_test ());
    txt += stage.first;
    txt += ":\t min ";
    txt += std::to_string (stage.second.size_datas_[0]);
    txt += ", \t";
    txt += "max ";
    txt += std::to_string (stage.second.size_datas_[1]);
    txt += ", \t";
    txt += "avr ";
    txt += std::to_string (stage.second.size_datas_[2] / finfo_.rprops_->dump_counter_frame_);
    txt += "\n";
  }

  U3_LOG_DATA_INFO (txt);
  finfo_.dll_codec_->reset_statistic_info ();
}


void
Filter::sync_props2int ()
{
}
}   // namespace dlls::codecs::vcodec_gen
