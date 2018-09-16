#pragma once
/**
\file       save2file-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       06.09.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace storage { namespace test { namespace helpers {
/**
\brief      Функция формирует имя каталога сеанса для сохранения всех файлов (как индексных, так и с данными).
\param[in]  _root_path  корневой каталог для каталога сеанса.
\param[in]  _info       информация о сеансе.
\return     имя каталога сеанса.
*/
inline std::string
get_seance_folder (const std::string& _root_path, const TestStorageImpl::info_seance_type& _info)
{
  UASSERT (!_root_path.empty ());
  auto _ret = ::libs::helpers::files::make_path (_root_path, _info.state_.id_);
  ::libs::helpers::files::create_folder (_ret);
  return _ret;
}
/**
\brief      Вспомогательная функция сброса объекта произвольного типа в файл в виде xml архива.
\tparam     ObjType     тип объекта для сохранения.
\param[in]  _obj        объект для сохранения.
\param[in]  _path2file  путь к файлу с архивом.
*/
template <typename ObjType>
bool
save_obj (const ObjType& _obj, const std::string& _path2file)
{
  UASSERT (!_path2file.empty ());
  std::ofstream _file (_path2file, std::ios::binary | std::ios::trunc);

  if (!_file.is_open ())
    {
      XULOG_ERROR ("failed open file for " << typeid (ObjType).name () << "save, " << _path2file);
      return false;
    }

  try
    {
      boost::archive::xml_oarchive _xmla (_file, boost::archive::no_header);
      _xmla&                       BOOST_SERIALIZATION_NVP (_obj);
    }
  catch (std::exception& _e)
    {
      XULOG_FATAL ("failed save " << typeid (ObjType).name () << "obj, " << _e.what () << ", " << _path2file);
      return false;
    }
  _file.flush ();
  return true;
}
/**
\brief      Функция сохранения информации о всем сеансе в целом. При необходимости производится создание каталога для файлов.
\param[in]  _root_path  корневой каталог для каталога сохранения.
\param[in]  _info информация о сеансе.
*/
inline void
store_seance (const std::string& _root_path, const TestStorageImpl::info_seance_type& _info)
{
  //  Сохраняем начальное состояние (пока пустое) в новой папке сеанса.
  const auto _full_dir_path = get_seance_folder (_root_path, _info);
  const auto _full_path     = ::libs::helpers::files::make_path (_full_dir_path, consts::name_seance_info_file);
  save_obj<StoredInfoSeance> (_info.state_, _full_path);
  return;
}
/**
\brief      Функция сохранения информации о конкретном индексе одного сеанса. При необходимости производится создание каталога для файлов.
\param[in]  _root_path  корневой каталог для каталога сохранения.
\param[in]  _info информация о сеансе.
*/
inline void
store_index_file (const std::string& _root_path, const TestStorageImpl::info_seance_type& _info)
{
  //  Сохраняем начальное состояние (пока пустое) в новой папке сеанса.
  const auto _full_dir_path = get_seance_folder (_root_path, _info);
  const auto _full_path     = ::libs::helpers::files::make_path (_full_dir_path, ::to_str (_info.index_state_.indx_data_file_)) + "." + consts::name_ext_index_data_file;
  save_obj<IndexDataFileState> (_info.index_state_, _full_path);
  return;
}
/**
\brief      Функция сохранения информации о конкретном индексе одного сеанса. При необходимости производится создание каталога для файлов.
\param[in]  _root_path  корневой каталог для каталога сохранения.
\param[in]  _info информация о сеансе.
*/
inline void
store_data_file (const std::string& _root_path, const TestStorageImpl::info_seance_type& _info)
{
  //  Сохраняем начальное состояние (пока пустое) в новой папке сеанса.
  const auto _full_dir_path = get_seance_folder (_root_path, _info);
  //const auto _full_path     = ::libs::helpers::files::make_path (_full_dir_path, consts::name_index_data_file);
  //save_obj<IndexDataFileState> (_info.index_state_, _full_path);
  //UASSERT_SIGNAL ("???");
  return;
}

}}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test::helpers
