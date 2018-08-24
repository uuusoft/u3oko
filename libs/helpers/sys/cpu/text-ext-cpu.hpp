#pragma once
/**
\file       text-ext-cpu.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace sys { namespace cpu {
/**
  \brief  empty brief
  */
class TextExtCpu
{
  public:
  TextExtCpu ();

  std::string get_text (const TypeExtCpu& _val) const;

  TypeExtCpu get_val (const std::string& _txt) const;


  private:
  //  int types
  using str2val_type = std::map<std::string, TypeExtCpu>;
  using val2str_type = std::map<TypeExtCpu, std::string>;

  str2val_type txt2val_;      //< ???
  val2str_type val2txt_;      //< ???
};

}}}}      // namespace libs::helpers::sys::cpu
