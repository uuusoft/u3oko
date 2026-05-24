#pragma once
/**
\file       transform-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.10.2016
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::dll
{
/// Структура, которая содержит параметры вызова для фильтра обработки данных
struct TransformInfo final {
  U3_HELPER_DISABLE_ACOPY_TYPE (TransformInfo)
  //  ext types
  using tevents_type  = std::list< ::libs::events::IEvent::ptr >;
  using ExpandedTimes = ::libs::helpers::statistic::ExpandedTimes;

  TransformInfo (
    ::libs::bufs::Bufs::ptr* ibuf,
    ::libs::bufs::Bufs::ptr* obuf,
    FilterInfo*              finfo,
    std::uint32_t            iindx,
    std::uint32_t            oindx,
    tevents_type*            pframe_events,
    ExpandedTimes&           exptimes) :

    ibuf_ (ibuf),
    obuf_ (obuf),
    finfo_ (finfo),
    iindx_ (iindx),
    oindx_ (oindx),
    frame_events_ (pframe_events),
    exptimes_ (exptimes)
  {
  }

  ~TransformInfo ()
  {
  }

  ::libs::bufs::Bufs::ptr* ibuf_;           //< Входной буфер данных
  ::libs::bufs::Bufs::ptr* obuf_;           //< Выходной буфер данных
  FilterInfo*              finfo_;          //< Фильтр обработки данных
  std::uint32_t            iindx_;          //< Индекс входной точки фильтра
  std::uint32_t            oindx_;          //< Индекс выходной точки фильтра
  tevents_type*            frame_events_;   //< Список событий, которые произошли на данный момент при обработке данного фрейма (кадр, буфер) данных
  ExpandedTimes&           exptimes_;       //< Вспомогательное поле для оценки времени работы алгоритмов внутри конкретного узла графа
};
}   // namespace libs::icore::impl::var1::obj::dll
