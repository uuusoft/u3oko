//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mem-impl-any-proc.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "../includes.hpp"
#include "mem-impl-any-proc.hpp"

namespace libs { namespace ilink { namespace impl { namespace anyproc {

MemImplAnyProc::MemImplAnyProc ()
{}


MemImplAnyProc::~MemImplAnyProc ()
{}


void*
MemImplAnyProc::mem_alloc (int _size, IBlockMem::ptr _hmem)
{
  return nullptr;
}


bool
MemImplAnyProc::mem_free (IBlockMem::ptr _hmem)
{
  return false;
}


bool
MemImplAnyProc::mem_atomic_call (IBlockMem::cptr _hmem, const IHandlerMem& _obj)
{
  return false;
}

#if 0
  void* LinkImplAnyProc::mem_get( const IBlockMem& _hmem )
  {
    std::lock_guard<std::mutex> _grd ( mtx_ );

    UASSERT(smem_ );
    UASSERT( _hmem.check() );

    void* _ret = smem_->get_address_from_handle( _hmem.hmem_ );

    return _ret;
  }
#endif
#if 0
  bool LinkImplAnyProc::fast_mem() const
  {
    return false;
  }
#endif
#if 0
  void* LinkImplAnyProc::mem_alloc ( int _size, IBlockMem& _hmem )
  {
    std::lock_guard<std::mutex> _process_grd ( mtx_ );

    UASSERT( _size>0);
    UASSERT(smem_ );

    _hmem.reset();

    void* _ret = smem_->allocate( _size, std::nothrow_t() );

    if( !_ret )
    {
      UASSERT_SIGNAL( "failed" );
      return _ret;
    }
    
    _hmem.hmem_ = smem_->get_handle_from_address( _ret );
    _hmem.size_ = _size;

    const std::string _process_id = to_str( ::libs::helpers::process::get_id() );
    const std::string _mem_id   = to_str( _hmem.hmem_ );
    const std::string _this_id  = to_str( UUU_MEM_CAST<long long>( this) );

    UASSERT( !_process_id.empty() );
    UASSERT( !_mem_id.empty() );
    UASSERT( !_this_id.empty() );

    _hmem.mtx_name_   = info_.get_prefix() + ".p_" + _process_id + ".t_" + _this_id + ".m_" + _mem_id + ".";
    _hmem.sync_name_  = _hmem.mtx_name_ + ".syncname";

    sync_type   _mtx( bip::create_only_t(), _hmem.mtx_name_.c_str() );
    guard_type  _grd( _mtx );

    UASSERT( _hmem.check() );
    UASSERT( !smem_->find< ::libs::link::details::TSyncMem >( _hmem.sync_name_.c_str() ).first );

    smem_->construct< ::libs::link::details::TSyncMem >( _hmem.sync_name_.c_str() )();

    UASSERT( smem_->find< ::libs::link::details::TSyncMem >( _hmem.sync_name_.c_str() ).first );

    return _ret;
  }
#endif
#if 0
  bool LinkImplAnyProc::mem_free ( IBlockMem& _hmem )
  {
    std::lock_guard<std::mutex> _grd ( mtx_ );

    UASSERT(smem_ );
    UASSERT( _hmem.check() );

    {
      sync_type   _mtx(bip::open_only_t(), _hmem.mtx_name_.c_str() );
      guard_type  _grd( _mtx );
      
      UASSERT( smem_->find< ::libs::link::details::TSyncMem >( _hmem.sync_name_.c_str() ).first );

      smem_->destroy< ::libs::link::details::TSyncMem >( _hmem.sync_name_.c_str() );

      UASSERT( !smem_->find< ::libs::link::details::TSyncMem >( _hmem.sync_name_.c_str() ).first );
      
      void* _ret = smem_->get_address_from_handle( _hmem.hmem_ );
      UASSERT( _ret );
      
      if( _ret )
      {
        smem_->deallocate( _ret );
      }
    }

    CHECK_CALL( 
      sync_type::remove( _hmem.mtx_name_.c_str() ), 
      "failed remove name mutex" );

    _hmem.reset();

    return true;
  }
#endif
#if 0
  bool LinkImplAnyProc::mem_atomic_call ( 
    const IBlockMem&    _hmem, 
    const IHandlerMem&  _obj )
  {
    bool _res = true;
    /*
    тут стоит обработка исключений, на тот случай, если мьютекс (и память которую он защищает) уже не существует.
    например, если в управляющем процессе произошло удаления источника данных (пользователь переключился на другой канал).
    */
    try
    {
      sync_type   _mtx ( bip::open_only_t (), _hmem.mtx_name_.c_str () );
      guard_type  _grd ( _mtx );

      if ( !smem_->find< ::libs::link::details::TSyncMem > ( _hmem.sync_name_.c_str () ).first )
      {
        XULOG_ERROR ("failed smem_->find<TSyncMem>=" << _hmem.sync_name_ );
        UASSERT_SIGNAL( "failed" );
        return false;
      }

      void* _pmem = mem_get ( _hmem );

      UASSERT ( _pmem);

      _res = _obj.update ( _pmem );

    }
    catch ( boost::exception& _e )
    {
      E1XCEPT_LOG( boost::diagnostic_information( _e ) );

      _res = false;
    }
    catch ( std::exception& _e )
    {
      E1XCEPT_LOG( boost::diagnostic_information( _e ) );

      _res = false;
    }

    return _res;
  }
#endif
}}}}      // namespace libs::ilink::impl::anyproc
