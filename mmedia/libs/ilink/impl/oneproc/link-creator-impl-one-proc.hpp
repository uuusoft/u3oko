#pragma once
/**
\file       link-creator-impl-one-proc.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
/// Реализация интерфейса для генерации объектов "связь" в сценарии работы системы в одном процессе
class LinkCreatorImplOneProc final : public ::libs::link::ILinkCreator
{
  public:
  LinkCreatorImplOneProc ()          = default;
  virtual ~LinkCreatorImplOneProc () = default;

  //  ILinkCreator impl
  virtual auto get_connect (const ::libs::link::CreateInfo&) -> ::libs::link::ILink::ptr override;
  virtual auto get_listen (const ::libs::link::CreateInfo&) -> ::libs::link::ILink::ptr override;
  virtual auto get_connect (const ::libs::link::details::ModuleLinks&) -> ::libs::link::ILink::ptr override;
  virtual auto get_listen (const ::libs::link::details::ModuleLinks&) -> ::libs::link::ILink::ptr override;
  virtual auto close_all () -> bool override;

  private:
  //  internal typess
  using sync_type       = std::mutex;
  using lock_type       = std::scoped_lock< sync_type >;
  using helper2ptr_type = boost::unordered_flat_map< ::libs::link::details::ModuleLinks, InfoOneLink >;

  helper2ptr_type links_;   //< Хранилище открытых каналов передачи данных
  sync_type       mtx_;     //< Мьютекс для синхронизации доступа к объекту
};
}   // namespace libs::ilink::impl::oneproc
