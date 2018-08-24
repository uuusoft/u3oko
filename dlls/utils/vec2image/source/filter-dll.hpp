#pragma once
/**
\file       filter-dll.hpp
\brief      Filter for corrected image
\date       01.08.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_dlls_vec2image
*/

namespace dlls { namespace utils { namespace vec2image1 {
/**
  \brief  Empty description
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

  void make_vec2buff (const BuffEventInfo& _b2b, const IVideoBuff& _src, IVideoBuff& _dst);

  ::libs::optim::io::hioptim vec2image1_;      //< ???
};

}}}      // namespace dlls::utils::vec2image1
