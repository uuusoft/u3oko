#pragma once
/**
\file       source-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.06.2016.
\copyright  www.uuusoft.com
\project    uuu_gen_lib
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_lib {
/**
\brief  empty brief
*/
struct SourceInfo
{
  SourceInfo (
    const VideoDriverProp::craw_ptr        _props         = nullptr,
    const VideoDriverCaptureProp::craw_ptr _capture_props = nullptr,
    const LinksVideoDriverProp::craw_ptr   _links_props   = nullptr) :

    props_ (_props),
    capture_props_ (_capture_props),
    links_props_ (_links_props)
  {}

  VideoDriverProp::craw_ptr        props_;              //< ???
  VideoDriverCaptureProp::craw_ptr capture_props_;      //< ???
  LinksVideoDriverProp::craw_ptr   links_props_;        //< ???
};

}}}      // namespace dlls::sources::gen_lib
