/**
\file       pict-vgen-source-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_pict_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "pict-vgen-source-impl.hpp"

namespace dlls::sources::pict_vgen
{
Image2Frames
image2frame (const std::string& val)
{
  static const std::unordered_map< std::string, const Image2Frames > str2image2frame_vals = {
    { "one", Image2Frames ::one },
    { "scroll", Image2Frames::scroll }
  };

  const auto finger = str2image2frame_vals.find (val);
  if (str2image2frame_vals.end () == finger)
  {
    return Image2Frames ::one;
  }
  return finger->second;
}


SourceImpl::SourceImpl () :
  indx_image_file_ (0),
  image2frame_style_ (Image2Frames::scroll),
  off_first_image_ (0.0F),
  icapture_ (std::make_shared< syn::IHardwareCapture > ())
{
  time_last_change_file_ = boost::posix_time::microsec_clock::universal_time ();
  exts_.fill (0);
  // image2frame_style_ = Image2Frames::one;   // debug
}


SourceImpl::~SourceImpl ()
{
  stop_and_free ();
}


void
SourceImpl::print_images2buf (utils::dbufs::video::IVideoBuf::ptr& genimage)
{
  const auto capwidth  = U3_CAST_INT32 (source_impl_info_.capture_props_->capi_.width_);
  const auto capheight = U3_CAST_INT32 (source_impl_info_.capture_props_->capi_.height_);
  const auto capstride = ::libs::helpers::mem::get_align64 (capwidth * 3);
  const auto size_copy = capheight * capstride;

  std::ranges::for_each (loaded_images_, [] (auto& val) { val.second.first += 1; });

  genimage->buf_alloc (
    ::utils::dbufs::video::AllocBufInfo (
      capwidth,
      capheight,
      capstride,
      ::libs::helpers::uids::minor::id_val::rgb24));

  ::utils::dbufs::video::helpers::override_data (*genimage, 0, size_copy);

  auto         dstbuf   = genimage->get_buf ();
  std::int32_t cpwidth  = 0;
  auto         offfirst = U3_CAST_INT32 (off_first_image_);

  const auto   folder         = ::libs::helpers::files::update_home_folder (srcimpinfo_.props_->ext_vals_.at (consts::param_keys::picter_folder));
  auto         loc_image_indx = indx_image_file_;
  std::int32_t cycle_counter  = 0;
  while (++cycle_counter)
  {
    loc_image_indx             = loc_image_indx % enum_files_.files_.size ();
    const auto image_file_name = ::libs::helpers::files::make_path (folder, enum_files_.files_[loc_image_indx].name_);
    if (!is_image_valid (image_file_name))
    {
      ++indx_image_file_;
      break;
    }

    auto curimage = loaded_images_.find (image_file_name);
    if (loaded_images_.end () == curimage)
    {
      auto resload = load_image2buf (image_file_name);
      if (!resload.data_)
      {
        U3_LOG_DATA_ERROR ("failed load image" + TOLOG (image_file_name));
        ++indx_image_file_;
        break;
      }

      const auto insertres = loaded_images_.emplace (
        std::make_pair (image_file_name, std::make_pair (0, std::move (resload))));

      curimage = insertres.first;
    }

    if (loaded_images_.end () == curimage)
    {
      U3_LOG_DATA_ERROR ("failed insert image" + TOLOG (image_file_name));
      ++indx_image_file_;
      break;
    }

    curimage->second.first = 0;

    const auto& image_info   = curimage->second.second;
    const auto  image_width  = image_info.width_;
    const auto  image_height = image_info.height_;
    const auto  srcstride    = image_width * image_info.bppx_;
    const auto  srcoff       = offfirst * image_info.bppx_;
    const auto  cpstride     = std::min< std::int32_t > (srcstride - srcoff, capstride - cpwidth * 3);

    if (offfirst >= image_width)
    {
      offfirst -= image_width;
      off_first_image_ -= image_width;
      ++indx_image_file_;
      ++loc_image_indx;
      continue;
    }

    if (image_height != capheight)
    {
      U3_LOG_DATA_ERROR ("error in implementation" + VTOLOG (capwidth) + VTOLOG (image_height));
      ++indx_image_file_;
      ++loc_image_indx;
      break;
    }

    for (std::int32_t iy = 0; iy < image_height; ++iy)
    {
      auto* srcline = image_info.data_->get () + iy * srcstride + offfirst * image_info.bppx_;
      auto* dstline = dstbuf + cpwidth * 3 + iy * capstride;
      U3_CHECK (srcline, "get scan file rgb24 image" + VTOLOG (iy));
      ::libs::helpers::mem::u3copy (srcline, dstline, cpstride);
    }

    cpwidth += image_width - offfirst;
    offfirst = 0;

    if (cpwidth >= capwidth ||
        ::dlls::sources::pict_vgen::Image2Frames::one == image2frame_style_)
    {
      break;
    }
    ++loc_image_indx;
  }

  std::erase_if (
    loaded_images_,
    [] (const auto& val) { return val.second.first >= consts::max_count_cycle_store_image; });
}


bool
SourceImpl::is_image_valid (const std::string& name)
{
  int width { 0 };
  int height { 0 };
  int bbpx { 0 };
  return 1 == stbi_info (name.c_str (), &width, &height, &bbpx) && width > 0 && height > 0 && bbpx > 0;
}


LoadedImage
SourceImpl::load_image2buf (const std::string& name)
{
  using stb_image_type = helpers::ResourceHolder< void, stbi_image_free >;

  const auto   capheight  = U3_CAST_INT32 (source_impl_info_.capture_props_->capi_.height_);
  std::int32_t filewidth  = 0;
  std::int32_t fileheight = 0;
  std::int32_t bbpx       = 0;

  stb_image_type data (stbi_load (name.c_str (), &filewidth, &fileheight, &bbpx, 3));
  if (!data || fileheight <= 0 || filewidth <= 0 || bbpx != 3)
  {
    U3_LOG_DATA_ERROR ("failed load image" + VTOLOG (fileheight) + VTOLOG (filewidth) + VTOLOG (bbpx) + TOLOG (name));
    return LoadedImage ();
  }

  const auto propwidth = U3_CAST_FLOAT (capheight) / U3_CAST_FLOAT (fileheight);
  const auto reswidth  = fileheight == capheight ? capheight : U3_CAST_INT32 (filewidth * propwidth);
  const auto resstride = reswidth * 3;
  const auto ressize   = capheight * resstride;

  syn::IBlockMem::ptr buf = srcimpinfo_.links_props_->pdriver2mem_->impl ()->alloc (0);
  buf->resize (ressize);

  stbir_resize_uint8_srgb (
    ::libs::helpers::casts::reinterpret_cast_helper< unsigned char* > (*data),
    filewidth,
    fileheight,
    filewidth * bbpx,
    buf->get (),
    reswidth,
    capheight,
    resstride,
    STBIR_RGB);

  buf->set_data_size (ressize);
  return { reswidth, capheight, bbpx, std::move (buf) };
}


void
SourceImpl::refresh_files ()
{
  const std::string loc_mask (
    "?.bmp?.cut?.dds?.exr?.g3?.gif?.hdr?.ico?.iff?.ibm?.j2k?.j2c?.jng?\
          .jp2?.jpg?.jif?.jpeg?.jpe?.koa?.mng?.pbm?.pcd?.pcx?.pgm?.png?.ppm?\
              .psd?.ras?.sgi?.tga?.targa?.tif?.tiff?.wap?.wbmp?.wbm?.xbm?\
                  .xpm?.djvu?");

  enum_files_.clear ();

  syn::DefaultFileMask check_cond (loc_mask);
  const auto           picters_folder = ::libs::helpers::files::update_home_folder (srcimpinfo_.props_->ext_vals_.at (consts::param_keys::picter_folder));

  U3_LOG_DATA_DEV ("begin refresh files in" + TOLOG (picters_folder));
  ::libs::helpers::files::get_files (
    picters_folder,
    enum_files_,
    { ::libs::helpers::files::IncludeSubFolders::disabled,
      ::libs::helpers::files::IncludeFiles::enabled,
      ::libs::helpers::files::Recursives::disabled,
      ::libs::helpers::files::Sorting::last_write_time },
    check_cond);

  if (enum_files_.files_.empty ())
  {
    indx_image_file_ = 0;
  }
  else
  {
    srand (std::chrono::duration_cast< std::chrono::milliseconds > (std::chrono::high_resolution_clock::now ().time_since_epoch ()).count ());
    indx_image_file_ = rand () % enum_files_.files_.size ();

    ::libs::helpers::utils::check_bound< std::uint64_t > (
      indx_image_file_,
      0llu,
      U3_CAST_UINT64 (enum_files_.files_.size () - 1));
  }
  U3_LOG_DATA_DEV ("refresh files in" + TOLOG (picters_folder) + VTOLOG (enum_files_.files_.size ()) + VTOLOG (indx_image_file_));
}


void
SourceImpl::sync_internal_structures ()
{
  loaded_images_.clear ();
  off_first_image_ = 0.0F;
  refresh_files ();
  image2frame_style_ = image2frame (srcimpinfo_.props_->ext_vals_.at (consts::param_keys::image2frame));
}


void
SourceImpl::stop_and_free ()
{
  stop ();
}
}   // namespace dlls::sources::pict_vgen
