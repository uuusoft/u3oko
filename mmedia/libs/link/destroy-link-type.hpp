#pragma once
/**
\file       destroy-link-type.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
*/

namespace libs::link
{
/// Перечисление различных режимов удаления связи
enum class LinkDestroys : std::uint32_t
{
  soft    = 0x00,   //< Мягкое удаление ссылки на связь. Сам обьект может существовать (а может и нет, если общее количество ссылок на него меньше или равно 0)
  force   = 0x01,   //< Принудительное удаление объекта, вне зависимости от количества ссылок на него
  unknown = 0xFF    //< Не определенно для общности
};
}   // namespace libs::link
