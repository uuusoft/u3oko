/**
\file       expanded-time.cpp
\date       10.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "expanded-time.hpp"

namespace libs::helpers::statistic
{
ExpandedTime&
ExpandedTime::operator+= (const ExpandedTime& val)
{
  min_ = std::min (min_, val.min_);
  max_ = std::max (max_, val.max_);
  sum_ += val.sum_;
  count_ += val.count_;
  return *this;
}


template< class Archive >
void
ExpandedTime::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (min_);
  arh& BOOST_SERIALIZATION_NVP (max_);
  arh& BOOST_SERIALIZATION_NVP (sum_);
  arh& BOOST_SERIALIZATION_NVP (count_);
}


#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const NodeID& src)
{
  jvs = {
    { "id_node_name", ::boost::json::value_from (src.get_name ()) },
    { "id_node_name_dll", ::boost::json::value_from (src.get_name_dll ()) }
  };
}


NodeID
tag_invoke (::boost::json::value_to_tag< NodeID >, const ::boost::json::value& jvs)
{
  NodeID                       ret;
  const ::boost::json::object& obj = jvs.as_object ();
  ::libs::helpers::json::extract (obj, ret.update_name (), "id_node_name");
  ::libs::helpers::json::extract (obj, ret.update_name_dll (), "id_node_name_dll");
  return ret;
}


void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jvs,
  const EventBufsInfo&  src)
{
  jvs = {
    { "indx_sbuf", src.indx_sbuf_ },
    { "indx_dbuf", src.indx_dbuf_ }
  };
}


EventBufsInfo
tag_invoke (
  ::boost::json::value_to_tag< EventBufsInfo >,
  const ::boost::json::value& jvs)
{
  EventBufsInfo                ret;
  const ::boost::json::object& obj = jvs.as_object ();

  ret.indx_sbuf_ = obj.at ("indx_sbuf").as_string ();
  ret.indx_dbuf_ = obj.at ("indx_dbuf").as_string ();
  return ret;
}

void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jvs,
  const TimePoint&      src)
{
  jvs = { "time", std::chrono::system_clock::to_time_t (src.get_time ()) };
}


TimePoint
tag_invoke (
  ::boost::json::value_to_tag< TimePoint >,
  const ::boost::json::value& jvs)
{
  const auto      raw_time = ::libs::helpers::json::get_int64 (jvs.at ("time"));
  const TimePoint ret (::std::chrono::system_clock::from_time_t (raw_time));
  return ret;
}

// return ::libs::helpers::casts::static_cast_helper< ExpandedTime > (::libs::helpers::json::get_uint32 (jvs));

#endif

void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jsn,
  const ExpandedTime&   src)
{
  jsn = {
    { "min", ::boost::posix_time::to_simple_string (src.min_) },
    { "max", ::boost::posix_time::to_simple_string (src.max_) },
    { "sum", ::boost::posix_time::to_simple_string (src.sum_) },
    { "count", src.count_ }
  };
}


ExpandedTime
tag_invoke (
  ::boost::json::value_to_tag< ExpandedTime >,
  const ::boost::json::value& jsn)
{
  ExpandedTime ret;
  ret.min_   = ::boost::posix_time::duration_from_string (libs::helpers::json::get_string (jsn.at ("min")));
  ret.max_   = ::boost::posix_time::duration_from_string (libs::helpers::json::get_string (jsn.at ("max")));
  ret.sum_   = ::boost::posix_time::duration_from_string (libs::helpers::json::get_string (jsn.at ("sum")));
  ret.count_ = libs::helpers::json::get_uint64 (jsn.at ("count"));
  return ret;
}
}   // namespace libs::helpers::statistic

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::helpers::statistic::ExpandedTime);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::helpers::statistic::ExpandedTime);
