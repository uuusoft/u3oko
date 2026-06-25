#pragma once
/**
\file       int2type.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::utils
{
/// Шаблон для генерации целочисленных типов от перечислений и тп
/// \tparam TTBase        Базовый тип, должен быть достаточно широким для размещения всех возможножных значений
/// \tparam TTDef         Значение по умолчанию для базового типа
/// \tparam TTFakeIndent  Фальшивый базовый класс для генерации нового типа
template< typename TTBase, TTBase TTDef, class TTFakeIdent >
class Int2Type
{
  public:
  //  ext types
  using value_type = TTBase;
  using item_type  = Int2Type< TTBase, TTDef, TTFakeIdent >;

  Int2Type ()  = default;
  ~Int2Type () = default;

  explicit Int2Type (const TTBase& val) :
    val_ (val)
  {
  }

  void
  set (const TTBase& val)
  {
    val_ = val;
  }

  item_type
  operator++ ()
  {
    ++val_;
    return *this;
  }

  item_type
  operator++ (int)
  {
    item_type Tmp = *this;
    val_++;
    return Tmp;
  }

  item_type
  operator-- ()
  {
    --val_;
    return *this;
  }

  item_type
  operator-- (int)
  {
    item_type Tmp = *this;
    val_--;
    return Tmp;
  }

  bool
  is_valid () const
  {
    return val_ != (TTBase) -1;
  }

  bool
  operator== (const item_type& val) const
  {
    return val_ == val.val_;
  }

  bool
  operator!= (const item_type& val) const
  {
    return val_ != val.val_;
  }

  bool
  operator< (const item_type& val) const
  {
    return val_ < val.val_;
  }

  bool
  operator> (const item_type& val) const
  {
    return val_ > val.val_;
  }

  bool
  operator<= (const item_type& val) const
  {
    return val_ <= val.val_;
  }

  bool
  operator>= (const item_type& val) const
  {
    return val_ >= val.val_;
  }

  /// возвращает ссылку на внутреннее значение (для использования в switch, к примеру)
  const TTBase&
  to_val () const
  {
    return val_;
  }

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (val_);
  }

  private:
  TTBase val_ = TTDef;   //<
};
}   // namespace libs::helpers::utils
