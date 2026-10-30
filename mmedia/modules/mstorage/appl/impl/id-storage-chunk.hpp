#pragma once
/**
\file       id-storage-chunk.hpp
\author     Erashov Anton erashov2026@proton.me
\date       03.09.2018
*/

namespace modules::mstorage::appl::impl
{
struct IdStorageChunk final {
  using id_type = std::int32_t;

  static constexpr id_type invalid_id = -1;

  IdStorageChunk ()
  {
    ::libs::utility::checks::throw_ifn (!is_valid ());
  }

  bool
  is_valid () const
  {
    if (invalid_id == id_file_ || invalid_id == id_fragment_)   // || id_session_.empty ())
    {
      return false;
    }
    return true;
  }

  void
  reset ()
  {
    id_file_     = invalid_id;
    id_fragment_ = invalid_id;
  }

  id_type id_file_ { invalid_id };       //<
  id_type id_fragment_ { invalid_id };   //<

  private:
  friend class boost::serialization::access;

#if (U3_USE_BOOST_SERIALIZTION)
  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    // arh& BOOST_SERIALIZATION_NVP (id_session_);
    arh& BOOST_SERIALIZATION_NVP (id_file_);
    arh& BOOST_SERIALIZATION_NVP (id_fragment_);
  }
#endif
};

inline std::ostream&
operator<< (std::ostream& stream, const IdStorageChunk& val)
{
  stream << val.id_file_ << "." << val.id_fragment_;
  return stream;
}
}   // namespace modules::mstorage::appl::impl
