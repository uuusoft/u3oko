#pragma once
/**
\file       codecs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Перечисление идентификаторов доступных кодеков в системе.
*/

namespace libs { namespace helpers { namespace uids { namespace codecs {
//  syn
using ::libs::helpers::utils::cuuid;

extern const cuuid any_codec;      //< ???
extern const cuuid mjpeg;          //< ???
extern const cuuid mjpg1;          //< ???
extern const cuuid mjpg2;          //< ???
extern const cuuid mjpg4;          //< ???
extern const cuuid x264;           //< ???
extern const cuuid x265;           //< ???
extern const cuuid test;           //< ???
extern const cuuid vp7;            //< ???
extern const cuuid vp9;            //< ???

extern const cuuid mp3;         //< ???
extern const cuuid aac;         //< ???
extern const cuuid ogg;         //< ???
extern const cuuid ilbc;        //< ???
extern const cuuid g723_1;      //< ???

}}}}      // namespace libs::helpers::uids::codecs
