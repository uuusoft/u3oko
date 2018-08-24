#pragma once
/**
\file       forever-load-dlls.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace dlls {
/**
  \brief  Тип для гарантированного удеражания в памяти всех загруженных модулей, даже если они уже не нужны.
          Количество расхода памяти при этом незначительно (несколько десятков мегабайт в худшем случае).
          И при этом мы избегаем сбоев при работе с объектами, порожденными различными модулями.
  */
class ForeverLoadDlls
{
  public:
  //  ext types
  using lib_type = boost::dll::shared_library;

  ForeverLoadDlls ()
  {}

  ~ForeverLoadDlls ()
  {}

  ForeverLoadDlls (const ForeverLoadDlls& _src) = delete;
  ForeverLoadDlls& operator= (const ForeverLoadDlls& _src) = delete;

  void
  add (const std::string& _name, lib_type& _lib)
  {
    UASSERT (!_name.empty ());
    UASSERT (_lib.is_loaded ());
    if (!_lib)
      {
        //  явно запрещаем добавление пустой бублиотеки, во избежании выгрузки уже сохраненной по ключу.
        return;
      }
    guard_type _grd (mtx_);
    dlls_.insert (dlls_type::value_type (_name, _lib));
    return;
  }


  private:
  //  int types
  using dlls_type  = std::map<std::string, lib_type>;
  using sync_type  = std::mutex;
  using guard_type = std::lock_guard<sync_type>;

  std::mutex mtx_;       //< Синх. поле для доступу к объекту, т.к. он может (и должен) максимально быть разделимым в процессе.
  dlls_type  dlls_;      //< Все загруженные модули
};

}}}      // namespace libs::helpers::dlls
