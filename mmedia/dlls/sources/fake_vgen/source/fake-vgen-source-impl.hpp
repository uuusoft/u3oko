#pragma once
/**
\file       fake-vgen-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_fake_vgen
*/

namespace dlls::sources::fake_vgen
{
/// Реализация генератора видео для тестов
class SourceImpl final : public ::dlls::sources::gen_lib::ISourceImpl
{
  public:
  SourceImpl ();
  virtual ~SourceImpl ();

  private:
  //  internal typess
  using gen_func_type          = std::function< void (std::uint32_t, std::uint32_t, std::uint32_t, std::uint8_t*) >;   //<
  using gen_funcs_type         = boost::unordered_flat_map< syn::id_val, gen_func_type >;                              //< Тип соответствия между индентификатором пикселей выходного формата и функции генерации
  using random_vals_array_type = std::array< std::uint8_t, 255 >;                                                      //< Тип для хранения случайно сгенерированных чисел

  //  ::dlls::sources::gen_lib::ISourceImpl
  virtual auto init_int () -> void override;
  virtual auto start_int () -> void override;
  virtual auto stop_int () -> void override;
  virtual auto get_sources_int (std::vector< syn::DataSourceInfo >& sources) -> void override;
  virtual auto get_raw_data_int (syn::pkeys2bufs_type& bufs, syn::tevents_type* events) -> void override;
  virtual auto set_cpu_int (::libs::utility::sys::cpu::CpuExts current_optim) -> void override;
  virtual auto update_source_info_int (const syn::SourceImplInfo& info) -> void override;

  //  internals
  auto free_int () -> bool;
  auto init_gen_funcs () -> void;
  auto fill_rand_vals () -> void;

  random_vals_array_type   rand_bcomp_ {};       //< Случайные числа для генерации шума
  std::uint64_t            indx_bcomp_ = 0;      //< Индекс в массиве случайных чисел
  boost::posix_time::ptime time_last_frame_;     //< Время последнег выданного кадра
  std::uint64_t            frame_counter_ = 0;   //< Счетчик выданных кадров
  gen_funcs_type           gen_funcs_;           //< Функции для генерации изображения с заданным форматом пиксела
};

}   // namespace dlls::sources::fake_vgen
