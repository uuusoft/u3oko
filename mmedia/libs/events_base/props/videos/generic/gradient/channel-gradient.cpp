/**
\file       channel-gradient.cpp
\author     Erashov Anton erashov2026@proton.me
\date       28.05.2022
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "type-gradient.hpp"
#include "channel-gradient.hpp"

namespace libs::events_base::props::videos::generic::gradient
{
ChannelGradient::ChannelGradient (const Gradients& type) :
  gradient_type_ (type),
  string_vals_ ("#0 20 10\n#20 40 30\n#40 60 50\n#60 80 70\n#80 100 90\n#100 120 110\n#120 140 130\n#140 180 160\n#180 200 190\n#200 240 220\n#240 256 250")
{
  std::ranges::fill (vals_, 0);
}


template< class Archive >
void
ChannelGradient::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (gradient_type_);
  arh& BOOST_SERIALIZATION_NVP (animation_);
  arh& BOOST_SERIALIZATION_NVP (blure_);
  arh& BOOST_SERIALIZATION_NVP (vals_);
  arh& BOOST_SERIALIZATION_NVP (string_vals_);
  arh& BOOST_SERIALIZATION_NVP (future_ext_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const ChannelGradient& src)
{
  jvs = {
    { "gradient_type", ::boost::json::value_from (src.gradient_type_) },
    { "animation", src.animation_ },
    { "blure", src.blure_ },
    { "vals", ::boost::json::value_from (src.vals_) },
    { "string_vals", src.string_vals_ },
    { "future_ext", src.future_ext_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< ChannelGradient >, const ::boost::json::value& jvs) -> ChannelGradient
{
  ChannelGradient              ret;
  const ::boost::json::object& obj = jvs.as_object ();

  ret.gradient_type_ = ::boost::json::value_to< Gradients > (obj.at ("gradient_type"));
  ret.animation_     = obj.at ("animation").as_bool ();
  ret.blure_         = obj.at ("blure").as_bool ();
  ret.vals_          = ::boost::json::value_to< std::array< std::int16_t, 256 > > (obj.at ("vals"));
  ret.string_vals_   = obj.at ("string_vals").as_string ();
  ret.future_ext_    = obj.at ("future_ext").as_string ();
  return ret;
}
}   // namespace libs::events_base::props::videos::generic::gradient

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::gradient::ChannelGradient);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::gradient::ChannelGradient);
