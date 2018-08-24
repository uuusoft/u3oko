#pragma once
/**
\file       cat.hpp 
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace uids { namespace cat {
//  syn
using ::libs::helpers::utils::cuuid;

extern const cuuid cat_video_device;
extern const cuuid audio_devices;
extern const cuuid audio_compressors;
extern const cuuid audio_renderers;
extern const cuuid legacy_am_filters;
extern const cuuid midi_renders;
extern const cuuid video_compressors;

}}}}      // namespace libs::helpers::uids::cat
