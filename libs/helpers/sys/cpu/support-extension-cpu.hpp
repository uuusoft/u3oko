#pragma once
/**
\file       support-extension-cpu.hpp
\brief      возращает описание типа процессора через инструкцию cpuid
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace sys { namespace cpu {
/**
  \brief  empty brief
  */
struct SupportExtensionCPU
{
  SupportExtensionCPU ()
  {
    reset ();
  }

  ~SupportExtensionCPU ()
  {}


  void
  reset ()
  {
    id_cpu_.clear ();
    exts_cpu_.clear ();
    return;
  }


  bool
  check (const TypeExtCpu& _prop) const
  {
    return exts_cpu_.end () == exts_cpu_.find (_prop) ? false : true;
  }


  void
  set (const TypeExtCpu& _prop)
  {
    exts_cpu_.insert (_prop);
    return;
  }


  void
  clear (const TypeExtCpu& _prop)
  {
    exts_cpu_.erase (_prop);
    return;
  }

  std::string          id_cpu_;        //< ???
  std::set<TypeExtCpu> exts_cpu_;      //< ???
};

}}}}      // namespace libs::helpers::sys::cpu
