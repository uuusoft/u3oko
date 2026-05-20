#pragma once
/**
\file       buf-med1impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

// EAI-REMOVE old shit
namespace dlls::filter_noise::time::impl::med3
{
#if 0
/**
\brief  Узел буфера для медианной фильтрации во временной области.
*/
class BuffMed1Impl3
{
  public:
  // syn
  using std::int16_t value_type;

  BuffMed1Impl3 (SharedInfoNodeBuff::craw_ptr info = nullptr);

  void update (const value_type& val);
  // void fill(  const value_type& val );
  value_type get_relement (int rang = -1) const;

  private:
  SharedInfoNodeBuff::craw_ptr info_;   //<разделяемая информация между всеми узлами буфера
};
#endif
}   // namespace dlls::filter_noise::time::impl::med3
