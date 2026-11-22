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
make_text_id (std::string_view info, const std::source_location& place) -> std::string
{
  return std::string (info.empty () ? "failed" : info) + " at " + ::libs::utility::log::get_text_source_place (place);
}


auto
throw_exception (std::string_view info, const std::source_location& place) -> void
{
  U3_XLOG_ASSERT ("{}", make_text_id (info, place));
  // U3_XLOG_DEV (std::stacktrace::current ());
  std::stringstream temp;
  temp << make_text_id (info, place);
  BOOST_THROW_EXCEPTION (std::runtime_error (temp.str ().c_str ()));
}


auto
assert_impl (
  bool                        cond,
  bool                        hard,
  std::string_view            info,
  const std::source_location& place) -> void
{
  if (!cond)
  {
    U3_XLOG_ASSERT ("{}", make_text_id (info, place));
    if (hard)
    {
      throw_exception (info, place);
    }
  }
}


auto
assert_hard (bool cond, std::string_view info, const std::source_location& place) -> void
{
  assert_impl (cond, true, info, place);
}


auto
assert_soft (bool cond, std::string_view info, const std::source_location& place) -> void
{
  assert_impl (cond, false, info, place);
}


auto
throw_if (bool cond, std::string_view info, const std::source_location& place) -> void
{
  if (cond)
  {
    ::libs::utility::checks::throw_exception (info, place);
  }
}


auto
throw_ifn (bool cond, std::string_view info, const std::source_location& place) -> void
{
  ::libs::utility::checks::throw_if (!cond, info, place);
}


auto
test (bool cond, std::string_view info, const std::source_location& place) -> void
{
  if (!cond)
  {
    U3_XLOG_MARK ("{}", make_text_id (info, place));
  }
}


auto
mark (std::string_view info, const std::source_location& place) -> void
{
  U3_XLOG_DEV ("MARK-G:{}", make_text_id (info, place));
}


auto
mark_i64 (std::string_view info, const std::source_location& place) -> void
{
  U3_XLOG_DEV ("MARK-64:{}", make_text_id (info, place));
}


auto
mark_todo (std::string_view info, const std::source_location& place) -> void
{
  U3_XLOG_DEV ("MARK-TODO:{}", make_text_id (info, place));
}
}   // namespace libs::utility::checks
