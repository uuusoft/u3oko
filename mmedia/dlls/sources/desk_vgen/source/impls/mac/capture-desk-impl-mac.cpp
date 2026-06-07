/**
\file       capture-desk-impl-mac.cpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_desk_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../desk-vgen-includes_int.hpp"
#include "capture-desk-impl-mac.hpp"

#ifdef U3_OS_MACX_DESKTOP

namespace dlls::sources::desk_vgen::impls::mac
{
void
CaptureDeskImplMac::get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info)
{
}
}   // namespace dlls::sources::desk_vgen::impls::mac

#endif
