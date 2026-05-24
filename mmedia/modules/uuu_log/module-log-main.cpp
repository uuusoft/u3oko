/**
\file       module-log-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_log
\brief      Модуль логирования
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "module-log-includes_int.hpp"

static std::mutex                                g_sinc;
static volatile std::int32_t                     counter_refs_ = 0;
static ::libs::link::appl::IApplication::raw_ptr g_appl        = nullptr;

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication::raw_ptr
create_impl_mpl_uuu_log ()
{
  std::lock_guard< std::mutex > lock (g_sinc);

  if (!g_appl)
  {
    g_appl = new ::modules::uuu_log::appl::LogModule;
  }

  counter_refs_ = counter_refs_ + 1;
  return g_appl;
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_uuu_log (::libs::link::appl::IApplication::raw_ptr appl)
{
  std::lock_guard< std::mutex > lock (g_sinc);

  U3_ASSERT_NT (appl, PTR_TOLOG (appl));
  U3_ASSERT_NT (appl == g_appl, PTR_TOLOG (appl));
  U3_ASSERT_NT (g_appl, PTR_TOLOG (g_appl));

  if (counter_refs_ <= 1)
  {
    delete g_appl;
    g_appl = nullptr;
  }

  counter_refs_ = counter_refs_ - 1;
}
