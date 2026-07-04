#pragma once
/**
\file       vgen-motion-filter-dll.hpp
\brief      Filter for corrected image
\date       01.08.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_vgd_motion
*/

namespace dlls::gens::vgen_motion
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  //  internal typess
  using off_buf2buf_type = boost::unordered_flat_map< ::utils::dbufs::video::consts::offs::off_buf_type, syn::IVideoBuf::ptr >;
  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo*, const ::pugi::xml_named_node_iterator&) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo&) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo&) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo*);
  auto itransform () -> void;
  void make_motion_est_buf (syn::EventBufsMotionEst&, const syn::IVideoBuf&, const syn::IVideoBuf&, syn::IVideoBuf&);

  off_buf2buf_type           indx2prev_buf_;   //<
  ::libs::optim::io::hioptim cmp_get_const_;   //<
  ::libs::optim::io::hioptim motion_est1_;     //<
};
}   // namespace dlls::gens::vgen_motion
