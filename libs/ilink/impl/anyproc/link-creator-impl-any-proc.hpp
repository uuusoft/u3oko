#pragma once
/**
\file       link-creator-impl-any-proc.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace anyproc {
/**
  \brief  empty brief
  */
class LinkCreatorImplAnyProc : public ::libs::link::ILinkCreator
{
  public:
  LinkCreatorImplAnyProc ();

  virtual ~LinkCreatorImplAnyProc ();

  //  ::libs::link::ILinkCreator impl
  virtual ::libs::link::ILink::ptr get_connect (const ::libs::link::CreateInfo* _info) override;
  virtual ::libs::link::ILink::ptr get_listen (const ::libs::link::CreateInfo* _info) override;
  virtual ::libs::link::ILink::ptr get_connect (const LinkModulesType& _type) override;
  virtual ::libs::link::ILink::ptr get_listen (const LinkModulesType& _type) override;
  virtual bool                     close_all () override;


  private:
  //  int types
  using helper2ptr_type  = std::map<LinkModulesType, ::libs::link::ILink::ptr>;
  using type_helper2info = std::map<LinkModulesType, ::libs::link::CreateInfo>;
  using sync_type        = std::mutex;
  using guard_type       = std::lock_guard<sync_type>;

  sync_type mtx_;      //< ???
};

}}}}      // namespace libs::ilink::impl::anyproc
