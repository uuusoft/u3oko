#pragma once
/**
\file       irect.hpp
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
class IRect
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IRect);

  virtual ~IRect ()
  {}

  virtual IPos::raw_ptr get_pos () = 0;

  virtual IPos::craw_ptr get_pos () const = 0;

  virtual ISize::raw_ptr get_size () = 0;

  virtual ISize::craw_ptr get_size () const = 0;
};

}}}      // namespace libs::igui_events::utils
