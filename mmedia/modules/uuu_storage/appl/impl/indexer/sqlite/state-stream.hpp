#pragma once
/**
\file       state-stream.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::indexer::sqlite
{
class StateStream final
{
  public:
  // ext types
  using records_type     = std::list< StateRecord >;
  using stream_id_type   = ::libs::istorage_events::stream_id_type;
  using time_stream_type = ::libs::istorage_events::StreamTimes;

  explicit StateStream (const stream_id_type& id = ::libs::istorage_events::consts::empty_stream_id) :
    id_ (id)
  {
  }

  virtual ~StateStream ()
  {
  }

  stream_id_type id_;        //<
  records_type   records_;   //<

  const time_stream_type*
  get_start () const
  {
    if (records_.empty ())
    {
      return nullptr;
    }

    return &records_.front ().start_;
  }

  const time_stream_type*
  get_stop () const
  {
    if (records_.empty ())
    {
      return nullptr;
    }

    return &records_.back ().stop_;
  }

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (records_);
    ar& BOOST_SERIALIZATION_NVP (id_);
  }
};
}   // namespace modules::uuu_storage::appl::impl::indexer::sqlite
