#pragma once
/**
\file       fake-vgen-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_fake_vgen
*/

namespace dlls::sources::fake_vgen
{
/// Реализация генератора видео для тестов.
class SourceImpl final : public ::dlls::sources::gen_lib::ISourceImpl
{
  public:
  SourceImpl ();
  virtual ~SourceImpl ();

  private:
  //  internal typess
  using gen_func_type    = std::function< void (std::uint32_t width, std::uint32_t height, std::uint32_t stride, std::uint8_t* beg_buf) >;   //<
  using gen_funcs_type   = std::unordered_map< ::libs::helpers::uids::minor::id_val, gen_func_type >;                                        //< Тип соответствия между индентификатором пикселей выходного формата и функции генерации
  using rvals_array_type = std::array< std::uint8_t, 255 >;                                                                                  //< Тип для хранения случайно сгенерированных чисел

  //  ::dlls::sources::gen_lib::ISourceImpl
  virtual void init_int () override;
  virtual void start_int () override;
  virtual void stop_int () override;
  virtual void get_sources_int (std::vector< syn::DataSourceInfo >& sources) override;
  virtual void get_raw_data_int (syn::pkeys2bufs_type& bufs, syn::tevents_type* events) override;
  virtual void set_cpu_int (::libs::helpers::sys::cpu::CpuExts current_optim) override;
  virtual void update_source_info_int (const syn::SourceImplInfo& info) override;
  //  internals
  bool free_int ();
  void init_gen_funcs ();
  void fill_rand_vals ();

  rvals_array_type         rand_bcomp_;        //< Случайные числа для генерации шума
  std::uint64_t            indx_bcomp_;        //< Индекс в массиве случайных чисел
  boost::posix_time::ptime time_last_frame_;   //< Время последнег выданного кадра
  std::uint64_t            counter_frames_;    //< Счетчик выданных кадров
  gen_funcs_type           gen_funcs_;         //< Функции для генерации изображения с заданным форматом пиксела
};

}   // namespace dlls::sources::fake_vgen
