#pragma once
/**
\file       iblock-mem-allocator.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_mem_functs
\brief      Файл интерфейса кеширования блоков памяти.
*/

namespace utils { namespace mem_functs {
/**
\brief  Интерфейс кэширования и выделения выровненных блоков памяти внутри одного процесса.
*/
class IBlockMemAllocator
{
  public:
  //  ext types
  using size_type = IBlockMem::size_type;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockMemAllocator);

  IBlockMemAllocator (const IBlockMemAllocator& _src) = delete;
  IBlockMemAllocator& operator= (const IBlockMemAllocator& _src) = delete;
  /**
  \brief      Функция выделения блока памяти с выравниваем.
  \param[in]  _size размер памяти под данные.
  \return     указатель на блок памяти.
  */
  virtual IBlockMem::ptr alloc (const size_type& _size) = 0;
  /// Функция трассировки статуса памяти системы в данном процессе.
  virtual void dump_status () = 0;


  protected:
  /// Конструктор закрытый.
  IBlockMemAllocator ()
  {}
  /// Деструктор закрытый.
  virtual ~IBlockMemAllocator ()
  {}
};

}}      // namespace utils::mem_functs
