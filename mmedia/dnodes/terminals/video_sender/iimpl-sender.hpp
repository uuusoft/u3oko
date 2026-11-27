#pragma once
/**
\file       iimpl-sender.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
*/

namespace dnodes::terminals::video_sender
{
class IImplSender
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (IImplSender)

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
}   // namespace dnodes::terminals::video_sender
