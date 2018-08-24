//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ievents-proxy.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events { namespace io {
/**
  \brief  Тип для доступа к реализации интерфейса для хранения событий системы.
          Реализован через шаблон проектирования "одиночка в строго смысле слова в пределах процесса".
  */
class IEventsProxy
{
  public:
  //  ext types
  using create_funct_type       = IEvents::raw_ptr ();
  using boost_create_funct_type = boost::function<create_funct_type>;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IEventsProxy);

  IEventsProxy (const IEventsProxy& _src) = delete;
  IEventsProxy& operator= (const IEventsProxy& _src) = delete;

  static IEventsProxy::raw_ptr
  instance (const std::string& _dll_path)
  {
    static IEventsProxy g_inst (_dll_path);
    return &g_inst;
  }


  IEvents::raw_ptr
  impl ()
  {
    UASSERT (creator_);
    IEvents::raw_ptr _ret = creator_ ();
    UASSERT (_ret);
    return _ret;
  }


  private:
  explicit IEventsProxy (const std::string& _dll_path)
  {
    boost::filesystem::path _cpath (_dll_path);
    _cpath /= ::utils::mem_functs::files::decorate_dll_name ("vdd_devents");
    creator_ = boost::dll::import_alias<create_funct_type> (_cpath, "instance_devents");
    UASSERT (creator_);
    return;
  }

  ~IEventsProxy ()
  {}

  boost_create_funct_type creator_;      //< ???
};

}}}      // namespace libs::events::io
