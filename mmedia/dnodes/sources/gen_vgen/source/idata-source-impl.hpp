#pragma once
/**
\file       idata-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       31.01.2022
*/

namespace dnodes::sources::gen_vgen
{
class IDataSourceImpl final : public libs::icore::impl::base::obj::interfs::IDataSourceInterfObjGraph
{
  public:
  IDataSourceImpl ()  = default;
  ~IDataSourceImpl () = default;

  auto init () -> void;

  private:
  virtual void get_types_int (std::vector< std::string >&) override;
  virtual void get_sources_int (const std::string&, syn::ListDevicesDataEvent::src_infos_type&) override;

  syn::ListDevicesDataEvent::src_names_type                types_;     //<
  std::vector< syn::ListDevicesDataEvent::src_infos_type > sources_;   //<
};
}   // namespace dnodes::sources::gen_vgen
