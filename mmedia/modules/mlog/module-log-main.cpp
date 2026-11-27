/**
\file       module-log-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\brief      Модуль логирования
*/
#include "-module-log-includes-int.hpp"

static std::mutex                                g_sinc;
static volatile std::int32_t                     counter_refs_ { 0 };
static ::libs::link::appl::IApplication::raw_ptr g_appl { nullptr };

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_mpl_mlog () -> ::libs::link::appl::IApplication::raw_ptr
{
  std::scoped_lock lock (g_sinc);

  if (!g_appl)
  {
    g_appl = new ::modules::mlog::appl::LogModule;
  }

  counter_refs_ = counter_refs_ + 1;
  return g_appl;
}

extern "C" BOOST_SYMBOL_EXPORT auto
delete_impl_mpl_mlog (::libs::link::appl::IApplication::raw_ptr appl) -> void
{
  std::scoped_lock lock (g_sinc);

  ::libs::utility::checks::assert_soft (appl && appl == g_appl);
  if (counter_refs_ <= 1)
  {
    delete g_appl;
    g_appl = nullptr;
  }

  counter_refs_ = counter_refs_ - 1;
}
