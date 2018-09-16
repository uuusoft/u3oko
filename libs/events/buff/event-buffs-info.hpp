#pragma once
/**
\file       event-buffs-info.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_events
*/

namespace libs { namespace events { namespace buff {
//  syn
using ::utils::dbuffs::video::consts::offs::off_buff_type;
/**
\brief  Функция проверка валидности узла для загрузки буфера. 
*/
inline bool
is_valid_node (const base_functs::xml::itn& _node)
{
  return _node->name () == consts::node_name ? true : false;
}
/**
\brief  Сохранение параметров стандартного буфера для всех свойств.
*/
struct EventBuffsInfo
{
  public:
  explicit EventBuffsInfo (const off_buff_type& _src = utils::dbuffs::video::consts::offs::invalid, const off_buff_type& _dst = utils::dbuffs::video::consts::offs::invalid);

  ~EventBuffsInfo ();

  void check (bool _check_src = true, bool _check_dst = true) const;

  void load (const base_functs::xml::itn& _node);

  off_buff_type indx_sbuff_;      //< Индекс буфера-источника.
  off_buff_type indx_dbuff_;      //< Индекс буфера-назначения.


  protected:
  virtual void load_int (const base_functs::xml::itn& _node);


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}}      // namespace libs::events::buff

BOOST_CLASS_EXPORT_KEY (::libs::events::buff::EventBuffsInfo);
