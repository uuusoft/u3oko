/**
\file       forever-load-dlls.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "forever-load-dlls.hpp"

namespace libs::helpers::dlls
{
ForeverLoadDlls::ForeverLoadDlls ()
{
}


ForeverLoadDlls::~ForeverLoadDlls ()
{
}


void
ForeverLoadDlls::add (const std::string& name, const dll_type& lib)
{
#ifndef U3_CNTRL_DEBUG_DISABLE_FROZEN_DLL_IN_MEMORY
  if (!lib)
  {
    return;
  }

  U3_ASSERT (!name.empty ());
  U3_ASSERT (lib.is_loaded ());
  lock_type lock (mtx_);
  dlls_.insert (dlls_type::value_type (name, lib));
#endif
}
}   // namespace libs::helpers::dlls
