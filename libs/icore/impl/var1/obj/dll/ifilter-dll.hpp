#pragma once
/**
\file       ifilter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       27.07.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      empty brief
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj { namespace dll {
/**
\brief  Интерфейс, который должен поддерживать каждый объект в графе обработки данных.
*/
class IFilter
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IFilter);

  IFilter ()
  {}

  virtual ~IFilter ()
  {}

  IFilter (const IFilter& _src) = delete;
  IFilter& operator= (const IFilter& _src) = delete;
  /**
  \brief          Функция инициализации объекта через xml конфигурацию.
  \param[in, out] _info информация связанная с объектом.
  \param[in]      _node узел, с которого будет загружены свойства фильтра.
  */
  void
  load (FilterInfo* _info, const base_functs::xml::itn& _node)
  {
    return load_int (_info, _node);
  }
  /**
  \brief          Функция преобразования данных данным объектом графа обработки данных.
  \param[in, out] _info параметры и данные для преобразования
  */
  void
  transform (TransformInfo& _info)
  {
    return transform_int (_info);
  }
  /**
  \brief          Функция вызова операции у данного фильтра.
  \param[in, out] _info свойства операции.
  */
  void
  call (CallInterfInfo& _info)
  {
    return call_int (_info);
  }
  /**
  \brief      Функция запроса интерфейса. Например для получения дополнительных свойствам от данного фильтра.
  \param[in]  _interf идентификатор интерфейса.
  \return     интерфейс или nullptr.
  */
  core::path::IInterfPathObj::raw_ptr
  query (const ::libs::helpers::utils::cuuid& _interf)
  {
    return query_int (_interf);
  }
  /// Запуск процесса обработки данных данным фильтром.
  void
  run ()
  {
    return run_int ();
  }
  /// Остановка процесса обработки данных данным фильтром.
  void
  stop ()
  {
    return stop_int ();
  }


  private:
  virtual void
  load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
  {
    UASSERT_SIGNAL ("failed, try call load_int");
    return;
  }

  virtual void
  transform_int (TransformInfo& _info)
  {
    UASSERT_SIGNAL ("failed, try call transform_int");
    return;
  }

  virtual void
  call_int (CallInterfInfo& _info)
  {
    UASSERT_SIGNAL ("failed, try call call_int");
    return;
  }

  virtual core::path::IInterfPathObj::raw_ptr
  query_int (const ::libs::helpers::utils::cuuid& inter)
  {
    //UASSERT_SIGNAL( "skip" ); //  Многие (большинство) фильтры не поддерживают вообще никаких интерфейсов, поэтому тут реализовано поведение по умолчанию.
    return nullptr;
  }

  virtual void
  run_int ()
  {
    //UASSERT_SIGNAL( "skip" );
    return;
  }

  virtual void
  stop_int ()
  {
    //UASSERT_SIGNAL( "skip" );
    return;
  }
};

}}}}}}      // namespace libs::icore::impl::var1::obj::dll
