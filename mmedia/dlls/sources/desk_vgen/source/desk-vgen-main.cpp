/**
\file       desk-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_desk_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "desk-vgen-includes_int.hpp"
#include "desk-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT bool
get_source_vss_desk_vgen (::dlls::sources::gen_lib::ISourceImpl** ret)
{
  U3_ASSERT (ret);
  U3_ASSERT (!*ret);
  *ret = new ::dlls::sources::desk_vgen::SourceImpl ();
  return true;
}


extern "C" BOOST_SYMBOL_EXPORT bool
free_source_vss_desk_vgen (::dlls::sources::gen_lib::ISourceImpl** ret)
{
  U3_ASSERT (ret);
  U3_ASSERT (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
