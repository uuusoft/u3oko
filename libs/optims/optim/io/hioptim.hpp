#pragma once
/**
\file       hioptim.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_lib
\brief      empty brief
*/

namespace libs { namespace optim { namespace io {
/**
  \brief Структура для хранения функции алгоритма для работы в рабочем потоке.
  */
class hioptim
{
  public:
  //  ext types
  typedef std::atomic<funct_mcall_type> store_funct_type;

  explicit hioptim (store_funct_type* _pfunct = nullptr) :
    pfunct_ (_pfunct)
  {}

  ~hioptim ()
  {}

  bool
  self_test () const
  {
    return pfunct_ ? true : false;
  }

  funct_mcall_type
  get () const
  {
    UASSERT (self_test ());
    const funct_mcall_type _ret = pfunct_->load ();
    return _ret;
  }

  void
  set (funct_mcall_type _pfunct)
  {
    UASSERT (self_test ());
    pfunct_->store (_pfunct);
    return;
  }

  void
  set_text (const std::string& _id)
  {
    UASSERT (!_id.empty ());
    id_funct_ = _id;

    return;
  }

  std::string
  get_text () const
  {
    UASSERT (!id_funct_.empty ());
    return id_funct_;
  }


  private:
  store_funct_type* pfunct_;        //< ???
  std::string       id_funct_;      //< ???
};

}}}      // namespace libs::optim::io
