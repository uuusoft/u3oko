#pragma once
/**
\file       obj-path-local.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.12.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление реализации объекта локальной версии графа.
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {
//  forward
class Path;
}}}}}      // namespace libs::icore::impl::var1::path

namespace libs { namespace icore { namespace impl { namespace var1 { namespace obj {
/**
  \brief  Реализация объекта в локальной версии графа обработки данных.
  */
class ObjPath : public IPathObjExt
{
  friend class ::libs::icore::impl::var1::path::Path;

  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ObjPath);

  ObjPath (const core::path::IPath* _pparent, ::libs::link::ILink::weak_ptr _logger);

  virtual ~ObjPath ();

  ObjPath (const ObjPath& _src) = delete;
  ObjPath& operator= (const ObjPath& _src) = delete;


  private:
  //  int types
  using forever_dlls_types = ::libs::helpers::dlls::ForeverLoadDlls;
  using create_funct_type  = ::boost::function<obj::dll::create_impl_funct_type>;

  //  IPathObj impl
  virtual core::path::IInterfPathObj::raw_ptr query_int (const ::libs::helpers::utils::cuuid& _id_intef) override;

  //  IPathObjExt impl
  virtual void load_int (const base_functs::xml::itn& _root) override;
  virtual void connect_int (int _idpt1, IPathObjExt::ptr& _filter, int _idpt2) override;
  virtual void send_event2me_int (::libs::events::IEvent::ptr& _evnt) override;
  virtual void stop_int () override;
  virtual void run_int () override;
  /**
    \brief      Функция загружает и иниицализирует объект из загружаемого кода (dll/so).
    \param[in]  _name_lib имя файла кода.
    \param[in]  _node   узел xml для инициализации свойств объекта.
    */
  void load_lib (const std::string& _name_lib, const base_functs::xml::itn& _node);
  /**
    \brief    Функция освобождает объект из загружаемого кода (dll/so).
    */
  void free_lib ();
  /**
    \brief      Функция устанавливает соединение между двумя объектами.
    \param[in]  _indx_src   ???
    \param[in]  _filter     ???
    \param[in]  _indx_dst   ???
    */
  void set_src_connect (int _indx_src, ObjPath* _filter, int _indx_dst);
  /**
    \brief      Функция устанавливает соединение между двумя объектами.
    \param[in]  _indx_src   ???
    \param[in]  _filter     ???
    \param[in]  _indx_dst   ???
    */
  void set_dst_connect (int _indx_src, ObjPath* _filter, int _indx_dst);
  /**
    \brief    Функция возвращает общую информацию о объекте графа обработки данных.
    \return   ???
    */
  const obj::FilterInfo& get_info () const;
  /**
    \brief          Основная рабочая функция по обработке данных объектом графа.
    \param[in, out] _info параметры вызова.
    */
  void transform (obj::dll::TransformInfo& _info);

  const core::path::IPath*      pparent_;         //< Указатель на граф, которому принадлежит данный объект.
  static forever_dlls_types     freez_libs_;      //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы.
  boost::dll::shared_library    lib_;             //< Собственно загруженная библиотека с реализацией.
  obj::FilterInfo               info_;            //< ???
  obj::InterfsForFilter         iinfo_;           //< ???
  obj::dll::IFilter::ptr        dfilter_;         //< Настоящая реализация полученная из dll/so.
  obj::RunStateFilter           state_;           //< Текущее состояние объекта с точки зрения запуска.
  std::string                   name_lib_;        //< Имя библиотеки, которая была использована для создания.
  create_funct_type             pf_create_;       //< Функция в библиотеки, для создания настоящей реализации.
  ::libs::link::ILink::weak_ptr logger_;          //< Логгер пути, устанавливается извне.
};

}}}}}      // namespace libs::icore::impl::var1::obj
