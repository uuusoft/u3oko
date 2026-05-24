#pragma once
/**
\file       idata-source-interf-obj-graph.hpp
\date       31.01.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::interfs
{
class IDataSourceInterfObjGraph : public core::graph::IInterfGraphObj
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IDataSourceInterfObjGraph)

  using src_infos_type = ::libs::imdata_events::events::ListDevicesDataEvent::src_infos_type;
  using src_names_type = ::libs::imdata_events::events::ListDevicesDataEvent::src_names_type;

  IDataSourceInterfObjGraph ();

  IDataSourceInterfObjGraph (const IDataSourceInterfObjGraph& src)            = delete;
  IDataSourceInterfObjGraph& operator= (const IDataSourceInterfObjGraph& src) = delete;

  virtual ~IDataSourceInterfObjGraph ();

  void get_types (src_names_type& types);

  void get_sources (const std::string& type, src_infos_type& sources);

  private:
  virtual void get_types_int (src_names_type& types)                              = 0;
  virtual void get_sources_int (const std::string& type, src_infos_type& sources) = 0;
};
}   // namespace libs::icore::impl::var1::obj::interfs
