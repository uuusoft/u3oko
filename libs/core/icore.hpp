#pragma once
/**
\file       icore.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Объявление интерфей ядра по обработки данных.
*/

namespace libs {
/// Пространство имен для ядра для обработки данных.
namespace core {
/**
\brief  Интерфейс ядра по обработки данных.
        Все функции открытого интерфейса должны быть потокобезопасны.
*/
class ICore
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ICore);
  /// Открытый деструктор, т.к. допускаетя полиморфное уделание через указатель на данный тип.
  virtual ~ICore ()
  {}
  /**
  \brief    Функция создания графа обработки данных. Созданный граф требует явного удаления через функцию delete_path.
  \return   указатель на граф.
  */
  path::IPath::weak_ptr
  create_path ()
  {
    return create_path_int ();
  }
  /**
  \brief      Функция получения существующих графов обработки данных ядра.
  \param[in]  _paths  список указателей на активные графы.
  */
  void
  get_paths (std::list<path::IPath::weak_ptr>& _paths)
  {
    return get_paths_int (_paths);
  }
  /**
  \brief      Функция удаления графа.
  \param[in]  _pobj указатель на граф.
  \return     true, при успехе.
  */
  bool
  delete_path (path::IPath::weak_ptr _obj)
  {
    return delete_path_int (_obj);
  }


  protected:
  /// Закрытый конструктор, т.к. это базовый класс и его экземпляры не могут существовать.
  ICore ()
  {}


  private:
  //  ICore interface
  virtual path::IPath::weak_ptr create_path_int ()                                       = 0;
  virtual void                  get_paths_int (std::list<path::IPath::weak_ptr>& _paths) = 0;
  virtual bool                  delete_path_int (path::IPath::weak_ptr _obj)             = 0;
};

}      // namespace core
}      // namespace libs
