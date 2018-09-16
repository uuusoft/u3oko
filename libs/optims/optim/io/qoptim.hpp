#pragma once
/**
\file       qoptim.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace io {
/**
\brief  Структура для запроса алгоритма из библиотеки по идентификатору.
*/
struct qoptim
{
  qoptim (const std::string& _id = "") :
    id_ (_id)
  {}

  ~qoptim ()
  {}

  void
  check () const
  {
    CHECK_STATE (!id_.empty (), "failed, empty id");
    return;
  }

  std::string id_;      //< ???
};

}}}      // namespace libs::optim::io
