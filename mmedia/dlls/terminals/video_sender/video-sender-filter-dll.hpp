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
  virtual ~Filter () = default;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  using send_func_type       = std::function< void (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr) >;
  using send_funcs_type      = boost::unordered_flat_map< syn::id_link_type, send_func_type >;
  using send_impl_func_type  = std::function< void (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr) >;
  using send_impl_funcs_type = boost::unordered_flat_map< syn::id_link_type, IImplSender::ptr >;

  // IFilter overrides
  virtual void load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;
  virtual void run_int () override;
  virtual auto stop_int () -> void override;

  void init_pts (syn::ConnectInfo* info);
  void send_info_msg (syn::TransformInfo& info);
  void process_events (syn::TransformInfo& info);
  void init_send_funcs ();
  void default_send_func (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr, const syn::id_link_type&);

  send_funcs_type      funcs_;     //< Функции передачи буферов по модулю-назачения
  send_impl_funcs_type senders_;   //<
};
}   // namespace dlls::terminals::video_sender
