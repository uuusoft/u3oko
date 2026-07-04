#pragma once
/**
\file       detect-face-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_detect_face
*/

namespace dlls::detectors::detect_face
{
///  Свойства фильтра по детектированию движения
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  syn::VideoDetectProp::raw_ptr rprops_ = nullptr;   //< Уже настроенный указатель на свойства фильтра props_
  dlib::frontal_face_detector   detector_;           //< Детектор лица из dlib, debug создается примерно полторы минуты и работает так же крайне медленно

  private:
  auto init () -> void;
};
}   // namespace dlls::detectors::detect_face
