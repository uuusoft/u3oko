#pragma once
//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       path-info.hpp
\date       22.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace storage {
/**
\brief СТруктура для группировки информации, связанной с одним из путей для сохранения данных подсистемы
*/
struct PathInfo
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (PathInfo);

  PathInfo () :
    state_ (UsingPathType::disabled),
    max_data_size_ (0)
  {}

  bool
  check () const
  {
    return path2data_.empty () || 0 == max_data_size_ ? false : true;
  }

  void
  load (const base_functs::xml::itn& _node)
  {
    pugi::xml_attribute _path2data     = _node->attribute ("path2data");
    pugi::xml_attribute _max_data_size = _node->attribute ("max_data_size");
    pugi::xml_attribute _state         = _node->attribute ("state");
    pugi::xml_attribute _impl_storage  = _node->attribute ("impl_storage_name");
    pugi::xml_attribute _impl_indexer  = _node->attribute ("impl_indexer_name");

    if (!_path2data || !_max_data_size || !_state || !_impl_storage || !_impl_indexer)
      {
        XULOG_WARNING ("failed load PathInfo, empty attrs");
        return;
      }

    path2data_         = _path2data.as_string ();
    max_data_size_     = _max_data_size.as_llong ();
    state_             = str2using_path (_state.as_string ());
    impl_storage_name_ = _impl_storage.as_string ();
    impl_indexer_name_ = _impl_indexer.as_string ();
    return;
  }

  std::string      path2data_;              //< Путь к данным.
  std::string      impl_storage_name_;      //< Имя реализации хранения данных, используемое в данной системе.
  std::string      impl_indexer_name_;      //< Имя реализации индексирования, используемое в данной системе.
  UsingPathType    state_;                  //< Статус данных с точки зрения возможности доступа к ним.
  signed long long max_data_size_;          //< Максимальный размер данных. При превышении начинается перезапись или блокировка записи, в зависимости от доступа.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (path2data_);
    ar& BOOST_SERIALIZATION_NVP (impl_storage_name_);
    ar& BOOST_SERIALIZATION_NVP (impl_indexer_name_);
    ar& BOOST_SERIALIZATION_NVP (state_);
    ar& BOOST_SERIALIZATION_NVP (max_data_size_);
    return;
  }
};

}}}}}      // namespace libs::ievents::props::modules::storage
