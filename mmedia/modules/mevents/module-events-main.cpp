/**
\file       module-events-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\brief      Модуль сервера событий
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "module-events-includes_int.hpp"
#include "appl/events-module-syn.hpp"
#include "appl/events-module.hpp"

namespace modules::mevents::appl
{
auto
factory_impl_mevents (::libs::link::appl::IApplication::raw_ptr impl, bool create) -> ::libs::link::appl::IApplication::raw_ptr
{
  static std::int64_t               count_eventsrefs = 0;
  static syn::IApplication::raw_ptr eventsappl       = nullptr;
  static std::mutex                 eventssinc;

  std::scoped_lock lock (eventssinc);
  if (create)
  {
    ::libs::utility::checks::assert_soft (nullptr == impl, PTR_TOLOG (impl));
    if (!eventsappl)
    {
      eventsappl = new ::modules::mevents::appl::EventsModule;
    }
    ++count_eventsrefs;
  }
  else
  {
    ::libs::utility::checks::assert_soft (impl, PTR_TOLOG (impl));
    ::libs::utility::checks::assert_soft (impl == eventsappl, PTR_TOLOG (impl));
    ::libs::utility::checks::assert_soft (eventsappl, PTR_TOLOG (eventsappl));
    --count_eventsrefs;
    if (count_eventsrefs <= 0 && eventsappl)
    {
      delete eventsappl;
      eventsappl = nullptr;
    }
    ::libs::utility::checks::assert_soft (count_eventsrefs >= 0, PTR_TOLOG (eventsappl));
  }
  return eventsappl;
}
}   // namespace modules::mevents::appl


extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_mpl_mevents () -> ::libs::link::appl::IApplication::raw_ptr
{
  U3_CALL_TRACE_DBG;
  return modules::mevents::appl::factory_impl_mevents (nullptr, true);
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_mevents (::libs::link::appl::IApplication::raw_ptr impl)
{
  modules::mevents::appl::factory_impl_mevents (impl, false);
}
