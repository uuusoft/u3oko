#pragma once
/**
\file       zip-data-event.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::mem
{
/// Событие-уведомление с буферами под/c данными
class ZipDataEvent : public RuntimeEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

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

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ZipDataEvent)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ZipDataEvent)
  U3_HELPER_DISABLE_ACOPY_TYPE (ZipDataEvent)

  explicit ZipDataEvent (const Acessor& = Acessor (0));
  explicit ZipDataEvent (::utils::dbufs::video::IVideoBuf::raw_ptr, const number_buf_type& number_buf = 0, const id_buf_type& id = "");
  ZipDataEvent (zip_buf_type&& buf, std::size_t size, const number_buf_type& number_buf = 0, const id_buf_type& id = "");
  virtual ~ZipDataEvent () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/runtime/mem/zip-data-event";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  const zip_buf_type&    get_zip () const;
  zip_buf_type&          update_zip ();
  void                   update_zip (::utils::dbufs::video::IVideoBuf::raw_ptr&);
  std::size_t            get_size () const;
  const id_buf_type&     get_id () const;
  void                   set_id (const id_buf_type& id);
  const number_buf_type& get_number () const;
  void                   set_number (const number_buf_type& number_buf);

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::runtime::RuntimeEvent)

  zip_buf_type    zip_buf_;          //< Буфер с данными, связанный с событием
  std::size_t     size_zip_buf_;     //< Размер буфера
  id_buf_type     id_zip_buf_;       //< Опциональный идентификатор буфера
  number_buf_type number_zip_buf_;   //< Опциональный порядковый номер буфера

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  // virtual void load_int( const ::pugi::xml_named_node_iterator& node ) override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::ievents::runtime::mem

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::mem::ZipDataEvent);
