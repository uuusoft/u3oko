#pragma once
/**
\file       ipos.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::utils
{
/// Интерфейс для работы с размерами любых объектов в GUI
class IPos
{
  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (IPos)
  typedef int value_type;
  //  IPos interface
  virtual value_type get_x () const = 0;
  virtual value_type get_y () const = 0;
  virtual ptr        clone () const = 0;


  protected:
  virtual ~IPos ()
  {
  }
};
}   // namespace libs::events_gui::utils
