#pragma once
/**
\file       get_appl_folder.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_iproperties_lib
*/

namespace libs::iproperties::appl_paths::helpers
{
inline std::string
get_appl_folder (const std::string& name_appl)
{
  U3_CHECK (!name_appl.empty (), "name_appl empty");
  std::string ret;

#if defined(U3_OS_WIN32_DESKTOP)
  {
    char tbuf[2 * MAX_PATH + 2];
    tbuf[0] = '\0';

    if (FAILED (SHGetFolderPathA (0, CSIDL_LOCAL_APPDATA, 0, SHGFP_TYPE_DEFAULT, tbuf)))
    {
      U3_ASSERT_SIGNAL ("failed");
      return ret;
    }

    ret = ::libs::helpers::files::make_path (std::string (tbuf), name_appl);
  }
#elif defined(U3_OS_ANDROID)
  ret = get_current_folder ();
  ret.clear ();
#else
  ret = get_current_folder ();
#endif
  return ret;
}


inline std::string
get_data_folder (const std::string& name_appl, const std::string& name_service)
{
  std::string ret;

#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_MACX_DESKTOP) || defined(U3_OS_ORANGE_PI)
  ret = get_appl_folder (name_appl);
#elif defined(U3_OS_ANDROID)
  auto                            orinfo = U3_CAST_PROP (vers::system::ISystemProperty::raw_ptr) (iproperties::helpers::get_shared_prop_os ());
  syn::ISharedProperty::lock_type lock (orinfo->get_sync ());
  ret = orinfo->get_mdata_lockfree ();
#else
#  error select OS
#endif
  return ::libs::helpers::files::make_path (ret, name_service);
}
}   // namespace libs::iproperties::appl_paths::helpers
