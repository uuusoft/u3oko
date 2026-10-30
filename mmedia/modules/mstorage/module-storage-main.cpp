/**
\file       module-storage-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\brief      Модуль хранения данных
*/
#include "module-storage-includes_int.hpp"

static std::mutex                                g_sinc;
static volatile std::int32_t                     counter_refs_ = 0;
static ::libs::link::appl::IApplication::raw_ptr g_appl        = nullptr;

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_mpl_mstorage () -> ::libs::link::appl::IApplication::raw_ptr
{
  std::scoped_lock lock (g_sinc);

  if (!g_appl)
  {
    g_appl = new ::modules::mstorage::appl::StorageModule;
  }

  counter_refs_ = counter_refs_ + 1;
  return g_appl;
}


extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_mstorage (::libs::link::appl::IApplication::raw_ptr appl)
{
  std::scoped_lock lock (g_sinc);

  ::libs::utility::checks::assert_soft (appl, PTR_TOLOG (appl));
  ::libs::utility::checks::assert_soft (appl == g_appl, PTR_TOLOG (appl));
  ::libs::utility::checks::assert_soft (g_appl, PTR_TOLOG (g_appl));

  if (counter_refs_ <= 1)
  {
    delete g_appl;
    g_appl = nullptr;
  }

  counter_refs_ = counter_refs_ - 1;
}
