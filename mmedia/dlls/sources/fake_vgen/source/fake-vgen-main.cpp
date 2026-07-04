/**
\file       fake-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_fake_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "includes_int.hpp"
#include "fake-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
get_source_vss_fake_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  U3_ASSERT (ret);
  U3_ASSERT (!*ret);
  *ret = new ::dlls::sources::fake_vgen::SourceImpl ();
  return true;
}


extern "C" BOOST_SYMBOL_EXPORT auto
free_source_vss_fake_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  U3_ASSERT (ret);
  U3_ASSERT (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
