#pragma once
/**
\file       detect-move-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dnodes::detectors::detect_move
{
/// Фильтр детектирования движения
class Filter final :
  public ::libs::icore::impl::base::obj::dll::IFilter,
  protected ::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()  = default;
  ~Filter () = default;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  auto init_pts (syn::ConnectInfo*) -> void;
  auto itransform (syn::TransformInfo&) -> void;
  auto get_move_count (syn::IVideoBuf::raw_ptr) -> std::int32_t;

  ::libs::optim::io::hioptim count_if_ge_;                                                                //< Быстрая функция вычисления "если больше"
  std::int64_t               count_detects_     = 0;                                                      //< Счетчик событий фиксации движения в последовательности
  boost::posix_time::ptime   time_first_detect_ = boost::posix_time::microsec_clock::universal_time ();   //< Время первого события детекции в текущей последовательности
};
}   // namespace dnodes::detectors::detect_move
