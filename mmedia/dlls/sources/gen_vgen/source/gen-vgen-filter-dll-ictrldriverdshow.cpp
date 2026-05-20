/**
\file       gen-vgen-filter-dll-ictrldriverdshow.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_gen_vgen
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "gen-vgen-includes_int.hpp"
#include "mmedia/modules/uuu_log/appl/thread/module-log-exception-logger.hpp"
#include "gen-vgen-info-filter-dll.hpp"
#include "gen-vgen-filter-dll.hpp"
#include "mmedia/dlls/doptim/algs/all_algs_impl.hpp"

namespace dlls::sources::gen_vgen
{
void
Filter::update_source_driver_exactly (InfoFilter* finfo, const std::string& name_impl)
{
  U3_ASSERT (!name_impl.empty ());

  std::unique_lock< InfoFilter::sync_type > lock (finfo->wdmtx_, consts::ms_wait_capture_device);
  U3_CHECK (lock.owns_lock (), "update source driver" + TOLOG (name_impl));

  finfo->proxy2hardware_.init (name_impl);

  auto driver = finfo->proxy2hardware_.get_source_impl ();
  U3_CHECK (driver, "empty source driver");

  frozen_dlls_.add (name_impl, finfo->proxy2hardware_.get_source_impl_lib ());

  driver->init ();

  auto pdemons = ::libs::iproperties::helpers::cast_prop_demons ();

  finfo->links_props_.pdriver2buf_ = pdemons->get_bufs_lockfree ();
  finfo->links_props_.pdriver2mem_ = pdemons->get_mem_lockfree ();

  U3_ASSERT (finfo->links_props_.pdriver2buf_);
  U3_ASSERT (finfo->links_props_.pdriver2mem_);

  driver->update_source_info (
    ::dlls::sources::gen_lib::SourceImplInfo (
      finfo->rprops_,
      finfo->capture_props_,
      &finfo->links_props_));

  driver->start ();
}


void
Filter::update_source_driver (InfoFilter* finfo)
{
  //  Тут обработчик исключения, т.к. одно исключение допустимо для переключения на фейковый драйвер в нормальной ситуации.
  try
  {
    update_source_driver_exactly (finfo, finfo->rprops_->name_impl_dll_);
    return;
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
  }

  //  у фальшивого драйвера все всегда должно быть нормально.
  update_source_driver_exactly (finfo, "vss_fake_vgen");
}


void
Filter::init_pts (syn::ConnectInfo* info)
{
  info->count_ins_  = 0;
  info->count_outs_ = 1;

  info->outs_[0].set_info (true);
}
}   // namespace dlls::sources::gen_vgen
