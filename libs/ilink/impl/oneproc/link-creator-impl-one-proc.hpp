#pragma once
/**
\file       link-creator-impl-one-proc.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace oneproc {
/**
  \brief  Реализация интерфейса для генерации объектов "связь" в сценарии работы системы в одном процессе.
  */
class LinkCreatorImplOneProc : public ::libs::link::ILinkCreator
{
  public:
  LinkCreatorImplOneProc ();

  virtual ~LinkCreatorImplOneProc ();

  //  ILinkCreator impl
  virtual ILink::ptr get_connect (const CreateInfo* _info) override;
  virtual ILink::ptr get_listen (const CreateInfo* _info) override;
  virtual ILink::ptr get_connect (const TypeLinkModules& _type) override;
  virtual ILink::ptr get_listen (const TypeLinkModules& _type) override;
  virtual bool       close_all () override;


  private:
  //  int types
  using sync_type       = std::mutex;
  using guard_type      = std::lock_guard<sync_type>;
  using helper2ptr_type = std::map<TypeLinkModules, InfoOneLink>;

  helper2ptr_type links_;      //< Хранилище открытых каналов передачи данных.
  sync_type       mtx_;        //< Мьютекс для синхронизации доступа к объекту.
};

}}}}      // namespace libs::ilink::impl::oneproc
