#pragma once
/**
\brief      Filter for corrected image
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_all2rgb
\brief      empty brief
*/

namespace dlls { namespace convertors { namespace all2rgb {
/**
  \brief  empty brief
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

  void alloc_buffs ();

  void alloc_temp_buffs ();

  void convert_buffs ();

  ::libs::optim::io::hioptim* get_funct_for_format (const cuuid& _format);

  cuuid get_out_format_from_format (const cuuid& _format);

  ::libs::optim::io::hioptim yuy2_to_rgb24_;      //< ???
  ::libs::optim::io::hioptim yuy2_to_y16_;        //< ???
  ::libs::optim::io::hioptim nv21_to_rgb24_;      //< ???
  ::libs::optim::io::hioptim nv21_to_y16_;        //< ???
  ::libs::optim::io::hioptim ycb_to_rgb24_;       //< ???
  ::libs::optim::io::hioptim scale_funct_;        //< ???
};

}}}      // namespace dlls::convertors::all2rgb
