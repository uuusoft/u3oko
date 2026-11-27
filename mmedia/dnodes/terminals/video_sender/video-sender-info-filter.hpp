#pragma once
/**
\file       video-sender-info-filter.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dnodes::terminals::video_sender
{
struct InfoFilter : public ::libs::icore::impl::base::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  syn::EndPointProp::raw_ptr rprops_       = nullptr;   //< Настроенный указатель на свойства (для удобства)
  std::uint64_t              count_frames_ = 0;         //< Счетчик обработанных кадров
  syn::IBaseId::weak_ptr     active_impl_;              //< Интерфейс для маршрутизации данных
};
}   // namespace dnodes::terminals::video_sender
