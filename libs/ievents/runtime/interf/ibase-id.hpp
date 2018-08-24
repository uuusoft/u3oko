//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       ibase-id.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       19.07.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace interf {
//  syn
using ::libs::events::IEvent;
using ::libs::ievents::props::base_id::BaseIdProp;
using ::libs::ievents::props::base_id::Buff2ModuleInfo;
using ::libs::ievents::props::base_id::source_name_type;
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::utils::dbuffs::IBuff;
using ::utils::dbuffs::video::IVideoBuff;
/**
  \brief  ��������� ���������� (������ ����� ����������) ������������� �����������.
  */
class IBaseId
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IBaseId);
  using buff2module_infos_type = std::list<Buff2ModuleInfo::craw_ptr>;

  virtual ~IBaseId ()
  {}
  /**
  \brief  ???
  */
  void
  change_state (bool _enable)
  {
    return change_state_int (_enable);
  }
  /**
  \brief  ???
  */
  void
  update_property (const IEvent::craw_ptr _info)
  {
    return update_property_int (_info);
  }
  /**
  \brief  Функция возвращает информацию маршрутизации данных от данного источника.
  \return информация маршрутизации.
  */
  buff2module_infos_type
  get_module_infos (const off_buff_type& _indx_buff) const
  {
    return get_module_infos_int (_indx_buff);
  }
  /**
  \brief  Функция возвращает имя (идентификатор) источника данных (камера, микрофон и т.п.).
  \return идентификатор источника.
  */
  const source_name_type&
  get_source_name () const
  {
    return get_source_name_int ();
  }


  protected:
  IBaseId ()
  {}


  private:
  //  IBaseId interface
  virtual void                    change_state_int (bool _enable)                              = 0;
  virtual void                    update_property_int (const IEvent::craw_ptr _info)           = 0;
  virtual buff2module_infos_type  get_module_infos_int (const off_buff_type& _indx_buff) const = 0;
  virtual const source_name_type& get_source_name_int () const                                 = 0;
};

}}}}      // namespace libs::ievents::runtime::interf
