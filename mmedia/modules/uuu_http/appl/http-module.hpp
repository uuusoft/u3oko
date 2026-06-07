#pragma once
/**
\file       http-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_http_module
*/

namespace modules::uuu_http::appl
{
/// Реализация интерфейса модуля для функционала HTTP сервер
class HttpModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  //  ext types
  using process_res_type = modules::uuu_http::impl::beast::handler_func_res_type;   // data + mime + status http

  HttpModule ();
  virtual ~HttpModule () = default;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  using sync_type        = std::mutex;
  using lock_type        = std::scoped_lock< sync_type >;
  using ids2bufs_type    = std::unordered_map< std::string, Id2BufInfo >;
  using impl_server_type = std::shared_ptr< impl::beast::listener >;

  //  IApplication overrides
  virtual void init_appl_data_int () override;

  //  BaseModule overrides
  virtual void appl_init_int (const syn::InitApplication& info) override;
  virtual void init_links_int (const syn::InitApplication& info) override;
  virtual void init_proxys_int () override;
  virtual bool appl_deinit_int () override;
  virtual void update_catch_funcs_int () override;

  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (syn::IEvent::ptr& evnt) override;
  virtual bool            is_now_thread_to_sleep (bool now_recv_evnt) override;

  // internal
  void check_process ();
  void run_http_server ();
  void stop_http_server ();
  void prepare_resources ();
  void create_rw_copy ();
  void delete_rw_copy ();
  void load_def_resource2mem ();
  void process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr);
  void process_zip_data_event (syn::ZipDataEvent::raw_ptr);
  void debug ();

  process_res_type process_http_request (const std::string& req, const std::string& body);
  process_res_type process_request_event (const std::string& req, const std::string& body);
  process_res_type process_request_file (const std::string& req, const std::string& body);
  bool             process_request_event_debug (const std::string&, const std::string&, const std::string&);

  impl_server_type                  impl_;               //< Реализация сервера
  std::thread                       impl_thread_;        //< Поток для сервера
  std::thread                       ssl_impl_thread_;    //< Поток для сервера
  std::vector< std::thread >        work_threads_;       //< Рабочие потоки
  std::vector< std::thread >        ssl_work_threads_;   //< Рабочие потоки
  syn::Loader::ptr                  resource_loader_;    //< Загрузчик статических ресурсов (файлов, скриптов и т.п) в память
  std::string                       temp_folder_;        //< Базовая директория с ресурсами http сервера, доступна как на запись, таки и на чтение Обнуляется при рестарте сервера
  sync_type                         mtx_;                //< Для синхронизации доступа к заделяемым ресурсам между внешними агентами и потоком обработки запросов от http интерфейса
  ids2bufs_type                     shared_ids2bufs_;    //< Хранилище для буферов с данными, которые приходят извне Разделяется между потоком обработки запросов от http интерфейса
  id_msg2func_type                  int_catch_funcs_;    //< Функции-обработчики сообщений со стороны http клиента пользуются для тех сообщений, которые мы можем (и должны) обработать внутри htpp сервера
  std::shared_ptr< WebSharedState > shared_state_;       //<
  SkipDataState                     skip_state_;         //<
  syn::ISystemProperty::raw_ptr     isys_ = nullptr;     //<
};
}   // namespace modules::uuu_http::appl
