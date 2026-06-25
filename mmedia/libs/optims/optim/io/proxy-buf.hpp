#pragma once
/**
\file       proxy-buf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_optim_lib
*/

#ifndef U3_CAST_CPROXY_BUFF
#  define U3_CAST_CPROXY_BUFF reinterpret_cast
#endif

namespace libs::optim::io
{
/// Легкий класс-обертка для работы с буфером данных
/// Используется для упрощения интерфейса для ряда операций над оригинальным буфером
struct ProxyBuf final {
  ProxyBuf () = default;

  ProxyBuf (
    std::int16_t* buf,
    std::uint32_t stride,
    std::uint32_t width,
    std::uint32_t height,
    const char*   debinfo) :

    buf_ (buf),
    stride_ (stride),
    width_ (width),
    height_ (height),
    const_data_ (false)
  {
    check (debinfo);
  }

  ProxyBuf (
    const std::int16_t* buf,
    std::uint32_t       stride,
    std::uint32_t       width,
    std::uint32_t       height,
    const char*         debinfo) :

    buf_ (const_cast< std::int16_t* > (buf)),
    stride_ (stride),
    width_ (width),
    height_ (height),
    const_data_ (true)
  {
    check (debinfo);
  }

  ProxyBuf (
    std::uint8_t* buf,
    std::uint32_t stride,
    std::uint32_t width,
    std::uint32_t height,
    const char*   debinfo) :

    buf_ (U3_CAST_CPROXY_BUFF< std::int16_t* > (buf)),
    stride_ (stride),
    width_ (width),
    height_ (height),
    const_data_ (false)
  {
    check (debinfo);
  }

  ProxyBuf (
    const std::uint8_t* buf,
    std::uint32_t       stride,
    std::uint32_t       width,
    std::uint32_t       height,
    const char*         debinfo) :

    buf_ (const_cast< std::int16_t* > (U3_CAST_CPROXY_BUFF< const std::int16_t* > (buf))),
    stride_ (stride),
    width_ (width),
    height_ (height),
    const_data_ (true)
  {
    check (debinfo);
  }

  explicit ProxyBuf (syn::IVideoBuf::raw_ptr buf, const char* debinfo)
  {
    if (!buf || 0 == (*buf)[::utils::dbufs::MemVars::size_buf])
    {
      reset ();
      return;
    }

    reinit (buf, debinfo);
  }

  explicit ProxyBuf (syn::IVideoBuf::craw_ptr buf, const char* debinfo)
  {
    if (!buf || 0 == (*buf)[::utils::dbufs::MemVars::size_buf])
    {
      reset ();
      const_data_ = true;
      return;
    }

    reinit (const_cast< syn::IVideoBuf::raw_ptr > (buf), debinfo);
    const_data_ = true;
  }

  ~ProxyBuf () = default;

  void
  reinit (syn::IVideoBuf::raw_ptr src, const char* debinfo)
  {
    U3_ASSERT (src);
    std::int16_t* buf = src->get_flag (utils::dbufs::BufFlags::null) ? nullptr : utils::dbufs::video::helpers::get_data_as< std::int16_t* > (src);

    set_buf (buf);

    stride_ = src->get_dim_var (::utils::dbufs::video::Dims::stride);
    width_  = src->get_dim_var (::utils::dbufs::video::Dims::width);
    height_ = src->get_dim_var (::utils::dbufs::video::Dims::height);

    const_data_ = false;
    check (debinfo);
  }

  void
  reset ()
  {
    buf_        = nullptr;
    stride_     = 0;
    width_      = 0;
    height_     = 0;
    const_data_ = false;
  }

  /// Функция отключения флага константности
  /// Введена т.к. иногда требуется изменить параметры константного буфера
  /// EAI-REFACT
  void
  reset_const ()
  {
    const_data_ = false;
  }

  void
  check (const char* info) const
  {
    if (!buf_)
    {
      return;
    }
    // Эти проверки не должны выбрасывать исключения, т.к. это допустимая ситуация во внешней логике
    // U3_CHECK_NT (stride_, "zero stride: " << info);
    // U3_CHECK_NT (width_, "zero width: " << info);
    // U3_CHECK_NT (height_, "zero height: " << info);
    U3_CHECK (width_ <= stride_, "stride less width: " + VTOLOG (width_) + ">" + VTOLOG (stride_) + " " + info);
  }

  bool
  self_test () const
  {
    return buf_ && stride_ && width_ && height_ && width_ <= stride_;
  }

  std::int16_t*
  buf ()
  {
    U3_ASSERT (!const_data_);
    return buf_;
  }

  const std::int16_t*
  buf () const
  {
    return buf_;
  }

  std::uint8_t*
  ubuf ()
  {
    U3_ASSERT (!const_data_);
    return U3_CAST_CPROXY_BUFF< std::uint8_t* > (buf_);
  }

  const std::uint8_t*
  ubuf () const
  {
    return U3_CAST_CPROXY_BUFF< const std::uint8_t* > (buf_);
  }

  void
  set_buf (int16_t* buf)
  {
    buf_        = buf;
    const_data_ = false;
  }

  void
  set_ubuf (uint8_t* buf)
  {
    U3_ASSERT (buf);
    buf_        = U3_CAST_CPROXY_BUFF< std::int16_t* > (buf);
    const_data_ = false;
  }

  std::int16_t*
  get_line (std::uint32_t indx, bool unsafe = false)
  {
    U3_ASSERT (!const_data_);
    U3_CHECK (buf_, "buf_:");
    U3_CHECK (indx < height_, "indx < height_:" + VTOLOG (indx) + VTOLOG (height_));
    return U3_CAST_CPROXY_BUFF< std::int16_t* > (ubuf () + stride_ * indx);
  }

  const std::int16_t*
  get_cline (std::uint32_t indx, bool unsafe = false) const
  {
    U3_CHECK (buf_, "buf_:");
    U3_CHECK (indx < height_, "indx < height_:" + VTOLOG (indx) + VTOLOG (height_));
    return U3_CAST_CPROXY_BUFF< const std::int16_t* > (ubuf () + stride_ * indx);
  }

  std::uint32_t width_  = 0;   //< Ширина данных в пикселях
  std::uint32_t height_ = 0;   //< Высота данных в пикселях
  std::uint32_t stride_ = 0;   //< Ширина строки в байтах

  private:
  std::int16_t* buf_        = nullptr;   //< Указатель на буфер с данными
  bool          const_data_ = false;     //< Флаг константности данных REFACT
};
}   // namespace libs::optim::io
