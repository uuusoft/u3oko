#pragma once
/**
\file       v4l2-vgen-cam-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/

namespace dlls::sources::v4l2_vgen::camera
{
class CamImpl final
{
  public:
  U3_ADD_POINTERS_TO_SELF (CamImpl)
  U3_ADD_DELETE_MOVE_COPY (CamImpl)

  explicit CamImpl (const gen_lib::SourceImplInfo& props_info);
  ~CamImpl () = default;

  auto get_buf () -> syn::IVideoBuf::ptr;
  auto sync_correct_props (syn::VideoCorrectProp::craw_ptr) -> void;
  auto is_init () const -> bool;

  private:
  void sync_runtime_props (const syn::VideoDriverCaptureProp&);

  const gen_lib::SourceImplInfo&  srcparams_;                 //<
  std::mutex                      sync_;                      //<
  std::unique_ptr< V4l2Capture >  v4l2capture_ { nullptr };   //<
  syn::VideoDriverCapturePropInfo capparams_;                 //<
};
}   // namespace dlls::sources::v4l2_vgen::camera
