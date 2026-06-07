#pragma once
/**
\file       buf2module-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.09.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::props::base_id
{
using id_link_type     = ::libs::ilink::consts::id_link_type;
using source_name_type = std::string;

struct Buff2ModuleInfo final {
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Buff2ModuleInfo)

  explicit Buff2ModuleInfo (
    float                                                    fps            = 0.0F,
    const ::utils::dbufs::video::consts::offs::off_buf_type& indx_buf       = ::utils::dbufs::video::consts::offs::invalid,
    const id_link_type&                                      dest_module_id = "");

  virtual ~Buff2ModuleInfo () = default;

  float                                             fps_;              //<
  ::utils::dbufs::video::consts::offs::off_buf_type indx_buf_;         //<
  id_link_type                                      dest_module_id_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void            tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Buff2ModuleInfo& src);
Buff2ModuleInfo tag_invoke (::boost::json::value_to_tag< Buff2ModuleInfo >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::base_id

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::base_id::Buff2ModuleInfo);
