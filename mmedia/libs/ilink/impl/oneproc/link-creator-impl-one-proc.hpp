#pragma once
/**
\file       link-creator-impl-one-proc.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
/// Реализация интерфейса для генерации объектов "связь" в сценарии работы системы в одном процессе
class LinkCreatorImplOneProc : public ::libs::link::ILinkCreator
{
  public:
  LinkCreatorImplOneProc ();
  virtual ~LinkCreatorImplOneProc ();

  //  ILinkCreator impl
  virtual ::libs::link::ILink::ptr get_connect (const ::libs::link::CreateInfo&) override;
  virtual ::libs::link::ILink::ptr get_listen (const ::libs::link::CreateInfo&) override;
  virtual ::libs::link::ILink::ptr get_connect (const ::libs::link::details::ModuleLinks&) override;
  virtual ::libs::link::ILink::ptr get_listen (const ::libs::link::details::ModuleLinks&) override;
  virtual bool                     close_all () override;

  private:
  //  internal typess
  using sync_type       = std::mutex;
  using lock_type       = std::lock_guard< sync_type >;
  using helper2ptr_type = std::unordered_map< ::libs::link::details::ModuleLinks, InfoOneLink >;

  helper2ptr_type links_;   //< Хранилище открытых каналов передачи данных
  sync_type       mtx_;     //< Мьютекс для синхронизации доступа к объекту
};
}   // namespace libs::ilink::impl::oneproc
