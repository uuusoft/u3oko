/**
\file       idata-source-interf-obj-graph.cpp
\date       31.01.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../libs-icore-includes_int.hpp"
#include "../../libs-icore-impl-var1-includes.hpp"

namespace libs::icore::impl::var1::obj::interfs
{
IDataSourceInterfObjGraph::IDataSourceInterfObjGraph ()
{
}


IDataSourceInterfObjGraph::~IDataSourceInterfObjGraph ()
{
}


void
IDataSourceInterfObjGraph::get_types (std::vector< std::string >& types)
{
  types.clear ();
  get_types_int (types);
}


void
IDataSourceInterfObjGraph::get_sources (
  const std::string&                                            type,
  std::vector< ::libs::imdata_events::events::DataSourceInfo >& sources)
{
  sources.clear ();
  get_sources_int (type, sources);
}
}   // namespace libs::icore::impl::var1::obj::interfs
