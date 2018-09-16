//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ipath-obj-ext.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
\brief  Расширенный интерфейс объекта в графе по обработке данных для данной реализации.
        Введен, чтобы избежать ненужных dynamic_cast преобразований типов в реализации.
*/
class IPathObjExt : public ::libs::core::path::IPathObj
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IPathObjExt);

  IPathObjExt ()
  {}

  virtual ~IPathObjExt ()
  {}

  IPathObjExt (const IPathObjExt& _src) = delete;
  IPathObjExt& operator= (const IPathObjExt& _src) = delete;
  /**
  \brief    Функция загрузки свойств из xml.
  \param[in]  _root узел xml.
  */
  void
  load (const base_functs::xml::itn& _root)
  {
    return load_int (_root);
  }
  /**
  \brief      Функция соединения двух объектов.
  \param[in]  _idpt1  индекс выходной точки соединения данного объекта.
  \param[in]  _next   следующий объект, к которому будет подсоединен данный.
  \param[in]  _idpt2  индекс входной точки следующего объектаю
  */
  void
  connect (int _idpt1, IPathObjExt::ptr& _next, int _idpt2)
  {
    return connect_int (_idpt1, _next, _idpt2);
  }


  private:
  //  IPathObjExt interface
  virtual void load_int (const base_functs::xml::itn& _root)                 = 0;
  virtual void connect_int (int _idpt1, IPathObjExt::ptr& _next, int _idpt2) = 0;
};

}}}}}      // namespace libs::icore::impl::var1::obj
