#pragma once
/**
\file       ipos.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils {
/**
\brief  Интерфейс для работы с размерами любых объектов в GUI.
*/
class IPos
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IPos);
  typedef int value_type;
  //  IPos interface
  virtual value_type get_x () const = 0;
  virtual value_type get_y () const = 0;
  virtual ptr clone () const = 0;


  protected:
  virtual ~IPos ()
  {}
};

}}}      // namespace libs::igui_events::utils
