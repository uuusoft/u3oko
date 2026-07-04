/**
\file       mem-impl-any-proc.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-impl-includes.hpp"
#include "mem-impl-any-proc.hpp"

namespace libs::ilink::impl::anyproc
{
auto
MemImplAnyProc::mem_alloc (int size, ::libs::link::mem::IBlockFakeMem::ptr hmem) -> void*
{
  return nullptr;
}


auto
MemImplAnyProc::mem_free (::libs::link::mem::IBlockFakeMem::ptr hmem) -> bool
{
  return false;
}


auto
MemImplAnyProc::mem_atomic_call (
  ::libs::link::mem::IBlockFakeMem::cptr hmem,
  const ::libs::link::mem::IHandlerMem&  obj) -> bool
{
  return false;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void*
LinkImplAnyProc::mem_get (const ::libs::utility::mem::IBlockMem& hmem)
{
  std::scoped_lock lock (mtx_);
  U3_ASSERT (smem_);
  U3_ASSERT (hmem.check ());
  void* ret = smem_->get_address_from_handle (hmem.hmem_);
  return ret;
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
LinkImplAnyProc::fast_mem () const
{
  return false;
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void*
LinkImplAnyProc::mem_alloc (int size, ::libs::utility::mem::IBlockMem& hmem)
{
  std::scoped_lock processlock (mtx_);

  U3_ASSERT (size > 0);
  U3_ASSERT (smem_);

  hmem.reset ();

  void* ret = smem_->allocate (size, std::nothrow_t ());

  if (!ret)
  {
    U3_ASSERT_SIGNAL ("failed");
    return ret;
  }

  hmem.hmem_ = smem_->get_handle_from_address (ret);
  hmem.size_ = size;

  const std::string process_id = to_str (::libs::utility::process::get_id ());
  const std::string mem_id     = to_str (hmem.hmem_);
  const std::string this_id    = to_str (::libs::utility::casts::reinterpret_cast_helper< long long > (this));

  U3_ASSERT (!process_id.empty ());
  U3_ASSERT (!mem_id.empty ());
  U3_ASSERT (!this_id.empty ());

  hmem.mtx_name_  = info_.get_prefix () + ".p_" + process_id + ".t_" + this_id + ".m_" + mem_id + ".";
  hmem.sync_name_ = hmem.mtx_name_ + ".syncname";

  sync_type mtx (boost::interprocess::create_only_t (), hmem.mtx_name_.c_str ());
  lock_type lock (mtx);

  U3_ASSERT (hmem.check ());
  U3_ASSERT (!smem_->find< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ()).first);

  smem_->construct< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ()) ();

  U3_ASSERT (smem_->find< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ()).first);

  return ret;
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
LinkImplAnyProc::mem_free (::libs::utility::mem::IBlockMem& hmem)
{
  std::scoped_lock lock (mtx_);

  U3_ASSERT (smem_);
  U3_ASSERT (hmem.check ());

  {
    sync_type mtx (boost::interprocess::open_only_t (), hmem.mtx_name_.c_str ());
    lock_type lock (mtx);

    U3_ASSERT (smem_->find< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ()).first);

    smem_->destroy< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ());

    U3_ASSERT (!smem_->find< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ()).first);

    void* ret = smem_->get_address_from_handle (hmem.hmem_);
    U3_ASSERT (ret);

    if (ret)
    {
      smem_->deallocate (ret);
    }
  }

  U3_CHECK (
    sync_type::remove (hmem.mtx_name_.c_str ()),
    "remove name mutex");

  hmem.reset ();

  return true;
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
bool
LinkImplAnyProc::mem_atomic_call (
  const ::libs::utility::mem::IBlockMem& hmem,
  const ::libs::link::mem::IHandlerMem&  obj)
{
  bool res = true;
  /*
  тут стоит обработка исключений, на тот случай, если мьютекс (и память которую он защищает) уже не существует.
  например, если в управляющем процессе произошло удаления источника данных (пользователь переключился на другой канал).
  */
  try
  {
    sync_type mtx (boost::interprocess::open_only_t (), hmem.mtx_name_.c_str ());
    lock_type lock (mtx);

    if (!smem_->find< ::libs::link::details::TSyncMem > (hmem.sync_name_.c_str ()).first)
    {
      U3_XLOG_ERROR ("smem_->find<TSyncMem>=" << hmem.sync_name_);
      U3_ASSERT_SIGNAL ("failed");
      return false;
    }

    void* pmem = mem_get (hmem);

    U3_ASSERT (pmem);

    res = obj.update (pmem);
  }
  catch (boost::exception& excpt)
  {
    E1XCEPT_LOG (boost::diagnostic_information (excpt));
    res = false;
  }
  catch (std::exception& excpt)
  {
    E1XCEPT_LOG (boost::diagnostic_information (excpt));
    res = false;
  }
  return res;
}
#endif
}   // namespace libs::ilink::impl::anyproc
