#pragma once
/**
\file       os-android-specific-includes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_includes
*/
#ifdef U3_OS_ANDROID
#  include <unistd.h>
#  include <android/log.h>

namespace android::log
{
inline void
android_log_write_helper (std::int32_t id, const std::string& tag, const char* info)
{
  __android_log_write (id, tag.c_str (), info);
}

inline void
android_log_write_helper (std::int32_t id, const char* tag, const char* info)
{
  __android_log_write (id, tag, info);
}
}   // namespace android::log
#endif
