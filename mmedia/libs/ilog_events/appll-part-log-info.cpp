/**
\file       appll-part-log-info.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "appll-part-log-info.hpp"

namespace libs::ilog_events
{
AppllPartLogInfo::AppllPartLogInfo (
  const syn::LogLevels&       msg_state,
  const std::string&          subsys,
  const std::string&          version,
  const std::source_location& place) :

  msg_state_ (msg_state),
  subsys_ (subsys),
  version_ (version),
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


AppllPartLogInfo::~AppllPartLogInfo ()
{
}


template< class Archive >
void
AppllPartLogInfo::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (msg_state_);
  ar& BOOST_SERIALIZATION_NVP (subsys_);
  ar& BOOST_SERIALIZATION_NVP (version_);
  ar& BOOST_SERIALIZATION_NVP (func_);
  ar& BOOST_SERIALIZATION_NVP (file_);
  ar& BOOST_SERIALIZATION_NVP (line_);
}
}   // namespace libs::ilog_events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::AppllPartLogInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::AppllPartLogInfo);
