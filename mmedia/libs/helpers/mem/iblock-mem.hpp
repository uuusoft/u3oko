#pragma once
/**
\file       iblock-mem.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_mem_funcs
\brief      Файл интерфейса для выделения выровненных блоков памяти
*/

namespace libs::helpers::mem
{
/// Пространство имен констант функционала для работы с памятью
namespace consts
{
constexpr std::uint8_t filling = 0;   //< Значение для заполнения памяти по умолчанию
}
}   // namespace libs::helpers::mem


namespace libs::helpers::mem
{
/// нтерфейс управления блоком памяти
class IBlockMem
{
  public:
  //  ext types
  using size_type = std::uint64_t;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockMem)

  virtual ~IBlockMem () = default;

  IBlockMem (const IBlockMem& src)            = delete;
  IBlockMem& operator= (const IBlockMem& src) = delete;

  /// Функция получения буфера памяти
  /// \return   сырой указатель на начало буфера
  std::uint8_t*
  get ()
  {
    return get_int ();
  }

  /// Функция получения констатного буфера памяти
  /// \return   сырой константный указатель на начало буфера
  const std::uint8_t*
  get () const
  {
    return get_int ();
  }

  /// Функция возврата размера буфера памяти
  /// \return   размер буфера
  IBlockMem::size_type
  get_buf_size () const
  {
    return get_buf_size_int ();
  }

  /// Функция возврата размера данных в буфере памяти
  /// \return   размер данных
  IBlockMem::size_type
  get_data_size () const
  {
    return get_data_size_int ();
  }

  /// Функция установки размера данных в буфере памяти
  /// \param[in]  size новый размер данных
  void
  set_data_size (const size_type& size)
  {
    set_data_size_int (size);
  }

  /// Функция перераспределения буфера памяти
  /// \param[in]  size новый требуемый размер памяти
  void
  resize (const size_type& size)
  {
    resize_int (size);
    U3_CHECK (get_buf_size () >= size, "resize failed");
  }

  protected:
  IBlockMem () = default;

  private:
  // IBlockMem itnterface
  virtual std::uint8_t*        get_int ()                                    = 0;
  virtual const std::uint8_t*  get_int () const                              = 0;
  virtual IBlockMem::size_type get_buf_size_int () const                     = 0;
  virtual IBlockMem::size_type get_data_size_int () const                    = 0;
  virtual void                 set_data_size_int (IBlockMem::size_type size) = 0;
  virtual void                 resize_int (IBlockMem::size_type size)        = 0;
};
}   // namespace libs::helpers::mem
