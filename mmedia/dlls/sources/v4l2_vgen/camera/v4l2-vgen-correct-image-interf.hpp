#pragma once
/**
\file       v4l2-vgen-correct-image-interf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/

// old shit
#if 0
namespace dlls::sources::v4l2_vgen::camera
{
class CorrectImageInterf : public ::libs::ievents::runtime::interf::interfaces::ICorrectImage
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (CorrectImageInterf)

  CorrectImageInterf () :
    update_ (false)
  {
  }

  virtual ~CorrectImageInterf ()
  {
  }

  bool
  is_correction_property_update () const
  {
    return update_;
  }

  VideoCorrectProp::craw_ptr
  get_correction_property () const
  {
    update_ = false;
    return &prop_;
  }


  private:
  virtual void
  change_state_int (bool enable) override
  {
    //  Отключить нельзя, так как функционал напрямую связан с устройством захвата.
    return;
  }

  virtual void
  update_property_int (const VideoCorrectProp::raw_ptr info) override
  {
    prop_   = *info;
    update_ = true;
    return;
  }

  virtual bool
  process_int (
    syn::IVideoBuf::raw_ptr h16s, 
    syn::IVideoBuf::raw_ptr s16s, 
    syn::IVideoBuf::raw_ptr l16s) override
  {
    // Вся работа идет аппаратно.
    return false;
  }

  mutable bool     update_;   //< 
  VideoCorrectProp prop_;     //< 
};
}   // namespace dlls::sources::v4l2_vgen::camera
#endif
