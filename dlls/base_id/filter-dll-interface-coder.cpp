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
  bool Filter::Coder1 (
    InfoFilter*    finfo,
    bool        array_to_coder,
    unsigned char*    pointer,
    long        size_pointer)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    LONG l1 = 0;

    unsigned char array_coder[] =
    {
      110, 167, 36, 89, 101, 67, 33, 21, 67, 98,
      210, 67, 61, 29, 121, 17, 13, 221, 167, 18,
      11, 17, 161, 81, 141, 60, 23, 121, 107, 48,
      21, 127, 216, 5, 151, 16, 93, 127, 127, 68,
      31, 117, 30, 67, 161, 17, 153, 210, 137, 28
    };



    //#pragma message( "Debug version" )
    if (pointer == 0)
      return S_OK;

    for ( l1 = 0; l1 < size_pointer; l1++)
    {
      pointer[l1] ^= array_coder[( l1 % sizeof ( array_coder) )];
    }
    return hr;
#endif
  }


  bool Filter::SetCoderOrDecoder (
    InfoFilter* finfo,
    bool array_to_coder)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_array_coder = array_to_coder;
#endif
  }

  bool Filter::EnableProcess (
    InfoFilter* finfo,
    bool enable_process)
  {
    UASSERT_SIGNAL( "failed" );
    return false;
#if 0
    finfo->m_enable_coder = enable_process;
#endif
  }
#endif
}}      // namespace dlls::base_id
