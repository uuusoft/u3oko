/**
\file       rect.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../includes_int.hpp"
#include "rect.hpp"

namespace libs::events::props::details
{
Rect::Rect (std::uint32_t width, std::uint32_t height) :
  width_ (width),
  height_ (height)
{
}


auto
Rect::get_width () const -> std::uint32_t
{
  return width_;
}


auto
Rect::get_height () const -> std::uint32_t
{
  return height_;
}


auto
Rect::load (::pugi::xml_named_node_iterator& param) -> bool
{
  return load (*param);
}


auto
Rect::load (::pugi::xml_node& param) -> bool
{
  ::pugi::xml_attribute width  = param.attribute ("width");
  ::pugi::xml_attribute height = param.attribute ("height");

  if (!width || !height)
  {
    ::libs::utility::checks::throw_exception ("failed");
    return false;
  }

  width_  = width.as_uint ();
  height_ = height.as_uint ();
  return true;
}


#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
Rect::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (width_);
  arh& BOOST_SERIALIZATION_NVP (height_);
}
#endif
}   // namespace libs::events::props::details

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::props::details::Rect);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::props::details::Rect);
