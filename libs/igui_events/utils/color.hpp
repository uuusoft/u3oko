#pragma once
/**   
\file       color.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils {
/**
\brief  empty brief
*/
class Color
{
  public:
  explicit Color (unsigned short _r = 0, unsigned short _g = 0, unsigned short _b = 0) :
    r_ (_r),
    g_ (_g),
    b_ (_b)
  {}

  unsigned short
  get_r () const
  {
    return r_;
  }

  unsigned short
  get_g () const
  {
    return g_;
  }

  unsigned short
  get_b () const
  {
    return b_;
  }


  private:
  unsigned short r_;      //< ???
  unsigned short g_;      //< ???
  unsigned short b_;      //< ???
};

}}}      // namespace libs::igui_events::utils
