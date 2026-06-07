#pragma once
/**
\file       is-empty-frame-helper.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_video_sender_dll
*/

// old shit
namespace dlls::terminals::video_sender::impl2gui
{
#ifdef U3_FAKE_DISABLE
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
  mutable Filter* obj_;   //<
};
#endif
}   // namespace dlls::terminals::video_sender::impl2gui
