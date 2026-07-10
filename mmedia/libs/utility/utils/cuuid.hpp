#pragma once
/**
\file       cuuid.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::utils
{
/// Расширение boost::uuids::uuid необходимым мне функционалом
class cuuid final
{
  public:
  //  ext types
  using value_type = ::boost::uuids::uuid::value_type;
  using data_type  = value_type[16];

  cuuid () = default;
  cuuid (const cuuid& left);
  explicit cuuid (const data_type);
  explicit cuuid (const std::initializer_list< value_type >);
  explicit cuuid (const ::boost::uuids::uuid& base);

#ifdef U3_OS_WIN32_DESKTOP
  explicit cuuid (const GUID& guid);
  const GUID* get_guid () const;
#endif

  virtual ~cuuid () = default;

  cuuid& operator= (const ::boost::uuids::uuid& left);
  cuuid& operator= (const cuuid& left);

  auto reset () -> void;
  auto empty () const -> bool;
  auto get_raw_uuid_vals () const -> const ::boost::uuids::uuid&;

  private:
  ::boost::uuids::uuid id_ = boost::uuids::nil_uuid ();   //< Поле, которые мы функционально расширяем

  friend class ::boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

bool operator< (const cuuid& l, const cuuid& r);
bool operator== (const cuuid& l, const cuuid& r);
bool operator!= (const cuuid& l, const cuuid& r);

auto to_string (const cuuid&) -> std::string;
auto cuuid_from_string (const std::string&) -> cuuid;
auto cuuid_to_buf (const cuuid&, std::uint8_t[16]) -> void;
}   // namespace libs::utility::utils


// Specialize std::hash
namespace boost
{
template<>
struct hash< ::libs::utility::utils::cuuid > {
  std::size_t
  operator() (const ::libs::utility::utils::cuuid& guid) const noexcept
  {
    boost::hash< boost::uuids::uuid > hasher;
    return hasher (guid.get_raw_uuid_vals ());
  }
};
}   // namespace boost

BOOST_CLASS_EXPORT_KEY (::libs::utility::utils::cuuid);
