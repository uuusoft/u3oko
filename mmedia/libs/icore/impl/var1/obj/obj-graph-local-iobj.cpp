/**
\file       obj-graph-local-iobj.cpp
\date       01.06.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../libs-icore-includes_int.hpp"
#include "../libs-icore-impl-var1-includes.hpp"
#include "obj-graph-local.hpp"

namespace libs::icore::impl::var1::obj
{
core::graph::IInterfGraphObj::raw_ptr
ObjGraph::query_int (const ::libs::helpers::utils::cuuid& id_interf)
{
  U3_ASSERT (dfilter_);
  return dfilter_->query (id_interf);
}
}   // namespace libs::icore::impl::var1::obj
