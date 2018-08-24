//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       zip-data-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace runtime { namespace mem {
/**
  \brief  Событие-уведомление с буферами под/c данными.
  */
class ZipDataEvent : public RuntimeEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  using element_zip_buff_type = unsigned char;
  using zip_buff_type         = std::vector<element_zip_buff_type>;
  using id_buff_type          = std::string;
  using number_buff_type      = long long;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ZipDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ZipDataEvent);
  UUU_DISABLE_ACOPY_TYPE (ZipDataEvent);

  explicit ZipDataEvent (const Acessor& = Acessor (0));

  ZipDataEvent (zip_buff_type&& _buff, std::size_t _size, const number_buff_type& _number_buff = 0, const id_buff_type& _id = "");

  explicit ZipDataEvent (IVideoBuff::raw_ptr, const number_buff_type& _number_buff = 0, const id_buff_type& _id = "");

  virtual ~ZipDataEvent ()
  {}

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/runtime/mem/zip-data-event";
    return _ret;
  }

  const zip_buff_type& get_zip () const;

  zip_buff_type& update_zip ();

  void update_zip (IVideoBuff::raw_ptr&);

  std::size_t get_size () const;

  const id_buff_type& get_id () const;

  void set_id (const id_buff_type& _id);

  const number_buff_type& get_number () const;

  void set_number (const number_buff_type& _number_buff);


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  zip_buff_type    buff_;             //< Буфер с данными, связанный с событием.
  std::size_t      size_;             //< Размер буфера.
  id_buff_type     id_buff_;          //< Опциональный идентификатор буфера.
  number_buff_type number_buff_;      //< Опциональный порядковый номер буфера.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::mem

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::mem::ZipDataEvent);
