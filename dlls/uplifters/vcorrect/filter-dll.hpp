#pragma once
/**
\brief      Filter for corrected image
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcorrect_vdd
\brief    
*/

namespace dlls { namespace uplifters { namespace vcorrect {
/**
\brief  Модуль для коррекции базовых свойств изображения (насыщенность/тон/яркость.etc).
*/
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  virtual ~Filter ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void itransform ();

  ICorrectImage::ptr soft_impl_;      //< Програмная реализация, которая присутствует всегда.
};

}}}      // namespace dlls::uplifters::vcorrect
