#pragma once
/**
\file       rect.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::utils::impl
{
/// Интерфейс для работы с размерами любых объектов в GUI
class Rect : public IRect
{
  public:
  explicit Rect (
    IPos::value_type  x      = 0,
    IPos::value_type  y      = 0,
    ISize::value_type width  = 0,
    ISize::value_type height = 0)
  {
    pos_.set (x, y);

    size_.set (width, height);
  }

  Rect (IPos::craw_ptr pos, ISize::craw_ptr size)
  {
    set (pos, size);
  }

  virtual ~Rect ()
  {
  }

  void
  set (IPos::craw_ptr pos, ISize::craw_ptr size)
  {
    U3_ASSERT (pos);
    U3_ASSERT (size);
    pos_.set (pos->get_x (), pos->get_y ());
    size_.set (size->get_width (), size->get_height ());
    return;
  }

  void
  reset ()
  {
    pos_.reset ();
    size_.reset ();
    return;
  }

  virtual IPos::raw_ptr
  get_pos () override
  {
    return &pos_;
  }

  virtual IPos::craw_ptr
  get_pos () const override
  {
    return &pos_;
  }

  virtual ISize::raw_ptr
  get_size () override
  {
    return &size_;
  }

  virtual ISize::craw_ptr
  get_size () const override
  {
    return &size_;
  }

  void
  check () const
  {
    pos_.check ();
    U3_CHECK (size_.self_test (), "invalid size");
    return;
  }


  private:
  Pos  pos_;    //<
  Size size_;   //<
};
}   // namespace libs::events_gui::utils::impl
