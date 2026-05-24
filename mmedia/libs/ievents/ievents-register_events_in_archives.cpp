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
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::TimedEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::Event);

#if defined(DEVENTS_COMPILE)
    // U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::wtf::WtfBase);
    // U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::wtf::WtfChild1);
#endif

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::RuntimeEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::error::BaseErrorEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::mem::BufsEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::mem::ZipDataEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::state::ChangeStateProcessEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::state::ExpandTimesEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::DetectViolation);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::FrameDone);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::FaceDetect);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::interf::BaseInterfEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::interf::InterfCorrectImageEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::interf::InterfCodecImageEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::control::SyncObjs);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::application::ApplicationProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::hardware::InfoCPUEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::mix_mul::MixMulProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::modules::events::PropertyEventsModuleEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::terminals::EndPointProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::base_id::BaseIdProp);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::codec::VideoCodecProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::convert::VideoConvertProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::convolution::VideoConvolutionProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::correct::VideoCorrectProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::detect::VideoDetectProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::vec2image::Vec2ImageProp);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::driver::VideoDriverProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::SystemSpecificDriverProp);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::gradient::GradientProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::histogram::VideoHistogramProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);

    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
    U3_HELPER_MAKE_FAKE_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
  }
};


void
register_events_in_archives ()
{
  static const RegisterEventsHelper helper;
  helper.process ();
}
}   // namespace libs::ievents
