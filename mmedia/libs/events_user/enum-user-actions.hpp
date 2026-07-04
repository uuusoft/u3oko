#pragma once
/**
\file       enum-user-actions.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.08.2018
\project    u3_events_storage
*/

namespace libs::events_user
{
enum class UserActions : std::uint32_t
{
  query   = 0x00,   //< запросить список пользователей
  add     = 0x01,   //< добавить -/-
  remove  = 0x02,   //< удалить -/-
  disable = 0x03,   //< отключить -/-
  unknown = 0xFF    //<
};

// std::string   to_string (const UserActions& val);
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const UserActions&) -> void;
auto tag_invoke (::boost::json::value_to_tag< UserActions >, const ::boost::json::value&) -> UserActions;
}   // namespace libs::events_user
