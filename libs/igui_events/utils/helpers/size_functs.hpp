#pragma once
/**
\file       size_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace helpers {

inline bool
is_equal (ISize::craw_ptr _left, ISize::craw_ptr _right)
{
  UASSERT (_left);
  UASSERT (_right);

  if (_left == _right)
    {
      return true;
    }

  if (_left->get_width () != _right->get_width ())
    {
      return false;
    }

  if (_left->get_height () != _right->get_height ())
    {
      return false;
    }

  return true;
}

}}}}      // namespace libs::igui_events::utils::helpers
