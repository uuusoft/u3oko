#pragma once
/**
\file       block-mem.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::impl::anyproc
{
struct BlockMem : public ::libs::link::mem::IBlockFakeMem {
  using handle_t = boost::interprocess::managed_shared_memory::handle_t;

  BlockMem ()          = default;
  virtual ~BlockMem () = default;

  bool
  check () const
  {
    return hmem_ && !mtx_name_.empty () && !sync_name_.empty () && size_;
  }

  void
  reset ()
  {
    hmem_ = 0;
    size_ = 0;
    mtx_name_.clear ();
    sync_name_.clear ();
  }

  handle_t    hmem_ = 0;    //<
  std::size_t size_ = 0;    //<
  std::string mtx_name_;    //<
  std::string sync_name_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void
  serialize (Archive& arh, const std::uint32_t /* file_version */)
  {
    arh& BOOST_SERIALIZATION_NVP (hmem_);
    arh& BOOST_SERIALIZATION_NVP (mtx_name_);
    arh& BOOST_SERIALIZATION_NVP (sync_name_);
    arh& BOOST_SERIALIZATION_NVP (size_);
    U3_ASSERT (check ());
  }
};
}   // namespace libs::ilink::impl::anyproc
