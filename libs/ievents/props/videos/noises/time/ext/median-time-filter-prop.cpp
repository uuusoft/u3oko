//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       median-time-filter-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../../includes_int.hpp"
#include "median-time-filter-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace time { namespace ext {

TypeSortAlg
str2sort (const std::string& _str)
{
  TypeSortAlg _ret = TypeSortAlg::usual;

  std::map<std::string, TypeSortAlg> _str2sort;

  _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("default", TypeSortAlg::usual));
  _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("adaptive", TypeSortAlg::adaptive));
  _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("skip", TypeSortAlg::skip));
  _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("standart", TypeSortAlg::standart));
  _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("insert", TypeSortAlg::insert));

  auto _find = _str2sort.find (_str);

  if (_str2sort.end () == _find)
    {
      UASSERT_SIGNAL ("failed");
    }
  else
    {
      _ret = _find->second;
    }

  return _ret;
}


MedianTimeFilterProp::MedianTimeFilterProp (const Acessor& _ph) :
  count_buffs_ (3),
  rang_ (2),
  motion_detect_ (false),
  sort_type_ (TypeSortAlg::usual)
{
  property_name_ = gen_get_mid ();
}


MedianTimeFilterProp::~MedianTimeFilterProp ()
{}


::libs::events::IEvent::ptr
MedianTimeFilterProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<MedianTimeFilterProp> (this, _deep);
}


void
MedianTimeFilterProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<int> (_param, "count_buffs", count_buffs_);
      ::libs::icore::xml::helpers::load<int> (_param, "rang", rang_);
      ::libs::icore::xml::helpers::load<bool> (_param, "motion_detect", motion_detect_);

      ::libs::icore::xml::helpers::load (
        _param,
        "sort_type",
        [this](const std::string& _str) {
          sort_type_ = str2sort (_str);
          return;
        });

      ++_param;
    }

  count_buffs_ = count_buffs_ / 2 * 2 + 1;      //гарантируем нечетность.
  count_buffs_ = ::libs::helpers::utils::ret_check_bound (count_buffs_, consts::min_count_buffs, consts::max_count_buffs);
  rang_        = ::libs::helpers::utils::ret_check_bound (rang_, 0, count_buffs_ - 1);

  self_correct ();
  return;
}


void
MedianTimeFilterProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MedianTimeFilterProp);
  super::copy_int (_src);
  count_buffs_   = _dsrc->count_buffs_;
  motion_detect_ = _dsrc->motion_detect_;
  sort_type_     = _dsrc->sort_type_;
  rang_          = _dsrc->rang_;
  UASSERT_SIGNAL ("unimplemented");
  return;
}


template <class Archive>
void
MedianTimeFilterProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (count_buffs_);
  ar& BOOST_SERIALIZATION_NVP (motion_detect_);
  ar& BOOST_SERIALIZATION_NVP (sort_type_);
  ar& BOOST_SERIALIZATION_NVP (rang_);
  return;
}

}}}}}}}      // namespace libs::ievents::props::videos::noises::time::ext

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp);
