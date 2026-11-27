#pragma once
/**
\file       info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dnodes::uplifters::vmatrix
{
struct InfoFilter final : public ::libs::icore::impl::base::obj::dll::BaseInfoFilter {
  // ext types
  typedef ::libs::events_base::Event props_type;

  InfoFilter ();
  virtual ~InfoFilter () = default;

  auto init () -> void;

  props_type::raw_ptr         rprops_ = nullptr;                            //< Настроенный указатель на свойства (для удобства)
  int                         count_update_correction_value_;               //<
  bool                        m_enable_send     = false;                    //<
  unsigned long               id_               = 0;                        //<
  bool                        req_update_files_ = true;                     //<
  std::vector< int >          m_array_stride_bufs_matrix_effect;            //<
  bool                        use_ext_files_ = false;                       // 10.02.2016 флаг использования раздельных шаблонов для нахождения и замещения блоков
  std::vector< int >          m_array_stride_extended_bufs_matrix_effect;   //<
  std::vector< int >          m_preSin_hue_correction;                      //<
  std::vector< int >          m_preCos_hue_correction;                      //<
  std::vector< std::int16_t > m_preSinCos_hue_corretion;                    //<
};
}   // namespace dnodes::uplifters::vmatrix
