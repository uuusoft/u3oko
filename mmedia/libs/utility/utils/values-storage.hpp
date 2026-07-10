#pragma once
/**
\file       values-storage.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
\brief      Объявление хранилища значений
*/

namespace libs::utility::utils
{
// EAI-REFACT
/// Класс для хранения значений определенного типа по ключам
/// Достаточно частая операция в свойствах и т.п
/// \tparam   TTKey   тип ключа
/// \tparam   TTVal   тип значения
/// \tparam   max_key максимальное значение ключа + 1 для массива
/// \tparam   def_val значения по умолчанию для сброса
template<
  typename TTKey,
  typename TTVal,
  TTKey max_key,
  TTVal def_val,
  typename TTStorage = std::array< TTVal, U3_CAST_SIZE_T_FORCE (max_key) > >
class ValuesStorage final
{
  public:
  //  ext types
  using raw_value_type  = TTVal;                                                        //< тип значения
  using key_type        = TTKey;                                                        //< тип ключа для поиска значения в массиве
  using check_func_type = std::function< bool (const TTKey& key, const TTVal& val) >;   //< тип функции доступа к значению при работе с массивом по диапазонам

  ValuesStorage ()
  {
    fill (def_val);
  }

  ~ValuesStorage () = default;

  raw_value_type&
  operator[] (const key_type& indx)
  {
    return raw_vals_[std::to_underlying (indx)];
  }

  const raw_value_type&
  operator[] (const key_type& indx) const
  {
    return raw_vals_[std::to_underlying (indx)];
  }

  /// Установка значений
  /// \param[in]  val  новое значение для всего контейнера
  void
  fill (const raw_value_type& val)
  {
    std::fill (raw_vals_.begin (), raw_vals_.end (), val);
  }

  private:
  mutable TTStorage raw_vals_;   //< значения

  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (raw_vals_);
  }
};
}   // namespace libs::utility::utils
