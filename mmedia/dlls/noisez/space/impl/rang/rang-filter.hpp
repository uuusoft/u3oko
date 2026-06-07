#pragma once
/**
\file       rang-filter.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_noisez
*/

namespace dlls::noisez::space::impl::rang
{
/// Ранговая фильтрация в пространственной области
/// Стандартное решение
class RangFilter final : public IFilterImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (RangFilter)

  using algs_storage_type = std::unordered_map< syn::Sortings, std::vector< IAlgImpl::ptr > >;

  RangFilter ();
  virtual ~RangFilter () = default;

  private:
  // IFilterImpl overrides
  virtual void transform_int (const ::libs::core::graph::NodeID&, space::syn::TransformInfo&, InfoFilter&, ::libs::bufs::Bufs*) override;
  virtual void load_int () override;

  /// Функция выбора наиболее подходящего алгоритма сортировки Учитывается длина сортируемой последовательности и ранг числа
  /// \return реализация
  IAlgImpl::ptr make_rang_impl (InfoFilter& finfo, syn::MedianSpaceFilterProp::raw_ptr impl_info);

  ::libs::optim::mcalls::IMCaller::ptr  pthreads_;                    //< Пул рабочих потоков
  ::libs::optim::io::hioptim::func_type store_call_;                  //< Поле для многопоточного вызова
  ::libs::optim::io::hioptim            ext_call_ { &store_call_ };   //< Поле для многопоточного вызова
  syn::IVideoBuf::ptr                   temp_src_buf_;                //< Временный буфер, для хранения буфера-источника
  algs_storage_type                     algs_;                        //< Массив реализации для каждого рабочего потока
};
}   // namespace dlls::noisez::space::impl::rang
