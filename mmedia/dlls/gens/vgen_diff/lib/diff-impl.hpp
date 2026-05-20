#pragma once
/**
\brief      Filter for corrected image
\file       diff-impl.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_vgen_diff_lib
*/

namespace dlls::gens::vgen_diff::lib
{
/// Реализация алгоритма вычисления разности между двумя кадрами
/// Используется, как минимум, в двух фильтрах: фильтре вычисления разности и фильтре вычисления детекции движения в кадре
class DiffImpl final
{
  public:
  DiffImpl ();
  ~DiffImpl ();

  void set_props (syn::VideoDiffProp::craw_ptr props);
  void set_transform_info (syn::TransformInfo*);
  void init ();
  void itransform (const syn::NodeID& id_node, ::libs::bufs::Bufs& pbufs);
  void make_diff_buf (const syn::NodeID& id_node, const syn::IVideoBuf& csrc1, syn::IVideoBuf& csrc2res);
  void bin_buf (const syn::NodeID& id_node, const std::int16_t bound, const std::int16_t val, syn::IVideoBuf* pdst);

  private:
  //  internal typess
  using off2bufs_type = std::unordered_map< ::utils::dbufs::video::consts::offs::off_buf_type, syn::IVideoBuf::ptr >;

  syn::VideoDiffProp::craw_ptr props_;           //< Свойства вычисления разности
  off2bufs_type                indx2prev_buf_;   //< Поле поиска предыдущего буфера (если он существует) по его индексу
  syn::IVideoBuf::ptr          temp_buf_;        //< Временный буфер для хранения текущего кадра, если источник и назначение разницы совпадают
  ::libs::optim::io::hioptim   cmp_get_const_;   //< Функция сравнения D[i] > Const1 ? Const2 : 0
  ::libs::optim::io::hioptim   abs_diff_;        //< Функция вычисления абсолютной разности между двумя изображениями
  syn::IMCaller::ptr           pthreads_;        //< Пул потоков для обработки данных
  syn::TransformInfo*          transinfo_;       //< Указатель на текущий параметр при вызове функции transform
};
}   // namespace dlls::gens::vgen_diff::lib
