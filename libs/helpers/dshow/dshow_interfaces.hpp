#pragma once
/**
\file       dshow_interfaces.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017.
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/
// old shit
namespace libs { namespace helpers { namespace dshow {
#if 0
#if defined(UUU_OS_WIN32_DESKTOP)
static const utils::cuuid IID_IReciverData ({ 0x69, 0x75, 0xe2, 0x4c, 0x4f, 0x23, 0x4f, 0x2a, 0xad, 0x96, 0xce, 0x3d, 0x97, 0x70, 0xbe, 0x13 });
/**
  \brief  Интерфейс для работы с нашим фильтром в настоящем графе DirectShow (uuu_dshow)
  */
DECLARE_INTERFACE_ (IReciverData, IUnknown)
{
  STDMETHOD (get_buff_ext)
  (keys2buffs_ptr_type & _buffs) PURE;

  STDMETHOD (get_time_last_frame_ext)
  (long long* time) PURE;

  STDMETHOD (set_prop_ext)
  (VideoDriverProp::craw_ptr _props, VideoDriverCaptureProp::craw_ptr _capture_props, LinksVideoDriverProp::craw_ptr _links_props) PURE;
};


static const utils::cuuid IID_ICPU ({ 0x1b, 0x4a, 0xda, 0xac, 0xec, 0x41, 0x46, 0x2a, 0x9d, 0xdd, 0x3f, 0x81, 0x6b, 0x57, 0x75, 0xf4 });
/**
  \brief  old shit
  */
DECLARE_INTERFACE_ (ICPU, IUnknown)
{
  STDMETHOD (set_cpu_ext)
  (unsigned long using_cpu) PURE;
};

#endif
#endif
}}}      // namespace libs::helpers::dshow
