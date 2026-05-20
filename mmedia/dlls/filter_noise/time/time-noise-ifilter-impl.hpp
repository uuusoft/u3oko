#pragma once
/**
\file       time-noise-ifilter-impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

namespace dlls::filter_noise::time
{
// forward
struct InfoFilter;
/// Интерфейс, который должны поддерживать все реализаций данного типа фильтрации (во временной области)
class IFilterImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IFilterImpl)

  IFilterImpl () :
    sync_request_ (false)
  {
  }

  virtual ~IFilterImpl ()
  {
  }

  IFilterImpl& operator= (const IFilterImpl& obj) = delete;
  IFilterImpl (const IFilterImpl& obj)            = delete;

  //  IFilterImpl interface
  virtual void transform_int (const ::libs::core::graph::NodeID&, ::libs::icore::impl::var1::obj::dll::TransformInfo&, InfoFilter&, ::libs::bufs::Bufs*) = 0;
  virtual void load_int ()                                                                                                                               = 0;
  virtual void sync_int ()                                                                                                                               = 0;

  protected:
  bool sync_request_;   //< Флаг-требование синхронизировать внутренние данные к внешним
};
}   // namespace dlls::filter_noise::time
