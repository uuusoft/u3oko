#pragma once
/**
\file       index-data-file-state.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       05.09.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace impl { namespace storage { namespace test {
/**
  \brief  Состояние (хранимое) индексации одного файла данных сессии.
  */
struct IndexDataFileState
{
  //  ext types
  using fragment_element_type  = std::pair<consts::consts_val_type, consts::consts_val_type>;
  using fragments_element_type = std::vector<fragment_element_type>;

  static const consts::consts_val_type invalid_indx = -1;

  IndexDataFileState () :
    indx_data_file_ (invalid_indx),
    count_fragments_ (0)
  {}

  void
  reset ()
  {
    indx_data_file_  = invalid_indx;
    count_fragments_ = 0;
    off_fragments_.clear ();
    off_fragments_.reserve (consts::max_count_fragments_session_data_file);
    UASSERT (!is_valid ());
    return;
  }

  bool
  is_valid () const
  {
    if (invalid_indx == indx_data_file_)
      {
        return false;
      }
    //  Если главный индекс корректен - все связанные с ним тоже должны быть корректными.
    CHECK_STATE (indx_data_file_ >= 0 && indx_data_file_ <= consts::max_count_session_data_files, "indx_data_file=" << indx_data_file_);
    CHECK_STATE (count_fragments_ >= 0 && count_fragments_ <= consts::max_count_fragments_session_data_file, "count_fragments=" << count_fragments_);
    CHECK_STATE (count_fragments_ <= off_fragments_.size (), "count_fragments=" << count_fragments_);
    return true;
  }

  consts::consts_val_type indx_data_file_;       //< Индекс файла данных, с котором свяазана текущая информация индексации, [0..max_count_session_data_files).
  consts::consts_val_type count_fragments_;      //< Текущее количество фрагментов в файле данных, [0..max_count_fragments_session_data_file).
  fragments_element_type  off_fragments_;        //< Смещение и размер фрагментов относительно начала файла данных.


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (indx_data_file_);
    ar& BOOST_SERIALIZATION_NVP (count_fragments_);
    ar& BOOST_SERIALIZATION_NVP (off_fragments_);
    return;
  }
};

}}}}}}      // namespace modules::uuu_storage::appl::impl::storage::test
