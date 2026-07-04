/**
\file       gen-vgen-info-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "gen-vgen-includes_int.hpp"
#include "gen-vgen-info-filter-dll.hpp"

namespace dlls::sources::gen_vgen
{
InfoFilter::InfoFilter () :
  rprops_ (::libs::iproperties::helpers::create_event_in_list< syn::VideoDriverProp > (ef_props_)),
  capture_props_ (::libs::iproperties::helpers::create_event_in_list< syn::VideoDriverCaptureProp > (ef_props_)),
  system_props_ (::libs::iproperties::helpers::create_event_in_list< syn::SystemSpecificDriverProp > (ef_props_))
{
  // EAI-REFACT
  str2props_.insert (str2prop_type::value_type (ef_props_.front ()->get_mid (), rprops_));
  str2props_.insert (str2prop_type::value_type ((*std::next (ef_props_.begin (), 1))->get_mid (), capture_props_));
  str2props_.insert (str2prop_type::value_type ((*std::next (ef_props_.begin (), 2))->get_mid (), system_props_));

  str2props_.insert (str2prop_type::value_type (links_props_.get_mid (), &links_props_));
}


InfoFilter::~InfoFilter ()
{
  try
  {
    if (recv_thread_)
    {
      {
        std::unique_lock< InfoFilter::sync_type > lock (wdmtx_, consts::ms_wait_capture_device);
        if (lock.owns_lock ())
        {
          stop_req_ = true;
        }
        else
        {
          U3_LOG_DATA_ERROR ("force stop, failed acquired mutex" + VTOLOG (consts::ms_wait_capture_device.count ()) + "ms");
          stop_req_ = true;
        }
      }

      recv_thread_->join ();
      recv_thread_.reset ();
    }
    //  останавливаем процесс приема данных по сети, удаляем объект для приема данных, удаляем все буфера с данными
    proxy2hardware_.clear ();
  }
  catch (boost::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (boost::diagnostic_information (excpt));
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
  }
  catch (...)
  {
    U3_LOG_DATA_EXCEPT ("unknown");
  }
}


void
InfoFilter::sync_int (bool force)
{
  if (synced_ && !force)
  {
    return;
  }
  // U3-REFACT
  if (auto impl = capture_impl_.lock ())
  {
    impl->update_capture_property (capture_props_);
    impl->update_driver_property (rprops_);
    impl->update_system_specific_property (system_props_);
  }

  capture_fps_.set_fps (capture_props_->capi_.fps_);
  synced_ = true;
}


auto
InfoFilter::load_int (const ::pugi::xml_named_node_iterator& node) -> bool
{
  synced_ = false;
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // U3-REFACT
  if (auto impl = capture_impl_.lock ())
  {
    U3_LOG_DATA_DBG ("sync_int:update properties");
    impl->update_capture_property (capture_props_);
    impl->update_driver_property (rprops_);
    impl->update_system_specific_property (system_props_);
  }

  capture_fps_.set_fps (capture_props_->capi_.fps_);
#endif
  return super::load_int (node);
}
}   // namespace dlls::sources::gen_vgen
