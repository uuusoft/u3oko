#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_data
\brief      empty brief
*/

namespace modules { namespace uuu_mdata { namespace appl { namespace consts {

const int         major_ver        = 2;
const int         minor_ver        = 2;
const int         major_build      = 0;
const int         minor_build      = 0;
const std::string name_company     = "uuusoft";
const std::string name_application = "uuu_mdata";
const std::string txt_ver          = to_str (major_ver) + "." + to_str (minor_ver) + "." + to_str (major_build) + "." + to_str (minor_build);

}}}}      // namespace modules::uuu_mdata::appl::consts
