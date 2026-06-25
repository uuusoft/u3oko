/**
\file       video-sender-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2016
\project    u3_video_sender_dll
\brief      Модуль передачи данных в другие подсистемы (http/etc)
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "video-sender-includes_int.hpp"
#include "video-sender-info-filter.hpp"
#include "video-sender-filter-dll.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr
create_impl_vts_video_sender ()
{
  ::libs::icore::impl::var1::obj::dll::IFilter::raw_ptr ret (new ::dlls::terminals::video_sender::Filter);
  return ret;
}
