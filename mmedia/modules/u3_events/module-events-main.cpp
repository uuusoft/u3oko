/**
\file       module-events-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_events
\brief      Модуль сервера событий
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "module-events-includes_int.hpp"
#include "appl/events-module-syn.hpp"
#include "appl/events-module.hpp"

#if 0
static std::mutex                                g_sinc;
static volatile std::int32_t                     counter_refs_ = 0;
static ::libs::link::appl::IApplication::raw_ptr g_appl        = nullptr;

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication::raw_ptr
create_impl_mpl_u3_events ()
{
  std::lock_guard< std::mutex > lock (g_sinc);

  if (!g_appl)
  {
    g_appl = new ::modules::u3_events::appl::EventsModule;
  }

  counter_refs_ = counter_refs_ + 1;
  return g_appl;
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_u3_events (::libs::link::appl::IApplication::raw_ptr appl)
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
#endif

namespace modules::u3_events::appl
{
::libs::link::appl::IApplication::raw_ptr
factory_impl_mpl_u3_events (::libs::link::appl::IApplication::raw_ptr impl, bool create)
{
  static std::int64_t               count_eventsrefs = 0;
  static syn::IApplication::raw_ptr eventsappl       = nullptr;
  static std::mutex                 eventssinc;
  std::lock_guard< std::mutex >     lock (eventssinc);
  if (create)
  {
    U3_ASSERT_NT (nullptr == impl, PTR_TOLOG (impl));
    if (!eventsappl)
    {
      eventsappl = new ::modules::u3_events::appl::EventsModule;
    }
    ++count_eventsrefs;
  }
  else
  {
    U3_ASSERT_NT (impl, PTR_TOLOG (impl));
    U3_ASSERT_NT (impl == eventsappl, PTR_TOLOG (impl));
    U3_ASSERT_NT (eventsappl, PTR_TOLOG (eventsappl));
    --count_eventsrefs;
    if (count_eventsrefs <= 0 && eventsappl)
    {
      delete eventsappl;
      eventsappl = nullptr;
    }
    U3_ASSERT_NT (count_eventsrefs >= 0, PTR_TOLOG (eventsappl));
  }
  return eventsappl;
}
}   // namespace modules::u3_events::appl


extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication::raw_ptr
create_impl_mpl_u3_events ()
{
  return modules::u3_events::appl::factory_impl_mpl_u3_events (nullptr, true);
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_u3_events (::libs::link::appl::IApplication::raw_ptr impl)
{
  modules::u3_events::appl::factory_impl_mpl_u3_events (impl, false);
}
