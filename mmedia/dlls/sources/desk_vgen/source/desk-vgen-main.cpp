/**
\file       desk-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
*/
#include "desk-vgen-includes_int.hpp"
#include "desk-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
get_source_vss_desk_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  ::libs::utility::checks::throw_ifn (ret);
  ::libs::utility::checks::throw_ifn (!*ret);
  *ret = new ::dlls::sources::desk_vgen::SourceImpl ();
  return true;
}


extern "C" BOOST_SYMBOL_EXPORT auto
free_source_vss_desk_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  ::libs::utility::checks::throw_ifn (ret);
  ::libs::utility::checks::throw_ifn (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
