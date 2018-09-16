//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       fill-frame-helper.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/

namespace dlls { namespace terminals { namespace video_sender { namespace impl2gui {

#if 0
/**
\brief  empty brief
*/
class FillFrameHelper : public ::libs::link::mem::IHandlerMem
{
  public:
  FillFrameHelper (Filter* _obj, TransformInfo& _info) :
    obj_ (_obj),
    info_ (_info)
  {}

  virtual ~FillFrameHelper ()
  {}

  virtual bool
  update (void* _pmem) const override
  {
    return obj_->fill_frame (info_, _pmem);
  }


  private:
  mutable Filter* obj_;       //<  ???
  TransformInfo&  info_;      //<  ???
};
#endif

}}}}      // namespace dlls::terminals::video_sender::impl2gui
