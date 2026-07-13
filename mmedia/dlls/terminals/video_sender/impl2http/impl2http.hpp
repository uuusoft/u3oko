#pragma once
/**
\file       impl2http.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender::impl2http
{
class Impl2Http final : public IImplSender
{
  public:
  Impl2Http ()          = default;
  virtual ~Impl2Http () = default;

  private:
  //  IImplSender overrides
  virtual void send_int (
    const InfoFilter&,
    const syn::TransformInfo&,
    const syn::Buff2ModuleInfo::craw_ptr,
    syn::IVideoBuf::raw_ptr) override;
};
}   // namespace dlls::terminals::video_sender::impl2http
