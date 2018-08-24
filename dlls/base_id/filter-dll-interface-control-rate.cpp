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
  bool Filter::SetFullStopData (InfoFilter* finfo, bool enable_full_stop )
  {
    finfo->m_enable_full_stop = enable_full_stop;
    //finfo->m_last_time_detect = finfo->time_server_.get ();
    //finfo->m_last_time = finfo->time_server_.get ();
    finfo->m_tail = 0.0f;
    return true;
  }


  bool Filter::FindMove (InfoFilter* finfo )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    double    full_time_to_detect = 0.0;
    long long i64_3 = 0;
    double    d1 = 0.0;
    double    d2 = 0.0;



    i64_3 = finfo->time_server_.get ();
    finfo->m_is_send_about_stop_detect = false;

    TEMP_DISABLED_UASSERT(0);
#if 0
    //смотрим, если данное сообщение первое и стоит запись только по детектору
    //надо скорректировать время последнего, якобы обрботанного, кадра
    if ( (finfo->m_sheduler_camera[finfo->m_offset_in_time] & 0x0F) == ::dlls::sources::windows_dshow_vgen::path::dshow::sct1OnlyEvents)
    {
      //рассчтиваем время в секундах, прошедшее с последний сработки детектора
      d1 = s1tatic_cast<double>(i64_3);
      d2 = s1tatic_cast<double>(finfo->m_last_time_detect );

      full_time_to_detect = d1 - d2;

      if (full_time_to_detect < 0.0)
      {
        full_time_to_detect = 1000.0;
      }
      else
      {
        full_time_to_detect = full_time_to_detect / 1000.0;
      }
      //чтобы начать писать сразу, указываем системе, что мы, обработали кадр достаточно давно
      if (full_time_to_detect >= finfo->m_default_post_time_detect[finfo->m_offset_in_zone] )
      {
        finfo->m_last_time = s1tatic_cast<long long>(finfo->time_server_.get () - (1.0 / finfo->m_array_frame_rate[finfo->m_offset_in_zone][ ::dlls::base_id::consts::off_eventl_compressed] ) * 1000);
      }
    }
#endif
    finfo->m_last_time_detect = finfo->time_server_.get ();
#endif
  }
#if 0
  bool Filter::UpdateInfoForZone (
    InfoFilter* finfo,
    int index_zone,
    ::libs::ievents::props::VideoCodecProp* array_cinfo_,
    float* array_frame_rate,
    bool enable_video_network,
    bool enable_special_video_network,
    bool use_standart_compress_network)
  {
    int i1 = 0;

    finfo->m_enable_video_network[index_zone] = enable_video_network;
    finfo->m_enable_special_video_network[index_zone] = enable_special_video_network;
    finfo->use_compress_net[index_zone] = use_standart_compress_network;

    //04.08.2016 corrected max bound from 3 to 4
    for (i1 = 0; i1 < 4; i1++)
    {
      finfo->m_info_video_compress[index_zone][i1] = array_cinfo_[i1];
    }
    //04.08.2016 corrected max bound from 4 to 5
    for (i1 = 0; i1 < 5; i1++)
    {
      finfo->m_array_frame_rate[index_zone][i1] = array_frame_rate[i1];
    }
    // 19.01.2016
    if (0 == index_zone )
    {
      finfo->view_fps_.set_fps ( array_frame_rate[ ::dlls::base_id::consts::off_view] );
    }
  }
#endif

  bool Filter::IsMove (
    InfoFilter*  finfo,
    bool*     is_move )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    double    full_time_to_detect = 0.0;
    long long i64_5 = 0;
    double    d1 = 0.0, d2 = 0.0;

    i64_5 = finfo->time_server_.get ();

    d1 = s1tatic_cast<double>(i64_5 );
    d2 = s1tatic_cast<double>(finfo->m_last_time_detect );

    full_time_to_detect = d1 - d2;

    if (full_time_to_detect < 0.0)
    {
      full_time_to_detect = 1000.0;
    }
    else
    {
      full_time_to_detect = full_time_to_detect / 1000.0;
    }

    // 21.11.2016
    *is_move = full_time_to_detect <= finfo->m_default_post_time_detect[finfo->m_offset_in_zone];
    /*
    if( full_time_to_detect <= finfo->m_default_post_time_detect[ finfo->m_offset_in_zone ] )
    {
    *is_move = true;
    }
    else
    {
    *is_move = false;
    };
    /**/
    return hr;
#endif
  }
#endif
}}      // namespace dlls::base_id
