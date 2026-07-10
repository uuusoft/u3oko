#pragma once
/**
\file       space-noise-ifilter-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
*/

namespace dlls::noisez::space
{
/// Интерфейс, который должны поддерживать все реализаций данного типа фильтрации (т.е. в пространственной области)
class IFilterImpl
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (IFilterImpl)
  U3_ADD_DELETE_MOVE_COPY (IFilterImpl);

  IFilterImpl ()          = default;
  virtual ~IFilterImpl () = default;

  //  IFilterImpl interface
  virtual void transform_int (const ::libs::core::graph::NodeID&, ::libs::icore::impl::var1::obj::dll::TransformInfo&, InfoFilter&, ::libs::bufs::Bufs*) = 0;
  virtual void load_int ()                                                                                                                               = 0;
};
}   // namespace dlls::noisez::space
