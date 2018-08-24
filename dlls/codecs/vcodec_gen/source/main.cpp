//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      Основной файл модуля кодирования.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"
#include "filter-dll.hpp"
#include "mmedia/android_log_functs.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl ()
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
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr _ret = new ::dlls::codecs::vcodec_gen::Filter;
  return _ret;
}
