#pragma once
/**
\file       statistic-stage.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
struct StatisticStage final {
  public:
  StatisticStage ()
  {
  }

  ~StatisticStage ()
  {
  }

  bool
  self_test () const
  {
    return true;
  }

  void
  update (std::uint64_t val)
  {
    U3_ASSERT (val > 0);
    size_datas_[0] = std::min< std::uint64_t > (size_datas_[0], val);
    size_datas_[1] = std::max< std::uint64_t > (size_datas_[1], val);
    size_datas_[2] += val;
  }

  std::array< std::uint64_t, 3 > size_datas_ = { 0xFFFFFFFFFFFFFFFFull, 0, 0 };   //< min, max, sum
};
}   // namespace dlls::codecs::codec_gen
