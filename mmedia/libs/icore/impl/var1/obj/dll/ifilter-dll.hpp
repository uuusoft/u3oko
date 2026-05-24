#pragma once
/**
\file       ifilter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       27.07.2016
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::obj::dll
{
/// Интерфейс, который должен поддерживать каждый объект в графе обработки данных
class IFilter
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IFilter)

  IFilter () :
    transinfo_ (nullptr)
  {
  }

  virtual ~IFilter ()
  {
  }

  IFilter (const IFilter& src)            = delete;
  IFilter& operator= (const IFilter& src) = delete;

  /// Функция инициализации объекта через xml конфигурацию
  /// \param[in, out] info информация связанная с объектом
  /// \param[in]      node узел, с которого будет загружены свойства фильтра
  void
  load (FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
  {
    id_obj_ = info->id_obj_;
    load_int (info, node);
  }

  /// Функция преобразования данных данным объектом графа обработки данных
  /// \param[in, out] info параметры и данные для преобразования
  void
  transform (TransformInfo& info)
  {
    transinfo_ = &info;
    transform_int (info);
    transinfo_ = nullptr;
  }

  /// Функция вызова операции у данного фильтра
  /// \param[in, out] info свойства операции
  void
  call (CallInterfInfo& info)
  {
    call_int (info);
  }

  /// Функция запроса интерфейса
  /// Например для получения дополнительных свойствам от данного фильтра
  /// \param[in]  interf идентификатор интерфейса
  /// \return     интерфейс или nullptr
  core::graph::IInterfGraphObj::raw_ptr
  query (const ::libs::helpers::utils::cuuid& interf)
  {
    return query_int (interf);
  }

  /// Запуск процесса обработки данных данным фильтром
  void
  run ()
  {
    run_int ();
  }

  /// Остановка процесса обработки данных данным фильтром
  void
  stop ()
  {
    stop_int ();
  }

  protected:
  TransformInfo*              transinfo_;   //< Указатель на текущий параметр при вызове функции transform
  ::libs::core::graph::NodeID id_obj_;      //< Идентификатор узла в графе данного объекта

  private:
  virtual void
  load_int (FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
  {
    U3_ASSERT_SIGNAL ("try call load_int");
  }

  virtual void
  transform_int (TransformInfo& info)
  {
    U3_ASSERT_SIGNAL ("try call transform_int");
  }

  virtual void
  call_int (CallInterfInfo& info)
  {
    U3_ASSERT_SIGNAL ("try call call_int");
  }

  virtual core::graph::IInterfGraphObj::raw_ptr
  query_int (const ::libs::helpers::utils::cuuid& inter)
  {
    //  Многие (большинство) фильтры не поддерживают вообще никаких интерфейсов, поэтому тут реализовано поведение по умолчанию
    // U3_ASSERT_SIGNAL( "skip" );
    return nullptr;
  }

  virtual void
  run_int ()
  {
  }

  virtual void
  stop_int ()
  {
  }
};
}   // namespace libs::icore::impl::var1::obj::dll
