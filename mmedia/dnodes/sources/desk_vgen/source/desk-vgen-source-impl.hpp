#pragma once
/**
\file       desk-vgen-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace dnodes::sources::desk_vgen
{
class SourceImpl final : public ::dnodes::sources::gen_lib::ISourceImpl
{
  public:
  SourceImpl ();
  virtual ~SourceImpl ();

  private:
  //  ::dnodes::sources::gen_lib::ISourceImpl
  virtual auto init_int () -> void override;
  virtual auto start_int () -> void override;
  virtual auto stop_int () -> void override;
  virtual auto get_sources_int (std::vector< syn::DataSourceInfo >&) -> void override;
  virtual auto get_raw_data_int (syn::pkeys2bufs_type&, syn::tevents_type*) -> void override;
  virtual auto set_cpu_int (syn::CpuExts) -> void override;
  virtual auto update_source_info_int (const syn::SourceImplInfo&) -> void override;

  void free_int ();

  std::unique_ptr< ICaptureDeskImpl >  impl_;      //<
  ::libs::utility::mem::IBlockMem::ptr rgb_buf_;   //<
};
}   // namespace dnodes::sources::desk_vgen
