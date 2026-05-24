#pragma once
/**
\file       ihandler-mem.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_link
*/

namespace libs::link::mem
{
class IHandlerMem
{
  public:
  virtual ~IHandlerMem ()
  {
  }

  //  IHandlerMem interface
  virtual bool update (void*) const = 0;

  protected:
  IHandlerMem ()
  {
  }
};
}   // namespace libs::link::mem
