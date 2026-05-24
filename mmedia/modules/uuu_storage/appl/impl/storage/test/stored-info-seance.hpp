#pragma once
/**
\file       stored-info-seance.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       06.09.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::storage::test
{
struct StoredInfoSeance final {
  StoredInfoSeance ()
  {
  }

  void
  reset ()
  {
    count_data_files_ = 0;
    id_.clear ();
  }

  IStorageImpl::seance_type id_;                     //<
  std::uint64_t             count_data_files_ = 0;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (id_);
    ar& BOOST_SERIALIZATION_NVP (count_data_files_);
  }
};
}   // namespace modules::uuu_storage::appl::impl::storage::test
