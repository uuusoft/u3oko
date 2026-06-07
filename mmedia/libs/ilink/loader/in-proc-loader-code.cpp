/**
\file       in-proc-loader-code.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "libs-ilink-loader-includes_int.hpp"
#include "in-proc-loader-code.hpp"
#include "mmedia/libs/helpers/thread/generic-thread-func.hpp"

namespace libs::ilink::loader
{
InProcLoaderCode::InProcLoaderCode () :
  info_ (nullptr)
{
  thread_done_.store (true);
}


InProcLoaderCode::~InProcLoaderCode ()
{
  while (!unload (true))
  {
  }
}


void
InProcLoaderCode::load_int (
  const ::libs::link::CreateInfo* info,
  const std::string&              name_proc,
  const std::string&              name_lib,
  const args_type&                args)
{
  info_ = info;
  if (is_load_int ())
  {
    return;
  }

  thread_done_.store (false);
  set_name_lib (name_lib);

  child_thread_ = std::thread (
    ::libs::helpers::thread::generic_thread_funct< InProcLoaderCode, libs::properties::vers::links::mids::appl2log >,
    this,
    0u);
}


bool
InProcLoaderCode::is_load_int () const
{
  return child_thread_.joinable () ? true : false;
}


bool
InProcLoaderCode::unload_int (bool force)
{
  if (child_thread_.joinable ())
  {
    if (thread_done_.load ())
    {
      std::this_thread::yield ();
      child_thread_.detach ();
      return true;
    }
  }
  else
  {
    thread_done_.store (true);
  }
  return thread_done_.load () ? true : false;
}


void
InProcLoaderCode::thread_func_impl (std::uint32_t indx_thread)
{
  ::libs::helpers::thread::set_thread_priority (std::this_thread::get_id (), ::libs::helpers::thread::Priorities::high);

  boost::filesystem::path fullpath (::libs::iproperties::appl_paths::get_current_folder ());
  const auto              sfullpath = fullpath.string ();

  thread_appl_.reset (new ::libs::link::appl::IApplicationProxy (sfullpath, lib_name_));

  auto impl = thread_appl_->impl ();
  U3_CHECK (impl, "empty thread impl" + PTR_TOLOG (impl))

  ::libs::link::appl::InitApplication info;
  info.company_name_ = info_->id_arg2val_[link::consts::text::id_company_name].empty () ? info.company_name_ : info_->id_arg2val_[link::consts::text::id_company_name];
  info.appl_name_    = info_->id_arg2val_[link::consts::text::id_appl_name].empty () ? info.appl_name_ : info_->id_arg2val_[link::consts::text::id_appl_name];
  info.lib_name_     = info_->id_arg2val_[link::consts::text::id_lib_name].empty () ? info.lib_name_ : info_->id_arg2val_[link::consts::text::id_lib_name];
  info.subsys_name_  = info_->id_arg2val_[link::consts::text::id_subsys_name].empty () ? info.subsys_name_ : info_->id_arg2val_[link::consts::text::id_subsys_name];
  info.service_name_ = info_->id_arg2val_[link::consts::text::id_service_name].empty () ? info.service_name_ : info_->id_arg2val_[link::consts::text::id_service_name];

  U3_XLOG_MARK (TOLOG (info.company_name_) + TOLOG (info.appl_name_) + TOLOG (info.lib_name_) + TOLOG (info.subsys_name_) + TOLOG (info.service_name_))

  impl->appl_init (info);
  impl->appl_work ();
}


void
InProcLoaderCode::thread_postfunc_impl (std::uint32_t indx_thread)
{
  thread_done_.store (true);
  U3_ASSERT (thread_appl_);
  U3_ASSERT (thread_appl_->impl ());
}


void
InProcLoaderCode::set_name_lib (const std::string& name_lib)
{
  U3_ASSERT (!name_lib.empty ());
  lib_name_ = name_lib;
}
}   // namespace libs::ilink::loader
