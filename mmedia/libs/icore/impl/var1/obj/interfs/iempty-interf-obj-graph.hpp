#pragma once
/**
\file       iempty-interf-obj-graph.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::interfs
{
/// Пустая реализация интерфейса-расширения, используется как сигнал поддержки интерфейса объектом графа, если кроме этого факта ничего больше не требуется
/// Можно считать возврат данного объекта как флаг true
class IEmptyInterfObjGraph final : public core::graph::IInterfGraphObj
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IEmptyInterfObjGraph)

  IEmptyInterfObjGraph ()
  {
  }

  virtual ~IEmptyInterfObjGraph ()
  {
  }

  IEmptyInterfObjGraph (const IEmptyInterfObjGraph& src)            = delete;
  IEmptyInterfObjGraph& operator= (const IEmptyInterfObjGraph& src) = delete;
};
}   // namespace libs::icore::impl::var1::obj::interfs
