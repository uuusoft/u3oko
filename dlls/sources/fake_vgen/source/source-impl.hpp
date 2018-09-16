#pragma once
/**
\file       source-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_fake_vgen
\brief      Объявление типов генерации видео для тестов.
*/

namespace dlls { namespace sources { namespace fake_vgen {
/**
\brief  Реализация генератора видео для тестов.
*/
class SourceImpl final : public ::dlls::sources::gen_lib::ISourceImpl
{
  public:
  //  ext types
  using make_buff_funct_type = std::function<void(std::size_t _width, std::size_t _height, std::size_t _stride, unsigned char* _beg_buff)>;

  SourceImpl ();

  virtual ~SourceImpl ();


  private:
  //  int types
  using make_buff_functs_type = std::map<cuuid, make_buff_funct_type>;      //< Тип соответствия между индентификатором пикселей выходного формата и функции генерации.
  using rvals_array_type      = std::array<unsigned char, 255>;             //< Тип для хранения случайно сгенерированных чисел.

  //  ::dlls::sources::gen_lib::ISourceImpl
  virtual void init_int () override;
  virtual void start_int () override;
  virtual void stop_int () override;
  virtual void get_raw_data_int (keys2buffs_ptr_type& _buffs, transform_events_type* _events) override;
  virtual void set_cpu_int (::libs::helpers::sys::cpu::TypeExtCpu current_optim) override;
  virtual void update_dinfo_int (const gen_lib::SourceInfo& _info) override;

  bool free_int ();

  void init_make_buff_functs ();

  void fill_rand_vals ();

  rvals_array_type         rand_bcomp_;            //< Случайные числа для генерации шума.
  std::size_t              indx_bcomp_;            //< Индекс в массиве случайных чисел.
  boost::posix_time::ptime time_last_frame_;       //< Время последнег выданного кадра.
  long long                counter_frames_;        //< Счетчик выданных кадров.
  make_buff_functs_type    make_buff_functs_;      //< Функции для генерации изображения с заданным форматом пиксела.
};

}}}      // namespace dlls::sources::fake_vgen
