/**
\file       median-space-filter-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../../events-base-includes_int.hpp"
#include "median-space-filter-prop.hpp"

namespace libs::events_base::props::videos::noises::space::ext
{
auto
to_string (const Sortings& val) -> const std::string&
{
  static const boost::unordered_flat_map< Sortings, const std::string > val2val = {
    { Sortings::usual, "usual" },
    { Sortings::adaptive, "adaptive" },
    { Sortings::skip, "skip" },
    { Sortings::standart, "standart" },
    { Sortings::insert, "insert" },
    { Sortings::count, "count" },
    { Sortings::rand, "rand" },
    { Sortings::unknown, "unknown" }
  };

  auto finger = val2val.find (val);
  if (val2val.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find name sorting type");
    finger = val2val.find (Sortings::usual);
  }
  return finger->second;
}


auto
str2sort (const std::string& str) -> Sortings
{
  static const boost::unordered_flat_map< std::string, const Sortings > str2sort = {
    { "usual", Sortings::usual },
    { "adaptive", Sortings::adaptive },
    { "skip", Sortings::skip },
    { "standart", Sortings::standart },
    { "insert", Sortings::insert },
    { "count", Sortings::count },
    { "rand", Sortings::rand },
    { "unknown", Sortings::unknown }
  };

  auto finger = str2sort.find (str);
  if (str2sort.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find sorting type by name " + TOLOG (str));
    finger = str2sort.find ("default");
  }
  return finger->second;
}


MedianSpaceFilterProp::MedianSpaceFilterProp (const Acessor& pha)
{
}


auto
MedianSpaceFilterProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return MedianSpaceFilterProp::gen_get_mid ();
}


void
MedianSpaceFilterProp::self_correct_int ()
{
  size_core_      = ::libs::utility::utils::ret_check_bound (size_core_, consts::min_size_core, consts::max_size_core);
  dim_core_       = ::libs::utility::utils::ret_check_bound (dim_core_, consts::min_dim_core, consts::max_dim_core);
  rang_           = ::libs::utility::utils::ret_check_bound (rang_, 0, U3_CAST_INT32 (std::pow (size_core_, dim_core_)) - 1);
  size_cond_core_ = ::libs::utility::utils::ret_check_bound (size_cond_core_, 0, consts::max_size_core);
  cond_rang_      = size_cond_core_ ? ::libs::utility::utils::ret_check_bound (cond_rang_, 0, U3_CAST_INT32 (std::pow (size_cond_core_, dim_core_)) - 1) : 0;
}


auto
MedianSpaceFilterProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< MedianSpaceFilterProp > (this, deep);
}


void
MedianSpaceFilterProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  size_core_      = ::libs::utility::json::get_uint32 (obj.at ("size_core"));
  dim_core_       = ::libs::utility::json::get_uint32 (obj.at ("dim_core"));
  rang_           = ::libs::utility::json::get_uint32 (obj.at ("rang"));
  sort_type_      = ::boost::json::value_to< Sortings > (obj.at ("sort_type"));
  size_cond_core_ = ::libs::utility::json::get_uint32 (obj.at ("size_cond_core"));
  cond_rang_      = ::libs::utility::json::get_uint32 (obj.at ("cond_rang"));
  indx_cond_buf_  = obj.at ("indx_cond_buf").as_string ();
  use_cond_buf_   = obj.at ("use_cond_buf").as_bool ();
}


void
MedianSpaceFilterProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["size_core"]      = size_core_;
  obj["dim_core"]       = dim_core_;
  obj["rang"]           = rang_;
  obj["sort_type"]      = ::boost::json::value_from (sort_type_);
  obj["size_cond_core"] = size_cond_core_;
  obj["cond_rang"]      = cond_rang_;
  obj["indx_cond_buf"]  = indx_cond_buf_;
  obj["use_cond_buf"]   = use_cond_buf_;
}


void
MedianSpaceFilterProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MedianSpaceFilterProp > (src);
  super::copy_int (src);

  size_core_      = dsrc->size_core_;
  dim_core_       = dsrc->dim_core_;
  rang_           = dsrc->rang_;
  sort_type_      = dsrc->sort_type_;
  size_cond_core_ = dsrc->size_cond_core_;
  cond_rang_      = dsrc->cond_rang_;
  indx_cond_buf_  = dsrc->indx_cond_buf_;
  use_cond_buf_   = dsrc->use_cond_buf_;
}


template< class Archive >
void
MedianSpaceFilterProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (size_core_);
  arh& BOOST_SERIALIZATION_NVP (dim_core_);
  arh& BOOST_SERIALIZATION_NVP (sort_type_);
  arh& BOOST_SERIALIZATION_NVP (rang_);
  arh& BOOST_SERIALIZATION_NVP (size_cond_core_);
  arh& BOOST_SERIALIZATION_NVP (cond_rang_);
  arh& BOOST_SERIALIZATION_NVP (indx_cond_buf_);
  arh& BOOST_SERIALIZATION_NVP (use_cond_buf_);

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
}   // namespace libs::events_base::props::videos::noises::space::ext

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::noises::space::ext::MedianSpaceFilterProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::noises::space::ext::MedianSpaceFilterProp);
