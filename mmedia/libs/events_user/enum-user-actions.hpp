#pragma once
/**
\file       enum-user-actions.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.08.2018
*/

namespace libs::events_user
{
enum class UserActions : std::uint32_t
{
  query = 0,         //< запросить список пользователей
  add,               //< добавить пользователей из списка
  remove,            //< удалить пользователей из списка
  disable,           //< отключить пользователей из списка
  unknown = 0xFFFF   //<
};

// std::string   to_string (const UserActions& );
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const UserActions&) -> void;
auto tag_invoke (::boost::json::value_to_tag< UserActions >, const ::boost::json::value&) -> UserActions;
}   // namespace libs::events_user
