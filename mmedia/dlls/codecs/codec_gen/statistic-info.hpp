#pragma once
/**
\file       statistic-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
struct StatisticInfo final {
  public:
  //  ext types
  using stages_type = std::unordered_map< std::string, StatisticStage >;

  StatisticInfo ()  = default;
  ~StatisticInfo () = default;

  bool
  self_test () const
  {
    U3_ASSERT (!stages_.empty ());
    return !stages_.empty ();
  }

  void
  update (const std::string& id, std::size_t val)
  {
    stages_[id].update (val);
  }

  void
  reset ()
  {
    stages_.clear ();
  }

  stages_type stages_;   //<
};
}   // namespace dlls::codecs::codec_gen
