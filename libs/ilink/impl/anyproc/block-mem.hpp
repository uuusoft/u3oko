#pragma once
/**
\file       block-mem.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace anyproc {
/**
  \brief  empty brief
  */
struct BlockMem : public ::libs::link::mem::IBlockMem
{
  using handle_t = managed_shared_memory::handle_t;

  BlockMem () :
    hmem_ (0), size_ (0)
  {}


  virtual ~BlockMem ()
  {}


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
    return;
  }

  handle_t    hmem_;           //< ???
  std::size_t size_;           //< ???
  std::string mtx_name_;       //< ???
  std::string sync_name_;      //< ???


  private:
  friend class boost::serialization::access;

  template <class Archive>
  void
  serialize (Archive& ar, const unsigned int /* file_version */)
  {
    ar& BOOST_SERIALIZATION_NVP (hmem_);
    ar& BOOST_SERIALIZATION_NVP (mtx_name_);
    ar& BOOST_SERIALIZATION_NVP (sync_name_);
    ar& BOOST_SERIALIZATION_NVP (size_);
    UASSERT (check ());
    return;
  }
};

}}}}      // namespace libs::ilink::impl::anyproc
