#pragma once
/**
\file       icorrect-image.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::interf::interfaces
{
class ICorrectImage : public IBaseRuntimeInterf
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ICorrectImage)

  virtual ~ICorrectImage ()
  {
  }

  void
  change_state (bool enable)
  {
    change_state_int (enable);
  }

  void
  update_correction_property (const syn::VideoCorrectProp::raw_ptr info)
  {
    update_correction_property_int (info);
  }

  bool
  process (
    syn::TransformInfo*     info,
    const syn::NodeID&      id_node,
    syn::IVideoBuf::raw_ptr h16_buf,
    syn::IVideoBuf::raw_ptr s16_buf,
    syn::IVideoBuf::raw_ptr l16_buf)
  {
    transinfo_     = info;
    id_node_graph_ = &id_node;
    const auto res = process_int (h16_buf, s16_buf, l16_buf);
    transinfo_     = nullptr;
    id_node_graph_ = nullptr;
    return res;
  }

  protected:
  ICorrectImage () :
    transinfo_ (nullptr)
  {
  }

  syn::TransformInfo* transinfo_;       //< Указатель на текущий параметр при вызове функции transform
  const syn::NodeID*  id_node_graph_;   //<

  private:
  //  ICorrectImage interface
  virtual void change_state_int (bool enable)                                             = 0;
  virtual void update_correction_property_int (const syn::VideoCorrectProp::raw_ptr info) = 0;

  virtual bool process_int (
    syn::IVideoBuf::raw_ptr h16s,
    syn::IVideoBuf::raw_ptr s16s,
    syn::IVideoBuf::raw_ptr l16s) = 0;
};
}   // namespace libs::ievents::runtime::interf::interfaces
