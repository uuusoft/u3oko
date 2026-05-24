#pragma once
/**
\file       iblock-mem-allocator.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_mem_funcs
*/

namespace utils::mem_funcs
{
/// Интерфейс кэширования и выделения выровненных блоков памяти внутри одного процесса
class IBlockMemAllocator
{
  public:
  //  ext types
  using size_type = ::libs::helpers::mem::IBlockMem::size_type;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockMemAllocator)

  IBlockMemAllocator (const IBlockMemAllocator& src)            = delete;
  IBlockMemAllocator& operator= (const IBlockMemAllocator& src) = delete;
  /// Функция выделения блока памяти с выравниваем
  /// \param[in]  size размер памяти под данные
  /// \return     указатель на блок памяти
  virtual ::libs::helpers::mem::IBlockMem::ptr alloc (const size_type& size) = 0;
  /// Функция трассировки статуса памяти системы в данном процессе
  virtual std::string dump_memory_status () = 0;

  protected:
  IBlockMemAllocator ()
  {
  }

  virtual ~IBlockMemAllocator ()
  {
  }
};
}   // namespace utils::mem_funcs
