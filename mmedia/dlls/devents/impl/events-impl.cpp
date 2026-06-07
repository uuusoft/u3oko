/**
\file       events-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2017
\project    u3_devents_dlls
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../generics-devents-includes_int.hpp"
#include "events-impl.hpp"

namespace dlls::devents::impl
{
EventsImpl::EventsImpl ()
{
  lock_type lock (mtx_);
  construct_func_event ();
}


syn::IEvent::ptr
EventsImpl::get (const hid_type& id)
{
  lock_type lock (mtx_);

  auto itf = gen_func_events_.find (id);
  if (gen_func_events_.end () == itf)
  {
    U3_XLOG_ERROR ("function for create id event not found" + TOLOG (id));
    return syn::IEvent::ptr ();
  }

  auto ret = itf->second ();
  U3_ASSERT (ret);
  ++counter_create_events_[id];

#ifdef U3_FAKE_DISABLE
  // debug
  if (counter_create_events_[id] >= 1024 && 0 == counter_create_events_[id] % 1024)
  {
    U3_XLOG_MARK ("dllevents" + TOLOG (id) + VTOLOG (counter_create_events_[id]));
  }
#endif
  return ret;
}


syn::IEvent::ptr
EventsImpl::clone (const syn::IEvent::craw_ptr src, const ::libs::events::Deeps& type)
{
  ++counter_clone_events_[src->gen_get_mid ()];
  return src->clone (type);
}


void*
EventsImpl::dcast (syn::IEvent::craw_ptr src, const hid_type& id)
{
  lock_type lock (mtx_);
  auto      itf = cast_func_events_.find (id);

  if (cast_func_events_.end () == itf)
  {
    U3_LOG_DATA_ERROR ("function for cast id event not found" + TOLOG (id));
    return nullptr;
  }

  auto ret = itf->second (src);
  return const_cast< libs::events::IEvent* > (ret);
}


bool
EventsImpl::event2xml (syn::IEvent::ptr& src, std::string& xml)
{
  U3_ASSERT (src);

  try
  {
    std::stringstream            istr;
    boost::archive::xml_oarchive xmla (istr, boost::archive::no_header);

    xmla& BOOST_SERIALIZATION_NVP (src);
    xml = istr.str ();
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what () + TOLOG (src->get_mid ()));
    return false;
  }
  return true;
}


bool
EventsImpl::xml2event (const std::string& xml, syn::IEvent::ptr& dst)
{
  std::stringstream            istr (xml);
  boost::archive::xml_iarchive xmla (istr, boost::archive::no_header);

  try
  {
    xmla >> BOOST_SERIALIZATION_NVP (dst);
    U3_ASSERT (dst);
    dst->sync_txt2val ();
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
    return false;
  }
  return true;
}


bool
EventsImpl::event2bin (syn::IEvent::ptr& src, std::ostream& bin)
{
  U3_ASSERT (src);

  try
  {
    boost::archive::binary_oarchive arc (bin);
    arc & src;
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what () + TOLOG (src->get_mid ()));
    return false;
  }
  return true;
}


bool
EventsImpl::bin2event (std::istream& bin, syn::IEvent::ptr& dst)
{
  boost::archive::binary_iarchive arc (bin);

  try
  {
    arc >> dst;
    U3_ASSERT (dst);
    dst->sync_txt2val ();
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
    return false;
  }
  return true;
}


void
EventsImpl::construct_func_event ()
{
  U3_ASSERT (gen_func_events_.empty ());
  U3_ASSERT (cast_func_events_.empty ());

  // add_event<::libs::events::IEvent);
  add_event< ::libs::events::IWrapBaseEvent > ();
  add_event< ::libs::events::IAnswerEvent > ();
  add_event< ::libs::events::IRequestEvent > ();
  add_event< ::libs::events::ISeqEvent > ();
  add_event< ::libs::events::ISyncEvent > ();


  add_event< ::libs::ievents::Event > ();
  add_event< ::libs::ievents::TimedEvent > ();
  add_event< ::libs::ievents::props::application::ApplicationProp > ();
  add_event< ::libs::ievents::props::base_id::BaseIdProp > ();
  add_event< ::libs::ievents::props::hardware::InfoCPUEvent > ();
  add_event< ::libs::ievents::props::mix_mul::MixMulProp > ();
  add_event< ::libs::ievents::props::modules::log::PropertyLogModuleEvent > ();
  add_event< ::libs::ievents::props::modules::events::PropertyEventsModuleEvent > ();
  add_event< ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent > ();
  add_event< ::libs::ievents::props::terminals::EndPointProp > ();
  add_event< ::libs::ievents::props::videos::generic::morph::VideoMorphologyProp > ();
  add_event< ::libs::ievents::props::videos::generic::codec::VideoCodecProp > ();
  add_event< ::libs::ievents::props::videos::generic::convert::VideoConvertProp > ();
  add_event< ::libs::ievents::props::videos::generic::convolution::VideoConvolutionProp > ();
  add_event< ::libs::ievents::props::videos::generic::correct::VideoCorrectProp > ();
  add_event< ::libs::ievents::props::videos::generic::detect::VideoDetectProp > ();
  add_event< ::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp > ();
  add_event< ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp > ();
  add_event< ::libs::ievents::props::videos::generic::driver::VideoDriverProp > ();
  add_event< ::libs::ievents::props::videos::generic::gradient::GradientProp > ();
  add_event< ::libs::ievents::props::videos::generic::histogram::VideoHistogramProp > ();
  add_event< ::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp > ();
  add_event< ::libs::ievents::props::videos::generic::scaler::VideoScalerProp > ();
  add_event< ::libs::ievents::props::videos::generic::vec2image::Vec2ImageProp > ();
  add_event< ::libs::ievents::props::videos::gens::diff::VideoDiffProp > ();
  add_event< ::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp > ();
  add_event< ::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp > ();
  add_event< ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp > ();
  add_event< ::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp > ();
  add_event< ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp > ();

  add_event< ::libs::ievents::runtime::RuntimeEvent > ();

  add_event< ::libs::ievents::runtime::error::BaseErrorEvent > ();

  add_event< ::libs::ievents::runtime::interf::BaseInterfEvent > ();
  add_event< ::libs::ievents::runtime::interf::InterfBaseIdEvent > ();
  add_event< ::libs::ievents::runtime::interf::InterfCodecImageEvent > ();
  add_event< ::libs::ievents::runtime::interf::InterfCorrectImageEvent > ();
  add_event< ::libs::ievents::runtime::interf::InterfCaptureImageEvent > ();

  add_event< ::libs::ievents::runtime::mem::BuffEvent > ();
  add_event< ::libs::ievents::runtime::mem::BufsEvent > ();
  add_event< ::libs::ievents::runtime::mem::ZipDataEvent > ();

  add_event< ::libs::ievents::runtime::state::ChangeStateProcessEvent > ();
  add_event< ::libs::ievents::runtime::state::ExpandTimesEvent > ();

  add_event< ::libs::ievents::runtime::video::DetectViolation > ();
  add_event< ::libs::ievents::runtime::video::FaceDetect > ();
  add_event< ::libs::ievents::runtime::video::FrameDone > ();
  add_event< ::libs::ievents::runtime::video::SystemSpecificDriverProp > ();

  add_event< ::libs::ievents_events::events::BaseEventsEvent > ();
  add_event< ::libs::ievents_events::events::WrapperEventsEvent > ();
  add_event< ::libs::ievents_events::events::AddEvent2Base > ();
  add_event< ::libs::ievents_events::events::GetEventsFromBase > ();
  add_event< ::libs::ievents_events::events::GetDataGraphsFromEventBase > ();
  add_event< ::libs::ievents_events::events::UpdateListener > ();

  add_event< ::libs::ilog_events::events::ProcessListLogsEvent > ();
  add_event< ::libs::ilog_events::events::ProcessLogEvent > ();
  add_event< ::libs::ilog_events::events::BaseLogEvent > ();
  add_event< ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent > ();
  add_event< ::libs::ilog_events::events::ExceptLogEvent > ();
  add_event< ::libs::ilog_events::events::InfoLogEvent > ();
  add_event< ::libs::ilog_events::events::WrapperLogEvent > ();

  add_event< ::libs::imdata_events::events::ListXmlFilesDataEvent > ();
  add_event< ::libs::imdata_events::events::ChangeGraphsDataEvent > ();
  add_event< ::libs::imdata_events::events::GetNodesDataEvent > ();
  add_event< ::libs::imdata_events::events::ListDevicesDataEvent > ();
  add_event< ::libs::imdata_events::events::ChangeNodeDataEvent > ();
  add_event< ::libs::imdata_events::events::BaseNodesDataEvent > ();
  add_event< ::libs::imdata_events::events::BaseDataEvent > ();

  add_event< ::libs::ihttp_events::events::MemResourceHttpEvent > ();
  add_event< ::libs::ihttp_events::events::BaseHttpEvent > ();
  add_event< ::libs::ihttp_events::events::WrapperHttpEvent > ();

  add_event< ::libs::istorage_events::events::BaseStorageEvent > ();
  add_event< ::libs::istorage_events::events::GetObjects > ();
  add_event< ::libs::istorage_events::events::GetRuntimeInfo > ();
  add_event< ::libs::istorage_events::events::GetStatisticInfo > ();
  add_event< ::libs::istorage_events::events::ReadData > ();
  add_event< ::libs::istorage_events::events::WriteData > ();
  add_event< ::libs::istorage_events::events::UpdateStream > ();
  add_event< ::libs::istorage_events::events::WrapperStorageEvent > ();
  add_event< ::libs::istorage_events::events::MemResourceStorageEvent > ();

  add_event< ::libs::igui_events::events::BaseGUIEvent > ();
  add_event< ::libs::igui_events::events::CommandCodeEvent > ();
  add_event< ::libs::igui_events::events::ExitApplEvent > ();
  add_event< ::libs::igui_events::events::MemBlockEvent > ();
  add_event< ::libs::igui_events::events::MouseButtonDownEvent > ();
  add_event< ::libs::igui_events::events::MouseButtonUpEvent > ();
  add_event< ::libs::igui_events::events::SizeChangedEvent > ();
  add_event< ::libs::igui_events::events::UpdateDrawEvent > ();
  add_event< ::libs::igui_events::events::VideoBufEvent > ();
}
}   // namespace dlls::devents::impl
