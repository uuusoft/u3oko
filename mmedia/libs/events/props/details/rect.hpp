#pragma once
/**
\file       rect.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::events::props::details
{
class Rect
{
  public:
  explicit Rect (std::uint32_t = 0, std::uint32_t = 0);
  virtual ~Rect () = default;

  auto get_width () const -> std::uint32_t;
  auto get_height () const -> std::uint32_t;
  auto load (::pugi::xml_named_node_iterator&) -> bool;
  auto load (::pugi::xml_node&) -> bool;

  private:
  std::uint32_t width_ { 0 };
  std::uint32_t height_ { 0 };

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events::props::details

U3_BOOST_CLASS_EXPORT_KEY (::libs::events::props::details::Rect);
