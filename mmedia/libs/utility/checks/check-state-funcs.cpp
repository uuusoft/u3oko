/**
\file       check-state-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2026
*/
// EAI-REFACT
// #include <stacktrace>
#include "../utility-lib-includes_int.hpp"
#include "check-state-funcs.hpp"

namespace libs::utility::checks
{
auto
throw_exception (std::string_view info, std::source_location place) -> void
{
  U3_XLOG_ASSERT (STOLOG (info) + std::string (".....") + ::libs::utility::log::get_text_source_place (place));
  // U3_XLOG_DEV (std::stacktrace::current ());
  std::stringstream temp;
  temp << STOLOG (info);
  BOOST_THROW_EXCEPTION (std::runtime_error (temp.str ().c_str ()));
}


auto
assert_impl (bool cond, bool hard, std::string_view info, std::source_location place) -> void
{
  if (cond)
  {
    return;
  }
  U3_XLOG_ASSERT (STOLOG (info) + std::string (".....") + ::libs::utility::log::get_text_source_place (place));
  if (hard)
  {
    throw_exception (info, place);
  }
}


auto
assert_hard (bool cond, std::string_view info, std::source_location place) -> void
{
  assert_impl (cond, true, info, place);
}


auto
assert_soft (bool cond, std::string_view info, std::source_location place) -> void
{
  assert_impl (cond, false, info, place);
}


auto
throw_if (bool cond, std::string_view info, std::source_location place) -> void
{
  if (!cond)
  {
    return;
  }
  ::libs::utility::checks::throw_exception (info, place);
}


auto
throw_ifn (bool cond, std::string_view info, std::source_location place) -> void
{
  ::libs::utility::checks::throw_if (!cond, info, place);
}


auto
test (bool cond, std::string_view info, std::source_location place) -> void
{
  if (cond)
  {
    return;
  }
  U3_XLOG_MARK (STOLOG (info) + ::libs::utility::log::get_text_source_place (place));
}


auto
mark (std::string_view info, std::source_location place) -> void
{
  U3_XLOG_DEV ("MARK:" + STOLOG (info) + ::libs::utility::log::get_text_source_place (place));
}


auto
mark_i64 (std::string_view info, std::source_location place) -> void
{
  U3_XLOG_DBG ("MARK-I64:" + STOLOG (info) + ::libs::utility::log::get_text_source_place (place));
}


auto
mark_todo (std::string_view info, std::source_location place) -> void
{
  U3_XLOG_DBG ("MARK-TODO:" + STOLOG (info) + ::libs::utility::log::get_text_source_place (place));
}
}   // namespace libs::utility::checks
