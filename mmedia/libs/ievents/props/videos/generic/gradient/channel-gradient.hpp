#pragma once
/**
\file       channel-gradient.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       28.05.2022

\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::gradient
{
struct ChannelGradient final {
  explicit ChannelGradient (const Gradients& type = Gradients::skip);
  virtual ~ChannelGradient ();

  Gradients                       gradient_type_;   //<
  bool                            animation_;       //<
  bool                            blure_;           //<
  std::array< std::int16_t, 256 > vals_;            //<
  std::string                     string_vals_;     //<
  std::string                     future_ext_;      //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void            tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const ChannelGradient& src);
ChannelGradient tag_invoke (::boost::json::value_to_tag< ChannelGradient >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::gradient

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::gradient::ChannelGradient);
