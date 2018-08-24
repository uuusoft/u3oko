//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       mem-impl-any-proc.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace anyproc {
/**
  \brief  Релизация памяти для канала передачи данных.
  */
class MemImplAnyProc : public ::libs::link::mem::IMem
{
  public:
  MemImplAnyProc ();

  virtual ~MemImplAnyProc ();

  //  IMem impl
  virtual void* mem_alloc (int _size, IBlockMem::ptr _hmem) override;
  virtual bool  mem_free (IBlockMem::ptr _hmem) override;
  virtual bool  mem_atomic_call (IBlockMem::cptr _hmem, const IHandlerMem& _obj) override;
};

}}}}      // namespace libs::ilink::impl::anyproc
