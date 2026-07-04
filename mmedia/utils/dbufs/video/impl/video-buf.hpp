#pragma once
/**
\file       video-buf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_dbufs
\brief      Объявление реализации буфера под видео
*/

namespace utils::dbufs::video::impl
{
/// Реализация интерфейса для управления буфера с видео данными
class VideoBuf final : public IVideoBuf
{
  friend class utils::dbufs::allocator::BufAllocator;

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (VideoBuf)

  virtual ~VideoBuf () = default;

  private:
  /// Скрытый конструктор, т.к возможность конструирования объектов данного класса есть только у utils::dbufs::allocator::CObj
  explicit VideoBuf ();

  //  IVideoBuf overrides
  virtual auto set_format_int (const libs::utility::uids::minor::id_val&) -> void override;
  virtual auto get_format_int () const -> libs::utility::uids::minor::id_val override;
  virtual auto set_dim_var_int (const Dims&, dim_type) -> void override;
  virtual auto get_dim_var_int (const Dims&) const -> dim_type override;
  virtual auto get_dim_vars_int () const -> const DimVars& override;
  virtual auto set_flag_int (const BufFlags&, bool) -> void override;
  virtual auto get_flag_int (const BufFlags&) const -> bool override;
  virtual auto buf_alloc_int (const AllocParams&) -> void override;
  virtual auto clone_int (IBuf::craw_ptr, float) -> void override;
  virtual auto swap_int (IBuf&) -> void override;
  virtual auto flush_int () -> void override;
  virtual auto check_int (const check_func_type&) const -> bool override;

  AllocParams params_;   //< Параметры, которые использовались при выделении буфера
};
}   // namespace utils::dbufs::video::impl
