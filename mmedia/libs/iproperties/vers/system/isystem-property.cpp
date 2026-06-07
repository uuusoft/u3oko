/**
\file       isystem-property.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       02.03.2022
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-iproperties-includes_int.hpp"
#include "isystem-property.hpp"

namespace libs::iproperties::vers::system
{
ISystemProperty::ISystemProperty ()
{
  // mthreads_  = std::make_shared< ::libs::optim::mcalls::IMCaller > ();
  appl_path_ = boost::filesystem::current_path ().string ();
}


auto
ISystemProperty::get_appl_lockfree () -> syn::ApplicationProp::craw_ptr const
{
  return main_appl_properties_;
}


void
ISystemProperty::set_appl_lockfree (syn::ApplicationProp::raw_ptr ptr)
{
  main_appl_properties_ = ptr;
}


auto
ISystemProperty::get_log_lockfree () -> syn::PropertyLogModuleEvent::craw_ptr const
{
  return module_log_props_;
}


void
ISystemProperty::set_log_lockfree (syn::PropertyLogModuleEvent::raw_ptr ptr)
{
  module_log_props_ = ptr;
}


auto
ISystemProperty::get_paths_lockfree () -> iproperties::appl_paths::IAppPaths::cptr const
{
  return appl_paths_;
}


void
ISystemProperty::set_paths_lockfree (iproperties::appl_paths::IAppPaths::ptr& ptr)
{
  appl_paths_ = ptr;
}


auto
ISystemProperty::get_appl_path_lockfree () -> std::string const
{
  return appl_path_;
}


void
ISystemProperty::set_appl_path_lockfree (const std::string& str)
{
  appl_path_ = str;
}


auto
ISystemProperty::get_mdata_lockfree () -> std::string const
{
  return data_path_;
}


void
ISystemProperty::set_mdata_lockfree (const std::string& str)
{
  data_path_ = str;
}


auto
ISystemProperty::get_mcalls_lockfree () -> ::libs::optim::mcalls::IMCaller::ptr
{
  return mthreads_;
}


void
ISystemProperty::set_mcalls_lockfree (::libs::optim::mcalls::IMCaller::ptr& ptr)
{
  mthreads_ = ptr;
}


bool
ISystemProperty::self_test_int () const
{
  U3_ASSERT (!appl_path_.empty ());
  U3_ASSERT (!data_path_.empty ());
  U3_ASSERT (mthreads_);
  U3_ASSERT (main_appl_properties_);
  return appl_path_.empty () || data_path_.empty () || !mthreads_ || !main_appl_properties_ ? false : true;
}


void*
ISystemProperty::cast2top_int ()
{
  return this;
}
}   // namespace libs::iproperties::vers::system
