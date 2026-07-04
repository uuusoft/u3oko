/**
\file       pict-vgen-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_pict_vgen
*/
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#ifdef U3_COMPILER_MSC
#  pragma warning(push)
// #pragma warning(disable : 4996)
#else
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wpedantic"
#endif

#include "includes_int.hpp"

#ifdef U3_COMPILER_MSC
#  pragma warning(pop)
#else
#  pragma GCC diagnostic pop
#endif

#include "pict-vgen-source-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
get_source_vss_pict_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  U3_ASSERT (ret);
  U3_ASSERT (!*ret);
  *ret = new ::dlls::sources::pict_vgen::SourceImpl ();
  return true;
}

extern "C" BOOST_SYMBOL_EXPORT auto
free_source_vss_pict_vgen (::dlls::sources::gen_lib::ISourceImpl** ret) -> bool
{
  U3_ASSERT (ret);
  U3_ASSERT (*ret);
  delete *ret;
  *ret = nullptr;
  return true;
}
