/**
\file       loader-code.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-ilink-loader-includes_int.hpp"
#include "../libs-ilink-includes_int.hpp"
#include "loader-code.hpp"

namespace libs::ilink::loader
{
LoaderCode::LoaderCode ()
{
}


LoaderCode::~LoaderCode ()
{
  impl_.reset ();
}


void
LoaderCode::load (
  const ::libs::link::details::CodeRuns& type,
  const ::libs::link::CreateInfo*        info,
  const std::string&                     name_proc,
  const std::string&                     name_lib,
  const std::vector< std::string >&      args)
{
  if (::libs::link::details::CodeRuns::appl == type)
  {
    U3_XLOG_ERROR ("temporarily disabled");
    impl_.reset (new OutProcLoaderCode);
  }
  else if (::libs::link::details::CodeRuns::dll == type)
  {
    impl_.reset (new InProcLoaderCode);
  }

  U3_ASSERT (impl_);
  impl_->load (info, name_proc, name_lib, args);
}


bool
LoaderCode::is_load () const
{
  return impl_->is_load ();
}


bool
LoaderCode::unload (bool force)
{
  return impl_->unload (force);
}
}   // namespace libs::ilink::loader
