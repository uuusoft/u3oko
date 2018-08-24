#pragma once
/**
\file       cpu-info.hpp
\brief      Class for checking CPU
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace sys { namespace cpu {
/**
  \brief  empty brief
  */
class CpuInfo
{
  public:
  CpuInfo ();


  TypeExtCpu get_max () const;

  TypeExtCpu get_min () const;

  bool is_less (const TypeExtCpu& _op1, const TypeExtCpu& _op2) const;

  void full_text (std::string& _info);


  protected:
  SupportExtensionCPU     exts_;                //< ???
  TextExtCpu              texter_;              //< ???
  std::vector<TypeExtCpu> ext_cpu_ranged_;      //< ???
  std::vector<TypeExtCpu> all_ext_;             //< ???
};

}}}}      // namespace libs::helpers::sys::cpu
