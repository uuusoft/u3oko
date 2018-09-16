#pragma once
/**
\file       pos.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace impl {
/**
\brief  Тривиальная реализация интерфейса IPos.
*/
class Pos : public IPos
{
  public:
  explicit Pos (IPos::value_type _x = 0, IPos::value_type _y = 0) :
    x_ (_x),
    y_ (_y)
  {}

  ~Pos ()
  {}

  virtual IPos::value_type
  get_x () const override
  {
    return x_;
  }

  virtual IPos::value_type
  get_y () const override
  {
    return y_;
  }

  virtual IPos::ptr
  clone () const override
  {
    Pos* _temp = new Pos;

    _temp->set (get_x (), get_y ());

    return IPos::ptr (_temp);
  }

  void
  check () const
  {
    return;
  }

  void
  reset ()
  {
    x_ = 0;
    y_ = 0;
    //info_.reset();
  }

  void
  set (IPos::value_type _x, IPos::value_type _y)
  {
    UASSERT (_x >= 0);
    UASSERT (_y >= 0);
    x_ = _x;
    y_ = _y;
    check ();
    return;
  }


  protected:
  IPos::value_type x_;      //< ???
  IPos::value_type y_;      //< ???
};

}}}}      // namespace libs::igui_events::utils::impl
