/**
\file       freezer-dlls.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "freezer-dlls.hpp"

namespace libs::utility::dlls
{
void
FreezerDlls::add (const std::string& name, const dll_type& lib)
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
}   // namespace libs::utility::dlls
