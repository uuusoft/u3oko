#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/

namespace modules { namespace uuu_log { namespace appl { namespace consts {

const int major_ver   = 2;      //< ???
const int minor_ver   = 2;      //< ???
const int major_build = 0;      //< ???
const int minor_build = 0;      //< ???

const std::string txt_ver = to_str (major_ver) + "." + to_str (minor_ver) + "." + to_str (major_build) + "." + to_str (minor_build);      //< ???

const std::size_t size_tab              = 8;       //< ???
const std::size_t max_count_tabs_date   = 4;       //< ???
const std::size_t max_count_tabs_subsys = 2;       //< ???
const std::size_t max_count_tabs_info   = 15;      //< ???

}}}}      // namespace modules::uuu_log::appl::consts
