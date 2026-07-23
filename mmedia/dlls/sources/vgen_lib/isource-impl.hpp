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
  auto start () -> void;
  auto stop () -> void;
  auto get_sources (std::vector< syn::DataSourceInfo >&) -> void;
  auto get_raw_data (syn::pkeys2bufs_type&, syn::tevents_type*) -> void;
  auto set_cpu (syn::CpuExts) -> void;
  auto update_source_info (const SourceImplInfo&) -> void;
  auto is_source_started () -> bool;

  protected:
  SourceImplInfo srcimpinfo_;                     //<
  bool           started_ { false };              //< Флаг запуска процесса захвата
  bool           send_interfaces_ { false };      //< Флаг посылки сообщения с интерфейсом кодека, чтобы управлять устройством
  syn::CpuExts   simd_ { syn::CpuExts::usual };   //< Используемое расширение CPU

  private:
  // ISourceImpl interface
  virtual auto init_int () -> void                                                  = 0;
  virtual auto start_int () -> void                                                 = 0;
  virtual auto stop_int () -> void                                                  = 0;
  virtual auto get_sources_int (std::vector< syn::DataSourceInfo >&) -> void        = 0;
  virtual auto get_raw_data_int (syn::pkeys2bufs_type&, syn::tevents_type*) -> void = 0;
  virtual auto set_cpu_int (syn::CpuExts) -> void                                   = 0;
  virtual auto update_source_info_int (const SourceImplInfo&) -> void               = 0;
  virtual auto is_source_started_int () -> bool;
};
}   // namespace dlls::sources::gen_lib
