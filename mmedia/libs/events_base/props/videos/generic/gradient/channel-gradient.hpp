#pragma once
/**
\file       channel-gradient.hpp
\author     Erashov Anton erashov2026@proton.me
\date       28.05.2022
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::gradient
{
struct ChannelGradient final {
  explicit ChannelGradient (const Gradients& type = Gradients::skip);
  virtual ~ChannelGradient () = default;

  Gradients                       gradient_type_;       //<
  bool                            animation_ = false;   //<
  bool                            blure_     = false;   //<
  std::array< std::int16_t, 256 > vals_ {};             //<
  std::string                     string_vals_;         //<
  std::string                     future_ext_;          //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void            tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const ChannelGradient& src);
ChannelGradient tag_invoke (::boost::json::value_to_tag< ChannelGradient >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::gradient

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::gradient::ChannelGradient);
