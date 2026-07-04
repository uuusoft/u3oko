/**
\file       impl2gui.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/
#include "../video-sender-includes_int.hpp"
#include "impl2gui.hpp"
#include "is-empty-frame-helper.hpp"
#include "fill-frame-helper.hpp"

namespace dlls::terminals::video_sender::impl2gui
{
void
Impl2Gui::send_int (
  const InfoFilter&                    finfo,
  const syn::TransformInfo&            info,
  const syn::Buff2ModuleInfo::craw_ptr minfo,
  syn::IVideoBuf::raw_ptr              send_buf)
{
  ::libs::link::ILink::ptr helper = ::libs::iproperties::helpers::get_prop_links ()->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
  if (!helper)
  {
    U3_LOG_DATA_WRN ("skip send msg to gui" + VTOLOG (finfo.count_frames_) + VTOLOG (send_buf->get_dim_var (utils::dbufs::video::Dims::height)));
    return;
  }

  send_frame (finfo, info, helper);
}


auto
Impl2Gui::fill_frame (const syn::TransformInfo& info, void* pmem) -> bool
{
  U3_ASSERT (pmem);
  bool ret = true;

  try
  {
    auto*      header = ::libs::utility::casts::reinterpret_cast_helper< ::modules::mgui::appl::io::VideoIO* > (pmem);
    const auto bbuf   = (**info.ibuf_)[utils::dbufs::video::consts::offs::lit];

    U3_CHECK (header, "empty header video frame");
    // U3_CHECK( header->check(), "check header video frame" );

    header->reset ();
    ++header->in_.counter_;

    header->in_.width_  = bbuf->get_dim_var (::utils::dbufs::video::Dims::width);
    header->in_.height_ = bbuf->get_dim_var (::utils::dbufs::video::Dims::height);

    const ::utils::dbufs::video::consts::offs::off_buf_type buf_indxs[] = {
      utils::dbufs::video::consts::offs::hue,
      utils::dbufs::video::consts::offs::sat,
      utils::dbufs::video::consts::offs::lit
    };

    std::int32_t* buf_offs[] = {
      &header->in_.off_buf_h_,
      &header->in_.off_buf_s_,
      &header->in_.off_buf_l_
    };

    int off_buf = header->off_bufs_;

    for (std::size_t bindx = 0; bindx < std::size (buf_indxs); ++bindx)
    {
      auto buf = (**info.ibuf_)[buf_indxs[bindx]];
      if (!buf || buf->get_flag (::utils::dbufs::BufFlags::empty))
      {
        continue;
      }

      void* dest_buf = ::libs::utility::mem::move_ptr< void* > (pmem, off_buf);

      header->in_.stride_ = buf->get_dim_var (::utils::dbufs::video::Dims::stride);
      *buf_offs[bindx]    = off_buf;

      ::libs::utility::mem::u3copy (utils::dbufs::video::helpers::get_const_data (buf), dest_buf, (*buf)[::utils::dbufs::MemVars::size_data]);
      off_buf += (*buf)[::utils::dbufs::MemVars::size_data];
    }
  }
  catch (boost::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (boost::diagnostic_information (excpt));
    ret = false;
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (excpt.what ());
    ret = false;
  }
  return ret;
}


auto
Impl2Gui::is_empty_frame (const void* pmem) const -> bool
{
  U3_ASSERT (pmem);
  const auto* header = ::libs::utility::casts::reinterpret_cast_helper< const ::modules::mgui::appl::io::VideoIO* > (pmem);
  return header->in_.is_valid () ? false : true;
}


void
Impl2Gui::send_frame (
  const InfoFilter&               finfo,
  const syn::TransformInfo&       info,
  const ::libs::link::ILink::ptr& helper)
{
  if (U3_MARK_UNUSED auto imem = helper->get_imem ())
  {
    U3_ASSERT_SIGNAL ("failed");
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    if (finfo_.last_hmem_.check ())
    {
      if (!helper->mem_atomic_call (finfo_.last_hmem_, IsEmptyFrameHelper (this)))
      {
        return;
      }
    }

    std::size_t size_mem = sizeof (::modules::mgui::appl::io::VideoIO) + 16;
    {
      std::size_t count_bufs = 0;

      const ::utils::dbufs::video::consts::offs::off_buf_type buf_indxs[] = {
        utils::dbufs::video::consts::offs::hue,
        utils::dbufs::video::consts::offs::sat,
        utils::dbufs::video::consts::offs::lit
      };

      for (std::size_t buf_indx = 0; buf_indx < std::size (buf_indxs); ++buf_indx)
      {
        auto buf = (**info.ibuf_)[buf_indxs[buf_indx]];
        if (!buf)
        {
          continue;
        }
        if (buf->get_flag (utils::dbufs::BufFlags::empty))
        {
          continue;
        }

          size_mem += buf->get_dim_var( ::utils::dbufs::MemVars::size_data];
          //buf->fill( rand() % 255 );//debug
          ++count_bufs;
      }

      if (0 == count_bufs)
      {
        return;
      }
    }

    if (finfo_.last_hmem_.check () && finfo_.last_hmem_.size_ < size_mem)
    {
      U3_CHECK (helper->mem_free (finfo_.last_hmem_), "free mem");
    }

    if (!finfo_.last_hmem_.check ())
    {
      U3_CHECK (helper->mem_alloc (size_mem, finfo_.last_hmem_), "alloc mem for send to gui");
    }

    U3_ASSERT (finfo_.last_hmem_.check ());
    U3_CHECK (helper->mem_atomic_call (finfo_.last_hmem_, FillFrameHelper (this, info)), "call mem_atomic_call");

    helper->s1end_msg (BaseGUIEvent::ptr (
      new ::libs::events_gui::events::MemBlockEvent (finfo_.last_hmem_, finfo_.rprops_->get_id ())));
#endif
  }
  else
  {
    if (!fast_buf2gui_)
    {
      fast_buf2gui_ = std::make_shared< ::libs::bufs::Bufs > ();
    }

    if (fast_buf2gui_.use_count () <= 1)
    {
      fast_buf2gui_->swap (**info.ibuf_);

      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::iproperties::helpers::create_event< ::libs::events_gui::events::VideoBufEvent > (rmsg);

      dmsg->set_buf (fast_buf2gui_);
      // dmsg->set_id (finfo.rprops_->get_id ());
      helper->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
    }
  }
}
}   // namespace dlls::terminals::video_sender::impl2gui
