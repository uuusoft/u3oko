#pragma once
/**
\file       icapture-image.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.08.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::interf::interfaces
{
class ICaptureImage : public IBaseRuntimeInterf
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (ICaptureImage)

  virtual ~ICaptureImage () = default;

  void
  change_state (bool enable)
  {
    change_state_int (enable);
  }

  void
  update_capture_property (const syn::VideoDriverCaptureProp::raw_ptr info)
  {
    update_capture_property_int (info);
  }

  void
  update_driver_property (const syn::VideoDriverProp::raw_ptr info)
  {
    update_driver_property_int (info);
  }

  void
  update_system_specific_property (const syn::SystemSpecificDriverProp::raw_ptr info)
  {
    update_system_specific_property_int (info);
  }

  protected:
  ICaptureImage () = default;

  private:
  //  ICaptureImage interface
  virtual void change_state_int (bool enable)                                                          = 0;
  virtual void update_capture_property_int (const syn::VideoDriverCaptureProp::raw_ptr info)           = 0;
  virtual void update_driver_property_int (const syn::VideoDriverProp::raw_ptr info)                   = 0;
  virtual void update_system_specific_property_int (const syn::SystemSpecificDriverProp::raw_ptr info) = 0;
};
}   // namespace libs::events_base::runtime::interf::interfaces
