#pragma once
/**
\file       ibuf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_dbufs
*/

namespace utils::dbufs
{
/// Базовый интерфейс хранения буфера в памяти под кадр (звук/видео)
class IBuf
{
  public:
  //  ext types
  using mem_var_type = std::uint64_t;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBuf)

  virtual ~IBuf () = default;

  IBuf (const IBuf&)                = delete;
  IBuf& operator= (const IBuf&)     = delete;
  IBuf (IBuf&&) noexcept            = delete;
  IBuf& operator= (IBuf&&) noexcept = delete;

  /// Функция установки значения переменной, для описания данные с точки зрения используемой памяти
  /// \param[in]  type тип переменной
  /// \param[in]  val  значение переменной
  void
  set_mem_var (const MemVars& type, const mem_var_type& val)
  {
    set_mem_var_int (type, val);
  }

  /// Функция получения значения переменной для описания данные с точки зрения используемой памяти
  /// \param[in]  type тип переменной
  /// \return     значение переменной
  mem_var_type
  operator[] (const MemVars& type) const
  {
    return get_mem_var_int (type);
  }

  /// Функция клонирования буфера
  /// \param[in]  _source   источник данных
  /// \param[in]  _perc_copy  проценты копирования по вертикали [0.0F..1000f]
  void
  clone (IBuf::ptr& _source, float _perc_copy)
  {
    clone_int (_source.get (), _perc_copy);
  }

  /// Функция клонирования буфера
  /// \param[in]  _source   источник данных
  /// \param[in]  _perc_copy  проценты копирования по вертикали [0.0F..1000f]
  void
  clone (IBuf::craw_ptr _source, float _perc_copy)
  {
    clone_int (_source, _perc_copy);
  }

  /// Функция обмена содержимого буферов
  /// \param[in]  buf буфер обмена
  void
  swap (IBuf& buf)
  {
    swap_int (buf);
  }

  /// Функция получения буфера
  /// \return   буфер
  std::uint8_t*
  get_buf ()
  {
    return get_buf_int ();
  }

  /// Функция получения константного буфера
  /// \return   буфер
  const std::uint8_t*
  get_cbuf () const
  {
    return get_cbuf_int ();
  }

  protected:
  IBuf () = default;

  private:
  //  IBuf interface
  virtual auto set_mem_var_int (const MemVars&, mem_var_type) -> void = 0;
  virtual auto get_mem_var_int (const MemVars&) const -> mem_var_type = 0;
  virtual auto get_buf_int () -> std::uint8_t*                        = 0;
  virtual auto get_cbuf_int () const -> const std::uint8_t*           = 0;
  virtual auto clone_int (IBuf::craw_ptr, float) -> void              = 0;
  virtual auto swap_int (IBuf&) -> void                               = 0;
};
}   // namespace utils::dbufs
