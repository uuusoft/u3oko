/**
\file       link-creator-impl-any-proc.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-creator-impl-any-proc.hpp"

namespace libs::ilink::impl::anyproc
{
LinkCreatorImplAnyProc::LinkCreatorImplAnyProc ()
{
}


LinkCreatorImplAnyProc::~LinkCreatorImplAnyProc ()
{
}

#if 0
::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get (const ::libs::link::CreateInfo* info)
{
  ::libs::link::ILink::ptr res;

  {
    lock_type lock (mtx_);

    helper2ptr_type&          sublink = links_[info->active_side_];
    ::libs::link::ILink::ptr& ret     = sublink[info->pt2pt_];

    if (ret)
    {
      return ret;
    }

    U3_ASSERT (info);
    type_helper2info& subinfo = infos_[info->active_side_];
    for (type_helper2info::value_type& finfo : subinfo)
    {
      if (*info == finfo.second)
      {
        U3_ASSERT_SIGNAL ("failed");
        return ret;
      }
    }

    subinfo[info->pt2pt_] = *info;
    ret.reset (new anyproc::LinkImplAnyProc);
    res = ret;
  }
  U3_CHECK_NT (res->create (*info));
  return res;
}
#endif

::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_connect (const ::libs::link::CreateInfo& info)
{
  ::libs::link::ILink::ptr res;
  U3_ASSERT_SIGNAL ("failed");
#if 0
  {
    lock_type lock (mtx_);

    helper2ptr_type&          sublink = links_[info->active_side_];
    ::libs::link::ILink::ptr& ret     = sublink[info->pt2pt_];

    if (ret)
    {
      // U3_ASSERTSIG( "failed" );
      return ret;
    }

    U3_ASSERT (info);
    type_helper2info& subinfo = infos_[info->active_side_];
    for (type_helper2info::value_type& finfo : subinfo)
    {
      if (*info == finfo.second)
      {
        U3_ASSERT_SIGNAL ("failed");
        return ret;
      }
    }

    subinfo[info->pt2pt_] = *info;
    ret.reset (new anyproc::LinkImplAnyProc);
    res = ret;
  }
  U3_CHECK_NT (res->create (*info));
#endif
  return res;
}


::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_listen (const ::libs::link::CreateInfo& info)
{
  ::libs::link::ILink::ptr res;
  U3_ASSERT_SIGNAL ("failed");
#if 0
  {
    lock_type lock (mtx_);

    helper2ptr_type&          sublink = links_[info->active_side_];
    ::libs::link::ILink::ptr& ret     = sublink[info->pt2pt_];

    if (ret)
    {
      // U3_ASSERTSIG( "failed" );
      return ret;
    }

    U3_ASSERT (info);
    type_helper2info& subinfo = infos_[info->active_side_];
    for (type_helper2info::value_type& finfo : subinfo)
    {
      if (*info == finfo.second)
      {
        U3_ASSERT_SIGNAL ("failed");
        return ret;
      }
    }

    subinfo[info->pt2pt_] = *info;
    ret.reset (new anyproc::LinkImplAnyProc);
    res = ret;
  }

  U3_CHECK_NT (res->create (*info));
#endif
  return res;
}

#if 0
::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get (const ETypeActivity& active, const ::libs::link::details::ModuleLinks& type)
{
  lock_type lock (mtx_);

  helper2ptr_type&         sublink = links_[active];
  ::libs::link::ILink::ptr ret     = sublink[type];

  if (!ret)
  {
    U3_ASSERT_SIGNAL ("failed");
  }

  return ret;
}
#endif

::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_connect (const ::libs::link::details::ModuleLinks& type)
{
  U3_ASSERT_SIGNAL ("failed");
  return ::libs::link::ILink::ptr ();
#if 0
  lock_type lock (mtx_);

  helper2ptr_type&         sublink = links_[active];
  ::libs::link::ILink::ptr ret     = sublink[type];

  if (!ret)
  {
    U3_ASSERT_SIGNAL ("failed");
  }
  return ret;
#endif
}


::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_listen (const ::libs::link::details::ModuleLinks& type)
{
  U3_ASSERT_SIGNAL ("failed");
  return ::libs::link::ILink::ptr ();
#if 0
  lock_type lock (mtx_);

  helper2ptr_type&         sublink = links_[active];
  ::libs::link::ILink::ptr ret     = sublink[type];

  if (!ret)
  {
    U3_ASSERT_SIGNAL ("failed");
  }

  return ret;
#endif
}


bool
LinkCreatorImplAnyProc::close_all ()
{
  U3_ASSERT_SIGNAL ("failed");
  return false;
#if 0
  lock_type lock (mtx_);

  for (type_info2ptr::value_type& sublinks : links_)
  {
    for (helper2ptr_type::value_type& info : sublinks.second)
    {
      if (info.second)
      {
        info.second->destroy (true);
        info.second.reset ();
      }
    }
  }

  links_.clear ();
  infos_.clear ();
  return true;
#endif
}

}   // namespace libs::ilink::impl::anyproc
