//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       icorrect-image.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace interf {
//  syn
using ::libs::ievents::props::videos::generics::correct::VideoCorrectProp;
using ::utils::dbuffs::IBuff;
using ::utils::dbuffs::video::IVideoBuff;
/**
  \brief  ��������� ���������� (������ ����� ����������) ������������� �����������.
  */
class ICorrectImage
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ICorrectImage);

  virtual ~ICorrectImage ()
  {}

  void
  change_state (bool _enable)
  {
    return change_state_int (_enable);
  }

  void
  update_property (const VideoCorrectProp::raw_ptr _info)
  {
    return update_property_int (_info);
  }

  bool
  process (IVideoBuff::raw_ptr _h16_buff, IVideoBuff::raw_ptr _s16_buff, IVideoBuff::raw_ptr _l16_buff)
  {
    return process_int (_h16_buff, _s16_buff, _l16_buff);
  }


  protected:
  ICorrectImage ()
  {}


  private:
  virtual void change_state_int (bool _enable)                                                                           = 0;
  virtual void update_property_int (const VideoCorrectProp::raw_ptr _info)                                               = 0;
  virtual bool process_int (IVideoBuff::raw_ptr _h16_buff, IVideoBuff::raw_ptr _s16_buff, IVideoBuff::raw_ptr _l16_buff) = 0;
};

}}}}      // namespace libs::ievents::runtime::interf
