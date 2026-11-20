#pragma once
/**
\file       event-bufs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::events::buf::syn
{
using off_buf_type            = ::utils::dbufs::video::consts::offs::off_buf_type;
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
}   // namespace libs::events::buf::syn


namespace libs::events::buf
{
/// Функция проверка валидности узла для загрузки буфера
bool is_valid_node (const ::pugi::xml_named_node_iterator& node);

/// Сохранение параметров стандартного буфера для всех свойств
struct EventBufs {
  public:
  explicit EventBufs (
    syn::off_buf_type = utils::dbufs::video::consts::offs::invalid,
    syn::off_buf_type = utils::dbufs::video::consts::offs::invalid);

  explicit EventBufs (syn::persistent_off_buf_type, syn::persistent_off_buf_type);

  virtual ~EventBufs () = default;

  void check (bool = true, bool = true);

  syn::persistent_off_buf_type indx_sbuf_;   //< Индекс буфера-источника
  syn::persistent_off_buf_type indx_dbuf_;   //< Индекс буфера-назначения

  protected:
  virtual auto check_int () -> void;
  virtual auto correct_int () -> void;

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const EventBufs&) -> void;
auto tag_invoke (::boost::json::value_to_tag< EventBufs >, const ::boost::json::value&) -> EventBufs;
}   // namespace libs::events::buf

U3_BOOST_CLASS_EXPORT_KEY (::libs::events::buf::EventBufs);
