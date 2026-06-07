#pragma once
/**
\file       ilink-creator.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_link
*/

namespace libs::link
{
/// Интерфейс для создания связи между модулями системы
class ILinkCreator
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ILinkCreator)

  virtual ~ILinkCreator () = default;

  ILinkCreator (const ILinkCreator&)            = delete;
  ILinkCreator& operator= (const ILinkCreator&) = delete;

  //  ILinkCreator interface
  virtual ILink::ptr get_connect (const CreateInfo&)           = 0;
  virtual ILink::ptr get_listen (const CreateInfo&)            = 0;
  virtual ILink::ptr get_connect (const details::ModuleLinks&) = 0;
  virtual ILink::ptr get_listen (const details::ModuleLinks&)  = 0;
  virtual bool       close_all ()                              = 0;

  protected:
  ILinkCreator () = default;
};
}   // namespace libs::link
