/**
\file       link-impl-any-proc-int-funcs.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "link-impl-any-proc.hpp"

namespace libs::ilink::impl::anyproc
{
#if 0
  bool LinkImplAnyProc::close_int ()
  {
    return destroy_int( ::libs::link::LinkDestroys::soft );
  }
#endif
#if 0
  bool LinkImplAnyProc::create_int( const ::libs::link::CreateInfo& info )
  {
    int_lock_type  lock ( mtx_ );

    info_ = info;

    U3_ASSERT( !info_.id_arg2val_[ ::libs::link::consts::text::id_name_queue2dest ].empty() );
    U3_ASSERT( !info_.id_arg2val_[ ::libs::link::consts::text::id_name_shared_mem ].empty() );

    if ( ::libs::link::details::ETypeSide::create_side == info.create_side_ )
    {
      return make_for_create();

    }
    
    return make_for_creation();
  }
#endif

bool
LinkImplAnyProc::listen_int (const ::libs::link::CreateInfo& info)
{
  U3_ASSERT_SIGNAL ("failed");
  return false;
#if 0
    int_lock_type  lock ( mtx_ );

    info_ = info;

    U3_ASSERT( !info_.id_arg2val_[ ::libs::link::consts::text::id_name_queue2dest ].empty() );
    U3_ASSERT( !info_.id_arg2val_[ ::libs::link::consts::text::id_name_shared_mem ].empty() );

    if ( ::libs::link::details::ETypeSide::create_side == info.create_side_ )
    {
      return make_for_create();

    }  
    return make_for_creation();
#endif
}


bool
LinkImplAnyProc::connect_int (const ::libs::link::CreateInfo& info)
{
  U3_ASSERT_SIGNAL ("failed");
  return false;
#if 0
    int_lock_type  lock ( mtx_ );

    info_ = info;

    U3_ASSERT( !info_.id_arg2val_[ ::libs::link::consts::text::id_name_queue2dest ].empty() );
    U3_ASSERT( !info_.id_arg2val_[ ::libs::link::consts::text::id_name_shared_mem ].empty() );

    if ( ::libs::link::details::ETypeSide::create_side == info.create_side_ )
    {
      return make_for_create();

    }    
    return make_for_creation();
#endif
}


bool
LinkImplAnyProc::destroy_int (const ::libs::link::LinkDestroys& type)
{
  U3_ASSERT_SIGNAL ("failed");
  return false;
#if 0
    int_lock_type  lock ( mtx_ );

    if( ::libs::link::details::ETypeSide::create_side != info_.create_side_ )
    {
      return true;
    }

    while( !loader_.unload( force ) && force )
    {}

    if( !info_.id_arg2val_.empty() )
    {
      remove_names();
      info_.id_arg2val_.clear();
    }
    return true;
#endif
}


bool
LinkImplAnyProc::is_connected_int () const
{
  U3_ASSERT_SIGNAL ("failed");
  return false;
}


::libs::events::IEvent::ptr
LinkImplAnyProc::received_msg_int ()
{
  U3_ASSERT_SIGNAL ("failed");
  return ::libs::events::IEvent::ptr ();
#if 0
    int_lock_type        lock ( mtx_ );
    std::string           serialized_string;
    std::stringstream     iss;
    msgs_type::size_type  recvd_size = 0;
    std::uint32_t          priority = 0;

    if ( !cmd_recv_msgs_ )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return ::libs::events::IEvent::ptr();
    }

    serialized_string.resize ( ::libs::link::consts::max_size_msg );

    const boost::posix_time::ptime        now( boost::posix_time::second_clock::universal_time () );
    const boost::posix_time::milliseconds wait_time( ::libs::link::consts::received_msg_max_wait_ms );
    const boost::posix_time::ptime        timeout ( now + wait_time );

    if ( !cmd_recv_msgs_->timed_receive (
      &serialized_string[0],
      ::libs::link::consts::max_size_msg,
      recvd_size,
      priority,
      timeout ) )
    {
      return ::libs::events::IEvent::ptr();
    }

    if ( !recvd_size )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return ::libs::events::IEvent::ptr();
    }

    ::libs::events::IEvent::ptr ret;

    iss << serialized_string;
    type_iarchive ia ( iss);
    ia >> ret;
    return ret;
#endif
}


::libs::events::IEvent::ptr
LinkImplAnyProc::send_msg_int (
  const ::libs::events::IEvent::ptr&        msg,
  const ::libs::link::details::CallSyncs&   sync,
  const ::libs::link::details::Calls&       req,
  const ::libs::events::ISeqEvent::id_type& id)
{
  U3_ASSERT_SIGNAL ("failed");
  return ::libs::events::IEvent::ptr ();
#if 0
    if ( !msg )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return IEvent::ptr();
    }

    int_lock_type  lock ( mtx_ );

    try
    {
      std::stringstream iss;
      std::uint32_t      priority = 0;
      type_oarchive     ia ( iss );

      ia & msg;

      std::string ss ( iss.str () );

      const boost::posix_time::ptime        now( boost::posix_time::second_clock::universal_time () );
      const boost::posix_time::milliseconds wait_time( ::libs::link::consts::send_msg_max_wait_ms );
      const boost::posix_time::ptime        timeout ( now + wait_time );
      const bool                            res = cmd_send_msgs_->timed_send ( ss.c_str (), ss.length (), priority, timeout );

      U3_ASSERT ( res );

      return res ? ::libs::events::IEvent::ptr() : ::libs::events::IEvent::ptr();//temp
    }
    catch (boost::interprocess::interprocess_exception& e )
    {
      E1XCEPT_LOGITS( boost::diagnostic_information( e ) );
    }
    catch ( boost::exception& e )
    {
      E1XCEPT_LOGITS( boost::diagnostic_information( e ) );
    }
    catch ( std::exception& e )
    {
      E1XCEPT_LOGITS( boost::diagnostic_information( e ) );
    }
    return ::libs::events::IEvent::ptr();
#endif
}


void
LinkImplAnyProc::complite_msg_int (
  const ::libs::events::IEvent::ptr&     msg,
  const ::libs::link::StateProcessEvent& state)
{
  U3_ASSERT_SIGNAL ("failed");   // не реализовано.
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
}   // namespace libs::ilink::impl::anyproc
