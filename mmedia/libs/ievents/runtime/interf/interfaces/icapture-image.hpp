#pragma once
/**
\file       icapture-image.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.08.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf::interfaces
{
class ICaptureImage : public IBaseRuntimeInterf
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ICaptureImage)

  virtual ~ICaptureImage ()
  {
  }

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
  ICaptureImage ()
  {
  }

  private:
  //  ICaptureImage interface
  virtual void change_state_int (bool enable)                                                          = 0;
  virtual void update_capture_property_int (const syn::VideoDriverCaptureProp::raw_ptr info)           = 0;
  virtual void update_driver_property_int (const syn::VideoDriverProp::raw_ptr info)                   = 0;
  virtual void update_system_specific_property_int (const syn::SystemSpecificDriverProp::raw_ptr info) = 0;
};
}   // namespace libs::ievents::runtime::interf::interfaces
