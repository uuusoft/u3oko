#pragma once
/**
\file       sync-objs-action.hpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::control
{
enum class SyncActions : std::uint32_t
{
  info     = 0x00,   //< команда, для получения списка объектов со статусами, которые уже связаны с клиентом
  sync     = 0x01,   //< команда, использовать объекты из списка, связав их с клиентом со статусом запущены, ранее связанные объекты вне списка удалить из привязки
  uplink   = 0x02,   //< команда, привязать объекты из списка к клиенту (при успехе статус объектов запущен)
  downlink = 0x03,   //< команда, удалить объекты из списка из связи
  start    = 0x04,   //< команда-статус, запустить объекты из списка, если они имеют связь с клиентом
  stop     = 0x05,   //< команда-статус, остановить объекта из списка, если они имеют связь с клиентом
  empty    = 0x06,   //< пустая команда, игнорировать список, ничего не делать
  unknown  = 0xFF    //< для общности
};

std::string to_string (const SyncActions& val);

inline constexpr SyncActions
sync_objs_action_from_raw_val (std::uint32_t val)
{
  return U3_CAST_STATIC< SyncActions > (val);
}
}   // namespace libs::ievents::runtime::control
