//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       main.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      Основной файл модуля логирования.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mmedia/libs/helpers/log/android-log-functs.hpp"

static std::mutex                                g_sinc;
static int                                       counter_refs_ = 0;
static ::libs::link::appl::IApplication::raw_ptr g_appl        = nullptr;

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication::raw_ptr
create_impl ()
{
  std::lock_guard<std::mutex> _grd (g_sinc);

  if (!g_appl)
    {
#ifdef UUU_OS_ANDROID
      ::libs::helpers::log::android::init ();
      ::libs::helpers::log::android::Logger logger;
      SET_MODULE (logger, UUU_LOG_TAG);
#endif
      g_appl = new ::modules::uuu_log::appl::LogModule;
    }

  ++counter_refs_;
  XULOG_TRACE ("::libs::link::appl::IApplication, " << to_str (counter_refs_) << ", " << to_str (g_appl));
  return g_appl;
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl (::libs::link::appl::IApplication::raw_ptr _appl)
{
  std::lock_guard<std::mutex> _grd (g_sinc);

  UASSERT (_appl);
  UASSERT (_appl == g_appl);
  UASSERT (g_appl);

  if (counter_refs_ <= 1)
    {
      delete g_appl;
      g_appl = nullptr;
#ifdef UUU_OS_ANDROID
      ::libs::helpers::log::android::deinit ();
#endif
    }

  --counter_refs_;
  return;
}

BOOST_DLL_ALIAS (create_impl, instance_iapplication);
BOOST_DLL_ALIAS (delete_impl, delete_iapplication);
