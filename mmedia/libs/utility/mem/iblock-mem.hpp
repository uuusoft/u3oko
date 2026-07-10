#pragma once
/**
\file       iblock-mem.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_mem_funcs
\brief      Файл интерфейса для выделения выровненных блоков памяти
*/

namespace libs::utility::mem
{
/// Пространство имен констант функционала для работы с памятью
namespace consts
{
inline constexpr std::uint8_t  filling               = 0;                    //< Значение для заполнения памяти по умолчанию
inline constexpr std::uint64_t max_memory_block_size = 1024 * 1024 * 1024;   //< эвристика
}   // namespace consts
}   // namespace libs::utility::mem

namespace libs::utility::mem
{
/// нтерфейс управления блоком памяти
class IBlockMem
{
  public:
  //  ext types
  using size_type = std::uint64_t;

  U3_ADD_POINTERS_TO_SELF (IBlockMem)
  U3_ADD_DELETE_MOVE_COPY (IBlockMem);

  virtual ~IBlockMem () = default;

  std::uint8_t*
  get ()
  {
    const auto ret = get_int ();
    return ret;
  }

  const std::uint8_t*
  get () const
  {
    const auto ret = get_int ();
    return ret;
  }

  IBlockMem::size_type
  get_capacity () const
  {
    auto ret = get_capacity_int ();
    U3_CHECK_NT (ret <= consts::max_memory_block_size, "unusual memory block size" + VTOLOG (ret) + VTOLOG (consts::max_memory_block_size));
    return ret;
  }

  IBlockMem::size_type
  get_size () const
  {
    const auto ret = get_size_int ();
    U3_CHECK (ret <= get_capacity_int (), "invalid state memory" + VTOLOG (get_capacity_int ()) + VTOLOG (ret));
    return ret;
  }

  void
  set_size (const size_type& size)
  {
    U3_CHECK (size <= get_capacity_int (), "capacity too small" + VTOLOG (get_capacity_int ()) + VTOLOG (size));
    set_size_int (size);
  }

  void
  resize (const size_type& size)
  {
    resize_int (size);
    U3_CHECK (get_capacity () >= size, "resize failed");
  }

  protected:
  IBlockMem () = default;

  private:
  // IBlockMem itnterface
  virtual auto get_int () -> std::uint8_t*                       = 0;
  virtual auto get_int () const -> const std::uint8_t*           = 0;
  virtual auto get_capacity_int () const -> IBlockMem::size_type = 0;
  virtual auto get_size_int () const -> IBlockMem::size_type     = 0;
  virtual auto set_size_int (IBlockMem::size_type) -> void       = 0;
  virtual auto resize_int (IBlockMem::size_type) -> void         = 0;
};
}   // namespace libs::utility::mem
