#pragma once
/**
\file       zip-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class ZipDataEvent : public RuntimeEvent
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  using element_zip_buf_type = std::uint8_t;
  using zip_buf_type         = std::vector< element_zip_buf_type >;
  using id_buf_type          = std::string;
  using number_buf_type      = long long;

  U3_ADD_POINTERS_TO_SELF (ZipDataEvent)
  U3_ADD_MAKE_SHARED_THIS (ZipDataEvent)
  U3_ADD_DELETE_MOVE_COPY (ZipDataEvent)

  explicit ZipDataEvent (const Acessor& = Acessor (0));
  explicit ZipDataEvent (::utils::dbufs::video::IVideoBuf::raw_ptr, const number_buf_type& number_buf = 0, id_buf_type id = "");
  ZipDataEvent (zip_buf_type&& buf, std::size_t size, const number_buf_type& number_buf = 0, const id_buf_type& id = "");
  virtual ~ZipDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/runtime/mem/zip-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  auto get_zip () const -> const zip_buf_type&;
  auto update_zip () -> zip_buf_type&;
  auto update_zip (::utils::dbufs::video::IVideoBuf::raw_ptr&) -> void;
  auto get_size () const -> std::size_t;
  auto get_id () const -> const id_buf_type&;
  auto set_id (const id_buf_type&) -> void;
  auto get_number () const -> const number_buf_type&;
  auto set_number (const number_buf_type&) -> void;

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::runtime::RuntimeEvent)

  zip_buf_type    zip_buf_;             //< Буфер с данными, связанный с событием
  std::size_t     size_zip_buf_ = 0;    //< Размер буфера
  id_buf_type     id_zip_buf_;          //< Опциональный идентификатор буфера
  number_buf_type number_zip_buf_ {};   //< Опциональный порядковый номер буфера

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::runtime::mem

BOOST_CLASS_EXPORT_KEY (::libs::events_base::runtime::mem::ZipDataEvent);
