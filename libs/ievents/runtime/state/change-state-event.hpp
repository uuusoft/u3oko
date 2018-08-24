//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       change-state-event.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace runtime { namespace state {
/**
  \brief  Событие-увеводмление об изменении состояния подсистемы с точки зрения активности.
  */
class ChangStateProcessTypeEvent : public RuntimeEvent
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ChangStateProcessTypeEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ChangStateProcessTypeEvent);
  UUU_DISABLE_ACOPY_TYPE (ChangStateProcessTypeEvent);

  explicit ChangStateProcessTypeEvent (const Acessor& = Acessor (0), bool _start = true);

  virtual ~ChangStateProcessTypeEvent ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/runtime/state/chang-state-process-type-event";
    return _ret;
  }

  bool is_start () const;

  void set_start (bool _val);


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (RuntimeEvent);

  bool start_;      //< Флаг старта подсистемы.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  //virtual void load_int( const base_functs::xml::itn& _node ) override;
  virtual void copy_int (const IEvent::craw_ptr _src) override;
};

}}}}      // namespace libs::ievents::runtime::state

BOOST_CLASS_EXPORT_KEY (::libs::ievents::runtime::state::ChangStateProcessTypeEvent);
