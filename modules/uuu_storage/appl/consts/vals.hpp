#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl { namespace consts {

const int         major_ver   = 2;                                                                                                            //< ???
const int         minor_ver   = 2;                                                                                                            //< ???
const int         major_build = 0;                                                                                                            //< ???
const int         minor_build = 0;                                                                                                            //< ???
const std::string txt_ver     = to_str (major_ver) + "." + to_str (minor_ver) + "." + to_str (major_build) + "." + to_str (minor_build);      //< ???

}}}}      // namespace modules::uuu_storage::appl::consts
