#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_gen_lib
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_lib { namespace consts {

const std::string name_get_funct  = "get_source";       //< ???
const std::string name_free_funct = "free_source";      //< ???

}}}}      // namespace dlls::sources::gen_lib::consts

namespace dlls { namespace sources { namespace gen_lib {

typedef bool(get_source_funct_type) (ISourceImpl** _obj);
typedef bool(free_source_funct_type) (ISourceImpl** _obj);

}}}      // namespace dlls::sources::gen_lib
