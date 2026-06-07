#pragma once
/**
\file       node-id.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_core_lib
*/

namespace libs::core::graph
{
/// Индентификатор объекта графа обработки данных
class NodeID final
{
  public:
  //  ext types
  using name_id_type  = std::string;
  using name_dll_type = std::string;

  /// Конструктор
  /// \param[in]  name   идентификатор узла
  /// \param[in]  name_dll имя библиотеки, использованной для создания узла
  explicit NodeID (const name_id_type& name = "", const name_dll_type& name_dll = "");
  virtual ~NodeID () = default;

  /// Функция возвращает имя идентификатора
  const name_id_type get_name () const;
  name_id_type&      update_name ();

  /// Функция возвращает имя идентификатора
  const name_dll_type& get_name_dll () const;
  name_dll_type&       update_name_dll ();

  /// Функция сравнения меньше для использования в а контейнерах
  bool operator< (const NodeID& obj) const;

  /// Функция сравнениядля использования в а контейнерах
  bool operator== (const NodeID& obj) const;

  /// Функция проверки корректности построения экземпляра класса
  bool check () const;

  private:
  name_id_type  id_node_name_;       //< Идентификатор объекта. Гарантирутся уникальность в графе и совпадение с идентификатором из xml узла, на основе которого создан данный объект
  name_dll_type id_node_name_dll_;   //< Имя библиотеки, которая использовалась для создания экземляра узла

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const NodeID& src);
NodeID      tag_invoke (::boost::json::value_to_tag< NodeID >, const ::boost::json::value& jvs);
std::string get_ext_graph_node_id (const NodeID&);
}   // namespace libs::core::graph

BOOST_CLASS_EXPORT_KEY (::libs::core::graph::NodeID);

namespace std
{
template<>
struct hash< ::libs::core::graph::NodeID > {
  std::size_t
  operator() (const ::libs::core::graph::NodeID& val) const
  {
    return std::hash< ::libs::core::graph::NodeID::name_id_type > () (val.get_name ());
  }
};
}   // namespace std
