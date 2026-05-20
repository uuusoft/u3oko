#pragma once
/**
\file       impl2gui.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender::impl2gui
{
class Impl2Gui final : public IImplSender
{
  public:
  Impl2Gui ();
  virtual ~Impl2Gui ();


  private:
  //  IImplSender overrides
  virtual void send_int (
    const InfoFilter&                    finfo,
    const syn::TransformInfo&            info,
    const syn::Buff2ModuleInfo::craw_ptr minfo,
    syn::IVideoBuf::raw_ptr              send_buf) override;

  bool fill_frame (const syn::TransformInfo& info, void* pmem);
  void send_frame (const InfoFilter& finfo, const syn::TransformInfo& info, ::libs::link::ILink::ptr helper);
  bool is_empty_frame (const void* pmem) const;

  ::libs::link::mem::IBlockFakeMem last_hmem_;      //<
  ::libs::bufs::Bufs::ptr          fast_buf2gui_;   //<
};
}   // namespace dlls::terminals::video_sender::impl2gui
