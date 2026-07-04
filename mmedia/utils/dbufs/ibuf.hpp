#pragma once
/**
\file       ibuf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_dbufs
*/

namespace utils::dbufs
{
/// Базовый интерфейс хранения буфера в памяти под кадр (звук/видео)
class IBuf
{
  public:
  //  ext types
  using mem_var_type = std::uint64_t;

  U3_ADD_POINTERS_TO_SELF (IBuf)
  U3_ADD_DELETE_MOVE_COPY (IBuf)

  virtual ~IBuf () = default;

  void
  set_mem_var (const MemVars& type, const mem_var_type& val)
  {
    set_mem_var_int (type, val);
  }

  mem_var_type
  operator[] (const MemVars& type) const
  {
    return get_mem_var_int (type);
  }

  void
  clone (IBuf::ptr& source, float perc_copy)
  {
    clone_int (source.get (), perc_copy);
  }

  void
  clone (IBuf::craw_ptr source, float perc_copy)
  {
    clone_int (source, perc_copy);
  }

  void
  swap (IBuf& buf)
  {
    swap_int (buf);
  }

  std::uint8_t*
  get_buf ()
  {
    return get_buf_int ();
  }

  const std::uint8_t*
  get_cbuf () const
  {
    return get_cbuf_int ();
  }

  protected:
  IBuf () = default;

  private:
  //  IBuf interface
  virtual auto set_mem_var_int (const MemVars&, mem_var_type) -> void = 0;
  virtual auto get_mem_var_int (const MemVars&) const -> mem_var_type = 0;
  virtual auto get_buf_int () -> std::uint8_t*                        = 0;
  virtual auto get_cbuf_int () const -> const std::uint8_t*           = 0;
  virtual auto clone_int (IBuf::craw_ptr, float) -> void              = 0;
  virtual auto swap_int (IBuf&) -> void                               = 0;
};
}   // namespace utils::dbufs
