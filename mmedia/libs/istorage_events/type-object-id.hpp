#pragma once
/**
\file       type-object-id.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.08.2018
\project    u3_istorage_events
*/

namespace libs::istorage_events
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
}   // namespace libs::istorage_events

BOOST_CLASS_EXPORT_KEY (::libs::istorage_events::TypeObjectId);

namespace std
{
template<>
struct hash< ::libs::istorage_events::TypeObjectId > {
  size_t
  operator() (const ::libs::istorage_events::TypeObjectId& val) const noexcept
  {
    return hash< typename ::libs::istorage_events::TypeObjectId::id_type > () (val.val_);
  }
};
}   // namespace std
