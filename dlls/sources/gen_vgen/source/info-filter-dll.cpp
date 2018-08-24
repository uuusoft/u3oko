//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"

namespace dlls { namespace sources { namespace gen_vgen {

InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  null_impl_ (std::make_shared<ICaptureImageNullImpl> ()),
  sync_ok_ (false),
  active_impl_ (null_impl_)
{
  init ();
}


InfoFilter::~InfoFilter ()
{
  try
    {
      if (recv_thread_)
        {
          {
            std::lock_guard<std::mutex> _grd (src_mtx_);
            stop_recv_ = true;
          }

          recv_thread_->join ();
          recv_thread_.reset ();
        }
      //  останавливаем процесс приема данных по сети, удаляем объект для приема данных
      //  удаляем все буфера с данными
      rdriver_.clear ();
    }
  catch (boost::exception& _e)
    {
      XULOG_FATAL ("gen_vgen, uuu_exception, " << boost::diagnostic_information (_e));
      DATA_EXCEPT_LOG (boost::diagnostic_information (_e));
    }
  catch (std::exception& _e)
    {
      XULOG_FATAL ("gen_vgen, uuu_exception, " << _e.what ());
      DATA_EXCEPT_LOG (_e.what ());
    }
  catch (...)
    {
      XULOG_FATAL ("gen_vgen, uuu_exception, unknown");
    }
  return;
}


void
InfoFilter::init ()
{
  sync_ok_   = false;
  stop_recv_ = false;
  rprops_    = ::libs::iproperties::helpers::get_and_cast_event<props_type> (props_);

  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));
  str2props_.insert (str2prop_type::value_type (capture_props_.get_mid (), &capture_props_));
  str2props_.insert (str2prop_type::value_type (links_props_.get_mid (), &links_props_));
  return;
}


void
InfoFilter::sync_int (bool _force)
{
  if (sync_ok_ && !_force)
    {
      return;
    }
  if (auto _impl = active_impl_.lock ())
    {
      _impl->update_property (&capture_props_);
    }
  sync_ok_ = true;
  return;
}


bool
InfoFilter::load_int (const base_functs::xml::itn& _node)
{
  sync_ok_ = false;
  return super::load_int (_node);
}

}}}      // namespace dlls::sources::gen_vgen
