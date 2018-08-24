#pragma once
/**
\file       int2type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace utils {
/**
  \brief                Шаблон для генерации целочисленных типов от перечислений и т.п.
  \tparam TTBase        Базовый тип, должен быть достаточно широким для размещения всех возможножных значени.
  \tparam TTDef         Значение по умолчанию типа.
  \tparam TTFakeIndent  Фальшивый базовый класс для генерации нового типа.
  */
template <
  typename TTBase,
  TTBase TTDef,
  class TTFakeIdent>
class Int2Type
{
  public:
  //  ext types
  using value_type = TTBase;
  using item_type  = Int2Type<TTBase, TTDef, TTFakeIdent>;
  /// Конструктор по умолчанию
  Int2Type () :
    val_ (TTDef)
  {}
  /// Конструктор c начальным значением
  explicit Int2Type (const TTBase& _val) :
    val_ (_val)
  {}

  void
  set (const TTBase& _val)
  {
    val_ = _val;
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
    return val_ != (TTBase)-1;
  }

  bool
  operator== (const item_type& _val) const
  {
    return val_ == _val.val_;
  }

  bool
  operator!= (const item_type& _val) const
  {
    return val_ != _val.val_;
  }

  bool
  operator< (const item_type& _val) const
  {
    return val_ < _val.val_;
  }

  bool
  operator> (const item_type& _val) const
  {
    return val_ > _val.val_;
  }

  bool
  operator<= (const item_type& _val) const
  {
    return val_ <= _val.val_;
  }

  bool
  operator>= (const item_type& _val) const
  {
    return val_ >= _val.val_;
  }
  /// возвращает ссылку на внутреннее значение (для использования в switch, к примеру)
  const TTBase&
  to_val () const
  {
    return val_;
  }

  template <
    class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (val_);
    return;
  }


  private:
  TTBase val_;      //< ???
};

}}}      // namespace libs::helpers::utils
