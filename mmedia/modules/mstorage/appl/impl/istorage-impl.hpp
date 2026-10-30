#pragma once
/**
\file       istorage-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       25.07.2018
*/

namespace modules::mstorage::appl::impl
{
class IStorageImpl
{
  public:
  //  ext types
  using id_chunk_type  = IdStorageChunk;                 //<
  using seance_type    = std::string;                    //<
  using ids_chunk_type = std::vector< id_chunk_type >;   //<
  using idlock_type    = std::string;                    //<

  U3_ADD_POINTERS_TO_SELF (IStorageImpl)

  virtual ~IStorageImpl () = default;

  void
  set_info (const syn::PathInfo::craw_ptr info)
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
  load (const seance_type& seance, const id_chunk_type& id, syn::IBlockMem::raw_ptr mem)
  {
    check_state_for_ops ("load");
    ::libs::utility::checks::throw_ifn (id.is_valid ());
    load_int (seance, id, mem);
  }

  id_chunk_type
  save (const seance_type& seance, syn::IBlockMem::craw_ptr mem)
  {
    check_state_for_ops ("save");
    const auto res = save_int (seance, mem);
    ::libs::utility::checks::throw_ifn (res.is_valid ());
    return res;
  }

  id_chunk_type
  save (const seance_type& seance, const std::uint8_t* mem, const std::size_t size_mem)
  {
    check_state_for_ops ("save");
    const auto res = save_int (seance, mem, size_mem);
    ::libs::utility::checks::throw_ifn (res.is_valid ());
    return res;
  }

  id_chunk_type
  save (const seance_type& seance, ::utils::dbufs::IMemBuf::craw_ptr mem)
  {
    check_state_for_ops ("save");
    const auto res = save_int (seance, mem->get_block ().get ());
    ::libs::utility::checks::throw_ifn (res.is_valid ());
    return res;
  }
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  void
  get_all_ids (ids_chunk_type& ids)
  {
    get_all_ids_int (ids);
  }
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
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
  IStorageImpl () = default;

  void
  check_state_for_ops (const std::string& op) const
  {
    ::libs::utility::checks::throw_ifn (ImplRuns::run == status_, "invalid status for operation" + TOLOG (op));
  }

  private:
  //  IStorageImpl interface
  virtual auto set_info_int (const syn::PathInfo::craw_ptr) -> void                                   = 0;
  virtual auto change_state_int (const ImplRuns&) -> bool                                             = 0;
  virtual auto load_int (const seance_type&, const id_chunk_type&, syn::IBlockMem::raw_ptr) -> void   = 0;
  virtual auto save_int (const seance_type&, syn::IBlockMem::craw_ptr) -> id_chunk_type               = 0;
  virtual auto save_int (const seance_type&, const std::uint8_t*, const std::size_t) -> id_chunk_type = 0;

  ImplRuns status_ { ImplRuns::stop };   //<
};
}   // namespace modules::mstorage::appl::impl
