#pragma once
/**
\file       vgen-conv3_11-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_conv
*/

namespace dlls::gens::vgen_conv3_11
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  syn::VideoConvolutionProp::raw_ptr rprops_;   //< Настроенный указатель на свойства (для удобства)

  protected:
  virtual bool load_int (const ::pugi::xml_named_node_iterator& node) override;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::BaseInfoFilter)
};
}   // namespace dlls::gens::vgen_conv3_11
