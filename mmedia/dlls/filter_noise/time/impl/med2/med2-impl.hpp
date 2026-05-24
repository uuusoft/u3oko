#pragma once
/**
\file       med2-impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med2
{
/// Медианая фильтрация во временной области
/// Стандартное решение
class Med2Impl final : public IFilterImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Med2Impl)

  Med2Impl ();
  virtual ~Med2Impl ();

  private:
  //  internal typess
  using src2meds_type = std::unordered_map< ::utils::dbufs::video::consts::offs::off_buf_type, BuffMed2Impl >;
  //  IFilterImpl overrides
  virtual void transform_int (const ::libs::core::graph::NodeID& id_node, syn::TransformInfo& transform_info, InfoFilter& finfo, ::libs::bufs::Bufs* pbuf) override;
  virtual void load_int () override;
  virtual void sync_int () override;

  ::libs::optim::mcalls::IMCaller::ptr        pthreads_;     //< Пул рабочих потоков
  src2meds_type                               mbufs_;        //< Буфера медианной фильтрации связанные с буферами-источниками данных
  ::libs::optim::io::hioptim::store_func_type store_call_;   //< Поле для многопоточного вызова
  ::libs::optim::io::hioptim                  ext_call_;     //< Поле для многопоточного вызова
};
}   // namespace dlls::filter_noise::time::impl::med2
