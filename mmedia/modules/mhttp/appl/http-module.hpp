#pragma once
/**
\file       http-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mhttp
*/

namespace modules::mhttp::appl
{
using impl_server_type = std::shared_ptr< impl::beast::listener >;

struct ImplState final {
  U3_ADD_DELETE_MOVE_COPY (ImplState)

  ImplState () = default;

  impl_server_type           impl_;           //< Реализация сервера
  std::thread                impl_thread_;    //< Поток для сервера
  std::vector< std::thread > work_threads_;   //< Рабочие потоки
  boost::asio::io_context    ioc_ { consts::count_work_threads };
  boost::asio::ssl::context  ctx_ { boost::asio::ssl::context::tlsv12 };
};

/// Реализация интерфейса модуля для функционала HTTP сервер
class HttpModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  //  ext types
  using process_res_type = modules::mhttp::impl::beast::handler_func_res_type;   // data + mime + status http

  HttpModule ();
  virtual ~HttpModule () = default;

  private:
  //  internal typess
  U3_ADD_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  using sync_type     = std::mutex;
  using lock_type     = std::scoped_lock< sync_type >;
  using ids2bufs_type = boost::unordered_flat_map< std::string, Id2BufInfo >;

  //  IApplication overrides
  virtual auto init_appl_data_int () -> void override;

  //  BaseModule overrides
  virtual auto appl_init_int (const syn::InitApplication& info) -> void override;
  virtual auto init_links_int (const syn::InitApplication& info) -> void override;
  virtual auto init_proxys_int () -> void override;
  virtual auto appl_deinit_int () -> bool override;
  virtual auto update_catch_funcs_int () -> void override;
  virtual auto get_recv_link_int () -> recv_links_type override;

  //  LeafModule overrides
  virtual auto catch_event_int (syn::IEvent::ptr& evnt) -> bool override;
  virtual auto is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool override;

  // internal
  auto check_process () -> void;
  auto start_http_server () -> void;
  auto stop_http_server () -> void;
  auto prepare_resources () -> void;
  auto create_rw_copy () -> void;
  auto delete_rw_copy () -> void;
  // auto load_def_resource2mem () -> void;
  auto process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr) -> void;
  auto process_zip_data_event (syn::ZipDataEvent::raw_ptr) -> void;
  auto debug () -> void;
  auto process_http_request (const std::string& req, const std::string& body) -> process_res_type;
  auto process_request_event (const std::string& req, const std::string& body) -> process_res_type;
  auto process_request_file (const std::string& req, const std::string& body) -> process_res_type;
  auto process_request_event_debug (const std::string&, const std::string&, const std::string&) -> bool;

  ImplState                         impl_state_;         //< Состояние для реализации
  ImplState                         impl_ssl_state_;     //< Состояние для SSL реализации
  syn::Loader::ptr                  resource_loader_;    //< Загрузчик статических ресурсов (файлов, скриптов и т.п) в память
  std::string                       temp_folder_;        //< Базовая директория с ресурсами http сервера, доступна как на запись, таки и на чтение Обнуляется при рестарте сервера
  sync_type                         mtx_;                //< Для синхронизации доступа к заделяемым ресурсам между внешними агентами и потоком обработки запросов от http интерфейса
  id_msg2func_type                  int_catch_funcs_;    //< Функции-обработчики запросов, используются для тех сообщений, которые мы можем обработать внутри http сервера
  std::shared_ptr< WebSharedState > shared_state_;       //<
  SkipDataState                     skip_state_;         //<
  syn::ISystemProperty::raw_ptr     isys_ { nullptr };   //<
  // ids2bufs_type                     shared_ids2bufs_;   //< Хранилище для буферов с данными, которые приходят извне Разделяется между потоком обработки запросов от http интерфейса
};
}   // namespace modules::mhttp::appl
