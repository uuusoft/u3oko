#pragma once
/**
\file       type-codec-mode.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::codec
{
/// Перечсиление режимов видеокодека
enum class CodecModes : std::uint32_t
{
  coder   = 0x00,   //< Режим кодера
  decoder = 0x01,   //< Режим декодер
  unknown = 0xFF    //< Не определенно для общности
};

void       tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const CodecModes& src);
CodecModes tag_invoke (::boost::json::value_to_tag< CodecModes >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::codec
