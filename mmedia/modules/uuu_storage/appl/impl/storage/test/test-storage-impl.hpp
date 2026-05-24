#pragma once
/**
\file       test-storage-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::storage::test
{
class TestStorageImpl : public IStorageImpl
{
  public:
  //  ext types
  using IStorageImpl::id_chunk_type;
  using IStorageImpl::seance_type;
  using IStorageImpl::ids_chunk_type;
  using IStorageImpl::idlock_type;
  using info_seance_type = RuntimeInfoSeance;

  explicit TestStorageImpl (const std::string& path);
  virtual ~TestStorageImpl ();

  private:
  // internal types
  using id_chunk2info = std::unordered_map< seance_type, info_seance_type >;
  using idlocks_type  = std::unordered_set< idlock_type >;

  //  IStorageImpl overrides
  virtual void          set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info) override;
  virtual bool          change_state_int (const ImplRuns& state) override;
  virtual void          load_int (const seance_type& info, const id_chunk_type& id, ::libs::helpers::mem::IBlockMem::raw_ptr mem) override;
  virtual id_chunk_type save_int (const seance_type& info, ::libs::helpers::mem::IBlockMem::craw_ptr mem) override;
  virtual id_chunk_type save_int (const seance_type& info, const std::uint8_t* mem, const std::size_t size_mem) override;
  // virtual void           get_all_ids_int (ids_chunk_type& ids) override;
  // virtual void           remove_ids_int (const idlock_type& lid) override;
  // virtual void           get_info_ids_int (const idlock_type& lid) override;
  // virtual idlock_type lock_ids_int (const ids_chunk_type& ids) override;
  // virtual void           unlock_ids_int (const idlock_type& lid) override;

  info_seance_type& get_seance_info (const seance_type& info);

  // id_chunk_type get_next_write_id_by_seance (const seance_type& info, info_seance_type& sinfo);
  void          get_next_write_id_by_seance (const seance_type& info, info_seance_type& sinfo);
  void          prepare_write_seance (const seance_type& info);
  id_chunk_type save_impl (const seance_type& info, const std::uint8_t* mem, const std::size_t size_mem);
  // bool save_data (const id_chunk_type& id, const std::uint8_t* mem, const std::size_t size_mem);
  bool save_data (const seance_type& info, info_seance_type& sinfo, const std::uint8_t* mem, const std::size_t size_mem);
  void flush_seances ();
  void update_path ();

  id_chunk2info                                      seances2infos_;   //<
  ::libs::ievents::props::modules::storage::PathInfo info_;            //<
  std::string                                        root_path_;       //<
  idlocks_type                                       lockers_;         //<
};
}   // namespace modules::uuu_storage::appl::impl::storage::test
