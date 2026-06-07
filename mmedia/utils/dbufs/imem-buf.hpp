#pragma once
/**
\file       imme-buf.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  using fragments_type = std::list< mem_type >;

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (IMemBuf)

  virtual ~IMemBuf () = default;

  IMemBuf (const IMemBuf& _rsc)           = delete;
  IMemBuf& operator= (const IMemBuf& src) = delete;

  ::libs::helpers::mem::IBlockMem::ptr
  getraw_buf () const
  {
    return raw_;
  }

  const fragments_type&
  get_fragments () const
  {
    return fragments_;
  }

  void
  set_fragments (const fragments_type& src)
  {
    fragments_ = src;
  }

  protected:
  //  internal typess
  using mem_vars_type = ::libs::helpers::utils::ValuesStorage< MemVars, mem_type, MemVars::max_bound, 0u >;

  //  IBuf overrides
  virtual void                set_mem_var_int (const MemVars&, mem_type) override;
  virtual mem_type            get_mem_var_int (const MemVars&) const override;
  virtual void                clone_int (IBuf::craw_ptr, float) override;
  virtual void                swap_int (IBuf&) override;
  virtual std::uint8_t*       get_buf_int () override;
  virtual const std::uint8_t* get_cbuf_int () const override;

  void ialloc (const mem_type& size);
  void flush ();

  IMemBuf () = default;

  private:
  mutable ::libs::helpers::mem::IBlockMem::ptr raw_ = nullptr;   //<
  mem_vars_type                                mem_vars_;        //<
  fragments_type                               fragments_;       //<
};
}   // namespace utils::dbufs
