#pragma once
/**
\file       end-point-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace terminals {
//  syn
using ::libs::events::buff::EventBuffsInfo;
/**
\brief  Свойство конечной точки графа обработки данных.
        Определяет дальнейший путь данных (http server, gui etc).
*/
class EndPointProp : public Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (EndPointProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (EndPointProp);
  UUU_DISABLE_ACOPY_TYPE (EndPointProp);

  explicit EndPointProp (const Acessor& = Acessor (0));

  virtual ~EndPointProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/terminals/end-point-prop";
    return _ret;
  }

  bool is_send () const;

  bool is_notify () const;


  protected:
  //  Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  bool enable_send_;        //< Флаг, глобальный для данной камеры, управляет включением передачи данных в другие модули.
  bool enable_notify_;      //< Флаг включения посылки сообщения о передаче данных.
};

}}}}      // namespace libs::ievents::props::terminals

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::terminals::EndPointProp);
