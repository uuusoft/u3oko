#pragma once
/**
\file       rect.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_igui_evenets
\brief      empty brief
*/

namespace libs { namespace igui_events { namespace utils { namespace impl {
/**
  \brief  Интерфейс для работы с размерами любых объектов в GUI.
  */
class Rect : public IRect
{
  public:
  explicit Rect (
    IPos::value_type  _x      = 0,
    IPos::value_type  _y      = 0,
    ISize::value_type _width  = 0,
    ISize::value_type _height = 0)
  {
    pos_.set (_x, _y);

    size_.set (_width, _height);
  }

  Rect (IPos::craw_ptr _pos, ISize::craw_ptr _size)
  {
    set (_pos, _size);
  }

  virtual ~Rect ()
  {}

  void
  set (IPos::craw_ptr _pos, ISize::craw_ptr _size)
  {
    UASSERT (_pos);
    UASSERT (_size);

    pos_.set (_pos->get_x (), _pos->get_y ());

    size_.set (_size->get_width (), _size->get_height ());
  }

  void
  reset ()
  {
    pos_.reset ();
    size_.reset ();
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
    CHECK_STATE (size_.self_test (), "failed, invalid size");
    return;
  }


  private:
  Pos  pos_;       //< ???
  Size size_;      //< ???
};

}}}}      // namespace libs::igui_events::utils::impl
