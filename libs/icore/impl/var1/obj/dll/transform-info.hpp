#pragma once
/**   
\file       transform-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.10.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace dll {
/**
\brief  Структура, которая содержит параметры вызова для фильтра обработки данных.
*/
struct TransformInfo
{
  //  ext types
  using events_type = std::list<::libs::events::IEvent::ptr>;

  TransformInfo () :

    ibuff_ (nullptr),
    obuff_ (nullptr),
    finfo_ (nullptr),
    pframe_events_ (nullptr),
    iindx_ (0),
    oindx_ (0)
  {}

  TransformInfo (
    Buffs::ptr*  _ibuff,
    Buffs::ptr*  _obuff,
    FilterInfo*  _finfo,
    std::size_t  _iindx,
    std::size_t  _oindx,
    events_type* _pframe_events) :

    ibuff_ (_ibuff),
    obuff_ (_obuff),
    finfo_ (_finfo),
    iindx_ (_iindx),
    oindx_ (_oindx),
    pframe_events_ (_pframe_events)
  {}

  ~TransformInfo ()
  {}

  TransformInfo (const TransformInfo& _src) = delete;
  TransformInfo& operator= (const TransformInfo& _src) = delete;

  Buffs::ptr*  ibuff_;              //< Входной буфер данных.
  Buffs::ptr*  obuff_;              //< Выходной буфер данных.
  FilterInfo*  finfo_;              //< Фильтр обработки данных.
  std::size_t  iindx_;              //< Индекс входной точки фильтра.
  std::size_t  oindx_;              //< Индекс выходной точки фильтра.
  events_type* pframe_events_;      //< Список событий, которые произошли на данный момент при обработке данного фрейма (кадр, буфер) данных.
};

}}}}}}      // namespace libs::icore::impl::var1::obj::dll
