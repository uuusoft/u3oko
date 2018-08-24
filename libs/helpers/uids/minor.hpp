#pragma once
/**
\file       minor.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      ќбъ€вление известных/поддерживаемых системой форматов данных.
*/

namespace libs { namespace helpers { namespace uids { namespace minor {
//  syn
using ::libs::helpers::utils::cuuid;

extern const cuuid unknow;
extern const cuuid device_specific;
extern const cuuid y8;
extern const cuuid y16;
extern const cuuid i420;
extern const cuuid yuy2;
extern const cuuid ycb;
extern const cuuid uyvy;
extern const cuuid rgb24;
extern const cuuid rgb555;
extern const cuuid rgb565;
extern const cuuid rgb8;
extern const cuuid rgb32;
extern const cuuid iyuv;
extern const cuuid yv12;
extern const cuuid yvu9;
extern const cuuid yuyv;
extern const cuuid y211;
extern const cuuid if09;
extern const cuuid nv21;

extern const cuuid mjpg;
extern const cuuid x264;

}}}}      // namespace libs::helpers::uids::minor
