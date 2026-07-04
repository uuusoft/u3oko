#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
#  pragma once
/**
\file       type-object-id.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.08.2018
\project    u3_events_user
*/

namespace libs::events_user
{
class TypeObjectId
{
  public:
  // ext types
  using id_type = std::string;

  explicit TypeObjectId (const id_type& val = consts::empty_object_id);
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
}   // namespace libs::events_user

BOOST_CLASS_EXPORT_KEY (::libs::events_user::TypeObjectId);

namespace boost
{
template<>
struct hash< ::libs::events_user::TypeObjectId > {
  size_t
  operator() (const ::libs::events_user::TypeObjectId& val) const noexcept
  {
    return hash< typename ::libs::events_user::TypeObjectId::id_type > () (val.val_);
  }
};
}   // namespace boost
#endif
