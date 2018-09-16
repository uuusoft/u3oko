//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       node-path-info.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  Структура для группировки информации о узле графа обработки данных.
*/
struct NodePathInfo
{
  explicit NodePathInfo (const std::string& _id = "", const std::string& _name_dll = "");

  virtual ~NodePathInfo ();

  bool check () const;

  std::string& update_id ();

  std::string& update_name_dll ();


  private:
  std::string id_;            //< Уникальный идентификатор узла в графе.
  std::string name_dll_;      //< Имя динамической библиотеки, которая хранит в себе код узла.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::NodePathInfo);
