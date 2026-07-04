#pragma once
/**
\file       convert-json-helper-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       10.06.2022
\project    u3_helpers_lib
*/

// EAI-REFACT strin_view serialization boost
#if 0
namespace boost::serialization
{
template< class Archive, class CharT, class Traits >
void
save (Archive& arh, const std::basic_string_view< CharT, Traits >& ssv, const unsigned int /*version*/)
{
  std::basic_string< CharT, Traits > sstr (ssv.data (), ssv.size ());
  arh & sstr;
}

template< class Archive, class CharT, class Traits >
void
load (Archive& arh, std::basic_string_view< CharT, Traits >& ssv, const unsigned int /*version*/)
{
  static thread_local std::basic_string< CharT, Traits > sstr;
  arh & sstr;
  ssv = std::basic_string_view< CharT, Traits > (sstr.data (), sstr.size ());
}

template< class Archive, class CharT, class Traits >
void
serialize (Archive& arh, std::basic_string_view< CharT, Traits >& ssv, const unsigned int version)
{
  split_free (arh, ssv, version);
}
}   // namespace boost::serialization
#endif


namespace libs::utility::json
{
auto get_bool (const ::boost::json::value& val) -> bool;
auto get_int32 (const ::boost::json::value& val) -> std::int32_t;
auto get_uint32 (const ::boost::json::value& val) -> std::uint32_t;
auto get_int64 (const ::boost::json::value& val) -> std::int64_t;
auto get_uint64 (const ::boost::json::value& val) -> std::uint64_t;
auto get_float (const ::boost::json::value& val) -> float;
auto get_double (const ::boost::json::value& val) -> double;
auto get_string (const ::boost::json::value& val) -> std::string;
auto to_string (const std::string& val) -> std::string;

template< class T >
void
extract (const ::boost::json::object& obj, T& res, ::boost::string_view key)
{
  res = ::boost::json::value_to< T > (obj.at (key));
}
}   // namespace libs::utility::json


namespace boost::serialization
{
template< class Archive >
void
save (Archive& ar, const ::boost::json::value& jv, unsigned int version)
{
  std::string s = ::boost::json::serialize (jv);
  ar << BOOST_SERIALIZATION_NVP (s);
}

template< class Archive >
void
load (Archive& ar, ::boost::json::value& jv, unsigned int version)
{
  std::string s;
  ar >> BOOST_SERIALIZATION_NVP (s);
  jv = ::boost::json::parse (s);
}

template< class Archive >
void
serialize (Archive& ar, ::boost::json::value& jv, unsigned int version)
{
  split_free (ar, jv, version);
}
}   // namespace boost::serialization
