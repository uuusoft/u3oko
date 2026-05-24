#pragma once
/**
\file       point-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/
namespace libs::icore::impl::var1::obj
{
//  forward
class ObjGraph;
}   // namespace libs::icore::impl::var1::obj

namespace libs::icore::impl::var1::obj
{
/// Структура связанная с каждой точкой соединения
/// Содержит в себе имя точки и флаг, указвающий, что данная точка будет менять состояние буфера и возможно потребуется сохранять буфер данных
struct PointInfo final {
  explicit PointInfo () noexcept :
    type_buf_ (Points::input),
    filter_ (0),
    indx_pt_ (0),
    active_ (false)
  {
    U3_ASSERT_NT (self_test (), "self_test");
  }

  PointInfo (const PointInfo& src) :
    type_buf_ (src.type_buf_),
    filter_ (src.filter_),
    indx_pt_ (src.indx_pt_),
    active_ (src.active_)
  {
    U3_ASSERT (&src != this);
    U3_ASSERT (src.self_test ());
    U3_ASSERT (self_test ());
  }

  ~PointInfo ()
  {
  }

  PointInfo&
  operator= (const PointInfo& src)
  {
    PointInfo temp (src);
    std::swap (*this, temp);
    return *this;
  }

  void
  set_info (
    bool          active   = false,
    const Points& type_buf = Points::output)
  {
    active_   = active;
    type_buf_ = type_buf;
    U3_ASSERT (self_test ());
  }

  /// Sef test method
  bool
  self_test () const
  {
    const bool res = true;   //! active_ || filter_  ? true : false;
    U3_ASSERT (res);
    return res;
  }

  void
  reset ()
  {
    filter_  = nullptr;
    indx_pt_ = 0;
    active_  = false;
    U3_ASSERT (self_test ());
  }

  void
  enable ()
  {
    active_ = true;
    U3_ASSERT (self_test ());
  }

  void
  disable ()
  {
    active_ = false;
    U3_ASSERT (self_test ());
  }

  bool                 active_;     //< Флаг разрешающий передачу данных через данную точку, фактически используется только для выходных точек. Т.к. для отключенных входных ничего не требуется
  Points               type_buf_;   //< Тип точки
  var1::obj::ObjGraph* filter_;     //< Указатель на объект, которому принадлежит данная точка
  std::int32_t         indx_pt_;    //< Индекс точки в данном направлении объекта
};


inline void
swap (PointInfo& src1, PointInfo& src2)
{
  std::swap (src1.active_, src2.active_);
  std::swap (src1.type_buf_, src2.type_buf_);
  std::swap (src1.filter_, src2.filter_);
  std::swap (src1.indx_pt_, src2.indx_pt_);
}
}   // namespace libs::icore::impl::var1::obj
