//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       storage-module-int-functs.cpp
\date       23.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "storage-module.hpp"

namespace modules { namespace uuu_storage { namespace appl {

void
StorageModule::sync_status_impls ()
{
  const auto _status = stop_module_ ? appl::impl::StateImplsType::stop : appl::impl::StateImplsType::run;

  if (storage_impl_)
    {
      storage_impl_->change_state (_status);
    }
  if (indexer_impl_)
    {
      indexer_impl_->change_state (_status);
    }
  return;
}


void
StorageModule::create_impls (mevents::storage::PropertyStorageModuleEvent::raw_ptr _props)
{
  storage_impl_ = storage_impl_ ? storage_impl_ : get_storage_impl ();
  indexer_impl_ = indexer_impl_ ? indexer_impl_ : get_indexer_impl ();

  indexer_impl_->set_info (_props->get_paths ().empty () ? nullptr : &_props->get_paths ().front ());
  storage_impl_->set_info (_props->get_paths ().empty () ? nullptr : &_props->get_paths ().front ());
  return;
}


bool
StorageModule::check_acesss_rights (const stream_id_type& _id, const TypeActionStream& _op) const
{
  auto _find = streams_rights_.find (_id);
  if (streams_rights_.end () == _find)
    {
      XULOG_ERROR ("failed find stream for check access rights");
      return false;
    }
  return _op == _find->second;
}


void
StorageModule::load_binary_statistic ()
{
  if (!storage_impl_)
    {
      return;      // Допустимо.
    }
  impl::IStorageImpl::ids_chunk_type _ids;
  UASSERT_SIGNAL ("umimplemented");
#if 0
  storage_impl_->get_all_ids (_ids);
  auto _locker = storage_impl_->lock_ids (_ids);
  storage_impl_->get_info_ids (_locker);
  storage_impl_->unlock_ids (_locker);
#endif
  return;
}

}}}      // namespace modules::uuu_storage::appl
