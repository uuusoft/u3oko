#pragma once
/**
\file       med3-impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med3
{
/// Медианая фильтрация во временной области
/// Решение основанное на частичной сортировке
/// Здесь мы не сортируем каждый раз весь массив, а используем уже отсортированный (исключая новый элемент) на предыдущем шаге
/// На данный момент скорость работы оставляет желать лучшего, приимущество перед версии 2 начинает проявляться с 30 буфера.
class Med3Impl final : public IFilterImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Med3Impl)

  Med3Impl ();
  virtual ~Med3Impl ();

  private:
  //  internal typess
  using src2meds_type = std::unordered_map< ::utils::dbufs::video::consts::offs::off_buf_type, BuffMed3Impl >;
  //  IFilterImpl overrides
  virtual void transform_int (const ::libs::core::graph::NodeID& id_node, ::libs::icore::impl::var1::obj::dll::TransformInfo& transform_info, InfoFilter& finfo, ::libs::bufs::Bufs* pbuf) override;
  virtual void load_int () override;
  virtual void sync_int () override;

  ::libs::optim::mcalls::IMCaller::ptr pthreads_;   //< Пул рабочих потоков
  src2meds_type                        mbufs_;      //< Буфера медианной фильтрации связанные с буферами-источниками данных
};
}   // namespace dlls::filter_noise::time::impl::med3
