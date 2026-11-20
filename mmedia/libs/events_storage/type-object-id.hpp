#pragma once
/**
\file       type-object-id.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.08.2018
*/

namespace libs::events_storage
{
class TypeObjectId
{
  public:
  // ext types
  using id_type = std::string;

  explicit TypeObjectId (std::string_view = consts::empty_object_id);
  virtual ~TypeObjectId () = default;

  auto is_valid () const -> bool;
  auto reset () -> void;
  auto operator== (const TypeObjectId& obj) const -> bool;

  id_type val_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */);
};

auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const TypeObjectId&) -> void;
auto tag_invoke (::boost::json::value_to_tag< TypeObjectId >, const ::boost::json::value&) -> TypeObjectId;
}   // namespace libs::events_storage

U3_BOOST_CLASS_EXPORT_KEY (::libs::events_storage::TypeObjectId);

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
