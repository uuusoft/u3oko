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
  using size_type = ::libs::helpers::mem::IBlockMem::size_type;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockMemAllocator)

  IBlockMemAllocator (const IBlockMemAllocator& src)                = delete;
  IBlockMemAllocator& operator= (const IBlockMemAllocator& src)     = delete;
  IBlockMemAllocator (IBlockMemAllocator&& src) noexcept            = delete;
  IBlockMemAllocator& operator= (IBlockMemAllocator&& src) noexcept = delete;

  /// Функция выделения блока памяти с выравниваем
  /// \param[in]  size размер памяти под данные
  /// \return     указатель на блок памяти
  virtual auto alloc (const size_type& size) -> ::libs::helpers::mem::IBlockMem::ptr = 0;

  /// Функция трассировки статуса памяти системы в данном процессе
  virtual auto dump_memory_status () -> std::string = 0;

  protected:
  IBlockMemAllocator ()          = default;
  virtual ~IBlockMemAllocator () = default;
};
}   // namespace utils::mem_funcs
