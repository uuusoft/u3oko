#pragma once
/**
\file       is-empty-frame-helper.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/

// old shit
namespace dnodes::terminals::video_sender::impl2gui
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
class IsEmptyFrameHelper : public ::libs::link::mem::IHandlerMem
{
  public:
  IsEmptyFrameHelper (Filter* obj) :
    obj_ (obj)
  {
  }

  virtual ~IsEmptyFrameHelper () = default;

  virtual bool
  update (void* pmem) const override
  {
    return obj_->is_empty_frame (pmem);
  }

  private:
  mutable Filter* obj_ { nullptr };   //<
};
#endif
}   // namespace dnodes::terminals::video_sender::impl2gui
