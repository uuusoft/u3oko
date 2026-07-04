#pragma once
/**
\file       create-info-ext.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
/// Структура для расширения полей оригинальной
struct CreateInfoExt final : public ::libs::link::CreateInfo {
  CreateInfoExt () = default;

  CreateInfoExt&
  operator= (const ::libs::link::CreateInfo& src)
  {
    ::libs::utility::casts::static_cast_helper< ::libs::link::CreateInfo& > (*this) = src;
    return *this;
  }

  bool server_side_ = false;   //< Флаг стороны канала
};

inline std::string
to_string (const CreateInfoExt& val)
{
  std::string int_res = to_string (::libs::utility::casts::static_cast_helper< const ::libs::link::CreateInfo& > (val));
  return "CreateInfoExt[" + std::to_string (val.server_side_) + " " + int_res + "]";
}
}   // namespace libs::ilink::impl::oneproc
