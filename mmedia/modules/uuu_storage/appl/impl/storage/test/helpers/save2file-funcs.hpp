#pragma once
/**
\file       save2file-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       06.09.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::storage::test::helpers
{
inline std::string
get_seance_folder (const std::string& root_path, const TestStorageImpl::info_seance_type& info)
{
  U3_ASSERT (!root_path.empty ());
  auto ret = ::libs::helpers::files::make_path (root_path, info.state_.id_);
  ::libs::helpers::files::create_folder (ret);
  return ret;
}


template< typename ObjType >
bool
save_obj (const ObjType& obj, const std::string& path2file)
{
  U3_ASSERT (!path2file.empty ());
  std::ofstream file (path2file, std::ios::binary | std::ios::trunc);

  if (!file.is_open ())
  {
    U3_XLOG_ERROR ("open file for " + std::string (typeid (ObjType).name ()) + "save path=" + path2file);
    return false;
  }

  try
  {
    boost::archive::xml_oarchive xmla (file, boost::archive::no_header);

    xmla& BOOST_SERIALIZATION_NVP (obj);
  }
  catch (std::exception& e)
  {
    U3_LOG_STORAGE_EXCEPT (std::string (typeid (ObjType).name ()) + ", " + e.what () + TOLOG (path2file));
    return false;
  }
  file.flush ();
  return true;
}


inline void
store_seance (const std::string& root_path, const TestStorageImpl::info_seance_type& info)
{
  const auto full_dir_path = get_seance_folder (root_path, info);
  const auto full_path     = ::libs::helpers::files::make_path (full_dir_path, consts::name_seance_info_file);
  save_obj< StoredInfoSeance > (info.state_, full_path);
}


inline void
store_index_file (const std::string& root_path, const TestStorageImpl::info_seance_type& info)
{
  const auto full_dir_path = get_seance_folder (root_path, info);
  const auto full_path     = ::libs::helpers::files::make_path (full_dir_path, std::to_string (info.index_state_.indx_data_file_)) + "." + consts::name_ext_index_data_file;
  save_obj< IndexDataFileState > (info.index_state_, full_path);
}


inline void
store_data_file (const std::string& root_path, const TestStorageImpl::info_seance_type& info)
{
  const auto full_dir_path = get_seance_folder (root_path, info);
  // const auto full_path     = ::libs::helpers::files::make_path (full_dir_path, consts::name_index_data_file);
  // save_obj<IndexDataFileState> (info.index_state_, full_path);
  // U3_ASSERT_SIGNAL ("???");
}
}   // namespace modules::uuu_storage::appl::impl::storage::test::helpers
