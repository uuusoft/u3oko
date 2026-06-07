#pragma once
/**
\file       pos.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::utils::impl
{
/// Тривиальная реализация интерфейса IPos
class Pos : public IPos
{
  public:
  explicit Pos (IPos::value_type x = 0, IPos::value_type y = 0) :
    x_ (x),
    y_ (y)
  {
  }

  ~Pos ()
  {
  }

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
    Pos* temp = new Pos;

    temp->set (get_x (), get_y ());

    return IPos::ptr (temp);
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
    // info_.reset();
  }

  void
  set (IPos::value_type x, IPos::value_type y)
  {
    U3_ASSERT (x >= 0);
    U3_ASSERT (y >= 0);
    x_ = x;
    y_ = y;
    check ();
    return;
  }


  protected:
  IPos::value_type x_;   //<
  IPos::value_type y_;   //<
};
}   // namespace libs::igui_events::utils::impl
