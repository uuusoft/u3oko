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
#if 0
class FillFrameHelper : public ::libs::link::mem::IHandlerMem
{
  public:
  FillFrameHelper (Filter* obj, syn::TransformInfo& info) :
    obj_ (obj),
    info_ (info)
  {
  }

  virtual ~FillFrameHelper ()
  {
  }

  virtual bool
  update (void* pmem) const override
  {
    return obj_->fill_frame (info_, pmem);
  }

  private:
  mutable Filter*     obj_;    //<  ???
  syn::TransformInfo& info_;   //<  ???
};
#endif
}   // namespace dlls::terminals::video_sender::impl2gui
