#pragma once
/**
\file       state-object.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       15.08.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl::indexer::sqlite
{
class StateObject
{
  public:
  // ext types
  using streams_type = std::list< StateStream >;
  using TypeObjectId = ::libs::istorage_events::TypeObjectId;

  StateObject ()
  {
  }

  virtual ~StateObject ()
  {
  }

  bool
  operator== (const StateObject& lv) const
  {
    return id_.val_ == lv.id_.val_;
  }

  TypeObjectId id_;        //<
  streams_type streams_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (id_);
    ar& BOOST_SERIALIZATION_NVP (streams_);
  }
};
}   // namespace modules::uuu_storage::appl::impl::indexer::sqlite


namespace std
{
template<>
struct hash< ::modules::uuu_storage::appl::impl::indexer::sqlite::StateObject > {
  size_t
  operator() (const ::modules::uuu_storage::appl::impl::indexer::sqlite::StateObject& val) const noexcept
  {
    return hash< typename ::modules::uuu_storage::appl::impl::indexer::sqlite::StateObject::TypeObjectId > () (val.id_);
  }
};
}   // namespace std
