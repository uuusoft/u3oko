//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       list-xml-files-data-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_imdata_events
\brief      empty brief
*/

namespace libs { namespace imdata_events { namespace events {
/**
\brief  Событие содержит в себе список доступных xml файлов конфигурации графов обработки данных.
        Данный список может служить как список идентификаторов графов данных для событий ChangePathsDataEvent.
*/
class ListXmlFilesDataEvent : public BaseDataEvent
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
  using xml_file_type  = std::string;
  using xml_files_type = std::list<xml_file_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ListXmlFilesDataEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ListXmlFilesDataEvent);
  UUU_DISABLE_ACOPY_TYPE (ListXmlFilesDataEvent);

  explicit ListXmlFilesDataEvent (const Acessor& = Acessor (0), const xml_files_type& _devices = xml_files_type ());

  virtual ~ListXmlFilesDataEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/imdata_events/events/list-xml-files-data-event";
    return _ret;
  }

  const ListXmlFilesDataEvent::xml_files_type& get_xml_files () const;

  void set_xml_files (xml_files_type&& _src);


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (BaseDataEvent);

  xml_files_type xml_files_;      //< Список путей обработки данных.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual void                        load_int (const base_functs::xml::itn& _prop) override;
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}      // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_KEY (::libs::imdata_events::events::ListXmlFilesDataEvent);
