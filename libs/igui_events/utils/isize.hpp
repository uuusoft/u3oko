#pragma once
/**
\file       isize.hpp
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
class ISize
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISize);
  typedef int value_type;
  //  ISize interface
  virtual value_type get_width () const = 0;
  virtual value_type get_height () const = 0;
  virtual ptr clone () const = 0;


  protected:
  virtual ~ISize ()
  {}


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    return;
  }
};

}}}      // namespace libs::igui_events::utils
