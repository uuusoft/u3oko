#pragma once
/**
\file       iimpl-sender.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender
{
class IImplSender
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IImplSender)

  virtual ~IImplSender () = default;

  void
  send (
    const InfoFilter&                    finfo,
    const syn::TransformInfo&            info,
    const syn::Buff2ModuleInfo::craw_ptr minfo,
    syn::IVideoBuf::raw_ptr              send_buf)
  {
    send_int (finfo, info, minfo, send_buf);
  }

  protected:
  IImplSender () = default;

  private:
  //  IImplSender interface
  virtual void send_int (
    const InfoFilter&,
    const syn::TransformInfo&,
    const syn::Buff2ModuleInfo::craw_ptr,
    syn::IVideoBuf::raw_ptr) = 0;
};
}   // namespace dlls::terminals::video_sender
