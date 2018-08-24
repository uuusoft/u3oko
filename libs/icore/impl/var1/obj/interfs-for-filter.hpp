#pragma once
/**
\file       interfs-for-filter.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
  \brief  empty brief
  */
struct InterfsForFilter
{
  InterfsForFilter ()
  {}

  ~InterfsForFilter ()
  {}

  void
  check () const
  {
    CHECK_STATE (!lib_name_.empty (), "failed, lib name empty");
    return;
  }

  std::string lib_name_;      //< ???
};

}}}}}      // namespace libs::icore::impl::var1::obj
