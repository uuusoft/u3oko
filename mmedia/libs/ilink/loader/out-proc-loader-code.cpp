/**
\file       out-proc-loader-code.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-ilink-loader-includes_int.hpp"
#include "out-proc-loader-code.hpp"

namespace libs::ilink::loader
{
OutProcLoaderCode::OutProcLoaderCode () :
  info_ (nullptr)
{
  // thread_done_.store( true );
}


OutProcLoaderCode::~OutProcLoaderCode ()
{
  while (!unload (true))
  {
  }
}


void
OutProcLoaderCode::load_int (
  const ::libs::link::CreateInfo* info,
  const std::string&              name_proc,
  const std::string&              name_lib,
  const args_type&                args)
{
  info_ = info;
  U3_ASSERT_SIGNAL ("process");

#if 0
  if (!child_process_)
  {
    child_process_.reset (
      new boost::process::child (
        boost::process::launch (name_proc, args, cntx)));
  }
#endif
}


bool
OutProcLoaderCode::is_load_int () const
{
  U3_ASSERT_SIGNAL ("process");
  return false;
#if 0
  //return child_process_ && *child_process_ ? true : false;
  return child_process_ && child_process_->get_id () ? true : false;
#endif
}


bool
OutProcLoaderCode::unload_int (bool force)
{
  U3_ASSERT_SIGNAL ("process");
#if 0
  if (child_process_)
  {
    if (force)
    {
      U3_ASSERT_SIGNAL ("process");
      //child_process_->terminate (false );
    }

    U3_ASSERT_SIGNAL ("process");
    //child_process_->wait ();
    child_process_.reset ();
  }
#endif
  return true;
}


void
OutProcLoaderCode::set_name_lib (const std::string& name_lib)
{
  U3_ASSERT (!name_lib.empty ());
  lib_name_ = name_lib;
}
}   // namespace libs::ilink::loader
