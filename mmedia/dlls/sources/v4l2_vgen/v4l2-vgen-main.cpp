/**
\file       v4l2-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "v4l2-vgen-includes_int.hpp"
#include "v4l2-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
get_source_vss_v4l2_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  U3_ASSERT (ret);
  U3_ASSERT (!*ret);
  *ret = new ::dlls::sources::v4l2_vgen::SourceImpl ();
  return true;
}


extern "C" BOOST_SYMBOL_EXPORT auto
free_source_vss_v4l2_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  U3_ASSERT (ret);
  U3_ASSERT (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
