#pragma once
/**
\file       detect-move-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_detect_move
*/

namespace dlls::detectors::detect_move
{
/// Фильтр детектирования движения
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (syn::CallInterfInfo& info) override;

  void         init_pts (syn::ConnectInfo* info);
  void         itransform (syn::TransformInfo& info);
  std::int32_t get_move_count (syn::IVideoBuf::raw_ptr);

  ::libs::optim::io::hioptim count_if_ge_;         //< Быстрая функция вычисления "если больше"
  std::int64_t               count_detects_;       //< Счетчик событий фиксации движения в последовательности
  boost::posix_time::ptime   time_first_detect_;   //< Время первого события детекции в текущей последовательности
};
}   // namespace dlls::detectors::detect_move
