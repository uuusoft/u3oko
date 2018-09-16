#pragma once
/**
\file       statistic-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
\brief  empty brief
*/
struct StatisticInfo
{
  public:
  //  ext types
  using stages_type = std::map<std::string, StatisticStage>;

  StatisticInfo ()
  {}

  ~StatisticInfo ()
  {}

  bool
  self_test () const
  {
    UASSERT (!stages_.empty ());
    return !stages_.empty ();
  }

  void
  update (const std::string& _id, std::size_t _val)
  {
    stages_[_id].update (_val);
    return;
  }

  void
  reset ()
  {
    stages_.clear ();
    return;
  }

  stages_type stages_;      //< ???
};

}}}      // namespace dlls::codecs::codec_gen
