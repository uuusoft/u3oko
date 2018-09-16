//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       events-impl-int-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2017
\copyright  www.uuusoft.com
\project    uuu_devents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "events-impl.hpp"

#ifndef ADD_EVENT_GENERATOR
#define ADD_EVENT_GENERATOR(event_type)                                               \
  XULOG_TRACE ("EventsImpl::construct: add gen event" << event_type::gen_get_mid ()); \
  gen_funct_events_[event_type::gen_get_mid ()] = []() {                              \
    return std::make_shared<event_type> ();                                           \
  };
#endif

#ifndef ADD_EVENT_CAST
#define ADD_EVENT_CAST(event_type)                                                                 \
  XULOG_TRACE ("EventsImpl::construct: add cast event" << event_type::gen_get_mid ());             \
  cast_funct_events_[event_type::gen_get_mid ()] = [](IEvent::craw_ptr _src) -> IEvent::craw_ptr { \
    event_type::craw_ptr _res = dynamic_cast<event_type::craw_ptr> (_src);                         \
    return _res;                                                                                   \
  };
#endif

#ifndef ADD_EVENT2ALL(event_type)
#define ADD_EVENT2ALL(event_type)   \
  ADD_EVENT_GENERATOR (event_type); \
  ADD_EVENT_CAST (event_type);
#endif

namespace dlls { namespace devents { namespace impl {

void
EventsImpl::construct ()
{
  XULOG_TRACE ("EventsImpl::construct: beg");
  gen_funct_events_.clear ();
  cast_funct_events_.clear ();

  ADD_EVENT2ALL (::libs::events::IAnswerEvent);
  //ADD_EVENT2ALL (::libs::events::IEvent);
  ADD_EVENT2ALL (::libs::events::IRequestEvent);
  ADD_EVENT2ALL (::libs::events::ISeqEvent);
  ADD_EVENT2ALL (::libs::events::ISyncEvent);
  ADD_EVENT2ALL (::libs::events::IWrapBaseEvent);

  ADD_EVENT2ALL (::libs::ievents::Event);
  ADD_EVENT2ALL (::libs::ievents::TimedEvent);
  ADD_EVENT2ALL (::libs::ievents::props::application::ApplicationProp);
  ADD_EVENT2ALL (::libs::ievents::props::base_id::BaseIdProp);
  ADD_EVENT2ALL (::libs::ievents::props::hardware::InfoCPUEvent);
  ADD_EVENT2ALL (::libs::ievents::props::mix_mul::MixMulProp);
  ADD_EVENT2ALL (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
  ADD_EVENT2ALL (::libs::ievents::props::modules::events::PropertyEventsModuleEvent);
  ADD_EVENT2ALL (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
  ADD_EVENT2ALL (::libs::ievents::props::terminals::EndPointProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::codec::VideoCodecProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::convert::VideoConvertProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::convolution::VideoConvolutionProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::correct::VideoCorrectProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::detect::VideoDetectProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::driver::LinksVideoDriverProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::driver::VideoDriverProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::gradient::GradientProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::histogram::VideoHistogramProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::motion_est::VideoEstMotionProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::scaler::VideoScalerProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::generics::vec2image::Vec2ImageProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::gens::diff::VideoDiffProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
  ADD_EVENT2ALL (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
  ADD_EVENT2ALL (::libs::ievents::runtime::RuntimeEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::error::BaseErrorEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::interf::BaseIdProp);
  ADD_EVENT2ALL (::libs::ievents::runtime::interf::BaseInterfEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::interf::InterfBaseIdEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::interf::InterfCodecImageEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::interf::InterfCorrectImageEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::interf::InterfCaptureImageEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::mem::BuffEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::mem::BuffsEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::mem::ZipDataEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::state::ChangStateProcessTypeEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::state::ExpandTimeStatisticEvent);
  ADD_EVENT2ALL (::libs::ievents::runtime::video::DetectViolation);
  ADD_EVENT2ALL (::libs::ievents::runtime::video::FaceDetect);
  ADD_EVENT2ALL (::libs::ievents::runtime::video::FrameDone);

  ADD_EVENT2ALL (::libs::ievents_events::events::BaseEventsEvent);
  ADD_EVENT2ALL (::libs::ievents_events::events::WrapperEventsEvent);
  ADD_EVENT2ALL (::libs::ievents_events::events::AddEvent2Base);
  ADD_EVENT2ALL (::libs::ievents_events::events::GetEventsFromBase);

  ADD_EVENT2ALL (::libs::ilog_events::events::ProcessListLogsEvent);
  ADD_EVENT2ALL (::libs::ilog_events::events::ProcessLogEvent);
  ADD_EVENT2ALL (::libs::ilog_events::events::BaseLogEvent);
  ADD_EVENT2ALL (::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent);
  ADD_EVENT2ALL (::libs::ilog_events::events::ExceptLogEvent);
  ADD_EVENT2ALL (::libs::ilog_events::events::InfoLogEvent);
  ADD_EVENT2ALL (::libs::ilog_events::events::WrapperLogEvent);

  ADD_EVENT2ALL (::libs::imdata_events::events::ListXmlFilesDataEvent);
  ADD_EVENT2ALL (::libs::imdata_events::events::ChangePathsDataEvent);
  ADD_EVENT2ALL (::libs::imdata_events::events::GetNodesDataEvent);
  ADD_EVENT2ALL (::libs::imdata_events::events::ListDevicesDataEvent);
  ADD_EVENT2ALL (::libs::imdata_events::events::ChangeNodeDataEvent);
  ADD_EVENT2ALL (::libs::imdata_events::events::BaseNodesDataEvent);
  ADD_EVENT2ALL (::libs::imdata_events::events::BaseDataEvent);

  ADD_EVENT2ALL (::libs::ihttp_events::events::MemResourceHttpEvent);
  ADD_EVENT2ALL (::libs::ihttp_events::events::BaseHttpEvent);
  ADD_EVENT2ALL (::libs::ihttp_events::events::WrapperHttpEvent);

  ADD_EVENT2ALL (::libs::istorage_events::events::BaseStorageEvent);
  ADD_EVENT2ALL (::libs::istorage_events::events::GetObjects);
  ADD_EVENT2ALL (::libs::istorage_events::events::GetRuntimeInfo);
  ADD_EVENT2ALL (::libs::istorage_events::events::GetStatisticInfo);
  ADD_EVENT2ALL (::libs::istorage_events::events::ReadData);
  ADD_EVENT2ALL (::libs::istorage_events::events::WriteData);
  ADD_EVENT2ALL (::libs::istorage_events::events::UpdateStream);
  ADD_EVENT2ALL (::libs::istorage_events::events::WrapperStorageEvent);
  ADD_EVENT2ALL (::libs::istorage_events::events::MemResourceStorageEvent);

  ADD_EVENT2ALL (::libs::igui_events::events::BaseGUIEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::CommandCodeEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::ExitApplEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::MemBlockEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::MouseButtonDownEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::MouseButtonUpEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::SizeChangedEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::UpdateDrawEvent);
  ADD_EVENT2ALL (::libs::igui_events::events::VideoBuffEvent);

  XULOG_TRACE ("EventsImpl::construct: end");
  return;
}

}}}      // namespace dlls::devents::impl
