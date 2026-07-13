/**
\file       median-time-filter-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../../../../events-base-includes_int.hpp"
#include "median-time-filter-prop.hpp"

namespace libs::events_base::props::videos::noises::time::ext
{
auto
str2sort (const std::string& val) -> Sortings
{
  static const boost::unordered_flat_map< std::string, const Sortings > val2val = {
    { "default", Sortings::usual },
    { "adaptive", Sortings::adaptive },
    { "skip", Sortings::skip },
    { "standart", Sortings::standart },
    { "insert", Sortings::insert },
    { "inplace_3_element", Sortings::inplace_3_element },
    { "unknown", Sortings::unknown }
  };

  auto finger = val2val.find (val);
  if (val2val.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find sorting type by name" + TOLOG (val));
    finger = val2val.find ("default");
  }
  return finger->second;
}


MedianTimeFilterProp::MedianTimeFilterProp (const Acessor& pha)
{
}


auto
MedianTimeFilterProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return MedianTimeFilterProp::gen_get_mid ();
}


auto
MedianTimeFilterProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< MedianTimeFilterProp > (this, deep);
}


void
MedianTimeFilterProp::self_correct_int ()
{
  count_bufs_ = count_bufs_ / 2 * 2 + 1;   // гарантируем нечетность.
  count_bufs_ = ::libs::utility::utils::ret_check_bound (count_bufs_, consts::min_count_bufs, consts::max_count_bufs);
  rang_       = ::libs::utility::utils::ret_check_bound (rang_, 0U, count_bufs_ - 1);
}


void
MedianTimeFilterProp::load_json_int (const ::boost::json::object& obj)
{
  U3_XLOG_DBG (TOLOG (::boost::json::serialize (obj)));
  super::load_json_int (obj);

  count_bufs_    = ::libs::utility::json::get_uint32 (obj.at ("count_bufs"));
  rang_          = ::libs::utility::json::get_uint32 (obj.at ("rang"));
  sort_type_     = ::boost::json::value_to< Sortings > (obj.at ("sort_type"));
  motion_detect_ = obj.at ("motion_detect").as_bool ();
  indx_diff_buf_ = obj.at ("indx_diff_buf").as_string ();
  use_diff_buf_  = obj.at ("use_diff_buf").as_bool ();
}


void
MedianTimeFilterProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["count_bufs"]    = count_bufs_;
  obj["rang"]          = rang_;
  obj["sort_type"]     = ::boost::json::value_from (sort_type_);
  obj["motion_detect"] = motion_detect_;
  obj["indx_diff_buf"] = indx_diff_buf_;
  obj["use_diff_buf"]  = use_diff_buf_;
}


void
MedianTimeFilterProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MedianTimeFilterProp > (src);
  super::copy_int (src);

  count_bufs_    = dsrc->count_bufs_;
  motion_detect_ = dsrc->motion_detect_;
  sort_type_     = dsrc->sort_type_;
  rang_          = dsrc->rang_;
  indx_diff_buf_ = dsrc->indx_diff_buf_;
  use_diff_buf_  = dsrc->use_diff_buf_;
}


template< class Archive >
void
MedianTimeFilterProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (count_bufs_);
  arh& BOOST_SERIALIZATION_NVP (motion_detect_);
  arh& BOOST_SERIALIZATION_NVP (sort_type_);
  arh& BOOST_SERIALIZATION_NVP (rang_);
  arh& BOOST_SERIALIZATION_NVP (indx_diff_buf_);
  arh& BOOST_SERIALIZATION_NVP (use_diff_buf_);

  self_correct ();
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Sortings& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


auto
tag_invoke (::boost::json::value_to_tag< Sortings >, const ::boost::json::value& jvs) -> Sortings
{
  return ::libs::utility::casts::static_cast_helper< Sortings > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base::props::videos::noises::time::ext

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::noises::time::ext::MedianTimeFilterProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::noises::time::ext::MedianTimeFilterProp);
