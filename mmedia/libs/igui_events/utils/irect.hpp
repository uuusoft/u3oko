#pragma once
/**
\file       irect.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::utils
{
/// Интерфейс для работы с размерами любых объектов в GUI
class IRect
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IRect)

  virtual ~IRect ()
  {
  }
  //  IRect interface
  virtual IPos::raw_ptr   get_pos ()        = 0;
  virtual IPos::craw_ptr  get_pos () const  = 0;
  virtual ISize::raw_ptr  get_size ()       = 0;
  virtual ISize::craw_ptr get_size () const = 0;
};
}   // namespace libs::igui_events::utils
