#pragma once
/**
\file       noise_remover3_x86.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_filter

Формула преобразования

koeff_remove_noise1 = [0.0f...1.0f] * 128
koeff_remove_noise2 = [0.0f...1.0f] * 128
koeff_remove_noise1 > koeff_remove_noise2
bound_koeff = (0.0f...0.5f] * 128

diff = ABS( IN[x,y] - OUT[x,y] )
temp_koeff = diff > bound_koeff ? koeff_remove_noise2 : koeff_remove_noise1;

OUT[x,y] = (1.0f - temp_koeff ) * IN[x,y] + temp_koeff * OUT[x,y]
IN[x,y] = OUT[x,y]


Добавил второй набор функций для генерации эффекта ЛСД путем суммирования с переполнением, т.к.
данный набор отличается от предыдущего только осуствием порога и инверитрованием коэффициента

30.05.2016 добавлен третитий вариант, в нем дополнительно введен буфер условий, если текущее значение
в буфере условий больше некого предела, коэффициент выбирается специфический
*/

namespace libs::optim::s16bit::filter::noise::var3
{

inline void
get_params (
  ::libs::optim::io::MCallInfo& info,
  std::array< int, 2 >*&        bound_koeffs,
  std::array< int, 3 >*&        koeffs_remove,
  std::array< int, 1 >*&        bound_cond_koeffs,
  std::array< int, 1 >*&        koeffs_cond_remove)
{
  U3_CHECK (4 == info.params_.evals_.size (), "evals not equal 4");
  U3_CHECK (2 == info.srcs_.size (), "src not equal 2");
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  bound_koeffs       = boost::any_cast< std::array< int, 2 >* > (info.params_.evals_[0]);
  koeffs_remove      = boost::any_cast< std::array< int, 3 >* > (info.params_.evals_[1]);
  bound_cond_koeffs  = boost::any_cast< std::array< int, 1 >* > (info.params_.evals_[2]);
  koeffs_cond_remove = boost::any_cast< std::array< int, 1 >* > (info.params_.evals_[3]);

  U3_CHECK (bound_koeffs, "bound_koeffs empty");
  U3_CHECK (koeffs_remove, "koeff_remove empty");
  U3_CHECK (bound_cond_koeffs, "bound_cond_koeffs empty");
  U3_CHECK (koeffs_cond_remove, "koeffs_cond_remove empty");
}
/**
\brief  первый коэффициент положительный это база, все полседующий отрицательные - это смещения
*/
void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
void avx2 (::libs::optim::io::MCallInfo& info);

}   // namespace libs::optim::s16bit::filter::noise::var3
