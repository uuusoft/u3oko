#pragma once
/**
\file       point-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/
namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
//  forward
class ObjPath;
}}}}}      // namespace libs::icore::impl::var1::obj

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
\brief  Структура связанная с каждой точкой соединения.
        Содержит в себе имя точки и флаг, указвающий, что данная точка будет менять состояние буфера
        и возможно потребуется сохранять буфер данных.
*/
struct PointInfo
{
  /// Constructor.
  explicit PointInfo () :
    type_buffer_ (static_cast<PointFilter> (PointFilter::input)),
    filter_ (0),
    indx_pt_ (0),
    active_ (false)
  {
    UASSERT (self_test ());
  }

  PointInfo (const PointInfo& _src) :
    type_buffer_ (_src.type_buffer_),
    filter_ (_src.filter_),
    indx_pt_ (_src.indx_pt_),
    active_ (_src.active_)

  {
    UASSERT (&_src != this);
    UASSERT (_src.self_test ());
    UASSERT (self_test ());
  }

  ~PointInfo ()
  {}

  PointInfo&
  operator= (const PointInfo& _src)
  {
    PointInfo _temp (_src);
    std::swap (*this, _temp);
    return *this;
  }

  void
  set_info (bool _active = false, const PointFilter& _type_buffer = PointFilter::output)
  {
    active_      = _active;
    type_buffer_ = _type_buffer;
    UASSERT (self_test ());
    return;
  }
  /// Sef test method
  bool
  self_test () const
  {
    const bool _res = true;      //!active_ || filter_  ? true : false;
    UASSERT (_res);
    return _res;
  }

  void
  reset ()
  {
    filter_  = nullptr;
    indx_pt_ = 0;
    active_  = false;
    UASSERT (self_test ());
    return;
  }

  void
  enable ()
  {
    active_ = true;
    UASSERT (self_test ());
    return;
  }

  void
  disable ()
  {
    active_ = false;
    UASSERT (self_test ());
    return;
  }

  bool                active_;           //< Флаг разрешающий передачу данных через данную точку, фактически используется только для выходных точек. Т.к. для отключенных входных ничего не требуется.
  PointFilter         type_buffer_;      //< Тип точки
  var1::obj::ObjPath* filter_;           //< Указатель на объект, которому принадлежит данная точка.
  int                 indx_pt_;          //< Индекс точки в данном направлении объекта.
};
/**
\brief  
*/
inline void
swap (PointInfo& _src1, PointInfo& _src2)
{
  std::swap (_src1.active_, _src2.active_);
  std::swap (_src1.type_buffer_, _src2.type_buffer_);
  std::swap (_src1.filter_, _src2.filter_);
  std::swap (_src1.indx_pt_, _src2.indx_pt_);
  return;
}

}}}}}      // namespace libs::icore::impl::var1::obj
