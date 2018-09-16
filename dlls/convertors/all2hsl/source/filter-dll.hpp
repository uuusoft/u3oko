//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       filter-dll.hpp
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_all2hsl
\brief      empty brief
*/

namespace dlls { namespace convertors { namespace all2hsl {
/**
\brief  Фильтр для преобразования всех поддерживаемых форматов в HSL.
*/
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  virtual ~Filter ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void alloc_fake_frame (TransformInfo& _info);

  void itransform ();

  void alloc_buffs ();

  void alloc_temp_buffs ();

  void duplicate_buffs ();

  void flip_y_buffs ();

  void convert_buffs_from_rgb ();

  void convert_buffs_from_y16 ();

  void convert_buffs_from_y8 ();

  ::libs::optim::io::hioptim fx8_to_x16_;               //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim rgb24_to_hsl_;             //< Указатель на реализиацию по преобразованию RGB24 в HSL.
  ::libs::optim::io::hioptim rgb24_to_l_fast_;          //< Указатель на реализиацию по преобразованию RGB24 в Y8.
  ::libs::optim::io::hioptim rgb24_to_l_accurate_;      //< Указатель на реализиацию по преобразованию RGB24 в Y8.
  ::libs::optim::io::hioptim set_const_funct_;          //< Указатель на реализиацию по установки буфера в константу.
  ::libs::optim::io::hioptim scale_funct_;              //< Указатель на реализиацию масштабирования изображения.
  ::libs::optim::io::hioptim flip_y_;                   //< Указатель на реализиацию по вертикальной инверсии изображения.
};

}}}      // namespace dlls::convertors::all2hsl
