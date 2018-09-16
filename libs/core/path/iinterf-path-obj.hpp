//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       iinterf-path-obj.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_core
\brief      empty brief
*/

namespace libs { namespace core { namespace path {
/**
\brief  Базовый интерфейс для расширения свойств объекта в графе по обработке данных.
        Запрашивается через вызов функции query из ObjPath.
*/
class IInterfPathObj
{
  friend class ::libs::icore::impl::var1::obj::ObjPath;

  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IInterfPathObj);

  IInterfPathObj (const IInterfPathObj& _src) = delete;
  IInterfPathObj& operator= (const IInterfPathObj& _src) = delete;


  protected:
  /// Конструктор, защищенный, т.к. создание объектов данного типа не предусмотренно.
  IInterfPathObj ()
  {}
  /// Деструктор. Закрываем, удалить данный объект можно только через удаления производного.
  virtual ~IInterfPathObj ()
  {}
};

}}}      // namespace libs::core::path
