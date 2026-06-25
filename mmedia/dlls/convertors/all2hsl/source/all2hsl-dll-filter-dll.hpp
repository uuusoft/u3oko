#pragma once
/**
\file       all2hsl-dll-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
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
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  auto init_pts (::libs::icore::impl::var1::obj::ConnectInfo*) -> void;
  auto alloc_fake_frame (::libs::icore::impl::var1::obj::dll::TransformInfo&) -> void;
  auto itransform () -> void;
  auto alloc_bufs () -> void;
  auto alloc_temp_bufs () -> void;
  auto duplicate_bufs () -> void;
  auto flip_y_bufs () -> void;
  auto convert_bufs_from_rgb () -> void;
  auto convert_bufs_from_y16 () -> void;
  auto convert_bufs_from_y8 () -> void;

  ::libs::optim::io::hioptim fx8_to_x16_;            //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim rgb24_to_hsl_;          //< Указатель на реализиацию по преобразованию RGB24 в HSL
  ::libs::optim::io::hioptim rgb24_to_l_fast_;       //< Указатель на реализиацию по преобразованию RGB24 в Y8
  ::libs::optim::io::hioptim rgb24_to_l_accurate_;   //< Указатель на реализиацию по преобразованию RGB24 в Y8
  ::libs::optim::io::hioptim set_const_func_;        //< Указатель на реализиацию по установки буфера в константу
  ::libs::optim::io::hioptim scale_func_;            //< Указатель на реализиацию масштабирования изображения
  ::libs::optim::io::hioptim flip_y_;                //< Указатель на реализиацию по вертикальной инверсии изображения
};
}   // namespace dlls::convertors::all2hsl
