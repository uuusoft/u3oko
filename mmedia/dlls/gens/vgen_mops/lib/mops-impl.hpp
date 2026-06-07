#pragma once
/**
\file       mops-impl.hpp
\date       01.10.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vgen_mops_lib
\brief      Объявление фильтра морфологических операций (МО)
*/

namespace dlls::gens::vgen_mops::lib
{
/// Релизация алогритма морфологических операций над изображением
class MopsImpl final
{
  public:
  MopsImpl ()  = default;
  ~MopsImpl () = default;

  void init ();
  void set_props (syn::VideoMorphologyProp::craw_ptr info);
  void set_transform_info (syn::TransformInfo*);
  void itransform (const syn::NodeID& id_node, ::libs::bufs::Bufs& pbufs);
  void alloc_bufs ();

  /// Реализация впомогательной функции бинаризации изображения
  /// Не является МО, но требуется для реализации МО через свертку
  /// \param[in]        b2b    параметры буфера
  /// \param[in]        bound  граница для пикселя
  /// \param[in]        val    значение, которое приобретает пиксель, если его начальное значение меньше bound
  /// \param[in, out ]  pdst буфер
  void bin_buf (
    const syn::NodeID&                id_node,
    const syn::MorphBuffInfo&         b2b,
    const std::int16_t                bound,
    const std::int16_t                val,
    ::utils::dbufs::video::IVideoBuf* pdst);

  private:
  syn::VideoMorphologyProp::craw_ptr                   props_ = nullptr;       //< Свойства морфологических операций, загруженных из xml
  ::dlls::gens::vgen_mops::lib::helpers::MorphOperator morph_helper_;          //< Вспомогательный объект, для реализации функционала МО, т.к возможно он будет использован в ряде лругих фильтров
  ::libs::optim::io::hioptim                           cmp_get_const_;         //< Функция сравнения для бинаризации изображения (подготовка буфера к МО через свертку)
  ::libs::optim::mcalls::IMCaller::ptr                 pthreads_;              //< Пул потоков для обработки данных
  syn::TransformInfo*                                  transinfo_ = nullptr;   //< Указатель на текущий параметр при вызове функции transform
};
}   // namespace dlls::gens::vgen_mops::lib
