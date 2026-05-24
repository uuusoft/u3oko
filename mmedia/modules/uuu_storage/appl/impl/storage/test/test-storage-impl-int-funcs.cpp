/**
\file       test-storage-impl-int-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       07.09.2018
\project    u3_module_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../module-storage-includes_int.hpp"
#include "test-storage-impl.hpp"

namespace modules::uuu_storage::appl::impl::storage::test
{
TestStorageImpl::info_seance_type&
TestStorageImpl::get_seance_info (const seance_type& info)
{
  auto find = seances2infos_.find (info);
  if (seances2infos_.end () == find)
  {
    auto& ret = seances2infos_[info];
    ret.reset ();
    ret.state_.id_ = info;
    prepare_write_seance (info);
    return ret;
  }
  return find->second;
}


void
TestStorageImpl::prepare_write_seance (const seance_type& info)
{
  auto full_path = ::libs::helpers::files::make_path (root_path_, info);
  U3_LOG_DATA_MARK ("prepare folder for write seance" + TOLOG (full_path));
  ::libs::helpers::files::create_folder (full_path);
  U3_ASSERT (seances2infos_.end () != seances2infos_.find (info));
  U3_ASSERT_SIGNAL ("TestStorageImpl::prepare_write_seance: unimplementated");
  // auto uinfo = seances2infos_[info];
  // helpers::store_seance (root_path_, uinfo);
  // uinfo.state_.count_fragments_ = 0;
  // uinfo.state_.indx_data_file_
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_impl (const seance_type& info, const std::uint8_t* mem, const std::size_t size_mem)
{
  auto& sinfo = get_seance_info (info);
  get_next_write_id_by_seance (info, sinfo);
  U3_CHECK (save_data (info, sinfo, mem, size_mem), "save data to file");
  return sinfo.cursor_;
}


void
TestStorageImpl::get_next_write_id_by_seance (const seance_type& info, info_seance_type& sinfo)
{
  if ((sinfo.index_state_.count_fragments_ >= consts::max_count_fragments_session_data_file) ||
      (sinfo.size_data_file_ >= consts::max_size_session_data_file))
  {
    helpers::store_index_file (root_path_, sinfo);
    sinfo.index_state_.reset ();
    sinfo.size_data_file_ = 0;
  }

  if (!sinfo.index_state_.is_valid ())
  {
    ++sinfo.state_.count_data_files_;
    sinfo.index_state_.count_fragments_ = 0;
    sinfo.index_state_.indx_data_file_  = sinfo.state_.count_data_files_ - 1;

    const auto dir_path  = ::libs::helpers::files::make_path (root_path_, sinfo.state_.id_);
    const auto file_name = std::to_string (sinfo.index_state_.indx_data_file_) + "." + consts::name_ext_data_file;
    const auto file_path = ::libs::helpers::files::make_path (dir_path, file_name);
    auto&      dfile     = sinfo.data_file_;

    if (dfile.is_open ())
    {
      dfile.close ();
      dfile.clear ();
    }

    dfile.open (file_path, std::ios::trunc | std::ios::binary | std::ios::out);
    U3_CHECK (dfile.is_open (), "open data file" + TOLOG (file_path));
    U3_CHECK (!dfile.bad (), "error state data file");
  }

  U3_ASSERT (sinfo.index_state_.is_valid ());
  sinfo.cursor_.reset ();
  sinfo.cursor_.id_file_     = sinfo.index_state_.indx_data_file_;
  sinfo.cursor_.id_fragment_ = sinfo.index_state_.count_fragments_;

  U3_ASSERT (sinfo.cursor_.is_valid ());
  U3_ASSERT (sinfo.data_file_.is_open ());
}


bool
TestStorageImpl::save_data (
  const seance_type&  info,
  info_seance_type&   sinfo,
  const std::uint8_t* mem,
  const std::size_t   size_mem)
{
  auto& file = sinfo.data_file_;
  U3_ASSERT (file.is_open ());
  U3_ASSERT (sinfo.index_state_.is_valid ());

  ++sinfo.index_state_.count_fragments_;
  sinfo.index_state_.off_fragments_.push_back ({ sinfo.size_data_file_, size_mem });   //
  file.write (U3_CAST_REINTERPRET< const char* > (mem), size_mem);                     //

  if (file.bad ())
  {
    U3_LOG_DATA_ERROR ("write to data file" + VTOLOG (errno) + TOLOG (strerror (errno)));
    --sinfo.index_state_.count_fragments_;
    sinfo.index_state_.off_fragments_.pop_back ();
    U3_ASSERT (sinfo.index_state_.is_valid ());
    return false;
  }

  sinfo.size_data_file_ += size_mem;
  U3_ASSERT (sinfo.index_state_.is_valid ());
  return true;
}


void
TestStorageImpl::update_path ()
{
  if (!root_path_.empty ())
  {
    return;
  }

  auto iappl = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_paths_lockfree ();
  auto path  = iappl->get_path (::libs::iproperties::appl_paths::Paths::active_storage_module);

  root_path_ = ::libs::helpers::files::make_path (path, std::string ("test-storage"));
  root_path_ = ::libs::helpers::files::make_path (root_path_, info_.path2data_);

  ::libs::helpers::files::create_folder (root_path_);
}


void
TestStorageImpl::flush_seances ()
{
  for (const auto& seance : seances2infos_)
  {
    helpers::store_seance (root_path_, seance.second);
    helpers::store_index_file (root_path_, seance.second);
  }

  seances2infos_.clear ();
}
}   // namespace modules::uuu_storage::appl::impl::storage::test
