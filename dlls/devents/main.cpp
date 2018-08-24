//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2017
\copyright  www.uuusoft.com
\project    uuu_devents
\brief      Основной файл модуля для преобразования идентификатора в нативный объект "событие системы".
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "impl/events-impl.hpp"
#include "mmedia/android_log_functs.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::events::io::IEvents::raw_ptr
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
  static ::dlls::devents::impl::EventsImpl _ret;
  return &_ret;
}

BOOST_DLL_ALIAS (create_impl, instance_devents);
