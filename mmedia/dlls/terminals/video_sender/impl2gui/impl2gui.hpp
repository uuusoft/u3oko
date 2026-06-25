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
  Impl2Gui ()          = default;
  virtual ~Impl2Gui () = default;

  private:
  //  IImplSender overrides
  virtual void send_int (
    const InfoFilter&,
    const syn::TransformInfo&,
    const syn::Buff2ModuleInfo::craw_ptr,
    syn::IVideoBuf::raw_ptr) override;

  bool fill_frame (const syn::TransformInfo&, void*);
  void send_frame (const InfoFilter&, const syn::TransformInfo&, ::libs::link::ILink::ptr);
  bool is_empty_frame (const void*) const;

  ::libs::link::mem::IBlockFakeMem last_hmem_;      //<
  ::libs::bufs::Bufs::ptr          fast_buf2gui_;   //<
};
}   // namespace dlls::terminals::video_sender::impl2gui
