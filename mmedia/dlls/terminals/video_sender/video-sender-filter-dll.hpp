#pragma once
/**
\file       video-sender-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2016
\project    u3_video_sender_dll
*/

namespace dlls::terminals::video_sender
{
//  forward
class IsEmptyFrameHelper;
class FillFrameHelper;

/// Основной фильтр графа обработки данных для передачи обработанных зображений в другие модули
/// Для примера, http server, gui etc
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  friend class IsEmptyFrameHelper;
  friend class FillFrameHelper;

  public:
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  using send_func_type       = std::function< void (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr) >;
  using send_funcs_type      = std::unordered_map< syn::id_link_type, send_func_type >;
  using send_impl_func_type  = std::function< void (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr) >;
  using send_impl_funcs_type = std::unordered_map< syn::id_link_type, IImplSender::ptr >;
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual void load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (syn::CallInterfInfo& info) override;
  virtual void run_int () override;
  virtual void stop_int () override;

  void init_pts (syn::ConnectInfo* info);
  void send_info_msg (syn::TransformInfo& info);
  void process_events (syn::TransformInfo& info);
  void init_send_funcs ();
  void default_send_funct (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr, const syn::id_link_type&);

  send_funcs_type      funcs_;     //< Функции передачи буферов по модулю-назачения
  send_impl_funcs_type senders_;   //<
};
}   // namespace dlls::terminals::video_sender
