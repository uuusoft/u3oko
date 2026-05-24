#pragma once
/**
\file       system-android-property.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/
#if defined(U3_OS_ANDROID)

#  include <android_native_app_glue.h>
#  include <jni.h>
#  include <android/log.h>
#  include <android/asset_manager.h>
#  include <android/asset_manager_jni.h>
#  include "isystem-property.hpp"

namespace libs::iproperties::vers::system
{
// syn
using gui_func_type = bool (android_app*, android_poll_source*);

class SystemAndroidProperty final : public ::libs::properties::ISharedProperty
{
  public:
  //  ext types
  using gui_functor_type = boost::function< gui_func_type >;
  using IVideoBuf        = ::utils::dbufs::video::IVideoBuf;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SystemAndroidProperty)

  SystemAndroidProperty () :
    pappl_ (nullptr)
  {
    work_cycle_ = false;
  }

  virtual ~SystemAndroidProperty ()
  {
  }

  android_app*
  get_aappl_lockfree ()
  {
    return pappl_;
  }

  void
  set_aappl_lockfree (android_app* pappl)
  {
    pappl_ = pappl;
  }

  syn::VideoDriverCaptureProp::craw_ptr
  get_capture_props_lockfree ()
  {
    return capture_props_;
  }

  void
  set_capture_props_lockfree (syn::VideoDriverCaptureProp::craw_ptr capture_props)
  {
    capture_props_ = capture_props;
  }

  ::utils::dbufs::video::IVideoBuf::ptr
  get_buf_lockfree ()
  {
    return buf_java2cpp_;
  }

  void
  set_buf_lockfree (::utils::dbufs::video::IVideoBuf::ptr buf)
  {
    buf_java2cpp_ = buf;
  }

  boost::function< gui_func_type >
  get_func_gui_lockfree ()
  {
    return pfunc_gui_;
  }

  void
  set_func_gui_lockfree (boost::function< gui_func_type > funct)
  {
    pfunc_gui_ = funct;
  }

  std::atomic_bool work_cycle_;   //<

  private:
  virtual bool
  self_test_int () const override
  {
    U3_ASSERT (pappl_);
    return !pappl_ ? false : true;
  }

  virtual void*
  cast2top_int () override
  {
    return this;
  }

  std::atomic< android_app* >                          pappl_;           //<
  std::atomic< syn::VideoDriverCaptureProp::craw_ptr > capture_props_;   //<
  ::utils::dbufs::video::IVideoBuf::ptr                buf_java2cpp_;    //<
  gui_functor_type                                     pfunc_gui_;       //<
};
}   // namespace libs::iproperties::vers::system

#endif
