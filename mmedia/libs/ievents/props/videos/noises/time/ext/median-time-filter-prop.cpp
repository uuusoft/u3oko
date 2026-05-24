/**
\file       median-time-filter-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../../includes_int.hpp"
#include "median-time-filter-prop.hpp"

namespace libs::ievents::props::videos::noises::time::ext
{
Sortings
str2sort (const std::string& str)
{
  Sortings                                    ret = Sortings::usual;
  std::unordered_map< std::string, Sortings > str2sort;

  str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("default", Sortings::usual));
  str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("adaptive", Sortings::adaptive));
  str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("skip", Sortings::skip));
  str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("standart", Sortings::standart));
  str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("insert", Sortings::insert));

  auto find = str2sort.find (str);
  if (str2sort.end () == find)
  {
    U3_ASSERT_SIGNAL ("failed");
  }
  else
  {
    ret = find->second;
  }
  return ret;
}


MedianTimeFilterProp::MedianTimeFilterProp (const Acessor& ph) :
  count_bufs_ (3),
  rang_ (2),
  motion_detect_ (false),
  sort_type_ (Sortings::usual)
{
  property_name_ = gen_get_mid ();
}


MedianTimeFilterProp::~MedianTimeFilterProp ()
{
}


::libs::events::IEvent::ptr
MedianTimeFilterProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MedianTimeFilterProp > (this, deep);
}


void
MedianTimeFilterProp::self_correct_int ()
{
  count_bufs_ = count_bufs_ / 2 * 2 + 1;   // гарантируем нечетность.
  count_bufs_ = ::libs::helpers::utils::ret_check_bound (count_bufs_, consts::min_count_bufs, consts::max_count_bufs);
  rang_       = ::libs::helpers::utils::ret_check_bound (rang_, 0u, count_bufs_ - 1);
}


void
MedianTimeFilterProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  count_bufs_    = ::libs::helpers::json::get_uint32 (obj.at ("count_bufs"));
  rang_          = ::libs::helpers::json::get_uint32 (obj.at ("rang"));
  sort_type_     = ::boost::json::value_to< Sortings > (obj.at ("sort_type"));
  motion_detect_ = obj.at ("motion_detect").as_bool ();
}


void
MedianTimeFilterProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["count_bufs"]    = count_bufs_;
  obj["rang"]          = rang_;
  obj["sort_type"]     = ::boost::json::value_from (sort_type_);
  obj["motion_detect"] = motion_detect_;
}


void
MedianTimeFilterProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (MedianTimeFilterProp);
  super::copy_int (src);
  count_bufs_    = dsrc->count_bufs_;
  motion_detect_ = dsrc->motion_detect_;
  sort_type_     = dsrc->sort_type_;
  rang_          = dsrc->rang_;
}


template< class Archive >
void
MedianTimeFilterProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (count_bufs_);
  ar& BOOST_SERIALIZATION_NVP (motion_detect_);
  ar& BOOST_SERIALIZATION_NVP (sort_type_);
  ar& BOOST_SERIALIZATION_NVP (rang_);

  self_correct ();
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const Sortings& src)
{
  jv = U3_CAST_UINT32_FORCE (src);
}


Sortings
tag_invoke (::boost::json::value_to_tag< Sortings >, const ::boost::json::value& jv)
{
  return U3_CAST_STATIC< Sortings > (::libs::helpers::json::get_uint32 (jv));
}
}   // namespace libs::ievents::props::videos::noises::time::ext

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
