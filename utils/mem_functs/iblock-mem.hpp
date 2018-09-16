#pragma once
/**
\file       iblock-mem.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      Файл интерфейса для выделения выровненных блоков памяти.
*/

//  Макрос включает принудительный сброс памяти в utils::mem_functs::consts::filling после перераспределения. Используется для отладки.
#ifdef UUU_DEBUG
#ifndef UUU_FORCE_RESET_MEMORY_AFTER_ALLOC
#define UUU_FORCE_RESET_MEMORY_AFTER_ALLOC
#endif
#endif

/// Пространство имен для утилит (как статически линкуемых, там и динамически загружаемых).
namespace utils {
/// Пространство имен функционала для работы с блоками памяти в ОЗУ.
namespace mem_functs {
/// Пространство имен констант функционала для работы с памятью.
namespace consts {

const unsigned char filling = 0;      //< Значение для заполнения памяти по умолчанию.
}
}      // namespace mem_functs
}      // namespace utils


namespace utils { namespace mem_functs {
/**
  \brief  Интерфейс управления блоком памяти.
  */
class IBlockMem
{
  public:
  //  ext types
  using size_type = std::size_t;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockMem);

  virtual ~IBlockMem ()
  {}

  IBlockMem (const IBlockMem& _src) = delete;
  IBlockMem& operator= (const IBlockMem& _src) = delete;
  /**
  \brief    Функция получения буфера памяти.
  \return   сырой указатель на начало буфера.
  */
  unsigned char*
  get ()
  {
    return get_int ();
  }
  /**
  \brief    Функция получения констатного буфера памяти.
  \return   сырой константный указатель на начало буфера.
  */
  const unsigned char*
  get () const
  {
    return get_int ();
  }
  /**
  \brief    Функция возврата размера буфера памяти
  \return   размер буфера.
  */
  IBlockMem::size_type
  get_buff_size () const
  {
    return get_buff_size_int ();
  }
  /**
  \brief    Функция возврата размера данных в буфере памяти
  \return   размер данных.
  */
  IBlockMem::size_type
  get_data_size () const
  {
    return get_data_size_int ();
  }
  /**
  \brief      Функция установки размера данных в буфере памяти.
  \param[in]  _size новый размер данных.
  */
  void
  set_data_size (const size_type& _size)
  {
    return set_data_size_int (_size);
  }
  /**
  \brief      Функция перераспределения буфера памяти.
  \param[in]  _size новый требуемый размер памяти.
  */
  void
  resize (const size_type& _size)
  {
    return resize_int (_size);
  }


  protected:
  IBlockMem ()
  {}


  private:
  // IBlockMem itnterface
  virtual unsigned char*       get_int ()                            = 0;
  virtual const unsigned char* get_int () const                      = 0;
  virtual std::size_t          get_buff_size_int () const            = 0;
  virtual std::size_t          get_data_size_int () const            = 0;
  virtual void                 set_data_size_int (std::size_t _size) = 0;
  virtual void                 resize_int (const std::size_t _size)  = 0;
};

}}      // namespace utils::mem_functs
