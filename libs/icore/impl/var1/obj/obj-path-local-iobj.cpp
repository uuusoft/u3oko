//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       obj-path-local-iobj.cpp
\date       01.06.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "../includes.hpp"
#include "obj-path-local.hpp"

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {

core::path::IInterfPathObj::raw_ptr
ObjPath::query_int (const ::libs::helpers::utils::cuuid& _id_interf)
{
  UASSERT (dfilter_);
  return dfilter_->query (_id_interf);
}

}}}}}      // namespace libs::icore::impl::var1::obj
