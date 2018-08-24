#pragma once
/**
\file       rect_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace helpers {

inline bool
is_equal (
  IRect::raw_ptr _left,
  IRect::raw_ptr _right)
{
  UASSERT (_left);
  UASSERT (_right);

  if (_left == _right)
    {
      return true;
    }

  if (!is_equal (_left->get_pos (), _right->get_pos ()))
    {
      return false;
    }

  if (!is_equal (_left->get_size (), _right->get_size ()))
    {
      return false;
    }

  return true;
}


inline bool
include (
  const IRect::raw_ptr _rect,
  const IPos::raw_ptr  _pos)
{
  UASSERT (_rect);
  UASSERT (_pos);

  auto _gpos  = _rect->get_pos ();
  auto _gsize = _rect->get_size ();

  return _gpos->get_x () <= _pos->get_x () &&
         _gpos->get_y () >= _pos->get_y () &&
         _gpos->get_x () + _gsize->get_width () >= _pos->get_x () &&
         _gpos->get_y () - _gsize->get_height () <= _pos->get_y ();
}

}}}}      // namespace libs::igui_events::utils::helpers
