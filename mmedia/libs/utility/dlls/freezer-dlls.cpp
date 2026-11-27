/**
\file       freezer-dnodes.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
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

  ::libs::utility::checks::throw_ifn (!name.empty ());
  ::libs::utility::checks::throw_ifn (lib.is_loaded ());
  lock_type lock (mtx_);
  dnodes_.insert (dnodes_type::value_type (name, lib));
#endif
}
}   // namespace libs::utility::dlls
