#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_appl
\brief      empty brief
*/

namespace modules { namespace uuu_appl {

using main_appl_funct_type = int(int _argc, char* _argv[]);
//using test1_funct_type = bool(::libs::properties::ISharedProperty::raw_ptr _ptr);      //  debug
//using test2_funct_type = ::libs::properties::ISharedProperty::raw_ptr ();              //  debug

}}      // namespace modules::uuu_appl


namespace modules { namespace uuu_appl { namespace consts {

const std::string name_main_appl_funct = "main_impl";      //< ???
//const std::string name_test_funct1     = "test_funct1";      //< Test name function
//const std::string name_test_funct2     = "test_funct2";      //< Test name function

}}}      // namespace modules::uuu_appl::consts
