#pragma once
/**
\file       link-creator-proxy.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::ilink
{
/// Фабрика для создания связи и передачи данных между подсистемами
/// Гарантируется единственность существования реализации (не экземпляров данного класса, который является фактически прокси к реализации)
/// внутри одного процесса (это необходимое и достаточное условие для любой реализации)
class LinkCreatorProxy final : protected ::libs::utility::proxy::MemProxyBase
{
  public:
  //  ext types
  using create_func_type = ::libs::link::ILinkCreator::raw_ptr ();

  U3_ADD_POINTERS_TO_SELF (LinkCreatorProxy)

  static LinkCreatorProxy::raw_ptr
  instance ()
  {
    static LinkCreatorProxy g_inst;
    return &g_inst;
  }

  ::libs::link::ILinkCreator::raw_ptr
  impl ()
  {
    ::libs::utility::checks::throw_ifn (pimpl_);
    ::libs::utility::checks::throw_ifn ((bool) *pimpl_);
    return pimpl_->get ();
  }

  private:
  LinkCreatorProxy ();
  virtual ~LinkCreatorProxy ();

  ::libs::link::ILinkCreator::ptr* pimpl_ { nullptr };   //<
};
}   // namespace libs::ilink
