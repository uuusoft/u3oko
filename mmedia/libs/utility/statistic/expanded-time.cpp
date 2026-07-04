/**
\file       expanded-time.cpp
\date       10.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "expanded-time.hpp"

namespace libs::utility::statistic
{
auto
ExpandedTime::operator+= (const ExpandedTime& val) -> ExpandedTime&
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
  ::libs::utility::json::extract (obj, ret.update_name (), "id_node_name");
  ::libs::utility::json::extract (obj, ret.update_name_dll (), "id_node_name_dll");
  return ret;
}


void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jvs,
  const EventBufs&      src)
{
  jvs = {
    { "indx_sbuf", src.indx_sbuf_ },
    { "indx_dbuf", src.indx_dbuf_ }
  };
}


EventBufs
tag_invoke (
  ::boost::json::value_to_tag< EventBufs >,
  const ::boost::json::value& jvs)
{
  EventBufs                    ret;
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
  const auto      raw_time = ::libs::utility::json::get_int64 (jvs.at ("time"));
  const TimePoint ret (::std::chrono::system_clock::from_time_t (raw_time));
  return ret;
}

// return ::libs::utility::casts::static_cast_helper< ExpandedTime > (::libs::utility::json::get_uint32 (jvs));

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


auto
tag_invoke (
  ::boost::json::value_to_tag< ExpandedTime >,
  const ::boost::json::value& jsn) -> ExpandedTime
{
  ExpandedTime ret;
  ret.min_   = ::boost::posix_time::duration_from_string (libs::utility::json::get_string (jsn.at ("min")));
  ret.max_   = ::boost::posix_time::duration_from_string (libs::utility::json::get_string (jsn.at ("max")));
  ret.sum_   = ::boost::posix_time::duration_from_string (libs::utility::json::get_string (jsn.at ("sum")));
  ret.count_ = libs::utility::json::get_uint64 (jsn.at ("count"));
  return ret;
}
}   // namespace libs::utility::statistic

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::utility::statistic::ExpandedTime);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::utility::statistic::ExpandedTime);
