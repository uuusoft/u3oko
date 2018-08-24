#pragma once
/**
\file       base-info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace dll {
/**
  \brief  Интерфейс для загружаемых из xml файла свойств фильтра графа обработки данных.
  */
struct BaseInfoFilter
{
  public:
  BaseInfoFilter ();

  virtual ~BaseInfoFilter ();

  /// Функция загрузки данных из узла xml.
  bool load (const base_functs::xml::itn& _node);
  /// Функция синхронизации данных после загрузки.
  void sync (bool _force);


  protected:
  //  int types
  using str2prop_type = std::map<std::string, ::libs::ievents::Event::raw_ptr>;

  virtual bool load_int (const base_functs::xml::itn& _node);
  virtual void sync_int (bool _force);

  str2prop_type str2props_;      //< Поле для процесса загрузки свойств из xml файла.
};

}}}}}}      // namespace libs::icore::impl::var1::obj::dll
