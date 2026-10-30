/**
\file       fake-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "includes_int.hpp"
#include "fake-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
get_source_vss_fake_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  ::libs::utility::checks::throw_ifn (ret);
  ::libs::utility::checks::throw_ifn (!*ret);
  *ret = new ::dlls::sources::fake_vgen::SourceImpl ();
  return true;
}


extern "C" BOOST_SYMBOL_EXPORT auto
free_source_vss_fake_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  ::libs::utility::checks::throw_ifn (ret);
  ::libs::utility::checks::throw_ifn (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
