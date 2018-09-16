#pragma once
/**
\file       connect-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление типов для информации о соединении объектов графа обработки данных.
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
\brief  Структура для группировки информации о соединении двух объектов графа обработки данных.
*/
struct ConnectInfo
{
  //  ext types
  using input_points_type  = std::array<PointInfo, ::libs::ievents::props::mix_mul::consts::max_input_points>;
  using output_points_type = std::array<PointInfo, ::libs::ievents::props::mix_mul::consts::max_output_points>;

  ConnectInfo ()
  {
    count_ins_  = 0;
    count_outs_ = 0;

    for (auto& _ins : ins_)
      {
        _ins.type_buffer_ = PointFilter::input;
      }
  }

  ConnectInfo&
  operator= (const ConnectInfo& source)
  {
    UASSERT (&source != this);

    count_ins_  = source.count_ins_;
    count_outs_ = source.count_outs_;
    ins_        = source.ins_;
    outs_       = source.outs_;
    return *this;
  }

  input_points_type  ins_;             //< ???
  output_points_type outs_;            //< ???
  int                count_ins_;       //< ???
  int                count_outs_;      //< ???
};

}}}}}      // namespace libs::icore::impl::var1::obj
