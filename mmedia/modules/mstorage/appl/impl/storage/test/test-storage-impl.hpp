#pragma once
/**
\file       test-storage-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       10.08.2018
*/

namespace modules::mstorage::appl::impl::storage::test
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
  virtual ~TestStorageImpl () = default;

  private:
  // internal types
  using id_chunk2info = boost::unordered_flat_map< seance_type, info_seance_type, ::libs::utility::utils::TransparentStringHash, std::equal_to<> >;
  using idlocks_type  = boost::unordered_flat_set< idlock_type >;

  //  IStorageImpl overrides
  virtual auto set_info_int (const syn::PathInfo::craw_ptr) -> void override;
  virtual auto change_state_int (const ImplRuns&) -> bool override;
  virtual auto load_int (const seance_type&, const id_chunk_type&, syn::IBlockMem::raw_ptr) -> void override;
  virtual auto save_int (const seance_type&, syn::IBlockMem::craw_ptr) -> id_chunk_type override;
  virtual auto save_int (const seance_type&, const std::uint8_t*, const std::size_t) -> id_chunk_type override;

  info_seance_type& get_seance_info (const seance_type& info);

  auto get_next_write_id_by_seance (const seance_type&, info_seance_type&) -> void;
  auto prepare_write_seance (const seance_type& info) -> void;
  auto save_impl (const seance_type& info, const std::uint8_t*, const std::size_t) -> id_chunk_type;
  auto save_data (const seance_type& info, info_seance_type&, const std::uint8_t*, const std::size_t) -> bool;
  auto flush_seances () -> void;
  auto update_path () -> void;

  id_chunk2info seances2infos_;   //<
  syn::PathInfo info_;            //<
  std::string   root_path_;       //<
  idlocks_type  lockers_;         //<
};
}   // namespace modules::mstorage::appl::impl::storage::test
