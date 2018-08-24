#pragma once
/**
\file       name-remover.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.03.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace hboost {
/**
  \brief  empty brief
  */
struct NameRemover
{
  NameRemover (const std::string& _name) :
    name_ (_name)
  {
    UASSERT (!name_.empty ());
    boost::interprocess::shared_memory_object::remove (name_.c_str ());
  }

  ~NameRemover ()
  {
    boost::interprocess::shared_memory_object::remove (name_.c_str ());
  }


  private:
  std::string name_;      //< ???
};

}}}      // namespace libs::helpers::hboost
