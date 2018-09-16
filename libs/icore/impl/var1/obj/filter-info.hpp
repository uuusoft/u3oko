#pragma once
/**
\file       filter-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
\brief  Тип для группировки свойств
*/
struct FilterInfo
{
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (FilterInfo);

  FilterInfo ()
  {}

  ~FilterInfo ()
  {}

  FilterInfo (const FilterInfo& _src)
  {
    (*this) = _src;
    return;
  }

  FilterInfo&
  operator= (const FilterInfo& _src)
  {
    pts_ = _src.pts_;
    return *this;
  }

  void
  correct ()
  {
    for (PointInfo& _pt : pts_.ins_)
      {
        _pt.filter_  = 0;
        _pt.indx_pt_ = 0;
      }

    for (PointInfo& _pt : pts_.outs_)
      {
        _pt.filter_  = 0;
        _pt.indx_pt_ = 0;
      }
    return;
  }

  ConnectInfo pts_;      //< ???
};

}}}}}      // namespace libs::icore::impl::var1::obj
