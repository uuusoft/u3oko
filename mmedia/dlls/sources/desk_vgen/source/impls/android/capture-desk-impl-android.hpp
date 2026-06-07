#pragma once
/**
\file       capture-desk-impl-android.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_desk_vgen
*/

namespace dlls::sources::desk_vgen::impls::android
{
class CaptureDeskImplAndroid : public ::dlls::sources::desk_vgen::ICaptureDeskImpl
{
  public:
  CaptureDeskImplAndroid ()          = default;
  virtual ~CaptureDeskImplAndroid () = default;

  private:
  // ICaptureDeskImpl
  virtual void get_buf_int (const syn::SourceImplInfo& props_info, CaptureDeskInfo& info) override;
};
}   // namespace dlls::sources::desk_vgen::impls::android
