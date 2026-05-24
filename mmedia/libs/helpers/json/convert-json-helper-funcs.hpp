#pragma once
/**
\file       convert-json-helper-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.06.2022
\project    u3_helpers_lib
*/

namespace libs::helpers::json
{
bool          get_bool (const ::boost::json::value& val);
std::int32_t  get_int32 (const ::boost::json::value& val);
std::uint32_t get_uint32 (const ::boost::json::value& val);
std::int64_t  get_int64 (const ::boost::json::value& val);
std::uint64_t get_uint64 (const ::boost::json::value& val);
float         get_float (const ::boost::json::value& val);
double        get_double (const ::boost::json::value& val);
std::string   get_string (const ::boost::json::value& val);
std::string   to_string (const std::string& val);

template< class T >
void
extract (const ::boost::json::object& obj, T& res, ::boost::string_view key)
{
  res = ::boost::json::value_to< T > (obj.at (key));
}
}   // namespace libs::helpers::json
