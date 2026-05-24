/**
\file       link-creator-impl-one-proc.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-creator-impl-one-proc.hpp"

namespace libs::ilink::impl::oneproc
{
LinkCreatorImplOneProc::LinkCreatorImplOneProc ()
{
}


LinkCreatorImplOneProc::~LinkCreatorImplOneProc ()
{
}


::libs::link::ILink::ptr
LinkCreatorImplOneProc::get_connect (const ::libs::link::CreateInfo& info)
{
  ::libs::link::ILink::ptr ret;

  {
    lock_type    lock (mtx_);
    InfoOneLink& sublink = links_[info.pt2pt_];
    auto&        wret    = sublink.client_;

    ret = wret.lock ();
    if (ret)
    {
      return ret;
    }

    if (!sublink.impl_)
    {
      sublink.impl_ = std::make_shared< LinkImplOneProcInt > ();
    }

    oneproc::LinkImplOneProcInt::weak_ptr tempp = oneproc::LinkImplOneProcInt::weak_ptr (sublink.impl_);

    ret  = std::make_shared< oneproc::LinkImplOneProc > (tempp);
    wret = ret;
  }

  U3_CHECK_NT (ret->connect (info), "LinkCreatorImplOneProc::get_connect");
  U3_ASSERT (ret);
  return ret;
}


::libs::link::ILink::ptr
LinkCreatorImplOneProc::get_listen (const ::libs::link::CreateInfo& info)
{
  ::libs::link::ILink::ptr ret;

  {
    lock_type    lock (mtx_);
    InfoOneLink& sublink = links_[info.pt2pt_];
    auto&        wret    = sublink.server_;

    ret = wret.lock ();
    if (ret)
    {
      return ret;
    }

    if (!sublink.impl_)
    {
      sublink.impl_ = std::make_shared< LinkImplOneProcInt > ();
    }

    auto tempp = oneproc::LinkImplOneProcInt::weak_ptr (sublink.impl_);
    ret        = std::make_shared< oneproc::LinkImplOneProc > (tempp);
    wret       = ret;
  }

  U3_CHECK_NT (ret->listen (info), "LinkCreatorImplOneProc::get_listen");
  U3_ASSERT (ret)
  return ret;
}


::libs::link::ILink::ptr
LinkCreatorImplOneProc::get_connect (const ::libs::link::details::ModuleLinks& type)
{
  lock_type    lock (mtx_);
  InfoOneLink& sublink = links_[type];
  auto         wret    = sublink.client_;
  auto         ret     = wret.lock ();
  U3_ASSERT (ret);
  return ret;
}


::libs::link::ILink::ptr
LinkCreatorImplOneProc::get_listen (const ::libs::link::details::ModuleLinks& type)
{
  lock_type    lock (mtx_);
  InfoOneLink& sublink = links_[type];
  auto         wret    = sublink.server_;
  auto         ret     = wret.lock ();
  U3_ASSERT (ret);
  return ret;
}


bool
LinkCreatorImplOneProc::close_all ()
{
  lock_type lock (mtx_);
  for (helper2ptr_type::value_type& sublinks : links_)
  {
    sublinks.second.client_.reset ();
    sublinks.second.server_.reset ();
    sublinks.second.impl_.reset ();
  }

  links_.clear ();
  return true;
}
}   // namespace libs::ilink::impl::oneproc
