#pragma once
/**
\file       video-buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Объявление реализации буфера под видео.
*/
namespace utils { namespace dbuffs { namespace video { namespace impl {
/**
  \brief  Реализация интерфейса для управления буфера с видео данными.
  */
class VideoBuff : public IVideoBuff
{
  friend class utils::dbuffs::allocator::BuffAllocator;

  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoBuff);

  virtual ~VideoBuff ();

  VideoBuff (const VideoBuff& _src) = delete;
  VideoBuff& operator= (const VideoBuff& _src) = delete;


  private:
  //  int types
  using flags_type    = libs::helpers::utils::ValuesStorage<TypeFlagsBuff, bool, UUU_ICAST_SIZE_T (TypeFlagsBuff::max_bound)>;
  using dim_vars_type = libs::helpers::utils::ValuesStorage<TypeDimVar, dim_type, UUU_ICAST_SIZE_T (TypeDimVar::max_bound)>;
  /// Скрытый конструктор. Т.к. возможность конструирования объектов данного класса есть только у utils::dbuffs::allocator::CObj.
  explicit VideoBuff ();
  //  IVideoBuff overrides
  virtual void         set_format_int (const cuuid& _id) override;
  virtual const cuuid& get_format_int () const override;
  virtual void         set_dim_var_int (const TypeDimVar& _type, dim_type _val) override;
  virtual dim_type     get_dim_var_int (const TypeDimVar& _type) const override;
  virtual void         set_flag_int (const TypeFlagsBuff& _type, bool _val) override;
  virtual bool         get_flag_int (const TypeFlagsBuff& _type) const override;
  virtual void         balloc_int (const AllocBuffInfo& _info) override;
  virtual void         clone_int (IBuff::craw_ptr _src, float _perc_copy) override;
  virtual void         swap_int (IBuff& _buff) override;
  virtual void         flush_int () override;
  virtual bool         check_int (const check_funct_type& _obj) const override;

  AllocBuffInfo va_info_;       //< Параметры, которые использовались при выделении буфера.
  flags_type    flags_;         //< Массив для признаков кадра.
  dim_vars_type dim_vars_;      //< Массив для переменных геометрии кадра.
};

}}}}      // namespace utils::dbuffs::video::impl
