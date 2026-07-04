#pragma once
/**
\file       isystem-property.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::vers::system
{
/// Тип для разделения свойств, общих для всего приложения, между всеми модулями системы
class ISystemProperty final : public ::libs::properties::ISharedProperty
{
  public:
  // ext types
  U3_ADD_POINTERS_TO_SELF (ISystemProperty)

  ISystemProperty ();
  virtual ~ISystemProperty () = default;

  auto get_appl_lockfree () -> syn::ApplicationProp::craw_ptr const;
  void set_appl_lockfree (syn::ApplicationProp::raw_ptr);
  auto get_log_lockfree () -> syn::PropertyLogModuleEvent::craw_ptr const;
  void set_log_lockfree (syn::PropertyLogModuleEvent::raw_ptr);
  auto get_paths_lockfree () -> iproperties::appl_paths::IAppPaths::cptr const;
  void set_paths_lockfree (iproperties::appl_paths::IAppPaths::ptr&);
  auto get_appl_path_lockfree () -> std::string const;
  void set_appl_path_lockfree (const std::string&);
  auto get_mdata_lockfree () -> std::string const;
  void set_mdata_lockfree (const std::string&);
  auto get_mcalls_lockfree () -> ::libs::optim::mcalls::IMCaller::ptr;
  void set_mcalls_lockfree (::libs::optim::mcalls::IMCaller::ptr&);

  private:
  virtual bool  self_test_int () const override;
  virtual void* cast2top_int () override;

  std::atomic< syn::ApplicationProp::raw_ptr >        main_appl_properties_ = nullptr;   //< Обшие статические свойства системы, загружаемые из xml файла
  std::atomic< syn::PropertyLogModuleEvent::raw_ptr > module_log_props_     = nullptr;   //< Свойства модуля логирования, загруженные из xml файла
  std::string                                         appl_path_;                        //< Путь к исполняемым файлам приложения
  std::string                                         data_path_;                        //< Путь к данным приложения
  ::libs::optim::mcalls::IMCaller::ptr                mthreads_;                         //< Пул потоков для обработки данных
  appl_paths::IAppPaths::ptr                          appl_paths_;                       //< Пути к различным подсистемам и свойствам
};
}   // namespace libs::iproperties::vers::system
