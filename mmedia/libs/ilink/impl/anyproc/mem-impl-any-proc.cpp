/**
\file       mem-impl-any-proc.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "mem-impl-any-proc.hpp"

namespace libs::ilink::impl::anyproc
{
MemImplAnyProc::MemImplAnyProc ()
{
}


MemImplAnyProc::~MemImplAnyProc ()
{
}


void*
MemImplAnyProc::mem_alloc (int size, ::libs::link::mem::IBlockFakeMem::ptr hmem)
{
  return nullptr;
}


bool
MemImplAnyProc::mem_free (::libs::link::mem::IBlockFakeMem::ptr hmem)
{
  return false;
}


bool
MemImplAnyProc::mem_atomic_call (
  ::libs::link::mem::IBlockFakeMem::cptr hmem,
  const ::libs::link::mem::IHandlerMem&  obj)
{
  return false;
}

#if 0
  void* LinkImplAnyProc::mem_get( const ::libs::helpers::mem::IBlockMem& hmem )
  {
    std::lock_guard<std::mutex> lock ( mtx_ );

    U3_ASSERT(smem_ );
    U3_ASSERT( hmem.check() );

    void* ret = smem_->get_address_from_handle( hmem.hmem_ );

    return ret;
  }
#endif
#if 0
  bool LinkImplAnyProc::fast_mem() const
  {
    return false;
  }
#endif
#if 0
  void* LinkImplAnyProc::mem_alloc ( int size, ::libs::helpers::mem::IBlockMem& hmem )
  {
    std::lock_guard<std::mutex> processlock ( mtx_ );

    U3_ASSERT( size>0);
    U3_ASSERT(smem_ );

    hmem.reset();

    void* ret = smem_->allocate( size, std::nothrow_t() );

    if( !ret )
    {
      U3_ASSERT_SIGNAL( "failed" );
      return ret;
    }
    
    hmem.hmem_ = smem_->get_handle_from_address( ret );
    hmem.size_ = size;

    const std::string process_id = to_str( ::libs::helpers::process::get_id() );
    const std::string mem_id   = to_str( hmem.hmem_ );
    const std::string this_id  = to_str( U3_CAST_REINTERPRET<long long>( this) );

    U3_ASSERT( !process_id.empty() );
    U3_ASSERT( !mem_id.empty() );
    U3_ASSERT( !this_id.empty() );

    hmem.mtx_name_   = info_.get_prefix() + ".p_" + process_id + ".t_" + this_id + ".m_" + mem_id + ".";
    hmem.sync_name_  = hmem.mtx_name_ + ".syncname";

    sync_type   mtx(boost::interprocess::create_only_t(), hmem.mtx_name_.c_str() );
    lock_type  lock( mtx );

    U3_ASSERT( hmem.check() );
    U3_ASSERT( !smem_->find< ::libs::link::details::TSyncMem >( hmem.sync_name_.c_str() ).first );

    smem_->construct< ::libs::link::details::TSyncMem >( hmem.sync_name_.c_str() )();

    U3_ASSERT( smem_->find< ::libs::link::details::TSyncMem >( hmem.sync_name_.c_str() ).first );

    return ret;
  }
#endif
#if 0
  bool LinkImplAnyProc::mem_free ( ::libs::helpers::mem::IBlockMem& hmem )
  {
    std::lock_guard<std::mutex> lock ( mtx_ );

    U3_ASSERT(smem_ );
    U3_ASSERT( hmem.check() );

    {
      sync_type   mtx(boost::interprocess::open_only_t(), hmem.mtx_name_.c_str() );
      lock_type  lock( mtx );
      
      U3_ASSERT( smem_->find< ::libs::link::details::TSyncMem >( hmem.sync_name_.c_str() ).first );

      smem_->destroy< ::libs::link::details::TSyncMem >( hmem.sync_name_.c_str() );

      U3_ASSERT( !smem_->find< ::libs::link::details::TSyncMem >( hmem.sync_name_.c_str() ).first );
      
      void* ret = smem_->get_address_from_handle( hmem.hmem_ );
      U3_ASSERT( ret );
      
      if( ret )
      {
        smem_->deallocate( ret );
      }
    }

    U3_CHECK( 
      sync_type::remove( hmem.mtx_name_.c_str() ), 
      "remove name mutex" );

    hmem.reset();

    return true;
  }
#endif
#if 0
  bool LinkImplAnyProc::mem_atomic_call ( 
    const ::libs::helpers::mem::IBlockMem&    hmem, 
    const ::libs::link::mem::IHandlerMem&  obj )
  {
    bool res = true;
    /*
    тут стоит обработка исключений, на тот случай, если мьютекс (и память которую он защищает) уже не существует.
    например, если в управляющем процессе произошло удаления источника данных (пользователь переключился на другой канал).
    */
    try
    {
      sync_type   mtx (boost::interprocess::open_only_t (), hmem.mtx_name_.c_str () );
      lock_type  lock ( mtx );

      if ( !smem_->find< ::libs::link::details::TSyncMem > ( hmem.sync_name_.c_str () ).first )
      {
        U3_XLOG_ERROR ("smem_->find<TSyncMem>=" << hmem.sync_name_ );
        U3_ASSERT_SIGNAL( "failed" );
        return false;
      }

      void* pmem = mem_get ( hmem );

      U3_ASSERT ( pmem);

      res = obj.update ( pmem );

    }
    catch ( boost::exception& e )
    {
      E1XCEPT_LOG( boost::diagnostic_information( e ) );
      res = false;
    }
    catch ( std::exception& e )
    {
      E1XCEPT_LOG( boost::diagnostic_information( e ) );
      res = false;
    }
    return res;
  }
#endif
}   // namespace libs::ilink::impl::anyproc
