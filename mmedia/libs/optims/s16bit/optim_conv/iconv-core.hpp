#pragma once
/**
\file       iconv-core.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.09.2016
\project    u3_optim_conv
*/

namespace libs::optim::s16bit::conv
{
template< typename TTElement, std::uint32_t aligned_size, std::uint32_t size >
class IConvCore final
{
  public:
  //  ext types
  const std::uint32_t aligned_ = aligned_size;
  const std::uint32_t size_    = size;

  using raw_elements_type = std::array< TTElement, aligned_size * size >;

  IConvCore ()
  {
    std::fill (vals_.begin (), vals_.end (), TTElement (0));
  }

  explicit IConvCore (const raw_elements_type& vals)
  {
    vals_ = vals;
  }

  explicit IConvCore (const std::vector< TTElement >& vals, bool sload)
  {
    U3_CHECK (load (vals), "failde load vals");
  }

  ~IConvCore ()
  {
  }

  bool
  load (const std::vector< TTElement >& vals)
  {
    if (vals.size () < size_ * size_)
    {
      U3_ASSERT_SIGNAL ("failed");
      return false;
    }

    for (std::uint32_t indxy = 0; indxy < size_; ++indxy)
    {
      for (std::uint32_t indxx = 0; indxx < size_; ++indxx)
      {
        get (indxx, indxy) = vals[size_ * indxy + indxx];
      }
    }
    return true;
  }

  const TTElement*
  raw_vals () const
  {
    return &vals_.front ();
  }

  const TTElement&
  get (std::uint32_t indxx, std::uint32_t indxy) const
  {
    U3_ASSERT (indxx < size);
    U3_ASSERT (indxy < size);
    return vals_[indxy * aligned_size + indxx];
  }

  TTElement&
  get (std::uint32_t indxx, std::uint32_t indxy)
  {
    U3_ASSERT (indxx < size);
    U3_ASSERT (indxy < size);
    return vals_[indxy * aligned_size + indxx];
  }

  const TTElement&
  center_val () const
  {
    return get (size_ / 2 + 1 - 1, size_ / 2 + 1 - 1);
  }

  TTElement&
  center_val ()
  {
    return get (size_ / 2 + 1 - 1, size_ / 2 + 1 - 1);
  }

  void
  fill (const TTElement& val)
  {
    for (std::uint32_t indxy = 0; indxy < size_; ++indxy)
    {
      for (std::uint32_t indxx = 0; indxx < size_; ++indxx)
      {
        get (indxx, indxy) = val;
      }
    }
  }

  //  temp
  TTElement
  summ () const
  {
    TTElement ret (0);

    for (std::uint32_t indxy = 0; indxy < size_; ++indxy)
    {
      for (std::uint32_t indxx = 0; indxx < size_; ++indxx)
      {
        ret += get (indxx, indxy);
      }
    }

    return ret;
  }

  private:
  U3_ALIGN_DEFAULT raw_elements_type vals_;   //<
};
}   // namespace libs::optim::s16bit::conv
