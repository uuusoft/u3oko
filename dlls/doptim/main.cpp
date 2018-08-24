//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2017
\copyright  www.uuusoft.com
\project    uuu_doptim_dll
\brief      Основной файл модуля доступа к реализациям алгоритмов обработки данных.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mmedia/libs/helpers/log/android-log-functs.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::optim::io::IOptim::raw_ptr
create_impl ()
{
#ifdef UUU_OS_ANDROID
  static bool init_android_log = false;
  if (!init_android_log)
    {
      ::libs::helpers::log::android::init ();
      ::libs::helpers::log::android::Logger logger;
      SET_MODULE (logger, UUU_LOG_TAG);
      init_android_log = true;
    }
#endif
  static ::dlls::doptim::impl::IOptimImpl _ret;
  return &_ret;
}

BOOST_DLL_ALIAS (create_impl, instance_doptim);
