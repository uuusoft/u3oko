/**
\file       graph-local-thread-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_icore_lib
*/
#define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "graph.hpp"
#include "mmedia/libs/helpers/statistic/helpers/expanded-times-helpers.hpp"

namespace libs::icore::impl::var1::graph
{
void
Graph::thread_func_impl (std::uint32_t indx_thread)
{
  ::libs::helpers::thread::set_thread_priority (std::this_thread::get_id (), ::libs::helpers::thread::Priorities::below_normal);

  bool          working                 = true;
  std::uint64_t frames_no_sleep         = 0;
  bool          sleep_now               = false;
  std::uint64_t ms_sleep                = graph::consts::ms_sleep_work_thread_soft;
  std::uint64_t count_live_ext_requests = 0;   // Счетчик итераций, которые прошли при взведенном флаге на обработку внешнего сообщения

  do
  {
    bool complite_buf = false;

    ms_sleep  = 0;
    sleep_now = false;

    const auto counter_external_requests = live_ext_requests_.load ();
    if (counter_external_requests <= 0 || 0 == count_live_ext_requests)
    {
      lock_type lock (ctrl_graph_mtx_);
      count_live_ext_requests = counter_external_requests > 0 ? 1 : 0;
      working                 = req_terminate_thread_ ? false : true;
      complite_buf            = data_graph_process_impl ();
    }
    else
    {
      ++count_live_ext_requests;

      sleep_now = true;
      ms_sleep  = ::libs::icore::impl::var1::graph::consts::ms_add_sleep_work_thread_by_external_request * count_live_ext_requests;
      ms_sleep  = std::min< std::uint64_t > (::libs::icore::impl::var1::graph::consts::ms_max_add_sleep_work_thread_by_external_request, ms_sleep);
      U3_LOG_DATA_MARK ("external request processing => waiting cycle {" + std::to_string (counter_external_requests) + "|" + std::to_string (count_live_ext_requests) + "|+" + std::to_string (ms_sleep) + "ms}");
    }

    if (!working)
    {
      break;
    }

    //  Если мы не обработали не одного буфера или превышено ммаксимальное количество обработанных буферов без засыпания - засыпаем.
    //  избегаем возможного замедления других подсистем на одноядерной машине.
    if (!complite_buf)
    {
      sleep_now = true;
      ms_sleep += graph::consts::ms_sleep_work_thread_soft;
    }
    else
    {
      ++frames_no_sleep;
    }

    if (frames_no_sleep > graph::consts::max_count_frames_without_sleep)
    {
      sleep_now = true;
      ms_sleep += ::libs::icore::impl::var1::graph::consts::ms_sleep_work_thread_force;
    }

#if 0
    // debug
    working   = true;
    sleep_now = false;
    //ms_sleep  = 30000;
#endif

    if (sleep_now)
    {
      U3_LOG_DATA_TIMING ("graph thread sleep" + VTOLOG (ms_sleep));
      std::this_thread::sleep_for (std::chrono::milliseconds (ms_sleep));
      // std::this_thread::yield ();
      frames_no_sleep = 0;
    }
  } while (true);
}


void
Graph::thread_postfunc_impl (std::uint32_t indx_thread)
{
}


bool
Graph::data_graph_process_impl ()
{
  if (obj::FilterRuns::run != state_)
  {
    return false;
  }
  if (!work_bufs_)
  {
    work_bufs_ = std::make_shared< ::libs::bufs::Bufs > ();
  }

  obj::dll::TransformInfo::tevents_type frame_events;   //< Список событий, которые произошли на данный момент при обработке данного фрейма (кадр, буфер) данных

  syn::IEvent::ptr    rmsg;
  bool                ret               = true;
  std::int64_t        count_filled_bufs = 0;
  const std::uint64_t count_source      = source_interf_objs_[graph::consts::indx_source_interf_helper];
  auto                dmsg              = ::libs::iproperties::helpers::create_event< syn::BufsEvent > (rmsg);

  dmsg->set_buf (work_bufs_);
  dmsg->set_events (&frame_events);

  for (std::uint32_t sindx = 0; sindx < count_source; ++sindx)
  {
    const auto& ssource = interf_objs_[graph::consts::indx_source_interf_helper];
    auto        source  = ssource[sindx].get ();
    auto        lsource = dynamic_cast< var1::obj::ObjGraph::raw_ptr > (source);
    //  Начинаем от объекта источника проходим по всем точкам соедининия и рекурсивно вызываем для каждого последующего
    //  фильтра функцию обработки
    work_bufs_->set_flag (::libs::bufs::BufsFlags::empty, true);

    {
      //  собираем статистику по источникам отдельно от статистики по остальным узлам
      syn::AddOpTime exp_stat (
        expand_objs_time_,
        ::libs::core::graph::get_ext_graph_node_id (lsource->info_.id_obj_),
        "");

      {
        ::libs::helpers::time::Timer timer;
        source->send_event2me (rmsg);
        const auto working_time = timer.get_time ().count ();
        if (working_time >= consts::ms_max_working_time_per_node_graph)
        {
          U3_LOG_DATA_WRN ("source exceeded the working time limit " + VTOLOG (working_time) + VTOLOG (consts::ms_max_working_time_per_node_graph));
        }
      }

      if (!work_bufs_->get_flag (::libs::bufs::BufsFlags::empty))
      {
        ++count_filled_bufs;
      }
      else
      {
        // exp_stat.change_last_name (lsource->lib_name_ + ".empty");
        exp_stat.set_skip ();
      }
    }

    if (!work_bufs_->get_flag (::libs::bufs::BufsFlags::empty) || !frame_events.empty ())
    {
      //  Если есть заполненный буфер надо его обработать - вызывая рекурсивно функцию обработки для всей цепочки фильтров - получаем заполненный буфер данных.
      data_graph_work_func_impl (
        lsource,
        work_bufs_,
        lsource->info_.pts_.outs_[0].indx_pt_,
        &frame_events);

      //  Передаем связанные с данным кадром события (если они есть) в общую подсистему обработки событий.
      if (!frame_events.empty ())
      {
        auto ievents = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
        U3_ASSERT (ievents);

        for (auto& fevent : frame_events)
        {
          if (::libs::iproperties::helpers::cast_event< syn::BaseInterfEvent > (fevent))
          {
            //  Все интерфейсные сообщения являются локальными для данного графа обработки данных, их не нужно передавать в подсистему хранения событий
            continue;
          }

          syn::IEvent::ptr wrapper;
          auto             iwrapper = ::libs::iproperties::helpers::create_event< ::libs::ievents_events::events::WrapperEventsEvent > (wrapper);

          iwrapper->set_msg (fevent);
          ievents->send_msg (
            wrapper,
            ::libs::link::details::CallSyncs::async,
            ::libs::link::details::Calls::set);
        }

        frame_events.clear ();
      }
    }

  }   // end for

  count_process_frames_ += count_filled_bufs;
  return count_filled_bufs ? ret : false;
}


void
Graph::data_graph_work_func_impl (
  var1::obj::ObjGraph::raw_ptr           pfilter,
  ::libs::bufs::Bufs::ptr&               ibufs,
  const std::uint32_t                    iindx,
  obj::dll::TransformInfo::tevents_type* frame_events)
{
  if (!pfilter)
  {
    //  Допустимая ситуация, конечный фильтр не имеет последующего, что очевидно.
    return;
  }

  try
  {
    const auto& finfo = pfilter->get_info ();
    //  Проходим по всем выходным точкам данного фильтра и для каждого фильтра связанного с ней вызываем рекурcивно данную функцию
    //  Точек может и не быть, но один раз выполнять работу мы должны в любом случае.
    const std::int32_t count_outs = finfo.pts_.count_outs_;
    for (int oindx = 0; oindx < count_outs; ++oindx)
    {
      const auto& out_pt = finfo.pts_.outs_[oindx];
      if (!out_pt.active_)
      {
        continue;
      }

      //  По умолчанию вход совпадает с выходом, вся обработка ведется на месте. Это поведение может быть изменено фильтром.
      ::libs::bufs::Bufs::ptr obufs = ibufs;

      {
        // Вызываем функцию преобразования для данного фильтра при этом фильтр должен сформировать таблицу флагов, указывающих
        // по каким соединенным выходным точкам следует пересылать данные
        obj::dll::TransformInfo cinfo (&ibufs, &obufs, 0, iindx, oindx, frame_events, exptimes_);
        syn::AddOpTime          exp_stat (expand_objs_time_, ::libs::core::graph::get_ext_graph_node_id (pfilter->info_.id_obj_), "");

        // debug
        // ::libs::bufs::dump (ibufs.get ());
        // if (frame_events)
        // {
        //  U3_LOG_DATA_DBG (FVTOLOG (U3_CAST_PTR2INT (frame_events)) + VTOLOG (frame_events->size ()) + TOLOG (pfilter->lib_name_));
        // }
        {
          ::libs::helpers::time::Timer timer;
          pfilter->transform (cinfo);
          const auto working_time = timer.get_time ().count ();
          if (working_time >= consts::ms_max_working_time_per_node_graph)
          {
            U3_LOG_DATA_WRN ("filter " + pfilter->lib_name_ + " exceeded the working time limit working_time:" + std::to_string (working_time) + " ms_max_working_time_per_node_graph=" + std::to_string (consts::ms_max_working_time_per_node_graph));
          }
        }
      }

      if (oindx < count_outs)
      {
        data_graph_work_func_impl (out_pt.filter_, obufs, out_pt.indx_pt_, frame_events);
      }
    }
  }
  catch (boost::interprocess::interprocess_exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
  catch (boost::exception& e)
  {
    U3_LOG_DATA_EXCEPT (boost::diagnostic_information (e));
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }
  catch (...)
  {
    U3_LOG_DATA_EXCEPT ("...");
  }
}
}   // namespace libs::icore::impl::var1::graph
