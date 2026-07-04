/**
\file       events-base-register_events_in_archives.cpp
\date       10.02.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "events-base-includes_int.hpp"
#include "events-base-register_events_in_archives.hpp"

namespace libs::events_base
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::TimedEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::Event > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::RuntimeEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::error::BaseErrorEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::mem::BufsEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::mem::ZipDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::state::ChangeStateProcessEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::state::ExpandTimesEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::video::DetectViolation > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::video::FrameDone > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::video::FaceDetect > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::interf::BaseInterfEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::interf::InterfCorrectImageEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::interf::InterfCodecImageEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::control::SyncObjs > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::application::ApplicationProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::hardware::InfoCPUEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::mix_mul::MixMulProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::modules::log::PropertyLogModuleEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::modules::events::PropertyEventsModuleEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::modules::storage::PropertyStorageModuleEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::terminals::EndPointProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::base_id::BaseIdProp > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::morph::VideoMorphologyProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::codec::VideoCodecProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::convert::VideoConvertProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::convolution::VideoConvolutionProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::correct::VideoCorrectProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::detect::VideoDetectProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::vec2image::Vec2ImageProp > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::driver::VideoDriverProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::runtime::video::SystemSpecificDriverProp > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::gradient::GradientProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::histogram::VideoHistogramProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::generic::motion_est::VideoEstMotionProp > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::noises::space::VideoSpaceNoiseRemoverProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::noises::space::ext::MedianSpaceFilterProp > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::noises::time::VideoTimeNoiseRemoverProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::noises::time::ext::MedianTimeFilterProp > ();

  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::noises::freq::FreqVideoNoiseRemoverProp > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_base::props::videos::noises::freq::InfoBuffFreqNoiseRemover > ();
}
}   // namespace libs::events_base
