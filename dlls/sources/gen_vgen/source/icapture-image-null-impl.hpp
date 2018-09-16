#pragma once
/**
\file       icapture-image-null-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       17.08.2018
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      empty brief
*/

namespace dlls { namespace sources { namespace gen_vgen {
//  syn
using ::libs::ievents::props::videos::generics::driver::VideoDriverCaptureProp;
using ::utils::dbuffs::IBuff;
using ::utils::dbuffs::video::IVideoBuff;
/**
\brief  ��������� ���������� (������ ����� ����������) ������������� �����������.
*/
class ICaptureImageNullImpl : public ICaptureImage
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ICaptureImageNullImpl);

  ICaptureImageNullImpl ()
  {}

  virtual ~ICaptureImageNullImpl ()
  {}


  private:
  virtual void
  change_state_int (bool _enable) override
  {
    _enable;
    return;
  }

  virtual void
  update_property_int (const VideoDriverCaptureProp::raw_ptr _info) override
  {
    _info;
    return;
  }
};

}}}      // namespace dlls::sources::gen_vgen
