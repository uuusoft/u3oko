//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-impl-any-proc-int-functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes.hpp"
#include "link-impl-any-proc.hpp"

namespace libs { namespace ilink { namespace impl { namespace anyproc {
#if 0
  bool LinkImplAnyProc::close_int ()
  {
    return destroy_int( DestroyLinkType::soft );
  }
#endif
#if 0
  bool LinkImplAnyProc::create_int( const ::libs::link::CreateInfo& _info )
  {
    int_guard_type  _grd ( mtx_ );

    info_ = _info;

    UASSERT( !info_.id2val_[ ::libs::link::consts::text::id_name_queue2dest ].empty() );
    UASSERT( !info_.id2val_[ ::libs::link::consts::text::id_name_shared_mem ].empty() );

    if ( ::libs::link::details::ETypeSide::create_side == _info.create_side_ )
    {
      return make_for_create();

    }
    
    return make_for_creation();
  }
#endif

bool
LinkImplAnyProc::listen_int (const ::libs::link::CreateInfo& _info)
{
  UASSERT_SIGNAL ("failed");
  return false;
#if 0
    int_guard_type  _grd ( mtx_ );

    info_ = _info;

    UASSERT( !info_.id2val_[ ::libs::link::consts::text::id_name_queue2dest ].empty() );
    UASSERT( !info_.id2val_[ ::libs::link::consts::text::id_name_shared_mem ].empty() );

    if ( ::libs::link::details::ETypeSide::create_side == _info.create_side_ )
    {
      return make_for_create();

    }
    
    return make_for_creation();
#endif
}


bool
LinkImplAnyProc::connect_int (const ::libs::link::CreateInfo& _info)
{
  UASSERT_SIGNAL ("failed");
  return false;
#if 0
    int_guard_type  _grd ( mtx_ );

    info_ = _info;

    UASSERT( !info_.id2val_[ ::libs::link::consts::text::id_name_queue2dest ].empty() );
    UASSERT( !info_.id2val_[ ::libs::link::consts::text::id_name_shared_mem ].empty() );

    if ( ::libs::link::details::ETypeSide::create_side == _info.create_side_ )
    {
      return make_for_create();

    }
    
    return make_for_creation();
#endif
}


bool
LinkImplAnyProc::destroy_int (const DestroyLinkType& _type)
{
  UASSERT_SIGNAL ("failed");
  return false;
#if 0
    int_guard_type  _grd ( mtx_ );

    if( ::libs::link::details::ETypeSide::create_side != info_.create_side_ )
    {
      return true;
    }

    while( !loader_.unload( _force ) && _force )
    {}

    if( !info_.id2val_.empty() )
    {
      remove_names();
      info_.id2val_.clear();
    }

    return true;
#endif
}


bool
LinkImplAnyProc::is_connected_int () const
{
  UASSERT_SIGNAL ("failed");
  return false;
}


::libs::link::IEvent::ptr
LinkImplAnyProc::received_msg_int ()
{
  UASSERT_SIGNAL ("failed");
  return ::libs::link::IEvent::ptr ();
#if 0
    int_guard_type        _grd ( mtx_ );
    std::string           _serialized_string;
    std::stringstream     _iss;
    msgs_type::size_type  _recvd_size = 0;
    unsigned int          _priority = 0;

    if ( !cmd_recv_msgs_ )
    {
      UASSERT_SIGNAL( "failed" );
      return ::libs::link::IEvent::ptr();
    }

    _serialized_string.resize ( ::libs::link::consts::max_size_msg );

    const boost::posix_time::ptime        _now( boost::posix_time::second_clock::universal_time () );
    const boost::posix_time::milliseconds _wait_time( ::libs::link::consts::received_msg_max_wait_ms );
    const boost::posix_time::ptime        _timeout ( _now + _wait_time );

    if ( !cmd_recv_msgs_->timed_receive (
      &_serialized_string[0],
      ::libs::link::consts::max_size_msg,
      _recvd_size,
      _priority,
      _timeout ) )
    {
      return ::libs::link::IEvent::ptr();
    }

    if ( !_recvd_size )
    {
      UASSERT_SIGNAL( "failed" );
      return ::libs::link::IEvent::ptr();
    }

    ::libs::link::IEvent::ptr _ret;

    _iss << _serialized_string;
    type_iarchive _ia ( _iss);
    _ia >> _ret;

    return _ret;
#endif
}


IEvent::ptr
LinkImplAnyProc::send_msg_int (
  IEvent::ptr               _msg,
  const SyncCallType&       _sync,
  const RequestCallType&    _req,
  const ISeqEvent::id_type& _id)
{
  UASSERT_SIGNAL ("failed");
  return ::libs::link::IEvent::ptr ();
#if 0
    if ( !_msg )
    {
      UASSERT_SIGNAL( "failed" );
      return IEvent::ptr();
    }

    int_guard_type  _grd ( mtx_ );

    try
    {
      std::stringstream _iss;
      unsigned int      _priority = 0;
      type_oarchive     _ia ( _iss );

      _ia & _msg;

      std::string _ss ( _iss.str () );

      const boost::posix_time::ptime        _now( boost::posix_time::second_clock::universal_time () );
      const boost::posix_time::milliseconds _wait_time( ::libs::link::consts::send_msg_max_wait_ms );
      const boost::posix_time::ptime        _timeout ( _now + _wait_time );
      const bool                            _res = cmd_send_msgs_->timed_send ( _ss.c_str (), _ss.length (), _priority, _timeout );

      UASSERT ( _res );

      return _res ? IEvent::ptr() : IEvent::ptr();//temp
    }
    catch ( bip::interprocess_exception& _e )
    {
      E1XCEPT_LOGITS( boost::diagnostic_information( _e ) );
    }
    catch ( boost::exception& _e )
    {
      E1XCEPT_LOGITS( boost::diagnostic_information( _e ) );
    }
    catch ( std::exception& _e )
    {
      E1XCEPT_LOGITS( boost::diagnostic_information( _e ) );
    }

    return IEvent::ptr();
#endif
}


void
LinkImplAnyProc::complite_msg_int (
  IEvent::ptr              _msg,
  const StateProcessEvent& _state)
{
  UASSERT_SIGNAL ("failed");      //не реализовано.
  return;
}


::libs::link::mem::IMem::raw_ptr
LinkImplAnyProc::get_imem_int ()
{
  if (!heap_mem_)
    {
      heap_mem_.reset (new MemImplAnyProc);
    }

  return heap_mem_.get ();
}

}}}}      // namespace libs::ilink::impl::anyproc
