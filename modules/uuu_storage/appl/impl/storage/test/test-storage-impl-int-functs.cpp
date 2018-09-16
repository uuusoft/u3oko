/**
\file       test-storage-impl-int-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       07.09.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "test-storage-impl.hpp"

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace storage { namespace test {

TestStorageImpl::info_seance_type&
TestStorageImpl::get_seance_info (const seance_type& _info)
{
  auto _find = seances2infos_.find (_info);
  if (seances2infos_.end () == _find)
    {
      auto& _ret = seances2infos_[_info];
      _ret.reset ();
      _ret.state_.id_ = _info;
      prepare_write_seance (_info);
      return _ret;
    }
  return _find->second;
}


void
TestStorageImpl::prepare_write_seance (const seance_type& _info)
{
  auto _full_path = ::libs::helpers::files::make_path (root_path_, _info);
  ::libs::helpers::files::create_folder (_full_path);
  UASSERT (seances2infos_.end () != seances2infos_.find (_info));
  UASSERT_SIGNAL ("unimplementated");
  //auto _uinfo = seances2infos_[_info];
  //  Сохраняем начальное состояние (пока пустое) в новой папке сеанса.
  //helpers::store_seance (root_path_, _uinfo);
  //_uinfo.state_.count_fragments_ = 0;
  //_uinfo.state_.indx_data_file_
  return;
}


TestStorageImpl::id_chunk_type
TestStorageImpl::save_impl (const seance_type& _info, const unsigned char* _mem, const std::size_t _size_mem)
{
  auto& _sinfo = get_seance_info (_info);
  get_next_write_id_by_seance (_info, _sinfo);
  CHECK_CALL (save_data (_info, _sinfo, _mem, _size_mem), "failed save data to file");
  return _sinfo.cursor_;
}


void
TestStorageImpl::get_next_write_id_by_seance (const seance_type& _info, info_seance_type& _sinfo)
{
  //  Если текущий файл данных уже переполнен - закрываем его.
  if ((_sinfo.index_state_.count_fragments_ >= consts::max_count_fragments_session_data_file) || (_sinfo.size_data_file_ >= consts::max_size_session_data_file))
    {
      XULOG_TRACE ("TestStorageImpl::get_next_write_id_by_seance, close exist index frame");
      helpers::store_index_file (root_path_, _sinfo);
      _sinfo.index_state_.reset ();
      _sinfo.size_data_file_ = 0;
    }
  //  Проверяем, может требуется открыть новый файл с данными.
  if (!_sinfo.index_state_.is_valid ())
    {
      XULOG_TRACE ("TestStorageImpl::get_next_write_id_by_seance, create new index frame");
      ++_sinfo.state_.count_data_files_;
      _sinfo.index_state_.count_fragments_ = 0;
      _sinfo.index_state_.indx_data_file_  = _sinfo.state_.count_data_files_ - 1;

      const auto _dir_path  = ::libs::helpers::files::make_path (root_path_, _sinfo.state_.id_);
      const auto _file_name = ::to_str (_sinfo.index_state_.indx_data_file_) + "." + consts::name_ext_data_file;
      const auto _file_path = ::libs::helpers::files::make_path (_dir_path, _file_name);
      auto&      _dfile     = _sinfo.data_file_;

      if (_dfile.is_open ())
        {
          _dfile.close ();
          _dfile.clear ();
        }

      _dfile.open (_file_path, std::ios::trunc | std::ios::binary | std::ios::out);
      CHECK_STATE (_dfile.is_open (), "failed open data file, " << _file_path);
      CHECK_STATE( !_dfile.bad(), "error state data file" );
    }

  UASSERT (_sinfo.index_state_.is_valid ());
  _sinfo.cursor_.reset ();
  _sinfo.cursor_.id_file_     = _sinfo.index_state_.indx_data_file_;
  _sinfo.cursor_.id_fragment_ = _sinfo.index_state_.count_fragments_;

  UASSERT (_sinfo.cursor_.is_valid ());
  UASSERT (_sinfo.data_file_.is_open ());
  XULOG_TRACE ("TestStorageImpl::get_next_write_id_by_seance ret=" << _ret);
  return;
}


bool
TestStorageImpl::save_data (const seance_type& _info, info_seance_type& _sinfo, const unsigned char* _mem, const std::size_t _size_mem)
{
  auto& _file = _sinfo.data_file_;
  UASSERT (_file.is_open ());
  UASSERT (_sinfo.index_state_.is_valid ());
  ++_sinfo.index_state_.count_fragments_;
  _sinfo.index_state_.off_fragments_.push_back ({ _sinfo.size_data_file_, _size_mem });      //  параметры нового фрагмента сохраняем в индексном файле.
  _file.write (UUU_MEM_CAST<const char*> (_mem), _size_mem);                                 //  пишем в файл бинарные данные фрагмента.
  if (_file.bad ())
    {
      XULOG_ERROR ("failed write to data file, "
                   << ", " << strerror (errno));
      --_sinfo.index_state_.count_fragments_;
      _sinfo.index_state_.off_fragments_.pop_back ();
      UASSERT (_sinfo.index_state_.is_valid ());
      return false;
    }
  _sinfo.size_data_file_ += _size_mem;
  UASSERT (_sinfo.index_state_.is_valid ());
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
      // Иначе генерируем значение по умолчанию, используя идентификатор и путь по умолчанию.
      auto _path = _iappl->get_path (::libs::iproperties::appl_paths::TypePath::default_storage);
      root_path_ = ::libs::helpers::files::make_path (_path, std::string ("test-storage"));
    }
  ::libs::helpers::files::create_folder (root_path_);
  XULOG_TRACE ("TestStorageImpl::update_path, end, root_path_=" << root_path_);
  return;
}


void
TestStorageImpl::flush_seances ()
{
  XULOG_TRACE ("TestStorageImpl::flush_seances, beg");
  for (const auto& _seance : seances2infos_)
    {
      helpers::store_seance (root_path_, _seance.second);
      helpers::store_index_file (root_path_, _seance.second);
    }

  seances2infos_.clear ();
  XULOG_TRACE ("TestStorageImpl::flush_seances, end");
  return;
}

}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test
