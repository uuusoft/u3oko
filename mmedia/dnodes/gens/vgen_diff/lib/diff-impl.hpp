#pragma once
/**
\brief      Filter for corrected image
\file       diff-impl.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::gens::vgen_diff::lib
{
/// Реализация алгоритма вычисления разности между двумя кадрами
/// Используется, как минимум, в двух фильтрах: фильтре вычисления разности и фильтре вычисления детекции движения в кадре
class DiffImpl final
{
  public:
  DiffImpl ()  = default;
  ~DiffImpl () = default;

  void set_props (syn::VideoDiffProp::craw_ptr);
  void set_transform_info (syn::TransformInfo*);
  auto init () -> void;
  void itransform (const syn::NodeID&, ::libs::bufs::Bufs&);
  void make_diff_buf (const syn::NodeID&, const syn::IVideoBuf&, syn::IVideoBuf&);
  void bin_buf (const syn::NodeID&, const std::int16_t, const std::int16_t, syn::IVideoBuf*);

  private:
  //  internal typess
  using off2bufs_type = boost::unordered_flat_map< syn::persistent_off_buf_type, syn::IVideoBuf::ptr, ::libs::utility::utils::TransparentStringHash, std::equal_to<> >;

  syn::VideoDiffProp::craw_ptr props_ { nullptr };       //< Свойства вычисления разности
  off2bufs_type                indx2prev_buf_;           //< Поле поиска предыдущего буфера (если он существует) по его индексу
  syn::IVideoBuf::ptr          temp_buf_;                //< Временный буфер для хранения текущего кадра, если источник и назначение разницы совпадают
  ::libs::optim::io::hioptim   cmp_get_const_;           //< Функция сравнения D[i] > Const1 ? Const2 : 0
  ::libs::optim::io::hioptim   abs_diff_;                //< Функция вычисления абсолютной разности между двумя изображениями
  syn::IMCaller::ptr           pthreads_;                //< Пул потоков для обработки данных
  syn::TransformInfo*          transinfo_ { nullptr };   //< Указатель на текущий параметр при вызове функции transform
};
}   // namespace dnodes::gens::vgen_diff::lib
