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
  bool Filter::SetNameCamera (
    InfoFilter* finfo,
    unsigned char* name_camera,
    int len_name_camera)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    TCHAR* temp_p1 = r1einterpret_cast<TCHAR*>(name_camera);
    finfo->name_ = temp_p1;
    return hr;
#endif
  }


  bool Filter::GetNameCamera (
    InfoFilter*  finfo,
    unsigned char*  name_camera,
    int       size_buff,
    int*      len_name_camera)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    int now_len_camera = 0;


    now_len_camera = finfo->name_.length ();

    if ( (name_camera == 0) ||
      ( len_name_camera == 0) ||
      (size_buff <= 0) )
    {
      if ( len_name_camera)
        *len_name_camera = now_len_camera;
      hr = S_OK;
      return hr;
    }

    *len_name_camera = now_len_camera + 1;
    name_camera[0] = '\0';

    if ( (now_len_camera + 1 ) >= size_buff )
    {
      hr = E_FAIL;
      return hr;
    }
    UASSERT_SIGNAL( "failed" );
    //finfo->name_.CopyToStandartString( temp_p1, size_buff );
#endif
  }

  bool Filter::SetIdCamera (InfoFilter* finfo, unsigned long _cid, unsigned long type_camera)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->id_ = _cid;
    finfo->type_ = type_camera;
#endif
  }


  bool Filter::SetColorCamera (InfoFilter* finfo, bool is_color)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_color_camera = is_color;
#endif
  }


  bool Filter::NeedFrameForSpecialCompressSend (InfoFilter* finfo )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_need_special_compress_now = true;
#endif
  }


  bool Filter::UpdateShedulerCamera (
    InfoFilter* finfo,
    unsigned char* data,
    int size_data)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    ::base_functs::mem::copy ( &finfo->m_sheduler_camera[0], data, finfo->m_sheduler_camera.size () * sizeof (finfo->m_sheduler_camera[0] ) );
#endif
  }


  bool Filter::GetIdCamera (InfoFilter* finfo, unsigned long* _cid)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    *_cid = finfo->id_;
#endif
  }


  bool Filter::SetRandomNoise (InfoFilter* finfo, bool enable )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_enable_noise = enable;
#endif
  }


  bool Filter::SetParentObject ( InfoFilter* finfo, ::libs::icore::impl::var1::path::controller::CObj* object )
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->controller_ = object;
#endif
  }
#endif
}}      // namespace dlls::base_id
