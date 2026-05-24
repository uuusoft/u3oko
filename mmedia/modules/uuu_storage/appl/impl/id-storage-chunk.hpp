#pragma once
/**
\file       id-storage-chunk.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       03.09.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::impl
{
struct IdStorageChunk final {
  using id_type = std::int32_t;

  static constexpr id_type invalid_id = -1;

  IdStorageChunk () :
    id_file_ (invalid_id), id_fragment_ (invalid_id)
  {
    U3_ASSERT (!is_valid ());
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

  // cuuid id_session_;       //<
  id_type id_file_;       //<
  id_type id_fragment_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& ar, const std::uint32_t /* file_version */)
  {
    // ar& BOOST_SERIALIZATION_NVP (id_session_);
    ar& BOOST_SERIALIZATION_NVP (id_file_);
    ar& BOOST_SERIALIZATION_NVP (id_fragment_);
  }
};

inline std::ostream&
operator<< (std::ostream& stream, const IdStorageChunk& val)
{
  // stream << val.id_session_.name () << "." << val.id_file_ << "." << val.id_fragment_;
  stream << val.id_file_ << "." << val.id_fragment_;
  return stream;
}
}   // namespace modules::uuu_storage::appl::impl
