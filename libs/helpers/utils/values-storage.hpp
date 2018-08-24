//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       values-storage.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Объявление хранилища значений.
*/

namespace libs { namespace helpers { namespace utils {
/**
  \brief    Класс для хранения значений определенного типа по ключам. Достаточно частая операция в свойствах и т.п.
  \tparam   TTKey   тип ключа.
  \tparam   TTVal   тип значения.
  \tparam   max_val   максимальное значение ключа + 1 для массива
  */
template <
  typename TTKey,
  typename TTVal,
  int max_val>
class ValuesStorage
{
  public:
  //  ext types
  using raw_value_type   = TTVal;                                                          //< тип значения
  using key_type         = TTKey;                                                          //< тип ключа для поиска значения в массиве.
  using check_funct_type = std::function<bool(const TTKey& _key, const TTVal& _val)>;      //< тип функции доступа к значению при работе с массивом по диапазонам.

  ValuesStorage ()
  {}

  ~ValuesStorage ()
  {}
  /**
    \brief      Установка значения по ключу.
    \param[in]  _key    ключ значения.
    \param[in]  _val    новое значение.
    */
  void
  set (const key_type& _key, const raw_value_type& _val)
  {
    const std::size_t _ikey = UUU_ICAST_SIZE_T (_key);
    vals_[_ikey]            = _val;
    return;
  }
  /**
    \brief      Получение значения по ключу.
    \param[in]  _key    ключ значения.
    \return     значение ключа.
    */
  raw_value_type
  get (const key_type& _key) const
  {
    const std::size_t _ikey = UUU_ICAST_SIZE_T (_key);
    //return boost::any_cast<raw_value_type>( vals_[ _ikey ] );
    return vals_[_ikey];
  }
  /**
    \brief      Установка значений.
    \param[in]  _val  новое значение для всего контейнера.
    */
  void
  fill (const raw_value_type& _val)
  {
    std::fill (vals_.begin (), vals_.end (), _val);
    return;
  }


  private:
  //  int types
  using values_type = std::array<raw_value_type, max_val>;

  mutable values_type vals_;      //< собственно массив значений.

  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (vals_);
    return;
  }
};

}}}      // namespace libs::helpers::utils
