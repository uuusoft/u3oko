#pragma once
/**
\file       bufs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.05.2016
\project    u3_bufs
\brief      Обявление структуры для группировки связанных буферов с данными
*/

namespace libs::bufs
{
/// Структура для группировки различных вспомогательных буферов, связанным с реальным кадром
/// Например буфера сжатого кадра, буфер разности, буфер оценки движения и прочее
class Bufs final
{
  public:
  // ext types
  using enum_bufs_func_type = std::function< void (const syn::off_buf_type& indx, const syn::IVideoBuf::cptr& buf) >;
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (Bufs)

  Bufs ();
  ~Bufs () = default;

  auto set_buf (const syn::off_buf_type& indx, ::utils::dbufs::video::IVideoBuf::ptr& buf) -> void;
  auto operator[] (const syn::off_buf_type& indx) -> syn::IVideoBuf::raw_ptr;
  auto operator[] (const syn::off_buf_type& indx) const -> syn::IVideoBuf::craw_ptr;
  auto set_base_index (const syn::off_buf_type& indx) -> void;
  auto get_base_index () const -> syn::off_buf_type;
  auto set_flag (const BufsFlags& key, bool val) -> void;
  auto get_flag (const BufsFlags& key) const -> bool;
  auto swap (Bufs& obj) -> void;
  auto clone (const Bufs& src) -> void;
  auto reset (bool only_indxs) -> void;
  auto enum_bufs (enum_bufs_func_type funct) const -> void;

  private:
  //  internal typess
  using video_bufs_type = std::unordered_map< syn::off_buf_type, syn::IVideoBuf::ptr >;
  using flags_type      = ::libs::helpers::utils::ValuesStorage< BufsFlags, bool, BufsFlags::max_bound, false >;

  syn::off_buf_type       base_buf_index_ = utils::dbufs::video::consts::offs::raw;   //< Индекс базового буфера, который будет ответственен за свойства, общие для всего списка
  mutable video_bufs_type childs_;                                                    //< Набор дочерних буферов
  flags_type              flags_;                                                     //< Флаги, разделяемые между всеми буферами
};
}   // namespace libs::bufs
