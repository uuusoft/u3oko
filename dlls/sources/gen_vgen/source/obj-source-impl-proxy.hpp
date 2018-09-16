#pragma once
/**
\file       obj-source-impl-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       20.05.2017
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_vgen {
/**
\brief  Обеспечивает загрузку выбранной реализации захвата данных в память процесса.
*/
class ObjSourceImplProxy
{
  public:
  ObjSourceImplProxy ();

  ~ObjSourceImplProxy ();

  ObjSourceImplProxy (const ObjSourceImplProxy& _src) = delete;
  ObjSourceImplProxy& operator= (const ObjSourceImplProxy& _src) = delete;

  void init (const std::string& _name_impl);

  void clear ();

  gen_lib::ISourceImpl::raw_ptr get ();

  boost::dll::shared_library get_lib ();


  private:
  //  int types
  using bfree_source_funct_type   = boost::function<gen_lib::free_source_funct_type>;
  using bcreate_source_funct_type = boost::function<gen_lib::get_source_funct_type>;

  boost::dll::shared_library    lib_;             //< Библиотека с выбранной реализацией захвата данных из видеоустройства.
  gen_lib::ISourceImpl::raw_ptr impl_;            //< Реализация захвата, полученная из библиотеки.
  bcreate_source_funct_type     funct_get_;       //< Функция создания реализации из библиотеки.
  bfree_source_funct_type       funct_free_;      //< Функция удаления реализации из библиотеки.
};

}}}      // namespace dlls::sources::gen_vgen
