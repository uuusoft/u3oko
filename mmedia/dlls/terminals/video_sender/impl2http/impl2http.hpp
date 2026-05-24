#pragma once
/**
\file       impl2http.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.08.2018
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender::impl2http
{
class Impl2Http final : public IImplSender
{
  public:
  Impl2Http ();
  virtual ~Impl2Http ();

  private:
  //  IImplSender overrides
  virtual void send_int (
    const InfoFilter&                    finfo,
    const syn::TransformInfo&            info,
    const syn::Buff2ModuleInfo::craw_ptr minfo,
    syn::IVideoBuf::raw_ptr              send_buf) override;
};
}   // namespace dlls::terminals::video_sender::impl2http
