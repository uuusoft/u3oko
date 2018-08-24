//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.06.2016.
\copyright  www.uuusoft.com
\project    uuu_fake_vgen
\brief      Основной файл модуля генерации фальшивых-тестовых данных.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "source-impl.hpp"
#include "mmedia/android_log_functs.hpp"

extern "C" BOOST_SYMBOL_EXPORT bool
get_source (::dlls::sources::gen_lib::ISourceImpl** _ret)
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
  UASSERT (_ret);
  UASSERT (!*_ret);
  *_ret = new ::dlls::sources::fake_vgen::SourceImpl ();
  return true;
}

extern "C" BOOST_SYMBOL_EXPORT bool
free_source (::dlls::sources::gen_lib::ISourceImpl** _ret)
{
  UASSERT (_ret);
  UASSERT (*_ret);
  delete *_ret;
  *_ret = nullptr;
  return true;
}
