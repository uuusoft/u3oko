#pragma once
/**
\file       source-impl-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_vgen_lib
*/

namespace dlls::sources::gen_lib
{
struct SourceImplInfo final {
  SourceImplInfo (
    const syn::VideoDriverProp::craw_ptr        props         = nullptr,
    const syn::VideoDriverCaptureProp::craw_ptr capture_props = nullptr,
    const syn::LinksVideoDriverProp::craw_ptr   links_props   = nullptr) :
    props_ (props),
    capture_props_ (capture_props),
    links_props_ (links_props)
  {
  }

  syn::VideoDriverProp::craw_ptr        props_         = nullptr;   //<
  syn::VideoDriverCaptureProp::craw_ptr capture_props_ = nullptr;   //<
  syn::LinksVideoDriverProp::craw_ptr   links_props_   = nullptr;   //<
};
}   // namespace dlls::sources::gen_lib
