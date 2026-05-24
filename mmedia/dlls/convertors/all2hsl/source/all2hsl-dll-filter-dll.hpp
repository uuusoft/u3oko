#pragma once
/**
\file       all2hsl-dll-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_all2hsl
*/

namespace dlls::convertors::all2hsl
{
/// Фильтр для преобразования всех поддерживаемых форматов в HSL
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void alloc_fake_frame (::libs::icore::impl::var1::obj::dll::TransformInfo& info);
  void itransform ();
  void alloc_bufs ();
  void alloc_temp_bufs ();
  void duplicate_bufs ();
  void flip_y_bufs ();
  void convert_bufs_from_rgb ();
  void convert_bufs_from_y16 ();
  void convert_bufs_from_y8 ();

  ::libs::optim::io::hioptim fx8_to_x16_;            //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim rgb24_to_hsl_;          //< Указатель на реализиацию по преобразованию RGB24 в HSL
  ::libs::optim::io::hioptim rgb24_to_l_fast_;       //< Указатель на реализиацию по преобразованию RGB24 в Y8
  ::libs::optim::io::hioptim rgb24_to_l_accurate_;   //< Указатель на реализиацию по преобразованию RGB24 в Y8
  ::libs::optim::io::hioptim set_const_func_;        //< Указатель на реализиацию по установки буфера в константу
  ::libs::optim::io::hioptim scale_func_;            //< Указатель на реализиацию масштабирования изображения
  ::libs::optim::io::hioptim flip_y_;                //< Указатель на реализиацию по вертикальной инверсии изображения
};
}   // namespace dlls::convertors::all2hsl
