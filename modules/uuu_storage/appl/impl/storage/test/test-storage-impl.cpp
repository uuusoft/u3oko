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
  XULOG_TRACE ("TestStorageImpl::change_state_int, beg, " << to_str (_state));
  switch (_state)
    {
    case StateImplsType::run:
      {
        break;
      }
    case StateImplsType::stop:
      {
        flush_seances ();
        break;
      }
    default:
      XULOG_ERROR ("unknown type StateImplsType, " << to_str (_state));
      return false;
    }
  XULOG_TRACE ("TestStorageImpl::change_state_int, end");
  return true;
}


void
TestStorageImpl::load_int (const seance_type& _info, const id_chunk_type& _id, IBlockMem::raw_ptr _mem)
{
  XULOG_ERROR ("unimplementated");
  UASSERT_SIGNAL (false);
  return;
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_int (const seance_type& _info, IBlockMem::craw_ptr _mem)
{
  CHECK_STATE (_mem->get_data_size (), "try save empty data");
  return save_impl (_info, _mem->get (), _mem->get_data_size ());
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_int (const seance_type& _info, const unsigned char* _mem, const std::size_t _size_mem)
{
  CHECK_STATE (_mem, "try save empty data");
  CHECK_STATE (_size_mem, "try save null data");
  return save_impl (_info, _mem, _size_mem);
}

#if 0
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
#endif
#if 0
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
#endif
#if 0
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
#endif

}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test
