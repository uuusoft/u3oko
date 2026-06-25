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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoBuf)

  virtual ~VideoBuf () = default;

  VideoBuf (const VideoBuf& src)                = delete;
  VideoBuf& operator= (const VideoBuf& src)     = delete;
  VideoBuf (VideoBuf&& src) noexcept            = delete;
  VideoBuf& operator= (VideoBuf&& src) noexcept = delete;

  private:
  /// Скрытый конструктор, т.к возможность конструирования объектов данного класса есть только у utils::dbufs::allocator::CObj
  explicit VideoBuf ();

  //  IVideoBuf overrides
  virtual auto set_format_int (const libs::helpers::uids::minor::id_val& _id) -> void override;
  virtual auto get_format_int () const -> libs::helpers::uids::minor::id_val override;
  virtual auto set_dim_var_int (const Dims& _type, dim_type _val) -> void override;
  virtual auto get_dim_var_int (const Dims& _type) const -> dim_type override;
  virtual auto get_dim_vars_int () const -> const DimVars& override;
  virtual auto set_flag_int (const BufFlags& _type, bool _val) -> void override;
  virtual auto get_flag_int (const BufFlags& _type) const -> bool override;
  virtual auto buf_alloc_int (const AllocBufInfo& info) -> void override;
  virtual auto clone_int (IBuf::craw_ptr src, float _perc_copy) -> void override;
  virtual auto swap_int (IBuf& buf) -> void override;
  virtual auto flush_int () -> void override;
  virtual auto check_int (const check_func_type& _obj) const -> bool override;

  AllocBufInfo params_;   //< Параметры, которые использовались при выделении буфера
};
}   // namespace utils::dbufs::video::impl
