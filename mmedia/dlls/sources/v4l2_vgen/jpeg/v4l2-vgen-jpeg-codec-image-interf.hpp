#pragma once
/**
\file       v4l2-vgen-codec-image-interf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/
#if 0
namespace dlls { namespace sources { namespace v4l2_openmax_vgen { namespace jpeg {
/**
\brief  gpu raspberry
*/
class JpegCodecImageInterf : public ::libs::ievents::runtime::interf::interfaces::ICodecImage
{
  public:
    //  ext types
U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (JpegCodecImageInterf)

  JpegCodecImageInterf () :
    update_ (false),
    id_format_ ("jpeg")
  {
  }

  virtual ~JpegCodecImageInterf ()
  {
  }

  bool
  is_codec_property_update () const
  {
    return update_;
  }

  VideoCodecProp::craw_ptr
  get_codec_property () const
  {
    update_ = false;
    return &props_;
  }


  private:
  virtual const id_format_type&
  get_id_format_int () const override
  {
    return id_format_;
  }

  virtual void
  update_codec_property_int (const VideoCodecProp::raw_ptr info) override
  {
    
    update_ = true;
    props_  = *info;
    return;
  }

  virtual void
  code_image_int (IBuf::raw_ptr buf) override
  {
    return;
  }

  virtual void
  decode_image_int (const std::uint8_t* info, const std::int32_t size_info, IBuf::raw_ptr buf) override
  {
    return;
  }

  mutable bool      update_;         //<
  const std::string id_format_;      //<
  VideoCodecProp    props_;          //<
};

}}}}      // namespace dlls::sources::v4l2_vgen::jpeg
#endif
