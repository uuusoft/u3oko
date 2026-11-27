#pragma once
/**
\file       TInfoForTextEffects.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017

*/

namespace dnodes::uplifters::vcorrectxxx
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
struct TInfoForTextEffects {
  typedef boost::array< core::obj::dll::CInfoBuff, NUMBER_BUFFERS_TEXT_EFFECT > TTextEffectsBufs;

  ::dnodes::sources::dshow_vgen::graph::dshow::TIntInfoForTextEffects m_user_info;
  bool                                                              m_use_struct;
  bool                                                              m_need_refresh_internal_state;
  TTextEffectsBufs                                                  bufs_;

  TInfoForTextEffects ()
  {
    m_use_struct                  = false;
    m_need_refresh_internal_state = true;
  }

  ~TInfoForTextEffects ()
  {
    HRESULT hr = S_OK;

    for (uint32_t indx1 = 0; indx1 < bufs_.size (); ++indx1)
    {
      // 27.03.2016
      hr = ::dnodes::sources::dshow_vgen::dshow::throw_ifn (bufs_[indx1].updateSize (16, 1));
    }
  }

  HRESULT
  resize_int_bufs (uint32_t new_width, std::uint32_t new_height)
  {
    HRESULT       hr             = S_OK;
    std::uint32_t loc_new_width  = new_width;
    std::uint32_t loc_new_height = new_height;

    for (uint32_t indx_buf = 0; indx_buf < bufs_.size (); ++indx_buf)
    {
      core::obj::dll::CInfoBuff& loc_current_buf = bufs_[indx_buf];

      hr = ::dnodes::sources::dshow_vgen::dshow::throw_ifn (loc_current_buf.updateSize (loc_new_width, loc_new_height));
    }
    return hr;
  }

  private:
  TInfoForTextEffects (const TInfoForTextEffects& source);
};
#endif
}   // namespace dnodes::uplifters::vcorrectxxx
