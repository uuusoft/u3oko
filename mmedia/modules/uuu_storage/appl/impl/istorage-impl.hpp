#pragma once
/**
\file       istorage-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       25.07.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl
{
class IStorageImpl
{
  public:
  //  ext types
  using id_chunk_type  = IdStorageChunk;                 //<
  using seance_type    = std::string;                    //<
  using ids_chunk_type = std::vector< id_chunk_type >;   //<
  using idlock_type    = std::string;                    //<

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IStorageImpl)

  virtual ~IStorageImpl ()
  {
  }

  void
  set_info (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info)
  {
    set_info_int (info);
  }

  void
  change_state (const ImplRuns& state)
  {
    if (!change_state_int (state))
    {
      U3_XLOG_ERROR ("change state storage impl " + to_string (state));
      return;
    }
    status_ = state;
  }

  void
  load (const seance_type& seance, const id_chunk_type& id, ::libs::helpers::mem::IBlockMem::raw_ptr mem)
  {
    check_state_for_ops ("load");
    U3_ASSERT (id.is_valid ());
    load_int (seance, id, mem);
  }

  id_chunk_type
  save (const seance_type& seance, ::libs::helpers::mem::IBlockMem::craw_ptr mem)
  {
    check_state_for_ops ("save");
    const auto res = save_int (seance, mem);
    U3_ASSERT (res.is_valid ());
    return res;
  }

  id_chunk_type
  save (const seance_type& seance, const std::uint8_t* mem, const std::size_t size_mem)
  {
    check_state_for_ops ("save");
    const auto res = save_int (seance, mem, size_mem);
    U3_ASSERT (res.is_valid ());
    return res;
  }

  id_chunk_type
  save (const seance_type& seance, ::utils::dbufs::IMemBuf::craw_ptr mem)
  {
    check_state_for_ops ("save");
    const auto res = save_int (seance, mem->getraw_buf ().get ());
    U3_ASSERT (res.is_valid ());
    return res;
  }
#if 0
  void
  get_all_ids (ids_chunk_type& ids)
  {    
    get_all_ids_int (ids);
  }
#endif
#if 0
  idlock_type
  lock_ids (const ids_chunk_type& ids)
  {    
    auto res = lock_ids_int (ids);
  }

  void
  unlock_ids (const idlock_type& lid)
  {    
    unlock_ids_int (lid);
  }

  void
  remove_ids (const idlock_type& lid)
  {    
    remove_ids (lid);
  }

  void
  get_info_ids (const idlock_type& lid)
  {    
    get_info_ids_int (lid);
  }
#endif

  protected:
  IStorageImpl () :
    status_ (ImplRuns::stop)
  {
  }

  void
  check_state_for_ops (const std::string& op) const
  {
    U3_CHECK (ImplRuns::run == status_, "invalid status for operation" + TOLOG (op));
  }

  private:
  //  IStorageImpl interface
  virtual void          set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info)                      = 0;
  virtual bool          change_state_int (const ImplRuns& state)                                                                    = 0;
  virtual void          load_int (const seance_type& seance, const id_chunk_type& id, ::libs::helpers::mem::IBlockMem::raw_ptr mem) = 0;
  virtual id_chunk_type save_int (const seance_type& seance, ::libs::helpers::mem::IBlockMem::craw_ptr mem)                         = 0;
  virtual id_chunk_type save_int (const seance_type& seance, const std::uint8_t* mem, const std::size_t size_mem)                   = 0;

  ImplRuns status_;   //<
};
}   // namespace modules::uuu_storage::appl::impl
