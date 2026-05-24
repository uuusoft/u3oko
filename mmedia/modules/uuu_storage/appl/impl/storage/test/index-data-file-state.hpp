#pragma once
/**
\file       index-data-file-state.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.09.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::storage::test
{
struct IndexDataFileState final {
  //  ext types
  using fragment_element_type  = std::pair< consts::consts_val_type, consts::consts_val_type >;   //< offset, size
  using fragments_element_type = std::vector< fragment_element_type >;

  static const consts::consts_val_type invalid_indx = 0xFFFFFFFFFFFFFFFFull;

  IndexDataFileState () :
    indx_data_file_ (invalid_indx),
    count_fragments_ (0)
  {
  }

  void
  reset ()
  {
    indx_data_file_  = invalid_indx;
    count_fragments_ = 0;
    off_fragments_.clear ();
    off_fragments_.reserve (consts::max_count_fragments_session_data_file);
    U3_ASSERT (!is_valid ());
  }

  bool
  is_valid () const
  {
    if (invalid_indx == indx_data_file_)
    {
      return false;
    }

    U3_CHECK (indx_data_file_ <= consts::max_count_session_data_files, VTOLOG (indx_data_file_));
    U3_CHECK (count_fragments_ <= consts::max_count_fragments_session_data_file, VTOLOG (count_fragments_));
    U3_CHECK (count_fragments_ <= off_fragments_.size (), VTOLOG (count_fragments_));
    return true;
  }

  consts::consts_val_type indx_data_file_;    //< [0..max_count_session_data_files)
  consts::consts_val_type count_fragments_;   //< [0..max_count_fragments_session_data_file)
  fragments_element_type  off_fragments_;     //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (indx_data_file_);
    ar& BOOST_SERIALIZATION_NVP (count_fragments_);
    ar& BOOST_SERIALIZATION_NVP (off_fragments_);
  }
};
}   // namespace modules::uuu_storage::appl::impl::storage::test
