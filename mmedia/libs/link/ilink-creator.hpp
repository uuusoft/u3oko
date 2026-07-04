#pragma once
/**
\file       ilink-creator.hpp
\author     Erashov Anton erashov2026@proton.me
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
  U3_ADD_POINTERS_TO_SELF (ILinkCreator)

  virtual ~ILinkCreator () = default;

  ILinkCreator (const ILinkCreator&)                = delete;
  ILinkCreator& operator= (const ILinkCreator&)     = delete;
  ILinkCreator (ILinkCreator&&) noexcept            = delete;
  ILinkCreator& operator= (ILinkCreator&&) noexcept = delete;

  //  ILinkCreator interface
  virtual auto get_connect (const CreateInfo&) -> ILink::ptr           = 0;
  virtual auto get_listen (const CreateInfo&) -> ILink::ptr            = 0;
  virtual auto get_connect (const details::ModuleLinks&) -> ILink::ptr = 0;
  virtual auto get_listen (const details::ModuleLinks&) -> ILink::ptr  = 0;
  virtual auto close_all () -> bool                                    = 0;

  protected:
  ILinkCreator () = default;
};
}   // namespace libs::link
