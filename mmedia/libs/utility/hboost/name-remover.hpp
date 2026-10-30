#pragma once
/**
\file       name-remover.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.03.2016
*/

namespace libs::utility::hboost
{
struct NameRemover final {
  NameRemover (const std::string& name) :
    name_ (name)
  {
    ::libs::utility::checks::throw_ifn (!name_.empty ());
    boost::interprocess::shared_memory_object::remove (name_.c_str ());
  }

  ~NameRemover ()
  {
    boost::interprocess::shared_memory_object::remove (name_.c_str ());
  }

  private:
  std::string name_;   //<
};
}   // namespace libs::utility::hboost
