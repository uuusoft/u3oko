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
  U3_ADD_POINTERS_TO_SELF (Bufs)

  Bufs ();
  ~Bufs () = default;

  auto set_buf (const syn::off_buf_type&, syn::IVideoBuf::ptr&) -> void;
  auto operator[] (const syn::off_buf_type&) -> syn::IVideoBuf::raw_ptr;
  auto operator[] (const syn::off_buf_type&) const -> syn::IVideoBuf::craw_ptr;
  auto set_base_index (const syn::off_buf_type&) -> void;
  auto get_base_index () const -> syn::off_buf_type;
  auto set_flag (const BufsFlags&, bool) -> void;
  auto get_flag (const BufsFlags&) const -> bool;
  auto swap (Bufs&) noexcept -> void;
  auto clone (const Bufs&) -> void;
  auto reset (bool) -> void;
  auto enum_bufs (const enum_bufs_func_type&) const -> void;

  private:
  //  internal typess
  using video_bufs_type = boost::unordered_flat_map< syn::off_buf_type, syn::IVideoBuf::ptr >;
  using flags_type      = ::libs::utility::utils::ValuesStorage< BufsFlags, bool, BufsFlags::max_bound, false >;

  syn::off_buf_type       base_buf_index_ = syn::offs::raw;   //< Индекс базового буфера, который будет ответственен за свойства, общие для всего списка
  mutable video_bufs_type childs_;                            //< Набор дочерних буферов
  flags_type              flags_;                             //< Флаги, разделяемые между всеми буферами
};
}   // namespace libs::bufs
