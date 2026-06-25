#pragma once
/**
\file       desk-vgen-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace dlls::sources::desk_vgen
{
class SourceImpl final : public ::dlls::sources::gen_lib::ISourceImpl
{
  public:
  SourceImpl ();
  virtual ~SourceImpl ();

  private:
  //  ::dlls::sources::gen_lib::ISourceImpl
  virtual void init_int () override;
  virtual void start_int () override;
  virtual auto stop_int () -> void override;
  virtual void get_sources_int (std::vector< syn::DataSourceInfo >& sources) override;
  virtual void get_raw_data_int (::dlls::sources::gen_lib::syn::pkeys2bufs_type& bufs, ::dlls::sources::gen_lib::syn::tevents_type* events) override;
  virtual void set_cpu_int (::libs::helpers::sys::cpu::CpuExts current_optim) override;
  virtual void update_source_info_int (const syn::SourceImplInfo& info) override;

  void free_int ();

  std::unique_ptr< ICaptureDeskImpl >  impl_;      //<
  ::libs::helpers::mem::IBlockMem::ptr rgb_buf_;   //<
};
}   // namespace dlls::sources::desk_vgen
