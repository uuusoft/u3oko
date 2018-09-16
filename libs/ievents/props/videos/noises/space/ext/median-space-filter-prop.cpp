//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       median-space-filter-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../../includes_int.hpp"
#include "median-space-filter-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace noises { namespace space { namespace ext {

TypeSortAlg
str2sort (const std::string& _str)
{
  TypeSortAlg _ret = TypeSortAlg::usual;

  static std::map<std::string, TypeSortAlg> _str2sort;

  if (_str2sort.empty ())
    {
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("default", TypeSortAlg::usual));
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("adaptive", TypeSortAlg::adaptive));
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("skip", TypeSortAlg::skip));
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("standart", TypeSortAlg::standart));
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("insert", TypeSortAlg::insert));
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("count", TypeSortAlg::count));
      _str2sort.insert (std::map<std::string, TypeSortAlg>::value_type ("rand", TypeSortAlg::rand));
    }

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


MedianSpaceFilterProp::MedianSpaceFilterProp (const Acessor& _ph) :
  size_core_ (5),
  dim_core_ (2),
  rang_ (2),
  sort_type_ (TypeSortAlg::usual),
  size_cond_core_ (0),
  cond_rang_ (0)
{
  property_name_ = gen_get_mid ();
}


MedianSpaceFilterProp::~MedianSpaceFilterProp ()
{}


void
MedianSpaceFilterProp::correct ()
{
  size_core_      = ::libs::helpers::utils::ret_check_bound (size_core_, consts::min_size_core, consts::max_size_core);
  dim_core_       = ::libs::helpers::utils::ret_check_bound (dim_core_, consts::min_dim_core, consts::max_dim_core);
  rang_           = ::libs::helpers::utils::ret_check_bound (rang_, 0, UUU_ICAST_INT (std::pow (size_core_, dim_core_)) - 1);
  size_cond_core_ = ::libs::helpers::utils::ret_check_bound (size_cond_core_, 0, consts::max_size_core);
  cond_rang_      = size_cond_core_ ? ::libs::helpers::utils::ret_check_bound (cond_rang_, 0, UUU_ICAST_INT (std::pow (size_cond_core_, dim_core_)) - 1) : 0;
  return;
}


::libs::events::IEvent::ptr
MedianSpaceFilterProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<MedianSpaceFilterProp> (this, _deep);
}


void
MedianSpaceFilterProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<int> (_param, "size_core", size_core_);
      ::libs::icore::xml::helpers::load<int> (_param, "dim_core", dim_core_);
      ::libs::icore::xml::helpers::load<int> (_param, "rang", rang_);
      ::libs::icore::xml::helpers::load<int> (_param, "size_cond_core", size_cond_core_);
      ::libs::icore::xml::helpers::load<int> (_param, "cond_rang", cond_rang_);

      ::libs::icore::xml::helpers::load (
        _param,
        "sort_type",
        [this](const std::string& _str) {
          sort_type_ = str2sort (_str);
          return;
        });

      ++_param;
    }

  correct ();
  self_correct ();
  return;
}


void
MedianSpaceFilterProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MedianSpaceFilterProp);
  super::copy_int (_src);

  size_core_      = _dsrc->size_core_;
  dim_core_       = _dsrc->dim_core_;
  rang_           = _dsrc->rang_;
  sort_type_      = _dsrc->sort_type_;
  size_cond_core_ = _dsrc->size_cond_core_;
  cond_rang_      = _dsrc->cond_rang_;

  correct ();
  return;
}


template <class Archive>
void
MedianSpaceFilterProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);

  ar& BOOST_SERIALIZATION_NVP (size_core_);
  ar& BOOST_SERIALIZATION_NVP (dim_core_);
  ar& BOOST_SERIALIZATION_NVP (sort_type_);
  ar& BOOST_SERIALIZATION_NVP (rang_);
  ar& BOOST_SERIALIZATION_NVP (size_cond_core_);
  ar& BOOST_SERIALIZATION_NVP (cond_rang_);
  return;
}

}}}}}}}      // namespace libs::ievents::props::videos::noises::space::ext

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp);
