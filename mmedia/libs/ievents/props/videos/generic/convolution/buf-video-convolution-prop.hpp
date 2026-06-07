#pragma once
/**
\file       buf-video-convolution-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::convolution::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;
}

namespace libs::ievents::props::videos::generic::convolution
{
struct BuffVideoConvolutionProp final : public ::libs::events::buf::EventBufsInfo {
  public:
  explicit BuffVideoConvolutionProp (
    const syn::off_buf_type& src              = utils::dbufs::video::consts::offs::invalid,
    const syn::off_buf_type& dst              = utils::dbufs::video::consts::offs::invalid,
    const Convs&             convolution_type = Convs::skip,
    const std::int32_t       core_size        = 5,
    const std::int32_t       core_koeff       = 0,
    const bool               use_module       = false);

  explicit BuffVideoConvolutionProp (
    const ::libs::events::buf::EventBufsInfo& buf,
    const Convs&                              convolution_type = Convs::skip,
    const std::int32_t                        core_size        = 5,
    const std::int32_t                        core_koeff       = 0,
    const bool                                use_module       = false);

  Convs                       convolution_type_ = Convs::skip;   //<
  std::int32_t                core_size_        = 5;             //<
  std::int32_t                core_koeff_       = 0;             //<
  bool                        use_module_       = false;         //<
  std::vector< std::int16_t > core_vals_;                        //<

  protected:
  virtual void check_int () override;
  virtual void correct_int () override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buf::EventBufsInfo)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const BuffVideoConvolutionProp& src);
BuffVideoConvolutionProp tag_invoke (::boost::json::value_to_tag< BuffVideoConvolutionProp >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::generic::convolution

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::convolution::BuffVideoConvolutionProp);
