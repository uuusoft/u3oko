#pragma once
/**
\file       filter-dll.hpp
\brief      Filter for corrected image
\date       01.08.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vgd_motion
\brief    
*/

namespace dlls { namespace gens { namespace vgen_motion {
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
  //  int types
  using off_buff2buff_type = std::map<off_buff_type, IVideoBuff::ptr>;
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void itransform ();

  void make_motion_est_buff (const EventBuffsInfo& _b2b, const IVideoBuff& _cur_src, const IVideoBuff& _prev_src, IVideoBuff& _dst_vecs);

  off_buff2buff_type         indx2prev_buff_;      //< ???
  ::libs::optim::io::hioptim cmp_get_const_;       //< ???
  ::libs::optim::io::hioptim motion_est1_;         //< ???
};

}}}      // namespace dlls::gens::vgen_motion
