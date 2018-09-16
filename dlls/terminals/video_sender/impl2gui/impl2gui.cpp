/**
\file       impl2gui.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "impl2gui.hpp"
#include "is-empty-frame-helper.hpp"
#include "fill-frame-helper.hpp"

namespace dlls { namespace terminals { namespace video_sender { namespace impl2gui {

Impl2Gui::Impl2Gui ()
{}


Impl2Gui::~Impl2Gui ()
{}


void
Impl2Gui::send_int (const InfoFilter& _finfo, const TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, IVideoBuff::raw_ptr _send_buff)
{
  ILink::ptr _helper = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
  send_frame (_finfo, _info, _helper);
  return;
}


bool
Impl2Gui::fill_frame (const TransformInfo& _info, void* _pmem)
{
  UASSERT (_pmem);
  bool _ret = true;

  try
    {
      auto                      _header = UUU_MEM_CAST<VideoIO*> (_pmem);
      const IVideoBuff::raw_ptr _bbuff  = (**_info.ibuff_)[utils::dbuffs::video::consts::offs::lit];

      CHECK_STATE (_header, "failed, empty header video frame");
      //CHECK_CALL( _header->check(), "failed check header video frame" );

      _header->reset ();
      ++_header->in_.counter_;

      _header->in_.width_  = _bbuff->get_dim_var (dvideo::TypeDimVar::width);
      _header->in_.height_ = _bbuff->get_dim_var (dvideo::TypeDimVar::height);

      const off_buff_type _buff_indxs[] = {
        utils::dbuffs::video::consts::offs::hue,
        utils::dbuffs::video::consts::offs::sat,
        utils::dbuffs::video::consts::offs::lit
      };

      int* _buff_offs[] = {
        &_header->in_.off_buff_h_,
        &_header->in_.off_buff_s_,
        &_header->in_.off_buff_l_
      };

      int _off_buff = _header->off_buffers_;

      for (std::size_t _bindx = 0; _bindx < COUNT_OF (_buff_indxs); ++_bindx)
        {
          IVideoBuff::craw_ptr _buff = (**_info.ibuff_)[_buff_indxs[_bindx]];
          if (!_buff || _buff->get_flag (::utils::dbuffs::TypeFlagsBuff::empty))
            {
              continue;
            }

          void* _dest_buff = ::libs::helpers::mem::move_ptr<void*> (_pmem, _off_buff);

          _header->in_.stride_ = _buff->get_dim_var (dvideo::TypeDimVar::stride);
          *_buff_offs[_bindx]  = _off_buff;

          ::libs::helpers::mem::acopy (
            utils::dbuffs::video::helpers::get_const_data (_buff),
            _dest_buff,
            (*_buff)[::utils::dbuffs::TypeMemVar::size_data]);

          _off_buff += (*_buff)[::utils::dbuffs::TypeMemVar::size_data];
        }
    }
  catch (boost::exception& _e)
    {
      DATA_EXCEPT_LOG (boost::diagnostic_information (_e));
      _ret = false;
    }
  catch (std::exception& _e)
    {
      DATA_EXCEPT_LOG (_e.what ());
      _ret = false;
    }
  UASSERT (_ret);
  return _ret;
}


bool
Impl2Gui::is_empty_frame (const void* _pmem) const
{
  UASSERT (_pmem);
  auto _header = UUU_MEM_CAST<const VideoIO*> (_pmem);
  return _header->in_.is_valid () ? false : true;
}


void
Impl2Gui::send_frame (const InfoFilter& _finfo, const TransformInfo& _info, ILink::ptr _helper)
{
  if (auto _imem = _helper->get_imem ())
    {
      REF_UASSERT_SIGNAL ("failed");

#if 0
      if ( finfo_.last_hmem_.check () )
      {
        if ( !_helper->mem_atomic_call (finfo_.last_hmem_, IsEmptyFrameHelper ( this ) ) )
        {
          //UASSERT_SIGNAL( "failed" );
          return;
        }
      }

      std::size_t _size_mem = sizeof ( VideoIO ) + 16;

      {
        std::size_t   _count_buffs = 0;
        const off_buff_type _buff_indxs[] =
        {
          utils::dbuffs::video::consts::offs::hue,
          utils::dbuffs::video::consts::offs::sat,
          utils::dbuffs::video::consts::offs::lit
        };

        for ( std::size_t _buff_indx = 0; _buff_indx < COUNT_OF ( _buff_indxs); ++_buff_indx )
        {
          IVideoBuff::craw_ptr  _buff = (**_info.ibuff_ )[ _buff_indxs[ _buff_indx ] ];

          if ( !_buff )
          {
            continue;
          }

          if ( _buff->get_flag( utils::dbuffs::TypeFlagsBuff::empty ) )
          {
            continue;
          }

          _size_mem += _buff->get_dim_var( ::utils::dbuffs::TypeMemVar::size_data];
          //_buff->fill( rand() % 255 );//debug
          ++_count_buffs;
        }

        if (0 == _count_buffs)
        {
          XULOG_TRACE("Filter::send_frame::failed:end2", "uuu_video_sender");
          return;
        }

      }

      if ( finfo_.last_hmem_.check () && finfo_.last_hmem_.size_ < _size_mem )
      {
        CHECK_CALL ( _helper->mem_free ( finfo_.last_hmem_ ), "failed, free mem" );
      }

      if ( !finfo_.last_hmem_.check () )
      {
        CHECK_CALL ( _helper->mem_alloc ( _size_mem, finfo_.last_hmem_ ), "failed, alloc mem for send to gui" );
      }

      UASSERT ( finfo_.last_hmem_.check () );
      CHECK_CALL ( _helper->mem_atomic_call ( finfo_.last_hmem_, FillFrameHelper ( this, _info ) ),"failed, call mem_atomic_call" );

      _helper->s1end_msg ( BaseGUIEvent::ptr (
        new ::libs::igui_events::events::MemBlockEvent ( finfo_.last_hmem_, finfo_.rprops_->get_id () )
        ) );
#endif

    }
  else
    {
      if (!fast_buff2gui_)
        {
          fast_buff2gui_ = std::make_shared<::libs::buffs::Buffs> ();
        }

      if (fast_buff2gui_.use_count () <= 1)
        {
          fast_buff2gui_->swap (**_info.ibuff_);

          IEvent::ptr _rmsg;
          auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::igui_events::events::VideoBuffEvent> (_rmsg);
          _dmsg->set_buff (fast_buff2gui_);
          //_dmsg->set_id (_finfo.rprops_->get_id ());
          _helper->send_msg (_rmsg);
        }
    }
  return;
}

}}}}      // namespace dlls::terminals::video_sender::impl2gui
