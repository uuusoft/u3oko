#pragma once
/**
\file       source-impl-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
*/

namespace dnodes::sources::gen_lib
{
struct SourceImplInfo final {
  // SourceImplInfo () = default;
  syn::VideoDriverProp::craw_ptr        props_ { nullptr };           //<
  syn::VideoDriverCaptureProp::craw_ptr capture_props_ { nullptr };   //<
  syn::LinksVideoDriverProp::craw_ptr   links_props_ { nullptr };     //<
};
}   // namespace dnodes::sources::gen_lib
