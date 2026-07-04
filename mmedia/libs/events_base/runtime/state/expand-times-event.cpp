/**
\file       expand-times-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "expand-times-event.hpp"

namespace libs::events_base::runtime::state
{
ExpandTimesEvent::ExpandTimesEvent (
  const Acessor&     ph,
  full_storages_type infos) :
  infos_ (std::move (infos))
{
}


auto
ExpandTimesEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ExpandTimesEvent::gen_get_mid ();
}


auto
ExpandTimesEvent::get_stats () const -> const ExpandTimesEvent::full_storages_type&
{
  return infos_;
}


auto
ExpandTimesEvent::get_stat (const key_storage_type& key) const -> const ExpandTimesEvent::storages_type&
{
  return infos_[key];
}


void
ExpandTimesEvent::set_stat (const key_storage_type& key, const storages_type& infos)
{
  infos_[key] = infos;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
const ::libs::utility::statistic::ExpandedTimes::infos_type&
ExpandTimesEvent::get_stat () const
{
  return infos_;
}


void
ExpandTimesEvent::set_stat (const ::libs::utility::statistic::ExpandedTimes::infos_type& infos)
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

auto
ExpandTimesEvent::get_action () const -> const Actions&
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

  jsn["actions"]   = U3_CAST_INT32_FORCE (action_);
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


auto
ExpandTimesEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ExpandTimesEvent > (this, deep);
}


void
ExpandTimesEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ExpandTimesEvent > (src);
  super::copy_int (src);

  action_    = dsrc->action_;
  infos_     = dsrc->infos_;
  source_id_ = dsrc->source_id_;
}


template< class Archive >
void
ExpandTimesEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (action_);
  arh& BOOST_SERIALIZATION_NVP (infos_);
  arh& BOOST_SERIALIZATION_NVP (source_id_);
  self_correct ();
}
}   // namespace libs::events_base::runtime::state

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::state::ExpandTimesEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::state::ExpandTimesEvent);
