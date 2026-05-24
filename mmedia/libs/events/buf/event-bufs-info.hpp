#pragma once
/**
\file       event-bufs-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_events
*/

namespace libs::events::buf::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;
}

namespace libs::events::buf
{
/// Функция проверка валидности узла для загрузки буфера
bool is_valid_node (const ::pugi::xml_named_node_iterator& node);

/// Сохранение параметров стандартного буфера для всех свойств
struct EventBufsInfo {
  public:
  explicit EventBufsInfo (
    const syn::off_buf_type& src = utils::dbufs::video::consts::offs::invalid,
    const syn::off_buf_type& dst = utils::dbufs::video::consts::offs::invalid);

  virtual ~EventBufsInfo ();

  void check (bool check_src = true, bool check_dst = true);

  syn::off_buf_type indx_sbuf_;   //< Индекс буфера-источника
  syn::off_buf_type indx_dbuf_;   //< Индекс буфера-назначения

  protected:
  virtual void check_int ();
  virtual void correct_int ();

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const EventBufsInfo& src);
EventBufsInfo tag_invoke (::boost::json::value_to_tag< EventBufsInfo >, const ::boost::json::value& jv);
}   // namespace libs::events::buf

BOOST_CLASS_EXPORT_KEY (::libs::events::buf::EventBufsInfo);
