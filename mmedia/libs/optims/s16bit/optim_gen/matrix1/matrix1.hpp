#pragma once
/**
\file       matrix1.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
Функция производит поиск блока, который наиболее всего подходит для текущего и замещает текуший найденным блоком
*/
// old shit
// #define CALCULATE_DIFF_BETWEEN_COLOR_AND_SECOND_STREAM

namespace libs::optim::s16bit::gen::matrix1
{
#if 0
inline bool
check (::libs::optim::io::MCallInfo& info)
{
  if (3 != info.params_.ints_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (info.dsts_.size () < 1)
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  if (4 != info.params_.parrayss_.size ())
  {
    U3_ASSERT_SIGNAL ("failed");
    return false;
  }

  return true;
}

void alu (::libs::optim::io::MCallInfo& info);
void sse2 (::libs::optim::io::MCallInfo& info);
void avx1 (::libs::optim::io::MCallInfo& info);
#endif
}   // namespace libs::optim::s16bit::gen::matrix1
