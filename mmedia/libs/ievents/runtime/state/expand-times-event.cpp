/**
\file       expand-times-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "expand-times-event.hpp"

namespace libs::ievents::runtime::state
{
ExpandTimesEvent::ExpandTimesEvent (
  const Acessor&            ph,
  const full_storages_type& infos) :
  action_ (Actions::get),
  infos_ (infos)
{
  property_name_ = gen_get_mid ();
}


ExpandTimesEvent::~ExpandTimesEvent ()
{
}


const ExpandTimesEvent::full_storages_type&
ExpandTimesEvent::get_stats () const
{
  return infos_;
}


const ExpandTimesEvent::storages_type&
ExpandTimesEvent::get_stat (const key_storage_type& key) const
{
  return infos_[key];
}


void
ExpandTimesEvent::set_stat (const key_storage_type& key, const storages_type& infos)
{
  infos_[key] = infos;
}

#if 0
const ::libs::helpers::statistic::ExpandedTimes::infos_type&
ExpandTimesEvent::get_stat () const
{
  return infos_;
}


void
ExpandTimesEvent::set_stat (const ::libs::helpers::statistic::ExpandedTimes::infos_type& infos)
{
  infos_ = infos;
}


const StatSources&
ExpandTimesEvent::get_source () const
{
  return source_;
}


void
ExpandTimesEvent::set_source (const StatSources& source)
{
  source_ = source;
}
#endif

const Actions&
ExpandTimesEvent::get_action () const
{
  return action_;
}


void
ExpandTimesEvent::set_action (const Actions& action)
{
  action_ = action;
}


void
ExpandTimesEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "ExpandTimesEvent::load_json_int: not implemented");
}


void
ExpandTimesEvent::save_json_int (::boost::json::object& jsn) const
{
  super::save_json_int (jsn);

  jsn["action"]    = U3_CAST_INT32_FORCE (action_);
  jsn["source_id"] = source_id_;

  // graph paths
  auto& graphs = jsn["infos"].emplace_array ();
  for (const auto& graph : infos_)
  {
    // graph path nodes
    auto nodes = boost::json::array ();
    for (const auto& node : graph.second)
    {
      //  algs graph path node
      auto algs = boost::json::array ();
      for (const auto& alg : node.second)
      {
        // propertys alg graph path node
        algs.push_back ({ { "algid", alg.first }, { "prop", ::boost::json::value_from (alg.second) } });
      }
      nodes.push_back ({ { "nodeid", node.first }, { "algs", algs } });
    }
    graphs.push_back ({ { "graphid", graph.first }, { "nodes", nodes } });
  }
}


::libs::events::IEvent::ptr
ExpandTimesEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ExpandTimesEvent > (this, deep);
}


void
ExpandTimesEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ExpandTimesEvent);
  super::copy_int (src);
  action_    = dsrc->action_;
  infos_     = dsrc->infos_;
  source_id_ = dsrc->source_id_;
}


template< class Archive >
void
ExpandTimesEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (infos_);
  ar& BOOST_SERIALIZATION_NVP (source_id_);
  self_correct ();
}
}   // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::state::ExpandTimesEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::state::ExpandTimesEvent);
