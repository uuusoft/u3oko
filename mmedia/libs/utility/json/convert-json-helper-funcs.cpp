/**
\file       convert-json-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.06.2022
\project    u3_helpers_lib
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../utility-lib-includes_int.hpp"
#include "convert-json-helper-funcs.hpp"

namespace libs::utility::json::consts
{
constexpr char special_symbol = '~';
}

namespace libs::utility::json::details
{
auto
check_source (const std::string& val) -> bool
{
  return std::string::npos == val.find (libs::utility::json::consts::special_symbol) ? true : false;
}

auto
to_json_string (const std::string& val) -> std::string
{
  U3_ASSERT (check_source (val));
  std::string temp (val);

  std::ranges::transform (
    temp,

    temp.begin (),
    [] (char ch) -> char {
      return ch == ' ' ? libs::utility::json::consts::special_symbol : ch;
    });
  U3_XLOG_DBG ("to_json_string" + TOLOG (val) + TOLOG (temp));
  return temp;
}

auto
from_json_string (const std::string& val) -> std::string
{
  std::string temp (val);

  std::ranges::transform (
    temp,

    temp.begin (),
    [] (char ch) -> char {
      return ch == libs::utility::json::consts::special_symbol ? ' ' : ch;
    });
  U3_XLOG_DBG ("from_json_string" + TOLOG (val) + TOLOG (temp));
  return temp;
}
}   // namespace libs::utility::json::details


namespace libs::utility::json
{
auto
get_bool (const ::boost::json::value& val) -> bool
{
  return U3_CAST_BOOL (val.is_string () ? std::stoi (val.as_string ().c_str ()) : (val.is_bool () ? val.as_bool () : (val.is_int64 () ? val.as_int64 () : val.as_uint64 ())));
}


auto
get_int32 (const ::boost::json::value& val) -> std::int32_t
{
  if (auto temp = val.try_as_int64 ())
  {
    return U3_CAST_INT32 (*temp);
  }
  if (auto temp = val.try_as_uint64 ())
  {
    return U3_CAST_INT32 (*temp);
  }
  if (auto temp = val.try_as_string ())
  {
    return U3_CAST_INT32 (std::stoi (temp->c_str ()));
  }
  U3_XLOG_WARN ("load int32 from json" + VTOLOG (U3_CAST_INT32_FORCE (val.kind ())));
  return 0;
}


auto
get_uint32 (const ::boost::json::value& val) -> std::uint32_t
{
  if (auto temp = val.try_as_uint64 ())
  {
    return U3_CAST_UINT32 (*temp);
  }
  if (auto temp = val.try_as_int64 ())
  {
    return U3_CAST_UINT32 (*temp);
  }
  if (auto temp = val.try_as_string ())
  {
    return U3_CAST_UINT32 (std::stoi (temp->c_str ()));
  }
  U3_XLOG_WARN ("load uint32 from json" + VTOLOG (U3_CAST_INT32_FORCE (val.kind ())));
  return 0;
}


auto
get_int64 (const ::boost::json::value& val) -> std::int64_t
{
  if (auto temp = val.try_as_int64 ())
  {
    return U3_CAST_INT64 (*temp);
  }
  if (auto temp = val.try_as_uint64 ())
  {
    return U3_CAST_INT64 (*temp);
  }
  if (auto temp = val.try_as_string ())
  {
    return U3_CAST_INT64 (std::stoi (temp->c_str ()));
  }
  U3_XLOG_WARN ("load int64 from json" + VTOLOG (U3_CAST_INT32_FORCE (val.kind ())));
  return 0;
}


auto
get_uint64 (const ::boost::json::value& val) -> std::uint64_t
{
  if (auto temp = val.try_as_uint64 ())
  {
    return U3_CAST_UINT64 (*temp);
  }
  if (auto temp = val.try_as_int64 ())
  {
    return U3_CAST_UINT64 (*temp);
  }
  if (auto temp = val.try_as_string ())
  {
    return U3_CAST_UINT64 (std::stoi (temp->c_str ()));
  }
  U3_XLOG_WARN ("load uint64 from json" + VTOLOG (U3_CAST_INT32_FORCE (val.kind ())));
  return 0;
}


auto
get_float (const ::boost::json::value& val) -> float
{
  return U3_CAST_FLOAT (val.is_double () ? val.as_double () : (val.is_int64 () ? val.as_int64 () : (val.is_uint64 () ? val.as_uint64 () : ::boost::lexical_cast< float > (val.as_string ()))));
}


auto
get_double (const ::boost::json::value& val) -> double
{
  return U3_CAST_DOUBLE (val.is_double () ? val.as_double () : (val.is_int64 () ? val.as_int64 () : (val.is_uint64 () ? val.as_uint64 () : ::boost::lexical_cast< double > (val.as_string ()))));
}


auto
get_string (const ::boost::json::value& val) -> std::string
{
  auto temp = std::string (val.as_string ());
  return details::from_json_string (temp);
}


auto
to_string (const std::string& val) -> std::string
{
  return details::to_json_string (val);
}
}   // namespace libs::utility::json
