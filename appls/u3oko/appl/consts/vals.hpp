#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    u3oko
\brief      empty brief
*/

namespace appls { namespace u3oko { namespace appl { namespace consts {

const int           max_records        = 4;
const time_duration max_time_per_cycle = boost::posix_time::milliseconds (20 * 30 * 1000);
const int           major_ver          = 2;
const int           minor_ver          = 3;
const int           major_build        = 0;
const int           minor_build        = 0;
const std::string   name_company       = "uuusoft";
const std::string   name_application   = "u3oko";
const std::string   txt_ver            = to_str (major_ver) + "." + to_str (minor_ver) + "." + to_str (major_build) + "." + to_str (minor_build);

}}}}      // namespace appls::u3oko::appl::consts
