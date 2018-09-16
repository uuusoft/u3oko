#pragma once
/**
\file       proxy-buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

#ifndef UUU_CPROXY_BUFF_CAST
#define UUU_CPROXY_BUFF_CAST reinterpret_cast
#endif

namespace libs { namespace optim { namespace io {
//  syn
using ::utils::dbuffs::video::IVideoBuff;
using ::utils::dbuffs::video::TypeDimVar;
/**
\brief  Легкий класс-обертка для работы с буфером данных. 
        Используется для упрощения интерфейса для ряда операций над оригинальным буфером.
*/
struct ProxyBuff
{
  ProxyBuff () :
    buff_ (nullptr),
    stride_ (0),
    width_ (0),
    height_ (0),
    const_data_ (false)
  {}

  ProxyBuff (
    short*      _buff,
    std::size_t _stride,
    std::size_t _width,
    std::size_t _height) :

    buff_ (_buff),
    stride_ (_stride),
    width_ (_width),
    height_ (_height),
    const_data_ (false)
  {
    check ();
  }

  ProxyBuff (
    const short* _buff,
    std::size_t  _stride,
    std::size_t  _width,
    std::size_t  _height) :

    buff_ (const_cast<short*> (_buff)),
    stride_ (_stride),
    width_ (_width),
    height_ (_height),
    const_data_ (true)
  {
    check ();
  }

  ProxyBuff (
    unsigned char* _buff,
    std::size_t    _stride,
    std::size_t    _width,
    std::size_t    _height) :

    buff_ (UUU_CPROXY_BUFF_CAST<short*> (_buff)),
    stride_ (_stride),
    width_ (_width),
    height_ (_height),
    const_data_ (false)
  {
    check ();
  }

  ProxyBuff (
    const unsigned char* _buff,
    std::size_t          _stride,
    std::size_t          _width,
    std::size_t          _height) :

    buff_ (const_cast<short*> (UUU_CPROXY_BUFF_CAST<const short*> (_buff))),
    stride_ (_stride),
    width_ (_width),
    height_ (_height),
    const_data_ (true)
  {
    check ();
  }

  explicit ProxyBuff (IVideoBuff::raw_ptr _buff)
  {
    if (!_buff || 0 == (*_buff)[::utils::dbuffs::TypeMemVar::size_buffer])
      {
        reset ();
        return;
      }

    reinit (_buff);
    return;
  }

  explicit ProxyBuff (IVideoBuff::craw_ptr _buff)
  {
    if (!_buff || 0 == (*_buff)[::utils::dbuffs::TypeMemVar::size_buffer])
      {
        reset ();
        const_data_ = true;
        return;
      }

    reinit (const_cast<IVideoBuff::raw_ptr> (_buff));
    const_data_ = true;
    return;
  }

  ~ProxyBuff ()
  {}

  void
  reinit (IVideoBuff::raw_ptr _src)
  {
    UASSERT (_src);
    short* _buff = _src->get_flag (utils::dbuffs::TypeFlagsBuff::null) ? nullptr : utils::dbuffs::video::helpers::get_data_as<short*> (_src);

    set_buff (_buff);

    stride_     = _src->get_dim_var (TypeDimVar::stride);
    width_      = _src->get_dim_var (TypeDimVar::width);
    height_     = _src->get_dim_var (TypeDimVar::height);
    const_data_ = false;

    check ();
    return;
  }

  void
  reset ()
  {
    buff_       = nullptr;
    stride_     = 0;
    width_      = 0;
    height_     = 0;
    const_data_ = false;
    return;
  }
  /**
  \brief  Функция отключения флага константности.
          Иногда требуется изменить параметры константного буфера.
  */
  void
  reset_const ()
  {
    const_data_ = false;
    return;
  }

  void
  check () const
  {
    if (!buff_)
      {
        return;
      }
    CHECK_STATE (stride_, "failed, zero stride");
    CHECK_STATE (width_, "failed, zero width");
    CHECK_STATE (height_, "failed, zero height");
    CHECK_STATE (width_ <= stride_, "failed, width less stride");
    return;
  }

  bool
  self_test () const
  {
    return buff_ && stride_ && width_ && height_ && width_ <= stride_;
  }

  short*
  buff ()
  {
    UASSERT (!const_data_);
    return buff_;
  }

  unsigned char*
  ubuff ()
  {
    UASSERT (!const_data_);
    return UUU_CPROXY_BUFF_CAST<unsigned char*> (buff_);
  }

  const short*
  buff () const
  {
    return buff_;
  }

  const unsigned char*
  ubuff () const
  {
    return UUU_CPROXY_BUFF_CAST<const unsigned char*> (buff_);
  }

  void
  set_buff (short* _buff)
  {
    //UASSERT( _buff );
    buff_       = _buff;
    const_data_ = false;
    return;
  }

  void
  set_ubuff (unsigned char* _buff)
  {
    UASSERT (_buff);
    buff_       = UUU_CPROXY_BUFF_CAST<short*> (_buff);
    const_data_ = false;
    return;
  }

  short*
  get_line (int _indx, bool _unsafe = false)
  {
    UASSERT (!const_data_);
    if (!_unsafe)
      {
        CHECK_STATE_RET (buff_, "", nullptr);
        CHECK_STATE_RET (_indx > 0, "", nullptr);
        CHECK_STATE_RET (_indx < UUU_ICAST_INT (height_), "", nullptr);
      }

    short* _ret = UUU_CPROXY_BUFF_CAST<short*> (ubuff () + stride_ * _indx);
    return _ret;
  }

  const short*
  get_cline (int _indx, bool _unsafe = false) const
  {
    if (!_unsafe)
      {
        CHECK_STATE_RET (buff_, "empty buff", nullptr);
        CHECK_STATE_RET (_indx >= 0, "", nullptr);
        CHECK_STATE_RET (_indx < UUU_ICAST_INT (height_), "", nullptr);
      }

    const short* _ret = UUU_CPROXY_BUFF_CAST<const short*> (ubuff () + stride_ * _indx);
    return _ret;
  }

  short*
  get_line (std::size_t _indx)
  {
    UASSERT (!const_data_);
    int _rindx = UUU_ICAST_INT (_indx);
    return get_line (_rindx, false);
  }

  const short*
  get_cline (std::size_t _indx) const
  {
    int _rindx = UUU_ICAST_INT (_indx);
    return get_cline (_rindx, false);
  }

  std::size_t width_;       //< Ширина данных в пикселях.
  std::size_t height_;      //< Высота данных в пикселях.
  std::size_t stride_;      //< Ширина строки в байтах.


  private:
  short* buff_;            //< Указатель на буфер с данными.
  bool   const_data_;      //< Флаг константности данных. REFACT
};

}}}      // namespace libs::optim::io
