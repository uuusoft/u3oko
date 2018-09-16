//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       imem.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace mem {
/**
\brief  Опиональный интерфейс памяти. 
        Если он предоставляется объектом-связью, то для передачи блоков данных нужно использовать его.
*/
class IMem
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IMem);

  IMem (const IMem& _src) = delete;
  IMem& operator= (const IMem& _src) = delete;
  //  IMem interface
  virtual void* mem_alloc (int _size, IBlockMem::ptr _hmem)                      = 0;
  virtual bool  mem_free (IBlockMem::ptr _hmem)                                  = 0;
  virtual bool  mem_atomic_call (IBlockMem::cptr _hmem, const IHandlerMem& _obj) = 0;


  protected:
  IMem ()
  {}

  virtual ~IMem ()
  {}
};

}}}      // namespace libs::link::mem
