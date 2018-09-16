#pragma once
/**
\file       links-application.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_properties
\brief      empty brief
*/

namespace libs { namespace properties { namespace vers { namespace links {
/**
\brief  Структура для группировки связей модуля.
\tparam link_ptr_type тип хранимого указателя. У владельцев он shared, у агрегатов weak.
*/
template <
  typename tlink_ptr_type>
struct LinksApplication
{
  public:
  //  ext types
  using link_ptr_type = tlink_ptr_type;

  LinksApplication ()
  {}

  ~LinksApplication ()
  {
    reset ();
  }

  void
  reset ()
  {
    appl2gui_.reset ();
    gui2appl_.reset ();
    appl2http_.reset ();
    http2appl_.reset ();
    appl2log_.reset ();
    log2appl_.reset ();
    appl2events_.reset ();
    events2appl_.reset ();
    appl2data_.reset ();
    data2appl_.reset ();
    appl2storage_.reset ();
    storage2appl_.reset ();
    appl2rtp_.reset ();
    rtp2appl_.reset ();
    return;
  }

  bool
  self_test () const
  {
    return true;
  }
  /**
  \brief  Функция присваивания двух объектов с разными (но конвертируемыми) указателями.
  \tparam APtr  указатель типа А
  \tparam BPtr  указатель типа B
  \return       левый объект.
  */
  template <
    typename BPtr>
  LinksApplication&
  operator= (LinksApplication<BPtr>& _right)
  {
    appl2gui_     = _right.appl2gui_;
    gui2appl_     = _right.gui2appl_;
    appl2http_    = _right.appl2http_;
    http2appl_    = _right.http2appl_;
    appl2data_    = _right.appl2data_;
    data2appl_    = _right.data2appl_;
    appl2log_     = _right.appl2log_;
    log2appl_     = _right.log2appl_;
    appl2events_  = _right.appl2events_;
    events2appl_  = _right.events2appl_;
    appl2storage_ = _right.appl2storage_;
    storage2appl_ = _right.storage2appl_;
    appl2rtp_     = _right.appl2rtp_;
    rtp2appl_     = _right.rtp2appl_;
    return *this;
  }

  link_ptr_type appl2gui_;          //< Связь между приложением и графическим интерфейсом.
  link_ptr_type gui2appl_;          //< Связь между приложением и графическим интерфейсом.
  link_ptr_type appl2http_;         //< Связь между приложением и http сервером.
  link_ptr_type http2appl_;         //< Связь между приложением и http сервером.
  link_ptr_type appl2data_;         //< Связь между текущем и модулем обработки данных.
  link_ptr_type data2appl_;         //< Связь между текущем и модулем обработки данных.
  link_ptr_type appl2log_;          //< Связь между текущем и модулем логирования.
  link_ptr_type log2appl_;          //< Связь между текущем и модулем логирования.
  link_ptr_type appl2events_;       //< Связь между текущем и модулем событий.
  link_ptr_type events2appl_;       //< Связь между текущем и модулем событий.
  link_ptr_type appl2storage_;      //< Связь между приложением и модулем хранилища данных.
  link_ptr_type storage2appl_;      //< Связь между модулем хранилища данных и приложением.
  link_ptr_type appl2rtp_;          //< Связь между приложением и модулем rtp.
  link_ptr_type rtp2appl_;          //< Связь между модулем rtp и приложением.
};

}}}}      // namespace libs::properties::vers::links
