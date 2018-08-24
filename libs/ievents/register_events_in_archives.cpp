//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       register_events_in_archives.cpp
\date       10.02.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Файл с принудительной регистрацией событий в архивах, чтобы исключить вероятность их удаления при линковке.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "register_events_in_archives.hpp"

namespace libs { namespace ievents {

struct RegisterHelper
{
  void
  process () const
  {
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::TimedEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::Event);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::RuntimeEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::error::BaseErrorEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::mem::BuffsEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::mem::ZipDataEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::state::ChangStateProcessTypeEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::state::ExpandTimeStatisticEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::DetectViolation);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::FrameDone);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::video::FaceDetect);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::interf::BaseInterfEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::interf::InterfCorrectImageEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::runtime::interf::InterfCodecImageEvent);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::application::ApplicationProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::hardware::InfoCPUEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::mix_mul::MixMulProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::terminals::EndPointProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::base_id::BaseIdProp);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generic::morph::VideoMorphologyProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::codec::VideoCodecProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::convert::VideoConvertProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::convolution::VideoConvolutionProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::correct::VideoCorrectProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::detect::VideoDetectProp);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::driver::LinksVideoDriverProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::driver::VideoDriverProp);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::gradient::GradientProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::histogram::VideoHistogramProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::generics::motion_est::VideoEstMotionProp);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);

    UUU_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
    UUU_MAKE_FAKE_OBJ_THIS_TYPE (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
    return;
  }
};

void
register_events_in_archives ()
{
  static const RegisterHelper _helper;
  _helper.process ();
  return;
}

}}      // namespace libs::ievents
