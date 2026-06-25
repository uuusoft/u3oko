#pragma once
/**
\file       detect-face-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_detect_face
*/

namespace dlls::detectors::detect_face
{
///  Фильтр детектирования лица
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter () = default;
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual auto load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) -> void override;
  virtual auto transform_int (syn::TransformInfo& info) -> void override;
  virtual auto call_int (syn::CallInterfInfo& info) -> void override;

  auto init_pts (syn::ConnectInfo* info) -> void;
  auto itransform (syn::TransformInfo& info) -> void;
  // void save_buf2file (const std::string& file_name, int counter, int quality, syn::IVideoBuf::raw_ptr psrc);
  // void convert_buf2rgb24 (syn::IVideoBuf::craw_ptr psrc, syn::IVideoBuf::raw_ptr pdst);

  ::libs::optim::io::hioptim fx16_x8_;                   //< Указатель на реализацию по преобразованию формата кадра из X16 в X8
  syn::IVideoBuf::ptr        temp_buf_;                  //< Временный буфер для хранения подготовленного к сжатию кадра в совместимом для этого формате (RGB, Y8, etc)
  tjhandle                   hjpeg_         = nullptr;   //< Устройство для кодирования jpeg для отладки
  std::uint8_t*              jpeg_buf_      = nullptr;   //< Буфер библиотеки JPEG для кодирования
  std::uint32_t              size_jpeg_buf_ = 0;         //< Размер буфера для кодирования
};
}   // namespace dlls::detectors::detect_face
