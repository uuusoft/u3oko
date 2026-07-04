/**
\file       appll-part-log-info.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "appll-part-log-info.hpp"

namespace libs::events_log
{
AppllPartLogInfo::AppllPartLogInfo (
  const syn::LogLevels&       msg_state,
  std::string                 subsys,
  std::string                 version,
  const std::source_location& place) :

  msg_state_ (msg_state),
  subsys_ (std::move (subsys)),
  version_ (std::move (version)),
  func_ (place.function_name ()),
  file_ (place.file_name ()),
  line_ (place.line ())
{
  const std::string id_begin = "mmedia";
  auto              beg_indx = file_.find (id_begin);

  if (std::string::npos != beg_indx && beg_indx)
  {
    file_ = file_.substr (beg_indx + id_begin.length () + 1);
  }
}


template< class Archive >
void
AppllPartLogInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (msg_state_);
  arh& BOOST_SERIALIZATION_NVP (subsys_);
  arh& BOOST_SERIALIZATION_NVP (version_);
  arh& BOOST_SERIALIZATION_NVP (func_);
  arh& BOOST_SERIALIZATION_NVP (file_);
  arh& BOOST_SERIALIZATION_NVP (line_);
}
}   // namespace libs::events_log

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::AppllPartLogInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::AppllPartLogInfo);
