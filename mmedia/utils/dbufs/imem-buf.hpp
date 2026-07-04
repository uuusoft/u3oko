#pragma once
/**
\file       imem-buf.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.08.2018
\project    u3_dbufs
*/

namespace utils::dbufs::allocator
{
//  forward
class BufAllocator;
}   // namespace utils::dbufs::allocator

namespace utils::dbufs
{
class IMemBuf : public IBuf
{
  public:
  //  ext types
  using fragments_type = std::list< mem_var_type >;

  U3_ADD_POINTERS_TO_SELF (IMemBuf)
  U3_ADD_DELETE_MOVE_COPY (IMemBuf);

  virtual ~IMemBuf () = default;

  auto
  getraw_buf () const -> ::libs::utility::mem::IBlockMem::ptr
  {
    return raw_block_;
  }

  auto
  get_fragments () const -> const fragments_type&
  {
    return fragments_;
  }

  auto
  set_fragments (const fragments_type& src) -> void
  {
    fragments_ = src;
  }

  protected:
  //  internal typess
  using mem_vars_type = ::libs::utility::utils::ValuesStorage< MemVars, mem_var_type, MemVars::max_bound, 0u >;

  //  IBuf overrides
  virtual auto set_mem_var_int (const MemVars&, mem_var_type) -> void override;
  virtual auto get_mem_var_int (const MemVars&) const -> mem_var_type override;
  virtual auto clone_int (IBuf::craw_ptr, float) -> void override;
  virtual auto swap_int (IBuf&) -> void override;
  virtual auto get_buf_int () -> std::uint8_t* override;
  virtual auto get_cbuf_int () const -> const std::uint8_t* override;

  auto ialloc (const mem_var_type&) -> void;
  auto flush () -> void;

  IMemBuf () = default;

  private:
  mutable syn::IBlockMem::ptr raw_block_ = nullptr;   //<
  mem_vars_type               mem_vars_;              //<
  fragments_type              fragments_;             //<
};
}   // namespace utils::dbufs
