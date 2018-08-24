#pragma once
/**
\file       isystem-property.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/

namespace libs { namespace iproperties { namespace vers { namespace system {
//  syn
using ::libs::ievents::props::application::ApplicationProp;
using ::libs::optim::mcalls::CallerImpl;
/**
  \brief  Тип для разделения свойств, общих для всего приложения, между всеми модулями системы.
  */
class ISystemProperty final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISystemProperty);

  ISystemProperty () :
    main_appl_ (nullptr)
  {
    mthreads_  = std::make_shared<::libs::optim::mcalls::CallerImpl> ();
    appl_path_ = boost::filesystem::current_path ().string ();
  }

  virtual ~ISystemProperty ()
  {}

  ApplicationProp::craw_ptr
  get_main_appl_lockfree () const
  {
    return main_appl_;
  }

  void
  set_main_appl_lockfree (ApplicationProp::raw_ptr _ptr)
  {
    main_appl_ = _ptr;
    return;
  }

  iproperties::appl_paths::IAppPaths::cptr
  get_appl_paths_lockfree () const
  {
    return appl_paths_;
  }

  void
  set_appl_paths_lockfree (iproperties::appl_paths::IAppPaths::ptr& _ptr)
  {
    appl_paths_ = _ptr;
    return;
  }

  std::string
  get_appl_path_lockfree () const
  {
    return appl_path_;
  }

  void
  set_appl_path_lockfree (const std::string& _str)
  {
    appl_path_ = _str;
    return;
  }

  std::string
  get_data_path_lockfree () const
  {
    return data_path_;
  }

  void
  set_data_path_lockfree (const std::string& _str)
  {
    data_path_ = _str;
    return;
  }

  CallerImpl::ptr
  get_count_threads_lockfree ()
  {
    return mthreads_;
  }


  private:
  virtual bool
  self_test_int () const override
  {
    UASSERT (!appl_path_.empty ());
    UASSERT (!data_path_.empty ());
    UASSERT (mthreads_);
    UASSERT (main_appl_);
    return appl_path_.empty () || data_path_.empty () || !mthreads_ || !main_appl_ ? false : true;
  }

  virtual void*
  cast2top_int () override
  {
    return this;
  }

  ApplicationProp::raw_ptr   main_appl_;       //< Обшие статические свойства системы, загружаемые из xml файла.
  std::string                appl_path_;       //< Путь к исполняемым файлам приложения.
  std::string                data_path_;       //< Путь к данным приложения.
  CallerImpl::ptr            mthreads_;        //< Пул потоков для обработки данных.
  appl_paths::IAppPaths::ptr appl_paths_;      //< Пути к различным подсистемам и свойствам
};

}}}}      // namespace libs::iproperties::vers::system
