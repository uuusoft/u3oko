#pragma once
/**
\file       rect.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_events
*/

namespace libs::events::props::details
{
class Rect
{
  public:
  explicit Rect (std::uint32_t width = 0, std::uint32_t height = 0);
  virtual ~Rect () = default;

  std::uint32_t get_width () const;
  std::uint32_t get_height () const;
  bool          load (::pugi::xml_named_node_iterator& param);
  bool          load (::pugi::xml_node& param);

  private:
  std::uint32_t width_;
  std::uint32_t height_;

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};
}   // namespace libs::events::props::details

BOOST_CLASS_EXPORT_KEY (::libs::events::props::details::Rect);
