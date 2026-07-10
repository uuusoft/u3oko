#pragma once
/**
\file       ihardware-correct.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_vgen_lib
*/

namespace dlls::sources::gen_lib::interfs
{
class IHardwareCorrect final : public syn::ICorrectImage
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (IHardwareCorrect)

  IHardwareCorrect ()          = default;
  virtual ~IHardwareCorrect () = default;

  bool
  is_correction_property_update () const
  {
    return update_;
  }

  syn::VideoCorrectProp::craw_ptr
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
  }

  virtual void
  update_correction_property_int (const syn::VideoCorrectProp::raw_ptr info) override
  {
    U3_LOG_DATA_DBG ("update prop:" + STOLOG (syn::VideoCorrectProp::gen_get_mid ()));
    prop_.copy (info);
    update_ = true;
  }

  virtual bool
  process_int (syn::IVideoBuf::raw_ptr h16, syn::IVideoBuf::raw_ptr s16, syn::IVideoBuf::raw_ptr l16) override
  {
    // Вся работа идет аппаратно.
    return false;
  }

  mutable bool          update_ = false;   //< Флаг-признак изменения данных в свойствах
  syn::VideoCorrectProp prop_;             //<
};
}   // namespace dlls::sources::gen_lib::interfs
