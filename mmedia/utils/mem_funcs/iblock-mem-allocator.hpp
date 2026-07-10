#pragma once
/**
\file       iblock-mem-allocator.hpp
\author     Erashov Anton erashov2026@proton.me
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
  using size_type = ::libs::utility::mem::IBlockMem::size_type;

  U3_ADD_POINTERS_TO_SELF (IBlockMemAllocator)
  U3_ADD_DELETE_MOVE_COPY (IBlockMemAllocator);

  /// Функция выделения блока памяти с выравниваем
  /// \param[in]  size размер памяти под данные
  /// \return     указатель на блок памяти
  virtual auto alloc (const size_type& size) -> ::libs::utility::mem::IBlockMem::ptr = 0;

  /// Функция трассировки статуса памяти системы в данном процессе
  virtual auto dump_memory_status () -> std::string = 0;

  protected:
  IBlockMemAllocator ()          = default;
  virtual ~IBlockMemAllocator () = default;
};
}   // namespace utils::mem_funcs
