#pragma once
/**
\file       filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_vgen {
/**
  \brief  Базовый фильтр захвата кадров из внешнего источника (web, ip, desktop, etc).
  */
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  virtual ~Filter ();

  void thread_funct_impl (std::size_t _indx_thread);

  void thread_postfunct_impl ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void                    load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void                    transform_int (TransformInfo& _info) override;
  virtual void                    call_int (CallInterfInfo& _info) override;
  virtual IInterfPathObj::raw_ptr query_int (const ::libs::helpers::utils::cuuid& inter) override;

  void init_pts (ConnectInfo* info);
  //  internal realization intreface IDataSource
  void fill_buffer (InfoFilter* _finfo, BuffsEvent::raw_ptr _buff);
  //  internal realization intreface ICtrlDriverDShow
  void update_driver (InfoFilter* _finfo);
  void update_driver_exact (InfoFilter* _finfo, const std::string& _name_impl);

  ::libs::optim::io::hioptim scale_;                 //< ???
  ::libs::optim::io::hioptim flip_y_;                //< ???
  IEmptyInterfObjPath        support_interf_;        //< Поле используется как флаг поддержки ряда интерфейсов.
  transform_events_type      events_from_impl_;      //< События, сгенерированные конкретной реализацией. Передаются данным объектом в граф обработки данных.
  static ForeverLoadDlls     freez_impls_;           //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы.
};

}}}      // namespace dlls::sources::gen_vgen
