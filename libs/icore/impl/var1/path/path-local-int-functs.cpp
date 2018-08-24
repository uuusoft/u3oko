//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       path-local-int-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "../includes.hpp"
#include "path.hpp"
#include "mmedia/libs/helpers/statistic/helpers/functors_with_statistic.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {
//  syn
using ::libs::helpers::statistic::helpers::functors::TStatLogger;
using ::libs::helpers::statistic::helpers::functors::TStatReset;

void
Path::clear_impl ()
{
  id2obj_.clear ();
  refresh_id_objs_impl ();
  return;
}


void
Path::connect_impl (const base_functs::xml::itn& _ipt)
{
  pugi::xml_attribute _left     = _ipt->attribute ("left_obj");
  pugi::xml_attribute _right    = _ipt->attribute ("right_obj");
  pugi::xml_attribute _left_pt  = _ipt->attribute ("left_pt");
  pugi::xml_attribute _right_pt = _ipt->attribute ("right_pt");

  CHECK_STATE (_left.as_string () && _right.as_string (), "invalid connect obj");
  CHECK_STATE (_left_pt.as_string () && _right_pt.as_string (), "invalid connect point");

  const auto _it_left = id2obj_.find (PathObjID (std::string (_left.as_string ())));

  CHECK_STATE (id2obj_.end () != _it_left, "failed find left obj for connect" + std::string (_left.as_string ()));

  const auto _it_right = id2obj_.find (PathObjID (std::string (_right.as_string ())));

  CHECK_STATE (id2obj_.end () != _it_right, "failed find right obj for connect, " + std::string (_right.as_string ()));
  CHECK_STATE (_it_left != _it_right, "failed, left obj equal right obj");

  _it_left->second->connect (_left_pt.as_int (), _it_right->second, _right_pt.as_int ());
  return;
}


void
Path::deb_load_objs_impl ()
{
  for (const auto& _obj : id2obj_)
    {
      if (_obj.second->query (::libs::helpers::uids::interf::idata_source))
        {
          interf_objs_[path::consts::indx_source_interf_helper][source_interf_objs_[path::consts::indx_source_interf_helper]] = _obj.second;
          source_interf_objs_[path::consts::indx_source_interf_helper]++;
        }
    }

  return;
}


void
Path::load_impl (const base_functs::xml::itn& _root)
{
  XULOG_TRACE ("Path::load_impl, beg");
  clear_impl ();

  auto _iappl = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_appl_paths_lockfree ();

  CHECK_STATE (_iappl, "failed, empty application");
  CHECK_STATE (std::string ("path") == std::string (_root->name ()), std::string ("failed, root = " + std::string (_root->name ())).c_str ());

  //  load objs
  base_functs::xml::ritn _range_nodes = _root->children ("node");
  base_functs::xml::itn  _node        = _range_nodes.begin ();
  int                    _indx_node   = 0;

  while (_node != _range_nodes.end ())
    {
      const char*               _raw_id_obj = _node->attribute ("id").as_string ();
      const PathObjID           _id_obj     = PathObjID (std::string (_raw_id_obj ? _raw_id_obj : "???"));
      path_obj_type::ptr        _new_obj    = std::make_shared<::libs::icore::impl::var1::obj::ObjPath> (this, logger_);
      const pugi::xml_attribute _attr       = _node->attribute ("name");
      const std::string         _name_node  = _attr.empty () ? "null" : _attr.as_string ();

      XULOG_TRACE (_name_node.c_str ());
      CHECK_STATE (_new_obj, std::string ("failed, null obj ") << _name_node);
      _new_obj->load (_node);
      CHECK_STATE (_id_obj.check (), "failed, null id obj");
      CHECK_STATE (id2obj_.end () == id2obj_.find (_id_obj), "failed, double id obj in one path");

      id2obj_.insert (std::pair<PathObjID, path_obj_type::ptr> (_id_obj, _new_obj));

      ++_node;
      ++_indx_node;
    }

  XULOG_TRACE ("Path::load_impl, load ok");

  //  load graph and connect objs
  base_functs::xml::ritn _range_pts = _root->children ("point");
  base_functs::xml::itn  _ipt       = _range_pts.begin ();

  //CHECK_STATE( _range_pts.begin () != _range_pts.end (), "failed - empty connect points" );

  while (_ipt != _range_pts.end ())
    {
      connect_impl (_ipt);
      ++_ipt;
    }

  XULOG_TRACE ("Path::load_impl, connect ok");
  //  applay property
  deb_load_objs_impl ();
  XULOG_TRACE ("Path::load_impl, applay ok");
  refresh_id_objs_impl ();
  XULOG_TRACE ("Path::load_impl, end");
  return;
}


void
Path::change_objs_state_impl (const obj::RunStateFilter& _new_state)
{
  //  Циклы оповещения объектов о изменении состоянии запуска графа.
  //  Первая итерация - изменяем состояние объектов-источников.
  //  Вторая итерация - всех остальных объектов.
  for (std::size_t _indx_type = 0; _indx_type < 2; ++_indx_type)
    {
      for (const auto& _obj : id2obj_)
        {
          if (!_obj.second)
            {
              continue;
            }

          auto _bsource = _obj.second->query (::libs::helpers::uids::interf::idata_source);

          if (((1 == _indx_type) && _bsource) || ((0 == _indx_type) && !_bsource))
            {
              continue;
            }

          switch (_new_state)
            {
            case obj::RunStateFilter::stop:
              _obj.second->stop ();
              break;
            case obj::RunStateFilter::run:
              _obj.second->run ();
              break;
            default:
              UASSERT_SIGNAL ("failed");
              break;
            }
        }
    }
  //  Сохраняем статистику использования процессора/памяти/etc каждым объектом в графе в данном сеансе работы графа.
  //  Данная статистика с точностью до конкретного узла в графе. Сам узел может зависеть от многих алгоритмов.
  {
    auto _link2appl = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
    ::libs::helpers::statistic::helpers::functors::dump (expand_objs_time_, _link2appl);
    //  и сбрасываем статистику для нового сеанса.
    expand_objs_time_.clear ();
  }
  //  Делаем о же самое для статистик рабочих потоков.
  //  Рабочие потоки владеют информацией о времени выполения с точностью до алгоритма.
  {
    auto _threads   = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
    auto _link2appl = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();

    if (!_threads)
      {
        UASSERT_SIGNAL ("failed");
        return;
      }

    CHECK_CALL (
      _threads->work_with_statistic (
        [this, _link2appl](::libs::helpers::statistic::ExpandedTimeStatistic& _obj) {
          ::libs::helpers::statistic::ExpandedTimeStatistic::infos_type _infos;

          _obj.get (_infos);

          for (const std::string& _info : _infos)
            {
              MSG2LOGGER (_link2appl, _info, "uuu_data");
            }

          return true;
        }),
      "failed dump thread statistic");

    CHECK_CALL (
      _threads->work_with_statistic ([this](::libs::helpers::statistic::ExpandedTimeStatistic& _obj) {
        _obj.clear ();
        return true;
      }),
      "failed work with statistic");
  }
  return;
}


bool
Path::recv_special_event_impl (const events::IEvent::ptr& _evnt)
{
  if (auto _hardevnt = ::libs::iproperties::helpers::cast_event<sprops::hardware::InfoCPUEvent> (_evnt))
    {
      auto _threads = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();
      _threads->set_count_threads (_hardevnt->get_count ());
      _threads->set_cpu (_hardevnt->get_type ());
      return true;
    }

  if (auto _startevnt = ::libs::iproperties::helpers::cast_event<sruntime::state::ChangStateProcessTypeEvent> (_evnt))
    {
      state_ = _startevnt->is_start () ? obj::RunStateFilter::run : obj::RunStateFilter::stop;
      change_objs_state_impl (state_);
      return true;
    }

  if (auto _startevnt = ::libs::iproperties::helpers::cast_event<sruntime::state::ExpandTimeStatisticEvent> (_evnt))
    {
      switch (_startevnt->get_source ())
        {
        case sruntime::state::TypeStatisticSource::alg:
          {
            auto _pthreads = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_count_threads_lockfree ();

            std::function<bool(::libs::helpers::statistic::ExpandedTimeStatistic & _stat)> _update_funct = [&_startevnt](::libs::helpers::statistic::ExpandedTimeStatistic& _stat) {
              ::libs::helpers::statistic::ExpandedTimeStatistic::infos_type _info;
              _stat.get (_info);
              _startevnt->set_stat (_info);
              return true;
            };

            _pthreads->work_with_statistic (_update_funct);
            break;
          }
        case sruntime::state::TypeStatisticSource::path_obj:
          {
            ::libs::helpers::statistic::ExpandedTimeStatistic::infos_type _info;
            expand_objs_time_.get (_info);
            _startevnt->set_stat (_info);
            break;
          }
        default:
          UASSERT_SIGNAL ("unknown sruntime::state::TypeStatisticSource");
          break;
        }

      return true;
    }
  return false;
}


Path::path_obj_type::weak_ptr
Path::get_obj_impl (const PathObjID& obj_id)
{
  auto _it = id2obj_.find (obj_id);
  if (id2obj_.end () != _it)
    {
      return path_obj_type::weak_ptr (_it->second);
    }

  UASSERT_SIGNAL ("failed");
  return path_obj_type::weak_ptr ();
}


void
Path::refresh_id_objs_impl () const
{
  id_objs_.clear ();

  for (auto _obj : id2obj_)
    {
      id_objs_.insert (_obj.first);
    }
  return;
}

}}}}}      // namespace libs::icore::impl::var1::path
