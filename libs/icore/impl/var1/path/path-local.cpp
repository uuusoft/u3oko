//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       path-local.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "mmedia/modules/uuu_log/appl/thread/exception-logger.hpp"
#include "../includes.hpp"
#include "path.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {
//  syn
using ::libs::iproperties::vers::system::ISystemProperty;
using ::libs::properties::ISharedProperty;
using ExceptionLogger = ::modules::uuu_log::appl::thread::ExceptionLogger<::libs::link::ILink::ptr>;

Path::Path () :
  count_process_frames_ (0),
  req_terminate_thread_ (false),
  state_ (obj::RunStateFilter::stop)
{
  guard_type                  _grd (ctrl_mtx_);
  ISystemProperty::raw_ptr    _orinfo = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  ISharedProperty::guard_type _guard (_orinfo->get_sync ());

  source_interf_objs_.fill (0);

  std::for_each (
    interf_objs_.begin (),
    interf_objs_.end (),
    [](array_interf_type& _obj) {
      _obj.fill (path_obj_type::ptr ());
      return;
    });

  //  создаем поток в котором будет происходить обработка данных
  data_thread_.reset (
    new std::thread (
      ::libs::helpers::thread::generic_thread_funct<Path, ExceptionLogger>,
      this,
      ExceptionLogger (::libs::link::ILink::ptr ()),
      UUU_ICAST_USHORT (0)));
  return;
}


Path::~Path ()
{
  try
    {
      //  выставляем флаг требование рабочему потока - завершить работу
      {
        guard_type _grd (ctrl_mtx_);
        state_ = obj::RunStateFilter::stop;
        change_objs_state_impl (state_);
        req_terminate_thread_ = true;
      }
      //  ждем, останавливаем поток данных
      UASSERT ((*data_thread_).joinable ());
      (*data_thread_).join ();
      data_thread_.reset (nullptr);
    }
  catch (std::exception& _e)
    {
      MSG2LOGGER (logger_.lock (), _e.what (), "uuu_mdata");
      UASSERT_SIGNAL ("failed");
    }
  return;
}

}}}}}      // namespace libs::icore::impl::var1::path
