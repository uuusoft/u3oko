//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       is-empty-frame-helper.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief    
*/

namespace dlls { namespace terminals { namespace video_sender { namespace impl2gui {

#if 0
/**
\brief  empty brief
*/
class IsEmptyFrameHelper : public ::libs::link::mem::IHandlerMem
{
  public:
  IsEmptyFrameHelper (Filter* _obj) :
    obj_ (_obj)
  {}

  virtual ~IsEmptyFrameHelper ()
  {}

  virtual bool
  update (void* _pmem) const override
  {
    return obj_->is_empty_frame (_pmem);
  }


  private:
  mutable Filter* obj_;      //< ???
};
#endif

}}}}      // namespace dlls::terminals::video_sender::impl2gui
