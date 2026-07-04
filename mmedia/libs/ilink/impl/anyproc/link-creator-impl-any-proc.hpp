#pragma once
/**
\file       link-creator-impl-any-proc.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::anyproc
{
class LinkCreatorImplAnyProc : public ::libs::link::ILinkCreator
{
  public:
  LinkCreatorImplAnyProc ()          = default;
  virtual ~LinkCreatorImplAnyProc () = default;

  //  ::libs::link::ILinkCreator impl
  virtual ::libs::link::ILink::ptr get_connect (const ::libs::link::CreateInfo&) override;
  virtual ::libs::link::ILink::ptr get_listen (const ::libs::link::CreateInfo&) override;
  virtual ::libs::link::ILink::ptr get_connect (const ::libs::link::details::ModuleLinks&) override;
  virtual ::libs::link::ILink::ptr get_listen (const ::libs::link::details::ModuleLinks&) override;
  virtual bool                     close_all () override;

  private:
  //  internal typess
  using helper2ptr_type  = boost::unordered_flat_map< ::libs::link::details::ModuleLinks, ::libs::link::ILink::ptr >;
  using type_helper2info = boost::unordered_flat_map< ::libs::link::details::ModuleLinks, ::libs::link::CreateInfo >;
  using sync_type        = std::mutex;
  using lock_type        = std::scoped_lock< sync_type >;

  sync_type mtx_;   //<
};
}   // namespace libs::ilink::impl::anyproc
