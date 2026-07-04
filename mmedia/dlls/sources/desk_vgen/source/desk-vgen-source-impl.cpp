/**
\file       desk-vgen-source-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.06.2016
\project    u3_desk_vgen
*/
#include "desk-vgen-includes_int.hpp"
#include "desk-vgen-source-impl.hpp"

namespace dlls::sources::desk_vgen
{
SourceImpl::SourceImpl ()
{
#ifdef U3_OS_WIN32_DESKTOP
  impl_ = std::make_unique< impls::win32::CaptureDeskImplWin32 > ();
#elif defined(U3_OS_ANDROID)
  impl_ = std::make_unique< impls::android::CaptureDeskImplAndroid > ();
#elif defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
  // impl_ = std::make_unique< impls::linux::x11::CaptureDeskImplLinux > ();
  impl_ = std::make_unique< impls::linux::wl::CaptureDeskImplLinux > ();
#elif defined(U3_OS_MACX_DESKTOP)
  impl_ = std::make_unique< impls::mac::CaptureDeskImplMac > ();
#else
#  pragma error "os selected";
#endif
}


SourceImpl::~SourceImpl ()
{
  free_int ();
}


void
SourceImpl::init_int ()
{
}


void
SourceImpl::start_int ()
{
}


void
SourceImpl::stop_int ()
{
}


void
SourceImpl::get_sources_int (std::vector< syn::DataSourceInfo >& sources)
{
  sources.emplace_back (
    "screen-camera",
    libs::events_media::events::DataSources::video,
    0,
    1);
}


void
SourceImpl::get_raw_data_int (
  ::dlls::sources::gen_lib::syn::pkeys2bufs_type& bufs,
  ::dlls::sources::gen_lib::syn::tevents_type*    events)
{
  auto& buf = (*bufs)[::utils::dbufs::video::consts::offs::raw];
  buf->set_flag (::utils::dbufs::BufFlags::empty, true);
  if (!rgb_buf_)
  {
    rgb_buf_ = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (0);
  }

  CaptureDeskInfo capinfo (rgb_buf_);
  impl_->get_buf (srcimpinfo_, capinfo);

  if (rgb_buf_->get ())
  {
    buf->buf_alloc (
      ::utils::dbufs::video::AllocParams (
        capinfo.width_dest_,
        capinfo.height_dest_,
        capinfo.stride_dest_,
        ::libs::utility::uids::minor::id_val::rgb24,
        utils::dbufs::video::DimChecks::disable));

    U3_CHECK (rgb_buf_->get_size () >= capinfo.size_dest_data_, "buf too small");
    ::libs::utility::mem::u3copy (rgb_buf_->get (), buf->get_buf (), capinfo.size_dest_data_);
    buf->set_flag (::utils::dbufs::BufFlags::empty, false);
    buf->set_mem_var (::utils::dbufs::MemVars::size_data, capinfo.size_dest_data_);
  }
}


void
SourceImpl::set_cpu_int (::libs::utility::sys::cpu::CpuExts current_optim)
{
}


void
SourceImpl::free_int ()
{
  stop ();
}


void
SourceImpl::update_source_info_int (const syn::SourceImplInfo& info)
{
}
}   // namespace dlls::sources::desk_vgen
