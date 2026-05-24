#pragma once
/**
\file       pict-vgen-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_pict_vgen
*/

namespace dlls::sources::pict_vgen
{
enum class Image2Frames : std::uint32_t
{
  one     = 0x00,   //<
  scroll  = 0x01,   //<
  unknown = 0xFF    //<
};

Image2Frames image2frame (const std::string& val);

struct LoadedImage final {
  LoadedImage () = default;

  LoadedImage (
    std::int32_t          width,
    std::int32_t          height,
    std::int32_t          bppx,
    syn::IBlockMem::ptr&& data) :
    width_ (width),
    height_ (height),
    bppx_ (bppx),
    data_ (std::move (data))
  {
    U3_CHECK (width_ >= 0 && height_ >= 0 && bppx_ >= 0 && bppx_ <= 8, "invalid parameters");
  }

  LoadedImage (LoadedImage&& src)
  {
    std::swap (width_, src.width_);
    std::swap (height_, src.height_);
    std::swap (bppx_, src.bppx_);
    std::swap (data_, src.data_);
  }

  LoadedImage (const LoadedImage&)            = delete;
  LoadedImage& operator= (const LoadedImage&) = delete;
  LoadedImage& operator= (LoadedImage&&)      = delete;

  ~LoadedImage ()
  {
  }

  std::int32_t        width_  = 0;
  std::int32_t        height_ = 0;
  std::int32_t        bppx_   = 0;
  syn::IBlockMem::ptr data_   = {};
};

class SourceImpl final : public ::dlls::sources::gen_lib::ISourceImpl
{
  public:
  SourceImpl ();
  virtual ~SourceImpl ();

  private:
  //  internal types
  using type_files_type       = std::vector< std::uint32_t >;                                   //<
  using exts_type             = std::array< std::uint32_t, 256 >;                               //<
  using ptime_type            = boost::posix_time::ptime;                                       //<
  using sources_type          = std::vector< ::libs::imdata_events::events::DataSourceInfo >;   //<
  using val_bufs_storage_type = std::pair< std::int32_t, LoadedImage >;                         //<
  using bufs_storage_type     = std::unordered_map< std::string, val_bufs_storage_type >;       //<

  //  ::dlls::sources::gen_lib::ISourceImpl
  virtual void init_int () override;
  virtual void start_int () override;
  virtual void stop_int () override;
  virtual void get_sources_int (SourceImpl::sources_type& sources) override;
  virtual void get_raw_data_int (syn::pkeys2bufs_type& bufs, syn::tevents_type* events) override;
  virtual void set_cpu_int (syn::CpuExts current_optim) override;
  virtual void update_source_info_int (const syn::SourceImplInfo& info) override;

  void        stop_and_free ();
  void        refresh_files ();
  void        print_images2buf (utils::dbufs::video::IVideoBuf::ptr& genimage);
  void        sync_internal_structures ();
  LoadedImage load_image2buf (const std::string& name);
  bool        is_image_valid (const std::string& name);

  std::string                           name_file_;               //<
  ::libs::helpers::files::NodeEnumFiles enum_files_;              //<
  type_files_type                       type_files_;              //<
  std::uint64_t                         indx_image_file_;         //<
  ptime_type                            time_last_change_file_;   //<
  exts_type                             exts_;                    //<
  syn::SourceImplInfo                   source_impl_info_;        //<
  Image2Frames                          image2frame_style_;       //<
  bufs_storage_type                     loaded_images_;           //<
  float                                 off_first_image_;         //<
  syn::IHardwareCapture::ptr            icapture_;                //<
};
}   // namespace dlls::sources::pict_vgen
