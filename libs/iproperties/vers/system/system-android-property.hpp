#pragma once
/**
\file       system-android-property.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief    
*/
#if defined(UUU_OS_ANDROID)

#include <android_native_app_glue.h>
#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "isystem-property.hpp"

namespace libs { namespace iproperties { namespace vers { namespace system {
// syn
using gui_funct_type = bool(android_app*, android_poll_source*);
/**
\brief  empty brief
*/
class SystemAndroidProperty final : public ::libs::properties::ISharedProperty
{
  public:
  //  ext types
  using gui_functor_type = boost::function<gui_funct_type>;
  using IVideoBuff       = ::utils::dbuffs::video::IVideoBuff;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (SystemAndroidProperty);

  SystemAndroidProperty () :
    pappl_ (nullptr)
  {
    XULOG_TRACE ("SystemAndroidProperty::SystemAndroidProperty");
    work_cycle_ = false;
  }

  virtual ~SystemAndroidProperty ()
  {
    XULOG_TRACE ("SystemAndroidProperty::~SystemAndroidProperty");
  }

  android_app*
  get_aappl_lockfree ()
  {
    return pappl_;
  }

  void
  set_aappl_lockfree (android_app* _pappl)
  {
    pappl_ = _pappl;
    return;
  }

  ::utils::dbuffs::video::IVideoBuff::ptr
  get_buff_lockfree ()
  {
    return buff_java2cpp_;
  }

  void
  set_buff_lockfree (::utils::dbuffs::video::IVideoBuff::ptr _buff)
  {
    buff_java2cpp_ = _buff;
    return;
  }

  boost::function<gui_funct_type>
  get_funct_gui_lockfree ()
  {
    return pfunct_gui_;
  }

  void
  set_funct_gui_lockfree (boost::function<gui_funct_type> _funct)
  {
    pfunct_gui_ = _funct;
    return;
  }

  std::atomic_bool work_cycle_;      //< ???


  private:
  virtual bool
  self_test_int () const override
  {
    UASSERT (pappl_);
    return !pappl_ ? false : true;
  }

  virtual void*
  cast2top_int () override
  {
    return this;
  }

  android_app*     pappl_;              //< пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ++ пїЅ android/
  gui_functor_type pfunct_gui_;         //< ???
  IVideoBuff::ptr  buff_java2cpp_;      //< пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ java пїЅ пїЅ++.
};

}}}}      // namespace libs::iproperties::vers::system

#endif
