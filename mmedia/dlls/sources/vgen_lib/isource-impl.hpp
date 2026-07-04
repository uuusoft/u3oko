#pragma once
/**
\file       isource-impl.hpp
\author     Erashov Anton erashov2026@proton.me
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
  U3_ADD_POINTERS_TO_SELF (ISourceImpl)
  U3_ADD_DELETE_MOVE_COPY (ISourceImpl)

  ISourceImpl ()          = default;
  virtual ~ISourceImpl () = default;

  auto init () -> void;
  void start ();
  void stop ();
  void get_sources (std::vector< syn::DataSourceInfo >&);
  void get_raw_data (syn::pkeys2bufs_type&, syn::tevents_type*);
  void set_cpu (syn::CpuExts);
  void update_source_info (const SourceImplInfo&);
  bool is_source_started ();

  protected:
  SourceImplInfo srcimpinfo_;                              //<
  bool           started_         = false;                 //< Флаг запуска процесса захвата
  bool           send_interfaces_ = false;                 //< Флаг посылки сообщения с интерфейсом кодека, чтобы управлять устройством
  syn::CpuExts   simd_            = syn::CpuExts::usual;   //< Используемое расширение CPU

  private:
  // ISourceImpl interface
  virtual void init_int ()                                                  = 0;
  virtual void start_int ()                                                 = 0;
  virtual void stop_int ()                                                  = 0;
  virtual void get_sources_int (std::vector< syn::DataSourceInfo >&)        = 0;
  virtual void get_raw_data_int (syn::pkeys2bufs_type&, syn::tevents_type*) = 0;
  virtual void set_cpu_int (syn::CpuExts)                                   = 0;
  virtual void update_source_info_int (const SourceImplInfo&)               = 0;
  virtual bool is_source_started_int ();
};
}   // namespace dlls::sources::gen_lib
