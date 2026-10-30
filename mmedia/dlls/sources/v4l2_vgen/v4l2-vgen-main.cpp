/**
\file       v4l2-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "v4l2-vgen-includes_int.hpp"
#include "v4l2-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
get_source_vss_v4l2_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  ::libs::utility::checks::throw_ifn (ret);
  ::libs::utility::checks::throw_ifn (!*ret);
  *ret = new ::dlls::sources::v4l2_vgen::SourceImpl ();
  return true;
}


extern "C" BOOST_SYMBOL_EXPORT auto
free_source_vss_v4l2_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  ::libs::utility::checks::throw_ifn (ret);
  ::libs::utility::checks::throw_ifn (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
