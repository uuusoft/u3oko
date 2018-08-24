/**
\file       test-storage-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       10.08.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "test-storage-impl.hpp"

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace storage { namespace test {

TestStorageImpl::TestStorageImpl (const std::string& _path)
{}


TestStorageImpl::~TestStorageImpl ()
{}


void
TestStorageImpl::set_info_int (const PathInfo::craw_ptr _info)
{
  if (_info)
    {
      info_ = *_info;
    }
  update_path ();
  //state_saved_ = false;
  return;
}


bool
TestStorageImpl::change_state_int (const StateImplsType& _state)
{
  return true;
}


void
TestStorageImpl::load_int (const id_chunk_type& _id, IBlockMem::raw_ptr _mem)
{
  XULOG_ERROR ("unimplementated");
  UASSERT_SIGNAL (false);
  return;
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_int (const info_about_mem_type& _info, IBlockMem::craw_ptr _mem)
{
  CHECK_STATE (_mem->get_data_size (), "try save empty data");
  return save_impl (_info, _mem->get (), _mem->get_data_size ());
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_int (const info_about_mem_type& _info, const unsigned char* _mem, const std::size_t _size_mem)
{
  CHECK_STATE (_mem, "try save empty data");
  CHECK_STATE (_size_mem, "try save null data");
  return save_impl (_info, _mem, _size_mem);
}


void
TestStorageImpl::get_all_ids_int (ids_chunk_type& _ids)
{
  _ids.clear ();
  NodeEnumFiles _beg;

  ::libs::helpers::files::get_files (
    root_path_,
    _beg,
    ::libs::helpers::files::TypeIncludeSubFolders::enabled,
    ::libs::helpers::files::TypeIncludeFiles::disabled,
    ::libs::helpers::files::TypeRecursive::disabled);

  for (auto& _folder : _beg.folders_)
    {
      NodeEnumFiles _sub_beg;
      auto          _sub_root = ::libs::helpers::files::make_path (root_path_, _folder.name_);

      ::libs::helpers::files::get_files (
        _sub_root,
        _sub_beg,
        ::libs::helpers::files::TypeIncludeSubFolders::disabled,
        ::libs::helpers::files::TypeIncludeFiles::enabled,
        ::libs::helpers::files::TypeRecursive::disabled);

      for (auto& _file : _sub_beg.files_)
        {
          _ids.push_back (::libs::helpers::files::make_path (_folder.name_, _file));
        }
    }
  return;
}


void
TestStorageImpl::remove_ids_int (const id_locker_type& _lid)
{
  XULOG_ERROR ("unimplementated");
  UASSERT_SIGNAL (false);
  return;
}


void
TestStorageImpl::get_info_ids_int (const id_locker_type& _lid)
{
  XULOG_ERROR ("unimplementated");
  UASSERT_SIGNAL (false);
  return;
}


TestStorageImpl::id_locker_type
TestStorageImpl::lock_ids_int (const ids_chunk_type& _ids)
{
  XULOG_ERROR ("unimplementated");
  UASSERT_SIGNAL (false);
  return id_locker_type ("");
}


void
TestStorageImpl::unlock_ids_int (const id_locker_type& _lid)
{
  XULOG_ERROR ("unimplementated");
  UASSERT_SIGNAL (false);
  return;
}


TestStorageImpl::info_seance_type&
TestStorageImpl::get_seance_info (const info_about_mem_type& _info)
{
  auto _find = seances2infos_.find (_info);
  if (seances2infos_.end () == _find)
    {
      seances2infos_[_info] = 0;
      _find                 = seances2infos_.find (_info);
      prepare_write_seanse (_info);
    }
  return _find->second;
}


void
TestStorageImpl::prepare_write_seanse (const info_about_mem_type& _info)
{
  auto _full_path = ::libs::helpers::files::make_path (root_path_, _info);
  ::libs::helpers::files::create_folder (_full_path);
  return;
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_impl (const info_about_mem_type& _info, const unsigned char* _mem, const std::size_t _size_mem)
{
  auto& _sinfo = get_seance_info (_info);
  ++_sinfo;
  auto _ret = get_id_by_seance (_info, _sinfo);
  CHECK_CALL (save_data (_ret, _mem, _size_mem), "failed save data to file");
  return _ret;
}


TestStorageImpl::id_chunk_type
TestStorageImpl::get_id_by_seance (const info_about_mem_type& _info, const info_seance_type& _sinfo)
{
  id_chunk_type _ret = _info + "/" + ::to_str (_sinfo);
  XULOG_TEST ("TestStorageImpl::get_id_by_seance ret=" << _ret);
  return _ret;
}


bool
TestStorageImpl::save_data (const id_chunk_type& _id, const unsigned char* _mem, const std::size_t _size_mem)
{
  const auto    _full_path = ::libs::helpers::files::make_path (root_path_, _id);
  std::ofstream _file (_full_path, std::ios::trunc | std::ios::binary);
  _file.write (UUU_MEM_CAST<const char*> (_mem), _size_mem);
  if (_file.bad ())
    {
      XULOG_ERROR ("failed write to file, " << _full_path << ", " << strerror (errno))
    }
  return true;
}


void
TestStorageImpl::update_path ()
{
  XULOG_TRACE ("TestStorageImpl::update_path, beg, root_path_=" << root_path_);
  if (!root_path_.empty ())
    {
      XULOG_TRACE ("TestStorageImpl::update_path, ready, skip");
      return;
    }

  auto _iappl = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();
  root_path_  = info_.path2data_;

  if (root_path_.empty ())
    {
      // »наче генерируем значение по умолчанию, использу€ идентификатор и путь по умолчанию.
      auto _path = _iappl->get_path (::libs::iproperties::appl_paths::TypePath::default_storage);
      root_path_ = ::libs::helpers::files::make_path (_path, std::string ("test-storage"));
    }
  ::libs::helpers::files::create_folder (root_path_);
  XULOG_TRACE ("TestStorageImpl::update_path, end, root_path_=" << root_path_);
  return;
}

}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test
