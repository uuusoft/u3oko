#pragma once
/**
\file       link-creator-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink {
/**
  \brief  Фабрика для создания связи и передачи данных между подсистемами.
          Гарантируется единственность существования реализации (не экземпляров данного класса, который является фактически прокси к реализации)
          внутри одного процесса (это необходимое и достаточное условие для любой реализации).
  */
class LinkCreatorProxy : protected ::libs::helpers::proxy::MemProxyBase
{
  public:
  //  ext types
  using create_funct_type = ::libs::link::ILinkCreator::raw_ptr ();
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (LinkCreatorProxy);

  static LinkCreatorProxy::raw_ptr
  instance ()
  {
    static LinkCreatorProxy g_inst;
    return &g_inst;
  }

  ::libs::link::ILinkCreator::raw_ptr
  impl ()
  {
    UASSERT (pimpl_);
    UASSERT (*pimpl_);
    return pimpl_->get ();
  }


  private:
  LinkCreatorProxy ();

  ~LinkCreatorProxy ();

  ::libs::link::ILinkCreator::ptr* pimpl_;      //< ???
};

}}      // namespace libs::ilink
