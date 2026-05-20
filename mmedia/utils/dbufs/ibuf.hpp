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
  using mem_type = std::uint64_t;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBuf)

  virtual ~IBuf ()
  {
  }

  IBuf (const IBuf& _rsc)           = delete;
  IBuf& operator= (const IBuf& src) = delete;
  // EAI-REFACT
  /// Функция установки значения переменной, для описания данные с точки зрения используемой памяти
  /// \param[in]  _type тип переменной
  /// \param[in]  _val  значение переменной
  void
  set_mem_var (const MemVars& _type, mem_type _val)
  {
    set_mem_var_int (_type, _val);
  }
  /// Функция получения значения переменной для описания данные с точки зрения используемой памяти
  /// \param[in]  _type тип переменной
  /// \return     значение переменной
  mem_type
  operator[] (const MemVars& _type) const
  {
    return get_mem_var_int (_type);
  }
  /// Функция клонирования буфера
  /// \param[in]  _source   источник данных
  /// \param[in]  _perc_copy  проценты копирования по вертикали [0.0f..1000f]
  void
  clone (IBuf::ptr& _source, float _perc_copy)
  {
    clone_int (_source.get (), _perc_copy);
  }
  /// Функция клонирования буфера
  /// \param[in]  _source   источник данных
  /// \param[in]  _perc_copy  проценты копирования по вертикали [0.0f..1000f]
  void
  clone (IBuf::craw_ptr _source, float _perc_copy)
  {
    clone_int (_source, _perc_copy);
  }
  /// Функция обмена содержимого буферов. \param[in]  buf буфер обмена
  void
  swap (IBuf& buf)
  {
    swap_int (buf);
  }
  /// Функция получения буфера. \return   буфер
  std::uint8_t*
  get_buf ()
  {
    return get_buf_int ();
  }
  /// Функция получения константного буфера.\return   буфер
  const std::uint8_t*
  get_cbuf () const
  {
    return get_cbuf_int ();
  }

  protected:
  IBuf ()
  {
  }

  private:
  //  IBuf interface
  virtual void                set_mem_var_int (const MemVars& _type, mem_type _val) = 0;
  virtual mem_type            get_mem_var_int (const MemVars& _type) const          = 0;
  virtual std::uint8_t*       get_buf_int ()                                        = 0;
  virtual const std::uint8_t* get_cbuf_int () const                                 = 0;
  virtual void                clone_int (IBuf::craw_ptr source, float _perc_copy)   = 0;
  virtual void                swap_int (IBuf& buf)                                  = 0;
};
}   // namespace utils::dbufs
