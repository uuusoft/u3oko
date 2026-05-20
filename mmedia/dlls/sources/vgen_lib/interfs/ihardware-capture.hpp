#pragma once
/**
\file       ihardware-capture.hpp
\author     Erashov Anton erashov2026@proton.me
\date       15.03.2022
\project    u3_vgen_lib
*/

namespace dlls::sources::gen_lib::interfs
{
class IHardwareCapture final : public syn::ICaptureImage
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IHardwareCapture)

  IHardwareCapture () :
    update_ (false)
  {
  }

  virtual ~IHardwareCapture ()
  {
  }

  bool
  is_capture_property_update () const
  {
    return update_;
  }

  syn::VideoDriverCaptureProp::craw_ptr
  get_capture_property () const
  {
    update_ = false;
    return &capture_;
  }

  syn::VideoDriverProp::craw_ptr
  get_driver_property () const
  {
    update_ = false;
    return &vdriver_;
  }

  syn::SystemSpecificDriverProp::craw_ptr
  get_system_specific_property () const
  {
    update_ = false;
    return &system_specific_;
  }

  private:
  virtual void
  change_state_int (bool enable) override
  {
  }

  virtual void
  update_capture_property_int (const syn::VideoDriverCaptureProp::raw_ptr info) override
  {
    U3_LOG_DATA_DATA ("update prop:" + syn::VideoDriverCaptureProp::gen_get_mid ());
    capture_.copy (info);
    update_ = true;
  }

  virtual void
  update_driver_property_int (const syn::VideoDriverProp::raw_ptr info) override
  {
    U3_LOG_DATA_DATA ("update prop:" + syn::VideoDriverProp::gen_get_mid ());
    vdriver_.copy (info);
    update_ = true;
  }

  virtual void
  update_system_specific_property_int (const syn::SystemSpecificDriverProp::raw_ptr info) override
  {
    U3_LOG_DATA_DATA ("update prop:" + syn::SystemSpecificDriverProp::gen_get_mid ());
    system_specific_.copy (info);
    update_ = true;
  }

  mutable bool                  update_;            //<
  syn::VideoDriverCaptureProp   capture_;           //<
  syn::VideoDriverProp          vdriver_;           //<
  syn::SystemSpecificDriverProp system_specific_;   //<
};
}   // namespace dlls::sources::gen_lib::interfs
