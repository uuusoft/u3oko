/**
\file       events-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2017
\project    u3_devents_dlls
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../generics-devents-includes_int.hpp"
#include "events-impl.hpp"

namespace dlls::devents::impl
{
EventsImpl::EventsImpl ()
{
  U3_XLOG_DBG ("EventsImpl::EventsImpl::---->");
  lock_type lock (mtx_);
  make_event_funcs ();
}


auto
EventsImpl::get (const hid_type& eid) -> syn::IEvent::ptr
{
  U3_XLOG_DBG ("EventsImpl::get::---->" + STOLOG (eid));
  lock_type lock (mtx_);
  auto      itf = gen_func_events_.find (id_event_type { eid });
  if (gen_func_events_.end () == itf)
  {
    U3_XLOG_ERROR ("function for create event by id not found" + STOLOG (eid));
    return {};
  }

  auto ret = itf->second ();
  U3_ASSERT (ret);
  ++counter_create_events_[id_event_type { eid }];

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // debug
  if (counter_create_events_[id] >= 1024 && 0 == counter_create_events_[id] % 1024)
  {
    U3_XLOG_MARK ("dllevents" + STOLOG (id) + VTOLOG (counter_create_events_[id]));
  }
#endif
  U3_XLOG_DBG ("EventsImpl::get::<----" + STOLOG (eid) + PTR_TOLOG (ret.get ()));
  return ret;
}


auto
EventsImpl::clone (const syn::IEvent::craw_ptr src, const ::libs::events::Deeps& type) -> syn::IEvent::ptr
{
  ++counter_clone_events_[id_event_type { src->gen_get_mid () }];
  return src->clone (type);
}

#if 0
void*
EventsImpl::dcast (syn::IEvent::raw_ptr src, const hid_type& eid)
{
  lock_type lock (mtx_);

  auto itf = cast_func_events_.find (id_event_type { eid });
  if (cast_func_events_.end () == itf)
  {
    U3_LOG_DATA_ERROR ("function for cast id event not found" + STOLOG (eid) + PTR_TOLOG (this));
    return nullptr;
  }

  auto ret = itf->second (src);
  return ret;
  // return const_cast< libs::events::IEvent* > (ret);
}
#endif

auto
EventsImpl::dcast (syn::IEvent::craw_ptr src, const hid_type& eid) -> const void*
{
  lock_type lock (mtx_);

  auto itf = cast_func_events_.find (id_event_type { eid });
  if (cast_func_events_.end () == itf)
  {
    U3_LOG_DATA_ERROR ("function for cast id event not found" + STOLOG (eid) + PTR_TOLOG (this));
    return nullptr;
  }

  auto ret = itf->second (src);
  return ret;
  // return const_cast< libs::events::IEvent* > (ret);
}


auto
EventsImpl::event2xml (syn::IEvent::ptr& src, std::string& xml) -> bool
{
  U3_ASSERT (src);
  try
  {
    std::stringstream            istr;
    boost::archive::xml_oarchive xmla (istr, boost::archive::no_header);

    xmla& BOOST_SERIALIZATION_NVP (src);
    xml = istr.str ();
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what () + STOLOG (src->get_mid ()));
    return false;
  }
  return true;
}


auto
EventsImpl::xml2event (const std::string& xml, syn::IEvent::ptr& dst) -> bool
{
  std::stringstream            istr (xml);
  boost::archive::xml_iarchive xmla (istr, boost::archive::no_header);

  try
  {
    xmla >> BOOST_SERIALIZATION_NVP (dst);
    U3_ASSERT (dst);
    dst->sync_txt2val ();
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
    return false;
  }
  return true;
}


auto
EventsImpl::event2bin (syn::IEvent::ptr& src, std::ostream& bin) -> bool
{
  U3_ASSERT (src);
  try
  {
    boost::archive::binary_oarchive arc (bin);
    arc & src;
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what () + STOLOG (src->get_mid ()));
    return false;
  }
  return true;
}


auto
EventsImpl::bin2event (std::istream& bin, syn::IEvent::ptr& dst) -> bool
{
  boost::archive::binary_iarchive arc (bin);
  try
  {
    arc >> dst;
    U3_ASSERT (dst);
    dst->sync_txt2val ();
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
    return false;
  }
  return true;
}


auto
EventsImpl::dbg_state_dump () -> void
{
  U3_XLOG_DEV ("EventsImpl::dbg_state_dump::---->");
  for (const auto& [eid, efunc] : cast_func_events_)
  {
    U3_XLOG_DEV (FSTOLOG (eid));
  }
}


void
EventsImpl::make_event_funcs ()
{
  U3_ASSERT (gen_func_events_.empty ());
  U3_ASSERT (cast_func_events_.empty ());

  // add_event<::libs::events::IEvent);
  add_event< ::libs::events::IWrapBaseEvent > ();
  add_event< ::libs::events::IAnswerEvent > ();
  add_event< ::libs::events::IRequestEvent > ();
  add_event< ::libs::events::ISeqEvent > ();
  add_event< ::libs::events::ISyncEvent > ();

  add_event< ::libs::events_base::Event > ();
  add_event< ::libs::events_base::TimedEvent > ();
  add_event< ::libs::events_base::OpsStatusEvent > ();
  add_event< ::libs::events_base::UserIdEvent > ();
  add_event< ::libs::events_base::props::application::ApplicationProp > ();

  add_event< ::libs::events_base::props::base_id::BaseIdProp > ();
  add_event< ::libs::events_base::props::hardware::InfoCPUEvent > ();
  add_event< ::libs::events_base::props::mix_mul::MixMulProp > ();
  add_event< ::libs::events_base::props::modules::log::PropertyLogModuleEvent > ();
  add_event< ::libs::events_base::props::modules::events::PropertyEventsModuleEvent > ();
  add_event< ::libs::events_base::props::modules::storage::PropertyStorageModuleEvent > ();
  add_event< ::libs::events_base::props::terminals::EndPointProp > ();
  add_event< ::libs::events_base::props::videos::generic::morph::VideoMorphologyProp > ();
  add_event< ::libs::events_base::props::videos::generic::codec::VideoCodecProp > ();
  add_event< ::libs::events_base::props::videos::generic::convert::VideoConvertProp > ();
  add_event< ::libs::events_base::props::videos::generic::convolution::VideoConvolutionProp > ();
  add_event< ::libs::events_base::props::videos::generic::correct::VideoCorrectProp > ();
  add_event< ::libs::events_base::props::videos::generic::detect::VideoDetectProp > ();
  add_event< ::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp > ();
  add_event< ::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp > ();
  add_event< ::libs::events_base::props::videos::generic::driver::VideoDriverProp > ();
  add_event< ::libs::events_base::props::videos::generic::gradient::GradientProp > ();
  add_event< ::libs::events_base::props::videos::generic::histogram::VideoHistogramProp > ();
  add_event< ::libs::events_base::props::videos::generic::motion_est::VideoEstMotionProp > ();
  add_event< ::libs::events_base::props::videos::generic::scaler::VideoScalerProp > ();
  add_event< ::libs::events_base::props::videos::generic::vec2image::Vec2ImageProp > ();
  add_event< ::libs::events_base::props::videos::gens::diff::VideoDiffProp > ();
  add_event< ::libs::events_base::props::videos::noises::freq::FreqVideoNoiseRemoverProp > ();
  add_event< ::libs::events_base::props::videos::noises::space::VideoSpaceNoiseRemoverProp > ();
  add_event< ::libs::events_base::props::videos::noises::space::ext::MedianSpaceFilterProp > ();
  add_event< ::libs::events_base::props::videos::noises::time::VideoTimeNoiseRemoverProp > ();
  add_event< ::libs::events_base::props::videos::noises::time::ext::MedianTimeFilterProp > ();

  add_event< ::libs::events_base::runtime::RuntimeEvent > ();

  add_event< ::libs::events_base::runtime::error::BaseErrorEvent > ();

  add_event< ::libs::events_base::runtime::interf::BaseInterfEvent > ();
  add_event< ::libs::events_base::runtime::interf::InterfBaseIdEvent > ();
  add_event< ::libs::events_base::runtime::interf::InterfCodecImageEvent > ();
  add_event< ::libs::events_base::runtime::interf::InterfCorrectImageEvent > ();
  add_event< ::libs::events_base::runtime::interf::InterfCaptureImageEvent > ();

  add_event< ::libs::events_base::runtime::mem::BuffEvent > ();
  add_event< ::libs::events_base::runtime::mem::BufsEvent > ();
  add_event< ::libs::events_base::runtime::mem::ZipDataEvent > ();

  add_event< ::libs::events_base::runtime::state::ChangeStateProcessEvent > ();
  add_event< ::libs::events_base::runtime::state::ExpandTimesEvent > ();

  add_event< ::libs::events_base::runtime::video::DetectViolation > ();
  add_event< ::libs::events_base::runtime::video::FaceDetect > ();
  add_event< ::libs::events_base::runtime::video::FrameDone > ();
  add_event< ::libs::events_base::runtime::video::SystemSpecificDriverProp > ();

  add_event< ::libs::events_msg::events::BaseEventsMsg > ();
  add_event< ::libs::events_msg::events::WrapperEventsEvent > ();
  add_event< ::libs::events_msg::events::AddEvent2EventsMsg > ();
  add_event< ::libs::events_msg::events::GetEventsFromBase > ();
  add_event< ::libs::events_msg::events::GetDataGraphsEventsMsg > ();
  add_event< ::libs::events_msg::events::UpdateListenerEventsMsg > ();

  add_event< ::libs::events_log::events::ProcessListLogsEvent > ();
  add_event< ::libs::events_log::events::ProcessLogEvent > ();
  add_event< ::libs::events_log::events::BaseLogEvent > ();
  add_event< ::libs::events_log::events::ChangeStateSubSysLogEvent > ();
  add_event< ::libs::events_log::events::ExceptLogEvent > ();
  add_event< ::libs::events_log::events::InfoLogEvent > ();
  add_event< ::libs::events_log::events::WrapperLogEvent > ();

  add_event< ::libs::events_media::events::ListXmlFilesDataEvent > ();
  add_event< ::libs::events_media::events::ChangeGraphsDataEvent > ();
  add_event< ::libs::events_media::events::GetNodesDataEvent > ();
  add_event< ::libs::events_media::events::ListDevicesDataEvent > ();
  add_event< ::libs::events_media::events::ChangeNodeDataEvent > ();
  add_event< ::libs::events_media::events::BaseNodesDataEvent > ();
  add_event< ::libs::events_media::events::BaseDataEvent > ();

  add_event< ::libs::events_http::events::MemResourceHttpEvent > ();
  add_event< ::libs::events_http::events::BaseHttpEvent > ();
  add_event< ::libs::events_http::events::WrapperHttpEvent > ();

  add_event< ::libs::events_storage::events::BaseStorageEvent > ();
  add_event< ::libs::events_storage::events::GetObjects > ();
  add_event< ::libs::events_storage::events::GetRuntimeInfo > ();
  add_event< ::libs::events_storage::events::GetStatisticInfo > ();
  add_event< ::libs::events_storage::events::ReadData > ();
  add_event< ::libs::events_storage::events::WriteData > ();
  add_event< ::libs::events_storage::events::UpdateStream > ();
  add_event< ::libs::events_storage::events::WrapperStorageEvent > ();
  add_event< ::libs::events_storage::events::MemResourceStorageEvent > ();

  add_event< ::libs::events_gui::events::BaseGUIEvent > ();
  add_event< ::libs::events_gui::events::CommandCodeEvent > ();
  add_event< ::libs::events_gui::events::ExitApplEvent > ();
  add_event< ::libs::events_gui::events::MemBlockEvent > ();
  add_event< ::libs::events_gui::events::MouseButtonDownEvent > ();
  add_event< ::libs::events_gui::events::MouseButtonUpEvent > ();
  add_event< ::libs::events_gui::events::SizeChangedEvent > ();
  add_event< ::libs::events_gui::events::UpdateDrawEvent > ();
  add_event< ::libs::events_gui::events::VideoBufEvent > ();

  // dbg_state_dump ();
}
}   // namespace dlls::devents::impl
