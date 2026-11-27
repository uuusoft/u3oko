/**
\file       video-sender-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2016
\brief      Модуль передачи данных в другие подсистемы (http/etc)
*/
#include "video-sender-includes_int.hpp"
#include "video-sender-info-filter.hpp"
#include "video-sender-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vts_video_sender () -> ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr
{
  ::libs::icore::impl::base::obj::dll::IFilter::raw_ptr ret (new ::dnodes::terminals::video_sender::Filter);
  return ret;
}
