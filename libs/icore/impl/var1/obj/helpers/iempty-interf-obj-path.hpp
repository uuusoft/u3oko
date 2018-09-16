//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       iempty-interf-obj-path.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace helpers {
/**
\brief  Пустая реализация интерфейса-расширения, используется как сигнал поддержки интерфейса объектом графа, если кроме этого факта ничего больше не требуется
        Можно считать возврат данного объекта как флаг true.
*/
class IEmptyInterfObjPath : public core::path::IInterfPathObj
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IEmptyInterfObjPath);

  IEmptyInterfObjPath ()
  {}

  IEmptyInterfObjPath (const IEmptyInterfObjPath& _src) = delete;
  IEmptyInterfObjPath& operator= (const IEmptyInterfObjPath& _src) = delete;

  virtual ~IEmptyInterfObjPath ()
  {}
};

}}}}}}      // namespace libs::icore::impl::var1::obj::helpers
