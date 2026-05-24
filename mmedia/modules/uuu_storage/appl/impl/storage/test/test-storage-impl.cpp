/**
\file       test-storage-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.08.2018
\project    u3_module_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "test-storage-impl.hpp"

namespace modules::uuu_storage::appl::impl::storage::test
{
TestStorageImpl::TestStorageImpl (const std::string& path)
{
}

TestStorageImpl::~TestStorageImpl ()
{
}


void
TestStorageImpl::set_info_int (const ::libs::ievents::props::modules::storage::PathInfo::craw_ptr info)
{
  if (info)
  {
    info_ = *info;
  }
  update_path ();
  // state_saved_ = false;
}


bool
TestStorageImpl::change_state_int (const ImplRuns& state)
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
TestStorageImpl::load_int (
  const seance_type&                       info,
  const id_chunk_type&                     id,
  ::libs::helpers::mem::IBlockMem::raw_ptr mem)
{
  U3_LOG_DATA_ERROR ("unimplementated");
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_int (const seance_type& info, ::libs::helpers::mem::IBlockMem::craw_ptr mem)
{
  U3_CHECK (mem->get_data_size (), "try save empty data");
  return save_impl (info, mem->get (), mem->get_data_size ());
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_int (
  const seance_type&  info,
  const std::uint8_t* mem,
  const std::size_t   size_mem)
{
  U3_CHECK (mem, "try save empty data");
  U3_CHECK (size_mem, "try save null data");
  return save_impl (info, mem, size_mem);
}

#if 0
void
TestStorageImpl::get_all_ids_int (ids_chunk_type& ids)
{
  ids.clear ();
  ::libs::helpers::files::NodeEnumFiles beg;

  ::libs::helpers::files::get_files (
    root_path_,
    beg,
    { ::libs::helpers::files::IncludeSubFolders::enabled, ::libs::helpers::files::IncludeFiles::disabled, ::libs::helpers::files::Recursives::disabled });

  for (auto& folder : beg.folders_)
  {
    ::libs::helpers::files::NodeEnumFiles sub_beg;
    auto                                  sub_root = ::libs::helpers::files::make_path (root_path_, folder.name_);

    ::libs::helpers::files::get_files (
      sub_root,
      sub_beg,
      { ::libs::helpers::files::IncludeSubFolders::disabled, ::libs::helpers::files::IncludeFiles::enabled, ::libs::helpers::files::Recursives::disabled });

    for (auto& file : sub_beg.files_)
    {
      ids.push_back (::libs::helpers::files::make_path (folder.name_, file));
    }
  }
}
#endif
#if 0
void
TestStorageImpl::remove_ids_int (const idlock_type& lid)
{
  U3_XLOG_ERROR ("unimplementated");
  U3_ASSERT_SIGNAL (false);
}


void
TestStorageImpl::get_info_ids_int (const idlock_type& lid)
{
  U3_XLOG_ERROR ("unimplementated");
  U3_ASSERT_SIGNAL (false);
}
#endif
#if 0
TestStorageImpl::idlock_type
TestStorageImpl::lock_ids_int (const ids_chunk_type& ids)
{
  U3_XLOG_ERROR ("unimplementated");
  U3_ASSERT_SIGNAL (false);
  return idlock_type ("");
}


void
TestStorageImpl::unlock_ids_int (const idlock_type& lid)
{
  U3_XLOG_ERROR ("unimplementated");
  U3_ASSERT_SIGNAL (false);
}
#endif
}   // namespace modules::uuu_storage::appl::impl::storage::test
