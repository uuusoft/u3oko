#pragma once
/**
\file       video-sender-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2016
*/

namespace dnodes::terminals::video_sender
{
//  forward
class IsEmptyFrameHelper;
class FillFrameHelper;

/// Основной фильтр графа обработки данных для передачи обработанных зображений в другие модули
/// Для примера, http server, gui etc
class Filter final :
  public ::libs::icore::impl::base::obj::dll::IFilter,
  protected ::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >
{
  friend class IsEmptyFrameHelper;
  friend class FillFrameHelper;

  public:
  Filter ();
  virtual ~Filter () = default;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >)

  using send_func_type       = std::function< void (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr) >;
  using send_funcs_type      = boost::unordered_flat_map< syn::persisent_id_link_type, send_func_type, ::libs::utility::utils::TransparentStringHash, std::equal_to<> >;
  using send_impl_func_type  = std::function< void (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr) >;
  using send_impl_funcs_type = boost::unordered_flat_map< syn::persisent_id_link_type, IImplSender::ptr, ::libs::utility::utils::TransparentStringHash, std::equal_to<> >;

  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;
  virtual auto run_int () -> void override;
  virtual auto stop_int () -> void override;

  void init_pts (syn::ConnectInfo*);
  void send_info_msg (syn::TransformInfo&);
  void process_events (syn::TransformInfo&);
  void init_send_funcs ();
  void default_send_func (syn::TransformInfo&, const syn::Buff2ModuleInfo::craw_ptr, const syn::persisent_id_link_type&);

  send_funcs_type      funcs_;     //< Функции передачи буферов по модулю-назачения
  send_impl_funcs_type senders_;   //<
};
}   // namespace dnodes::terminals::video_sender
