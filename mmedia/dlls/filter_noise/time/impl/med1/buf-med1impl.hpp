#pragma once
/**
\file       buf-med1impl.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_time_filter_noise
*/

namespace dlls::filter_noise::time::impl::med1
{
/// Узел буфера для медианной фильтрации во временной области
class BuffMed1Impl final
{
  public:
  //  syn
  using value_type  = short;
  using values_type = std::array< value_type, ::libs::ievents::props::videos::noises::time::ext::consts::max_count_bufs >;

  BuffMed1Impl (CSharedInfoNodeBuffMed::craw_ptr info = nullptr);

  void       update (const value_type& val);
  void       fill (const value_type& val);
  value_type get_relement (int rang = -1) const;

  private:
  values_type                      vals_;   //< значения буферов для данного узла во временной области
  CSharedInfoNodeBuffMed::craw_ptr info_;   //< разделяемая информация между всеми узлами буфера
};
}   // namespace dlls::filter_noise::time::impl::med1
