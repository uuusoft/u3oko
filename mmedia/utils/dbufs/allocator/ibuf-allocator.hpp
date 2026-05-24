#pragma once
/**
\file       ibuf-allocator.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_dbufs
*/

namespace utils::dbufs::allocator
{
/// Интерфейс по выделению буферов под данные
/// Реализуется как "одиночка" для системы в целом (как для статически линкуемых модулей, так и для динамически загружаемых)
class IBufAllocator
{
  public:
  //  ext types
  using size_type = std::uint64_t;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IBufAllocator)

  IBufAllocator (const IBufAllocator& src)            = delete;
  IBufAllocator& operator= (const IBufAllocator& src) = delete;

  /// Функция получения (создание нового или возврает ранее созданного и свободного) буфера
  /// \param[in]  size опциональный предполагаемый размер данных для буфера или 0, если размер не известен
  /// \return     указатель на выделенный буфер
  virtual utils::dbufs::video::IVideoBuf::ptr create (IBufAllocator::size_type size) = 0;

  /// Функция трассировки состояния реализации интерфейса. Количество буферов, количество свободных буферов, используемая память и т.п
  virtual std::string dump_bufs_state () = 0;

  protected:
  IBufAllocator ()
  {
  }

  virtual ~IBufAllocator ()
  {
  }
};
}   // namespace utils::dbufs::allocator
