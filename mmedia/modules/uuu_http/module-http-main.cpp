/**
\file       module-http-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_http_module
\brief      Модуль http сервера.
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "module-http-includes-special.hpp"
#include "mmedia/includes/includes.hpp"
#include "module-http-includes_int.hpp"

namespace modules::uuu_http::appl
{
::libs::link::appl::IApplication::raw_ptr
factory_impl_mpl_uuu_http (::libs::link::appl::IApplication::raw_ptr impl, bool create)
{
  static std::int64_t               count_httprefs = 0;
  static syn::IApplication::raw_ptr httpappl       = nullptr;

  static std::mutex             httpsinc;
  std::lock_guard< std::mutex > lock (httpsinc);
  if (create)
  {
    U3_ASSERT_NT (nullptr == impl, PTR_TOLOG (impl));
    if (!httpappl)
    {
      httpappl = new ::modules::uuu_http::appl::HttpModule;
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
}   // namespace modules::uuu_http::appl


extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication::raw_ptr
create_impl_mpl_uuu_http ()
{
  return modules::uuu_http::appl::factory_impl_mpl_uuu_http (nullptr, true);
}

extern "C" BOOST_SYMBOL_EXPORT void
delete_impl_mpl_uuu_http (::libs::link::appl::IApplication::raw_ptr impl)
{
  modules::uuu_http::appl::factory_impl_mpl_uuu_http (impl, false);
}
