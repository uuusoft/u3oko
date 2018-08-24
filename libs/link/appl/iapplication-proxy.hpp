#pragma once
/**
\file       iapplication-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.05.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace appl {
/**
  \brief  Прокси для создания объекта "подсистема" из разделяемого кода (dll/so)
  */
class IApplicationProxy
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IApplicationProxy);
  using create_obj_type = IApplication::raw_ptr ();
  using delete_obj_type = void(IApplication::raw_ptr);

  IApplicationProxy (const char* _dll_path, const char* _name_lib);

  ~IApplicationProxy ();

  IApplicationProxy (const IApplicationProxy& _src) = delete;
  IApplicationProxy& operator= (const IApplicationProxy& _src) = delete;

  IApplication::raw_ptr impl ();


  private:
  //  int types
  using forever_dlls_type = ::libs::helpers::dlls::ForeverLoadDlls;
  using create_funct_type = boost::function<create_obj_type>;
  using delete_funct_type = boost::function<delete_obj_type>;

  boost::dll::shared_library lib_;             //< Держим в памяти dll принудительно вечно, до завершения работы всего процесса.
  static forever_dlls_type   freez_libs_;      //< собственно список для хранения модулей и гарантии, что они будут выгруженны последними.
  create_funct_type          creator_;         //< Указатель на функтор в dll, который собственно и создает приложение.
  delete_funct_type          deletor_;         //< Указатель на функтор в dll, который уменьшает ссылку на созданное приложение и при необходимости удаляет его.
  IApplication::raw_ptr      impl_;            //< Созданное приложение.
};

}}}      // namespace libs::link::appl
