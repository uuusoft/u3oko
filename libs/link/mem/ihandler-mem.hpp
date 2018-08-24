#pragma once
/**
\file       ihandler-mem.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace mem {
/**
  \brief  empty brief
  */
class IHandlerMem
{
  public:
  virtual ~IHandlerMem ()
  {}

  virtual bool update (void* _pmem) const = 0;


  protected:
  IHandlerMem ()
  {}
};

}}}      // namespace libs::link::mem
