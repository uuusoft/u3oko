/**
\file       graph-local-int-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_icore_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "graph.hpp"
#include "mmedia/libs/helpers/statistic/helpers/expanded-times-helpers.hpp"

namespace libs::icore::impl::var1::graph
{
void
Graph::clear_impl ()
{
  id2data_graph_objs_.clear ();
  refresh_id_objs_impl ();
}


void
Graph::connect_impl (const ::pugi::xml_named_node_iterator& ipt)
{
  pugi::xml_attribute left     = ipt->attribute ("left_obj");
  pugi::xml_attribute right    = ipt->attribute ("right_obj");
  pugi::xml_attribute left_pt  = ipt->attribute ("left_pt");
  pugi::xml_attribute right_pt = ipt->attribute ("right_pt");

  U3_CHECK (left.as_string () && right.as_string (), "invalid connect obj");
  U3_CHECK (left_pt.as_string () && right_pt.as_string (), "invalid connect point");

  const auto it_left = id2data_graph_objs_.find (syn::NodeID (std::string (left.as_string ())));

  U3_CHECK (id2data_graph_objs_.end () != it_left, "find left obj for connect" + TOLOG (left.as_string ()));

  const auto it_right = id2data_graph_objs_.find (syn::NodeID (std::string (right.as_string ())));

  U3_CHECK (id2data_graph_objs_.end () != it_right, "find right obj for connect: " + std::string (right.as_string ()));
  U3_CHECK (it_left != it_right, "left obj equal right obj " + std::string (right.as_string ()));

  it_left->second->connect (left_pt.as_int (), it_right->second, right_pt.as_int ());
}


void
Graph::deb_load_objs_impl ()
{
  const auto& idata_source = ::libs::helpers::uids::minor::get (::libs::helpers::uids::minor::id_val::idata_source);
  for (const auto& obj : id2data_graph_objs_)
  {
    if (obj.second->query (idata_source))
    {
      interf_objs_[graph::consts::indx_source_interf_helper][source_interf_objs_[graph::consts::indx_source_interf_helper]] = obj.second;
      source_interf_objs_[graph::consts::indx_source_interf_helper]++;
    }
  }
}


void
Graph::load_impl (const ::pugi::xml_named_node_iterator& root)
{
  clear_impl ();

  U3_CHECK (std::string ("path") == std::string (root->name ()), std::string ("root = " + std::string (root->name ())).c_str ());
  //  load objs
  ::pugi::xml_object_range< ::pugi::xml_named_node_iterator > range_nodes = root->children ("node");
  ::pugi::xml_named_node_iterator                             node        = range_nodes.begin ();

  while (node != range_nodes.end ())
  {
    const char*               raw_id_obj = node->attribute ("id").as_string ();
    const char*               dll_name   = node->attribute ("name").as_string ();
    const auto                id_obj     = syn::NodeID (std::string (raw_id_obj ? raw_id_obj : "???"), dll_name);
    graph_obj_type::ptr       new_obj    = std::make_shared< ::libs::icore::impl::var1::obj::ObjGraph > (this, id_obj, logger_, exptimes_);
    const pugi::xml_attribute attr       = node->attribute ("name");
    const std::string         name_node  = attr.empty () ? "null" : attr.as_string ();

    U3_CHECK (new_obj, std::string ("null obj ") + TOLOG (name_node));

    new_obj->load (node);

    U3_CHECK (id_obj.check (), "null id obj");
    U3_CHECK (id2data_graph_objs_.end () == id2data_graph_objs_.find (id_obj), "double id obj in one graph");

    id2data_graph_objs_.insert (std::pair< syn::NodeID, graph_obj_type::ptr > (id_obj, new_obj));
    ++node;
  }

  //  load graph and connect objs
  auto range_pts = root->children ("point");
  auto ipt       = range_pts.begin ();

  while (ipt != range_pts.end ())
  {
    connect_impl (ipt);
    ++ipt;
  }

  //  applay property
  deb_load_objs_impl ();
  refresh_id_objs_impl ();
}


void
Graph::change_objs_state_impl (const obj::FilterRuns& new_state)
{
  //  Циклы оповещения объектов о изменении состоянии запуска графа.
  //  Первая итерация - изменяем состояние объектов-источников.
  //  Вторая итерация - всех остальных объектов.
  for (std::size_t indx_type = 0; indx_type < 2; ++indx_type)
  {
    for (const auto& obj : id2data_graph_objs_)
    {
      if (!obj.second)
      {
        continue;
      }

      const auto& idata_source = ::libs::helpers::uids::minor::get (::libs::helpers::uids::minor::id_val::idata_source);
      auto        bsource      = obj.second->query (idata_source);
      if (((1 == indx_type) && bsource) || ((0 == indx_type) && !bsource))
      {
        continue;
      }

      switch (new_state)
      {
      case obj::FilterRuns::stop:
        obj.second->stop ();
        break;
      case obj::FilterRuns::run:
        obj.second->run ();
        break;
      case obj::FilterRuns::pause:
        obj.second->stop ();
        break;
      case obj::FilterRuns::unknown:
        U3_LOG_DATA_ERROR ("recive unknown graph state");
        break;
      default:
        U3_LOG_DATA_ERROR ("unknown graph state" + VTOLOG (U3_CAST_UINT32_FORCE (new_state)));
        break;
      }
    }
  }

  {
    auto link2appl = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
    //  Сохраняем статистику использования процессора/памяти/etc каждым объектом в графе в данном сеансе работы графа.
    //  Данная статистика с точностью до конкретного узла в графе. Сам узел может зависеть от многих алгоритмов.
    ::libs::helpers::statistic::helpers::functors::dump (expand_objs_time_, link2appl);
    ::libs::helpers::statistic::helpers::functors::dump (exptimes_, link2appl);
    //  и сбрасываем статистики для нового сеанса.
    expand_objs_time_.clear ();
    exptimes_.clear ();
  }
  //  Делаем о же самое для статистик рабочих потоков.
  //  Рабочие потоки владеют информацией о времени выполения с точностью до алгоритма.
  {
    auto threads   = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
    auto link2appl = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();

    if (!threads)
    {
      U3_LOG_DATA_ERROR ("empty threads for data graph");
      return;
    }

#if 0
    U3_CHECK (
      threads->visit_with (
        [this, link2appl] (syn::ExpandedTimes& obj)
        {
          syn::ExpandedTimes::infos_type infos;
          obj.get (infos);

          for (const std::string& info : infos)
          {
            U~3_MSG2LOGGER (link2appl, info, ::libs::ilink::consts::id_data, ::libs::ievents::props::modules::log::LogLevels::info);
          }

          return true;
        }),
      "dump thread statistic");

    U3_CHECK (
      threads->visit_with (
        [this] (syn::ExpandedTimes& obj)
        {
          obj.clear ();
          return true;
        }),
      "work with statistic");
#endif
  }
}


void
Graph::recive_special_event_impl (const events::IEvent::ptr& evnt)
{
#if 0
  if (auto hardevnt = ::libs::iproperties::helpers::cast_event< ::libs::ievents::props::hardware::InfoCPUEvent > (evnt))
  {
    auto threads = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
    threads->set_count_threads (::libs::optim::mcalls::get_count_work_threads_by_count_cpu (hardevnt->get_cpu_count ()));
    //threads->set_cpu (hardevnt->get_cpu_type ());
    return;
  }
#endif
  if (auto startevnt = ::libs::iproperties::helpers::cast_event< ::libs::ievents::runtime::state::ChangeStateProcessEvent > (evnt))
  {
    state_ = startevnt->is_start () ? obj::FilterRuns::run : obj::FilterRuns::stop;
    change_objs_state_impl (state_);
    return;
  }

  if (auto startevnt = ::libs::iproperties::helpers::cast_event< ::libs::ievents::runtime::state::ExpandTimesEvent > (evnt))
  {
    syn::ExpandedTimes::storages_type alg_info;
    syn::ExpandedTimes::storages_type info;

    exptimes_.visit_with (
      [&alg_info] (const syn::ExpandedTimes::storages_type& vals) {
        alg_info = vals;
      });

    expand_objs_time_.visit_with (
      [&info] (const syn::ExpandedTimes::storages_type& vals) {
        info = vals;
      });

    ::libs::helpers::statistic::merge (alg_info, info);
    startevnt->set_stat (data_graph_folder_, info);
  }
}


Graph::graph_obj_type::weak_ptr
Graph::get_obj_impl (const syn::NodeID& obj_id)
{
  auto it = id2data_graph_objs_.find (obj_id);
  if (id2data_graph_objs_.end () != it)
  {
    return graph_obj_type::weak_ptr (it->second);
  }
  U3_XLOG_ERROR ("find graph by id" + TOLOG (obj_id.get_name ()));
  return graph_obj_type::weak_ptr ();
}


void
Graph::refresh_id_objs_impl () const
{
  data_graph_obj_ids_.clear ();

  for (const auto& obj : id2data_graph_objs_)
  {
    data_graph_obj_ids_.insert (obj.first);
  }
}
}   // namespace libs::icore::impl::var1::graph
