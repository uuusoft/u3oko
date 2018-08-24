//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       iblock-mem.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace mem {
/**
  \brief  empty brief
  */
class IBlockMem
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IBlockMem);

  IBlockMem ()
  {}

  virtual ~IBlockMem ()
  {}
};

}}}      // namespace libs::link::mem
