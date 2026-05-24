#pragma once
/**
\file       dim-vars.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_dbufs
*/

namespace utils::dbufs::video
{
/// Перечисление типов переменных, описывающих геометрию буфера с данными
enum class Dims : std::uint32_t
{
  stride    = 0x00,   //< Шаг строки буфера в байтах
  width     = 0x01,   //< Размер ширины буфера в пикселях
  height    = 0x02,   //< Размер высоты буфера в пикселях
  max_bound = 0x04,   //< Максимальное значение данного типа для определения массивов
  unknown   = 0xFF    //< Не определенно для общности
};

inline constexpr std::uint32_t
                 enum_to_raw (const Dims& _val)
{
  return U3_CAST_STATIC< std::uint32_t > (_val);
}

/// Тип для хранения геометрических параметров буфера
class DimVars final
{
  public:
  //  ext types
  using dim_type  = std::uint32_t;
  using dims_type = ::libs::helpers::utils::ValuesStorage< Dims, std::uint32_t, Dims::max_bound, 0u >;

  DimVars ()
  {
    reset ();
  }

  explicit DimVars (const dims_type& _vals) :
    vals_ (_vals)
  {
  }

  dim_type&
  operator[] (const Dims& _indx)
  {
    return vals_[_indx];
  }

  const dim_type&
  operator[] (const Dims& _indx) const
  {
    return vals_[_indx];
  }

  void
  reset ()
  {
    vals_.fill (0);
  }

  private:
  dims_type vals_;
};
}   // namespace utils::dbufs::video
