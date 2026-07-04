#pragma once
/**
\file       impl2storage.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender::impl2storage
{
class Impl2Storage final : public IImplSender
{
  public:
  Impl2Storage () = default;
  virtual ~Impl2Storage ();

  private:
  //  IImplSender overrides
  virtual void send_int (
    const InfoFilter&                    finfo,
    const syn::TransformInfo&            info,
    const syn::Buff2ModuleInfo::craw_ptr minfo,
    syn::IVideoBuf::raw_ptr              send_buf) override;

  void open_stream ();
  void close_stream ();

  void send_message (
    syn::IEvent::ptr&     rmsg,
    const syn::CallSyncs& sync,
    const syn::Calls&     req);

  ::libs::events_storage::stream_id_type active_stream_;   //<
};
}   // namespace dlls::terminals::video_sender::impl2storage
