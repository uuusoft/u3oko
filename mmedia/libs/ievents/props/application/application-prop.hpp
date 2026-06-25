#pragma once
/**
\file       application-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
\brief      Объявление типа для хранения (в xml) свойств для приложения в целом
*/

namespace libs::ievents::props::application
{
/// Тип для хранения свойств, общих для приложения в целом
class ApplicationProp : virtual public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ApplicationProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ApplicationProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (ApplicationProp)
  using xml_path_folders_type = std::vector< std::string >;

  explicit ApplicationProp (const Acessor& = Acessor (0));
  virtual ~ApplicationProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/ievents/props/application/application-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  bool               is_single_process () const;
  const std::string& get_messenger_impl () const;

  protected:
  //  ievents::Event overrides
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  std::string                   machine_name_;              //< Имя машины для человека
  ::libs::helpers::utils::cuuid machine_guid_id_;           //< Идентификатор машины (постоянный на все время инсталяции системы на данную машину, генерируется автоматически при инсталяции)
  bool                          single_process_ = true;     //< Флаг, режим работы в одной процессе, иначе в нескольких
  std::string                   messenger_impl_ = "fast";   //< Текстовый идентфикатор реализации передачи сообщений (и данных) между подсистемами. Пустое значение - значение по умолчанию
};
}   // namespace libs::ievents::props::application

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::application::ApplicationProp);
