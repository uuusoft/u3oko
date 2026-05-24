#pragma once
/**
\file       idata-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       31.01.2022
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen
{
class IDataSourceImpl final : public libs::icore::impl::var1::obj::interfs::IDataSourceInterfObjGraph
{
  public:
  void init ();

  private:
  virtual void get_types_int (std::vector< std::string >&) override;
  virtual void get_sources_int (const std::string&, syn::ListDevicesDataEvent::src_infos_type&) override;

  syn::ListDevicesDataEvent::src_names_type                types_;     //<
  std::vector< syn::ListDevicesDataEvent::src_infos_type > sources_;   //<
};
}   // namespace dlls::sources::gen_vgen
