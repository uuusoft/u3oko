#pragma once
/**
\file       filter-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj
{
/// Тип для группировки свойств
struct FilterInfo final {
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (FilterInfo)

  FilterInfo ()
  {
  }

  ~FilterInfo ()
  {
  }

  FilterInfo (const FilterInfo& src) :
    pts_ (src.pts_),
    id_obj_ (src.id_obj_)
  {
  }

  FilterInfo&
  operator= (const FilterInfo& src)
  {
    FilterInfo temp (src);
    std::swap (*this, temp);
    return *this;
  }

  void
  correct ()
  {
    for (PointInfo& pt : pts_.ins_)
    {
      pt.filter_  = 0;
      pt.indx_pt_ = 0;
    }

    for (PointInfo& pt : pts_.outs_)
    {
      pt.filter_  = 0;
      pt.indx_pt_ = 0;
    }
  }

  ConnectInfo                 pts_;      //<
  ::libs::core::graph::NodeID id_obj_;   //< Идентификатор узла в графе данного объекта
};
}   // namespace libs::icore::impl::var1::obj
