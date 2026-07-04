#pragma once
/**
\file       ibase-id.hpp
\author     Erashov Anton erashov2026@proton.me
\date       19.07.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::interf::interfaces
{
class IBaseId : public IBaseRuntimeInterf
{
  public:
  //  ext types
  using buf2module_infos_type = std::list< ::libs::events_base::props::base_id::Buff2ModuleInfo::craw_ptr >;

  U3_ADD_POINTERS_TO_SELF (IBaseId)

  virtual ~IBaseId () = default;

  void
  change_state (bool enable)
  {
    change_state_int (enable);
  }

  void
  update_property (const ::libs::events::IEvent::craw_ptr info)
  {
    update_property_int (info);
  }

  /// Функция возвращает информацию маршрутизации данных от данного источника
  /// \return информация маршрутизации
  buf2module_infos_type
  get_module_infos (const syn::off_buf_type& indx_buf) const
  {
    return get_module_infos_int (indx_buf);
  }

  /// Функция возвращает имя (идентификатор) источника данных (камера, микрофон etc)
  /// \return идентификатор источника
  const syn::source_name_type&
  get_source_name () const
  {
    return get_source_name_int ();
  }

  protected:
  IBaseId () = default;

  private:
  //  IBaseId interface
  virtual void                         change_state_int (bool enable)                                    = 0;
  virtual void                         update_property_int (const ::libs::events::IEvent::craw_ptr info) = 0;
  virtual buf2module_infos_type        get_module_infos_int (const syn::off_buf_type& indx_buf) const    = 0;
  virtual const syn::source_name_type& get_source_name_int () const                                      = 0;
};
}   // namespace libs::events_base::runtime::interf::interfaces
