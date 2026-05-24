/**
\file       graph-local.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "mmedia/libs/helpers/thread/generic-thread-func.hpp"
#include "graph.hpp"

namespace libs::icore::impl::var1::graph
{
Graph::Graph () :
  count_process_frames_ (0),
  req_terminate_thread_ (false),
  state_ (obj::FilterRuns::stop),
  live_ext_requests_ (0)
{
  auto             orinfo = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  std::scoped_lock locks (ctrl_graph_mtx_, orinfo->get_sync ());

  source_interf_objs_.fill (0);

  std::for_each (
    interf_objs_.begin (),
    interf_objs_.end (),
    [] (array_interf_type& obj) {
      obj.fill (graph_obj_type::ptr ());
      return;
    });

  //  создаем поток в котором будет происходить обработка данных
  data_thread_.reset (
    new std::thread (
      ::libs::helpers::thread::generic_thread_funct< Graph, libs::properties::vers::links::mids::mdata2appl >,
      this,
      0u));
}


Graph::~Graph ()
{
  try
  {
    //  выставляем флаг требование рабочему потока - завершить работу
    {
      U3_XLOG_DBG ("Graph::~Graph::ctrl_graph_mtx_" + PTR_TOLOG (this));
      lock_type lock (ctrl_graph_mtx_);
      state_ = obj::FilterRuns::stop;
      change_objs_state_impl (state_);
      req_terminate_thread_ = true;
    }
    //  ждем, останавливаем поток данных
    U3_ASSERT ((*data_thread_).joinable ());
    (*data_thread_).join ();
    data_thread_.reset (nullptr);
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
    // U3_MSG2LOGGER (logger_.lock (), e.what (), "u3m_mdata", "wtfversion", ::libs::ievents::props::modules::log::LogLevels::info);
  }
}
}   // namespace libs::icore::impl::var1::graph
