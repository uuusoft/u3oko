#pragma once
/**
\file       icapture-image-null-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.08.2018
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen
{
class ICaptureImageNullImpl final : public ::libs::ievents::runtime::interf::interfaces::ICaptureImage
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ICaptureImageNullImpl)

  ICaptureImageNullImpl ()
  {
  }

  virtual ~ICaptureImageNullImpl ()
  {
  }

  private:
  virtual void
  change_state_int (U3_MARK_UNUSED bool enable) override
  {
  }

  virtual void
  update_capture_property_int (const syn::VideoDriverCaptureProp::raw_ptr) override
  {
    U3_LOG_DATA_DATA ("skip update_capture_property_int - VideoDriverCaptureProp");
  }

  virtual void
  update_driver_property_int (const syn::VideoDriverProp::raw_ptr) override
  {
    U3_LOG_DATA_DATA ("skip update_driver_property_int - VideoDriverProp");
  }

  virtual void
  update_system_specific_property_int (const syn::SystemSpecificDriverProp::raw_ptr) override
  {
    U3_LOG_DATA_DATA ("skip update_system_specific_property_int - SystemSpecificDriverProp");
  }
};
}   // namespace dlls::sources::gen_vgen
