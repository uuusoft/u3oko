#pragma once
/**
\file       node-graph-info.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
/// Структура для группировки информации о узле графа обработки данных
struct NodeGraphInfo {
  explicit NodeGraphInfo (const std::string& id = "", const std::string& name_dll = "");
  virtual ~NodeGraphInfo () = default;

  bool               check () const;
  const std::string& get_id () const;
  std::string&       update_id ();
  const std::string& get_name_dll () const;
  std::string&       update_name_dll ();

  private:
  std::string id_;         //< Уникальный идентификатор узла в графе
  std::string name_dll_;   //< Имя динамической библиотеки, которая хранит в себе код узла

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const NodeGraphInfo& src);
NodeGraphInfo tag_invoke (::boost::json::value_to_tag< NodeGraphInfo >, const ::boost::json::value& jvs);
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::NodeGraphInfo);
