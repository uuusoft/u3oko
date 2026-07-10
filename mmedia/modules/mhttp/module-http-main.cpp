/**
\file       module-http-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mhttp
\brief      Модуль http сервера
*/
#include "module-http-includes_int.hpp"

namespace modules::mhttp::appl
{
auto
factory_impl_mpl_mhttp (::libs::link::appl::IApplication::raw_ptr impl, bool create) -> ::libs::link::appl::IApplication::raw_ptr
{
  static std::int64_t               count_httprefs = 0;
  static syn::IApplication::raw_ptr httpappl       = nullptr;

  static std::mutex httpsinc;
  std::scoped_lock  lock (httpsinc);
  if (create)
  {
    U3_ASSERT_NT (nullptr == impl, PTR_TOLOG (impl));
    if (!httpappl)
    {
      httpappl = new ::modules::mhttp::appl::HttpModule;
    }
    ++count_httprefs;
  }
  else
  {
    U3_ASSERT_NT (impl, PTR_TOLOG (impl));
    U3_ASSERT_NT (impl == httpappl, PTR_TOLOG (impl));
    U3_ASSERT_NT (httpappl, PTR_TOLOG (httpappl));
    --count_httprefs;
    if (count_httprefs <= 0 && httpappl)
    {
      delete httpappl;
      httpappl = nullptr;
    }
    U3_ASSERT_NT (count_httprefs >= 0, PTR_TOLOG (httpappl));
  }
  return httpappl;
}
}   // namespace modules::mhttp::appl

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_mpl_mhttp () -> ::libs::link::appl::IApplication::raw_ptr
{
  return modules::mhttp::appl::factory_impl_mpl_mhttp (nullptr, true);
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_mhttp (::libs::link::appl::IApplication::raw_ptr impl)
{
  modules::mhttp::appl::factory_impl_mpl_mhttp (impl, false);
}
