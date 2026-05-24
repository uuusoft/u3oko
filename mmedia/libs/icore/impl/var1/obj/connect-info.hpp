#pragma once
/**
\file       connect-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
\brief      Объявление типов для информации о соединении объектов графа обработки данных
*/

namespace libs::icore::impl::var1::obj
{
/// Структура для группировки информации о соединении двух объектов графа обработки данных
struct ConnectInfo final {
  //  ext types
  using input_points_type  = std::array< PointInfo, ::libs::ievents::props::mix_mul::consts::max_input_points >;
  using output_points_type = std::array< PointInfo, ::libs::ievents::props::mix_mul::consts::max_output_points >;

  ConnectInfo ()
  {
    count_ins_  = 0;
    count_outs_ = 0;

    for (auto& ins : ins_)
    {
      ins.type_buf_ = Points::input;
    }
  }

  ConnectInfo (const ConnectInfo& src) :
    count_ins_ (src.count_ins_),
    count_outs_ (src.count_outs_),
    ins_ (src.ins_),
    outs_ (src.outs_)
  {
  }

  ConnectInfo&
  operator= (const ConnectInfo& src)
  {
    U3_ASSERT (&src != this);
    ConnectInfo temp (src);
    std::swap (*this, temp);
    return *this;
  }

  input_points_type  ins_;          //<
  output_points_type outs_;         //<
  std::int32_t       count_ins_;    //<
  std::int32_t       count_outs_;   //<
};
}   // namespace libs::icore::impl::var1::obj
