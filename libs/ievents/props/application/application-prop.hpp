#pragma once
/**
\file       application-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Объявление типа для хранения (в xml) свойств для приложения в целом.
*/

namespace libs { namespace ievents { namespace props { namespace application {
/**
  \brief  Тип для хранения свойств, общих для приложения в целом.
  */
class ApplicationProp : public ievents::Event
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
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ApplicationProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ApplicationProp);
  UUU_DISABLE_ACOPY_TYPE (ApplicationProp);

  explicit ApplicationProp (const Acessor& = Acessor (0));

  virtual ~ApplicationProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/application/application-prop";
    return _ret;
  }

  bool is_single_process () const;

  const std::string& get_messenger_impl () const;


  protected:
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  bool        single_process_;      //< Флаг, режим работы в одной процессе, иначе в нескольких.
  std::string messenger_impl_;      //< Текстовый идентфикатор реализации передачи сообщений (и данных) между подсистемами. Пустое значение - значение по умолчанию.
  std::string min_log_filter_;      //< Фильтрация логирования, совпадает с boost::logging::trivial.
};

}}}}      // namespace libs::ievents::props::application

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::application::ApplicationProp);
