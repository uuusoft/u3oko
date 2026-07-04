/**
\file       appls-u3oko-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3oko
\brief      Центральный модуль системы видеонаблюдения u3oko
*/
#include "appls-u3oko-includes_int.hpp"
#include "appl/u3oko-appl.hpp"

static std::mutex                                g_sinc;
static volatile std::int32_t                     counter_refs_ = 0;
static ::libs::link::appl::IApplication::raw_ptr g_appl        = nullptr;

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_appl_u3oko () -> ::libs::link::appl::IApplication::raw_ptr
{
  std::scoped_lock lock (g_sinc);

  if (!g_appl)
  {
    g_appl = new ::appls::u3oko::appl::U3OkoAppl;
  }

  counter_refs_ = counter_refs_ + 1;
  return g_appl;
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_appl_u3oko (::libs::link::appl::IApplication::raw_ptr appl)
{
  std::scoped_lock (g_sinc);
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
