#pragma once
/**
\file       node-id.hpp
\author     Erashov Anton erashov2026@proton.me
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
  using id_name_type  = std::string;
  using dll_name_type = std::string;

  /// Конструктор
  /// \param[in]  name   идентификатор узла
  /// \param[in]  name_dll имя библиотеки, использованной для создания узла
  explicit NodeID (id_name_type = "", dll_name_type = "");
  virtual ~NodeID () = default;

  auto get_name () const -> const id_name_type;
  auto update_name () -> id_name_type&;

  auto get_name_dll () const -> const dll_name_type&;
  auto update_name_dll () -> dll_name_type&;

  bool operator< (const NodeID& obj) const;
  bool operator== (const NodeID& obj) const;

  /// Функция проверки корректности построения экземпляра класса
  bool check () const;

  private:
  id_name_type  id_node_name_;       //< Идентификатор объекта. Гарантирутся уникальность в графе и совпадение с идентификатором из xml узла, на основе которого создан данный объект
  dll_name_type id_node_name_dll_;   //< Имя библиотеки, которая использовалась для создания экземляра узла

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const NodeID& src);
NodeID      tag_invoke (::boost::json::value_to_tag< NodeID >, const ::boost::json::value& jvs);
std::string get_ext_graph_node_id (const NodeID&);
}   // namespace libs::core::graph

BOOST_CLASS_EXPORT_KEY (::libs::core::graph::NodeID);

namespace boost
{
template<>
struct hash< ::libs::core::graph::NodeID > {
  std::size_t
  operator() (const ::libs::core::graph::NodeID& val) const
  {
    return std::hash< ::libs::core::graph::NodeID::id_name_type > () (val.get_name ());
  }
};
}   // namespace boost
