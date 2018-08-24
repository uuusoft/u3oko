//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      Файл реализации типа для расширения постоянных свойств фильтра фильтрации в пространственной области.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter-dll.hpp"

namespace dlls { namespace filter_noise { namespace space {

InfoFilter::InfoFilter () :
  rprops_ (nullptr),
  counter_frame_ (0)
{
  rprops_ = ::libs::iproperties::helpers::get_and_cast_event<props_type> (props_);
  str2props_.insert (str2prop_type::value_type (props_->get_mid (), rprops_));

  rprops_->impl_info_ = std::make_shared<::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp> ();
  str2props_.insert (str2prop_type::value_type (rprops_->impl_info_->get_mid (), rprops_->impl_info_.get ()));
}


InfoFilter::~InfoFilter ()
{}

}}}      // namespace dlls::filter_noise::space
