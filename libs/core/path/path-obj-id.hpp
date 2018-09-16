#pragma once
/**
\file       path-obj-id.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Объявление идентификатора объекта графа.
*/

namespace libs { namespace core { namespace path {
/**
\brief  Индентификатор объекта графа обработки данных.
*/
class PathObjID
{
  public:
  //  ext types
  using name_id_type  = std::string;
  using name_dll_type = std::string;
  /**
  \brief      Конструктор.
  \param[in]  _name   идентификатор узла.
  \param[in]  _name_dll имя библиотеки, использованной для создания узла.
  */
  explicit PathObjID (const name_id_type& _name = "", const name_dll_type& _name_dll = "");
  /// Деструктор.
  virtual ~PathObjID ();
  /**
  \brief  Функция возвращает имя идентификатора.
  \return имя.
  */
  const name_id_type get_name () const;
  /**
  \brief  Функция возвращает имя идентификатора.
  \return имя.
  */
  const name_dll_type& get_name_dll () const;
  /**
  \brief      Функция сравнения меньше. для использования в а. контейнерах.
  \param[in]  _obj  объект сравнения.
  \return     true, если this меньше _obj
  */
  bool operator< (const PathObjID& _obj) const;
  /**
  \brief  Функция проверки корректности построения экземпляра класса.
  \return true при успехе.
  */
  bool check () const;


  private:
  name_id_type  id_node_name_;          //< Идентификатор объекта. Гарантирутся уникальность в графе и совпадение с идентификатором из xml узла, на основе которого создан данный объект.
  name_dll_type id_node_name_dll_;      //< Имя библиотеки, которая использовалась для создания экземляра узла.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}      // namespace libs::core::path

BOOST_CLASS_EXPORT_KEY (::libs::core::path::PathObjID);
