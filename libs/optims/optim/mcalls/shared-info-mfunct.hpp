#pragma once
/**
\file       shared-info-mfunct.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace mcalls {
/**
  \brief  Структура, которая разделяется между всеми рабочими потоками при вызове.
  */
class SharedInfoMFunct
{
  public:
  //  ext types
  using barier_type     = boost::barrier;
  using barier_ptr_type = std::unique_ptr<barier_type>;

  SharedInfoMFunct () :
    exit_request_ (false)
  {}

  ~SharedInfoMFunct ()
  {}

  SharedInfoMFunct (const SharedInfoMFunct& _src) = delete;
  SharedInfoMFunct& operator= (const SharedInfoMFunct& _src) = delete;

  bool            exit_request_;      //<  ???
  barier_ptr_type bstart_;            //<  ???
  barier_ptr_type bend_;              //<  ???
};

}}}      // namespace libs::optim::mcalls
