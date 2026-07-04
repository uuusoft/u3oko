#pragma once
/**
\file       type-object-id.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.08.2018
\project    u3_events_storage
*/

namespace libs::events_storage
{
class TypeObjectId
{
  public:
  // ext types
  using id_type = std::string;

  explicit TypeObjectId (const id_type& = consts::empty_object_id);
  virtual ~TypeObjectId () = default;

  bool is_valid () const;
  void reset ();

  bool operator== (const TypeObjectId& obj) const;

  id_type val_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void         tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const TypeObjectId& src);
TypeObjectId tag_invoke (::boost::json::value_to_tag< TypeObjectId >, const ::boost::json::value& jvs);
}   // namespace libs::events_storage

BOOST_CLASS_EXPORT_KEY (::libs::events_storage::TypeObjectId);

namespace boost
{
template<>
struct hash< ::libs::events_storage::TypeObjectId > {
  size_t
  operator() (const ::libs::events_storage::TypeObjectId& val) const noexcept
  {
    return hash< typename ::libs::events_storage::TypeObjectId::id_type > () (val.val_);
  }
};
}   // namespace boost
