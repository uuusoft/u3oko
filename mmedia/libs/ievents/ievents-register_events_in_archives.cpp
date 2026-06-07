/**
\file       ievents-register_events_in_archives.cpp
\date       10.02.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "ievents-register_events_in_archives.hpp"

namespace libs::ievents
{
struct RegisterEventsHelper final {
  void
  process () const
  {
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::TimedEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::Event > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::RuntimeEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::error::BaseErrorEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::mem::BufsEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::mem::ZipDataEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::state::ChangeStateProcessEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::state::ExpandTimesEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::video::DetectViolation > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::video::FrameDone > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::video::FaceDetect > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::interf::BaseInterfEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::interf::InterfCorrectImageEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::interf::InterfCodecImageEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::control::SyncObjs > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::application::ApplicationProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::hardware::InfoCPUEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::mix_mul::MixMulProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::modules::log::PropertyLogModuleEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::modules::events::PropertyEventsModuleEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::terminals::EndPointProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::base_id::BaseIdProp > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::morph::VideoMorphologyProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::codec::VideoCodecProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::convert::VideoConvertProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::convolution::VideoConvolutionProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::correct::VideoCorrectProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::detect::VideoDetectProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::vec2image::Vec2ImageProp > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::driver::VideoDriverProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::runtime::video::SystemSpecificDriverProp > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::gradient::GradientProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::histogram::VideoHistogramProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp > ();

    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp > ();
    ::libs::iproperties::helpers::make_fake_obj_this_type< ::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover > ();
  }
};


void
register_events_in_archives ()
{
  static const RegisterEventsHelper helper;
  helper.process ();
}
}   // namespace libs::ievents
