//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       statistic-stage.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
  \brief  empty brief
  */
struct StatisticStage
{
  public:
  StatisticStage ()
  {
    size_datas_[0] = UUU_ICAST_SIZE_T (-1);
    size_datas_[1] = 0;
    size_datas_[2] = 0;
  }

  ~StatisticStage ()
  {}

  bool
  self_test () const
  {
    return true;
  }

  void
  update (std::size_t _val)
  {
    UASSERT (_val > 0);
    size_datas_[0] = std::min<std::size_t> (size_datas_[0], _val);
    size_datas_[1] = std::max<std::size_t> (size_datas_[1], _val);
    size_datas_[2] += _val;
    return;
  }

  std::array<std::size_t, 3> size_datas_;      //< min, max, sum
};

}}}      // namespace dlls::codecs::codec_gen
