#pragma once
/**
\file       video-buf.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  virtual ~VideoBuf ();

  VideoBuf (const VideoBuf& src)            = delete;
  VideoBuf& operator= (const VideoBuf& src) = delete;

  private:
  /// Скрытый конструктор, т.к возможность конструирования объектов данного класса есть только у utils::dbufs::allocator::CObj
  explicit VideoBuf ();

  //  IVideoBuf overrides
  virtual void                               set_format_int (const libs::helpers::uids::minor::id_val& _id) override;
  virtual libs::helpers::uids::minor::id_val get_format_int () const override;
  virtual void                               set_dim_var_int (const Dims& _type, dim_type _val) override;
  virtual dim_type                           get_dim_var_int (const Dims& _type) const override;
  virtual const DimVars&                     get_dim_vars_int () const override;
  virtual void                               set_flag_int (const BufFlags& _type, bool _val) override;
  virtual bool                               get_flag_int (const BufFlags& _type) const override;
  virtual void                               buf_alloc_int (const AllocBufInfo& info) override;
  virtual void                               clone_int (IBuf::craw_ptr src, float _perc_copy) override;
  virtual void                               swap_int (IBuf& buf) override;
  virtual void                               flush_int () override;
  virtual bool                               check_int (const check_func_type& _obj) const override;

  AllocBufInfo params_;   //< Параметры, которые использовались при выделении буфера
};
}   // namespace utils::dbufs::video::impl
