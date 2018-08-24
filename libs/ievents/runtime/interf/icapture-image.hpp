//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       icapture-image.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       17.08.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
*/

namespace libs { namespace ievents { namespace runtime { namespace interf {
//  syn
using ::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp;
using ::utils::dbuffs::IBuff;
using ::utils::dbuffs::video::IVideoBuff;
/**
  \brief  ��������� ���������� (������ ����� ����������) ������������� �����������.
  */
class ICaptureImage
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ICaptureImage);

  virtual ~ICaptureImage ()
  {}

  void
  change_state (bool _enable)
  {
    return change_state_int (_enable);
  }

  void
  update_property (const VideoDriverCaptureProp::raw_ptr _info)
  {
    return update_property_int (_info);
  }


  protected:
  ICaptureImage ()
  {}


  private:
  //  ICaptureImage interface
  virtual void change_state_int (bool _enable)                                   = 0;
  virtual void update_property_int (const VideoDriverCaptureProp::raw_ptr _info) = 0;
};

}}}}      // namespace libs::ievents::runtime::interf
