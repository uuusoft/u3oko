/**
\file       loader-code.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/
#include "libs-ilink-loader-includes_int.hpp"
#include "../libs-ilink-includes_int.hpp"
#include "memory"
#include "loader-code.hpp"

namespace libs::ilink::loader
{
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
  if (!impl_)
  {
    switch (type)
    {
    case ::libs::link::details::CodeRuns::appl:
      impl_ = std::make_unique< OutProcLoaderCode > ();
      break;
    case ::libs::link::details::CodeRuns::dll:
    default:
      impl_ = std::make_unique< InProcLoaderCode > ();
      break;
    }
  }

  U3_ASSERT (impl_);
  impl_->load (info, name_proc, name_lib, args);
}


auto
LoaderCode::is_load () const -> bool
{
  return impl_->is_load ();
}


auto
LoaderCode::unload (bool force) -> bool
{
  return impl_->unload (force);
}
}   // namespace libs::ilink::loader
