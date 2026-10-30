/**
\file       test-storage-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.08.2018
*/
#include "../../../../module-storage-includes_int.hpp"
#include "test-storage-impl.hpp"

namespace modules::mstorage::appl::impl::storage::test
{
TestStorageImpl::TestStorageImpl (const std::string& path)
{
}

void
TestStorageImpl::set_info_int (const syn::PathInfo::craw_ptr info)
{
  if (info)
  {
    info_ = *info;
  }
  update_path ();
  // state_saved_ = false;
}


auto
TestStorageImpl::change_state_int (const ImplRuns& state) -> bool
{
  switch (state)
  {
  case ImplRuns::run:
    break;
  case ImplRuns::stop: {
    flush_seances ();
    break;
  }
  default:
    U3_LOG_DATA_ERROR ("unknown type ImplRuns " + to_string (state));
    return false;
  }
  return true;
}


void
TestStorageImpl::load_int (const seance_type& info, const id_chunk_type& id, syn::IBlockMem::raw_ptr mem)
{
  U3_LOG_DATA_ERROR ("unimplementated");
}


auto
TestStorageImpl::save_int (const seance_type& info, syn::IBlockMem::craw_ptr mem) -> TestStorageImpl::id_chunk_type
{
  ::libs::utility::checks::throw_ifn (mem->get_size (), "try save empty data");
  return save_impl (info, mem->get (), mem->get_size ());
}


auto
TestStorageImpl::save_int (
  const seance_type&  info,
  const std::uint8_t* mem,
  const std::size_t   size_mem) -> TestStorageImpl::id_chunk_type
{
  ::libs::utility::checks::throw_ifn (mem, "try save empty data");
  ::libs::utility::checks::throw_ifn (size_mem, "try save null data");
  return save_impl (info, mem, size_mem);
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
TestStorageImpl::get_all_ids_int (ids_chunk_type& ids)
{
  ids.clear ();
  ::libs::utility::files::NodeEnumFiles beg;

  ::libs::utility::files::get_files (
    root_path_,
    beg,
    { ::libs::utility::files::IncludeSubFolders::enabled, ::libs::utility::files::IncludeFiles::disabled, ::libs::utility::files::Recursives::disabled });

  for (auto& folder : beg.folders_)
  {
    ::libs::utility::files::NodeEnumFiles sub_beg;
    auto                                  sub_root = ::libs::utility::files::make_path (root_path_, folder.name_);

    ::libs::utility::files::get_files (
      sub_root,
      sub_beg,
      { ::libs::utility::files::IncludeSubFolders::disabled, ::libs::utility::files::IncludeFiles::enabled, ::libs::utility::files::Recursives::disabled });

    for (auto& file : sub_beg.files_)
    {
      ids.push_back (::libs::utility::files::make_path (folder.name_, file));
    }
  }
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
TestStorageImpl::remove_ids_int (const idlock_type& lid)
{
  U3_XLOG_ERROR ("unimplementated");
  ::libs::utility::checks::throw_exception (false);
}


void
TestStorageImpl::get_info_ids_int (const idlock_type& lid)
{
  U3_XLOG_ERROR ("unimplementated");
  ::libs::utility::checks::throw_exception (false);
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
TestStorageImpl::idlock_type
TestStorageImpl::lock_ids_int (const ids_chunk_type& ids)
{
  U3_XLOG_ERROR ("unimplementated");
  ::libs::utility::checks::throw_exception (false);
  return idlock_type ("");
}


void
TestStorageImpl::unlock_ids_int (const idlock_type& lid)
{
  U3_XLOG_ERROR ("unimplementated");
  ::libs::utility::checks::throw_exception (false);
}
#endif
}   // namespace modules::mstorage::appl::impl::storage::test
