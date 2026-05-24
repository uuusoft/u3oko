#pragma once
/**
\file       rang-filter.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::space::impl::rang
{
/// Ранговая фильтрация в пространственной области
/// Стандартное решение
class RangFilter final : public IFilterImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (RangFilter)

  RangFilter ();
  virtual ~RangFilter ();

  private:
  // IFilterImpl overrides
  virtual void transform_int (const ::libs::core::graph::NodeID&, space::syn::TransformInfo&, InfoFilter&, ::libs::bufs::Bufs*) override;
  virtual void load_int () override;

  /// Функция выбора наиболее подходящего алгоритма сортировки Учитывается длина сортируемой последовательности и ранг числа
  /// \return реализация
  IAlgImpl::ptr make_rang_impl (InfoFilter& finfo);

  ::libs::optim::mcalls::IMCaller::ptr                                  pthreads_;       //< Пул рабочих потоков
  ::libs::optim::io::hioptim::store_func_type                           store_call_;     //< Поле для многопоточного вызова
  ::libs::optim::io::hioptim                                            ext_call_;       //< Поле для многопоточного вызова
  ::utils::dbufs::video::IVideoBuf::ptr                                 temp_src_buf_;   //< Временный буфер, для хранения буфера-источника
  std::vector< ::dlls::filter_noise::space::impl::rang::IAlgImpl::ptr > algs_;           //< Массив реализации для каждого рабочего потока
  ::libs::ievents::props::videos::noises::space::ext::Sortings          sort_type_;      //< Тип сортировки
};
}   // namespace dlls::filter_noise::space::impl::rang
