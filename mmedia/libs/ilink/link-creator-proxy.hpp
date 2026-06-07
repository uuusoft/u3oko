#pragma once
/**
\file       link-creator-proxy.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink
{
/// Фабрика для создания связи и передачи данных между подсистемами
/// Гарантируется единственность существования реализации (не экземпляров данного класса, который является фактически прокси к реализации)
/// внутри одного процесса (это необходимое и достаточное условие для любой реализации)
class LinkCreatorProxy final : protected ::libs::helpers::proxy::MemProxyBase
{
  public:
  //  ext types
  using create_func_type = ::libs::link::ILinkCreator::raw_ptr ();

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (LinkCreatorProxy)

  static LinkCreatorProxy::raw_ptr
  instance ()
  {
    static LinkCreatorProxy g_inst;
    return &g_inst;
  }

  ::libs::link::ILinkCreator::raw_ptr
  impl ()
  {
    U3_ASSERT (pimpl_);
    U3_ASSERT (*pimpl_);
    return pimpl_->get ();
  }

  private:
  LinkCreatorProxy ();
  virtual ~LinkCreatorProxy () = default;

  ::libs::link::ILinkCreator::ptr* pimpl_ = nullptr;   //<
};
}   // namespace libs::ilink
