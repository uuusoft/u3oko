//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       base-error-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace runtime { namespace error {
/**
  \brief  Базовое событие-уведомление об ошибке. Может быть получено в ответ на неверное синхронное событие, как сигнал о неверной ситуации и т.п.
  */
class BaseErrorEvent : public RuntimeEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseErrorEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (BaseErrorEvent);
  UUU_DISABLE_ACOPY_TYPE (BaseErrorEvent);

  explicit BaseErrorEvent (const Acessor& = Acessor (0), const std::string& _info = std::string ());

  virtual ~BaseErrorEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/runtime/error/base-error-event";
    return _ret;
  }

  const std::string& what () const;


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  std::string info_;      //< Текстовое описание ошибки.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::error

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::error::BaseErrorEvent);
