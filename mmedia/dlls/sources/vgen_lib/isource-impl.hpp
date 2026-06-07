#pragma once
/**
\file       isource-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.06.2016
\project    u3_vgen_lib
*/

namespace dlls::sources::gen_lib
{
/// Интерфейс, который должна поддерживать любая реализация захвата данных из устройства
class ISourceImpl
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ISourceImpl)

  ISourceImpl ()          = default;
  virtual ~ISourceImpl () = default;

  ISourceImpl (const ISourceImpl& src)            = delete;
  ISourceImpl& operator= (const ISourceImpl& src) = delete;

  void init ();
  void start ();
  void stop ();
  void get_sources (std::vector< syn::DataSourceInfo >& sources);
  void get_raw_data (syn::pkeys2bufs_type& bufs, syn::tevents_type* events);
  void set_cpu (syn::CpuExts current_optim);
  void update_source_info (const SourceImplInfo& info);
  bool is_source_started ();

  protected:
  SourceImplInfo srcimpinfo_;                              //<
  bool           started_         = false;                 //< Флаг запуска процесса захвата
  bool           send_interfaces_ = false;                 //< Флаг посылки сообщения с интерфейсом кодека, чтобы управлять устройством
  syn::CpuExts   simd_            = syn::CpuExts::usual;   //< Используемое расширение CPU

  private:
  // ISourceImpl interface
  virtual void init_int ()                                                              = 0;
  virtual void start_int ()                                                             = 0;
  virtual void stop_int ()                                                              = 0;
  virtual void get_sources_int (std::vector< syn::DataSourceInfo >& sources)            = 0;
  virtual void get_raw_data_int (syn::pkeys2bufs_type& bufs, syn::tevents_type* events) = 0;
  virtual void set_cpu_int (syn::CpuExts current_optim)                                 = 0;
  virtual void update_source_info_int (const SourceImplInfo& info)                      = 0;
  virtual bool is_source_started_int ();
};
}   // namespace dlls::sources::gen_lib
