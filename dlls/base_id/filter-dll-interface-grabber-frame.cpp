//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       16.07.2018
\copyright  www.uuusoft.com
\project    uuu_base_id_dll
\brief      empty brief.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace base_id {
#if 0
  bool Filter::EnableGrabber (InfoFilter* finfo, bool enable_grabber)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_enable_grabber = enable_grabber;
#endif
  }


  bool Filter::EnableAllwasGrabber (InfoFilter* finfo, bool enable_grabber)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_enable_allwas_grabber = enable_grabber;
#endif
  }


  bool Filter::IsEnableGrabber (InfoFilter* finfo, bool *enable_grabber)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    *enable_grabber = finfo->m_enable_grabber;
#endif
  }


  bool  Filter::get_buff_ext (InfoFilter* finfo, unsigned char* out_buffer, int *size_buffer)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    int need_size = 0;
    int max_size = 0;

    max_size = *size_buffer;
    *size_buffer = 0;

    if (finfo->m_enable_grabber == false )
    {
      UASSERT_SIGNAL( "failed" );
      hr = E_FAIL;
      return hr;
    }

    if (0 >= finfo->last_buff_->size_data_ )
    {
      *size_buffer = 0;
      return hr;
    }

    //creating header for buffer - struct utils::dbuffs::CBuff
    need_size = finfo->last_buff_.size_data_ + sizeof (utils::dbuffs::CBuff );

    //копируем содержимое буфера в указанный 
    if ( (out_buffer) && ( max_size >= need_size ) )
    {
      if (finfo->last_buff_.m_data)
      {
        // 27.03.2016
        memset (out_buffer, 0, sizeof (utils::dbuffs::CBuff ) );

        utils::dbuffs::video::IVideoBuff::raw_ptr temp_header = r1einterpret_cast<utils::dbuffs::video::IVideoBuff::raw_ptr>(out_buffer);

        // 27.03.2016
        //const_cast<unsigned long&>( temp_header->bin_size_ ) = sizeof( utils::dbuffs::CBuff );
        const_cast<unsigned char*&>( temp_header->m_data) = 0;
        const_cast<int&>( temp_header->size_buffer_ ) = need_size;
        const_cast<int&>( temp_header->size_data_ ) = finfo->last_buff_.size_data_;
        const_cast<int&>( temp_header->offset_data_ ) = sizeof (utils::dbuffs::CBuff );

        temp_header->get_info().major_  = finfo->last_buff_.einfo_.major_;
        temp_header->get_format() = finfo->last_buff_.einfo_.minor_;
        temp_header->get_info().state_  = utils::dbuffs::tsbFill;???
        //temp_header->get_info().reserve1_ = 0;
        //temp_header->get_info().reserve2_ = 0;
        temp_header->get_info().format_ = finfo->last_buff_.einfo_.format_;
        //temp_header->get_info().count_using_ = true;

        temp_header->einfo_ = finfo->last_buff_.einfo_;

        // 27.03.2016 comment
        //04.07.2016
        //temp_header->get_info().events_ = finfo->last_buff_.einfo_.events_;

        if (out_buffer + sizeof (utils::dbuffs::CBuff ) != finfo->last_buff_.m_data)
        {
          ::base_functs::mem::copy (out_buffer + sizeof (utils::dbuffs::CBuff ), finfo->last_buff_.m_data, finfo->last_buff_.size_data_ );
        }
        else
        {
          UASSERT_SIGNAL( "failed" );
          memmove (out_buffer + sizeof (utils::dbuffs::CBuff ), finfo->last_buff_.m_data, finfo->last_buff_.size_data_ );
        }

        const_cast<int&>(finfo->last_buff_.size_data_ ) = 0;
        *size_buffer = need_size;
      }
      else
      {
        hr = S_FALSE;
        *size_buffer = 0;
      }
    }
#endif
  }


  bool  Filter::SaveFrameToFile (InfoFilter* finfo, char* name_file )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_path_to_saved_file = name_file;
    finfo->m_now_saved_to_file = true;
#endif
  }

  
  bool  Filter::SaveFrameToFileNow (
    InfoFilter*    finfo,
    const std::string&    name_file,
    std::string&      zagolovok_frame )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    base_functs::mem::CCharBlock  temp_image;
    std::string         _tbuff1;
    std::string         _tbuff3;


    if (finfo->last_buff_.m_data)
    {
      if (zagolovok_frame.length () <= 0)
      {
        _tbuff3.clear ();
        _tbuff1.clear ();

        zagolovok_frame = _tbuff1;

        if ( core::path::todp1SYSTEMTIME == finfo->last_buff_.einfo_.events_[utils::dbuffs::video::consts::offs::off_time_view_arc_frame].get_type_info () )
        {
          _tbuff3 = ::libs::helpers::strings::time2string (
            finfo->last_buff_.einfo_.events_[utils::dbuffs::video::consts::offs::off_time_view_arc_frame].get ( core::path::todp1SYSTEMTIME).systime_ );

          UASSERT_SIGNAL( "failed" );
          //_tbuff1 = _tbuff3 + " Camera : " + ToString( finfo->id_ );
        }
      }

      UASSERT_SIGNAL( "failed" );
#if 0
      if( SUCCEEDED( CreateImageBMPFile4x3( 
        temp_image, 
        finfo->last_buff_.m_data, 
        finfo->last_buff_.size_data_, 
        finfo->last_buff_.einfo_.minor_,
        finfo->last_buff_.einfo_.video_.width_,
        finfo->last_buff_.einfo_.video_.height_,
        zagolovok_frame, 
        1.0f ) ) )
      {
        icore::files::SaveDataToFile (name_file, temp_image.get (), temp_image.byte_size (), 0);
      }
#endif
    }
#endif
  }


  bool Filter::GetSizeData (InfoFilter* finfo, int* size_data)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    *size_data = 0;

    if (0 < finfo->last_buff_.size_data_ )
    {
      *size_data = finfo->last_buff_.size_data_ + sizeof (utils::dbuffs::CBuff );
    }
#endif
  }
#endif

}}      // namespace dlls::base_id
