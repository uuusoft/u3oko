/**
\file       buf-video-convolution-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buf-video-convolution-prop.hpp"

namespace libs::ievents::props::videos::generic::convolution
{
BuffVideoConvolutionProp::BuffVideoConvolutionProp (
  const syn::off_buf_type& src,
  const syn::off_buf_type& dst,
  const Convs&             convolution_type,
  const std::int32_t       core_size,
  const std::int32_t       core_koeff,
  const bool               use_module) :

  ::libs::events::buf::EventBufsInfo (src, dst),
  core_size_ (core_size),
  core_koeff_ (core_koeff),
  use_module_ (use_module),
  convolution_type_ (convolution_type)
{
}


BuffVideoConvolutionProp::BuffVideoConvolutionProp (
  const ::libs::events::buf::EventBufsInfo& buf,
  const Convs&                              convolution_type,
  const std::int32_t                        core_size,
  const std::int32_t                        core_koeff,
  const bool                                use_module) :

  ::libs::events::buf::EventBufsInfo (buf),
  core_size_ (core_size),
  core_koeff_ (core_koeff),
  use_module_ (use_module),
  convolution_type_ (convolution_type)
{
}


void
BuffVideoConvolutionProp::check_int ()
{
  U3_CHECK (core_size_ >= 3, "size core less 3");
  U3_CHECK (core_size_ <= 11, "size core large 11");
  U3_CHECK (Convs::skip == convolution_type_ || Convs::use_exist != convolution_type_ || core_vals_.size () == U3_CAST_SIZE_T (core_size_ * core_size_), "invalid vals core" + VTOLOG (core_size_ * core_size_) + "!=" + VTOLOG (core_vals_.size ()));
}


void
BuffVideoConvolutionProp::correct_int ()
{
  core_size_ = ::libs::helpers::utils::ret_check_bound< std::int16_t > (core_size_, 3, 11);

  const auto req_vsize = U3_CAST_SIZE_T (core_size_ * core_size_);
  if (core_vals_.size () != req_vsize)
  {
    core_vals_.resize (req_vsize);
  }
}


template< class Archive >
void
BuffVideoConvolutionProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoeventsobufoEventBufsInfo", super);
  arh& BOOST_SERIALIZATION_NVP (core_size_);
  arh& BOOST_SERIALIZATION_NVP (core_vals_);
  arh& BOOST_SERIALIZATION_NVP (core_koeff_);
  arh& BOOST_SERIALIZATION_NVP (convolution_type_);
  arh& BOOST_SERIALIZATION_NVP (use_module_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const BuffVideoConvolutionProp& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::helpers::casts::static_cast_helper< const ::libs::events::buf::EventBufsInfo& > (src));

  // EAI-JSON-TEST-86
  jvs = {
    { "parent", pjv },
    { "convolution_type", U3_CAST_INT32_FORCE (src.convolution_type_) },
    { "core_size", src.core_size_ },
    { "core_vals", ::boost::json::value_from (src.core_vals_) },
    { "core_koeff", src.core_koeff_ },
    { "use_module", src.use_module_ }
  };
}


BuffVideoConvolutionProp
tag_invoke (::boost::json::value_to_tag< BuffVideoConvolutionProp >, const ::boost::json::value& jvs)
{
  const auto&                  pobj = jvs.at ("parent").as_object ();
  BuffVideoConvolutionProp     ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufsInfo > (), pobj));
  const ::boost::json::object& obj = jvs.as_object ();

  ret.convolution_type_ = ::boost::json::value_to< Convs > (obj.at ("convolution_type"));
  ret.core_size_        = ::libs::helpers::json::get_int32 (obj.at ("core_size"));
  ret.core_vals_        = ::boost::json::value_to< std::vector< std::int16_t > > (obj.at ("core_vals"));
  ret.core_koeff_       = ::libs::helpers::json::get_int32 (obj.at ("core_koeff"));
  ret.use_module_       = obj.at ("use_module").as_bool ();
  return ret;
}
}   // namespace libs::ievents::props::videos::generic::convolution

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::convolution::BuffVideoConvolutionProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::convolution::BuffVideoConvolutionProp);
