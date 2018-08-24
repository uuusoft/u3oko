#pragma once
/**
\file       base-id-interf.hpp
\author     Erashov A. /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       19.07.2018
\copyright  www.uuusoft.com
\project    uuu_base_id_dll
*/

namespace dlls { namespace base_id {
/**
\brief  Реализация интерфейса фильтра "базовый идентификатор" для взаимодействия с другими фильтрами в графе.
*/
class BaseIdInterf : public ::libs::ievents::runtime::interf::IBaseId
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (BaseIdInterf);

  BaseIdInterf () :
    update_ (false)
  {}

  virtual ~BaseIdInterf ()
  {}

  bool
  is_correction_property_update () const
  {
    return update_;
  }

  BaseIdProp::craw_ptr
  get_base_property () const
  {
    update_ = false;
    return &props_;
  }


  private:
  virtual void
  change_state_int (bool _enable) override
  {
    return;
  }

  virtual void
  update_property_int (const IEvent::craw_ptr _info) override
  {
    props_.copy (_info);
    update_ = true;
    return;
  }

  virtual buff2module_infos_type
  get_module_infos_int (const off_buff_type& _indx_buff) const override
  {
    buff2module_infos_type _ret;

    for (const auto& _info : props_.buff2modules_)
      {
        if (_indx_buff == _info.indx_buff_)
          {
            _ret.push_back (&_info);
          }
      }
    return _ret;
  }

  virtual const source_name_type&
  get_source_name_int () const override
  {
    return props_.source_name_;
  }

  mutable bool update_;      //< ???
  BaseIdProp   props_;       //< �������� ��������� �����������, ��������������� ������� �������
};

}}      // namespace dlls::base_id
