/**
\file       median-space-filter-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../../includes_int.hpp"
#include "median-space-filter-prop.hpp"

namespace libs::ievents::props::videos::noises::space::ext
{
std::string
to_string (const Sortings& val)
{
  switch (val)
  {
  case Sortings::usual:
    return "usual";
  case Sortings::adaptive:
    return "adaptive";
  case Sortings::skip:
    return "skip";
  case Sortings::standart:
    return "standart";
  case Sortings::insert:
    return "insert";
  case Sortings::count:
    return "count";
  case Sortings::rand:
    return "rand";
  case Sortings::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown Sortings" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown Sortings";
  }
}


Sortings
str2sort (const std::string& str)
{
  Sortings                                           ret = Sortings::usual;
  static std::unordered_map< std::string, Sortings > str2sort;

  if (str2sort.empty ())
  {
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("default", Sortings::usual));
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("adaptive", Sortings::adaptive));
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("skip", Sortings::skip));
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("standart", Sortings::standart));
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("insert", Sortings::insert));
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("count", Sortings::count));
    str2sort.insert (std::unordered_map< std::string, Sortings >::value_type ("rand", Sortings::rand));
  }

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


MedianSpaceFilterProp::MedianSpaceFilterProp (const Acessor& ph) :
  size_core_ (5),
  dim_core_ (2),
  rang_ (2),
  sort_type_ (Sortings::usual),
  size_cond_core_ (0),
  cond_rang_ (0)
{
  property_name_ = gen_get_mid ();
}


MedianSpaceFilterProp::~MedianSpaceFilterProp ()
{
}


void
MedianSpaceFilterProp::self_correct_int ()
{
  size_core_      = ::libs::helpers::utils::ret_check_bound (size_core_, consts::min_size_core, consts::max_size_core);
  dim_core_       = ::libs::helpers::utils::ret_check_bound (dim_core_, consts::min_dim_core, consts::max_dim_core);
  rang_           = ::libs::helpers::utils::ret_check_bound (rang_, 0, U3_CAST_INT32 (std::pow (size_core_, dim_core_)) - 1);
  size_cond_core_ = ::libs::helpers::utils::ret_check_bound (size_cond_core_, 0, consts::max_size_core);
  cond_rang_      = size_cond_core_ ? ::libs::helpers::utils::ret_check_bound (cond_rang_, 0, U3_CAST_INT32 (std::pow (size_cond_core_, dim_core_)) - 1) : 0;
}


::libs::events::IEvent::ptr
MedianSpaceFilterProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MedianSpaceFilterProp > (this, deep);
}


void
MedianSpaceFilterProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  size_core_      = ::libs::helpers::json::get_uint32 (obj.at ("size_core"));
  dim_core_       = ::libs::helpers::json::get_uint32 (obj.at ("dim_core"));
  rang_           = ::libs::helpers::json::get_uint32 (obj.at ("rang"));
  sort_type_      = ::boost::json::value_to< Sortings > (obj.at ("sort_type"));
  size_cond_core_ = ::libs::helpers::json::get_uint32 (obj.at ("size_cond_core"));
  cond_rang_      = ::libs::helpers::json::get_uint32 (obj.at ("cond_rang"));
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
}


void
MedianSpaceFilterProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (MedianSpaceFilterProp);
  super::copy_int (src);

  size_core_      = dsrc->size_core_;
  dim_core_       = dsrc->dim_core_;
  rang_           = dsrc->rang_;
  sort_type_      = dsrc->sort_type_;
  size_cond_core_ = dsrc->size_cond_core_;
  cond_rang_      = dsrc->cond_rang_;
}


template< class Archive >
void
MedianSpaceFilterProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  ar& BOOST_SERIALIZATION_NVP (size_core_);
  ar& BOOST_SERIALIZATION_NVP (dim_core_);
  ar& BOOST_SERIALIZATION_NVP (sort_type_);
  ar& BOOST_SERIALIZATION_NVP (rang_);
  ar& BOOST_SERIALIZATION_NVP (size_cond_core_);
  ar& BOOST_SERIALIZATION_NVP (cond_rang_);

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
}   // namespace libs::ievents::props::videos::noises::space::ext

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);
