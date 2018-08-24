//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-creator-impl-any-proc.cpp
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
#include "link-creator-impl-any-proc.hpp"

namespace libs { namespace ilink { namespace impl { namespace anyproc {

LinkCreatorImplAnyProc::LinkCreatorImplAnyProc ()
{}


LinkCreatorImplAnyProc::~LinkCreatorImplAnyProc ()
{
  //UASSERT_SIGNAL( "failed" );
  //CHECK_CALL_NO_THROW( destroy( true ) );
  return;
}

#if 0
  ::libs::link::ILink::ptr LinkCreatorImplAnyProc::get ( const ::libs::link::CreateInfo* _info )
  {
    ::libs::link::ILink::ptr _res;

    {
      guard_type  _grd ( mtx_ );

      helper2ptr_type&      _sublink  = links_[_info->active_side_];
      ::libs::link::ILink::ptr& _ret    = _sublink[_info->pt2pt_];

      if ( _ret )
      {
        //UASSERT_SIGNAL( "failed" );
        return _ret;
      }

      UASSERT ( _info );

      type_helper2info& _subinfo = infos_[_info->active_side_];

      for ( type_helper2info::value_type& _finfo : _subinfo )
      {
        if (*_info == _finfo.second)
        {
          UASSERT_SIGNAL( "failed" );
          return _ret;
        }
      }

      _subinfo[_info->pt2pt_] = *_info;

      _ret.reset ( new anyproc::LinkImplAnyProc );

      _res = _ret;
    }
      
    CHECK_CALL_NO_THROW ( _res->create (*_info ) );

    return _res;
  }
#endif

::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_connect (const ::libs::link::CreateInfo* _info)
{
  ::libs::link::ILink::ptr _res;

  UASSERT_SIGNAL ("failed");
#if 0
    {
      guard_type  _grd ( mtx_ );

      helper2ptr_type&      _sublink  = links_[_info->active_side_];
      ::libs::link::ILink::ptr& _ret    = _sublink[_info->pt2pt_];

      if ( _ret )
      {
        //UASSERT_SIGNAL( "failed" );
        return _ret;
      }

      UASSERT ( _info );

      type_helper2info& _subinfo = infos_[_info->active_side_];

      for ( type_helper2info::value_type& _finfo : _subinfo )
      {
        if (*_info == _finfo.second)
        {
          UASSERT_SIGNAL( "failed" );
          return _ret;
        }
      }

      _subinfo[_info->pt2pt_] = *_info;

      _ret.reset ( new anyproc::LinkImplAnyProc );

      _res = _ret;
    }
      
    CHECK_CALL_NO_THROW ( _res->create (*_info ) );
#endif
  return _res;
}


::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_listen (const ::libs::link::CreateInfo* _info)
{
  ::libs::link::ILink::ptr _res;

  UASSERT_SIGNAL ("failed");
#if 0
    {
      guard_type  _grd ( mtx_ );

      helper2ptr_type&      _sublink  = links_[_info->active_side_];
      ::libs::link::ILink::ptr& _ret    = _sublink[_info->pt2pt_];

      if ( _ret )
      {
        //UASSERT_SIGNAL( "failed" );
        return _ret;
      }

      UASSERT ( _info );

      type_helper2info& _subinfo = infos_[_info->active_side_];

      for ( type_helper2info::value_type& _finfo : _subinfo )
      {
        if (*_info == _finfo.second)
        {
          UASSERT_SIGNAL( "failed" );
          return _ret;
        }
      }

      _subinfo[_info->pt2pt_] = *_info;

      _ret.reset ( new anyproc::LinkImplAnyProc );

      _res = _ret;
    }
      
    CHECK_CALL_NO_THROW ( _res->create (*_info ) );
#endif
  return _res;
}

#if 0
  ::libs::link::ILink::ptr LinkCreatorImplAnyProc::get( const ETypeActivity&  _active, const TypeLinkModules& _type )
  {
    guard_type  _grd ( mtx_ );

    helper2ptr_type&      _sublink  = links_[_active];
    ::libs::link::ILink::ptr  _ret    = _sublink[_type];

    if ( !_ret )
    {
      UASSERT_SIGNAL( "failed" );
    }

    return _ret;
  }
#endif

::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_connect (const TypeLinkModules& _type)
{
  UASSERT_SIGNAL ("failed");
  return ::libs::link::ILink::ptr ();
#if 0
    guard_type  _grd ( mtx_ );

    helper2ptr_type&      _sublink  = links_[_active];
    ::libs::link::ILink::ptr  _ret    = _sublink[_type];

    if ( !_ret )
    {
      UASSERT_SIGNAL( "failed" );
    }

    return _ret;
#endif
}


::libs::link::ILink::ptr
LinkCreatorImplAnyProc::get_listen (const TypeLinkModules& _type)
{
  UASSERT_SIGNAL ("failed");
  return ::libs::link::ILink::ptr ();
#if 0
    guard_type  _grd ( mtx_ );

    helper2ptr_type&      _sublink  = links_[_active];
    ::libs::link::ILink::ptr  _ret    = _sublink[_type];

    if ( !_ret )
    {
      UASSERT_SIGNAL( "failed" );
    }

    return _ret;
#endif
}


bool
LinkCreatorImplAnyProc::close_all ()
{
  UASSERT_SIGNAL ("failed");
  return false;
#if 0
    guard_type  _grd ( mtx_ );

    for( type_info2ptr::value_type& _sublinks : links_ )
    {

      for ( helper2ptr_type::value_type& _info : _sublinks.second )
      {
        if ( _info.second)
        {
          _info.second->destroy ( true );
          _info.second.reset ();
        }
      }

    }

    links_.clear();

    infos_.clear();

    return true;
#endif
}

}}}}      // namespace libs::ilink::impl::anyproc
