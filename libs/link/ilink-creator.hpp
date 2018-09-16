#pragma once
/**
\file       ilink-creator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link {
/**
\brief  Интерфейс для создания связи между модулями системы.
*/
class ILinkCreator
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ILinkCreator);

  virtual ~ILinkCreator ()
  {}

  ILinkCreator (const ILinkCreator& _src) = delete;
  ILinkCreator& operator= (const ILinkCreator& _src) = delete;
  //  ILinkCreator interface
  virtual ILink::ptr get_connect (const CreateInfo* _info)               = 0;
  virtual ILink::ptr get_listen (const CreateInfo* _info)                = 0;
  virtual ILink::ptr get_connect (const details::LinkModulesType& _type) = 0;
  virtual ILink::ptr get_listen (const details::LinkModulesType& _type)  = 0;
  virtual bool       close_all ()                                        = 0;


  protected:
  ILinkCreator ()
  {}
};

}}      // namespace libs::link
