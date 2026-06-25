#pragma once
/**
\file       fill-frame-helper.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_video_sender_dll
*/

// old shit
namespace dlls::terminals::video_sender::impl2gui
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
class FillFrameHelper : public ::libs::link::mem::IHandlerMem
{
  public:
  FillFrameHelper (Filter* obj, syn::TransformInfo& info) :
    obj_ (obj),
    info_ (info)
  {
  }

  virtual ~FillFrameHelper () = default;

  virtual bool
  update (void* pmem) const override
  {
    return obj_->fill_frame (info_, pmem);
  }

  private:
  mutable Filter*     obj_ = nullptr;   //<
  syn::TransformInfo& info_;            //<
};
#endif
}   // namespace dlls::terminals::video_sender::impl2gui
