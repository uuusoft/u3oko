//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-creator-impl-one-proc.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes.hpp"
#include "link-creator-impl-one-proc.hpp"

namespace libs { namespace ilink { namespace impl { namespace oneproc {

LinkCreatorImplOneProc::LinkCreatorImplOneProc ()
{}


LinkCreatorImplOneProc::~LinkCreatorImplOneProc ()
{}


ILink::ptr
LinkCreatorImplOneProc::get_connect (const CreateInfo* _info)
{
  ILink::ptr _ret;

  {
    guard_type       _grd (mtx_);
    InfoOneLink&     _sublink = links_[_info->pt2pt_];
    ILink::weak_ptr& _wret    = _sublink.client_;

    _ret = _wret.lock ();
    if (_ret)
      {
        //UASSERT_SIGNAL( "failed" );
        return _ret;
      }

    UASSERT (_info);
    if (!_sublink.impl_)
      {
        _sublink.impl_ = std::make_shared<LinkImplOneProcInt> ();
      }

    oneproc::LinkImplOneProcInt::weak_ptr _tempp = oneproc::LinkImplOneProcInt::weak_ptr (_sublink.impl_);
    _ret                                         = std::make_shared<oneproc::LinkImplOneProc> (_tempp);
    _wret                                        = _ret;
  }

  CHECK_CALL_NO_THROW (_ret->connect (*_info));
  return _ret;
}


ILink::ptr
LinkCreatorImplOneProc::get_listen (const CreateInfo* _info)
{
  ILink::ptr _ret;

  {
    guard_type       _grd (mtx_);
    InfoOneLink&     _sublink = links_[_info->pt2pt_];
    ILink::weak_ptr& _wret    = _sublink.server_;

    _ret = _wret.lock ();
    if (_ret)
      {
        //UASSERT_SIGNAL( "failed" );
        return _ret;
      }

    UASSERT (_info);
    if (!_sublink.impl_)
      {
        _sublink.impl_ = std::make_shared<LinkImplOneProcInt> ();
      }

    oneproc::LinkImplOneProcInt::weak_ptr _tempp = oneproc::LinkImplOneProcInt::weak_ptr (_sublink.impl_);
    _ret                                         = std::make_shared<oneproc::LinkImplOneProc> (_tempp);
    _wret                                        = _ret;
  }

  CHECK_CALL_NO_THROW (_ret->listen (*_info));
  return _ret;
}


ILink::ptr
LinkCreatorImplOneProc::get_connect (const TypeLinkModules& _type)
{
  guard_type      _grd (mtx_);
  InfoOneLink&    _sublink = links_[_type];
  ILink::weak_ptr _wret    = _sublink.client_;
  ILink::ptr      _ret     = _wret.lock ();
  UASSERT (_ret);
  return _ret;
}


ILink::ptr
LinkCreatorImplOneProc::get_listen (const TypeLinkModules& _type)
{
  guard_type      _grd (mtx_);
  InfoOneLink&    _sublink = links_[_type];
  ILink::weak_ptr _wret    = _sublink.server_;
  ILink::ptr      _ret     = _wret.lock ();
  UASSERT (_ret);
  return _ret;
}


bool
LinkCreatorImplOneProc::close_all ()
{
  guard_type _grd (mtx_);

  for (helper2ptr_type::value_type& _sublinks : links_)
    {
      _sublinks.second.client_.reset ();
      _sublinks.second.server_.reset ();
      _sublinks.second.impl_.reset ();
    }

  links_.clear ();
  return true;
}

}}}}      // namespace libs::ilink::impl::oneproc
