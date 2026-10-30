#pragma once
/**
\file       index-data-file-state.hpp
\author     Erashov Anton erashov2026@proton.me
\date       05.09.2018
*/

namespace modules::mstorage::appl::impl::storage::test
{
struct IndexDataFileState final {
  //  ext types
  using fragment_element_type  = std::pair< consts::consts_val_type, consts::consts_val_type >;   //< offset, size
  using fragments_element_type = std::vector< fragment_element_type >;

  static const consts::consts_val_type invalid_indx = 0xFFFFFFFFFFFFFFFFull;

  IndexDataFileState ()  = default;
  ~IndexDataFileState () = default;

  void
  reset ()
  {
    indx_data_file_  = invalid_indx;
    count_fragments_ = 0;
    off_fragments_.clear ();
    off_fragments_.reserve (consts::max_count_fragments_session_data_file);
    ::libs::utility::checks::throw_ifn (!is_valid ());
  }

  bool
  is_valid () const
  {
    if (invalid_indx == indx_data_file_)
    {
      return false;
    }

    ::libs::utility::checks::throw_ifn (indx_data_file_ <= consts::max_count_session_data_files, VTOLOG (indx_data_file_));
    ::libs::utility::checks::throw_ifn (count_fragments_ <= consts::max_count_fragments_session_data_file, VTOLOG (count_fragments_));
    ::libs::utility::checks::throw_ifn (count_fragments_ <= off_fragments_.size (), VTOLOG (count_fragments_));
    return true;
  }

  consts::consts_val_type indx_data_file_  = invalid_indx;   //< [0..max_count_session_data_files)
  consts::consts_val_type count_fragments_ = 0;              //< [0..max_count_fragments_session_data_file)
  fragments_element_type  off_fragments_;                    //<

  private:
  friend class boost::serialization::access;

#if (U3_USE_BOOST_SERIALIZTION)
  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (indx_data_file_);
    arh& BOOST_SERIALIZATION_NVP (count_fragments_);
    arh& BOOST_SERIALIZATION_NVP (off_fragments_);
  }
#endif
};
}   // namespace modules::mstorage::appl::impl::storage::test
