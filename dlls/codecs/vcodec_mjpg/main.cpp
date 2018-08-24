//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_mjpg
\brief      Основной файл кодека MJPEG.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/android_log_functs.hpp"

extern "C" BOOST_SYMBOL_EXPORT void
create_codec (::dlls::codecs::codec_gen::CodecGeneric** _pobj)
{
#ifdef UUU_OS_ANDROID
  static bool init_android_log = false;
  if (!init_android_log)
    {
      log::android::init ();
      log::android::Logger logger;
      SET_MODULE (logger, UUU_LOG_TAG);
      init_android_log = true;
    }
#endif
  UASSERT (nullptr == *_pobj);
  *_pobj = new ::dlls::codecs::vcodec_mjpg::MjpegImpl;
  return;
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_codec (::dlls::codecs::codec_gen::CodecGeneric* _obj)
{
  ::dlls::codecs::vcodec_mjpg::MjpegImpl* _del = dynamic_cast<::dlls::codecs::vcodec_mjpg::MjpegImpl*> (_obj);
  delete _del;
  _del = nullptr;
  return;
}

extern "C" BOOST_SYMBOL_EXPORT void
get_codec_info (::libs::helpers::utils::cuuid* _guid)
{
  *_guid = ::libs::helpers::uids::codecs::mjpeg;
  return;
}
