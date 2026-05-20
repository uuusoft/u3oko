#pragma once
/**
\file       med3-impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med1
{
/**
  \brief  Медианая фильтрация во временной области.
          Решение в лоб, тестовый вариант для сравнения.
*/
class Med1Impl final : public IFilterImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Med1Impl)

  Med1Impl ();
  virtual ~Med1Impl ();

  private:
  //  internal typess
  using src2meds_type = std::unordered_map< ::utils::dbufs::video::consts::offs::off_buf_type, BuffMed1Impl >;
  //  IFilterImpl overrides
  virtual void transform_int (const ::libs::core::graph::NodeID& id_node, ::libs::icore::impl::var1::obj::dll::TransformInfo& transform_info, InfoFilter& finfo, ::libs::bufs::Bufs* pbuf) override;
  virtual void load_int () override;
  virtual void sync_int () override;

  ::libs::optim::mcalls::IMCaller::ptr pthreads_;   //< Пул рабочих потоков
  src2meds_type                        mbufs_;      //< Буфера медианной фильтрации связанные с буферами-источниками данных
};
}   // namespace dlls::filter_noise::time::impl::med1
