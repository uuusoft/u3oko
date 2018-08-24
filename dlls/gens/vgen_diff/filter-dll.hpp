#pragma once
/**
\file       filter-dll.hpp
\date       01.01.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vgen_diff
\brief      empty brief
*/

namespace dlls { namespace gens { namespace vgen_diff {
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
  using off2buffs_type = std::map<off_buff_type, IVideoBuff::ptr>;
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  lib::DiffImpl impl_;      //< Реализация вычисления разности.
};

}}}      // namespace dlls::gens::vgen_diff
