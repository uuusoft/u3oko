#pragma once
/**
\file       state-record.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::indexer::test
{
class StateRecord final
{
  public:
  // ext types
  using id_chunk_type    = IStorageImpl::id_chunk_type;
  using time_record_type = ::libs::istorage_events::StreamTimes;

  StateRecord ()
  {
  }

  virtual ~StateRecord ()
  {
  }

  id_chunk_type    id_;      //<
  time_record_type start_;   //<
  time_record_type stop_;    //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (id_);
    ar& BOOST_SERIALIZATION_NVP (start_);
    ar& BOOST_SERIALIZATION_NVP (stop_);
  }
};
}   // namespace modules::uuu_storage::appl::impl::indexer::test
